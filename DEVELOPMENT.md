# Development Documentation

## Project Overview

This is a Digital Attendance System built in C++ for managing student attendance in lecture halls. The system is designed for the HND Electrical Engineering program (Level 200), Course EEE227.

## Architecture

### Class Structure

#### Student Class
Manages individual student records.

**Header File:** `Student.h`
**Implementation:** `Student.cpp`

**Key Methods:**
- `Student(std::string idx, std::string n)` - Constructor
- `getIndexNumber()` - Returns student's index number
- `getName()` - Returns student's name
- `toFileFormat()` - Converts to pipe-separated format for file storage
- `fromFileFormat(std::string line)` - Parses from file format

**Data Format:**
```
INDEX_NUMBER|STUDENT_NAME
```

#### AttendanceSession Class
Manages lecture sessions and attendance records.

**Header File:** `AttendanceSession.h`
**Implementation:** `AttendanceSession.cpp`

**Key Methods:**
- `AttendanceSession(std::string code, std::string d, std::string time, int dur)` - Constructor
- `markAttendance(std::string indexNumber, std::string status)` - Records attendance
- `getAttendanceStatus(std::string indexNumber)` - Retrieves attendance status
- `updateAttendance(std::string indexNumber, std::string newStatus)` - Modifies record
- `displayAttendanceList()` - Shows all attendance records
- `displaySummary()` - Shows attendance statistics
- `toFileFormat()` - Converts to file storage format

**Data Format:**
```
COURSE_CODE|DATE|START_TIME|DURATION
STUDENT_INDEX|ATTENDANCE_STATUS
STUDENT_INDEX|ATTENDANCE_STATUS
...
```

### Main Application Flow

**File:** `main.cpp`

**Global Data Structures:**
- `std::vector<Student> students` - All registered students
- `std::vector<AttendanceSession> sessions` - All created sessions

**Key Functions:**

1. **File Operations**
   - `loadStudents()` - Loads students from `students.txt`
   - `saveStudents()` - Saves students to `students.txt`
   - `loadSessions()` - Loads sessions from individual files
   - `saveSessions()` - Saves all sessions to files
   - `exportAttendanceReport()` - Exports comprehensive report

2. **Student Management**
   - `addStudent()` - Register new student with validation
   - `viewAllStudents()` - Display all registered students
   - `searchStudent()` - Search by index number
   - `studentManagementMenu()` - Student management submenu

3. **Session Management**
   - `createSession()` - Create new lecture session with validation
   - `markAttendance()` - Record attendance for a student
   - `updateAttendance()` - Modify existing attendance record
   - `sessionManagementMenu()` - Session management submenu

4. **Reports**
   - `viewSessionAttendance()` - Display attendance list for a session
   - `viewAttendanceSummary()` - Show attendance statistics
   - `viewAllSessions()` - List all sessions
   - `exportAttendanceReport()` - Export to text file
   - `reportsMenu()` - Reports submenu

5. **Main Interface**
   - `displayMainMenu()` - Main menu with error handling
   - `main()` - Application entry point

## Data Persistence

### File Storage

**students.txt**
```
EE001|John Doe
EE002|Jane Smith
EE003|Bob Johnson
```

**session_[COURSE]_[DATE].txt**
```
EE201|2026-02-16|10:00|60
EE001|Present
EE002|Absent
EE003|Late
```

**attendance_report_[N].txt**
```
===== ATTENDANCE REPORT =====
Generated: [DATE] [TIME]
==================================================

Course: EE201
Date: 2026-02-16
Time: 10:00
Duration: 60 minutes
--------------------------------------------------
EE001 | Present
EE002 | Absent
EE003 | Late
--------------------------------------------------
Summary: Present=1, Absent=1, Late=1
```

## Input Validation

### Student Registration
- Index number cannot be empty
- Index number must be unique
- Name cannot be empty

### Session Creation
- Course code cannot be empty
- Date format: YYYY-MM-DD (validated)
- Time format: HH:MM (validated)
- Duration must be > 0

