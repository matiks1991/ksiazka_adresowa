#include <iostream>
#include <fstream>
#include <windows.h>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;


class MainInterface
{

private:
    struct User
    {
        int id = 0;
        string name = "", password = "";
    };
    string name, password, line;
    User templateUser;
    int i = 0;
    int numberOfLine = 1;
    fstream file;

public:
    vector<User> users;
    int idLoggedInUser = 0;

    MainInterface();
    void overwriteFileUsers();
    void registration();
    int login();
    void passwordChange();
    void downloadDataOfUsersFromFile();
};
