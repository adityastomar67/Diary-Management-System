#include <iostream>
#include <iomanip>
#include <ctime>
#include <stdlib.h>
#include <fstream>
#include <cstring>
// #include <bits/stdc++.h>
// #include <sys/stat.h>
// #include <sys/types.h>
#include <direct.h>
// #include <stdio.h>

using namespace std;

string id, pass, t;

class record
{
    string title;
    string note;

public:
    void addrecord();
    void viewrecord();
    void editrecord();
    void deleterecord();
};

void output(int choice)
{
    switch (choice)
    {
    case 1:
        system("cls");
        cout << setw(119) << "**********************************************************" << endl
             << setw(119) << "*                                                        *" << endl
             << setw(119) << "*                                                        *" << endl
             << setw(119) << "*                                                        *" << endl
             << setw(119) << "*                    [1]LOGIN                            *" << endl
             << setw(119) << "*                    [2]REGISTER                         *" << endl
             << setw(119) << "*                                                        *" << endl
             << setw(119) << "*                                                        *" << endl
             << setw(119) << "*                                                        *" << endl
             << setw(119) << "**********************************************************" << endl;
        cout << endl
             << endl
             << setw(98) << "Enter Your Choice :";
        break;
    case 2:
        system("cls");
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
bool is_file_exist(string fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}
bool login()
{
    // string id, pass;
    bool check = false;
    cout << "Enter your Username :";
    cin >> id;
    cout << "Enter your Password :";
    cin >> pass;
    string content;
    if (is_file_exist("database/" + id + "/__PASS.txt"))
    {
        ifstream file;
        file.open("database/" + id + "/__PASS.txt");
        getline(file, content);
        if (content == pass)
            check = true;
        else
            check = false;
    }
    else
    {
        check = false;
    }
    return check;
}
void reg()
{
    cout << "Enter your Username :";
    cin >> id;
    cout << "Enter your Password :";
    cin >> pass;

    ofstream file;
    const char *c = ("database/" + id).c_str();
    mkdir(c);

    file.open("database/" + id + "/__PASS.txt");
    file << pass;
    file.close();
}
void time()
{
    time_t tt;
    struct tm *ti;
    time(&tt);
    ti = localtime(&tt);
    t = asctime(ti);
}
void editpassword()
{
    string currentPass;
    cout << "Enter Current Password: ";
    cin >> currentPass;
    if (currentPass == pass)
    {
        ofstream file;
        file.open("database/" + id + "/__PASS.txt", std::ofstream::out | std::ofstream::trunc);
        cout << "Enter New Password: ";
        cin >> currentPass;
        file << currentPass;
        file.close();
    }
}
void choices()
{
    time();
    int choice;
    output(2);
    cin >> choice;
    record file;
    switch (choice)
    {
    case 1:
        file.addrecord();
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
}

void record::addrecord()
{
    bool paraChange = false;

    system("cls");

    ofstream file;

    cout << "Enter the title" << endl;
    cin.ignore();
    getline(cin, title);

    file.open("database/" + id + "/" + title + ".txt");
    // cout << time << endl;
    file << t;
    file << endl;

    cout << "Enter the note \n==>To stop typing -  \":END\"\n==>To put a para change - \":PC\"\n==>To put a new line\":N\"" << endl;
    while (true)
    {
        note = "";
        getline(cin, note);
        if (note == ":END")
            break;
        else if (note == ":PC")
        {
            note = "\n\t";
            paraChange = true;
        }
        else if (note == ":N")
        {
            note = "\n"
        }

        file << note;
        if (!paraChange)
        {
            file << endl;
            paraChange = false;
        }
    }

    file.close();
}
void record::viewrecord()
{
    system("cls");
    string title;
    string content;
    ifstream file;
    cout << "Enter the Title :";
    cin >> title;
    cout << endl;
    file.open("database/" + id + "/" + title + ".txt");

    system("cls");
    while (!file.eof())
    {
        getline(file, content);
        cout << content;
        cout << endl;
    }
    cout << "\n\nPress 1 for Main Menu\n";
    cin >> content;
    if (content == "1")
        choices();
}
void record::editrecord()
{
    bool paraChange = false;
    system("cls");
    string title, content, content2;
    ifstream file;

    cout << "Enter the Title :";
    cin >> title;
    if (is_file_exist("database/" + id + "/" + title + ".txt"))
    {
        file.open("database/" + id + "/" + title + ".txt", ios::app);
        system("cls");
        while (!file.eof())
        {
            getline(file, content);
            cout << content;
            cout << endl;
        }

        file.close();
        ofstream file;
        file.open("database/" + id + "/" + title + ".txt", ios::app);

        // file.open(titleString + ".txt");

        cout << endl;
        cout << "Enter the note \n==>To stop typing -  \"-END-\"\n==>To put a para change - \"-PC-\"" << endl;
        while (true)
        {
            note = "";
            getline(cin, note);
            if (note == "-END-")
                break;
            else if (note == "-PC-")
            {
                note = "\n\t";
                paraChange = true;
            }
            file << note;
            if (!paraChange)
            {
                file << endl;
                paraChange = false;
            }
        }
        file.close();
    }
}
void record::deleterecord()
{
    char file[100];
    char ext[] = {'.', 't', 'x', 't', '\0'};
    cout << "Enter file name :";
    cin >> file;
    strcat(file, ext);
    if (remove(file) != 0)
        perror("Error deleting file");
    else
        puts("File successfully deleted");
}
