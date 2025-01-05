#include "Stack_1.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
class Expression_Conversion // User are able to convert number or variable (A, B, C) to prefix or postfix
{
private:
    string infix;
    string infix_with_space;
    string valid_file_name;
    string invalid_file_name;
    string postfix;
    string prefix;

public:
    Expression_Conversion()
    {
        infix = "";
        valid_file_name = "valid_infix_file.csv";
        invalid_file_name = "invalid_infix_file.txt";
    }
    Expression_Conversion(string valid, string invalid)
    {
        infix = "";
        valid_file_name = valid;
        invalid_file_name = invalid;
    }
    Expression_Conversion(string infix, string valid, string invalid)
    {
        this->infix = infix;
        this->infix_with_space = infix;
        postfix = _convert_to_postfix(infix);
        prefix = _convert_to_prefix(infix);
        valid_file_name = valid;
        invalid_file_name = invalid;
        for (size_t i = infix_with_space.size() - 1; i > 0; i--)
        {
            if (!isdigit(infix_with_space[i]) && !isdigit(infix_with_space[i - 1]))
            {
                infix_with_space.insert(i, " ");
            }
        }
    }
    void menu_conversion()
    {
        int choice;
        do
        {
            system("cls");
            const string RESET = "\033[0m";
            const string RED = "\033[31m";
            const string GREEN = "\033[32m";
            const string YELLOW = "\033[33m";
            const string CYAN = "\033[36m";
            const string BOLD = "\033[1m";

            // Header with Colorful Formatting
            cout << CYAN;
            cout << "***********************************************" << endl;
            cout << "*                                             *" << endl;
            cout << "*     " << BOLD << YELLOW << "WELCOME TO THE EXPRESSION CONVERSION" << RESET << CYAN << "    *" << endl;
            cout << "*                                             *" << endl;
            cout << "***********************************************" << RESET << endl
                 << endl;

            // Current Infix Expression with Color
            cout << BOLD << YELLOW << "Current Infix Expression: " << RESET << infix_with_space << endl
                 << endl;

            // Prompt to choose an option with Color
            cout << BOLD << YELLOW << "Please choose an option from the menu below:" << RESET << endl
                 << endl;

            // Menu Options with Color
            cout << GREEN << "  1. Enter a New Infix Expression" << RESET << endl;
            cout << GREEN << "  2. Modify the Current Infix Expression" << RESET << endl;
            cout << GREEN << "  3. Update Expression in File" << RESET << endl;
            cout << GREEN << "  4. View Expressions from File" << RESET << endl;
            cout << GREEN << "  5. Delete an Expression in File" << RESET << endl;
            cout << GREEN << "  6. Convert to Postfix Notation" << RESET << endl;
            cout << GREEN << "  7. Convert to Prefix Notation" << RESET << endl;
            cout << GREEN << "  8. Save the Expression to File" << RESET << endl;
            cout << RED << "  9. Exit the Program" << RESET << endl
                 << endl;

            cout << BOLD << CYAN << "Enter your choice: " << RESET;
            cin >> choice;

            cin.ignore();
            cout << endl;
            switch (choice)
            {
            case 1:
                input_infix();
                break;
            case 2:
                update();
                break;
            case 3:
                int line;
                read_from_file();
                cout << endl
                     << "Enter the line you want to update: ";
                cin >> line;
                cin.ignore();
                update_to_file(line);
                break;
            case 4:
                read_from_file();
                break;
            case 5:
                int line_delete;
                read_from_file();
                cout << endl
                     << "Enter the line you want to delete: ";
                cin >> line_delete;
                delete_from_file(line_delete);
                break;
            case 6:
                cout << endl
                     << "The postfix expression is: " << convert_to_postfix();
                break;
            case 7:
                cout << endl
                     << "The prefix expression is: " << convert_to_prefix();
                break;
            case 8:
                save_to_file();
                cout << endl
                     << "The expression and its conversions have been saved successfully to [" << valid_file_name << "]";
                break;
            case 9:
                cout << "Returning to Main Menu..." << endl;
                return;
            default:
                cout << endl
                     << "Invalid choice";
            }
            cout << endl;
            system("pause");
        } while (choice != 9);
    }
    void save_to_file()
    {
        if (infix != "")
        {
            ofstream write_file(valid_file_name, ios::app);
            write_file << infix_with_space << " = " << prefix << ',' << infix_with_space << " = " << postfix << endl;
            write_file.close();
        }
    }

