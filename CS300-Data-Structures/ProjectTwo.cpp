#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <limits>
using namespace std;

/**
 * Converts a string to uppercase.
 * Used for case-insensitive course number comparisons.
 * 
 * @param str The string to convert
 * @return The uppercase version of the input string
 */
string toUpper(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

/**
 * Removes leading and trailing whitespace from a string.
 * 
 * @param str The string to trim
 * @return The trimmed string
 */
string trim(string str) {
    str.erase(0, str.find_first_not_of(" \t\r\n"));
    str.erase(str.find_last_not_of(" \t\r\n") + 1);
    return str;
}

/**
 * Represents a single course in the course.
 * courseNumber - Unique course identifier (e.g., "CSCI101")
 * courseTitle - The title of the course  (e.g., "Introduction to Computer Science")  
 * prerequisites - Vector of course numbers that are prerequisites for this course (e.g., ["MATH101", "CSCI100"])
 */
struct Course {
    string courseNumber;          
    string courseTitle;             
    vector<string> prerequisites;  
    
    /**
     * Default constructor.
     * Initializes an empty course with no data.
     * Prerequisites vector is automatically initialized as empty by vector's constructor
     */
    Course() {
        courseNumber = "";
        courseTitle = "";
        
    }
    
    /**
     * Parameterized constructor.
     * Creates a course with specified attributes.
     * 
     * @param number The unique course identifier 
     * @param name The course title
     * @param prereqs Vector of prerequisite course numbers
     */
    Course(string number, string name, vector<string> prereqs) {
        courseNumber = number;
        courseTitle = name;  
        prerequisites = prereqs;
    }
};

/**
 * Loads course data from a CSV file and validates the data structure.
 * Performs two-pass validation: first collects all course numbers,
 * then validates that all prerequisites exist in the course list.
 * 
 * @param filename The path to the CSV file to load
 * @param courses Output vector to store validated Course objects
 * @return true if file was successfully loaded or false if an error happened
 */
bool LoadCoursesFromFile(const string& filename, vector<Course>& courses) {
    ifstream file(filename);// Open the file for reading
    
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return false;
    }

    unordered_set<string> validCourseNumbers;  
    vector<vector<string>> allCourseData;      
    string line;  
    
    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        
        vector<string> dataPieces; 
        stringstream ss(line); 
        string piece; 
        
        /**
         * Parse CSV line into individual fields.
         * Reads each comma-separated value from the stringstream ss and stores it in the variable piece.
         * Piece is stored at the end of the dataPieces vector
         * Each line created must have at least 2 elements (course number and title)
         * 
         * Example: "CSCI101, Intro to Programming, MATH101" becomes:
         *   dataPieces[0] = "CSCI101"
         *   dataPieces[1] = "Intro to Programming"
         *   dataPieces[2] = "MATH101"
         */
        while (getline(ss, piece, ',')) {
            piece = trim(piece); 
            dataPieces.push_back(piece); 
        }
        
        if (dataPieces.size() < 2) {
            cerr << "Invalid: Line has invalid amount, cannot be less than 2 fields" << endl;
            file.close();
            return false;
        }
        
        // Store the course number from the current line into validCourseNumbers set
        validCourseNumbers.insert(toUpper(dataPieces[0]));
        
        // Store the entire line's data 
        allCourseData.push_back(dataPieces);
    }
    
    file.close();
   
    /**
     * For each course, checks indices 2+ (prerequisites) against the Set
     * of valid course numbers collected in the first pass allCourseData.
     */
    for (const auto& currentCourse : allCourseData) {
        if (currentCourse.size() > 2) {
            for (size_t i = 2; i < currentCourse.size(); ++i) {
                string prerequisite = toUpper(currentCourse[i]);
                
                if (!validCourseNumbers.count(prerequisite)) {
                    cerr << "Error: Prerequisite " << prerequisite 
                         << " for course " << currentCourse[0] << " does not exist" << endl;
                    return false;
                }
            }
        }
    }
    
    courses.clear();  
    
    // Create Course objects from validated data and store in courses vector
    for (const auto& dataPieces : allCourseData) {
        string courseNumber = toUpper(dataPieces[0]);
        string courseTitle = dataPieces[1];
        vector<string> prerequisites;
        
        if (dataPieces.size() > 2) {
            for (size_t i = 2; i < dataPieces.size(); ++i) {
                prerequisites.push_back(toUpper(dataPieces[i]));
            }
        }
        
        Course newCourse(courseNumber, courseTitle, prerequisites);
        courses.push_back(newCourse);
    }

    return true;
}


