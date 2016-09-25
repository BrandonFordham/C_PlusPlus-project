/* DISCLAIMER: The majority of this code was taken directly out of the textbook/slides for COP4530 
 Data Structures and Algorithm Analysis In C++ fourth edition and Dr. Duan lecture slides
I do not claim credit for anything that was copied verbatim!
*/
template <typename T>
List<T>::const_iterator::const_iterator(): current { nullptr } { }

//The const_iterator increment and decrement

template <typename T>
const T&  List<T>::const_iterator::operator*() const
{
	return retrieve();
}

template <typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator++()
{
	current = current->next;
	return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int)
{
	const_iterator old = *this;
	++( *this );
	return old;
}

template <typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator--()
{
	current = current->prev;
	return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int)
{
	const_iterator old = *this;
	--( *this );
	return old;
}

//comparison and inequality operators

template <typename T>
bool List<T>::const_iterator::operator==(const List<T>::const_iterator & rhs ) const
{
	return current == rhs.current;
}

template <typename T>
bool List<T>::const_iterator::operator!=( const List<T>::const_iterator & rhs )
const
{
	return !( *this == rhs );
}

template <typename T>
T& List<T>::const_iterator::retrieve() const
{
	return current->data;
}

template <typename T>
List<T>::const_iterator::const_iterator( Node *p ): current { p } { }

template <typename T>
T& List<T>::iterator::operator* ()
{
	return const_iterator::retrieve();
}

template <typename T>
const T& List<T>::iterator::operator* () const
{
	return const_iterator::operator*();
}

//iterator increment and decrement operators

template <typename T>
typename List<T>::iterator & List<T>::iterator::operator++()
{
	this->current = this->current->next;
	return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator++ ( int )
{
	iterator old = *this;
	++( *this );
	return old;
}

template <typename T>
typename List<T>::iterator & List<T>::iterator::operator--()
{
	this->current = this->current->prev;
	return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator-- (int)
{
	iterator old = *this;
	--( *this );
	return old;
}

template <typename T>
List<T>::iterator::iterator( Node *p ): const_iterator { p } { }

template <typename T>
List<T>::List()			//constructor
{
	init(); //init() initializes the basic values making a doubly link list
}

template <typename T>
List<T>::iterator::iterator() {}

template <typename T>
List<T>::~List()
{
	clear();			//destructor
	delete head;
	delete tail;
}

template <typename T>
List<T>::List( const List & rhs )  		//copy constructor
{
	init();
	for( auto & x : rhs )
	  push_back( x );
}

template <typename T>
const List<T> & List<T>::operator=( const List & rhs ) //copy assign operator=
{
	List copy = rhs;
	std::swap( *this, copy );
	return *this;
}

template <typename T>
List<T>::List( List && rhs ): 
theSize{ rhs.theSize }, head{ rhs.head }, tail{ rhs.tail } //move constructor
{
	rhs.theSize = 0;
	rhs.head = nullptr;
	rhs.tail = nullptr;
}

template <typename T>
List<T>& List<T>::operator=( List && rhs )  // move assign operator=
{
	std::swap( theSize, rhs.theSize );
	std::swap( head, rhs.head );
	std::swap( tail, rhs.tail );
	return *this;
}


template <typename T>
typename List<T>::iterator List<T>::begin()
{
	return iterator ( head->next );
}

template <typename T>
typename List<T>::const_iterator List<T>::begin() const
{
	return const_iterator( head->next );
}

template <typename T>
typename List<T>::iterator List<T>::end()
{
	return iterator( tail );
}

template <typename T>
typename List<T>::const_iterator List<T>::end() const
{
	return const_iterator( tail ); 
}

//List functions


template <typename T>
int List<T>::size() const
{
	return theSize;
}

template <typename T>
bool List<T>::empty() const
{
	return size() == 0;
}

template <typename T>
void List<T>::clear()
{
	while(!empty())
	  pop_front();
}

template <typename T>
T& List<T>::front()
{
	return *begin(); 
}

template <typename T>
const T& List<T>::front() const
{
	return *begin(); 
}

template <typename T>
T& List<T>::back()
{
	return *--end();
}

template <typename T>
const T& List<T>::back() const
{
	return *--end();
}

template <typename T>
void List<T>::push_front( const T & x)
{
	insert( begin(), x );
}

template <typename T>
void List<T>::push_back( const T & x )
{
	insert( end(), x );
}

template <typename T>
void List<T>::push_front( T && x)
{
	insert( begin(), std::move( x ) );
}

template <typename T>
void List<T>::push_back( T && x )
{
	insert( end(), std::move( x ) );
}

template <typename T>
void List<T>::pop_front()
{
	erase( begin() );
}

template <typename T>
void List<T>::pop_back()
{
	erase( --end() );
}

template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, const T & x)
{
	Node *p = itr.current;
	++theSize;
	return iterator( p->prev = p->prev->next = new Node{ x, p->prev, p } );
}

template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, T&& x)
{
Node *p = itr.current;
++theSize;
return iterator( p->prev = p->prev->next = new Node { std::move( x ), p->prev, p } );
}