    bool validate(string infix) // Validate if the input expression is right or wrong
    {
        int parenthesis = 0;
        if (!isalnum(infix[0]))
        {
            return false;
        }
        for (size_t i = 0; i < infix.length(); i++)
        {
            if (parenthesis < 0)
            {
                return false;
            }
            else if (infix[i] == '(')
            {
                parenthesis++;
                continue;
            }
            else if (infix[i] == ')')
            {
                parenthesis--;
                continue;
            }
            else if (i != infix.length() - 1 && ((!isalnum(infix[i]) && !isalnum(infix[i + 1])) || (isalpha(infix[i]) && isalpha(infix[i + 1]))))
            {
                if (infix[i + 1] == '(')
                {
                    continue;
                }
                return false;
            }
        }
        if (parenthesis != 0)
        {
            return false;
        }
        return true;
    }

    void input_infix() // Allow users to input as many whitespace as they want
    {
        cout << endl
             << "Enter the infix expression: ";
        getline(cin, infix);
        infix.erase(remove(infix.begin(), infix.end(), ' '), infix.end());
        if (!validate(infix))
        {
            ofstream write_file(invalid_file_name, ios::app);
            write_file << infix << endl;
            write_file.close();
            input_infix();
        }
        else
        {
            postfix = _convert_to_postfix(infix);
            prefix = _convert_to_prefix(infix);
            infix_with_space = infix;
            for (size_t i = infix_with_space.size() - 1; i > 0; i--)
            {
                if (!isdigit(infix_with_space[i]) && !isdigit(infix_with_space[i - 1]))
                {
                    infix_with_space.insert(i, " ");
                }
                else if ((isdigit(infix_with_space[i]) && !isdigit(infix_with_space[i - 1])) || (i != infix_with_space.size() - 1 && !isdigit(infix_with_space[i]) && isdigit(infix_with_space[i - 1])))
                {
                    infix_with_space.insert(i, " ");
                }
            }
        }
    }

    void update()
    {
        cout << endl
             << "The old expression: " << infix_with_space;
        input_infix();
    }

    void update_to_file(int line) // using vector to store both prefix and postfix in the file. The update will be on the vector before writing it to the file
    {
        if (line <= 0)
        {
            cout << "Invalid Line";
            return;
        }
        vector<string> vec_postfix;
        string temp_postfix;
        vector<string> vec_prefix;
        string temp_prefix;
        string temp;
        ifstream read_file(valid_file_name);
        if (!read_file.is_open())
        {
            cout << endl
                 << "Cannot open the file";
            return;
        }

        while (getline(read_file, temp))
        {
            stringstream ss(temp);
            getline(ss, temp_prefix, ',');
            vec_prefix.push_back(temp_prefix);
            getline(ss, temp_postfix);
            vec_postfix.push_back(temp_postfix);
        }
        read_file.close();
        stringstream ss(vec_postfix[line - 1]); // Line - 1 because Line is count from 1 instead of 0 like index
        string store_infix;
        getline(ss, store_infix, '=');
        cout << endl
             << "[" << line << "] " << store_infix;
        input_infix();
        vec_postfix[line - 1] = infix_with_space + " = " + postfix;
        vec_prefix[line - 1] = infix_with_space + " = " + prefix;
        ofstream write_file(valid_file_name);
        if (!write_file.is_open())
        {
            cout << "Unable to open file";
            return;
        }
        for (size_t i = 0; i < vec_postfix.size(); i++)
        {
            write_file << vec_prefix[i] << ',' << vec_postfix[i] << endl;
        }
        write_file.close();
    }

