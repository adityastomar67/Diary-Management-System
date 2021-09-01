#include <iostream>
#include <cstring>
#include <fstream>

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
        cout << "Success";
        return true;
    }
}

string reg()
{
    string id, pass;
    cout << "Enter your Username :";
    cin >> id;
    cout << "Enter your Password :";
    cin >> pass;

    ofstream file;
    file.open("database/" + id + ".txt");
    file << pass;
    file.close();
}

// int main()
// {
//     login("new", "pass");
//     reg();
// }