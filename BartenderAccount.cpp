#pragma once
#include <iostream>
#include "Account.cpp"
#include "validation.cpp"
#include <iomanip>
using namespace std;

class BartenderAccount : public Account {

  private:
    int duration;

  public:
    BartenderAccount() : Account() {
      duration = 0;
    }

    BartenderAccount(int DrinkID, string name, string quantity_num, int duration) : Account (DrinkID, name, quantity_num) {
      setdays(duration);
    }

    void setdays(int duration) {
      if(duration > 0) {
        this-> duration = duration;
      }
      else {
        throw BadInputException();
      }
    }

    int getdays () const {
      return duration;
    }

    void input() {
      int duration;
      Account::input();
      duration = vali.input_day();
      setdays(duration);
    }

    void output() override {
      Account::output();
      cout << setw(18) << getdays();
    }

    ofstream &write(std::ofstream &out) {
      Account::write(out);
      out.write(reinterpret_cast<const char *>(&duration), sizeof(duration));
      return out;
    }

    istream &read(std::istream &in) {
      Account::read(in);
      in.read(reinterpret_cast<char *>(&duration), sizeof(duration));
      return in;
    }

};