#include <iostream>
#include <cctype>
#include <cmath>
#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

class Node
{
public:
    double data;
    Node *next;

    Node(double newData)
    {
        data = newData;
        next = NULL;
    }
};

class Stack
{
    int size;
    Node *topNode;

public:
    Stack()
    {
        size = 0;
        topNode = NULL;
    }

    void push(double newData)
    {
        Node *a = new Node(newData);
        a->next = topNode;
        topNode = a;
        size++;
    }

    double pop()
    {
        if (size == 0)
        {
            cout << "Error: Stack underflow\n";
            return NAN;
        }
        else
        {
            Node *temp = topNode;
            double poppedData = topNode->data;
            topNode = topNode->next;
            delete temp;
            size--;
            return poppedData;
        }
    }

    double top()
    {
        if (size == 0)
        {
            cout << "Error: Stack is empty\n";
            return NAN;
        }
        else
        {
            return topNode->data;
        }
    }

    bool isEmpty()
    {
        return size == 0;
    }
};
class PrefixEvaluation
{

public:
    bool isValid(const string &expression)
    {
        int operandCount = 0; // To track the number of operands

        // Iterate over each character in the expression (from right to left)
        for (int i = expression.length() - 1; i >= 0; --i)
        {
            char ch = expression[i];

            // Skip spaces
            if (isspace(ch))
            {
                continue;
            }

            // If the character is a digit (operand) or a decimal number
            if (isdigit(ch) || (ch == '-' && i - 1 >= 0 && isdigit(expression[i - 1])))
            {
                // Handle negative number, if '-' is followed by a digit, treat it as part of the number
                if (ch == '-' && (i - 1 >= 0 && isdigit(expression[i - 1])))
                {
                    --i; // Skip the negative sign as part of the number
                }

                // We need to handle the full number, including negative and decimal numbers
                while (i - 1 >= 0 && (isdigit(expression[i - 1]) || expression[i - 1] == '.'))
                {
                    --i;
                }

                // An operand is found, increment the count
                operandCount++;
            }
            // Handle operators
            else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^')
            {
                // Ensure there are at least two operands before an operator
                if (operandCount < 2)
                {
                    cout << "Error: Not enough operands for operator '" << ch << "'!" << endl;
                    return false;
                }

                // After the operator, reduce the operand count by 1 (as the operator consumes two operands)
                operandCount--;
            }
            else
            {
                // Invalid character
                cout << "Error: Invalid character '" << ch << "' in the expression!" << endl;
                return false;
            }
        }

        // At the end, there must be exactly one operand left in the stack (the result)
        if (operandCount != 1)
        {
            cout << "Error: Invalid prefix expression - unbalanced operands/operators!" << endl;
            return false;
        }

        return true;
    }
    void storeValidExpression(const string &expression, double result)
    {
        if (result == NAN)
        {
            cout << "Error: Invalid result; cannot store the expression." << endl;
            return;
        }

        ofstream file("prefix_valid_expressions.csv", ios::app);
        if (file.is_open())
        {
            file << expression << "," << fixed << setprecision(2) << result << "\n";
            file.close();
        }
        else
        {
            cout << "Error: Unable to open prefix_valid_expressions.csv for writing." << endl;
        }
    }

    void storeInvalidExpression(const string &expression)
    {
        ofstream file("prefix_invalid_expressions.csv", ios::app);
        if (file.is_open())
        {
            file << expression << ",Invalid\n";
            file.close();
        }
        else
        {
            cout << "Error: Unable to open prefix_invalid_expressions.csv for writing." << endl;
        }
    }

    void deleteEvaluation(const string &filename, const string &expressionToDelete)
    {
        ifstream inputFile(filename);
        vector<string> lines;
        bool deleted = false;

        if (inputFile.is_open())
        {
            string line;
            while (getline(inputFile, line))
            {
                // Check if the line starts with the expression to delete
                if (line.substr(0, line.find(',')) != expressionToDelete)
                {
                    lines.push_back(line); // Keep lines that don't match
                }
                else
                {
                    deleted = true; // Mark as deleted if found
                }
            }
            inputFile.close();
        }
        else
        {
            cout << "Error: Unable to open " << filename << " for reading." << endl;
            return;
        }

        // Write back the filtered lines to the file
        ofstream outputFile(filename, ios::trunc);
        if (outputFile.is_open())
        {
            for (const auto &line : lines)
            {
                outputFile << line << "\n";
            }
            outputFile.close();
            if (deleted)
            {
                cout << "Expression deleted successfully from " << filename << "." << endl;
            }
            else
            {
                cout << "Expression not found in " << filename << "." << endl;
            }
        }
        else
        {
            cout << "Error: Unable to open " << filename << " for writing." << endl;
        }
    }

