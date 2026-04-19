# ✈️ Airline Crew Management System

## 📌 Crew Assignment Graph CRUD

A **menu-driven C program** for **Airline Crew Management** that implements full **CRUD operations** using a **Graph Data Structure** to manage crew assignments between crew members.

---

## 👥 Team Members

- **Thirumala Reddy** – Lead Developer  
- **Jaydeep Ram** – Graph Implementation & Testing  

---

## 🎯 Problem Statement

Design a system to manage airline crew members and their assignment relationships efficiently using graphs.

The program supports:

- ✅ Crew Member Management (**Create, Read, Update, Delete**)
- ✅ Crew Assignments (**Directed Graph Relationships**)
- ✅ Dynamic Memory Allocation
- ✅ Proper Memory Cleanup
- ✅ Robust Input Validation
- ✅ Error Handling

---

## 🏗️ Data Structures Used

### 1️⃣ Crew Node (Primary Linked List)


typedef struct Crew {
    int id;                 // Unique crew ID
    char name[50];          // Crew member name
    struct Crew* next;      // Next crew in list
    struct AdjList* adj;    // Adjacency list for assignments
} Crew;
2️⃣ Adjacency List Node (Graph Edges)  :


 typedef struct AdjList {
    struct Crew* dest;      // Destination crew member
    struct AdjList* next;   // Next assignment
} AdjList;

⚙️ Features
1.Add New Crew Members
2.Delete Existing Crew Members
3.Update Crew Details
4.Search Crew by ID
5.Display Crew Assignment Graph
6.Add Directed Assignments Between Crew Members
7.Menu Driven Interface

📊 Time Complexity  :

| Operation      | Time Complexity | Space Complexity |
| -------------- | --------------- | ---------------- |
| Add Crew       | O(1)            | O(1)             |
| Delete Crew    | O(n)            | O(1)             |
| Update Crew    | O(n)            | O(1)             |
| Search Crew    | O(n)            | O(1)             |
| Display Graph  | O(V + E)        | O(1)             |
| Add Assignment | O(n)            | O(1)             |


🖥️ Compilation:

• GCC Compiler (Linux / Mac / Windows with MinGW)
• Standard C Library
 

📋 Menu Interface  :

====================================
 ✈ AIRLINE CREW MANAGEMENT SYSTEM
====================================
1. Add Crew (Create)
2. Delete Crew
3. Update Crew
4. Search Crew
5. Display Graph
6. Add Assignment
7. Exit
====================================

📌 Sample Output :  

Enter Choice: 1

Enter Crew ID: 101
Enter Crew Name: Captain Smith
✅ Crew Added Successfully!

Enter Choice: 1

Enter Crew ID: 102
Enter Crew Name: Co-Pilot Jones
✅ Crew Added Successfully!

Enter Choice: 6

Enter Source Crew ID: 101
Enter Destination Crew ID: 102
✅ Assignment Added!

Enter Choice: 5

--- Crew Assignment Graph ---
Crew 102 (Co-Pilot Jones) ➝
Crew 101 (Captain Smith) ➝ 102

Enter Choice: 4

Enter Crew ID to Search: 101
🔍 Found → ID: 101 | Name: Captain Smith

Demo Video Link  :



  

