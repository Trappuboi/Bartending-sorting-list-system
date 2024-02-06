#pragma once
#include <iostream>
#include "Bartender.cpp"
#include "BartenderAccount.cpp"
#include "signupfordrinking.cpp"
#include "validation.cpp"
using namespace std;

enum {
    ADDDRINK = 1,
    DISPLAYDRINK,
    UPDATEDRINK,
    DELETEDRINK,
    SORTDRINK,
    SEARCHDRINK,
    SAVEDRINK,
    LOGOUT,
};

class Application {
    private:

        Bartender re;
        Account* account;
        validation vali;

        void PubMenu() {
            cout << "========== My Bartending List ==========" << endl;
            cout << "1. Add Drinks" << endl;
            cout << "2. View Drink" << endl;
            cout << "3. Update a specific Drink" << endl;
            cout << "4. Delete a specific Drink" << endl;
            cout << "5. Sort Drink" << endl;
            cout << "6. Search for a specific Drink" << endl;
            cout << "7. Save drink data" << endl;
            cout << "8. Log out" << endl;
        }

        void authenticationMenu(){
            cout <<"========== Bars Drinking Management System ==========" << endl;
            cout << "1. Login back to drinking" << endl;
            cout << "2. Register to drinking heaven" << endl;
            cout << "3. Exit" << endl;
        }
        
    public:

        void BartendingManagement() {
            int choice = 0;
            do {
                PubMenu();
                choice = vali.getChoice();
                switch (choice) {
                    case ADDDRINK: {
                        re.adddrink(account);
                        break;
                    }

                    case DISPLAYDRINK:
                        re.viewdrink();
                        break;

                    case UPDATEDRINK: {
                        re.updateDrinkinginformation(account);
                        break;
                    }

                    case DELETEDRINK:
                        re.deleteDrinkinginformation(account);
                        break;

                    case SORTDRINK:
                        re.sortDrinkinginformation();
                        break;

                    case SEARCHDRINK:
                        re.searchDrinkinginformation(account);
                        break;

                    case SAVEDRINK:
                        re.saveDrinkinginformation();
                        break;
                        
                    case LOGOUT:
                        break;

                    default:
                        cout << "Invalid Choice, Try again" << endl;
                        break;
                    }
                
                }while (choice != 8);
        }

        void run() {
            int choice = 0;
            login log;

            do {
                authenticationMenu();
                choice = vali.getChoice();
                switch (choice)
                {
                case 1:
                    if (log.userLogin() == true) {
                        system("cls");
                        re.loadDrinkinginformation();
                        cout << "Welcome to The PUB management system" << endl;
                        BartendingManagement();
                    }
                    break;

                case 2:
                    log.userRegister();
                    break;

                case 3:
                    cout << "Exiting Programm..." << endl;
                    exit(1);

                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
                }
            } while (choice != 0);
        }
};