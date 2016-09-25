#include <iostream>
#include <list>

using namespace std;
using namespace cop4530;


template<typename T>
Stack<T>::Stack()
{

}

template<typename T>
Stack<T>::~Stack()
{

}

template<typename T>
Stack<T>::Stack(const Stack<T> & s)
{
	myList = s.myList;
}

template<typename T>
Stack<T>::Stack(Stack<T> && s)
{
	myList = move(s.myList);
}

//copy assignment operator
template<typename T>
Stack<T> & Stack<T>::operator =(const Stack <T> & s)
{
	myList = s.myList;
	return *this;
}

//move assignment operator
template<typename T>
Stack<T> & Stack<T>::operator =(Stack<T> && s)
{
	myList = move(s.Mylist);
}

template<typename T>
void Stack<T>::push(const T & x)
{
	myList.push_back(x);
}

template<typename T>
void Stack<T>::push(T && x)
{
	myList.push_back(move(x));
}

template<typename T>
void Stack<T>::pop()
{
	myList.pop_back();
}

template<typename T>
T & Stack<T>::top()
{
	return myList.back();
}

template<typename T>
const T& Stack<T>::top() const
{
	return myList.back();
}



template<typename T>
bool Stack<T>::empty() const
{
	return myList.empty();
}

template<typename T>

int Stack<T>::size() const
{
	return myList.size();
}

template<typename T>
void Stack<T>::clear()
{
	myList.clear();
}

template<typename T>
void Stack<T>::print(ostream& os, char ofc) const
{
	for( auto i = myList.begin(); i != myList.end(); ++i)
		os << *i << ofc;
}

template<typename T>
ostream & operator <<(ostream & os, const Stack<T> & s)
{
	s.print(os);
	return os;
}

template<typename T>
bool operator ==(const Stack<T> & l, const Stack<T> & r)
{

int k = 0; //holds value for false

	Stack<T> holdLeft = l;
	Stack<T> holdRight = r;

	if( holdLeft.size() != holdRight.size() )
	return false;
	else
	{
		while(!holdLeft.empty())
		{
			if( holdLeft.top() != holdRight.top() ) 
			k++;
			else
			{
				holdLeft.pop();
				holdRight.pop();
			}
			if(k != 0)
			return false;
		}
	return true;
	}
return true;
}


template<typename T>
bool operator !=(const Stack<T> & l, const Stack<T> & r)
{

	return !(r == l);
}

template<typename T>
bool operator <(const Stack<T> & l, const Stack<T> & r)
{

	Stack<T> holdLeft = l;
	Stack<T> holdRight = r;

if( (holdLeft.size() > holdRight.size() ) && (holdLeft.size() != holdRight.size() ) )
return false;
	while(!holdLeft.empty() )
	{
	if( (holdLeft.top() < holdRight.top()) || (holdLeft.top() == holdRight.top()) )
	{
		holdLeft.pop();
		holdRight.pop();
	}
	else
	return false;
	}
	return true;

return true;
}


