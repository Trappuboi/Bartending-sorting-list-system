#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
#include "Account.cpp"
#include "BartenderAccount.cpp"
#include "AccountDAO.cpp"
#include "validation.cpp"
using namespace std;

enum {

  FINDNUM = 1 , FINDNAME

};

enum {

  SORTNUM = 1 , SORTNAME

};

class Bartender : public AccountDAO {

private:

  vector<BartenderAccount*> Acc;

public:

  validation vali;

  ~Bartender() {
    for (auto& account : Acc) {
      delete account;
    }
  }

  void info_edit_menu() {
    cout << "==========EDIT MENU==========" << endl;
    cout << "1. DrinkID" << endl;
    cout << "2. Name drink" << endl;
    cout << "3. Quantity" << endl;
    cout << "4. Duration" << endl;
    cout << "5. Back" << endl;
  }

  void search_menu() {
    cout << "==========Search MENU==========" << endl;
    cout << "1. Seach by DrinkID" << endl;
    cout << "2. Seach by Name" << endl;
    cout << "3. Back to main menu" << endl;
  }

  void Button_to_Continue() {
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
  }

  void DotDotDot() {
    for (int i = 0; i < 5; i++) {
        cout << ".";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    cout << endl;
  }

  void output_title() {
    cout << "------------------------------------------------------------------\n";
    cout << "    DrinkID           Name            Quantity           Duration \n";
    cout << "------------------------------------------------------------------\n";
  }

  void adddrink(Account* account){
    auto receptionistAccount = make_unique<BartenderAccount>();
    receptionistAccount->input();
    Acc.push_back(receptionistAccount.release());
  }

  void viewdrink() {
    output_title();
    for (const auto& it : Acc) {
      try {
          it->output();
          cout << endl;
      }
      catch (const std::exception& e) {
          cerr << "Exception: " << e.what() << endl;
      }
    }
    Button_to_Continue();
  }

  void updateDrinkinginformation (Account* account) {
    int choice;
    char ans = 'N';
    search_menu();
    choice = vali.getChoice();
    switch (choice) {
    case FINDNUM: {
      int RoomNumber;
      RoomNumber = vali.input_drinkID();
      auto it = find_if(Acc.begin(), Acc.end(), [RoomNumber](Account *account) { return account->getdrinkID() == RoomNumber; });
      do {
        if (it != Acc.end()) {
          int choice;
          info_edit_menu();
          choice = vali.getChoice();
          switch (choice) {
            case 1: {
              int new_drinkID;
              cout << "Enter new Drinks: ";
              cin >> new_drinkID;
              Account *target = (*it);
              target->setdrinkID(new_drinkID);
              cout << "Drink changed successfully" << endl;
            }
            break;

            case 2: {
              string new_name;
              cout << "Enter new name: ";
              cin >> new_name;
              Account *target = (*it);
              target->setname(new_name);
              cout << "Name changed successfully" << endl;
            }
            break;

            case 3: {
              string new_num;
              cout << "Enter new Quantity: ";
              cin >> new_num;
              Account *target = (*it);
              target->setnum(new_num);
              cout << "Quantity changed successfully" << endl;
            }
            break;

            case 4: {
              int new_duration;
              cout << "Enter new check-in-duration: ";
              cin >> new_duration;
              dynamic_cast<BartenderAccount *>(*it)->setdays(new_duration);
              cout << "duration changed successfully" << endl;
            }
            break;

            case 5:
              break;

            default:
              cout << "Invalid Choice. Please try again" << endl;
              break;
          }
        }
        else {
          cout << "Drink not found" << endl;
        }
        if (Acc.empty()) {
          cout << "Nothing left to update" << endl;
          Button_to_Continue();
          break;
        }
        cout << "Do you want to continue (Y/N)? ";
        cin >> ans;
      } while ((ans == 'Y') || (ans == 'y'));
    }
    break;

    case FINDNAME:
    {
      string name;
      cout << "Enter name: ";
      cin >> name;
      auto it = find_if(Acc.begin(), Acc.end(), [name](const Account *account) { return account->getname() == name; });
      do {
        if (it != Acc.end()) {
          int choice;
          Account *target = (*it);
          info_edit_menu();
          choice = vali.getChoice();
          switch (choice) {
          case 1: {
            int new_drinkID;
            cout << "Enter new DrinkID: ";
            cin >> new_drinkID;
            target->setdrinkID(new_drinkID);
            cout << "DrinkID changed successfully" << endl;
          }
          break;

          case 2: {
            string new_name;
            cout << "Enter new Name: ";
            cin >> new_name;
            target->setname(new_name);
            cout << "Name changed successfully" << endl;
          }
          break;

          case 3: {
            string new_num;
            cout << "Enter new Quantity: ";
            cin >> new_num;
            target->setnum(new_num);
            cout << "Quantity changed successfully" << endl;
          }
          break;

          case 4: {
            int new_duration;
            cout << "Enter new duration-check-in: ";
            cin >> new_duration;
            dynamic_cast<BartenderAccount *>(*it)->setdays(new_duration);
            cout << "duration changed successfully" << endl;
          }
          break;

          case 5:
            break;

          default:
            cout << "Invalid Choice. Please try again" << endl;
            break;
          }
        }

        else
        {
          cout << "drink not found" << endl;
        }

        if (Acc.empty()) {
          cout << "Nothing left to update" << endl;
          Button_to_Continue();
          break;
        }

        cout << "Do you want to continue (Y/N)? ";
        cin >> ans;

      } while ((ans == 'Y') || (ans == 'y'));
    }
    break;

    case 3:
      break;

    default:
      cout << "Invalid choice." << endl;
      Button_to_Continue();
      updateDrinkinginformation(account);
    }
  }

  void deleteDrinkinginformation (Account* account) {
    int choice;
    char ans = 'N';
    search_menu();
    choice = vali.getChoice();
    switch (choice) {
    case FINDNUM: {
      int RoomNumber;
      do {
        RoomNumber = vali.input_drinkID();
        auto it = find_if(Acc.begin(), Acc.end(), [RoomNumber](const Account *account) { return account->getdrinkID() == RoomNumber; });
        if (it != Acc.end())
        {
          cout << "drink information to be deleted:\n";
          Account *target = (*it);
          output_title();
          target->output();
          cout << endl;
          char choice;
          cout << "Do you want to delete this information? (y/n): ";
          cin >> choice;
          if (choice == 'y' || choice == 'Y') {
            Acc.erase(it);
            cout << "drink information deleted successfully.\n";
          }
          else {
            cout << "Deletion canceled.\n";
          }
        }
        else {
          cout << "drink info not found" << endl;
        }
        if (Acc.empty()) {
          cout << "Nothing left to delete" << endl;
          Button_to_Continue();
          break;
        }
        cout << "Do you want to continue (Y/N)? ";
        cin >> ans;
      } while ((ans == 'Y') || (ans == 'y'));
    }
    break;

    case FINDNAME: {
      string name;
      do {
        cout << "Enter name: ";
        cin >> name;
        auto it = find_if(Acc.begin(), Acc.end(), [name](const Account *account) { return account->getname() == name; });
        if (it != Acc.end()) {
          cout << "drink information to be deleted:\n";
          Account *target = (*it);
          output_title();
          target->output();
          cout << endl;
          cout << "Do you want to delete this information? (y/n): ";
          char choice;
          cin >> choice;
          if (choice == 'y' || choice == 'Y') {
            Acc.erase(it);
            cout << "drink information deleted successfully.\n";
          }
          else {
            cout << "Deletion canceled.\n";
          }
        }
        else {
          cout << "drink info not found" << endl;
        }
        if (Acc.empty()) {
          cout << "Nothing left to delete" << endl;
          cout << "Press Enter to continue...";
          cin.ignore();
          cin.get();
          break;
        }
        cout << "Do you want to continue (Y/N)? ";
        cin >> ans;
      } while ((ans == 'Y') || (ans == 'y'));
    }
    break;

    case 3:
      break;

    default:
      cout << "Invalid choice." << endl;
      Button_to_Continue();
      deleteDrinkinginformation(account);
    }
  }

  void sortDrinkinginformation() {
    int choice;
    cout << "==========SORT METHOD==========" << endl;
    cout << "1. Sort by Ascending" << endl;
    cout << "2. Sort by Descending" << endl;
    cout << "3. Back to main menu" << endl;
    choice = vali.getChoice();
    switch (choice)
    {
    case 1:
      sort(Acc.begin(), Acc.end(), [](const Account *a, const Account *b) { return a->getnum() < b->getnum(); });
      cout << "Sorting";
      DotDotDot();
      cout << "Sorted successfully" << endl;
      Button_to_Continue();
      break;

    case 2:
      sort(Acc.begin(), Acc.end(), [](const Account *a, const Account *b) { return a->getnum() > b->getnum(); });
      cout << "Sorting";
      DotDotDot();
      cout << "Sorted successfully" << endl;
      Button_to_Continue();
      break;

    case 3:
      break;

    default:
      cout << "Invalid choice." << endl;
      Button_to_Continue();
      sortDrinkinginformation();
    }
  }

  void searchDrinkinginformation(Account* account){
    int choice;
    char ans = 'N';
    search_menu();
    choice = vali.getChoice();
    switch (choice) {
    case FINDNUM: {
      int RoomNumber;
      do {
        RoomNumber = vali.input_drinkID();
        auto it = find_if(Acc.begin(), Acc.end(), [RoomNumber](const Account *account) { return account->getdrinkID() == RoomNumber; });
        if (it != Acc.end()) {
          cout << "Roomid found:" << endl;
          output_title();
          Account *target = (*it);
          target->output();
          cout << endl;
        }
        else {
          cout << "drink info not found" << endl;
        }
        if (Acc.empty()) {
          cout << "Nothing left to search" << endl;
          Button_to_Continue();
          break;
        }
        cout << "Do you want to continue (Y/N)? ";
        cin >> ans;
      } while ((ans == 'Y') || (ans == 'y'));
    }
    break;

    case FINDNAME: {
      string name;
      do {
        cout << "Enter name: ";
        cin >> name;
        auto it = find_if(Acc.begin(), Acc.end(), [name](const Account *account) { return account->getname() == name; });
        if (it != Acc.end()) {
          cout << "Name found:" << endl;
          output_title();
          Account *target = (*it);
          target->output();
          cout << endl;
        }
        else {
          cout << "drink info not found" << endl;
        }
        if (Acc.empty()) {
          cout << "Nothing left to search" << endl;
          Button_to_Continue();
          break;
        }
        cout << "Do you want to continue (Y/N)? ";
        cin >> ans;
      } while ((ans == 'Y') || (ans == 'y'));
    }
    break;

    case 3:
      break;

    default:
      cout << "Invalid choice." << endl;
      Button_to_Continue();
      searchDrinkinginformation(account);
    }
  }

  void saveDrinkinginformation() {
    ofstream outputFile("Guest.dat", ios::out |ios::app |ios::binary);
    if (!outputFile.is_open()) {
      cout << "Error in creating file...\n";
      exit(1);
    }
    else {
      for (BartenderAccount *Baccount : Acc) {
        Baccount->write(outputFile);
      }
      cout << "File saved successfully" << endl;
    }
    outputFile.close();
  }

  void loadDrinkinginformation() {
    ifstream inputFile("Guest.dat", ios::in|ios::binary);
    if (!inputFile.is_open()) {
        cout << "Error in opening file...\n";
        exit(1);
    }
    Acc.clear();
    while (inputFile) {
      BartenderAccount *Baccount = new BartenderAccount();
      Baccount->read(inputFile);
      if (inputFile.eof()) {
        delete Baccount;
        break;
      }
      Acc.push_back(Baccount);
    }
    cout << "File loaded successfully" << endl;
    inputFile.close();
  }

};