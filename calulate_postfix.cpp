#include <string>
#include <iostream>
#include <cctype>  // For isdigit
#include <sstream> // For stringstream
#include <iomanip> // For setprecision
#include <cmath>   // For NaN
#include <fstream>
#include <limits>
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
    int operandCount = 0;  // Tracks the number of operands
    bool hasDigit = false; // Ensures the expression has at least one number

    for (size_t i = 0; i < expression.length(); ++i)
    {
        char ch = expression[i];

        // Purpose: This ensures the code treats valid negative numbers like -1 correctly, distinguishing them from the - operator.
        if (isdigit(ch) || (ch == '-' && (i + 1 < expression.length() && isdigit(expression[i + 1])))) // Handle numbers, including negative number
        {

            hasDigit = true; // Mark that a digit exists

            // Skip the rest of the number
            if (ch == '-')
                ++i; // Skip the negative sign
            while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.'))
            {
                ++i;
            }
            --i;            // Adjust for loop increment
            ++operandCount; // Count this as an operand
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^'|| ch == 'e')
        {

            // It's an operator
            if (operandCount < 2)
            {
                cout << "Error: Not enough operands for operator '" << ch << "'!" << endl;
                return false;
            }

            // Each operator combines two operands into one result
            --operandCount;
        }
        else if (!isspace(ch))
        {
            // Invalid character
            cout << "Error: Invalid character '" << ch << "' in the expression!" << endl;
            return false;
        }
    }

    // Final checks: Ensure at least one digit and valid operand/operator balance
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

    return true; // Expression is valid
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
        else if (token == "+" || token == "-" || token == "*" || token == "/"|| token == "^")
        {
            // It's an operator, check for sufficient operands
            // if (stack.size() < 2)
            // {
            //     cout << "Error: Not enough operands for operation!" << endl;
            //     return NAN; // Return NaN for invalid expression
            // }

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
                result = pow(op1,op2);
                break;
            case '/':
                if (op2 == 0)
                {
                    return numeric_limits<double>::infinity();
                }
                result = op1 / op2;
                break;
            default:
                cout << "Error: Invalid operator!" << endl;
            }

            // Push the result back onto the stack
            stack.push(result);
        }
    }

    // The final result should be the only item left in the stack
    // if (stack.size() == 1)
    // {
    //     cout << fixed << setprecision(2) << endl;
    //     return stack.peek();
    // }
    // else
    // {
    //     cout << "Error: Invalid expression!" << endl;
    //     return NAN; // Return NaN for invalid expression
    // }
    cout << fixed << setprecision(2);
    return stack.peek();
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
void invalid_expression(auto expression)
{

    fstream out1file("C:\\Users\\MSI PC\\Desktop\\advance final\\ALGORITHM-DATA-STRUCTURES-Final-Project-\\invalid_postfix_expression.csv", ios::app);

    if (!out1file.is_open())
    {
        cout << "Error: file 1 Could not open the file!" << endl;
    }

    out1file << expression << endl;

    out1file.close();
}
void display_valid_file()
{
    ifstream infile("C:\\Users\\MSI PC\\Desktop\\advance final\\ALGORITHM-DATA-STRUCTURES-Final-Project-\\expression_postfix.csv", ios::in);

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
void display_invalid_file()
{
    ifstream infile("C:\\Users\\MSI PC\\Desktop\\advance final\\ALGORITHM-DATA-STRUCTURES-Final-Project-\\invalid_postfix_expression.csv", ios::in);

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

void update_expression(const string &old_expression, const string &new_expression)
{
    ifstream infile("C:\\Users\\MSI PC\\Desktop\\advance final\\ALGORITHM-DATA-STRUCTURES-Final-Project-\\expression_postfix.csv");
    ofstream outfile("C:\\Users\\MSI PC\\Desktop\\advance final\\ALGORITHM-DATA-STRUCTURES-Final-Project-\\expression_postfix_temp.csv");

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
    string result;

    // Calculate the result for the new expression
    double calculated_result = evaluatePostfix(new_expression);
    result = to_string(calculated_result);
    stringstream result_stream;
    result_stream << fixed << setprecision(2) << calculated_result; // Set the precision to 2 decimal places
    result = result_stream.str();

    // Read each line from the input file
    while (getline(infile, line))
    {
        stringstream ss(line);
        string expression;

        // Split the line by '=' to separate expression and result
        getline(ss, expression, '=');

        // Trim whitespace from the expression
        expression.erase(0, expression.find_first_not_of(" \n\r\t")); // Left trim
        expression.erase(expression.find_last_not_of(" \n\r\t") + 1); // Right trim

        // If the expression matches the one to update, modify it
        if (expression == old_expression)
        {
            line = new_expression + " = " + result;
            found = true;
        }

        // Write the updated or original line to the new file

        outfile << line << endl;
    }

    if (!found)
    {
        cout << "Error: Expression not found in the file!" << endl;
    }

    // Close both input and output files
    infile.close();
    outfile.close();

    // If the expression was found, replace the original file with the updated one
    if (found)
    {
        remove("C:\\Users\\MSI PC\\Desktop\\advance final\\ALGORITHM-DATA-STRUCTURES-Final-Project-\\expression_postfix.csv");
        rename("C:\\Users\\MSI PC\\Desktop\\advance final\\ALGORITHM-DATA-STRUCTURES-Final-Project-\\expression_postfix_temp.csv",
               "C:\\Users\\MSI PC\\Desktop\\advance final\\ALGORITHM-DATA-STRUCTURES-Final-Project-\\expression_postfix.csv");
        cout << "Expression updated successfully!" << endl;
    }
    else
    {
        // If the expression was not found, delete the temporary file
        remove("C:\\Users\\MSI PC\\Desktop\\advance final\\ALGORITHM-DATA-STRUCTURES-Final-Project-\\expression_postfix_temp.csv");
    }
}
void delete_expression(const string &expression_to_delete)

{
    ifstream infile("C:\\Users\\MSI PC\\Desktop\\advance final\\ALGORITHM-DATA-STRUCTURES-Final-Project-\\expression_postfix.csv");
    ofstream outfile("C:\\Users\\MSI PC\\Desktop\\advance final\\ALGORITHM-DATA-STRUCTURES-Final-Project-\\expression_postfix_temp.csv");

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
    string expression;
    // Read each line from the input file
    while (getline(infile, line))
    {
        stringstream ss(line);

        // Split the line by '=' to separate expression and result
        getline(ss, expression, '=');

        // Trim whitespace from the expression
        expression.erase(0, expression.find_first_not_of(" \n\r\t")); // Left trim
        expression.erase(expression.find_last_not_of(" \n\r\t") + 1); // Right trim

        // If the expression matches the one to delete, skip writing it to the temp file
        if (expression == expression_to_delete)
        {
            found = true;
            continue; // Skip this line
        }

        // Write the line to the new file (excluding the deleted expression)
        outfile << line << endl;
    }

    if (!found)
    {
        cout << "Error: Expression not found in the file!" << endl;
    }

    // Close both input and output files
    infile.close();
    outfile.close();

    // If the expression was found, replace the original file with the updated one
    if (found)
    {
        remove("C:\\Users\\MSI PC\\Desktop\\advance final\\ALGORITHM-DATA-STRUCTURES-Final-Project-\\expression_postfix.csv");
        rename("C:\\Users\\MSI PC\\Desktop\\advance final\\ALGORITHM-DATA-STRUCTURES-Final-Project-\\expression_postfix_temp.csv",
               "C:\\Users\\MSI PC\\Desktop\\advance final\\ALGORITHM-DATA-STRUCTURES-Final-Project-\\expression_postfix.csv");
        cout << "Expression deleted successfully!" << endl;
    }
    else
    {
        // If the expression was not found, delete the temporary file
        remove("C:\\Users\\MSI PC\\Desktop\\advance final\\ALGORITHM-DATA-STRUCTURES-Final-Project-\\expression_postfix_temp.csv");
    }
}


int main()
{

    while (1)
    {

        string expression;

        cout << "Enter a postfix expression to calculate (e.g., '23 4 + 5 *'): ";
        getline(cin, expression); // Using getline to capture multi-digit numbers

        if (!validate(expression))
        {
            invalid_expression(expression);
        }
        else
        {

            double result = evaluatePostfix(expression);
            if (isinf(result))
            {
                cout << "Result is infinity!"<< result << endl;
                
                add_expression(expression, result);
            }else{

                cout << result <<endl ;
                 add_expression(expression, result);
            }
        }
    }
    //         // if (!isnan(result))
    //         // {

    //         //     cout << result << endl;

    //         //     add_expression(expression, result);
    //         // }
    //         // else
    //         // {
    //         //     cout << "Error: Calculation failed!" << endl;
    //         // }
    //  }
    // string old_expression;
    // string new_expression;
    // string delete_express;
    // while (1)
    // {

    //     display_valid_file();
    //     cout << "Enter the expression you want to update: ";
    //     getline(cin, old_expression);
    //     cout << "Enter the new expression: ";
    //     getline(cin, new_expression);

    //     update_expression(old_expression, new_expression);
    //     system("cls");
    //     display_valid_file();
    // }
    // while (1)
    // {

    //     display_valid_file();
    //     cout << "Enter the expression you want to delete: ";
    //     getline(cin, old_expression);

    //     delete_expression(delete_express);
    //     system("cls");
    //     display_valid_file();
    // }
    // display_valid_file();
    // display_invalid_file();
    return 0;
}
