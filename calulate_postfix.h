#include <string>
#include <iostream>
#include <cctype>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <limits>
using namespace std;

struct Node_1
{
    double value;
    Node_1 *next;
};

class stack
{
private:
    int length;
    Node_1 *top;

public:
    stack()
    {
        top = nullptr;
        length = 0;
    }

    ~stack()
    {
        while (!isEmpty())
        {
            pop();
        }
    }
    void push(double newValue)
    {
        Node_1 *newNode = new Node_1;
        newNode->value = newValue;
        newNode->next = top;
        top = newNode;
        length++;
    }

    void pop()
    {
        if (length == 0)
        {
            cout << "Error: The stack is empty!" << endl;
        }
        else
        {
            Node_1 *temp = top;
            top = top->next;
            delete temp;
            length--;
        }
    }

    double peek()
    {
        if (length == 0)
        {
            cout << "Error: The stack is empty!" << endl;
            return NAN;
        }
        else
        {
            return top->value;
        }
    }

    bool isEmpty()
    {
        return (length == 0);
    }

    int size()
    {
        return length;
    }
};

class Calculate_postfix
{

public:
    bool validate_postfix(const string &expression)
    {
        int operandCount = 0;
        bool hasDigit = false;

        for (size_t i = 0; i < expression.length(); ++i)
        {
            char ch = expression[i];

            // First Check, if it is a number(negative and decimal and negative decimal)
            //  if it is a number || - a negative sign follow by a number
            // check if there is only one number

            if (isdigit(ch) || (ch == '-' && (i + 1 < expression.length() && isdigit(expression[i + 1]))))
            {

                hasDigit = true;

                if (ch == '-')
                    ++i;
                // already know it is a negative number
                // check the next index and if it is a number or decimal point
                // if not go to the previous index and skip past the space
                while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.'))
                {
                    ++i;
                }
                --i;
                ++operandCount;
            }
            else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^')
            {

                if (operandCount < 2)
                {
                    cout << "Error: Not enough operands for operator '" << ch << "'!" << endl;
                    return false;
                }

                --operandCount;
            }
            else if (!isspace(ch))
            {

                cout << "Error: Invalid character '" << ch << "' in the expression!" << endl;
                return false;
            }
        }

        if (!hasDigit)
        {
            cout << "Error: Expression must contain at least one number!" << endl;
            return false;
        }

        if (operandCount != 1)
        {
            cout << "Error: Invalid postfix expression - unbalanced operands/operators!" << endl;
            return false;
        }

        return true;
    }

    double evaluate_postfix(const string &expression)
    {
        stack stack;
        stringstream ss(expression);
        string token;

        while (ss >> token)
        {

            stringstream tokenStream(token);
            double number;

            if (tokenStream >> number && tokenStream.eof())
            {

                stack.push(number);
            }
            else if (token == "+" || token == "-" || token == "*" || token == "/" || token == "^")
            {

                double op2 = stack.peek();
                stack.pop();
                double op1 = stack.peek();
                stack.pop();
                double result;

                switch (token[0])
                {
                case '+':
                    result = op1 + op2;
                    break;
                case '-':
                    result = op1 - op2;
                    break;
                case '*':
                    result = op1 * op2;
                    break;
                case '^':
                    result = pow(op1, op2);
                    break;
                case '/':
                    if (op2 == 0)
                    {
                        cout << "Can't divide by 0" << endl;
                        return NAN;
                    }
                    result = op1 / op2;
                    break;
                default:
                    cout << "Error: Invalid operator!" << endl;
                }

                stack.push(result);
            }
        }

        if (stack.size() == 1)
        {

            return stack.peek();
        }
        else
        {
            cout << "Error: Invalid expression!" << endl;
            return NAN;
        }
    }

    void store_valid_expression(const string &expression, double result)
    {

        fstream out1file("expression_postfix.csv", ios::app);

        if (!out1file.is_open())
        {
            cout << "Error: file 1 Could not open the file!" << endl;
        }

        out1file << expression << " = " << result << endl;

        out1file.close();
    }
    void store_invalid_expression(const string &expression)
    {

        fstream out1file("invalid_postfix_expression.csv", ios::app);

        if (!out1file.is_open())
        {
            cout << "Error: file 1 Could not open the file!" << endl;
        }

        out1file << expression << endl;

        out1file.close();
    }
    void display_valid_expression()
    {
        ifstream infile("expression_postfix.csv", ios::in);

        if (!infile.is_open())
        {
            cout << "Error: file Could not open the file!" << endl;
        }
        string line;
        while (getline(infile, line))
        {

            cout << line << endl;
        }
        infile.close();
    }
    // void display_invalid_expression()
    // {
    //     ifstream infile("invalid_postfix_expression.csv", ios::in);

