# Cpp-Projects
 
![C++](https://img.shields.io/badge/C%2B%2B-00599C?logo=c%2B%2B&logoColor=white)
![OOP](https://img.shields.io/badge/OOP-Object--Oriented-blue)
 
A collection of C++ projects demonstrating core C++ principles, focusing on memory management, robustness, and clean system architecture.
 
## 🔑 Key Concepts Demonstrated
 
- **Classes & Objects** — encapsulation of data and behavior
- **Dynamic Memory Management** — heap allocation with `new`/`delete`, Rule of Three
- **Inheritance & Polymorphism** — virtual functions, abstract base classes, pure virtual methods
- **Operator Overloading** — customizing standard operators for user-defined types
- **Abstract Interfaces** — interface pattern using pure virtual classes
- **Factory Pattern** — decoupled object creation
- **File I/O** — persistent data storage and retrieval using standard streams
 
---
 
## 📂 Featured Projects
 
### Ikariam
A building simulation engine inspired by the browser strategy game Ikariam.
- Abstract base class `Building` with pure virtual `print()` and `clone()`
- Rule of Three — deep copy constructor, assignment operator, destructor
- Clone pattern — buildings heap-allocated when added to Island
- Polymorphic `Island` managing a dynamic array of `Building*` pointers
 
```bash
cd Ikariam/src && g++ -I../include *.cpp -o ikariam && ./ikariam
```
 
---
 
### Sorting Algorithms
Five sorting algorithms implemented via an abstract `iSorter` interface.
- Selection, Bubble, Insertion, Quick, and Merge sort
- Factory pattern — `CreateSorter(int)` instantiates the correct algorithm
- All sorting through `iSorter*` pointers — no knowledge of concrete type needed
- No STL — raw arrays and manual memory management throughout
 
```bash
cd Sorting && g++ Sorter.cpp main.cpp -o sorting && ./sorting
```
 
---
 
### MarketPlus
A dynamic inventory and shopping engine simulating e-commerce logic with dynamic arrays.
 
```bash
cd MarketPlus && g++ *.cpp -o marketplus && ./marketplus
```
 
---
 
### CreditCard
Financial utility for validating card numbers and managing credit limits.
 
```bash
cd CreditCard && g++ *.cpp -o creditcard && ./creditcard
```
 
---
 
⚙️ Each project is self-contained. Navigate to the project directory and compile using a C++ compiler (e.g., g++).
 
*Developed by Xenofon Gkioka 
 
