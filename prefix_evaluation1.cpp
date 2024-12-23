#include <iostream>
#include <cctype>
#include <cmath>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

class Node
{
public:
    int data;
    Node *next;

    Node(int newData)
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

    void push(int newData)
    {
        Node *a = new Node(newData);
        a->next = topNode;
        topNode = a;
        size++;
    }

    int pop()
    {
        if (size == 0)
        {
            cout << "Error: Stack underflow\n";
            return -1;
        }
        else
        {
            Node *temp = topNode;
            int poppedData = topNode->data;
            topNode = topNode->next;
            delete temp;
            size--;
            return poppedData;
        }
    }

    int top()
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

// Function to store valid expressions along with their results in a CSV file
void storeValidExpression(const string &expression, int result)
{
    ofstream file("prefix_valid_expressions.csv", ios::app);
    if (file.is_open())
    {
        file << expression << "," << result << "\n";
        file.close();
    }
    else
    {
        cout << "Error: Unable to open prefix_valid_expressions.csv for writing." << endl;
    }
}

// Function to store invalid expressions in a CSV file
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

// Function to delete evaluations from CSV files
void deleteEvaluations()
{
    ofstream validFile("prefix_valid_expressions.csv", ios::trunc);
    ofstream invalidFile("prefix_invalid_expressions.csv", ios::trunc);

    if (validFile.is_open() && invalidFile.is_open())
    {
        validFile.close();
        invalidFile.close();
        cout << "All evaluations have been deleted from the files." << endl;
    }
    else
    {
        cout << "Error: Unable to open files for deleting evaluations." << endl;
    }
}

// Function to update an evaluation in a CSV file
void updateEvaluation(const string &filename, const string &oldExpression, const string &newExpression)
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
                lines.push_back(newExpression);
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

// Function to display evaluations from a CSV file
void displayEvaluations(const string &filename)
{
    ifstream file(filename);
    if (file.is_open())
    {
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

// Function to evaluate prefix expressions
int prefixEvaluation(const string &prefixExpression)
{
    Stack opStack;

    for (int i = prefixExpression.length() - 1; i >= 0; i--)
    {
        if (isdigit(prefixExpression[i]))
        {
            int num = 0;
            int placeValue = 1;

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
            int op2 = opStack.pop();

            if (opStack.isEmpty())
            {
                cout << "Error: Insufficient operands for operator " << prefixExpression[i] << endl;
                return -1;
            }
            int op1 = opStack.pop();

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

void displayMenu()
{
    cout << "\n--- Menu ---\n";
    cout << "1. Evaluate Prefix Expression\n";
    cout << "2. Display Evaluations\n";
    cout << "3. Delete All Evaluations\n";
    cout << "4. Update an Evaluation\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

int main()
{
    int choice;

    do
    {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
        {
            string prefixExpression;
            cout << "Enter a valid prefix expression: ";
            getline(cin, prefixExpression);

            int result = prefixEvaluation(prefixExpression);
            if (result != -1)
            {
                cout << "The result of the prefix expression is: " << result << endl;
                storeValidExpression(prefixExpression, result);
            }
            else
            {
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
            deleteEvaluations();
            break;
        }
        case 4:
        {
            char type;
            cout << "Update (v)alid or (i)nvalid expressions? ";
            cin >> type;
            cin.ignore();

            if (type == 'v' || type == 'V')
            {
                cout << "Displaying valid expressions:" << endl;
                displayEvaluations("prefix_valid_expressions.csv");

                string oldExpression, newExpression;
                cout << "Enter the old valid expression to update: ";
                getline(cin, oldExpression);
                cout << "Enter the new expression: ";
                getline(cin, newExpression);
                updateEvaluation("prefix_valid_expressions.csv", oldExpression, newExpression);
            }
            else if (type == 'i' || type == 'I')
            {
                cout << "Displaying invalid expressions:" << endl;
                displayEvaluations("prefix_invalid_expressions.csv");

                string oldExpression, newExpression;
                cout << "Enter the old invalid expression to update: ";
                getline(cin, oldExpression);
                cout << "Enter the new expression: ";
                getline(cin, newExpression);
                updateEvaluation("prefix_invalid_expressions.csv", oldExpression, newExpression);
            }
            else
            {
                cout << "Invalid choice." << endl;
            }
            break;
        }
        case 5:
            cout << "Exiting program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
