//
//  main.cpp
//  Project Two
//
//  Created by Austin Ketron on 2/20/25.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Define Course struct
struct Course {
    string courseNumber;
    string title;
    vector<string> preReqs;
};

// Define BST class
class BinarySearchTree {
private:
    struct Node {
        Course course;
        Node* left;
        Node* right;
        
        Node() : left(nullptr), right(nullptr) {}
        Node(Course aCourse) : course(aCourse), left(nullptr), right(nullptr) {}
    };

    Node* root; // Track the root

    // Helper functions for BST operations
    void addNode(Node* node, Course course);
    void inOrder(Node* node, vector<Course>& sortedCourses);
    Node* removeNode(Node* node, string courseNumber);
    Node* minValueNode(Node* node);
    Course searchNode(Node* node, string courseNumber);

public:
    BinarySearchTree() : root(nullptr) {}
    virtual ~BinarySearchTree() {}
    void InOrder(vector<Course>& sortedCourses);
    void Insert(Course course);
    void Remove(string courseNumber);
    Course Search(string courseNumber);
};

// Add a node to the tree
void BinarySearchTree::addNode(Node* node, Course course) {
    if (course.courseNumber < node->course.courseNumber) {
        if (node->left == nullptr) {
            node->left = new Node(course);
        } else {
            addNode(node->left, course);
        }
    } else {
        if (node->right == nullptr) {
            node->right = new Node(course);
        } else {
            addNode(node->right, course);
        }
    }
}

// Insert a course into the tree
void BinarySearchTree::Insert(Course course) {
    if (root == nullptr) {
        root = new Node(course);
    } else {
        addNode(root, course);
    }
}

// InOrder traversal to get sorted courses
void BinarySearchTree::InOrder(vector<Course>& sortedCourses) {
    inOrder(root, sortedCourses);
}

void BinarySearchTree::inOrder(Node* node, vector<Course>& sortedCourses) {
    if (node != nullptr) {
        inOrder(node->left, sortedCourses);
        sortedCourses.push_back(node->course);
        inOrder(node->right, sortedCourses);
    }
}

// Search for a course in the tree
Course BinarySearchTree::Search(string courseNumber) {
    return searchNode(root, courseNumber);
}

Course BinarySearchTree::searchNode(Node* node, string courseNumber) {
    if (node == nullptr || node->course.courseNumber == courseNumber) {
        return node ? node->course : Course();
    }
    if (courseNumber < node->course.courseNumber) {
        return searchNode(node->left, courseNumber);
    }
    return searchNode(node->right, courseNumber);
}

// Load courses from a file
bool loadCoursesFromFile(const string& filename, BinarySearchTree& bst) {
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error opening file: " << filename << endl;
        return false;
    }

    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        Course course;
        getline(ss, course.courseNumber, ',');
        getline(ss, course.title, ',');

        string prereq;
        while (getline(ss, prereq, ',')) {
            course.preReqs.push_back(prereq);
        }
        bst.Insert(course);
    }
    infile.close();
    return true;
}

// Menu
void printMenu() {
    cout << "Menu Options:\n";
    cout << "1. Load Courses\n";
    cout << "2. Print All Courses\n";
    cout << "3. Print Course Information\n";
    cout << "9. Exit\n";
    cout << "Enter your choice: ";
}

void printCourse(const Course& course) {
    cout << "Course Number: " << course.courseNumber << "\n";
    cout << "Course Title: " << course.title << "\n";
    cout << "Prerequisites: ";
    for (const auto& prereq : course.preReqs) {
        cout << prereq << " ";
    }
    cout << "\n";
}

int main() {
    BinarySearchTree bst;
    int choice;
    
    while (true) {
        printMenu();
        cin >> choice;
        
        switch (choice) {
            case 1: {
                if (loadCoursesFromFile("CS 300 ABCU_Advising_Program_Input.csv", bst)) {
                    cout << "Courses loaded successfully";
                }
                break;
            case 2: {
                vector<Course> courses;
                bst.InOrder(courses);
                for (const auto& course : courses) {
                    printCourse(course);
                }
                break;
            }
            case 3: {
                string courseNumber;
                cout << "Enter course number: ";
                cin >> courseNumber;
                Course course = bst.Search(courseNumber);
                if (!course.courseNumber.empty()) {
                    printCourse(course);
                } else {
                    cout << "Course not found.\n";
                }
                break;
            }
            case 9:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice.\n";
            }
        }
    }
}
