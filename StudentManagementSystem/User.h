#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class User {
protected:
    string username;
    string password;

public:
    User(const string& user, const string& pass) : username(user), password(pass) {}
    virtual bool Authenticate(const string& user, const string& pass) {
        return username == user && password == pass;
    }
    virtual void DisplayRole() const = 0;
    virtual ~User() {}
};

class Admin : public User {
public:
    Admin(const string& user, const string& pass) : User(user, pass) {}
    void DisplayRole() const override {
        cout << "Role: Admin" << endl;
    }
};

class Teacher : public User {
public:
    Teacher(const string& user, const string& pass) : User(user, pass) {}
    void DisplayRole() const override {
        cout << "Role: Teacher" << endl;
    }
};

class StudentUser : public User {
public:
    StudentUser(const string& user, const string& pass) : User(user, pass) {}
    void DisplayRole() const override {
        cout << "Role: Student" << endl;
    }
};
