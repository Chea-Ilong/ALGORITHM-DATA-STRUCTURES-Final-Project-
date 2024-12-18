#include <string>
#include <iostream>
using namespace std;

struct Nodes
{
    char value;
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
    void push(char newValue)
    {

        Nodes *newNode;
        newNode = new Nodes;

        newNode->value = newValue;
        newNode->next = top;
        top = newNode;
        length++;
    };
    void pop()
    {
        if (length == 0)
        {
            cout << "The stack is empty";
        }
        else
        {

            Nodes *temp = top;
            top = top->next;
            delete temp;
            length--;
        }
    };
    char peek()
    {
        if (length == 0)
        {
            return '0';
        }
        else
        {
            return top->value;
        }
    };
    bool isEmpty()
    {
        return (length == 0);
    };
    string print()
    {
        Nodes *t = top;
        string store = " ";
        while (t != nullptr)
        {
            store += (t->value) + " ";
            t = t->next;
        }
        return store;
    }
    int size()
    {

        return length;
    };
};
