# Bank Management System

This is my C++ project for a Banking System. It uses OOP concepts and File Handling to keep data saved permanently.

### Features
* **Open Account:** Create a new account with a name and initial balance.
* **Deposit & Withdraw:** Add or remove money (checks for minimum balance).
* **Balance Enquiry:** Check details for a specific account.
* **Close Account:** Delete an account from the system.
* **Show All:** Lists every account currently in the file.
* **Persistence:** Everything saves to `my.txt` automatically.

### Technical Details
* **Language:** C++
* **Data Structure:** Used `std::map` for fast account lookups.
* **File Handling:** Uses `ifstream` and `ofstream` to read/write data.
* **Exception Handling:** Throws error if you try to withdraw more than you have.
* **Operator Overloading:** Overloaded `<<` and `>>` for easier file I/O.

### How to Run
1. Compile the code:
   ```bash
   g++ banking.cpp -o bank
   ```
2. Run the application:
   ```bash
   ./bank
   ```