template <typename T>
typename List<T>::iterator List<T>::erase(iterator itr)
{
	Node *p = itr.current;
	iterator retVal(p->next);
	p->prev->next = p->next;
	p->next->prev = p->prev;
	delete p;
	--theSize;
	return retVal;

}

template <typename T>
typename List<T>::iterator List<T>::erase(iterator from, iterator to)
{
	for( iterator itr = from; itr != to; )
	   itr = erase( itr );

	return to;
}
template <typename T>
bool operator==(const List<T> & lhs, const List<T> & rhs)
{	
auto itr_lhs = lhs.begin();
auto itr_rhs = rhs.begin();

	if( lhs.size() != rhs.size() )
	return false;
	else
	{
		while ( itr_lhs != lhs.end() )
	   	{
			if(*itr_lhs != *itr_rhs)
		           return false;
			if(*itr_lhs == *itr_rhs)
		   	{
			   itr_lhs++;
			   itr_rhs++;
		   	}
	   	}
	}	
	return true;
}

template <typename T>
bool operator !=(const List<T> & lhs, const List<T> &rhs)
{
int i = 0;
auto itr_lhs = lhs.begin();
auto itr_rhs = rhs.begin();
// Checks for the size and then for equalities
	if( lhs.size() == rhs.size() )
	   {
		while( lhs.begin() != lhs.end() )
		{
			if(*itr_lhs == *itr_rhs)
			i++;

			itr_lhs++;
			itr_rhs++;
		}
	   }
	   if(i == lhs.size() ) //if i gets incremented, it is fale
	      return false;
	   else
	      return true;
}

template <typename T>
void List<T>::reverse()
{	//current hold takes the value that would otherwise be overwritten
int k = 0;
	Node *hold_head = head;
	Node *current = head;
        Node *current_hold = nullptr;

	while(current != nullptr)
	{
		if(k == 0)
		{
			k++;
			current = current->next;
		}
		else
		{
			current_hold = current->prev;
			current->prev = current->next;
			current->next = current_hold;
			current = current->prev;
		}
	}
	head = tail;
	tail = hold_head;

}

template <typename T>
void List<T>::print(std::ostream & os, char ofc) const 
{ //does the actual printing
	for ( auto itr = begin(); itr != end(); ++itr )
	   os << *itr << ofc;
}

template <typename T>
std::ostream & operator<<(std::ostream &os, const List<T> &l)
{
	l.print(os);	//calls the object and prints
	return os;
}

template <typename T>
void List<T>::remove(const T &val)
{

	for ( auto itr = begin(); itr != end(); ++itr)
	   {
		if(*itr == val )
		   {
			erase( itr );
		   }
	   }

}

template <typename T>
List<T>::List(int num, const T& val)
{ 
	init();	
	for( int i = 0; i < num; i++)
		push_back(val);
}

template <typename T>
List<T>::List(const_iterator start, const_iterator end)
{
        init();
	for ( auto itr = start; itr != end; ++itr )
		push_back(*itr);
}

template <typename T>
void List<T>::init() //
{
	theSize = 0;
	head = new Node;
	tail = new Node;
	head->next = tail;
	tail->prev = head;
}

