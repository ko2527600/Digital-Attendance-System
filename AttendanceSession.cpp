#include "AttendanceSession.h"
#include <iostream>
#include <sstream>
#include <iomanip>

// Constructor with parameters
AttendanceSession::AttendanceSession(std::string code, std::string d, std::string time, int dur)
    : courseCode(code), date(d), startTime(time), duration(dur) {}

// Default constructor
AttendanceSession::AttendanceSession()
    : courseCode(""), date(""), startTime(""), duration(0) {}

// Getters
std::string AttendanceSession::getCourseCode() const {
    return courseCode;
}

std::string AttendanceSession::getDate() const {
    return date;
}

std::string AttendanceSession::getStartTime() const {
    return startTime;
}

int AttendanceSession::getDuration() const {
    return duration;
}

// Setters
void AttendanceSession::setCourseCode(std::string code) {
    courseCode = code;
}

void AttendanceSession::setDate(std::string d) {
    date = d;
}

void AttendanceSession::setStartTime(std::string time) {
    startTime = time;
}

void AttendanceSession::setDuration(int dur) {
    duration = dur;
}

// Mark attendance for a student
void AttendanceSession::markAttendance(std::string indexNumber, std::string status) {
    attendance[indexNumber] = status;
}

// Get attendance status for a student
std::string AttendanceSession::getAttendanceStatus(std::string indexNumber) const {
    auto it = attendance.find(indexNumber);
    if (it != attendance.end()) {
        return it->second;
    }
    return "Not Marked";
}

// Update attendance record
void AttendanceSession::updateAttendance(std::string indexNumber, std::string newStatus) {
    if (studentExists(indexNumber)) {
        attendance[indexNumber] = newStatus;
    }
}

// Check if student has attendance record
bool AttendanceSession::studentExists(std::string indexNumber) const {
    return attendance.find(indexNumber) != attendance.end();
}

// Display session information
void AttendanceSession::displaySessionInfo() const {
    std::cout << "\n===== SESSION INFORMATION =====" << std::endl;
    std::cout << "Course Code: " << courseCode << std::endl;
    std::cout << "Date: " << date << std::endl;
    std::cout << "Start Time: " << startTime << std::endl;
    std::cout << "Duration: " << duration << " minutes" << std::endl;
    std::cout << "Total Students Marked: " << attendance.size() << std::endl;
}

// Display attendance list
void AttendanceSession::displayAttendanceList() const {
    std::cout << "\n===== ATTENDANCE LIST =====" << std::endl;
    std::cout << std::left << std::setw(15) << "Index Number" 
              << std::setw(20) << "Status" << std::endl;
    std::cout << std::string(35, '-') << std::endl;
    
    for (const auto& record : attendance) {
        std::cout << std::left << std::setw(15) << record.first 
                  << std::setw(20) << record.second << std::endl;
    }
}

// Display attendance summary
void AttendanceSession::displaySummary() const {
    int present = 0, absent = 0, late = 0;
    
    for (const auto& record : attendance) {
        if (record.second == "Present") present++;
        else if (record.second == "Absent") absent++;
        else if (record.second == "Late") late++;
    }
    
    std::cout << "\n===== ATTENDANCE SUMMARY =====" << std::endl;
    std::cout << "Course: " << courseCode << " | Date: " << date << std::endl;
    std::cout << "Present: " << present << std::endl;
    std::cout << "Absent: " << absent << std::endl;
    std::cout << "Late: " << late << std::endl;
    std::cout << "Total: " << attendance.size() << std::endl;
}

// Get file name for this session
std::string AttendanceSession::getFileName() const {
    return "session_" + courseCode + "_" + date + ".txt";
}

// Convert to file format
std::string AttendanceSession::toFileFormat() const {
    std::string result = courseCode + "|" + date + "|" + startTime + "|" + std::to_string(duration) + "\n";
    
    for (const auto& record : attendance) {
        result += record.first + "|" + record.second + "\n";
    }
    
    return result;
}

// Parse from file format
AttendanceSession AttendanceSession::fromFileFormat(std::string headerLine) {
    std::stringstream ss(headerLine);
    std::string code, date, time, durStr;
    
    std::getline(ss, code, '|');
    std::getline(ss, date, '|');
    std::getline(ss, time, '|');
    std::getline(ss, durStr, '|');
    
    int duration = std::stoi(durStr);
    return AttendanceSession(code, date, time, duration);
}

// Get all attendance records
std::map<std::string, std::string> AttendanceSession::getAttendanceRecords() const {
    return attendance;
}
