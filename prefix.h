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
            return -1;
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
            return -1;
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
            if (isdigit(expression[i]))
            {
                while (i >= 0 && isdigit(expression[i]))
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

    void storeValidExpression(const string &expression, int result)
    {
        if (result == -1)
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

    void updateEvaluation(const string &filename, const string &oldExpression, const string &newExpression, int result)
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

    int prefixEvaluation(const string &prefixExpression)
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
                cout << "Enter a prefix expression: ";
                getline(cin, prefixExpression);

                if (isValid(prefixExpression))
                {
                    int result = prefixEvaluation(prefixExpression);
                    if (result != -1)
                    {
                        cout << "The result of the prefix expression is: " << result << endl;
                        storeValidExpression(prefixExpression, result);
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
                char type;
                cout << "Display (v)alid, (i)nvalid, or (a)ll evaluations? ";
                cin >> type;
                cin.ignore();

                if (type == 'v' || type == 'V')
                {
                    displayEvaluations("prefix_valid_expressions.csv");
                }
                else if (type == 'i' || type == 'I')
                {
                    displayEvaluations("prefix_invalid_expressions.csv");
                }
                else if (type == 'a' || type == 'A')
                {
                    cout << "\nDisplaying valid evaluations:" << endl;
                    displayEvaluations("prefix_valid_expressions.csv");
                    cout << "\nDisplaying invalid evaluations:" << endl;
                    displayEvaluations("prefix_invalid_expressions.csv");
                }
                else
                {
                    cout << "Invalid choice." << endl;
                }
                break;
            }
            case 3:
            {
                char type;
                cout << "Delete from (v)alid or (i)nvalid expressions? ";
                cin >> type;
                cin.ignore();

                string filename;
                if (type == 'v' || type == 'V')
                {
                    filename = "prefix_valid_expressions.csv";
                    cout << "\nValid evaluations:\n";
                    displayEvaluations(filename);
                }
                else if (type == 'i' || type == 'I')
                {
                    filename = "prefix_invalid_expressions.csv";
                    cout << "\nInvalid evaluations:\n";
                    displayEvaluations(filename);
                }
                else
                {
                    cout << "Invalid choice." << endl;
                    break;
                }

                string expressionToDelete;
                cout << "\nEnter the expression to delete (exact match): ";
                getline(cin, expressionToDelete);

                deleteEvaluation(filename, expressionToDelete);
                break;
            }

            case 4:
            {
                char type;
                string filename;
                cout << "Update (v)alid or (i)nvalid expressions? ";
                cin >> type;
                cin.ignore();

                if (type == 'v' || type == 'V')
                {
                    filename = "prefix_valid_expressions.csv";
                    cout << "\nValid evaluations:\n";
                    displayEvaluations(filename);
                    string oldExpression, newExpression;
                    cout << "Enter the expression to update: ";
                    getline(cin, oldExpression);
                    cout << "Enter the new expression: ";
                    getline(cin, newExpression);

                    if (isValid(newExpression))
                    {
                        int result = prefixEvaluation(newExpression);
                        if (result != -1)
                        {
                            updateEvaluation("prefix_valid_expressions.csv", oldExpression, newExpression, result);
                        }
                    }
                    else
                    {
                        cout << "The new prefix expression is invalid." << endl;
                        updateEvaluation("prefix_invalid_expressions.csv", oldExpression, newExpression, -1);
                    }
                }
                else if (type == 'i' || type == 'I')
                {
                    string oldExpression, newExpression;
                    filename = "prefix_invalid_expressions.csv";
                    cout << "\nInvalid evaluations:\n";
                    displayEvaluations(filename);
                    cout << "Enter the expression to update: ";
                    getline(cin, oldExpression);
                    cout << "Enter the new expression: ";
                    getline(cin, newExpression);

                    updateEvaluation("prefix_invalid_expressions.csv", oldExpression, newExpression, -1);
                }
                else
                {
                    cout << "Invalid choice." << endl;
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
