#include <iostream>
#include "Account.cpp"
using namespace std;

class AccountDAO {
  public:
    virtual void adddrink(Account* account) = 0;
    virtual void viewdrink() = 0;
    virtual void updateDrinkinginformation(Account* account) = 0;
    virtual void deleteDrinkinginformation(Account* account) = 0;
    virtual void sortDrinkinginformation() = 0;
    virtual void searchDrinkinginformation(Account* account) = 0;
    virtual void saveDrinkinginformation() = 0;
    virtual void loadDrinkinginformation() = 0;
};