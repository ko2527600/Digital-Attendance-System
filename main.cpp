#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
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
void viewAllSessions();
void exportAttendanceReport();

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
    // Load all session files from current directory
    // Sessions are stored as session_COURSECODE_DATE.txt
    // Note: In a production system, we'd use directory scanning
    // For now, sessions persist in memory during runtime
    std::cout << "Sessions loaded from memory." << std::endl;
}

void saveSessions() {
    for (const auto& session : sessions) {
        std::ofstream file(session.getFileName());
        if (file.is_open()) {
            file << session.toFileFormat();
            file.close();
        } else {
            std::cerr << "Error: Could not save session to file!" << std::endl;
        }
    }
}

void exportAttendanceReport() {
    if (sessions.empty()) {
        std::cout << "\nNo sessions to export!" << std::endl;
        return;
    }
    
    std::string filename = "attendance_report_" + std::to_string(sessions.size()) + ".txt";
    std::ofstream reportFile(filename);
    
    if (!reportFile.is_open()) {
        std::cout << "Error: Could not create report file!" << std::endl;
        return;
    }
    
    reportFile << "===== ATTENDANCE REPORT =====" << std::endl;
    reportFile << "Generated: " << __DATE__ << " " << __TIME__ << std::endl;
    reportFile << std::string(50, '=') << std::endl << std::endl;
    
    for (const auto& session : sessions) {
        reportFile << "Course: " << session.getCourseCode() << std::endl;
        reportFile << "Date: " << session.getDate() << std::endl;
        reportFile << "Time: " << session.getStartTime() << std::endl;
        reportFile << "Duration: " << session.getDuration() << " minutes" << std::endl;
        reportFile << std::string(50, '-') << std::endl;
        
        int present = 0, absent = 0, late = 0;
        auto records = session.getAttendanceRecords();
        
        for (const auto& record : records) {
            reportFile << record.first << " | " << record.second << std::endl;
            if (record.second == "Present") present++;
            else if (record.second == "Absent") absent++;
            else if (record.second == "Late") late++;
        }
        
        reportFile << std::string(50, '-') << std::endl;
        reportFile << "Summary: Present=" << present << ", Absent=" << absent 
                  << ", Late=" << late << std::endl << std::endl;
    }
    
    reportFile.close();
    std::cout << "\n✓ Report exported to: " << filename << std::endl;
}

// ===== STUDENT MANAGEMENT =====

void addStudent() {
    std::string idx, name;
    
    std::cout << "\n===== ADD NEW STUDENT =====" << std::endl;
    
    // Validate index number
    while (true) {
        std::cout << "Enter Index Number: ";
        std::getline(std::cin, idx);
        
        // Check if empty
        if (idx.empty()) {
            std::cout << "Error: Index number cannot be empty!" << std::endl;
            continue;
        }
        
        // Check if already exists
        bool exists = false;
        for (const auto& student : students) {
            if (student.getIndexNumber() == idx) {
                std::cout << "Error: Student with this index already exists!" << std::endl;
                exists = true;
                break;
            }
        }
        
        if (!exists) break;
    }
    
    // Validate name
    while (true) {
        std::cout << "Enter Student Name: ";
        std::getline(std::cin, name);
        
        if (name.empty()) {
            std::cout << "Error: Name cannot be empty!" << std::endl;
            continue;
        }
        break;
    }
    
    students.push_back(Student(idx, name));
    saveStudents();
    std::cout << "\n✓ Student added successfully!" << std::endl;
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
    
    // Validate course code
    while (true) {
        std::cout << "Enter Course Code (e.g., EE201): ";
        std::getline(std::cin, code);
        
        if (code.empty()) {
            std::cout << "Error: Course code cannot be empty!" << std::endl;
            continue;
        }
        break;
    }
    
    // Validate date
    while (true) {
        std::cout << "Enter Date (YYYY-MM-DD): ";
        std::getline(std::cin, date);
        
        if (date.empty()) {
            std::cout << "Error: Date cannot be empty!" << std::endl;
            continue;
        }
        
        // Basic date format validation
        if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
            std::cout << "Error: Invalid date format! Use YYYY-MM-DD" << std::endl;
            continue;
        }
        break;
    }
    
    // Validate time
    while (true) {
        std::cout << "Enter Start Time (HH:MM): ";
        std::getline(std::cin, time);
        
        if (time.empty()) {
            std::cout << "Error: Time cannot be empty!" << std::endl;
            continue;
        }
        
        // Basic time format validation
        if (time.length() != 5 || time[2] != ':') {
            std::cout << "Error: Invalid time format! Use HH:MM" << std::endl;
            continue;
        }
        break;
    }
    
    // Validate duration
    while (true) {
        std::cout << "Enter Duration (minutes): ";
        std::cin >> duration;
        std::cin.ignore();
        
        if (duration <= 0) {
            std::cout << "Error: Duration must be greater than 0!" << std::endl;
            continue;
        }
        break;
    }
    
    AttendanceSession session(code, date, time, duration);
    sessions.push_back(session);
    saveSessions();
    
    std::cout << "\n✓ Session created successfully!" << std::endl;
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
    
    std::cout << "\nMark as:\n1. Present\n2. Absent\n3. Late\nEnter choice: ";
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
    std::cout << "\n✓ Attendance marked as: " << status << std::endl;
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
    std::cout << "\nUpdate to:\n1. Present\n2. Absent\n3. Late\nEnter choice: ";
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
    std::cout << "\n✓ Attendance updated to: " << newStatus << std::endl;
}