    void updateEvaluation(const string &filename, const string &oldExpression, const string &newExpression, double result)
    {
        ifstream inputFile(filename);
        vector<string> lines;
        bool updated = false;

        if (inputFile.is_open())
        {
            string line;
            while (getline(inputFile, line))
            {
                if (line.substr(0, line.find(',')) == oldExpression && !updated)
                {
                    if (filename == "prefix_valid_expressions.csv")
                    {
                        if (!isValid(newExpression))
                        {
                            cout << "New expression is invalid; cannot update valid evaluations." << endl;
                            inputFile.close();
                            return;
                        }
                        lines.push_back(newExpression + "," + to_string(result));
                    }
                    else
                    {
                        lines.push_back(newExpression + ",Invalid");
                    }
                    updated = true;
                }
                else
                {
                    lines.push_back(line);
                }
            }
            inputFile.close();
        }
        else
        {
            cout << "Error: Unable to open " << filename << " for reading." << endl;
            return;
        }

        ofstream outputFile(filename, ios::trunc);
        if (outputFile.is_open())
        {
            for (const auto &line : lines)
            {
                outputFile << line << "\n";
            }
            outputFile.close();
            if (updated)
            {
                cout << "Evaluation updated successfully in " << filename << "." << endl;
            }
            else
            {
                cout << "Expression not found in " << filename << "." << endl;
            }
        }
        else
        {
            cout << "Error: Unable to open " << filename << " for writing." << endl;
        }
    }

    void displayEvaluations(const string &filename)
    {
        ifstream file(filename);
        if (file.is_open())
        {
            if (file.peek() == ifstream::traits_type::eof())
            {
                cout << "No evaluations found in " << filename << "." << endl;
                return;
            }

            string line;
            cout << "\nContents of " << filename << ":\n";
            cout << "Expression, Result\n";
            while (getline(file, line))
            {
                cout << line << endl;
            }
            file.close();
        }
        else
        {
            cout << "Error: Unable to open " << filename << " for reading." << endl;
        }
    }

    double prefixEvaluation(const string &prefixExpression)
    {
        Stack opStack;

        for (int i = prefixExpression.length() - 1; i >= 0; i--)
        {
            if (isdigit(prefixExpression[i]))
            {
                double num = 0;
                double placeValue = 1;

                while (i >= 0 && isdigit(prefixExpression[i]))
                {
                    num = (prefixExpression[i] - '0') * placeValue + num;
                    placeValue *= 10;
                    i--;
                }
                i++;
                opStack.push(num);
            }
            else if (isspace(prefixExpression[i]))
            {
                continue;
            }
            else
            {
                if (opStack.isEmpty())
                {
                    cout << "Error: Insufficient operands for operator " << prefixExpression[i] << endl;
                    return NAN;
                }
                double op2 = opStack.pop();

                if (opStack.isEmpty())
                {
                    cout << "Error: Insufficient operands for operator " << prefixExpression[i] << endl;
                    return NAN;
                }
                double op1 = opStack.pop();

                switch (prefixExpression[i])
                {
                case '+':
                    opStack.push(op2 + op1);
                    break;
                case '-':
                    opStack.push(op2 - op1);
                    break;
                case '*':
                    opStack.push(op2 * op1);
                    break;
                case '/':
                    if (op1 == 0 && op2 == 0)
                    {
                        cout << "0 divided by 0, returning 0" << endl;
                        return 0; // Return 0 when both operands are zero
                    }
                    else if (op1 == 0)
                    {
                        cout << "Can't divide by 0" << endl;
                        return NAN;
                    }
                    break;
                case '^':
                    opStack.push(pow(op2, op1));
                    break;
                default:
                    cout << "Error: Unknown operator " << prefixExpression[i] << endl;
                    return NAN;
                }
            }
        }
        return opStack.top();
    }

