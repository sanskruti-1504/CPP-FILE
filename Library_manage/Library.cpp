#include <iostream>
#include <string>
#include <sqlite3.h>
using namespace std;
 
 

sqlite3* db;
 
 

void runQuery(string sql) {
    char* error;
    sqlite3_exec(db, sql.c_str(), NULL, NULL, &error);
}
 
 

int printRow(void* unused, int cols, char* value[], char* colName[]) {
    for (int i = 0; i < cols; i++) {
        cout << colName[i] << ": " << value[i] << "  |  ";
    }
    cout << endl;
    return 0;
}
 
 

void showResults(string sql) {
    char* error;
    sqlite3_exec(db, sql.c_str(), printRow, NULL, &error);
}
 
 
void createTables() {
 
    
    string sql1 =
        "CREATE TABLE IF NOT EXISTS books ("
        "id       INTEGER PRIMARY KEY AUTOINCREMENT, "
        "title    TEXT, "
        "author   TEXT, "
        "is_issued INTEGER DEFAULT 0"   
        ");";
 
    
    string sql2 =
        "CREATE TABLE IF NOT EXISTS members ("
        "id    INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name  TEXT, "
        "email TEXT"
        ");";
 
    
    string sql3 =
        "CREATE TABLE IF NOT EXISTS issued_books ("
        "id          INTEGER PRIMARY KEY AUTOINCREMENT, "
        "book_id     INTEGER, "
        "member_id   INTEGER, "
        "issue_date  TEXT, "
        "return_date TEXT"    
        ");";
 
    runQuery(sql1);
    runQuery(sql2);
    runQuery(sql3);
}
 
 

 
void addBook() {
    string title, author;
 
    cout << "Enter Book Title  : ";
    cin.ignore();
    getline(cin, title);
 
    cout << "Enter Author Name : ";
    getline(cin, author);
 
    string sql = "INSERT INTO books (title, author) VALUES ('" + title + "', '" + author + "');";
    runQuery(sql);
 
    cout << "Book added successfully!\n";
}
 
 
void showAllBooks() {
    cout << "\n--- ALL BOOKS ---\n";
    string sql = "SELECT * FROM books;";
    showResults(sql);
    cout << "-----------------\n";
}
 
 
void searchBook() {
    string keyword;
    cout << "Enter title to search: ";
    cin.ignore();
    getline(cin, keyword);
 
    string sql = "SELECT * FROM books WHERE title LIKE '%" + keyword + "%';";
    cout << "\n--- Search Results ---\n";
    showResults(sql);
}
 
 
void deleteBook() {
    showAllBooks();
    int id;
    cout << "Enter Book ID to delete: ";
    cin >> id;
 
    string sql = "DELETE FROM books WHERE id = " + to_string(id) + ";";
    runQuery(sql);
 
    cout << "Book deleted!\n";
}
 
 

 
void addMember() {
    string name, email;
 
    cout << "Enter Member Name  : ";
    cin.ignore();
    getline(cin, name);
 
    cout << "Enter Email        : ";
    getline(cin, email);
 
    string sql = "INSERT INTO members (name, email) VALUES ('" + name + "', '" + email + "');";
    runQuery(sql);
 
    cout << "Member added successfully!\n";
}
 
 
void showAllMembers() {
    cout << "\n--- ALL MEMBERS ---\n";
    string sql = "SELECT * FROM members;";
    showResults(sql);
    cout << "-------------------\n";
}
 
 

 
void issueBook() {
    showAllBooks();
    int bookId;
    cout << "Enter Book ID to issue: ";
    cin >> bookId;
 
    showAllMembers();
    int memberId;
    cout << "Enter Member ID       : ";
    cin >> memberId;
 
    
    string sql1 = "INSERT INTO issued_books (book_id, member_id, issue_date, return_date) "
                  "VALUES (" + to_string(bookId) + ", " + to_string(memberId) + ", date('now'), '');";
 
    
    string sql2 = "UPDATE books SET is_issued = 1 WHERE id = " + to_string(bookId) + ";";
 
    runQuery(sql1);
    runQuery(sql2);
 
    cout << "Book issued successfully!\n";
}
 
 
void returnBook() {
    
    cout << "\n--- ISSUED BOOKS ---\n";
    string sql = "SELECT * FROM books WHERE is_issued = 1;";
    showResults(sql);
    cout << "--------------------\n";
 
    int bookId;
    cout << "Enter Book ID to return: ";
    cin >> bookId;
 
   
    string sql1 = "UPDATE issued_books SET return_date = date('now') "
                  "WHERE book_id = " + to_string(bookId) + " AND return_date = '';";
 
    
    string sql2 = "UPDATE books SET is_issued = 0 WHERE id = " + to_string(bookId) + ";";
 
    runQuery(sql1);
    runQuery(sql2);
 
    cout << "Book returned successfully!\n";
}
 
 
void showIssueHistory() {
    cout << "\n--- ISSUE HISTORY ---\n";
 
    
    string sql =
        "SELECT "
        "  issued_books.id, "
        "  books.title, "
        "  members.name, "
        "  issued_books.issue_date, "
        "  issued_books.return_date "
        "FROM issued_books "
        "JOIN books   ON issued_books.book_id   = books.id "
        "JOIN members ON issued_books.member_id = members.id;";
 
    showResults(sql);
    cout << "---------------------\n";
}
 
 

int main() {
 
    
    sqlite3_open("library.db", &db);
 
    
    createTables();
 
    cout << "\nWelcome to Library Management System\n";
 
    int choice;
 
    do {
        cout << "\n====== MENU ======\n";
        cout << "1. Add Book\n";
        cout << "2. Show All Books\n";
        cout << "3. Search Book\n";
        cout << "4. Delete Book\n";
        cout << "5. Add Member\n";
        cout << "6. Show All Members\n";
        cout << "7. Issue Book\n";
        cout << "8. Return Book\n";
        cout << "9. Issue History\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
 
        switch (choice) {
            case 1: addBook();          break;
            case 2: showAllBooks();     break;
            case 3: searchBook();       break;
            case 4: deleteBook();       break;
            case 5: addMember();        break;
            case 6: showAllMembers();   break;
            case 7: issueBook();        break;
            case 8: returnBook();       break;
            case 9: showIssueHistory(); break;
            case 0: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
 
    } while (choice != 0);
 
    sqlite3_close(db);   
    return 0;
}