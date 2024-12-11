#include <string>
#include <iostream>
#include <cctype>  // For isdigit
#include <sstream> // For stringstream
#include <iomanip> // For setprecision
#include <cmath>   // For NaN
#include <fstream>
using namespace std;

struct Nodes
{
    double value;
    Nodes *next;
};

class Stack
{
private:
    int length;
    Nodes *top;

public:
    Stack()
    {
        top = nullptr;
        length = 0;
    }

    ~Stack()
    {
        while (!isEmpty())
        {
            pop();
        }
    }

    void push(double newValue)
    {
        Nodes *newNode = new Nodes;
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
            Nodes *temp = top;
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
            return NAN; // Return NaN to indicate an error
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
// Function to validate the expression (returns true if valid)
bool validate(const string &expression)
{
    bool hasDigit = false; // Tracks if the expression has at least one digit

    for (size_t i = 0; i < expression.length(); ++i)
    {
        char ch = expression[i];

        if (isdigit(ch))
        {
            hasDigit = true; // A valid number is found
        }
        else if (ch != '+' && ch != '-' && ch != '*' && ch != '/' && !isspace(ch) && ch != '.')
        {
            // Invalid character
            cout << "Error: Invalid character '" << ch << "' in the expression!" << endl;
            return false;
        }
    }

    // Ensure there is at least one digit
    if (!hasDigit)
    {
        cout << "Error: Expression must contain at least one number!" << endl;
        return false;
    }

    return true; // All checks passed
}

// Function to evaluate the postfix expression
double evaluatePostfix(const string &expression)
{
    Stack stack;
    stringstream ss(expression);
    string token;

    while (ss >> token)
    {
        // Check if token is a valid number (including decimal numbers)
        stringstream tokenStream(token);
        double number;

        if (tokenStream >> number && tokenStream.eof())
        {
            // It's a valid number, push it to the stack
            stack.push(number);
        }
        else if (token == "+" || token == "-" || token == "*" || token == "/")
        {
            // It's an operator, check for sufficient operands
            if (stack.size() < 2)
            {
                cout << "Error: Not enough operands for operation!" << endl;
                return NAN; // Return NaN for invalid expression
            }

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
            case '/':
                if (op2 == 0)
                {
                    cout << "Error: Division by zero!" << endl;
                    return NAN; // Return NaN for invalid division
                }
                result = op1 / op2;
                break;
            default:
                cout << "Error: Invalid operator!" << endl;
                return NAN; // Return NaN for invalid operator
            }

            // Push the result back onto the stack
            stack.push(result);
        }
        else if (isspace(token[0]))
        {
            // Ignore spaces in the expression
            continue;
        }
        else
        {
            cout << "Error: Invalid character in expression!" << endl;
            return NAN; // Return NaN for invalid character
        }
    }

    // The final result should be the only item left in the stack
    if (stack.size() == 1)
    {
        cout << fixed << setprecision(2) << endl;
        return stack.peek();
    }
    else
    {
        cout << "Error: Invalid expression!" << endl;
        return NAN; // Return NaN for invalid expression
    }
}
void add_expression(auto expression, auto result)
{

    fstream out1file("C:\\Users\\MSI PC\\Desktop\\advance final\\ALGORITHM-DATA-STRUCTURES-Final-Project-\\expression_postfix.csv", ios::app);

    if (!out1file.is_open())
    {
        cout << "Error: file 1 Could not open the file!" << endl;
    }
   
    out1file << expression << " = " << result << endl;
   
    out1file.close();
    
}
void displayfile(){
    ifstream infile("C:\\Users\\MSI PC\\Desktop\\advance final\\ALGORITHM-DATA-STRUCTURES-Final-Project-\\expression_postfix.csv", ios::in);

    if (!infile.is_open())
    {
        cout << "Error: file Could not open the file!" << endl;
    }
    string line;
    while (getline(infile, line))
    {

    cout << line << endl ;
   
    infile.close();
}}
int main()
{

    while (1)
    {

        string expression;

        cout << "Enter a postfix expression to calculate (e.g., '23 4 + 5 *'): ";
        getline(cin, expression); // Using getline to capture multi-digit numbers

        // if (!validate(expression))
        // {
        //     continue; // Skip invalid expressions and ask for input again
        // }
        validate(expression);

        double result = evaluatePostfix(expression);

        if (!isnan(result))
        {

            cout << result << endl;

            add_expression(expression , result);
        }
        else
        {
            cout << "Error: Calculation failed!" << endl;
        }
     
    }
    //    displayfile();
    return 0;
}
