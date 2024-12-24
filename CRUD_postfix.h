#include <string>
#include <iostream>
#include <cctype>  // For isdigit
#include <sstream> // For stringstream
#include <iomanip> // For setprecision
#include <cmath>   // For NaN
#include <fstream>
#include <limits>
using namespace std;
void add_expression(auto expression, auto result)
{

    fstream out1file("expression_postfix.csv", ios::app);

    if (!out1file.is_open())
    {
        cout << "Error: file 1 Could not open the file!" << endl;
    }

    out1file << expression << " = " << result << endl;

    out1file.close();
}
void invalid_expression(auto expression)
{

    fstream out1file("invalid_postfix_expression.csv", ios::app);

    if (!out1file.is_open())
    {
        cout << "Error: file 1 Could not open the file!" << endl;
    }

    out1file << expression << endl;

    out1file.close();
}
void display_valid_file()
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
void display_invalid_file()
{
    ifstream infile("invalid_postfix_expression.csv", ios::in);

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
        remove("expression_postfix.csv");
        rename("expression_postfix_temp.csv",
               "expression_postfix.csv");
        cout << "Expression deleted successfully!" << endl;
    }
    else
    {
        // If the expression was not found, delete the temporary file
        remove("expression_postfix_temp.csv");
    }
}
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
        remove("expression_postfix.csv");
        rename("expression_postfix_temp.csv",
               "expression_postfix.csv");
        cout << "Expression updated successfully!" << endl;
    }
    else
    {
        // If the expression was not found, delete the temporary file
        remove("expression_postfix_temp.csv");
    }
}
