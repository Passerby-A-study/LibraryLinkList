#include"LibraryLinkList.h"
// ============ Admin Functions ============
void Admin::AddBook(Library& Li) {
    string name;
    string id;
    cout << "Pls Enter the Name of Book: " << endl;
    cin >> name;
    cout << "Pls Enter the ID of Book: " << endl;
    cin >> id;
    Book* p = new Book(name, id);
    Li.Add(*p);
}

void Admin::Show(Library& Li) {
    cout << "BookShelter: " << endl;
    cout << setw(20) << "Book_Name" << setw(20) << "Book_ID" << setw(20) << "Status" << endl;
    cout << setfill('-') << setw(60) << "" << setfill(' ') << endl;
    Li.Show();
    cout << "\n";
}

int Admin::PrintAdminMenu(Library& Li) {
    cout << "Welcome " << GetName() << " !" << endl;
    cout << "1 : Show the Books in the Shelter" << endl;
    cout << "2 : Add Book" << endl;
    cout << "Pls Enter Your Choice (Enter the Number, Q / q to Quit to Login):" << endl;
    int choice;
    cin >> choice;
    if (!cin) {
        return 0;
    }
    return choice;
}

void Admin::Choose(Library& Li) {
    while (1) {
        int choice = PrintAdminMenu(Li);
        switch (choice) {
        case 1:
            Show(Li);
            break;
        case 2:
            AddBook(Li);
            break;
        case 0:
            cout << "Returning to login..." << endl;
            return;
        default:
            cout << "Invalid choice, please try again." << endl;
            break;
        }
    }
}

// ============= Book Functions ============
Book::Book(string& name, string& id, bool ib) {
    BookInfo.BookName = name;
    BookInfo.BookID = id;
    BookInfo.isBorrow = ib;
    Next = nullptr;
}
Book::Book(const string& name, const string& id, bool ib) {
    BookInfo.BookID = id;
    BookInfo.BookName = name;
    BookInfo.isBorrow = ib;
    Next = nullptr;
}

// ============ Library Functions ===========
Library::Library() {
    BookShelterHead = &Header;
    BookShelterRear = &Header;
    Header.Next = BookShelterHead;
}

void Library::Add(Book& b) {
    BookShelterRear->Next = &b;
    BookShelterRear = &b;
    BookShelterRear->Next = BookShelterHead;
    cout << "\nBook added successfully!\n\n";
}

void Library::Show() {
    Book* current = BookShelterHead->Next;
    while (current != BookShelterHead) {
        cout << setw(20) << current->GetName()
            << setw(20) << current->GetID()
            << setw(20) << (current->GetStatus() ? "Borrowed" : "Available") << endl;
        current = current->Next;
    }
}

bool Library::isBorrow(string& s) {
    if (s == "q" || s == "Q") return true;

    Book* current = BookShelterHead->Next;
    while (current != BookShelterHead) {
        if (current->GetID() == s) {
            if (!current->GetStatus()) {
                current->ChangeStatus();
                cout << "Borrow Successfully!" << endl;
                return true;
            }
            else {
                cout << "Failed, the book is already borrowed. Try Again." << endl;
                return false;
            }
        }
        current = current->Next;
    }
    cout << "Book not found, Try Again: " << endl;
    return false;
}

bool Library::isReturn(string& s) {
    if (s == "q" || s == "Q") return true;

    Book* current = BookShelterHead->Next;
    while (current != BookShelterHead) {
        if (current->GetID() == s) {
            if (current->GetStatus()) {
                current->ChangeStatus();
                cout << "Return Successfully!" << endl;
                return true;
            }
            else {
                cout << "Failed, You Haven't Borrowed the Book. Try Again.£¨ q / Q to Quit£©" << endl;
                return false;
            }
        }
        current = current->Next;
    }
    cout << "Book not found, Try Again: " << endl;
    return false;
}

Library::~Library() {
    Book* current = BookShelterHead->Next;
    while (current != BookShelterHead) {
        Book* next = current->Next;
        delete current;
        current = next;
    }

    for (auto admin : LibAdmin) {
        delete admin;
    }

    for (auto user : LibUser) {
        delete user;
    }
}

// ============ User Functions ============
void User::Show(Library& Li) {
    cout << "BookShelter: " << endl;
    cout << setw(20) << "Book_Name" << setw(20) << "Book_ID" << setw(20) << "Status" << endl;
    cout << setfill('-') << setw(60) << "" << setfill(' ') << endl;
    Li.Show();
    cout << "\n";
}

void User::BorrowBook(Library& Li) {
    string b;
    cout << "Pls Enter the ID of Book( q / Q to Quit): ";
    cin >> b;
    while (!Li.isBorrow(b)) {
        cin >> b;
    }
}

void User::ReturnBook(Library& Li) {
    string b;
    cout << "Pls Enter the ID of Book( q / Q to Quit): ";
    cin >> b;
    while (!Li.isReturn(b)) {
        cin >> b;
    }
}

int User::PrintUserMenu(Library& Li) {
    cout << "Welcome " << GetName() << " !" << endl;
    cout << "1 : Show the Books in the Shelter" << endl;
    cout << "2 : Borrow Book" << endl;
    cout << "3 : Return Book" << endl;
    cout << "Pls Enter Your Choice (Enter the Number, Q / q to Quit to Login):" << endl;
    int choice;
    cin >> choice;
    if (!cin) {
        cout << "Bye! ";
        return 0;
    }
    return choice;
}

void User::Choose(Library& Li) {
    while (1) {
        int choice = PrintUserMenu(Li);
        switch (choice) {
        case 1:
            Show(Li);
            break;
        case 2:
            BorrowBook(Li);
            break;
        case 3:
            ReturnBook(Li);
            break;
        case 0:
            cout << "Returning to login..." << endl;
            return;
        default:
            cout << "Invalid choice, please try again." << endl;
            break;
        }
    }
}

// ============ Menu =====================
int PrintLogin() {
    cout << "Pls Login" << endl;
    cout << "1 : Admin" << endl;
    cout << "2 : User" << endl;
    cout << "Choose Your Identity (Enter the Number, Q / q to Quit):" << endl;
    string input;
    cin >> input;
    if (input == "q" || input == "Q") {
        return 0;
    }
    try {
        return stoi(input);
    }
    catch (...) {
        cout << "Invalid input. Please enter 1 for Admin or 2 for User, or Q to quit." << endl;
        return -1;
    }
}