    void read_from_file()
    {
        vector<string> vec_postfix;
        string temp_postfix;
        vector<string> vec_prefix;
        string temp_prefix;
        string temp;
        ifstream read_file(valid_file_name);
        if (!read_file.is_open())
        {
            cout << endl
                 << "Cannot open the file";
            return;
        }
        while (getline(read_file, temp))
        {
            stringstream ss(temp);
            getline(ss, temp_prefix, ',');
            vec_prefix.push_back(temp_prefix);
            getline(ss, temp_postfix);
            vec_postfix.push_back(temp_postfix);
        }
        read_file.close();
        cout << "Conversion to Prefix Expression : ";
        for (size_t i = 0; i < vec_prefix.size(); i++)
        {
            cout << endl
                 << "[" << i + 1 << "] " << vec_prefix[i];
        }
        cout << endl
             << "Conversion to Postfix Expression : ";
        for (size_t i = 0; i < vec_postfix.size(); i++)
        {
            cout << endl
                 << "[" << i + 1 << "] " << vec_postfix[i];
        }
    }

    void delete_from_file(int line)
    {
        if (line <= 0)
        {
            cout << "Invalid Line";
            return;
        }
        vector<string> vec_postfix;
        string temp_postfix;
        vector<string> vec_prefix;
        string temp_prefix;
        string temp;
        ifstream read_file(valid_file_name);
        if (!read_file.is_open())
        {
            cout << endl
                 << "Cannot open the file";
            return;
        }

        while (getline(read_file, temp))
        {
            stringstream ss(temp);
            getline(ss, temp_prefix, ',');
            vec_prefix.push_back(temp_prefix);
            getline(ss, temp_postfix);
            vec_postfix.push_back(temp_postfix);
        }
        read_file.close();
        vec_postfix.erase(vec_postfix.begin() + line - 1);
        vec_prefix.erase(vec_prefix.begin() + line - 1);
        ofstream write_file(valid_file_name);
        if (!write_file.is_open())
        {
            cout << "Unable to open file";
            return;
        }
        for (size_t i = 0; i < vec_postfix.size(); i++)
        {
            write_file << vec_prefix[i] << ',' << vec_postfix[i] << endl;
        }
        write_file.close();
    }
    int precedence(char optr) // Evaluate which operator should take the priority
    {
        if (optr == '+' || optr == '-')
            return 1;
        if (optr == '*' || optr == '/')
            return 2;
        if (optr == '^')
            return 3;
        return 0;
    }
    string _convert_to_postfix(string input = "") // Allow users to convert the infix directly or use it to convert userinput expression
    {
        if (input == "")
            input = infix;
        Stack_1 storage;
        string temp_postfix;
        for (unsigned int i = 0; i < input.size(); i++)
        {
            if (isalnum(input[i]))
            {
                if (!isalnum(input[i + 1]))
                    temp_postfix = temp_postfix + input[i] + " ";
                else
                    temp_postfix = temp_postfix + input[i];
            }
            else if (input[i] == '(')
            {
                storage.push(input[i]);
            }
            else if (input[i] == ')')
            {
                while (!storage.isEmpty() && storage.peek() != '(')
                {
                    temp_postfix = temp_postfix + storage.peek() + " ";
                    storage.pop();
                }
                storage.pop();
            }
            else
            {
                while (!storage.isEmpty() && precedence(storage.peek()) >= precedence(input[i]))
                {
                    temp_postfix = temp_postfix + storage.peek() + " ";
                    storage.pop();
                }
                storage.push(input[i]);
            }
        }
        while (!storage.isEmpty())
        {
            temp_postfix = temp_postfix + storage.peek() + " ";
            storage.pop();
        }
        ofstream write_file(valid_file_name, ios::app);
        return temp_postfix;
    }
    string _convert_to_prefix(string input = "") // To convert from infix to prefix, we can just reverse the infix,turn it into postfix, then reverse again
    {
        if (input == "")
            input = infix;
        reverse(input.begin(), input.end());
        for (size_t i = 0; i < input.size(); i++)
        {
            if (input[i] == '(')
            {
                input[i] = ')';
            }
            else if (input[i] == ')')
            {
                input[i] = '(';
            }
        }
        string temp = _convert_to_postfix(input);
        reverse(temp.begin(), temp.end());
        ofstream write_file(valid_file_name, ios::app);
        return temp;
    }
    string convert_to_postfix()
    {
        return postfix;
    }
    string convert_to_prefix()
    {
        return prefix;
    }
};