### Attendance Marking
- Student must exist in system
- Session must exist
- Status must be: Present, Absent, or Late

## Error Handling

The application includes comprehensive error handling:

1. **File I/O Errors**
   - Checks if files can be opened
   - Handles missing files gracefully
   - Reports save failures

2. **Input Validation**
   - Validates all user inputs
   - Prevents duplicate entries
   - Checks data format compliance

3. **User Input Errors**
   - Handles invalid menu choices
   - Recovers from invalid numeric input
   - Provides clear error messages

## Compilation

### Requirements
- C++ compiler (MinGW, GCC, or Clang)
- Standard C++ library with C++11 support

### Compile Command
```bash
g++ -o attendance main.cpp Student.cpp AttendanceSession.cpp
```

### Run Command
```bash
./attendance.exe  # Windows
./attendance      # Linux/Mac
```

## Testing Checklist

### Week 1: Foundation
- [x] Student class implementation
- [x] Add student functionality
- [x] View all students
- [x] Search student by index
- [x] File persistence for students

### Week 2: Session Management
- [x] AttendanceSession class
- [x] Create lecture sessions
- [x] Menu-driven interface
- [x] Session display

### Week 3: Attendance & Reports
- [x] Mark attendance
- [x] Update attendance records
- [x] Input validation
- [x] Attendance reports
- [x] Summary statistics
- [x] View all sessions

### Week 4: Polish & Submission
- [x] Complete file I/O
- [x] Export functionality
- [x] Error handling
- [x] Code refactoring
- [x] Documentation
- [x] Final testing

## Code Quality Standards

### Naming Conventions
- Classes: PascalCase (e.g., `AttendanceSession`)
- Functions: camelCase (e.g., `markAttendance`)
- Variables: camelCase (e.g., `indexNumber`)
- Constants: UPPER_CASE (if used)

### Code Organization
- Clear separation of concerns
- Modular function design
- Consistent indentation (4 spaces)
- Comments for complex logic

### Best Practices
- Input validation before processing
- Error messages for user feedback
- Proper resource management
- Consistent error handling

## Future Enhancements

Potential improvements for future versions:

1. **Database Integration**
   - Replace text files with SQLite
   - Improved data querying

2. **Advanced Features**
   - Student attendance statistics
   - Automated email notifications
   - Biometric attendance marking

3. **User Interface**
   - GUI using Qt or wxWidgets
   - Web-based interface
   - Mobile app

4. **Security**
   - User authentication
   - Role-based access control
   - Data encryption

## Troubleshooting

### Issue: "students.txt not found"
**Solution:** Normal on first run. File is created when first student is added.

### Issue: Compilation errors
**Solution:** Ensure all source files are in the same directory.

### Issue: Data not persisting
**Solution:** Check that `saveStudents()` and `saveSessions()` are called after modifications.

### Issue: Invalid date format error
**Solution:** Use YYYY-MM-DD format (e.g., 2026-02-16).

### Issue: Invalid time format error
**Solution:** Use HH:MM format in 24-hour time (e.g., 14:30).

## Git Workflow

### Commit Strategy
- Commit after completing a feature
- Use descriptive commit messages
- Minimum 3 commits per week

### Commit Message Format
```
[Week N]: Brief description of changes
```

### Example Commits
```
Week 1: Implement Student class with file persistence
Week 2: Add session creation and menu system
Week 3: Implement attendance marking and reports
Week 4: Add export functionality and final polish
```

## Performance Considerations

- Current implementation uses in-memory vectors
- Suitable for small to medium class sizes (< 500 students)
- File I/O is synchronous (blocking)
- No database indexing

## Security Notes

- No user authentication implemented
- All data stored in plain text files
- No encryption of sensitive data
- Suitable for educational use only

## Support and Maintenance

For issues or questions:
1. Check the README.md for usage instructions
2. Review SETUP_GUIDE.md for setup help
3. Check error messages for specific issues
4. Review code comments for implementation details

---

**Last Updated:** Week 4
**Status:** Complete and Ready for Submission
