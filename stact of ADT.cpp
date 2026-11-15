#include <iostream>
#include <string>
#include <cctype>
 
using namespace std;
 
class Node      // Node of Singly Linked List
{
public:
    int data;
    Node *next;
 
    Node(int value)
    {
        data = value;
        next = NULL;
    }
};
 
// Stack ADT using Linked List
class Stack
{
    Node *top;
 
public:
    Stack()
    {
        top = NULL;
    }
 
    void push(int value)
    {
        Node *newNode = new Node(value);
        newNode->next = top;
        top = newNode;
    }
 
    int pop()
    {
        if (top == NULL)
            return 0;
 
        int value = top->data;
        Node *temp = top;
        top = top->next;
        delete temp;
 
        return value;
    }
 
    int peek()
    {
        if (top == NULL)
            return 0;
 
        return top->data;
    }
 
    bool isEmpty()
    {
        return top == NULL;
    }
};
 
// Check operator
bool isOperator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}
 
// Priority of operator
int priority(char ch)
{
    if (ch == '+' || ch == '-')
        return 1;
 
    if (ch == '*' || ch == '/')
        return 2;
 
    return 0;
}
 
// Infix to Postfix
string infixToPostfix(string infix)
{
    Stack s;
    string postfix = "";
 
    for (char ch : infix)
    {
        if (isdigit(static_cast<unsigned char>(ch)))
        {
            postfix += ch;
        }
        else if (ch == '(')
        {
            s.push(ch);
        }
        else if (ch == ')')
        {
            while (!s.isEmpty() && s.peek() != '(')
                postfix += static_cast<char>(s.pop());
 
            if (!s.isEmpty())
                s.pop(); // remove '('
        }
        else if (isOperator(ch))
        {
            while (!s.isEmpty() && s.peek() != '(' &&
                   priority(static_cast<char>(s.peek())) >= priority(ch))
            {
                postfix += static_cast<char>(s.pop());
            }
 
            s.push(ch);
        }
    }
 
    while (!s.isEmpty())
        postfix += static_cast<char>(s.pop());
 
    return postfix;
}
 
// Evaluate Postfix
int evaluatePostfix(string postfix)
{
    Stack s;
    int a, b, result;
 
    for (char ch : postfix)
    {
        if (isdigit(static_cast<unsigned char>(ch)))
        {
            s.push(ch - '0');
        }
        else if (isOperator(ch))
        {
            b = s.pop();
            a = s.pop();
 
            switch (ch)
            {
            case '+':
                result = a + b;
                break;
 
            case '-':
                result = a - b;
                break;
 
            case '*':
                result = a * b;
                break;
 
            case '/':
                if (b == 0)
                {
                    cout << "Error: Division by zero." << endl;
                    return 0;
                }
                result = a / b;
                break;
            }
 
            s.push(result);
        }
    }
 
    return s.pop();
}
 
int main()
{
    string infix, postfix;
 
    cout << "Enter infix expression: ";
    cin >> infix;
 
    postfix = infixToPostfix(infix);
 
    cout << "Postfix expression: " << postfix << endl;
    cout << "Result: " << evaluatePostfix(postfix) << endl;
 
    return 0;
}
