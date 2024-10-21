//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Rich Knoll
// Version     : 1.0
// Copyright   : Copyright © 2023 SNHU COCE
// Description : Project Two - Linked List
//============================================================================

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// course data structure
struct Course {
	string courseID;
	string courseDescription;
	string preReq1;
	string preReq2;
	// Default constructor
	Course() {
		courseID = "";
		courseDescription = "";
		preReq1 = "";
		preReq2 = "";
	}
};


// Course structs will be stored within a linked list for access and manipulation
class LinkedList {

private:
	
	// Internal structure for list entries
	struct Node {
		Course course;
		Node* next;

		// Default constructor
		Node() {
			next = nullptr;
		}

		// Initialized with a course
		Node(Course acourse) : Node() {
			course = acourse;
		}
	};

	// Initiate head node and tail node as well as size for linked list
	Node* head;
	Node* tail;
	int size = 0;

public:
	LinkedList();
	virtual ~LinkedList();
	void loadFile(string fileName);
	Course individualCourse(string courseID);
	void sortedList();

};

// Default constructor
LinkedList::LinkedList() {
	head = nullptr;
	tail = nullptr;
}

// Destructor
LinkedList::~LinkedList() {
	Node* current = head;
	Node* temp;

	// loop over each node, detach from list then delete
	while (current != nullptr) {
		temp = current; // hang on to current node
		current = current->next; // make current the next node
		delete temp; // delete the orphan node
	}
}


// Load file and create linked list
void LinkedList::loadFile(string fileName) {
	// Input file strream
	ifstream inputFile;

	// Open file
	inputFile.open(fileName);

	// Message if file does not open 
	if (!inputFile.is_open()) {
		std::cout << "Could not open file!" << endl;
	}

	// Initiate line variable used to hold each line of csv file
	string line = "";

	// While loop for parsing through csv file
	while (getline(inputFile, line)) {

		// variables for each attribute of csv file
		string courseID;
		string courseDescription;
		string preReq1;
		string preReq2;

		// creates string of each line that can be further parsed through
		stringstream inputString(line);

		// stores each attribute of everyline the previously declared variables
		getline(inputString, courseID, ',');
		getline(inputString, courseDescription, ',');
		getline(inputString, preReq1, ',');
		getline(inputString, preReq2, ',');

		// new course structure created to hold all the course information
		Course* thisCourse = new Course();
		thisCourse->courseID = courseID;
		thisCourse->courseDescription = courseDescription;
		thisCourse->preReq1 = preReq1;
		thisCourse->preReq2 = preReq2;

		Node* newNode = new Node();
		newNode->course.courseID = courseID;
		newNode->course.courseDescription = courseDescription;
		newNode->course.preReq1 = preReq1;
		newNode->course.preReq2 = preReq2;
		newNode->next = nullptr;

		//if there is nothing at the head...
			// new node becomes the head and the tail
		if (head == nullptr) {
			head = newNode;
			tail = newNode;
		}
		//else 
			// make current tail node point to the new node
			// and tail becomes the new node
		else {
			tail->next = newNode;
			tail = newNode;
		}
		//increase size count
		size += 1;
		
		line = "";
	}	
}

// Print the course title and the prerequisites for any individual course
Course LinkedList::individualCourse(string courseID) {
	// special case if matching bid is the head
	if (head->course.courseID == courseID) {
		return head->course;
	}
	else {
		// start at the head of the list
		Node* current = head->next;
		// keep searching until end reached with while loop (current != nullptr)
		while (current != nullptr) {
			// if the current node matches, return current bid
			if (current->course.courseID == courseID) {
				return current->course;
			}
			// else current node is equal to next node
			else {
				current = current->next;
			}
		}
		Course emptyCourse = Course();
		return emptyCourse;

	}
}

void LinkedList::sortedList() {
	// Create vector of course descriptions from linked list
	vector<string> courseList(size);
	Node* current = head;
	int k = 0;
	while (current != nullptr) {
		courseList[k] = current->course.courseDescription;
		k += 1;
		current = current->next;
	}

	// Sort items in the vector alphanumerically
	int i = 0;
	int j = 0;
	string temp;
	for (i = 1; i < courseList.size(); ++i) {
		j = i;
		while (j > 0 && courseList[j] < courseList[j - 1]) {
			temp = courseList[j];
			courseList[j] = courseList[j - 1];
			courseList[j - 1] = temp;
			--j;
		}
	}
	// Print sorted course descriptions
	cout << "Sorted course list:" << endl;
	for (int i = 0; i < courseList.size(); ++i) {
		cout << courseList[i] << endl;
	}
}



int main()
{
	// Ask user for file name
	// CS 300 ABCU_Advising_Program_Input.csv
	std::cout << "Enter program file name:";
	string programName;
	getline(cin, programName);
	std::cout << endl;

	// Declare linked List
	LinkedList classList;

	// Menu
	int choice = 0;
	while (choice != 9) {
		std::cout << "Menu" << endl;
		std::cout << "  1. Load File" << endl;
		std::cout << "  2. Print Alphanumeric List" << endl;
		std::cout << "  3. Print Individual Course Info" << endl;
		std::cout << "  9. Exit" << endl;
		std::cout << "Endter Choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			classList.loadFile(programName);
			break;
		case 2:
			classList.sortedList();
			break;
		case 3:
			string courseID;
			Course searchedCourse;
			cout << endl;
			cout << "Enter Course ID: ";
			cin >> courseID;
			searchedCourse = classList.individualCourse(courseID);
			cout << "Course Title: " << searchedCourse.courseDescription << endl;
			cout << "Pre-Requisite #1: " << searchedCourse.preReq1 << endl;
			cout << "Pre-Requisite #2: " << searchedCourse.preReq2 << endl;
			cout << endl;
			break;
		}
	}
	std::cout << "Goodbye!" << endl;
	return 0;

	
}

