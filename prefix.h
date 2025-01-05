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
        int operandCount = 0;
        int operatorCount = 0;

        for (int i = expression.length() - 1; i >= 0; i--)
        {
            if (isdigit(expression[i]) || expression[i] == '.')
            {
                // Parse a number with optional decimal point
                while (i >= 0 && (isdigit(expression[i]) || expression[i] == '.'))
                    i--;
                if (i >= 0 && expression[i] == '-') // Handle negative numbers
                    i--;
                i++;
                operandCount++;
            }
            else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/' || expression[i] == '^')
            {
                operatorCount++;
                if (operatorCount >= operandCount)
                    return false;
            }
            else if (!isspace(expression[i]))
            {
                return false; // Invalid character
            }
        }
        return operandCount == operatorCount + 1;
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
            if (isdigit(prefixExpression[i]) || prefixExpression[i] == '.')
            {
                string numberStr = "";

                // Collect the digits and decimal point
                while (i >= 0 && (isdigit(prefixExpression[i]) || prefixExpression[i] == '.'))
                {
                    numberStr = prefixExpression[i] + numberStr; // Add to the front
                    i--;
                }
                i++; // Adjust index after the inner loop

                // Check if there is a negative sign before the number
                if (i > 0 && prefixExpression[i - 1] == '-')
                {
                    if (i == 1 || !isdigit(prefixExpression[i - 2])) // Ensure it's a negative sign, not a subtraction operator
                    {
                        numberStr = '-' + numberStr;
                        i--; // Skip the negative sign
                    }
                }

                // Convert the string to a double
                double num = stod(numberStr);
                opStack.push(num);
            }
            else if (isspace(prefixExpression[i]))
            {
                continue; // Skip spaces
            }
            else
            {
                if (opStack.isEmpty())
                {
                    cout << "Error: Insufficient operands for operator " << prefixExpression[i] << endl;
                    return -1;
                }
                double op2 = opStack.pop();

                if (opStack.isEmpty())
                {
                    cout << "Error: Insufficient operands for operator " << prefixExpression[i] << endl;
                    return -1;
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
                    if (op1 == 0)
                    {
                        cout << "Error: Division by zero" << endl;
                        return -1;
                    }
                    opStack.push(op2 / op1);
                    break;
                case '^':
                    opStack.push(pow(op2, op1));
                    break;
                default:
                    cout << "Error: Unknown operator " << prefixExpression[i] << endl;
                    return -1;
                }
            }
        }
        return opStack.top();

    }
        void prefix(){
               string expression;
                int count = 0;
                char option;

                while (count < 3)
                {
                    cout << "Enter a prefix expression to calculate (ex: '+ 1 1'): ";
                    getline(cin, expression);

                    if (!isValid(expression)) // Validate the prefix expression
                    {
                        storeInvalidExpression(expression); // Store invalid expression
                        count++;
                        if (count == 3)
                        {
                            cout << "Too many invalid expressions entered!" << endl;
                            cout << "Would you like help understanding prefix expressions?" << endl;
                            cout << "Press 'y' for yes or 'n' for no: ";
                            cin >> option;
                            cin.ignore();

                            if (option == 'y' || option == 'Y')
                            {
                                cout << "Prefix Notation Help:" << endl;
                                cout << "--------------------------" << endl;

                                cout << "1. Order of Operations:" << endl;
                                cout << "   - Prefix: Operators come before operands (ex: '+ 1 2')." << endl;
                                cout << "   - This avoids the need for parentheses or operator precedence rules." << endl;

                                cout << "2. Evaluation:" << endl;
                                cout << "   - Prefix expressions are processed from right to left using a stack." << endl;

                                cout << "3. Example:" << endl;
                                cout << "   - Prefix: '+ 3 * 4 5' evaluates to 23 (3 + (4 * 5))." << endl;

                                count = 0; // Reset invalid count after help
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
                        double result = prefixEvaluation(expression); // Evaluate the prefix expression
                        if (isnan(result))
                        {
                            storeInvalidExpression(expression); // Store invalid if evaluation fails
                        }
                        else
                        {
                            cout << "Result: " << result << endl;
                            storeValidExpression(expression, result); // Store valid expression with result
                            cout << "\nPress any key to continue..." << endl;
                            getchar();
                            system("cls");
                        }
                        break;
                    }
                }
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
            // case 1:
            // {
            //     string prefixExpression;
            //     cout << "Enter a prefix expression (ex: + 1 1): ";
            //     getline(cin, prefixExpression);

            //     if (isValid(prefixExpression))
            //     {
            //         double result = prefixEvaluation(prefixExpression);
            //         if (result != NAN)
            //         {
            //             cout << "The result of the prefix expression is: " << result << endl;
            //             storeValidExpression(prefixExpression, result);
            //             cout << "\nPress any key to continue..." << endl;
            //             getchar();
            //             system("cls");
            //         }
            //     }
            //     else
            //     {
            //         cout << "The prefix expression is invalid." << endl;
            //         storeInvalidExpression(prefixExpression);
            //     }
            //     break;
            case 1:
            {
             
              prefix();
                  break;
            }

            case 2:
            {
                cout << "Display valid expression:  ";
                displayEvaluations("prefix_valid_expressions.csv");
                cout << "\nPress any key to continue..." << endl;
                getchar();
                system("cls");

                break;
            }
            case 3:
            {

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
