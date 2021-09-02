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
        {
            output(2);
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
                // editpassword();
                break;
            case 6:
                exit(0);
                break;
            }
            return 0;
        }
        break;
    case 2:
        reg();
        main();

    default:
        break;
    }
}
