# Setup and Development Guide

## Initial Setup

### 1. Initialize Git Repository

```bash
git init
git config user.name "Your Name"
git config user.email "your.email@example.com"
```

### 2. Create GitHub Repository

1. Go to [github.com](https://github.com)
2. Click "New Repository"
3. Name it: `digital-attendance-system`
4. Add description: "Digital Attendance System for Hour-Based Lectures"
5. Choose "Public" or "Private"
6. Click "Create Repository"

### 3. Connect Local Repository to GitHub

```bash
git remote add origin https://github.com/YOUR_USERNAME/digital-attendance-system.git
git branch -M main
git add .
git commit -m "Initial project structure with Student and AttendanceSession classes"
git push -u origin main
```

## Compilation Instructions

### Using MinGW (Windows)

```bash
g++ -o attendance main.cpp Student.cpp AttendanceSession.cpp
```

### Run the Application

```bash
attendance.exe
```

## Project Structure Explanation

```
digital-attendance-system/
├── main.cpp                    # Entry point with menu system
├── Student.h                   # Student class header
├── Student.cpp                 # Student class implementation
├── AttendanceSession.h         # AttendanceSession class header
├── AttendanceSession.cpp       # AttendanceSession class implementation
├── README.md                   # Project documentation
├── SETUP_GUIDE.md             # This file
├── .gitignore                  # Git ignore rules
├── students.txt                # Student records (auto-generated)
└── session_*.txt               # Session records (auto-generated)
```

## Code Organization

### Student Class
- **Purpose:** Manages individual student data
- **Key Methods:**
  - `getIndexNumber()` - Get student's index number
  - `getName()` - Get student's name
  - `toFileFormat()` - Convert to file storage format
  - `fromFileFormat()` - Parse from file storage format

### AttendanceSession Class
- **Purpose:** Manages a single lecture session and its attendance records
- **Key Methods:**
  - `markAttendance()` - Record attendance for a student
  - `getAttendanceStatus()` - Check a student's status
  - `updateAttendance()` - Modify existing attendance record
  - `displayAttendanceList()` - Show all attendance records
  - `displaySummary()` - Show attendance statistics

### Main Menu System
- **Student Management:** Add, view, search students
- **Session Management:** Create sessions, mark attendance, update records
- **Reports:** View attendance lists and summaries

## File Format Specifications

### students.txt
```
INDEX_NUMBER|STUDENT_NAME
EE001|John Doe
EE002|Jane Smith
EE003|Bob Johnson
```

### session_[COURSE]_[DATE].txt
```
COURSE_CODE|DATE|START_TIME|DURATION
STUDENT_INDEX|ATTENDANCE_STATUS
EE001|Present
EE002|Absent
EE003|Late
```

Example: `session_EE201_2026-02-24.txt`

## Development Workflow

### Week 1: Foundation
1. Create GitHub repository ✓
2. Set up project structure ✓
3. Implement Student class ✓
4. Test add/view students functionality
5. Make 3+ meaningful commits

**Commit Examples:**
```bash
git add .
git commit -m "Add Student class with basic functionality"
git commit -m "Implement student file persistence"
git commit -m "Add student search functionality"
git push
```

### Week 2: Session Management
1. Implement AttendanceSession class ✓
2. Create session creation functionality
3. Build menu-driven interface ✓
4. Test session creation
5. Make 3+ meaningful commits

### Week 3: Attendance & Reports
1. Implement attendance marking logic ✓
2. Add report generation ✓
3. Improve input validation
4. Test all features
5. Make 3+ meaningful commits

### Week 4: Polish & Submission
1. Implement complete file I/O
2. Refactor code for readability
3. Add error handling
4. Final testing
5. Update documentation
6. Make 3+ meaningful commits

## Testing Checklist

### Student Management
- [ ] Add a new student
- [ ] View all students
- [ ] Search for a student
- [ ] Verify students persist after restart

### Session Management
- [ ] Create a new session
- [ ] Mark attendance for multiple students
- [ ] Update attendance records
- [ ] Verify sessions persist after restart

### Reports
- [ ] View attendance list for a session
- [ ] View attendance summary
- [ ] Verify counts are accurate

## Common Issues and Solutions

### Issue: "students.txt not found"
**Solution:** This is normal on first run. The file is created when you add the first student.

### Issue: Compilation errors
**Solution:** Ensure all files are in the same directory and use the correct compilation command:
```bash
g++ -o attendance main.cpp Student.cpp AttendanceSession.cpp
```

### Issue: Data not persisting
**Solution:** Check that `saveStudents()` and `saveSessions()` are called after modifications.

## Git Commit Best Practices

### Good Commit Messages
```
✓ "Add Student class with getters and setters"
✓ "Implement file persistence for student records"
✓ "Add attendance marking functionality"
```

### Poor Commit Messages
```
✗ "Update"
✗ "Fix stuff"
✗ "Changes"
```

### Commit Frequency
- Commit after completing a feature
- Commit after fixing a bug
- Commit after significant refactoring
- Aim for 3+ commits per week minimum

## Useful Git Commands

```bash
# Check status
git status

# View commit history
git log --oneline

# View changes before committing
git diff

# Undo last commit (keep changes)
git reset --soft HEAD~1

# View a specific file's history
git log --oneline -- filename.cpp
```

## Next Steps

1. Initialize Git and GitHub repository
2. Compile and test the application
3. Add a few test students
4. Create a test session
5. Mark attendance
6. Make your first commit
7. Push to GitHub

Good luck with your project!
