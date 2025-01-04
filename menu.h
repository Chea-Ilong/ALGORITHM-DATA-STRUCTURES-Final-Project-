#include "calulate_postfix.h"
#include "converter.h"
#include "prefix.h"
using namespace std;

void menu()
{
    int choice;

    do
    {
        system("cls");
        cout << "Select an option:" << endl;
        cout << "1. Convert Menu" << endl;
        cout << "2. Prefix Menu" << endl;
        cout << "3. Postfix Menu" << endl;
        cout << "0. Exit" << endl;

        // Read user input
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            system("cls");
            Expression_Conversion convert;
            convert.menu_conversion();
            break;
        }
        case 2:
        {
            system("cls");
            PrefixEvaluation prefix;
            prefix.run();
            break;
        }
        case 3:
        {
            system("cls");
            Calculate_postfix postfix;
            postfix.menu();
            break;
        }
        case 0:
            cout << endl
                 << "Exiting the program";
            break;
        default:
            cout << "Invalid choice. Please select 1 or 2 or 3." << endl;
        }
    } while (choice != 0);
}