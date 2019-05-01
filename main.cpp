#include <iostream>
#include <fstream>
#include <windows.h>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

string loadLine()
{
    string input = "";
    getline(cin, input);
    return input;
}

struct User
{
    int id = 0;
    string name = "", password = "";
};

void overwriteFileUsers(vector<User> &users)
{
    fstream file;
    file.open( "Uzytkownicy.txt", ios::out | ios::trunc );

    if(file.good() == true)
    {
        for(int i=0; i<users.size(); i++)
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

void registration(vector<User> &users)
{
    string name, password;
    User templateUser;

    cout << "Podaj nazwe uzytkownika: " << endl;
    cin >> name;

    int i = 0;
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

    fstream file;
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

int login(vector<User> &users)
{
    string name, password;
    int numberOfLine = 1;

    cout << "Podaj login: ";
    cin >> name;

    for(int i = 0; i < users.size(); i++)
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

void passwordChange(vector<User> &users, int idLoggedInUser)
{
    string password;
    cout << "Podaj nowe haslo: ";
    cin >> password;


    for(int i=0; i<users.size(); i++)
    {
        if(users[i].id == idLoggedInUser)
        {
            users[i].password = password;
        }
    }

    overwriteFileUsers(users);
}

string changeFirstLetterToUpperAndRestToLower(string text)
{
    if (!text.empty())
    {
        transform(text.begin(), text.end(), text.begin(), ::tolower);
        text[0] = toupper(text[0]);
    }
    return text;
}

void downloadDataOfUsersFromFile(vector<User> &users)
{
    string line;
    int numberOfLine = 1;
    User templateUser;

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

struct Recipient
{
    int idRecipient = 0, idUser = 0;
    string firstName = "", lastName = "", phoneNumber = "", email = "", address = "";
};

vector<Recipient> downloadDataOfRecipientsFromFile(int &idLoggedInUser, int &idLastRecipient)
{
    vector<Recipient> recipients;
    string line;
    int numberOfLine = 1;
    Recipient templateRecipient;

    fstream file;
    file.open("Adresaci.txt", ios::in);

    if(file.good() == true)
    {
        while (getline(file,line,'|'))
        {
            switch (numberOfLine)
            {
            case 1:
                templateRecipient.idRecipient = atoi(line.c_str());
                break;
            case 2:
                templateRecipient.idUser = atoi(line.c_str());
                break;
            case 3:
                templateRecipient.firstName = line;
                break;
            case 4:
                templateRecipient.lastName = line;
                break;
            case 5:
                templateRecipient.phoneNumber = line;
                break;
            case 6:
                templateRecipient.email = line;
                break;
            case 7:
                templateRecipient.address = line;
                break;
            }

            if (numberOfLine >= 7)
            {
                numberOfLine = 1;
                idLastRecipient = templateRecipient.idRecipient;
                if(templateRecipient.idUser == idLoggedInUser)
                    recipients.push_back(templateRecipient);
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

    return recipients;
}

int addRecipient(vector<Recipient> &recipients, int idLoggedInUser, int idLastRecipient)
{
    Recipient templateRecipient;

    system("cls");

    cin.ignore();
    cout << "Podaj imie: ";
    templateRecipient.firstName = loadLine();
    templateRecipient.firstName = changeFirstLetterToUpperAndRestToLower(templateRecipient.firstName);
    cout << "Podaj nazwisko: ";
    templateRecipient.lastName = loadLine();
    templateRecipient.lastName = changeFirstLetterToUpperAndRestToLower(templateRecipient.lastName);
    cout << "Podaj numer telefonu: ";
    templateRecipient.phoneNumber = loadLine();
    cout << "Podaj email: ";
    templateRecipient.email = loadLine();
    cout << "Podaj adres: ";
    templateRecipient.address = loadLine();

    templateRecipient.idUser = idLoggedInUser;

    templateRecipient.idRecipient = idLastRecipient + 1;

    recipients.push_back(templateRecipient);

    fstream file;
    file.open("Adresaci.txt", ios::app);

    if(file.good() == true)
    {
        file << templateRecipient.idRecipient << "|";
        file << templateRecipient.idUser << "|";
        file << templateRecipient.firstName << "|";
        file << templateRecipient.lastName << "|";
        file << templateRecipient.phoneNumber << "|";
        file << templateRecipient.email << "|";
        file << templateRecipient.address << "|"  << endl;

        file.close();

        idLastRecipient++;

        cout << "Dodano adresata." << endl;
    }
    else
    {
        cout << "Nie udalo sie zapisac adresata!" << endl;
    }

    Sleep(1500);

    return idLastRecipient;
}

void displayAllRecipientsDetails(vector<Recipient> recipients)
{
    system("cls");

    if(recipients.size() > 0)
    {
        int i = 0;
        while(i<recipients.size())
        {
            cout << "Id:                " << recipients[i].idRecipient << endl;
            cout << "Imie:              " << recipients[i].firstName << endl;
            cout << "Nazwisko:          " << recipients[i].lastName << endl;
            cout << "Numer telefonu:    " << recipients[i].phoneNumber << endl;
            cout << "Email:             " << recipients[i].email << endl;
            cout << "Adres:             " << recipients[i].address  << endl << endl;
            i++;
        }
    }
    else
        cout << "Nie dodano jeszcze przyjaciol do ksiazki adresowej!" << endl;

    system("pause");
}

void searchAfterTheFirstName(vector<Recipient> recipients)
{
    int numberFound = 0;
    string searchedName;

    system("cls");

    cout << "Podaj imie adresata: ";
    cin >> searchedName;
    cout << endl;

    for(int i = 0; i < recipients.size(); i++)
    {
        if(recipients[i].firstName == searchedName)
        {
            cout << "Id: " << recipients[i].idRecipient << endl;
            cout << "Imie: " << recipients[i].firstName << endl;
            cout << "Nazwisko: " << recipients[i].lastName << endl;
            cout << "Numer telefonu: " << recipients[i].phoneNumber << endl;
            cout << "Email: " << recipients[i].email << endl;
            cout << "Adres: " << recipients[i].address  << endl << endl;
            numberFound++;
        }
    }

    cout << "Liczba znalezionych adresatow o danym imieniu: " << numberFound << endl;
    system("pause");
}

void searchAfterTheLastName(vector<Recipient> recipients)
{
    int numberFound = 0;
    string searchedName;

    system("cls");

    cout << "Podaj nazwisko adresata: ";
    cin >> searchedName;
    cout << endl;

    for(int i = 0; i < recipients.size(); i++)
    {
        if(recipients[i].lastName == searchedName)
        {
            cout << "Id: " << recipients[i].idRecipient << endl;
            cout << "Imie: " << recipients[i].firstName << endl;
            cout << "Nazwisko: " << recipients[i].lastName << endl;
            cout << "Numer telefonu: " << recipients[i].phoneNumber << endl;
            cout << "Email: " << recipients[i].email << endl;
            cout << "Adres: " << recipients[i].address  << endl << endl;
            numberFound++;
        }
    }
    cout << "Liczba znalezionych adresatow o danym nazwisku: " << numberFound << endl;
    system("pause");
}

void rewriteDataOfRecipientsWithoutDeleted(vector<Recipient> &recipients, int idEraseRecipient)
{
    string line;
    int numberOfLine = 1;
    Recipient templateRecipient;

    fstream fileSource;
    fileSource.open("Adresaci.txt", ios::in);

    fstream fileTarget;
    fileTarget.open("Adresaci_tymczasowy.txt", ios::out | ios::app);

    if(fileSource.good() == true)
    {
        while (getline(fileSource,line,'|'))
        {
            switch (numberOfLine)
            {
            case 1:
                templateRecipient.idRecipient = atoi(line.c_str());
                break;
            case 2:
                templateRecipient.idUser = atoi(line.c_str());
                break;
            case 3:
                templateRecipient.firstName = line;
                break;
            case 4:
                templateRecipient.lastName = line;
                break;
            case 5:
                templateRecipient.phoneNumber = line;
                break;
            case 6:
                templateRecipient.email = line;
                break;
            case 7:
                templateRecipient.address = line;
                break;
            }
            if (numberOfLine >= 7)
            {
                numberOfLine = 1;

                if(templateRecipient.idRecipient != idEraseRecipient)
                {
                    fileTarget << templateRecipient.idRecipient << "|";
                    fileTarget << templateRecipient.idUser << "|";
                    fileTarget << templateRecipient.firstName << "|";
                    fileTarget << templateRecipient.lastName << "|";
                    fileTarget << templateRecipient.phoneNumber << "|";
                    fileTarget << templateRecipient.email << "|";
                    fileTarget << templateRecipient.address << "|" << endl;
                }
            }
            else
            {
                numberOfLine++;
            }
        }
        fileTarget.close();
        fileSource.close();
        remove("Adresaci.txt");
        rename("Adresaci_tymczasowy.txt", "Adresaci.txt");
    }
    else
    {
        cout << "Nie udalo sie wczytac pliku zrodlowego!" << endl;
        system("pause");
    }
}

void deleteRecipient(vector<Recipient> &recipients)
{
    int idRecipient;
    char choice;
    bool ifThereIsRecipient = false;

    system("cls");
    cout << "Podaj id adresata: ";
    cin >> idRecipient;

    for(int i = 0; i < recipients.size(); i++)
    {
        if(recipients[i].idRecipient == idRecipient)
        {
            while(true)
            {
                system("cls");
                cout << "Czy na pewno chcesz usunac " << recipients[i].firstName << " " << recipients[i].lastName << "? (t/n)" << endl;

                cin >> choice;

                if(choice == 't')
                {
                    ifThereIsRecipient = true;
                    recipients.erase(recipients.begin()+i);
                    rewriteDataOfRecipientsWithoutDeleted(recipients, idRecipient);
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
    if(ifThereIsRecipient == false)
    {
        cout << "Podany adresat nie istnieje!" << endl;
        system("pause");
    }

}

void rewriteDataOfRecipientsWithEdited(vector<Recipient> &recipients, Recipient editedRecipient)
{
    string line;
    int numberOfLine = 1;
    Recipient templateRecipient;

    fstream fileSource;
    fileSource.open("Adresaci.txt", ios::in);

    fstream fileTarget;
    fileTarget.open("Adresaci_tymczasowy.txt", ios::out | ios::app);

    if(fileSource.good() == true)
    {
        while (getline(fileSource,line,'|'))
        {
            switch (numberOfLine)
            {
            case 1:
                templateRecipient.idRecipient = atoi(line.c_str());
                break;
            case 2:
                templateRecipient.idUser = atoi(line.c_str());
                break;
            case 3:
                templateRecipient.firstName = line;
                break;
            case 4:
                templateRecipient.lastName = line;
                break;
            case 5:
                templateRecipient.phoneNumber = line;
                break;
            case 6:
                templateRecipient.email = line;
                break;
            case 7:
                templateRecipient.address = line;
                break;
            }
            if (numberOfLine >= 7)
            {
                numberOfLine = 1;

                if(templateRecipient.idRecipient != editedRecipient.idRecipient)
                {
                    fileTarget << templateRecipient.idRecipient << "|";
                    fileTarget << templateRecipient.idUser << "|";
                    fileTarget << templateRecipient.firstName << "|";
                    fileTarget << templateRecipient.lastName << "|";
                    fileTarget << templateRecipient.phoneNumber << "|";
                    fileTarget << templateRecipient.email << "|";
                    fileTarget << templateRecipient.address << "|" << endl;
                }
                else
                {
                    fileTarget << editedRecipient.idRecipient << "|";
                    fileTarget << editedRecipient.idUser << "|";
                    fileTarget << editedRecipient.firstName << "|";
                    fileTarget << editedRecipient.lastName << "|";
                    fileTarget << editedRecipient.phoneNumber << "|";
                    fileTarget << editedRecipient.email << "|";
                    fileTarget << editedRecipient.address << "|" << endl;
                }
            }
            else
            {
                numberOfLine++;
            }
        }
        fileTarget.close();
        fileSource.close();
        remove("Adresaci.txt");
        rename("Adresaci_tymczasowy.txt", "Adresaci.txt");
    }
    else
    {
        cout << "Nie udalo sie wczytac pliku zrodlowego!" << endl;
        system("pause");
    }
}

void editInformationAboutRecipient(vector<Recipient> &recipients, int idRecipient, int typeOfData)
{
    string newdata;
    bool ifThereIsRecipient = false;

    system("cls");
    cout << "Zmien na: ";
    cin.ignore();
    getline(cin, newdata);

    for(int i = 0; i < recipients.size(); i++)
    {
        if(recipients[i].idRecipient == idRecipient)
        {
            ifThereIsRecipient = true;

            switch(typeOfData)
            {
            case 1:
                recipients[i].firstName = newdata;
                break;
            case 2:
                recipients[i].lastName = newdata;
                break;
            case 3:
                recipients[i].phoneNumber = newdata;
                break;
            case 4:
                recipients[i].email = newdata;
                break;
            case 5:
                recipients[i].address = newdata;
                break;
            }
            rewriteDataOfRecipientsWithEdited(recipients, recipients[i]);
            break;
        }
    }

    if(ifThereIsRecipient == false)
    {
        cout << "Podany adresat nie istnieje!" << endl;
        system("pause");
    }
}

void editRecipients(vector<Recipient> &recipients)
{
    char choice;
    int idRecipient;

    if(!recipients.empty())
    {
        system("cls");
        cout << "Podaj id adresata: ";
        cin >> idRecipient;

        while(true)
        {
            system("cls");
            cout << "Edytuj dane:" << endl << endl;
            cout << "1. Imie" << endl;
            cout << "2. Nazwisko" << endl;
            cout << "3. Numer telefonu" << endl;
            cout << "4. Email" << endl;
            cout << "5. Adres" << endl;
            cout << "9. Powrot do menu" << endl;
            cout << endl << "Twoj wybor: " << endl;
            cin >> choice;

            if(choice == '1')
            {
                editInformationAboutRecipient(recipients, idRecipient, 1);
            }
            else if (choice == '2')
            {
                editInformationAboutRecipient(recipients, idRecipient, 2);
            }
            else if (choice == '3')
            {
                editInformationAboutRecipient(recipients, idRecipient, 3);
            }
            else if (choice == '4')
            {
                editInformationAboutRecipient(recipients, idRecipient, 4);
            }
            else if (choice == '5')
            {
                editInformationAboutRecipient(recipients, idRecipient, 5);
            }
            else if (choice == '9')
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
    int idLoggedInUser = 0;
    vector<User> users;
    vector<Recipient> recipients;
    char choice;
    bool recipientsDownloaded = false;
    int idLastRecipient = 0;

    downloadDataOfUsersFromFile(users);

    while(1)
    {
        if(idLoggedInUser == 0)
        {
            recipientsDownloaded = false;
            system("cls");
            cout << "--- MENU GLOWNE ---" << endl << endl;
            cout << "1. Logowanie" << endl;
            cout << "2. Rejestracja" << endl;
            cout << "9. Zamknij program" << endl;
            cin >> choice;

            switch (choice)
            {
            case '1':
                idLoggedInUser = login(users);
                break;
            case '2':
                registration(users);
                break;
            case '9':
                exit(0);
                break;
            default:
                cout << endl << "Nie ma takiej opcji w menu." << endl << endl;
                system("pause");
                break;
            }
        }
        else
        {

            if(recipientsDownloaded == false)
            {
                recipients = downloadDataOfRecipientsFromFile(idLoggedInUser, idLastRecipient);
                recipientsDownloaded = true;
            }

            system("cls");
            cout << "--- MENU UZYTKOWNIKA ---" << endl << endl;
            cout << "1. Dodaj adresata" << endl;
            cout << "2. Wyszukaj po imieniu" << endl;
            cout << "3. Wyszukaj po nazwisku" << endl;
            cout << "4. Wyswietl wszystkich adresatow" << endl;
            cout << "5. Usun adresata" << endl;
            cout << "6. Edytuj adresata" << endl;
            cout << "--------------------" << endl;
            cout << "8. Zmiana hasla" << endl;
            cout << "9. Wylogowanie" << endl;
            cin >> choice;

            switch (choice)
            {
            case '1':
                idLastRecipient = addRecipient(recipients, idLoggedInUser, idLastRecipient);
                break;
            case '2':
                searchAfterTheFirstName(recipients);
                break;
            case '3':
                searchAfterTheLastName(recipients);
                break;
            case '4':
                displayAllRecipientsDetails(recipients);
                break;
            case '5':
                deleteRecipient(recipients);
                break;
            case '6':
                editRecipients(recipients);
                break;
            case '8':
                passwordChange(users, idLoggedInUser);
                break;
            case '9':
                idLoggedInUser = 0;
                break;
            }
        }
    }

    return 0;
}
