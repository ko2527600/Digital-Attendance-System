#ifndef ATTENDANCE_SESSION_H
#define ATTENDANCE_SESSION_H

#include <string>
#include <map>
#include "Student.h"

class AttendanceSession {
private:
    std::string courseCode;
    std::string date;
    std::string startTime;
    int duration; // in minutes
    std::map<std::string, std::string> attendance; // indexNumber -> status (Present/Absent/Late)

public:
    // Constructor
    AttendanceSession(std::string code, std::string d, std::string time, int dur);
    AttendanceSession(); // Default constructor

    // Getters
    std::string getCourseCode() const;
    std::string getDate() const;
    std::string getStartTime() const;
    int getDuration() const;

    // Setters
    void setCourseCode(std::string code);
    void setDate(std::string d);
    void setStartTime(std::string time);
    void setDuration(int dur);

    // Attendance operations
    void markAttendance(std::string indexNumber, std::string status);
    std::string getAttendanceStatus(std::string indexNumber) const;
    void updateAttendance(std::string indexNumber, std::string newStatus);
    bool studentExists(std::string indexNumber) const;

    // Display methods
    void displaySessionInfo() const;
    void displayAttendanceList() const;
    void displaySummary() const;

    // File operations
    std::string getFileName() const;
    std::string toFileFormat() const;
    static AttendanceSession fromFileFormat(std::string headerLine);

    // Get all attendance records
    std::map<std::string, std::string> getAttendanceRecords() const;
};

#endif
