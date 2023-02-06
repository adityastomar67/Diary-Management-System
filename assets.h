#include <iostream>
#include <iomanip>
#include <ctime>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <cstdlib>
// #include <bits/stdc++.h>
// #include <sys/stat.h>
// #include <sys/types.h>
/* #include <direct.h> */
// #include <stdio.h>

using namespace std;
string ID, PASS, TIME;

void create_directory(string dirname){
    #ifdef WINDOWS
        string command = "mkdir " + dirname;
        system(command.c_str());
    #else
        // Assume POSIX
        string command = "mkdir -p " + dirname;
        system(command.c_str());
    #endif
}
void clear_screen()
{
    #ifdef WINDOWS
        std::system("cls");
    #else
        // Assume POSIX
        std::system ("clear");
    #endif
}
bool is_file_exist(string fileName)
{
    ifstream infile(fileName);
    return infile.good();
}

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

void output(int choice){
    switch (choice)
    {
    case 1:
        clear_screen();
        cout << setw(119) << "**********************************************************" << endl
             << setw(119) << "*                                                        *" << endl
             << setw(119) << "*                                                        *" << endl
             << setw(119) << "*                                                        *" << endl
             << setw(119) << "*                    [1] LOGIN                           *" << endl
             << setw(119) << "*                    [2] REGISTER                        *" << endl
             << setw(119) << "*                    [3] EXIT                            *" << endl
             << setw(119) << "*                                                        *" << endl
             << setw(119) << "*                                                        *" << endl
             << setw(119) << "*                                                        *" << endl
             << setw(119) << "**********************************************************" << endl;
        cout << endl
             << endl
             << setw(98) << "Enter Your Choice :";
        break;
    case 2:
        clear_screen();
        cout << setw(99) << "WELCOME TO YOUR PERSONAL DIARY" << endl << setw(98) << endl << setw(98) << endl
             << setw(97) << "What would you like to do?" << endl << setw(98) << endl
             << setw(98) << "Add Record               [1]" << endl
             << setw(98) << "View Record              [2]" << endl
             << setw(98) << "Edit Record              [3]" << endl
             << setw(98) << "Delete Record            [4]" << endl
             << setw(98) << "Edit Password            [5]" << endl
             << setw(98) << "Exit                     [6]" << endl;
        break;
    }
}
bool login() {
    string userPass;
    cout << "Enter your Username :";
    cin >> ID;
    if (is_file_exist("database/" + ID + "/__PASS.txt")) {
        cout << "Enter your Password :";
        cin >> PASS;
        ifstream file;
        file.open("database/" + ID + "/__PASS.txt");
        getline(file, userPass);
        if (userPass == PASS)
            return true;
        else
            cout << "Wrong Pass!";
            return false;
    }
    else {
        cout << "User doesn't exists!";
        return false;
    }
}
void reg() {
    cout << "Enter your Username :";
    cin >> ID;
    if (!is_file_exist("database/" + ID + "/__PASS.txt")) {
        create_directory("database/" + ID);
        cout << "Enter your Password :";
        cin >> PASS;
        ofstream file;
        file.open("database/" + ID + "/__PASS.txt");
        file << PASS;
        file.close();
    }
    else{
        cout << "Username already exists" << endl;
        reg();
    }
}
void time() {
    time_t tt;
    struct tm *ti;
    time(&tt);
    ti = localtime(&tt);
    TIME = asctime(ti);
}
void editpassword() {
    clear_screen();
    string curPass;
    cout << "Enter Current Password: ";
    cin >> curPass;
    if (curPass == PASS)
    {
        ofstream file;
        file.open("database/" + ID + "/__PASS.txt", std::ofstream::out | std::ofstream::trunc);
        cout << "Enter New Password: ";
        cin >> curPass;
        file << curPass;
        file.close();
        cout << "Password Changed Successfully!" << endl;
    }
    else {
        cout << "Wrong Password Given!" << endl;
    }
}
void choices() {
    time();
    int choice;
    output(2);
    cin >> choice;
    record file;
    switch (choice) {
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
    default:
        cout << "Invalid Choice"<<endl;
        choices();
        break;
    }
}

void record::addrecord(){
    clear_screen();
    ofstream file;
    cout << "Enter the title" << endl;
    cin.ignore();
    getline(cin, title);
    file.open("database/" + ID + "/" + title + ".txt");
    file << TIME;
    file << endl;
    cout << "Enter the note (When done typing, type \"-END-\" at the end." << endl;

    while (true){
        note = "";
        cin >> note;
        if (note == "-END-")
            break;
        file << note;
        file << endl;
    }
    file.close();
}
void record::viewrecord(){
    clear_screen();
    string titleString, content;
    ifstream file;
    cout << "Enter the Title :";
    cin >> titleString;
    cout << endl;
    file.open("database/" + ID + "/" + titleString + ".txt");

    clear_screen();
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
    clear_screen();
    string titleString, content, content2, extension = ".txt";
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
