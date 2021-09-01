#include <iostream>
#include <iomanip>
#include <ctime>
#include <stdlib.h>
#include <fstream>
#include <cstring>

using namespace std;

bool is_file_exist(string fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}
bool login()
{
    string id, pass;
    cout << "Enter your Username :";
    cin >> id;
    cout << "Enter your Password :";
    cin >> pass;
    string content;
    if (is_file_exist("database/" + id + ".txt"))
    {
        ifstream file;
        file.open("database/" + id + ".txt");
        getline(file, content);
    }
    else
    {
        return false;
    }
    if (content == pass)
    {
        // cout << "Success";
        return true;
    }
}
void reg()
{
    string id, pass;
    cout << "Enter your Username :";
    cin >> id;
    cout << "Enter your Password :";
    cin >> pass;

    ofstream file;
    file.open("database/" + id + "/__PASS.txt");
    file << pass;
    file.close();
}
string time()
{
    time_t tt;
    struct tm *ti;
    time(&tt);
    ti = localtime(&tt);
    return asctime(ti);
}