    void run()
    {
        int choice;
        do
        {
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
            cout << "*      " << BOLD << YELLOW << "WELCOME TO PREFIX EVALUATION" << RESET << CYAN << "      *" << endl;
            cout << "*                                        *" << endl;
            cout << "******************************************" << RESET << endl
                 << endl;

            // Menu Title
            cout << BOLD << YELLOW << "Please select an option from the menu below:" << RESET << endl
                 << endl;

            // Menu Options with Color
            cout << GREEN << "  1. Evaluate the Expression" << RESET << endl;
            cout << GREEN << "  2. Display Evaluations" << RESET << endl;
            cout << GREEN << "  3. Delete an Evaluation" << RESET << endl;
            cout << GREEN << "  4. Update an Evaluation" << RESET << endl;
            cout << RED << "  5. Exit" << RESET << endl
                 << endl;

            // Input Prompt
            cout << BOLD << CYAN << "Enter your choice: " << RESET;

            cin >> choice;
            cin.ignore();

            switch (choice)
            {
            case 1:
            {
                string prefixExpression;
                cout << "Enter a prefix expression (ex: + 1 1): ";
                getline(cin, prefixExpression);

                if (isValid(prefixExpression))
                {
                    double result = prefixEvaluation(prefixExpression);
                    if (result != NAN)
                    {
                        cout << "The result of the prefix expression is: " << result << endl;
                        storeValidExpression(prefixExpression, result);
                        cout << "\nPress any key to continue..." << endl;
                        getchar();
                        system("cls");
                    }
                }
                else
                {
                    cout << "The prefix expression is invalid." << endl;
                    storeInvalidExpression(prefixExpression);
                }
                break;
            }
            case 2:
            {
                cout << "Display valid expression:  ";
                displayEvaluations("prefix_valid_expressions.csv");
                cout << "\nPress any key to continue..." << endl;
                getchar();
                system("cls");
                // char type;
                // cout << "Display (v)alid, (i)nvalid, or (a)ll evaluations? ";

                // cin >> type;
                // cin.ignore();

                // if (type == 'v' || type == 'V')
                // {
                //     displayEvaluations("prefix_valid_expressions.csv");
                // }
                // else if (type == 'i' || type == 'I')
                // {
                //     displayEvaluations("prefix_invalid_expressions.csv");
                // }
                // else if (type == 'a' || type == 'A')
                // {
                //     cout << "\nDisplaying valid evaluations:" << endl;
                //     displayEvaluations("prefix_valid_expressions.csv");
                //     cout << "\nDisplaying invalid evaluations:" << endl;
                //     displayEvaluations("prefix_invalid_expressions.csv");
                // }
                // else
                // {
                //     cout << "Invalid choice." << endl;
                // }
                break;
            }
            case 3:
            {

                // char type;
                // cout << "Delete from (v)alid or (i)nvalid expressions? ";
                // cin >> type;
                // cin.ignore();

                // string filename;
                // if (type == 'v' || type == 'V')
                // {
                //     filename = "prefix_valid_expressions.csv";
                //     cout << "\nValid evaluations:\n";
                //     displayEvaluations(filename);
                // }
                // else if (type == 'i' || type == 'I')
                // {
                //     filename = "prefix_invalid_expressions.csv";
                //     cout << "\nInvalid evaluations:\n";
                //     displayEvaluations(filename);
                // }
                // else
                // {
                //     cout << "Invalid choice." << endl;
                //     break;
                // }

                cout << "Display valid expression:  ";
                displayEvaluations("prefix_valid_expressions.csv");

                string filename = "prefix_valid_expressions.csv";
                string expressionToDelete;
                cout << "\nEnter the expression to delete ( ex: + 1 1): ";
                getline(cin, expressionToDelete);

                deleteEvaluation(filename, expressionToDelete);
                cout << "\nPress any key to continue..." << endl;
                getchar();
                system("cls");
                break;
            }

            case 4:
            {

                // char type;
                // string filename;
                // cout << "Update (v)alid or (i)nvalid expressions? ";
                // cin >> type;
                // cin.ignore();

                // if (type == 'v' || type == 'V')
                // {
                //     filename = "prefix_valid_expressions.csv";
                //     cout << "\nValid evaluations:\n";
                //     displayEvaluations(filename);
                //     string oldExpression, newExpression;
                //     cout << "Enter the expression to update: ";
                //     getline(cin, oldExpression);
                //     cout << "Enter the new expression: ";
                //     getline(cin, newExpression);

                //     if (isValid(newExpression))
                //     {
                //         double result = prefixEvaluation(newExpression);
                //         if (result != NAN)
                //         {
                //             updateEvaluation("prefix_valid_expressions.csv", oldExpression, newExpression, result);
                //         }
                //     }
                //     else
                //     {
                //         cout << "The new prefix expression is invalid." << endl;
                //         updateEvaluation("prefix_invalid_expressions.csv", oldExpression, newExpression, NAN);
                //     }
                // }
                // else if (type == 'i' || type == 'I')
                // {
                //     string oldExpression, newExpression;
                //     filename = "prefix_invalid_expressions.csv";
                //     cout << "\nInvalid evaluations:\n";
                //     displayEvaluations(filename);
                //     cout << "Enter the expression to update: ";
                //     getline(cin, oldExpression);
                //     cout << "Enter the new expression: ";
                //     getline(cin, newExpression);

                //     updateEvaluation("prefix_invalid_expressions.csv", oldExpression, newExpression, NAN);
                // }
                // else
                // {
                //     cout << "Invalid choice." << endl;
                // }

                string filename = "prefix_valid_expressions.csv";

                cout << "\nValid evaluations:\n";
                displayEvaluations(filename);

                string oldExpression, newExpression;
                cout << "Enter the expression to update (ex: + 1 1): ";
                getline(cin, oldExpression);
                cout << "Enter the new expression (ex: + 2 2): ";
                getline(cin, newExpression);

                // Validate the new expression
                if (isValid(newExpression))
                {
                    double result = prefixEvaluation(newExpression);
                    if (result != NAN)
                    {
                        updateEvaluation(filename, oldExpression, newExpression, result);
                        cout << "Expression updated successfully in valid expressions file." << endl;
                        cout << "\nPress any key to continue..." << endl;
                        getchar();
                        system("cls");
                    }
                    else
                    {
                        cout << "Error: Could not evaluate the new expression." << endl;
                    }
                }
                else
                {
                    cout << "The new prefix expression is invalid. No changes were made." << endl;
                }

                break;
            }
            case 5:
            {
                cout << "Exiting the program." << endl;
                break;
            }
            default:
            {
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
            }
        } while (choice != 5);
    }
};