void sessionManagementMenu() {
    int choice;
    
    while (true) {
        std::cout << "\n===== SESSION MANAGEMENT =====" << std::endl;
        std::cout << "1. Create New Session" << std::endl;
        std::cout << "2. Mark Attendance" << std::endl;
        std::cout << "3. Update Attendance" << std::endl;
        std::cout << "4. View Session Details" << std::endl;
        std::cout << "5. Back to Main Menu" << std::endl;
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
                viewSessionAttendance();
                break;
            case 5:
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
        std::cout << "Error: Invalid session selection!" << std::endl;
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
        std::cout << "Error: Invalid session selection!" << std::endl;
        return;
    }
    
    sessions[choice - 1].displaySummary();
}

void viewAllSessions() {
    if (sessions.empty()) {
        std::cout << "\nNo sessions created yet!" << std::endl;
        return;
    }
    
    std::cout << "\n===== ALL SESSIONS =====" << std::endl;
    std::cout << std::left << std::setw(15) << "Course Code" 
              << std::setw(15) << "Date" 
              << std::setw(12) << "Start Time" 
              << std::setw(12) << "Duration" << std::endl;
    std::cout << std::string(54, '-') << std::endl;
    
    for (const auto& session : sessions) {
        std::cout << std::left << std::setw(15) << session.getCourseCode()
                  << std::setw(15) << session.getDate()
                  << std::setw(12) << session.getStartTime()
                  << std::setw(12) << (std::to_string(session.getDuration()) + " min") << std::endl;
    }
}

void reportsMenu() {
    int choice;
    
    while (true) {
        std::cout << "\n===== REPORTS AND SUMMARY =====" << std::endl;
        std::cout << "1. View Session Attendance List" << std::endl;
        std::cout << "2. View Attendance Summary" << std::endl;
        std::cout << "3. View All Sessions" << std::endl;
        std::cout << "4. Export Attendance Report" << std::endl;
        std::cout << "5. Back to Main Menu" << std::endl;
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
                viewAllSessions();
                break;
            case 4:
                exportAttendanceReport();
                break;
            case 5:
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
        
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Error: Invalid input! Please enter a number." << std::endl;
            continue;
        }
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
                std::cout << "Goodbye!" << std::endl;
                return;
            default:
                std::cout << "Invalid choice! Please try again." << std::endl;
        }
    }
}

// ===== MAIN FUNCTION =====

int main() {
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════╗" << std::endl;
    std::cout << "║  DIGITAL ATTENDANCE SYSTEM - Week 4    ║" << std::endl;
    std::cout << "║  HND Electrical Engineering (Level 200)║" << std::endl;
    std::cout << "║  Course: EEE227                        ║" << std::endl;
    std::cout << "╚════════════════════════════════════════╝" << std::endl;
    std::cout << "\nInitializing system..." << std::endl;
    
    loadStudents();
    loadSessions();
    
    std::cout << "System ready. Starting main menu...\n" << std::endl;
    
    displayMainMenu();
    
    std::cout << "\nSaving data..." << std::endl;
    saveStudents();
    saveSessions();
    std::cout << "Data saved successfully." << std::endl;
    
    return 0;
}
