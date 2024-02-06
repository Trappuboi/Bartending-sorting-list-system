#pragma once
#include<iostream>
#include<fstream>
#include <stdexcept>
#include <string>
#include <algorithm>
#include "validation.cpp"
using namespace std;
class login
{
private:
    string username;
    string length;
    string password;
public:

validation vali;


bool userLogin() {
    bool userFound = false;
    string fileUsername, filePassword;
    username = vali.input_username();
    password = vali.input_password();
    ifstream fin("users.dat", ios::in);
    if (!fin.is_open()) {   
        cerr << "Cannot open file" << endl;
        return false;
    }
    while (fin >> fileUsername >> filePassword) {
        if (fileUsername == username && filePassword == password) {
            userFound = true;
            break;
        }
    }
    fin.close();
    if (!userFound) {
        cout << "Username or Password is incorrected!" << endl;
    }
    return userFound;
}

void userRegister() {
    username = vali.input_username();
    password = vali.input_password();
    ofstream fout("users.dat", ios::out | ios::app);
    if (!fout.is_open()) {
        cerr << "Cannot open file" << endl;
        return;
    }
    fout << username << " " << password << endl;
    fout.close();
    cout << "User created" << endl;
}


};