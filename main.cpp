#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Student.h"
#include "AttendanceSession.h"

// Global data structures
std::vector<Student> students;
std::vector<AttendanceSession> sessions;

// Function declarations
void loadStudents();
void saveStudents();
void loadSessions();
void saveSessions();

void studentManagementMenu();
void sessionManagementMenu();
void reportsMenu();

void addStudent();
void viewAllStudents();
void searchStudent();

void createSession();
void markAttendance();
void updateAttendance();

void viewSessionAttendance();
void viewAttendanceSummary();

void displayMainMenu();

// ===== FILE OPERATIONS =====

void loadStudents() {
    std::ifstream file("students.txt");
    if (!file.is_open()) {
        std::cout << "No existing student records found. Starting fresh." << std::endl;
        return;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            students.push_back(Student::fromFileFormat(line));
        }
    }
    file.close();
    std::cout << "Loaded " << students.size() << " students." << std::endl;
}

void saveStudents() {
    std::ofstream file("students.txt");
    for (const auto& student : students) {
        file << student.toFileFormat() << std::endl;
    }
    file.close();
}

void loadSessions() {
    // Note: Session loading from individual files will be implemented in Week 4
    std::cout << "Session loading will be implemented in Week 4." << std::endl;
}

void saveSessions() {
    for (const auto& session : sessions) {
        std::ofstream file(session.getFileName());
        file << session.toFileFormat();
        file.close();
    }
}

// ===== STUDENT MANAGEMENT =====

void addStudent() {
    std::string idx, name;
    
    std::cout << "\n===== ADD NEW STUDENT =====" << std::endl;
    std::cout << "Enter Index Number: ";
    std::getline(std::cin, idx);
    
    // Check if student already exists
    for (const auto& student : students) {
        if (student.getIndexNumber() == idx) {
            std::cout << "Error: Student with this index already exists!" << std::endl;
            return;
        }
    }
    
    std::cout << "Enter Student Name: ";
    std::getline(std::cin, name);
    
    students.push_back(Student(idx, name));
    saveStudents();
    std::cout << "Student added successfully!" << std::endl;
}

void viewAllStudents() {
    if (students.empty()) {
        std::cout << "\nNo students registered yet." << std::endl;
        return;
    }
    
    std::cout << "\n===== ALL REGISTERED STUDENTS =====" << std::endl;
    std::cout << "Total: " << students.size() << std::endl;
    std::cout << std::string(40, '-') << std::endl;
    
    for (const auto& student : students) {
        student.display();
    }
}

void searchStudent() {
    std::string idx;
    
    std::cout << "\n===== SEARCH STUDENT =====" << std::endl;
    std::cout << "Enter Index Number to search: ";
    std::getline(std::cin, idx);
    
    for (const auto& student : students) {
        if (student.getIndexNumber() == idx) {
            std::cout << "\nStudent Found:" << std::endl;
            student.display();
            return;
        }
    }
    
    std::cout << "Student not found!" << std::endl;
}

void studentManagementMenu() {
    int choice;
    
    while (true) {
        std::cout << "\n===== STUDENT MANAGEMENT =====" << std::endl;
        std::cout << "1. Add New Student" << std::endl;
        std::cout << "2. View All Students" << std::endl;
        std::cout << "3. Search Student" << std::endl;
        std::cout << "4. Back to Main Menu" << std::endl;
        std::cout << "Enter your choice: ";
        
        std::cin >> choice;
        std::cin.ignore(); // Clear input buffer
        
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                viewAllStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                return;
            default:
                std::cout << "Invalid choice! Please try again." << std::endl;
        }
    }
}

// ===== SESSION MANAGEMENT =====

void createSession() {
    std::string code, date, time;
    int duration;
    
    std::cout << "\n===== CREATE NEW SESSION =====" << std::endl;
    std::cout << "Enter Course Code (e.g., EE201): ";
    std::getline(std::cin, code);
    
    std::cout << "Enter Date (YYYY-MM-DD): ";
    std::getline(std::cin, date);
    
    std::cout << "Enter Start Time (HH:MM): ";
    std::getline(std::cin, time);
    
    std::cout << "Enter Duration (minutes): ";
    std::cin >> duration;
    std::cin.ignore();
    
    AttendanceSession session(code, date, time, duration);
    sessions.push_back(session);
    saveSessions();
    
    std::cout << "Session created successfully!" << std::endl;
}

