/* 
    This projects contains the following functions:
        password()      � contains/manages/handles password protection
        addrecord()     � to add new diary record
        viewrecord()    � to view added record in list
        editrecord()    � to modify and update an added record
        editpassword()  � to modify/change a password
        deleterecord()  � to delete or remove a record permanently from system file

    Author - Aditya Singh Tomar
*/
#include <iostream>
#include <iomanip>
#include <ctime>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include "login.h"

using namespace std;
string PASS;

void output(int);
void editpassword();
bool password();
string time();

class record
{
    // string date, day, time;
    string title;
    string note;

public:
    void addrecord(string);
    void viewrecord();
    void editrecord();
    void deleterecord();
};

int main()
{
    if (login())
    {
        output(2);
        int choice;
        cin >> choice;
        record file;
        string t = time();
        switch (choice)
        {
        case 1:
            file.addrecord(t);
            break;
        case 2:
            file.viewrecord();
            break;
        case 3:
            file.editrecord();
            break;
        case 4:
            file.deleterecord();
            break;
        case 5:
            editpassword();
            break;
        case 6:
            exit(0);
            break;
        }
        return 0;
    }
}

void record::addrecord(string time)
{
    system("clear");

    ofstream file;

    cout << "Enter the title" << endl;
    cin.ignore();
    getline(cin, title);

    file.open(title + ".txt");

    file << time;
    file << endl;

    cout << "Enter the note" << endl;
    getline(cin, note);
    file << note;

    file.close();
}
void record::viewrecord()
{
    system("clear");
    // int choice;
    string titleString;
    string content;
    ifstream file;
    cout << "Enter the Title :";
    cin >> titleString;
    cout << endl;
    file.open(titleString + ".txt");

    system("clear");
    while (!file.eof())
    {
        getline(file, content);
        cout << content;
        cout << endl;
    }
}
void record::editrecord()
{
    system("clear");
    string titleString;
    string content;
    string content2;
    string extension = ".txt";
    fstream file;

    cout << "Enter the Title :";
    cin >> titleString;
    titleString = titleString + extension;
    cout << endl;
    file.open(titleString, ios::app);

    // system("clear");
    // while (!file.eof())
    // {
    //     getline(file, content);
    //     cout << content;
    //     cout << endl;
    // }

    // file.close();
    // ofstream file;

    // file.open(titleString + ".txt");

    cout << "Enter the note" << endl;
    cin.ignore();
    getline(cin, content2);
    file << content2;
    file.close();
}
void record::deleterecord()
{
    char file[10];
    char ext[] = {'.', 't', 'x', 't', '\0'};
    cout << "Enter file name :";
    cin >> file;
    strcat(file, ext);
    if (remove(file) != 0)
        perror("Error deleting file");
    else
        puts("File successfully deleted");
}

void output(int choice)
{
    switch (choice)
    {
    case 1:
        system("clear");
        cout << setw(119) << "**********************************************************" << endl
             << setw(119) << "*                                                        *" << endl
             << setw(119) << "*                                                        *" << endl
             << setw(119) << "*                                                        *" << endl
             << setw(119) << "*                    [1]LOGIN                            *" << endl
             << setw(119) << "*                    [2]SET NEW PASSWORD                 *" << endl
             << setw(119) << "*                                                        *" << endl
             << setw(119) << "*                                                        *" << endl
             << setw(119) << "*                                                        *" << endl
             << setw(119) << "**********************************************************" << endl;
        cout << endl
             << endl
             << setw(98) << "Enter Your Choice :";
        break;
    case 2:
        system("clear");
        cout << setw(99) << "WELCOME TO YOUR PERSONAL DIARY" << endl
             << setw(98) << endl
             << setw(98) << endl
             << setw(97) << "What would you like to do?" << endl
             << setw(98) << endl
             << setw(98) << "Add Record               [1]" << endl
             << setw(98) << "View Record              [2]" << endl
             << setw(98) << "Edit Record              [3]" << endl
             << setw(98) << "Delete Record            [4]" << endl
             << setw(98) << "Edit Password            [5]" << endl
             << setw(98) << "Exit                     [6]" << endl;
        break;
    }
}
void editpassword()
{
    system("clear");
    string tempPass;
    string rPASS;
    ofstream wPass;
    ifstream rPass;
    rPass.open("Password.txt");
    rPass >> rPASS;
    rPass.close();
    cout << "NOTE : If Not Set any Password Earlier, then leave Empty!" << endl;
    cout << "Enter old Password :";
    cin >> tempPass;
    if (tempPass == rPASS)
    {
        system("clear");
        cout << endl
             << "Enter the New Password :";
        wPass.open("Password.txt");
        cin.ignore();
        getline(cin, PASS);

        wPass << PASS;
        wPass.close();
    }
    else
    {
        cout << "Wrong Password";
        exit(0);
    }
}
// bool password()
// {
//     ifstream Pass;
//     Pass.open("Password.txt");
//     Pass >> PASS;
//     Pass.close();

//     int choice;
//     output(1);
//     cin >> choice;
//     if (choice == 1)
//     {
//         cout << "Enter Password :";
//         string tempPass;
//         cin >> tempPass;
//         if (tempPass == PASS)
//         {
//             return true;
//         }
//         else
//         {
//             cout << "Wrong Password!";
//             return false;
//         }
//     }
//     else if (choice == 2)
//     {
//         editpassword();
//     }
// }
string time()
{
    time_t tt;
    struct tm *ti;
    time(&tt);
    ti = localtime(&tt);
    return asctime(ti);
}