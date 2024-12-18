#include "header/Stack.h"
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int precedence(char optr)
{
    if(optr == '+' || optr == '-')
        return 1;
    if (optr == '*' || optr == '/')
        return 2;
    if (optr == '^')
        return 3;
    return 0;
}
string convert_to_postfix(string infix)
{
    Stack storage;
    string temp;
    for(unsigned int i = 0; i<infix.size();i++)
    {
        if(isalnum(infix[i]))
        {
            temp+=infix[i];
        }
        else if (infix[i] == '(')
        {
            storage.push(infix[i]);
        }
        else if(infix[i] == ')')
        {
            while(!storage.isEmpty() && storage.peek()!='(')
            {
                temp += storage.peek();
                storage.pop();
            }
            storage.pop();
        }
        else
        {
            while(!storage.isEmpty() && precedence(storage.peek()) >= precedence(infix[i]))
            {
                temp +=storage.peek();
                storage.pop();
            }
            storage.push(infix[i]);
        }
    }
    while(!storage.isEmpty())
    {
        temp+=storage.peek();

        storage.pop();
    }
    return temp;   
}
string convert_to_prefix(string infix)
{ 
    reverse(infix.begin(),infix.end());
    for(int i = 0 ;i <infix.size();i++)
    {
        if(infix[i] == '(')
        {
            infix[i] = ')';
        }
        else if (infix[i] == ')')
        {
            infix[i] = '(';
        }
    }
    string temp = convert_to_postfix(infix);
    reverse(temp.begin(),temp.end());
    return temp;
}
void input_infix(string& infix)
{
    cout<<"Enter the infix expression: ";
    getline(cin,infix);
    infix.erase(remove(infix.begin(),infix.end(),' '),infix.end());
}
int main()
{
    string infix;
    input_infix(infix);
    cout<<convert_to_postfix(infix);
    cout<<endl<<convert_to_prefix(infix);
}
