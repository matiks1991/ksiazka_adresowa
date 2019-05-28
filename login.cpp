#include <iostream>
#include <fstream>
#include <windows.h>
#include <sstream>
#include <vector>
#include <algorithm>
#include "login.h"

using namespace std;

MainInterface::MainInterface()
{

}

void MainInterface::overwriteFileUsers()
{
    file.open( "Uzytkownicy.txt", ios::out | ios::trunc );

    if(file.good() == true)
    {
        for(i=0; i<users.size(); i++)
        {
            file << users[i].id << "|";
            file << users[i].name << "|";
            file << users[i].password << "|"  << endl;

        }
        file.close();

        cout << "Sukces!" << endl;
        Sleep(1500);
    }
    else
    {
        cout << "Nie udalo sie przeprowadzic operacji!" << endl;
        system("pause");
    }
}

void MainInterface::registration()
{
    cout << "Podaj nazwe uzytkownika: " << endl;
    cin >> name;

    i = 0;
    while(i < users.size())
    {
        if(users[i].name == name)
        {
            cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika.";
            cin >> name;
            i = 0;
        }
        else
        {
            i++;
        }
    }
    cout << "Podaj haslo: ";
    cin >> password;

    templateUser.name = name;
    templateUser.password = password;
    templateUser.id = users.size()+1;
    users.push_back(templateUser);


    file.open("Uzytkownicy.txt", ios::app);

    if(file.good() == true)
    {
        file << templateUser.id << "|";
        file << templateUser.name << "|";
        file << templateUser.password << "|"  << endl;

        file.close();

        cout << "Konto zalozone." << endl;
    }
    else
    {
        cout << "Nie udalo sie dodac konta!" << endl;
    }

    Sleep(1500);
}

int MainInterface::login()
{
    cout << "Podaj login: ";
    cin >> name;

    for(i = 0; i < users.size(); i++)
    {
        if(users[i].name == name)
        {
            for (int proby = 0; proby < 3; proby++)
            {
                cout << "Podaj haslo. Pozostalo prob " << 3-proby << ": ";
                cin >> password;
                if (users[i].password == password)
                {
                    cout << "Zalogowales sie." << endl;
                    Sleep(500);
                    return users[i].id;
                }
            }
            cout << "Podales 3 razy bledna haslo. Poczekaj 3 sekundy przed kolejna proba" << endl;
            Sleep(3000);
            return 0;
        }
    }
    cout << "Nie ma uzytkownika z takim loginem" << endl;
    Sleep(1000);
    return 0;
}

void MainInterface::passwordChange()
{
    cout << "Podaj nowe haslo: ";
    cin >> password;


    for(i=0; i<users.size(); i++)
    {
        if(users[i].id == idLoggedInUser)
        {
            users[i].password = password;
        }
    }

    overwriteFileUsers();
}

void MainInterface::downloadDataOfUsersFromFile()
{
    numberOfLine = 1;

    fstream file;
    file.open("Uzytkownicy.txt", ios::in);

    if(file.good() == true)
    {
        while (getline(file,line,'|'))
        {
            switch (numberOfLine)
            {
            case 1:
                templateUser.id = atoi(line.c_str());
                break;
            case 2:
                templateUser.name = line;
                break;
            case 3:
                templateUser.password = line;
                break;
            }
            if (numberOfLine >= 3)
            {
                numberOfLine = 1;
                users.push_back(templateUser);
            }
            else
            {
                numberOfLine++;
            }
        }
        file.close();
    }
    else
    {
        cout << "Nie udalo sie wczytac pliku uzytkownikow!" << endl;
        system("pause");
    }
}
