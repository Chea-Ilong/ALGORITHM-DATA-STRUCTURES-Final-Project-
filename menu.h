#include "calulate_postfix.h"
#include "converter.h"
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

void menu_conversion()
{
    Expression_Conversion convert;

    int choice;
    do
    {

        cout << endl
             << endl
             << "Welcome to Expression conversion";
        cout << endl
             << endl
             << "1. Input Infix Expression";
        cout << endl
             << "2. Update ";
        cout << endl
             << "3. Update in File";
        cout << endl
             << "4. Read from file";
        cout << endl
             << "5. Delete in File";
        cout << endl
             << "6. Convert to Postfix Expression";
        cout << endl
             << "7. Convert to Prefix Expression";
        cout << endl
             << "8. Save to file";
        cout << endl
             << "9. Exit";
        cout << endl
             << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        system("cls");
        cout << endl;
        switch (choice)
        {
        case 1:
            
            convert.input_infix();
            break;
        case 2:
            convert.update();
            break;
        case 3:
            int line;
            convert.read_from_file();
            cout << endl
                 << "Enter the line you want to update: ";
            cin >> line;
            cin.ignore();
            convert.update_to_file(line);
            break;
        case 4:
            convert.read_from_file();
            break;
        case 5:
            int line_delete;
            convert.read_from_file();
            cout << endl
                 << "Enter the line you want to delete: ";
            cin >> line_delete;
            convert.delete_from_file(line_delete);
            break;
        case 6:
            cout << endl
                 << "The postfix expression is: " << convert.convert_to_postfix();
            break;
        case 7:
            cout << endl
                 << "The prefix expression is: " << convert.convert_to_prefix();
            break;
        case 8:
            convert.save_to_file();
            cout << endl
                 << "The expression and its conversions have been saved successfully to [" << "valid_file_name" << "]";
            break;
        case 9:
            cout << "Returning to Main Menu..." << endl;
            return;
        default:
            cout << endl
                 << "Invalid choice";
        }
    } while (choice != 9);
}
void menu()
{
    int choice;

    // Display menu options to the user
    do
    {
        cout << "Select an option:" << endl;
        cout << "1.  Convert Menu" << endl;
        cout << "2. Postfix Menu" << endl;
        cout << "3. Exit" << endl;

        // Read user input
        cout << "Enter your choice (1 or 2): ";
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
            menu_postfix();
            break;
        case 3:
            cout << endl
                 << "Exiting the program";
            break;

        default:
            cout << "Invalid choice. Please select 1 or 2." << endl;
            break;
        }

    } while (choice != 3);
}