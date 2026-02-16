#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>

class Student {
private:
    std::string indexNumber;
    std::string name;

public:
    // Constructor
    Student(std::string idx, std::string n);
    Student(); // Default constructor

    // Getters
    std::string getIndexNumber() const;
    std::string getName() const;

    // Setters
    void setIndexNumber(std::string idx);
    void setName(std::string n);

    // Display student info
    void display() const;

    // Convert to file format
    std::string toFileFormat() const;

    // Parse from file format
    static Student fromFileFormat(std::string line);
};

#endif