    //     if (!infile.is_open())
    //     {
    //         cout << "Error: file Could not open the file!" << endl;
    //     }
    //     string line;
    //     while (getline(infile, line))
    //     {

    //         cout << line << endl;
    //     }
    //     infile.close();
    // }

    void update_expression(const string &old_expression, const string &new_expression)
    {
        ifstream infile("expression_postfix.csv");
        ofstream outfile("expression_postfix_temp.csv");

        if (!infile.is_open())
        {
            cout << "Error: Could not open the input file!" << endl;
            return;
        }

        if (!outfile.is_open())
        {
            cout << "Error: Could not open the output file!" << endl;
            return;
        }

        string line, result;
        bool found = false;

        if (!validate_postfix(new_expression))
        {
            return;
        }

        double calculated_result = evaluate_postfix(new_expression);
        result = to_string(calculated_result);

        while (getline(infile, line))
        {

            string trimmed_line = line;
            trimmed_line.erase(0, trimmed_line.find_first_not_of(" \n\r\t")); // Left trim
            trimmed_line.erase(trimmed_line.find_last_not_of(" \n\r\t") + 1); // Right trim

            // If the expression matches the one to update, modify it
            if (trimmed_line == old_expression)
            {
                line = new_expression + " = " + result;
                found = true;
            }

            outfile << line << endl;
        }

        if (!found)
        {
            cout << "Error: Expression not found in the file!" << endl;
        }

        infile.close();
        outfile.close();

        if (found)
        {
            remove("expression_postfix.csv");
            rename("expression_postfix_temp.csv",
                   "expression_postfix.csv");
            cout << "Expression updated successfully!" << endl;
        }
        else
        {
            remove("expression_postfix_temp.csv");
        }
    }

    void delete_expression(const string &expression_to_delete)
    {
        ifstream infile("expression_postfix.csv");
        ofstream outfile("expression_postfix_temp.csv");

        if (!infile.is_open())
        {
            cout << "Error: Could not open the input file!" << endl;
            return;
        }

        if (!outfile.is_open())
        {
            cout << "Error: Could not open the output file!" << endl;
            return;
        }

        string line;
        bool found = false;

        while (getline(infile, line))
        {
            // Trim whitespace from the entire line (left and right)
            string trimmed_line = line;
            trimmed_line.erase(0, trimmed_line.find_first_not_of(" \n\r\t")); // Left trim
            trimmed_line.erase(trimmed_line.find_last_not_of(" \n\r\t") + 1); // Right trim

            if (trimmed_line == expression_to_delete)
            {
                found = true;

                continue;
            }

            outfile << line << endl;
        }

        infile.close();
        outfile.close();

        if (found)
        {
            remove("expression_postfix.csv");
            rename("expression_postfix_temp.csv",
                   "expression_postfix.csv");
            cout << "Expression deleted successfully!" << endl;
        }
        else
        {
            cout << "Error: Expression not found in the file!" << endl;
            remove("expression_postfix_temp.csv");
        }
    }

    // void remove_postfix_expression()
    // {
    //     string old_expression;

    //     display_valid_expression();
    //     cout << "Enter the equation you want to delete (ex: 1 1 + = 2): ";
    //     getline(cin, old_expression);
    //     delete_expression(old_expression);
    //     // display_valid_expression();
    // }
    // void update_postfix_expression()
    // {
    //     string old_expression;
    //     string new_expression;

    //     display_valid_expression();
    //     cout << "Enter the equation you want to update (ex: 1 1 + = 2): ";
    //     getline(cin, old_expression);
    //     cout << "Enter the new expression (ex: 1 1 + ): ";
    //     getline(cin, new_expression);
    //     update_expression(old_expression, new_expression);

