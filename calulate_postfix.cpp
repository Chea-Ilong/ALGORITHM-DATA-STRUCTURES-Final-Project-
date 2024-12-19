#include <string>
#include <iostream>
#include <cctype> // For isdigit
#include <sstream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <cstdlib>
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

class Postfix_expression
{

public:
    bool validate_postfix(const string &expression)
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
            else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^')
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

        return true;
    }

    // Function to evaluate the postfix expression
    double evaluate_postfix(const string &expression)
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
            else if (token == "+" || token == "-" || token == "*" || token == "/" || token == "^")
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

                // Push the result back onto the stack
                stack.push(result);
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

    void store_valid_expression(auto expression, auto result)
    {

        fstream out1file("C:\\Users\\MSI PC\\Desktop\\advance final\\ALGORITHM-DATA-STRUCTURES-Final-Project-\\expression_postfix.csv", ios::app);

        if (!out1file.is_open())
        {
            cout << "Error: file 1 Could not open the file!" << endl;
        }

        out1file << expression << " = " << result << endl;

        out1file.close();
    }
    void store_invalid_expression(auto expression)
    {

        fstream out1file("C:\\Users\\MSI PC\\Desktop\\advance final\\ALGORITHM-DATA-STRUCTURES-Final-Project-\\invalid_postfix_expression.csv", ios::app);

        if (!out1file.is_open())
        {
            cout << "Error: file 1 Could not open the file!" << endl;
        }

        out1file << expression << endl;

        out1file.close();
    }
    void display_valid_expression()
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
    void display_invalid_expression()
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

        string line, result;
        bool found = false;

        double calculated_result = evaluate_postfix(new_expression);
        result = to_string(calculated_result);

        stringstream result_stream;
        result_stream << fixed << setprecision(2) << calculated_result;
        result = result_stream.str();

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

        while (getline(infile, line))
        {
            // Trim whitespace from the entire line (left and right)
            string trimmed_line = line;
            trimmed_line.erase(0, trimmed_line.find_first_not_of(" \n\r\t")); // Left trim
            trimmed_line.erase(trimmed_line.find_last_not_of(" \n\r\t") + 1); // Right trim

            // Check if the entire line matches the expression to delete
            if (trimmed_line == expression_to_delete)
            {
                found = true;

                continue; // Skip writing this line to the output file
            }

            outfile << line << endl; // Write the line to the temporary file
        }

        infile.close();
        outfile.close();

        if (found)
        {
            remove("C:\\Users\\MSI PC\\Desktop\\advance final\\ALGORITHM-DATA-STRUCTURES-Final-Project-\\expression_postfix.csv");
            rename("C:\\Users\\MSI PC\\Desktop\\advance final\\ALGORITHM-DATA-STRUCTURES-Final-Project-\\expression_postfix_temp.csv",
                   "C:\\Users\\MSI PC\\Desktop\\advance final\\ALGORITHM-DATA-STRUCTURES-Final-Project-\\expression_postfix.csv");
            cout << "Expression deleted successfully!" << endl;
        }
        else
        {
            cout << "Error: Expression not found in the file!" << endl;
            remove("C:\\Users\\MSI PC\\Desktop\\advance final\\ALGORITHM-DATA-STRUCTURES-Final-Project-\\expression_postfix_temp.csv");
        }
    }

    void remove_postfix_expression()
    {
        string old_expression;

        display_valid_expression();
        cout << "Enter the expression you want to delete: ";
        getline(cin, old_expression);
        delete_expression(old_expression);
        // display_valid_expression();
    }
    void update_postfix_expression()
    {
        string old_expression;
        string new_expression;

        display_valid_expression();
        cout << "Enter the expression you want to update: ";
        getline(cin, old_expression);
        cout << "Enter the new expression: ";
        getline(cin, new_expression);
        update_expression(old_expression, new_expression);
        // display_valid_expression();
    }
    void help()
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
    }

    void menu()
    {
        int choice;
        cout << "Choose an option: \n"
             << "1. Evaluate postfix expression\n"
             << "2. View all expressions\n"
             << "3. Update an expression\n"
             << "4. Delete an expression\n"
             << "5. Exit\n";
        cin >> choice;
        cin.ignore(); // to ignore the leftover newline character
        system("cls");
        switch (choice)
        {
        case 1:
            postfix();
            break;
        case 2:
            display_valid_expression();
            break;
        case 3:
            update_postfix_expression();
            break;
        case 4:
            remove_postfix_expression();
            break;
        case 5:
            exit(0);
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    }
    void postfix()
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
                        help();
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
                double result = evaluate_postfix(expression);
                if (isnan(result))
                {
                    store_invalid_expression(expression);
                }
                else
                {
                    cout << "Result: " << result << endl;
                    store_valid_expression(expression, result);
                }
                break; // Exit after successfully evaluating the expression
            }
        }
    }
};
int main()
{
    Postfix_expression post;
    while (1)
    {
        
        post.menu();
    }
    return 0;
}
