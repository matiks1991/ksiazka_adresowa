#include <iostream>
#include <fstream>
#include <windows.h>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Friend
{
    int id = 0;
    string firstName = "", lastName = "", phoneNumber = "", address = "", email = "";
};

void downloadDataFromFile(vector<Friend> &friends)
{
    string line;
    int numberOfLine = 1;
    Friend templateFriend;

    fstream file;
    file.open("KsiazkaAdresowa.txt", ios::in);

    if(file.good() == true)
    {
        while (getline(file,line,'|'))
        {
            switch (numberOfLine)
            {
            case 1:
                templateFriend.id = atoi(line.c_str());
                break;
            case 2:
                templateFriend.firstName = line;
                break;
            case 3:
                templateFriend.lastName = line;
                break;
            case 4:
                templateFriend.phoneNumber = line;
                break;
            case 5:
                templateFriend.email = line;
                break;
            case 6:
                templateFriend.address = line;
                break;
            }
            if (numberOfLine >= 6)
            {
                friends.push_back(templateFriend);
                numberOfLine = 1;
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
        cout << "Nie udalo sie wczytac pliku!" << endl;
        system("pause");
    }
}

void addFriend(vector<Friend> &friends)
{
    Friend templateFriend;

    system("cls");

    cin.ignore();
    cout << "Podaj imie: ";
    getline(cin, templateFriend.firstName, '\n');
    cout << "Podaj nazwisko: ";
    getline(cin, templateFriend.lastName, '\n');
    cout << "Podaj numer telefonu: ";
    getline(cin, templateFriend.phoneNumber, '\n');
    cout << "Podaj email: ";
    getline(cin, templateFriend.email, '\n');
    cout << "Podaj adres: ";
    getline(cin, templateFriend.address, '\n');

    if(friends.size() == 0)
    {
        templateFriend.id = 1;
    }
    else
    {
        templateFriend.id = friends[friends.size()-1].id + 1;
    }

    friends.push_back(templateFriend);

    fstream file;
    file.open("KsiazkaAdresowa.txt", ios::app);

    if(file.good() == true)
    {
        file << templateFriend.id << "|";
        file << templateFriend.firstName << "|";
        file << templateFriend.lastName << "|";
        file << templateFriend.phoneNumber << "|";
        file << templateFriend.email << "|";
        file << templateFriend.address << "|"  << endl;

        file.close();

        cout << "Dodano adresata." << endl;
    }
    else
    {
        cout << "Nie udalo sie zapisac adresata!" << endl;
    }

    Sleep(1500);
}

void displayAllFriendsDetails(vector<Friend> friends)
{
    system("cls");

    if(friends.size() > 0)
    {
        for(int i = 0; i<friends.size(); i++)
        {
            cout << "Id:                " << friends[i].id << endl;
            cout << "Imie:              " << friends[i].firstName << endl;
            cout << "Nazwisko:          " << friends[i].lastName << endl;
            cout << "Numer telefonu:    " << friends[i].phoneNumber << endl;
            cout << "Email:             " << friends[i].email << endl;
            cout << "Adres:             " << friends[i].address  << endl << endl;
        }
    }
    else
        cout << "Nie dodano jeszcze przyjaciol do ksiazki adresowej!" << endl;

    system("pause");
}


void searchAfterTheFirstName(vector<Friend> friends)
{
    int numberFound = 0;
    string searchedName;

    system("cls");

    cout << "Podaj imie adresata: ";
    cin >> searchedName;
    cout << endl;

    for(int i = 0; i < friends.size(); i++)
    {
        if(friends[i].firstName == searchedName)
        {
            cout << "Id: " << friends[i].id << endl;
            cout << "Imie: " << friends[i].firstName << endl;
            cout << "Nazwisko: " << friends[i].lastName << endl;
            cout << "Numer telefonu: " << friends[i].phoneNumber << endl;
            cout << "Email: " << friends[i].email << endl;
            cout << "Adres: " << friends[i].address  << endl << endl;
            numberFound++;
        }
    }

    cout << "Liczba znalezionych przyjaciol o danym imieniu: " << numberFound << endl;
    system("pause");
}

void searchAfterTheLastName(vector<Friend> friends)
{
    int numberFound = 0;
    string searchedName;

    system("cls");

    cout << "Podaj nazwisko adresata: ";
    cin >> searchedName;
    cout << endl;

    for(int i = 0; i < friends.size(); i++)
    {
        if(friends[i].lastName == searchedName)
        {
            cout << "Id: " << friends[i].id << endl;
            cout << "Imie: " << friends[i].firstName << endl;
            cout << "Nazwisko: " << friends[i].lastName << endl;
            cout << "Numer telefonu: " << friends[i].phoneNumber << endl;
            cout << "Email: " << friends[i].email << endl;
            cout << "Adres: " << friends[i].address  << endl << endl;
            numberFound++;
        }
    }
    cout << "Liczba znalezionych przyjaciol o danym nazwisku: " << numberFound << endl;
    system("pause");
}

void overwriteFile(vector<Friend> &friends)
{
    fstream file;
    file.open( "KsiazkaAdresowa.txt", ios::out | ios::trunc );

    if(file.good() == true)
    {
        for(int i = 0; i < friends.size(); i++)
        {
            file << friends[i].id << "|";
            file << friends[i].firstName << "|";
            file << friends[i].lastName << "|";
            file << friends[i].phoneNumber << "|";
            file << friends[i].email << "|";
            file << friends[i].address << "|"  << endl;
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

void deleteFriend(vector<Friend> &friends)
{
    int idAddressee;
    char choice;
    bool ifThereIsAddressee = false;

    system("cls");
    cout << "Podaj id adresata: ";
    cin >> idAddressee;

    for(int i = 0; i < friends.size(); i++)
    {
        if(friends[i].id == idAddressee)
        {
            while(true)
            {
                system("cls");
                cout << "Czy na pewno chcesz usunac " << friends[i].firstName << " " << friends[i].lastName << "? (t/n)" << endl;

                cin >> choice;

                if(choice == 't')
                {
                    ifThereIsAddressee = true;
                    friends.erase(friends.begin()+i);
                    overwriteFile(friends);
                    break;
                }
                else if(choice == 'n')
                {
                    break;
                }
            }
            break;
        }
    }
    if(ifThereIsAddressee == false)
    {
        cout << "Podany adresat nie istnieje!" << endl;
        system("pause");
    }

}

void editInformationAboutFriend(vector<Friend> &friends, int idAddressee, int typeOfData)
{
    string newdata;
    bool ifThereIsAddressee = false;

    system("cls");
    cout << "Zmien na: ";
    cin.ignore();
    getline(cin, newdata);

    for(int i = 0; i < friends.size(); i++)
    {
        if(friends[i].id == idAddressee)
        {
            ifThereIsAddressee = true;
            switch(typeOfData)
            {
            case 1:
                friends[i].firstName = newdata;
                break;
            case 2:
                friends[i].lastName = newdata;
                break;
            case 3:
                friends[i].phoneNumber = newdata;
                break;
            case 4:
                friends[i].email = newdata;
                break;
            case 5:
                friends[i].address = newdata;
                break;
            }
            overwriteFile(friends);
            break;
        }
    }
    if(ifThereIsAddressee == false)
    {
        cout << "Podany adresat nie istnieje!" << endl;
        system("pause");
    }
}

void editFriends(vector<Friend> &friends)
{
    char choice;
    int idAddressee;

    if(!friends.empty())
    {
        system("cls");
        cout << "Podaj id adresata: ";
        cin >> idAddressee;

        while(true)
        {
            system("cls");
            cout << "Edytuj dane:" << endl << endl;
            cout << "1. Imie" << endl;
            cout << "2. Nazwisko" << endl;
            cout << "3. Numer telefonu" << endl;
            cout << "4. Email" << endl;
            cout << "5. Adres" << endl;
            cout << "6. Powrot do menu" << endl;
            cout << endl << "Twoj wybor: " << endl;
            cin >> choice;

            if(choice == '1')
            {
                editInformationAboutFriend(friends, idAddressee, 1);
            }
            else if (choice == '2')
            {
                editInformationAboutFriend(friends, idAddressee, 2);
            }
            else if (choice == '3')
            {
                editInformationAboutFriend(friends, idAddressee, 3);
            }
            else if (choice == '4')
            {
                editInformationAboutFriend(friends, idAddressee, 4);
            }
            else if (choice == '5')
            {
                editInformationAboutFriend(friends, idAddressee, 5);
            }
            else if (choice == '6')
            {
                break;
            }
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta." << endl << endl;
    }
}

int main()
{
    vector<Friend> friends;
    char choice;

    downloadDataFromFile(friends);

    while(1)
    {
        system("cls");
        cout << "--- KSIAZKA ADRESOWA ---" << endl << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl;
        cout << endl << "Twoj wybor: " << endl;
        cin >> choice;

        switch (choice)
        {
        case '1':
            addFriend(friends);
            break;
        case '2':
            searchAfterTheFirstName(friends);
            break;
        case '3':
            searchAfterTheLastName(friends);
            break;
        case '4':
            displayAllFriendsDetails(friends);
            break;
        case '5':
            deleteFriend(friends);
            break;
        case '6':
            editFriends(friends);
            break;
        case '9':
            exit(0);
        }
    }
    return 0;
}
