#include"LibraryLinkList.h"
int main() {
    Library Li;
    while (1) {
        int choice = PrintLogin();
        if (choice == 0) {
            cout << "Bye!\n";
            break;
        }

        switch (choice) {
        case 1: {
            string name, id;
            cout << "Pls Enter Your Name: ";
            cin >> name;
            cout << "Pls Enter Your ID: ";
            cin >> id;
            Admin A(name, id);
            A.Choose(Li);
            cout << "Bye Admin!\n";
            break;
        }
        case 2: {
            string name, id;
            cout << "Pls Enter Your Name: ";
            cin >> name;
            cout << "Pls Enter Your ID: ";
            cin >> id;
            User U(name, id);
            U.Choose(Li);
            cout << "Bye User!\n";
            break;
        }
        default:
            cout << "Invalid choice. Try again.\n";
            break;
        }
        cin.clear();
        cin.ignore(10000, '\n');
    }
    return 0;
}
