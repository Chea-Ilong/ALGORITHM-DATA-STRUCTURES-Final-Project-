#include "calulate_postfix.h"
#include "converter.h"
#include "prefix.h"
using namespace std;

void menu_postfix()
{
    Calculate_postfix calulate;

    int choice;
    do
    {
        cout << endl
             << endl
             << "Welcome to Postfix Evaluation\n";
        cout << "Choose an option: \n"
             << "1. Evaluate postfix expression\n"
             << "2. View all expressions\n"
             << "3. Update an expression\n"
             << "4. Delete an expression\n"
             << "5. Exit\n";
        cin >> choice;
        cin.ignore();
        system("cls");
        switch (choice)
        {
        case 1:
        {
            string expression;
            int count = 0;
            char option;

            while (count < 3)
            {
                cout << "Enter a postfix expression to calculate (e.g., '23 4 + 5 *'): ";
                getline(cin, expression);

                if (!calulate.validate_postfix(expression))
                {
                    calulate.store_invalid_expression(expression);
                    count++;
                    if (count == 3)
                    {
                        cout << "Too many invalid expressions entered!" << endl;
                        cout << "Would you like help understanding postfix expressions?" << endl;
                        cout << "Press 'y' for yes or 'n' for no: ";
                        cin >> option;
                        cin.ignore();

                        if (option == 'y' || option == 'Y')
                        {

                            cout << "Postfix Notation Help:" << endl;
                            cout << "--------------------------" << endl;

                            cout << "1. Parentheses:" << endl;
                            cout << "   - Infix: Uses parentheses to show operation order (e.g., (3 + 4) * 5)." << endl;
                            cout << "   - Postfix: No parentheses needed; order is clear from position (e.g., 3 4 + 5 *)." << endl;

                            cout << "2. Operator Precedence:" << endl;
                            cout << "   - Infix: Operators follow rules (e.g., multiplication before addition)." << endl;
                            cout << "   - Postfix: Order is determined by position, no need for precedence rules." << endl;

                            cout << "3. Evaluation:" << endl;
                            cout << "   - Infix: Needs extra steps to handle parentheses and operator order." << endl;
                            cout << "   - Postfix: Simply processed left to right with a stack." << endl;

                            count = 0;
                            continue;
                        }
                        else
                        {
                            cout << "Alright, feel free to ask for help anytime!" << endl;
                            break;
                        }
                    }
                }
                else
                {
                    double result = calulate.evaluate_postfix(expression);
                    if (isnan(result))
                    {

                        calulate.store_invalid_expression(expression);
                    }
                    else
                    {

                        cout << "Result: " << result << endl;
                        calulate.store_valid_expression(expression, result);
                    }
                    break;
                }
            }
        }
        break;
        case 2:
            calulate.display_valid_expression();
            break;
        case 3:
        {
            string old_expression;
            string new_expression;

            calulate.display_valid_expression();
            cout << "Enter the equation you want to update (ex: 1 1 + = 2): ";
            getline(cin, old_expression);
            cout << "Enter the new expression (ex: 1 1 + ): ";
            getline(cin, new_expression);
            calulate.update_expression(old_expression, new_expression);
        }
        break;
        case 4:
        {
            string old_expression;
            calulate.display_valid_expression();
            cout << "Enter the equation you want to delete (ex: 1 1 + = 2): ";
            getline(cin, old_expression);
            calulate.delete_expression(old_expression);
            break;
        }
        case 5:
            cout << "Returning to Main Menu..." << endl;
            return;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (1);
}
void menu_prefix()
{
    PrefixEvaluation prefix;
    prefix.run();
}
void menu_conversion()
{
    Expression_Conversion convert;
    convert.menu_conversion();
}
void menu()
{
    int choice;

    // Display menu options to the user
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

        // Switch based on user choice
        switch (choice)
        {
        case 1:
            system("cls");
            menu_conversion();
            break;
        case 2:
            system("cls");
            menu_prefix();
            break;
        case 3:
             system("cls");
            menu_postfix();
            break;
        case 0:
            cout << endl
                 << "Exiting the program";
            break;
        default:
            cout << "Invalid choice. Please select 1 or 2 or 3." << endl;
        }
    } while (choice != 0);
}