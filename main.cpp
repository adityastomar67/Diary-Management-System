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
#include "assets.h"

int main()
{
    int choice;
    output(1);
    cin >> choice;
    switch (choice)
    {
    case 1:
        if (login())
            choices();
        break;
    case 2:
        reg();
        main();
    case 3:
        exit(0);
        break;
    default:
        cout << "Invalid Choice"<< endl;
        main();
    }
    return 0;
}
