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
        cout << "******************************************" << endl;
        cout << "*                                        *" << endl;
        cout << "*               WELCOME                  *" << endl;
        cout << "*                  TO                    *" << endl;
        cout << "*         EXPRESSION EVALUATION          *" << endl;
        cout << "*             AND CONVERSION             *" << endl;
        cout << "*                                        *" << endl;
        cout << "******************************************" << endl
             << endl;

        cout << "Choose an option from the menu below:" << endl
             << endl;

        cout << "  1. Explore the Conversion Menu" << endl;
        cout << "  2. Dive into the Prefix Menu" << endl;
        cout << "  3. Navigate the Postfix Menu" << endl;
        cout << "  4. Exit the Program (Goodbye!)" << endl
             << endl;

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
        case 4:
            cout << endl
            << "Exiting the program";
            break;
        default:
            cout << "Invalid choice. Please select 1 or 2 or 3." << endl;
        }
    } while (choice != 4);
}