#include "header/Stack.h"
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;
string convert_to_postfix(string infix)
{
    Stack storage;
    string temp;
    for(unsigned int i = 0; i<infix.size();i++)
    {
        if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '(' || infix[i] == ')')
        {
            if((storage.peek()=='+'&&infix[i]=='-')||(storage.peek()=='-'&&infix[i]=='+'))
            {
                temp +=storage.peek();
                storage.pop();
                storage.push(infix[i]);
            }
            else if ((storage.peek()=='*'&&infix[i]=='/')||(storage.peek()=='/'&&infix[i]=='*'))
            {
                temp +=storage.peek();
                storage.pop();
                storage.push(infix[i]);
            }
            else if(infix[i]==')')
            {
                while (storage.peek()!='(')
                {
                    temp +=storage.peek();
                    storage.pop();
                }
                storage.pop();
            }
            else
            {
                storage.push(infix[i]);
            }
        }
        else
        {
            temp +=infix[i];
        }
    }
    int size = storage.size();
    for(int i = 0 ; i<size;i++)
    {
        temp +=storage.peek();
        storage.pop();
    }
    return temp;   
}
string convert_to_prefix(string infix)
{
    string temp = convert_to_postfix(infix);
    reverse(temp.rbegin(),temp.rend());
    return temp;
}
int main()
{
    string test = "(A+B)-(C*D)";
    string prefix = convert_to_prefix(test);
    cout<<prefix;
    return 0;
}
