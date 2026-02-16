# Digital Attendance System

A console-based C++ application for managing student attendance in lecture halls.

## Project Overview

This system addresses the challenges of paper-based attendance taking by providing a digital solution that:
- Registers and manages student records
- Creates and manages lecture sessions
- Marks attendance (Present, Absent, Late)
- Generates attendance reports and summaries
- Persists data locally in text files

## Features

### 1. Student Management
- Register new students with index number and name
- View all registered students
- Search students by index number
- Data persists in `students.txt`

### 2. Attendance Session Management
- Create lecture sessions (course code, date, start time, duration)
- Mark attendance for each student in a session
- Update attendance records
- Sessions saved as `session_[COURSE_CODE]_[DATE].txt`

### 3. Reports and Summaries
- Display attendance list for a specific session
- Show attendance summary counts (Present, Absent, Late)
- Generate attendance statistics

### 4. Data Persistence
- All student records stored in `students.txt`
- Each session stored in separate file
- Data automatically loads on program startup
- Works completely offline

## Technical Stack

- **Language:** C++
- **Compiler:** MinGW (Windows)
- **IDE:** VS Code
- **File Storage:** Text files (fstream)
- **Version Control:** Git & GitHub

## Project Structure

```
digital-attendance-system/
├── main.cpp                    # Entry point, menu system
├── Student.h                   # Student class header
├── Student.cpp                 # Student class implementation
├── AttendanceSession.h         # AttendanceSession class header
├── AttendanceSession.cpp       # AttendanceSession class implementation
├── students.txt                # Student records (auto-generated)
├── session_*.txt               # Session records (auto-generated)
├── README.md                   # This file
└── .gitignore                  # Git ignore rules
```

## Getting Started

### Prerequisites
- Windows OS
- MinGW C++ compiler (or any C++ compiler)
- VS Code with C++ extension
- Git

### Installation

1. Clone the repository:
```bash
git clone https://github.com/YOUR_USERNAME/digital-attendance-system.git
cd digital-attendance-system
```

2. Compile the project:
```bash
g++ -o attendance main.cpp Student.cpp AttendanceSession.cpp
```

3. Run the application:
```bash
attendance.exe
```

## Usage

### Main Menu
```
===== DIGITAL ATTENDANCE SYSTEM =====
1. Student Management
2. Attendance Session Management
3. Reports and Summary
4. Exit
```

### Student Management
- Add new students
- View all students
- Search by index number

### Session Management
- Create new lecture session
- Mark attendance for students
- Update attendance records

### Reports
- View session attendance list
- View attendance summary

## Data Files

### students.txt
Stores all registered students:
```
INDEX_NUMBER|STUDENT_NAME
EE001|John Doe
EE002|Jane Smith
```

### session_[COURSE]_[DATE].txt
Stores attendance for each session:
```
COURSE_CODE|DATE|START_TIME|DURATION
STUDENT_INDEX|ATTENDANCE_STATUS
EE001|Present
EE002|Absent
EE003|Late
```

## Development Timeline

### Week 1: Foundation
- ✓ GitHub repository setup
- ✓ Project structure
- Student class implementation
- Add/view students functionality

### Week 2: Session Management
- AttendanceSession class
- Create lecture sessions
- Menu-driven interface

### Week 3: Attendance & Reports
- Attendance marking logic
- Report generation
- Input validation

### Week 4: Polish & Submission
- File I/O implementation
- Code refactoring
- Testing and bug fixes
- Final documentation

## Code Quality Standards

- Clear variable and function names
- Comments for complex logic
- Proper error handling
- Input validation
- Modular design with separate classes

## Marking Scheme (30 Marks)

| Component | Marks |
|-----------|-------|
| Student Management | 6 |
| Session Creation | 6 |
| Attendance Marking | 6 |
| File Storage & Loading | 6 |
| Reports & Summary | 4 |
| Code Quality | 2 |

## Submission

- **Code Deadline:** February 23, 2026
- **Demonstration:** February 24, 2026
- **Submission Method:** GitHub repository with commit history

## Important Notes

- Application must work offline (no internet required)
- All data stored locally in text files
- Minimum 3 meaningful commits per week
- Original work only
- Individual or team of 2 maximum

## Author

[Your Name]
Course: EEE227 - Introduction to C++ Programming
Programme: HND Electrical Engineering (Level 200)