/**
 * Represents a node in the binary search tree.
 * Each node contains a Course object and pointers to left and right children.
 * Course -The actual data stored at this node
 * left - Pointer to left child (courses with smaller course numbers)
 * right - Pointer to right child (courses with larger course numbers)
 */
struct Node {
    Course course;   
    Node* left;      
    Node* right;     
    
    /**
     * Constructor for creating a new node.
     * Initializes the node with a course and sets child pointers to nullptr.
     * 
     * @param courseData The Course object to store in this node
     */
    Node(Course courseData) {
        course = courseData;
        left = nullptr;   
        right = nullptr;  
    }
};

/**
 * Binary Search Tree implementation for storing and managing courses.
 * Courses are organized alphabetically by course number for efficient searching.
 */
class BinarySearchTree {
private:
    // Root is the entry point to the entire tree
    Node* root;
    
    /**
     * Recursive helper function for inserting a course into the tree.
     * Traverses the tree to find the appropriate position based on course number.
     * Compare course numbers to determine which direction to go
     * String comparison works alphabetically (CSCI101 < CSCI201)
     * 
     * @param node The current node being examined
     * @param course The Course object to insert
     */
    void insertHelper(Node* node, Course course) {
        if (course.courseNumber < node->course.courseNumber) {
            // if less than the current node, check if left child exists

            if (node->left == nullptr) {
                // If no left child exists, this is where we insert the new course
                // Call the new operator to create a new Node with the course and assign it to the left child pointer
                node->left = new Node(course);
            } else {
                // If the left child exists, continue searching down left subtree
                // Using the recursive call on the current node's left child
                insertHelper(node->left, course);
            }
        } else {
            // Else if course number is greater than the current node's course number check if right child exists
            if (node->right == nullptr) {
                // If no right child exists, this is where we insert the new course
                // Call the new operator to create a new Node with the course and assign it to the right child pointer
                node->right = new Node(course);
            } else {
                // If the right child exists, continue searching down right subtree
                // Using the recursive call on the current node's right child
                insertHelper(node->right, course);
            }
        }
    }
    

    /**
     * Recursive helper function for in-order traversal.
     * Prints courses in alphabetically sorted order.
     * Order: Left subtree → Current → Right subtree
     * 
     * @param node The current node being processed
     */
    void inOrderPrintHelper(Node* node) {
        
        // BASE CASE: Empty subtree recursion ends
        if (node != nullptr) {
            inOrderPrintHelper(node->left);
            
            cout << node->course.courseNumber << ", " 
                 << node->course.courseTitle << endl;  
            
            inOrderPrintHelper(node->right);
        }
    }
    
