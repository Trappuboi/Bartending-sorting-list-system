#pragma once
#include <iostream>
#include <iomanip>
#include "validation.cpp"
#include "BadInputException.cpp"
using namespace std;

class Account {

  protected:

    int DrinkID;
    string name;
    string quantity_num;
    validation vali;

  public:

    Account () {
    DrinkID = 0;
    name = "unknown";
    quantity_num = "";
    }

    Account (int DrinkID, string name, string quantity_num) {
      setdrinkID(DrinkID);
      setname(name);
      setnum(quantity_num);
    }

    void setdrinkID(const int DrinkID) {
      if(DrinkID > 0) {
        this-> DrinkID = DrinkID;
      }
      else {
        throw BadInputException();
      }
    }

    int getdrinkID() const {
      return DrinkID;
    }

    void setname(const string name) {
      if (!name.empty()) {
        this->name = name;
      }
      else
      {
        throw BadInputException();
      }
    }

    string getname() const {
      return name;
    }

    void setnum(const string quantity_num) {
      if (!quantity_num.empty()) {
        this->quantity_num = quantity_num;
      }
      else {
        throw BadInputException();
      }
    }

    string getnum() const {
      return quantity_num;
    }


    virtual void output() {
      cout << setw(8) << getdrinkID() << setw(17) << getname() << setw(22) << getnum();
    }
      
    virtual void input() {
      int drinkID;
      string name;
      string num;

      drinkID = vali.input_drinkID();
      setdrinkID(drinkID);

      name = vali.input_name();
      setname(name);

      num = vali.input_num();
      setnum(num);

    }

    ofstream &write(std::ofstream &out)
    {
      out.write(reinterpret_cast<const char *>(&DrinkID), sizeof(DrinkID));

      int length = name.length();
      out.write(reinterpret_cast<const char *>(&length), sizeof(length));
      out.write(name.c_str(), length);

      length = quantity_num.length();
      out.write(reinterpret_cast<const char *>(&length), sizeof(length));
      out.write(quantity_num.c_str(), length);

      return out;
    }

    istream &read(std::istream &in)
    {
      int length;

      in.read(reinterpret_cast<char *>(&DrinkID), sizeof(DrinkID));

      in.read(reinterpret_cast<char *>(&length), sizeof(length));
      name.resize(length);
      in.read(&name[0], length);

      in.read(reinterpret_cast<char *>(&length), sizeof(length));
      quantity_num.resize(length);
      in.read(&quantity_num[0], length);

      return in;
    }

};