void markAttendance() {
    if (sessions.empty()) {
        std::cout << "\nNo sessions available. Create a session first!" << std::endl;
        return;
    }
    
    if (students.empty()) {
        std::cout << "\nNo students registered. Register students first!" << std::endl;
        return;
    }
    
    std::cout << "\n===== MARK ATTENDANCE =====" << std::endl;
    std::cout << "Available Sessions:" << std::endl;
    
    for (int i = 0; i < sessions.size(); i++) {
        std::cout << i + 1 << ". " << sessions[i].getCourseCode() 
                  << " - " << sessions[i].getDate() << std::endl;
    }
    
    int sessionChoice;
    std::cout << "Select session: ";
    std::cin >> sessionChoice;
    std::cin.ignore();
    
    if (sessionChoice < 1 || sessionChoice > sessions.size()) {
        std::cout << "Invalid session!" << std::endl;
        return;
    }
    
    AttendanceSession& currentSession = sessions[sessionChoice - 1];
    
    std::cout << "\nStudents:" << std::endl;
    for (int i = 0; i < students.size(); i++) {
        std::cout << i + 1 << ". " << students[i].getIndexNumber() 
                  << " - " << students[i].getName() << std::endl;
    }
    
    int studentChoice;
    std::cout << "Select student: ";
    std::cin >> studentChoice;
    std::cin.ignore();
    
    if (studentChoice < 1 || studentChoice > students.size()) {
        std::cout << "Invalid student!" << std::endl;
        return;
    }
    
    std::cout << "Mark as (1=Present, 2=Absent, 3=Late): ";
    int statusChoice;
    std::cin >> statusChoice;
    std::cin.ignore();
    
    std::string status;
    switch (statusChoice) {
        case 1: status = "Present"; break;
        case 2: status = "Absent"; break;
        case 3: status = "Late"; break;
        default: std::cout << "Invalid status!" << std::endl; return;
    }
    
    currentSession.markAttendance(students[studentChoice - 1].getIndexNumber(), status);
    saveSessions();
    std::cout << "Attendance marked successfully!" << std::endl;
}

void updateAttendance() {
    if (sessions.empty()) {
        std::cout << "\nNo sessions available!" << std::endl;
        return;
    }
    
    std::cout << "\n===== UPDATE ATTENDANCE =====" << std::endl;
    std::cout << "Available Sessions:" << std::endl;
    
    for (int i = 0; i < sessions.size(); i++) {
        std::cout << i + 1 << ". " << sessions[i].getCourseCode() 
                  << " - " << sessions[i].getDate() << std::endl;
    }
    
    int sessionChoice;
    std::cout << "Select session: ";
    std::cin >> sessionChoice;
    std::cin.ignore();
    
    if (sessionChoice < 1 || sessionChoice > sessions.size()) {
        std::cout << "Invalid session!" << std::endl;
        return;
    }
    
    AttendanceSession& currentSession = sessions[sessionChoice - 1];
    
    std::string indexNumber;
    std::cout << "Enter Student Index Number: ";
    std::getline(std::cin, indexNumber);
    
    if (!currentSession.studentExists(indexNumber)) {
        std::cout << "Student not found in this session!" << std::endl;
        return;
    }
    
    std::cout << "Current Status: " << currentSession.getAttendanceStatus(indexNumber) << std::endl;
    std::cout << "Update to (1=Present, 2=Absent, 3=Late): ";
    int statusChoice;
    std::cin >> statusChoice;
    std::cin.ignore();
    
    std::string newStatus;
    switch (statusChoice) {
        case 1: newStatus = "Present"; break;
        case 2: newStatus = "Absent"; break;
        case 3: newStatus = "Late"; break;
        default: std::cout << "Invalid status!" << std::endl; return;
    }
    
    currentSession.updateAttendance(indexNumber, newStatus);
    saveSessions();
    std::cout << "Attendance updated successfully!" << std::endl;
}

