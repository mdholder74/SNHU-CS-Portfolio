# CS 300: Data Structures and Algorithms Portfolio

## Overview
This portfolio contains my work from CS 300, demonstrating proficiency in data structures, algorithms, and software design principles.

---

## Project Artifacts

### Project One: Data Structure Analysis
**File:** `ProjectOne-Analysis.md`

Runtime and memory analysis comparing three data structures for the ABCU advising program:
- Vectors
- Hash Tables  
- Binary Search Trees

This analysis evaluates Big O complexity for key operations and recommends the optimal data structure based on performance characteristics and operational requirements.

### Project Two: BST Implementation
**File:** `ProjectTwo.cpp`

Working C++ implementation of a Binary Search Tree that:
- Loads course data from CSV files with two-pass validation
- Maintains courses in alphanumeric order automatically
- Provides efficient search functionality with O(log n) performance
- Displays course information with prerequisites
- Includes comprehensive error handling and input validation

---

## Reflections

### What was the problem you were solving in the projects for this course?

The core problem was developing an advising assistance program for ABCU's Computer Science department. Academic advisors needed an efficient way to access course information, view courses in sorted order, and identify prerequisites. My challenge was reviewing three different data structure types including vectors, hash tables, and binary search trees and determining which was the most appropriate for solving the problem. I needed a data structure that could maintain fast search times and sorted output. Throughout my analysis, I reviewed the performance characteristics of each to help determine the most appropriate data structure. After understanding the performance and trade-offs, I implemented the solution that met the most important functional requirements for ABCU's Computer Science department advisors.

### How did you approach the problem? Consider why data structures are important to understand.

Throughout the project, we have been writing pseudocode for vectors, hash tables, and binary search trees for the academic advisors program we are building. My approach was to analyze the code for the major parts of the program, which involve loading, searching, and creating course objects. For each data structure, I broke down the runtime complexity and memory usage. This was important because it allowed me to determine the most appropriate data structure for the program and support that decision using performance and scalability analysis. For example, I evaluated each structure's strengths, including vectors for simplicity, hash tables for constant time search, and binary search trees for maintaining sorted order. Ultimately, I chose the binary search tree because it efficiently supports both sorted traversal and searching operations, which meets the program's needs and aligns with the functions most frequently used by the advisors.

### How did you overcome any roadblocks you encountered while going through the activities or project?

One significant roadblock was understanding the runtime analysis and time complexity of each data structure. At first, it was difficult to identify which operations had a major impact on performance versus those that were minor, and to understand how it all came together to be calculated using Big O notation. I had to go back and review Big O analysis from previous lessons, watch YouTube tutorials, and write detailed comments in my code to help with my understanding. I also created comparison tables for each data structure, analyzing where they performed similarly and where they differed most significantly. Overall, I gained a good understanding of runtime analysis and time complexity, which helped me select the appropriate data structure.

### How has your work on this project expanded your approach to designing software and developing programs?

This project has expanded my approach to software design and program development in a major way. Before, I only knew about vectors, arrays, and objects. Now, I understand hash tables and binary search trees, which gives me more options when designing programs based on different scenarios and program needs. I have learned that before getting started on a design, you should first think about the data structure because, ultimately, you want to ensure your program works efficiently and elegantly. I have also improved my understanding of the trade-offs between time complexity, space complexity, and overall maintainability, and how these factors need to be considered when designing a program.

### How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?

This project changed my approach to programming by emphasizing the planning process. I learned that planning with pseudocode allows you to think through scenarios and work out potential problems before writing actual code. Once you have a solid pseudocode framework, implementing the actual code becomes significantly easier because you have a clear reference to follow and refine. I also learned how crucial comprehensive documentation is, allowing you to clarify why certain decisions were made. Additionally, I improved my ability to write single-responsibility functions that do one thing well, making the code easier to understand and modify. For example, in my BST implementation, separating the public `Insert()` method from the private recursive `insertHelper()` function made the logic clearer and more maintainable. Overall, these good fundamental habits will benefit me in the long run.

---

## Technical Skills Demonstrated

- **Data Structure Analysis**: Comparative evaluation of Vectors, Hash Tables, and Binary Search Trees
- **Algorithm Complexity**: Big O notation analysis for time and space complexity
- **C++ Programming**: Object-oriented design with structs and classes
- **Binary Search Tree Implementation**: Recursive insertion, search, and traversal operations
- **File I/O**: CSV parsing with comprehensive validation
- **Memory Management**: Dynamic allocation with proper deallocation (destructors)
- **Error Handling**: Input validation, file error handling, and edge case management
- **Code Documentation**: Comprehensive inline comments and function documentation
- **Software Design**: Pseudocode planning, modular functions, and maintainable code structure

---

## Course Information

**Course:** CS 300 - Data Structures and Algorithms  
**Institution:** Southern New Hampshire University (SNHU)  
**Completion Date:** December 2025

---

## Repository Structure

```
CS300-Data-Structures/
├── README.md                    (This file - reflections and overview)
├── ProjectOne-Analysis.md       (Data structure comparison and analysis)
└── ProjectTwo.cpp              (Working BST implementation)
```

---

*This portfolio demonstrates proficiency in data structures, algorithmic thinking, and professional software development practices.*
