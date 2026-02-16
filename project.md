INTRODUCTION TO C++ PROGRAMMING – MID SEMESTER 
CAPSTONE PROJECT 
Digital Attendance System for Hour-Based Lectures 
Programme: HND Electrical Engineering (Level 200) 
Course Code: EEE227  
Assessment Type: Project-Based Midterm Assignment 
Weighting: 30 percent 
Duration: Four Weeks 
Code Submission Deadline: February 23, 2026 
Project Demonstration Date: February 24, 2026 
Development Environment: VS Code 
Version Control: GitHub 
Platform: Windows, Offline First 
1. Background and Problem Scenario 
Attendance taking in many lecture halls is still paper-based. This practice leads to lecture 
disruptions, delays between consecutive lectures, misplaced records, and difficulty 
generating reliable attendance summaries. This assignment requires students to design 
and implement a digital attendance system using C++ to address this challenge. 
2. Assignment Type and Rules 
• This is an individual assignment or a team of two students maximum 
• All submitted work must be original 
• GitHub must be used for version control and submission 
• The repository must show steady progress over four weeks 
• Late submissions attract penalties in line with departmental policy 
3. Learning Objectives 
• Apply C++ programming concepts to a real engineering-related problem 
• Demonstrate effective use of variables, arrays, functions, and classes 
• Design a menu-driven console application 
• Implement file handling for persistent storage 
• Demonstrate professional software development practices using GitHub 
4. Technical Requirements 
• Programming Language: C++ 
• User Interface: Console-based 
• Data Storage: Text files using fstream 
• Platform: Windows (offline operation required) 
5. Functional Requirements 
5.1 Student Management 
1. Register students 
2. View all registered students 
3. Search students by index number 
5.2 Attendance Session Management 
1. Create a lecture session (course code, date, start time, duration) 
2. Mark attendance as Present, Absent, or Late 
3. Update attendance records where necessary 
5.3 Reports and Summary 
• Display attendance list for a session 
• Display summary counts of attendance status 
5.4 File Storage 
• Save student records to file 
• Save and load attendance sessions 
• Data must persist between program executions 
6. Weekly Timeline and Milestones 
Week 1 
• Create GitHub repository and initial project structure 
• Implement Student class 
• Add and view students 
• Minimum of 3 meaningful commits 
Week 2 
• Implement AttendanceSession class 
• Create lecture sessions 
• Build menu-driven program flow 
• Minimum of 3 meaningful commits 
Week 3 
• Implement attendance marking logic 
• Generate reports and summaries 
• Improve input validation 
• Minimum of 3 meaningful commits 
Week 4 
• Implement file saving and loading 
• Refactor code and improve readability 
• Complete README documentation 
• Final testing and submission 
• Minimum of 3 meaningful commits 
7. Sample Repository Structure 
digital-attendance-system/ 
│── main.cpp 
│── README.md 
│── students.txt 
│── session_EE201_YYYY_MM_DD.txt 
8. Marking Scheme (30 Marks) 
Student management: 6 marks 
Session creation: 6 marks 
Attendance marking: 6 marks 
File storage and loading: 6 marks 
Reports and summary: 4 marks 
Code quality and structure: 2 marks