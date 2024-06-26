//============================================================================
// Name        : Project_Two
// Author      : Mohammed Khan
// Version     : 1.0
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

// Structure to hold course information
struct Course {
    std::string courseNumber;  // Course number (e.g., CSCI101)
    std::string title;         // Course title (e.g., Introduction to Programming in C++)
    std::vector<std::string> prerequisites; // List of prerequisite course numbers
};

// Function to load course data from a file
void loadCourseData(const std::string& filename, std::unordered_map<std::string, Course>& courses) {
    std::ifstream file(filename); // Open the file
    if (!file) { // Check if the file opened successfully
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    std::string line;
    while (getline(file, line)) { // Read the file line by line
        std::stringstream ss(line); // Create a stringstream for parsing
        std::string courseNumber, title, prereq1, prereq2;

        // Parse the line by commas
        getline(ss, courseNumber, ',');
        getline(ss, title, ',');
        getline(ss, prereq1, ',');
        getline(ss, prereq2, ',');

        // Create a Course object and populate its fields
        Course course;
        course.courseNumber = courseNumber;
        course.title = title;

        // Add prerequisites if they are not empty
        if (!prereq1.empty()) {
            course.prerequisites.push_back(prereq1);
        }
        if (!prereq2.empty()) {
            course.prerequisites.push_back(prereq2);
        }

        // Add the course to the map using the course number as the key
        courses[courseNumber] = course;
    }

    file.close(); // Close the file
    std::cout << "Data loaded successfully." << std::endl;
}

// Function to print the course list in alphanumeric order
void printCourseList(const std::unordered_map<std::string, Course>& courses) {
    std::vector<std::string> courseNumbers;

    // Collect all course numbers
    for (const auto& pair : courses) {
        courseNumbers.push_back(pair.first);
    }

    // Sort the course numbers alphanumerically
    std::sort(courseNumbers.begin(), courseNumbers.end());

    std::cout << "Here is a sample schedule:" << std::endl;
    // Print each course number and title
    for (const auto& courseNumber : courseNumbers) {
        const Course& course = courses.at(courseNumber);
        std::cout << course.courseNumber << ", " << course.title << std::endl;
    }
}

// Function to print course information
void printCourseInfo(const std::unordered_map<std::string, Course>& courses, const std::string& courseNumber) {
    auto it = courses.find(courseNumber); // Find the course in the map
    if (it != courses.end()) { // If the course is found
        const Course& course = it->second;
        std::cout << course.courseNumber << ", " << course.title << std::endl;
        std::cout << "Prerequisites: ";

        // Print the prerequisites, if any
        if (course.prerequisites.empty()) {
            std::cout << "None";
        }
        else {
            for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                if (i > 0) std::cout << ", ";
                std::cout << course.prerequisites[i];
            }
        }

        std::cout << std::endl;
    }
    else { // If the course is not found
        std::cerr << "Error: Course not found." << std::endl;
    }
}

// Function to display the menu and handle user input
void displayMenu(std::unordered_map<std::string, Course>& courses) {
    const std::string filename = "U:\\Project_Two\\ABCU_Advising_Program_Input.csv";
    int choice;
    std::string courseNumber;

    do {
        // Display the menu
        std::cout << "Welcome to the course planner." << std::endl;
        std::cout << "1. Load Data Structure." << std::endl;
        std::cout << "2. Print Course List." << std::endl;
        std::cout << "3. Print Course." << std::endl;
        std::cout << "9. Exit" << std::endl;
        std::cout << "What would you like to do? ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            // Load the course data from the file
            loadCourseData(filename, courses);
            break;
        case 2:
            // Print the list of courses
            printCourseList(courses);
            break;
        case 3:
            // Prompt the user for a course number and print the course information
            std::cout << "What course do you want to know about? ";
            std::cin >> courseNumber;
            // Convert the course number to uppercase
            std::transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::toupper);
            printCourseInfo(courses, courseNumber);
            break;
        case 9:
            // Exit the program
            std::cout << "Thank you for using the course planner!" << std::endl;
            break;
        default:
            // Handle invalid menu options
            std::cerr << choice << " is not a valid option." << std::endl;
            break;
        }
    } while (choice != 9); // Continue until the user chooses to exit
}

int main() {
    std::unordered_map<std::string, Course> courses; // Create a map to store courses
    displayMenu(courses); // Display the menu and handle user input
    return 0;
}
