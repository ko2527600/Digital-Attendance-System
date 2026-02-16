#include "Student.h"
#include <iostream>
#include <sstream>

// Constructor with parameters
Student::Student(std::string idx, std::string n) 
    : indexNumber(idx), name(n) {}

// Default constructor
Student::Student() 
    : indexNumber(""), name("") {}

// Getters
std::string Student::getIndexNumber() const {
    return indexNumber;
}

std::string Student::getName() const {
    return name;
}

// Setters
void Student::setIndexNumber(std::string idx) {
    indexNumber = idx;
}

void Student::setName(std::string n) {
    name = n;
}

// Display student information
void Student::display() const {
    std::cout << "Index: " << indexNumber << " | Name: " << name << std::endl;
}

// Convert to file format (pipe-separated)
std::string Student::toFileFormat() const {
    return indexNumber + "|" + name;
}

// Parse from file format
Student Student::fromFileFormat(std::string line) {
    std::stringstream ss(line);
    std::string idx, name;
    
    std::getline(ss, idx, '|');
    std::getline(ss, name, '|');
    
    return Student(idx, name);
}