    /**
     * Recursive helper function for deallocating tree memory.
     * Uses post-order traversal to safely delete all nodes.
     * 
     * @param node The current node to delete
     */
    void deleteTree(Node* node) {
        if (node != nullptr) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

    /**
     * Recursive helper function for searching the tree.
     * 
     * @param node The current node being examined
     * @param courseNumber The course number to search for (case-insensitive)
     * @return Pointer to the Course if found, nullptr otherwise
     */
    Course* SearchHelper(Node* node, const string& courseNumber) {
        if (node == nullptr) {
            return nullptr;  
        }
        
        if (courseNumber == node->course.courseNumber) {
            return &(node->course);
        }
        else if (courseNumber < node->course.courseNumber) {
            return SearchHelper(node->left, courseNumber);
        }
        else {
            return SearchHelper(node->right, courseNumber);
        }
    }
    
public:
    /**
     * Default constructor.
     * Initializes an empty binary search tree.
     */
    BinarySearchTree() {
        root = nullptr;
    }
    
    /**
     * Inserts a course into the binary search tree.
     * Maintains BST property: left < parent < right.
     * Empty tree - Creates root node directly
     * Non-empty tree - Calls insertHelper to find correct position
     * 
     * @param course The Course object to insert
     */
    void Insert(Course course) {
        if (root == nullptr) {
            root = new Node(course);
        } else {
            insertHelper(root, course);
        }
    }
    
    /**
     * Destructor.
     * Prevents memory leaks by deleting all nodes we created with 'new'
     */
    ~BinarySearchTree() {
        deleteTree(root);
    }
    
    /**
     * Searches for a course by course number 
     * 
     * @param courseNumber The course number to search for
     * @return Pointer to the Course if found, nullptr otherwise
     */
    Course* Search(const string& courseNumber) {
        string upperCourseNumber = toUpper(courseNumber);
        return SearchHelper(root, upperCourseNumber);
    }
    
    /**
     * Prints all courses in the tree in alphabetically sorted order.
     * Uses in-order traversal to achieve sorted output.
     */
    void PrintCourseList() {
        cout << "Here is a sample schedule:" << endl;
        cout << endl; 
        inOrderPrintHelper(root);
    }
    
    /**
     * Prints detailed information about a specific course.
     * Includes course number, title, and prerequisites.
     * 
     * @param courseNumber The course number to display 
     */
    void PrintCourse(const string& courseNumber) {
        Course* course = Search(courseNumber);
        
        if (course == nullptr) {
            cout << "Course " << toUpper(courseNumber) << " not found." << endl;
            return;
        }
        
        cout << course->courseNumber << ", " << course->courseTitle << endl;
        cout << "Prerequisites: ";
        
        if (course->prerequisites.empty()) {
            cout << "None";
        } else {
            for (size_t i = 0; i < course->prerequisites.size(); ++i) {
                if (i > 0) {  
                    cout << ", ";
                }
                cout << course->prerequisites[i];
            }
        }
        cout << endl;
    }
};

/**
 * Populates the binary search tree with course data.
 * Inserts all courses from the vector into the BST.
 * 
 * @param courses Vector of Course objects to insert
 * @param bst Reference to the BinarySearchTree to populate
 */
void PopulateBST(const vector<Course>& courses, BinarySearchTree& bst) {
    for (const auto& course : courses) {
        bst.Insert(course);
    }
    
    cout << "Successfully loaded " << courses.size() << " courses into BST" << endl;
}

/**
 * Main entry point for the Course Planner application.
 * Provides an interactive menu for loading courses, viewing course lists,
 * and searching for specific course information.
 * 
 * @return 0 on successful program termination
 */
int main() {
    BinarySearchTree bst;
    bool dataLoaded = false;
    int choice = 0;
    string filename;
    string courseNumber;
    
    while (choice != 9) {
        cout << "\n===================================" << endl;
        cout << "Course Planner Menu:" << endl;
        cout << "===================================" << endl;
        cout << "  1. Load Data Structure" << endl;
        cout << "  2. Print Course List" << endl;
        cout << "  3. Print Course" << endl;
        cout << "  9. Exit" << endl;
        cout << "===================================" << endl;
        cout << "Enter choice: ";
        
        cin >> choice;
        
        
        if (cin.fail()) {
            cin.clear();  
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  
            cout << "\nInvalid input. Please enter a number." << endl;
            continue;  
        }
        
        cin.ignore();
        
        switch (choice) {
            case 1: {
                cout << "\nEnter filename: ";
                getline(cin, filename);
                
                vector<Course> courses;
                
                if (LoadCoursesFromFile(filename, courses)) {
                    PopulateBST(courses, bst);
                    dataLoaded = true;
                    cout << "Data loaded successfully!" << endl;
                } else {
                    cout << "Failed to load data. Please check you have entered the correct filename." << endl;
                }
                
                break;  
            }
            
            case 2: {
                if (!dataLoaded) {
                    cout << "\nError: Please load data first" << endl;
                } else {
                    cout << endl;
                    bst.PrintCourseList();
                }
                
                break;  
            }
            
            case 3: {
                if (!dataLoaded) {
                    cout << "\nError: Please load data first" << endl;
                } else {
                    cout << "\nWhat course do you want more detailed informatoin ? ";
                    getline(cin, courseNumber);
                    cout << endl;
                    bst.PrintCourse(courseNumber);
                }
                
                break;  
            }
            
            case 9: {
                cout << "\nSee you next time! " << endl;
                break;  
            }
            
            default: {
                cout << "\n" << choice << " is not a valid option." << endl;
                cout << "Please enter 1, 2, 3, or 9." << endl;
                break;  
            }
        }
    }
    
    cout << "Good bye. Program has ended." << endl;
    return 0;
}


