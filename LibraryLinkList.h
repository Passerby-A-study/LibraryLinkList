#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

class Book;
class Admin;
class User;

// ============= Book ====================
class Book {
private:
    struct {
        string BookName;
        string BookID;
        bool isBorrow;
    } BookInfo;
    Book* Next;  // 指向下一本书的指针

public:
    Book(string& name, string& id, bool ib = false);
    Book(const string& name = "None", const string& id = "000000", bool ib = false);
    virtual string GetName() { return BookInfo.BookName; }
    virtual string GetID() { return BookInfo.BookID; }
    virtual bool GetStatus() { return BookInfo.isBorrow; }
    virtual Book* GetNext() { return Next; }
    virtual void ChangeStatus() { BookInfo.isBorrow = !BookInfo.isBorrow; }
    friend class Library;
};

// ============ Library =================
class Library {
private:
    Book* BookShelterHead;
    Book* BookShelterRear;
    Book Header;
    vector<Admin*> LibAdmin;
    vector<User*> LibUser;

public:
    Library();
    void Add(Book& b);
    void Show();
    bool isBorrow(string& s);
    bool isReturn(string& s);
    ~Library();
};

// ============= Person ===================
class Person {
private:
    string UserName;
    string UserID;

public:
    Person(string& name, string& id) : UserName(name), UserID(id) {}
    virtual string GetName() { return UserName; }
    virtual string GetID() { return UserID; }
};

// ============= Admin ====================
class Admin : public Person {
public:
    Admin(string& name, string& id) : Person(name, id) {}
    void AddBook(Library& Li);
    void Show(Library& Li);
    void Choose(Library& Li);
    int PrintAdminMenu(Library& Li);
};

// ============= User =====================
class User : public Person {
public:
    User(string& name, string& id) : Person(name, id) {}
    void BorrowBook(Library& Li);
    void ReturnBook(Library& Li);
    void Show(Library& Li);
    void Choose(Library& Li);
    int PrintUserMenu(Library& Li);
};

// ============= Menu =====================
int PrintLogin();