#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include "stack.h"
using namespace std;
using namespace cop4530;

bool parenCheck(const vector<string>&);
bool operatorMatch(const vector<string>&);
float calcOperator(float, float, string);
bool checkVars(Stack<string>);


/*
void infix2postfix(const vector<string> &infix)
{

	Stack<string> s;

	for ( int I = 0; I < infix.size(); ++I)
	{
		cout << " hi hi hi ";
	}

if ((infix[I] != '+') && (infix[I] != '-') && (infix[I] != '*') 
		(infix[I] != '/') && (infix[I] != '(') && (infix[I] != ')'))
		{
		cout << infix[I];
		}
		
		else if ((infix[I] == '+') || (infix[I] == '-') || (infix[I] == '*')
		                (infix[I] == '/') || (infix[I] == '(') || (infix[I] == ')'))
		{
			while ( s.top() != '(' && s.top() >= infix[I])
			{
				cout <<  s.top();
				cout << s.pop();
			}
			s.push(infix[I]);
		}
		else if (infix[I] == ')' )
		{
			while (s.top() != '(' )
			{
				cout << s.top(); 
				cout << s.pop();
			}
			s.pop(); // remove
		}
	}
	while (!s.empty())
	{
		cout << s.top(); 
		cout << s.pop;
	}




}
*/

void in2post(const vector<string> & line, Stack<string> & myStack)
{

    Stack<string> operands; 
   
    string postfix = ""; // used for empty string

    for (unsigned int i=0; i<line.size(); ++i)
        {
	        if (line[i] == "+" || line[i] == "-")
		        {

			while ( ( !operands.empty() &&  operands.top() != "(" ) && 
			        (operands.top() != "*" || operands.top() != "/") )
	                {
			 myStack.push(operands.top() );
			operands.pop();
			}
			operands.push(line[i]);
	}
	else if (line[i] == "*" || line[i] == "/")
	{
	 	while (!operands.empty() && operands.top() != "(" && 
	        (operands.top() != "-" && operands.top() != "+") )
		{
			myStack.push(operands.top() );
			operands.pop();
		}
		operands.push(line[i]);

	}

	else if (line[i] == "(" )
	{
		operands.push(line[i]);
	}
	else if (line[i] == ")" )
	{
		while (operands.top() != "(" )
		{
			myStack.push(operands.top() );
			operands.pop();
		}
		operands.pop();
	}
	else
	myStack.push(line[i]);
     }
     while(operands.empty() == false)
     {
     myStack.push(operands.top() );
     operands.pop();
     }
 }

float evalPostfix(Stack<string> & myStack)
{
	stringstream ss;
	Stack<string> stkTemp;
        string temp;

	myStack.print(ss, ' ');

	while (ss >> temp)
	{
           if (temp == "+" || temp == "-" || temp == "*" || temp == "/")
           {
	   float rhs = stof( stkTemp.top() );
	   stkTemp.pop();
	   float lhs = stof( stkTemp.top() );
	   stkTemp.pop();

	   stringstream val;
	   val << calcOperator(lhs, rhs, temp);
	   string a;
	   val >> a;
	   stkTemp.push(a);
	}
	else
	{
		stkTemp.push(temp);
	}
     }
	 return stof( stkTemp.top() );
}

bool parenCheck(const vector<string> & line)
{
  Stack<string> check;

 for (size_t i=0; i< line.size(); ++i)
      {
         if ( line[i] == "(" || line[i] == "[" )
	       check.push(line[i]);

	 else if (line[i] == ")" )
	         {
		     if (check.top() != "(")
		         return false;
		     else 
		         check.pop();
                  }
		  else if (line[i] == "]")
		  {
		  if (check.top() != "[")
		     return false;
                  else
		     check.pop();
		  }
      }

	if (check.empty())
	    return true;
	else
	       return false;


}

bool operatorMatch(const vector<string> & line)
{

	int operators = 0;
    	int operands = 0;

	for (size_t i=0; i< line.size(); ++i)
	{
		if (line[i] == "+" || line[i] == "-" ||
	        line[i] == "*" || line[i] == "/" )
		++operators;
		 else if (line[i] == "[" || line[i] == "]" ||
		 line[i] == "(" || line[i] == ")" )
		 continue;
		 else
		 ++operands;
	}

	if (operators == 0 && operands == 0) return true;
	else if ( operators == (operands-1)) return true;
	else return false;
}

	bool checkVars(Stack<string> myStack)
	{
		while (!myStack.empty())
		{
			stringstream ss;
			float tmp;
		        ss << myStack.top();

			 if ( myStack.top() == "+" || myStack.top() == "-" || myStack.top() == "*" || myStack.top() == "/" )
			         {}
			else if ( !(ss >> tmp) )
			return false;   
			        myStack.pop();
		}
		return true;
	}


	float calcOperator(float lhs, float rhs, string oper)
	{
		 if (oper == "+")
		    return lhs + rhs;
		 else if (oper == "-")
		    return lhs - rhs;
		 else if (oper == "*")
		    return lhs * rhs;
		 else
		    return lhs / rhs;
	}

int main()
{
	Stack<string> postfix;
	string input;

	cout << "Enter infix expression (\"exit\" to quit): ";

	while(getline(cin,input) )
	{
		cout << endl;
	  	if (input == "exit") break;
		vector<string> currLine;
		stringstream ss(input);
		string temp;

		 while(ss >> temp)
		 {
		 currLine.push_back(temp);
		 }
		
		 if ( parenCheck(currLine) == false )
		 {
		 	 cout << "Error: Infix expression: ";
			 for (size_t i=0; i< currLine.size(); ++i)
			 cout << currLine[i] << ' ';
			 cout << "has mismatched parens!" << endl;
		}

		 else if( operatorMatch(currLine) == false )
		 {
		 	 cout << "Error: Missing operand in postfix string.";
			  cout << "Unable to evaluate postfix string!" << endl;
		}
		else
		{
	//	in2post(currLine);
		in2post(currLine, postfix);

		cout << "Infix expression: ";
		for (size_t i=0; i<currLine.size(); ++i)
		cout << currLine[i] << ' ';
		cout << endl;

		cout << "Postfix expression: ";
		cout << postfix << endl;
		cout << "Postfix evaluation: ";
		cout << postfix << " = ";

		if (checkVars(postfix) == false)
		cout << postfix << endl;
		else
		cout << evalPostfix(postfix) << endl;

		postfix.clear();

		}
		cout << "enter infix expression ( exit to quit): ";
	}
		cout << endl;


return 1;

}
