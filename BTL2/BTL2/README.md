# Hash Table Implementation in C++ (Linear Probing with Fibonacci Hashing)

This project implements a hash table in C++ using:

### **Linear Probing** for collision resolution
### **Fibonacci Hashing** for better key distribution

---

### How to Build and Run

## Using Visual Studio 2022

1. **Create or open a C++ project:**
   - Open Visual Studio 2022.
   - Create a new C++ Console Application or open your existing one.

2. **Add source files:**
   - Add all `.cpp` and `.h` files into the project:  
     _Right-click the project → Add → Existing Item..._

3. **Build the project:**
   - Go to `Build > Build Solution` or press `Ctrl + Shift + B`.

4. **Run the program:**
   - Press `F5` (with debugger) or `Ctrl + F5` (without debugger).

---

### Features

## **Linear Probing**
  - Uses open addressing with linear probing.
  - Efficient for search, insert, and delete operations.
  - Avoids clustering better when combined with Fibonacci hashing.

## **Fibonacci Hashing**
  - Uses the golden ratio constant to distribute keys more evenly.
  - Helps reduce collisions compared to modulo-based hash functions.

## **Operations Supported**
  - Insert key-value pairs
  - Search for keys
  - Overwrite values if keys already exist
  - Print current hash table state

---

### Notes

- No automatic resizing is implemented.
- The hash table size is fixed at initialization (a prime number is recommended).
- You can customize or extend the hash function as needed.

---

### Files

- `main.cpp` — Example usage of the hash table.
- `Traditional_Hash.h / .cpp` — Linear probing with traditional hash.
- `Fibonacci_Hash.h / .cpp` — Linear probing with Fibonacci hash.

---