void sessionManagementMenu() {
    int choice;
    
    while (true) {
        std::cout << "\n===== SESSION MANAGEMENT =====" << std::endl;
        std::cout << "1. Create New Session" << std::endl;
        std::cout << "2. Mark Attendance" << std::endl;
        std::cout << "3. Update Attendance" << std::endl;
        std::cout << "4. Back to Main Menu" << std::endl;
        std::cout << "Enter your choice: ";
        
        std::cin >> choice;
        std::cin.ignore();
        
        switch (choice) {
            case 1:
                createSession();
                break;
            case 2:
                markAttendance();
                break;
            case 3:
                updateAttendance();
                break;
            case 4:
                return;
            default:
                std::cout << "Invalid choice! Please try again." << std::endl;
        }
    }
}

// ===== REPORTS =====

void viewSessionAttendance() {
    if (sessions.empty()) {
        std::cout << "\nNo sessions available!" << std::endl;
        return;
    }
    
    std::cout << "\n===== VIEW SESSION ATTENDANCE =====" << std::endl;
    std::cout << "Available Sessions:" << std::endl;
    
    for (int i = 0; i < sessions.size(); i++) {
        std::cout << i + 1 << ". " << sessions[i].getCourseCode() 
                  << " - " << sessions[i].getDate() << std::endl;
    }
    
    int choice;
    std::cout << "Select session: ";
    std::cin >> choice;
    std::cin.ignore();
    
    if (choice < 1 || choice > sessions.size()) {
        std::cout << "Invalid session!" << std::endl;
        return;
    }
    
    sessions[choice - 1].displaySessionInfo();
    sessions[choice - 1].displayAttendanceList();
}

void viewAttendanceSummary() {
    if (sessions.empty()) {
        std::cout << "\nNo sessions available!" << std::endl;
        return;
    }
    
    std::cout << "\n===== VIEW ATTENDANCE SUMMARY =====" << std::endl;
    std::cout << "Available Sessions:" << std::endl;
    
    for (int i = 0; i < sessions.size(); i++) {
        std::cout << i + 1 << ". " << sessions[i].getCourseCode() 
                  << " - " << sessions[i].getDate() << std::endl;
    }
    
    int choice;
    std::cout << "Select session: ";
    std::cin >> choice;
    std::cin.ignore();
    
    if (choice < 1 || choice > sessions.size()) {
        std::cout << "Invalid session!" << std::endl;
        return;
    }
    
    sessions[choice - 1].displaySummary();
}

void reportsMenu() {
    int choice;
    
    while (true) {
        std::cout << "\n===== REPORTS AND SUMMARY =====" << std::endl;
        std::cout << "1. View Session Attendance List" << std::endl;
        std::cout << "2. View Attendance Summary" << std::endl;
        std::cout << "3. Back to Main Menu" << std::endl;
        std::cout << "Enter your choice: ";
        
        std::cin >> choice;
        std::cin.ignore();
        
        switch (choice) {
            case 1:
                viewSessionAttendance();
                break;
            case 2:
                viewAttendanceSummary();
                break;
            case 3:
                return;
            default:
                std::cout << "Invalid choice! Please try again." << std::endl;
        }
    }
}

// ===== MAIN MENU =====

void displayMainMenu() {
    int choice;
    
    while (true) {
        std::cout << "\n===== DIGITAL ATTENDANCE SYSTEM =====" << std::endl;
        std::cout << "1. Student Management" << std::endl;
        std::cout << "2. Attendance Session Management" << std::endl;
        std::cout << "3. Reports and Summary" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        
        std::cin >> choice;
        std::cin.ignore();
        
        switch (choice) {
            case 1:
                studentManagementMenu();
                break;
            case 2:
                sessionManagementMenu();
                break;
            case 3:
                reportsMenu();
                break;
            case 4:
                std::cout << "\nThank you for using Digital Attendance System!" << std::endl;
                return;
            default:
                std::cout << "Invalid choice! Please try again." << std::endl;
        }
    }
}

// ===== MAIN FUNCTION =====

int main() {
    std::cout << "===== DIGITAL ATTENDANCE SYSTEM =====" << std::endl;
    std::cout << "Loading data..." << std::endl;
    
    loadStudents();
    loadSessions();
    
    displayMainMenu();
    
    return 0;
}
