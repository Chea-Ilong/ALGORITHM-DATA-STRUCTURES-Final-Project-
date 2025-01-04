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
        const string RESET = "\033[0m";
        const string RED = "\033[31m";
        const string GREEN = "\033[32m";
        const string YELLOW = "\033[33m";
        const string CYAN = "\033[36m";
        const string BOLD = "\033[1m";

        // Header with Colorful Formatting
        cout << CYAN;
        cout << "******************************************" << endl;
        cout << "*                                        *" << endl;
        cout << "*               " << BOLD << YELLOW << "WELCOME" << RESET << CYAN << "                  *" << endl;
        cout << "*                  " << BOLD << YELLOW << "TO" << RESET << CYAN << "                    *" << endl;
        cout << "*         " << BOLD << GREEN << "EXPRESSION EVALUATION" << RESET << CYAN << "          *" << endl;
        cout << "*             " << BOLD << GREEN << "AND CONVERSION" << RESET << CYAN << "             *" << endl;
        cout << "*                                        *" << endl;
        cout << "******************************************" << RESET << endl
             << endl;

        // Menu Title
        cout << BOLD << YELLOW << "Choose an option from the menu below:" << RESET << endl
             << endl;

        // Menu Options with Color
        cout << GREEN << "  1. Explore the Conversion Menu" << RESET << endl;
        cout << GREEN << "  2. Dive into the Prefix Menu" << RESET << endl;
        cout << GREEN << "  3. Navigate the Postfix Menu" << RESET << endl;
        cout << RED << "  4. Exit the Program (Goodbye!)" << RESET << endl
             << endl;

        // Wait for user input
        cout << BOLD << CYAN << "Enter your choice: " << RESET;
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