    // }
    // void help()
    // {
    //     cout << "Postfix Notation Help:" << endl;
    //     cout << "--------------------------" << endl;

    //     cout << "1. Parentheses:" << endl;
    //     cout << "   - Infix: Uses parentheses to show operation order (e.g., (3 + 4) * 5)." << endl;
    //     cout << "   - Postfix: No parentheses needed; order is clear from position (e.g., 3 4 + 5 *)." << endl;

    //     cout << "2. Operator Precedence:" << endl;
    //     cout << "   - Infix: Operators follow rules (e.g., multiplication before addition)." << endl;
    //     cout << "   - Postfix: Order is determined by position, no need for precedence rules." << endl;

    //     cout << "3. Evaluation:" << endl;
    //     cout << "   - Infix: Needs extra steps to handle parentheses and operator order." << endl;
    //     cout << "   - Postfix: Simply processed left to right with a stack." << endl;
    // }

    void menu()
    {
        int choice;
        do
        {

            cout << "******************************************" << endl;
            cout << "*                                        *" << endl;
            cout << "*      WELCOME TO POSTFIX EVALUATION     *" << endl;
            cout << "*                                        *" << endl;
            cout << "******************************************" << endl
                 << endl;

            cout << "Please choose an option from the menu below:" << endl
                 << endl;

            cout << "  1. Evaluate Postfix Expression" << endl;
            cout << "  2. View All Expressions" << endl;
            cout << "  3. Update an Expression" << endl;
            cout << "  4. Delete an Expression" << endl;
            cout << "  5. Exit" << endl
                 << endl;
            cout << "Enter your choice: ";
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

                    if (!validate_postfix(expression))
                    {
                        store_invalid_expression(expression);
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
                                     system("cls");

                                break;
                            }
                        }
                    }
                    else
                    {
                        double result = evaluate_postfix(expression);
                        if (isnan(result))
                        {

                            store_invalid_expression(expression);
                        }
                        else
                        {

                            cout << "Result: " << result << endl;
                            store_valid_expression(expression, result);
                            cout << "\nPress any key to continue..." << endl;
                            getchar();
                            system("cls");
                        }
                        break;
                    }
                }
            }
            break;
            case 2:
            {

                display_valid_expression();
                cout << "\nPress any key to continue..." << endl;
                getchar();
                system("cls");
            }
            break;
            case 3:
            {
                string old_expression;
                string new_expression;

                display_valid_expression();
                cout << "Enter the equation you want to update (ex: 1 1 + = 2): ";
                getline(cin, old_expression);
                cout << "Enter the new expression (ex: 1 1 + ): ";
                getline(cin, new_expression);
                update_expression(old_expression, new_expression);
                cout << "\nPress any key to continue..." << endl;
                getchar();
                system("cls");
            }
            break;
            case 4:
            {
                string old_expression;
                display_valid_expression();
                cout << "Enter the equation you want to delete (ex: 1 1 + = 2): ";
                getline(cin, old_expression);
                delete_expression(old_expression);

                cout << "\nPress any key to continue..." << endl;
                getchar();
                system("cls");
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
};
// void postfix()
// {
//     string expression;
//     int count = 0;
//     char option;

//     while (count < 3)
//     {
//         cout << "Enter a postfix expression to calculate (e.g., '23 4 + 5 *'): ";
//         getline(cin, expression);

//         if (!validate_postfix(expression))
//         {
//             store_invalid_expression(expression);
//             count++;
//             if (count == 3)
//             {
//                 cout << "Too many invalid expressions entered!" << endl;
//                 cout << "Would you like help understanding postfix expressions?" << endl;
//                 cout << "Press 'y' for yes or 'n' for no: ";
//                 cin >> option;
//                 cin.ignore();

//                 if (option == 'y' || option == 'Y')
//                 {
//                     help();
//                     count = 0;
//                     continue;
//                 }
//                 else
//                 {
//                     cout << "Alright, feel free to ask for help anytime!" << endl;
//                     break;
//                 }
//             }
//         }
//         else
//         {
//             double result = evaluate_postfix(expression);
//             if (isnan(result))
//             {

//                 store_invalid_expression(expression);
//             }
//             else
//             {

//                 cout << "Result: " << result << endl;
//                 store_valid_expression(expression, result);
//             }
//             break;
//         }
//     }
// }
// };
