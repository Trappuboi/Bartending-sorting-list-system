#pragma once
#include<iostream>
#include <string>
#include "BadInputException.cpp"
class validation
{
  private:
    const int maxchar = 12;
    bool boolean;

    bool validate_user(string user) {
      if (user.length() > 10 ) {
        return false;
      }
      return true;
    }

    bool validate_drinkID(int num) {
      if (cin.fail() || num > 200) {
        return false;
      }
      return true;
    }

    bool validate_name(string name) {
      if (name.length() > 30) {
        return false;
      }
      for(int i = 0;i<name.length();i++){
        if(!(name[i] >= 65 && name[i] <= 122)) {
          return false;
        }
      }
      return true;
    }

    bool validate_num(string num) {
      if (num.length() > 10) {
        return false;
      }
      return true;
    }

  public:

    string input_username() {
      string username;
      while (true) {
        cout << "Enter Username: ";
        cin >> username;
        if (!validate_user(username)) {
          cout << "Error: Invalid/max letter reached" << endl;
        }
        else {
          return username;
        }
      }
    }

    string input_password() {
      string password;
      while (true) {
        cout << "Enter Password: ";
        cin >> password;
        if (!validate_user(password)) {
          cout << "Error: Invalid/max letter reached" << endl;
        }
        else {
          return password;
        }
      }
    }

    int input_drinkID() {
      int drinkID;
        while (true)
        {
          cout << "Enter DrinkID: ";
          cin >> drinkID;
          if (!validate_drinkID(drinkID)) {
            cin.clear();
            cin.ignore(200, '\n');
            cout << "Error: Invalid Input" << endl;
          }
          else {
            return drinkID;
          }
        }
    }

    string input_name() {
      string name;
      while (true)
      {
        cout << "Enter Name: ";
        cin >> name;
        if (!validate_name(name)) {
          cout << "Error: Invalid/max letter reached" << endl;
        }
        else {
          return name;
        }
      }
    }

    string input_num() {
      string num;
      while (true) {
        cout << "Enter Quantity: ";
        cin >> num;
        if (!validate_num(num)) {
          cout << "Error: Invalid Input" << endl;
        }
        else {
          return num;
        }
      }
    }

    int input_day() {
      int day;
      while (true) {
        cout << "Enter duration check-ins: ";
        cin >> day;
        if (!validate_drinkID(day)) {     
          cin.clear();
          cin.ignore(200, '\n');
          cout << "Error: Invalid Input" << endl;
          }
        else {
            return day;
        }
      }
    }

    int getChoice() {
      int choice;
      bool valid = false;
      do {
        cout << "Enter a choice: " << flush;
        cin >> choice;
        if (cin.good()) {
          valid = true;
        }
        else {
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cout << "Invalid input! please re-enter." << endl;
        }
      } while (!valid);
      return choice;
    }

};