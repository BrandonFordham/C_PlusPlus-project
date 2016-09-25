#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "stack.h"
using namespace std;
using namespace cop4530;

bool checkOperator(string);
bool isVariable(string);
bool checkNumber(string);

/*
string precedence(string a)
{
int precedence = 0;
switch(a)
{
case '+':
precedence = 1;

case '-':
precedence = 1;

case '*':
precedence = 2;

case '/':
precedence = 2;
}
return precedence;
}

string usePrecedence(string a)
{
	int aWeight;
	
	aWeight = precedence(a);		
	return aWeight;
}
*/

void in2post(const vector<string> & myStringVector, Stack<string> & myStack)
{
    Stack<string> Operands; 
   
    string postfix = ""; // used for empty string
    for (unsigned int i=0; i<myStringVector.size(); ++i)
       {
	  if( checkOperator(myStringVector[i]) && myStringVector[i] 
	  != "*" && myStringVector[i]  != "/" ) 
	      {
                 while (!Operands.empty() && Operands.top() != "(" )
		    if( checkOperator(Operands.top() ) && Operands.top()  
		    != "*" && Operands.top() != "/" )
		    {
		       //do nothing
		       break;
		    }
		    else
		    {
		       myStack.push(Operands.top() );
		       Operands.pop();
		    }
		       Operands.push(myStringVector[i]);
              }
	  else if ( checkOperator(myStringVector[i]) && myStringVector[i] 
	  != "+" && myStringVector[i] != "-")
	  {
		  while (!Operands.empty() && Operands.top() != "(" )  
                    if(( checkOperator(Operands.top() ) && ( Operands.top()  
		    == "+" || Operands.top() == "*" ) ) )
	            {
		       // do nothing
	        	break;
	            }
      		    else
         	    {
			myStack.push(Operands.top() );
			Operands.pop();
		    }
			Operands.push(myStringVector[i]);
	}
	else if (myStringVector[i] == "(" )
	{
	   Operands.push(myStringVector[i]);
	}
	   else if (myStringVector[i] == ")" )
	{
	while (Operands.top() != "(" )
	{
  	   myStack.push(Operands.top() );
	   Operands.pop();
	}
	Operands.pop();	
	}
	else
	myStack.push(myStringVector[i]);
   }
	while(Operands.empty() == false)
        {
           myStack.push(Operands.top() );
           Operands.pop();
        }    
}


void evaluate(Stack<string> & myStack)
{
int counterOperator = 0;
int counterVariable = 0;
int counterr = 0;
int leftParen = 0;
int rightParen = 0;
int argument = 0;
float holdAnswer = 0;

	stringstream ssValue;
	Stack<string> myTemp;
	string holdMyValue;

	float value1 = 0;
	float value2 = 0;
	float holdValue = 0;

	myStack.print(ssValue, ' ');

	while(ssValue >> holdMyValue)
	{
	   if(checkOperator(holdMyValue))
	   {
	      counterOperator++;
	      value1 = stof(myTemp.top());
              myTemp.pop();
	      value2 = stof(myTemp.top());
	      myTemp.pop();
		if(holdMyValue == "+")
		holdValue = value1 + value2;
		if(holdMyValue == "-")
		holdValue = value1 - value2;
		if(holdMyValue == "*")
		holdValue = value1 * value2;
		if(holdMyValue == "/")
               	holdValue = value1 / value2;		
		}
		 else if(checkNumber(holdMyValue))
		 {
		 counterVariable++;
		myTemp.push(holdMyValue);
		}
		else if(isVariable(holdMyValue))
		{
		//counterVariable++;
		cout << myStack << endl;
		counterr++;
		//cout << "It can not be evaluated ";
		break;
		}
		else if( holdMyValue == "(" )
		leftParen++;
		else if( holdMyValue == ")" )
		rightParen++;
		else
		argument++;

	        holdAnswer = value1 + value2; 
		myTemp.push(to_string(holdAnswer));	
	}

	if(counterVariable > counterOperator + 1)
	{
	   cout << "Invalid expression! Too many variables! ";
	}
	else if(counterVariable <= counterOperator)
	{
	   cout << "Invalid expression! Too many operators! ";
	}
	   else if(argument != 0)
	{
	   cout << "Invalid expression! Unrecognized token! ";
	   counterr++;
	}
	   else if(leftParen != rightParen)
	{
	   counterr++;
	   cout << "Invalid expression! Parentheses do not match! ";
	}
	else
	{
	   if(counterr == 0)
	   cout << holdAnswer;
	else
	{ 
	   // do nothing
	}
	}
	   myTemp.clear();
}

bool isVariable(string s)
{
   int counter = 0;
   for(unsigned int i = 0; i < s.length(); i++ )
   {
      if( ( isalpha(s[i])) || (isdigit(s[i])) ||  (s[i] == '_') ) 
      { 
      //do nothing
      }
      else
      counter++;
   }
   
   if(counter == 0)
   return true;
   else
   return false;
}

bool checkOperator(string op)
{
   if(op == "+")
   return true;
   else if(op == "-")
   return true;
   else if(op == "*")
   return true;
   else if(op == "/")
   return true;
   else 
   return false;
}

bool checkNumber(string num)
{
int counter = 0;
   for(unsigned int i = 0; i < num.length(); i++)
   {
      if(num[i] == '.' || isdigit(num[i]) )
      {
	// do nothing
      }
      else
      counter++;
   }
      if(counter == 0 )
      return true;
      else
      return false;
}

int main()
{
   int a = 0;
   Stack<string> infix;
   Stack<string> postfix;
   string input = "";
   string post;
   string hold2;
   vector<string> holdVectorValue;

   while(getline(cin,input) && a == 0 )
   {
      a = 0;

      if(input == "exit")
      a++;
      else
      {
         stringstream ssValue(input);
         string holdMyValue;
       while(ssValue >> holdMyValue)
       {
       holdVectorValue.push_back(holdMyValue);
	}	

	in2post(holdVectorValue, postfix);

	cout << "Postfix expression: ";
	cout << postfix << endl;

	cout << "Postfix evaluation: ";
	cout << postfix << " = ";
	evaluate(postfix);
	cout << "\n";
	cout << "Enter infix expression (\"exit\" to quit): " << endl;

	postfix.clear();
	holdVectorValue.clear();	
	}	
}
return 0;
}
