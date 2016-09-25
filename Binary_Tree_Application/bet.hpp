
//These are helper functions
bool isOperator(string);
bool digits(const string & ); 

//constructor
BET::BET()
{
   root = new BinaryNode;
}

//one-param constructor
BET::BET(const string postfix)
{
   root = new BinaryNode;
   buildFromPostfix(postfix);
}

//copy constructor
BET::BET(const BET & a)
{
   root = clone(a.root);
}

//destructor
BET::~BET()
{
   makeEmpty(root);
}

//Learned from new C++11 website
//checks through "a" checking if each iteration is a digit
bool digits(const string & a)
{
 return all_of(a.begin(), a.end(), ::isdigit);
}

bool BET::buildFromPostfix(const string postfix)
{
   bool flag = true;
   unsigned int count = 0;
   vector<string> input;
   stack<BinaryNode*> myStack;
   string hold;
   stringstream ss(postfix);
   
   while( ss >> hold )
      input.push_back(hold);

   while( count < input.size() )
   {
        if(( digits(input[count]) == flag ||( input[count] <= "z" &&
	    input[count] >= "a")) || (input[count] >= "A" && input[count] <= "Z"            )) 
     {
         BinaryNode * node = new BinaryNode(input[count]);
	 myStack.push(node);
      }
      else if( ( (input[count] == "+" || input[count] == "-" ) ||
              ( input[count] == "*" || input[count] == "/")   )  )
      {
         BinaryNode * node = new BinaryNode(input[count]);
	 node->left = myStack.top();
	 myStack.pop();
         
	 node->right = myStack.top();
	 myStack.pop();
	 myStack.push(node);
      }
      else
      {
	cout << "There is an error!! " << endl;
	return false;
      }
   count++;
   }
   root = myStack.top();
   myStack.pop();
   return true;
}

//assignment operator
const BET & BET::operator=(const BET & a)
{
    this->root = clone(a.root);
    return *this;
}

void BET::printInfixExpression()
{
   printInfixExpression(root);
}

void BET::printPostfixExpression()
{
   printPostfixExpression(root);
}

size_t BET::size()
{
 
  return  size(root);
}

size_t BET::leaf_nodes()
{
  
   return leaf_nodes(root);
}

//if root points to nothing, it is empty
bool BET::empty()
{
   if(root == 0)
   return true;
   else
   return false;
}

//checks if x is a operator
bool isOperator(string x )
{
   if(x == "+")
   return true;
   else if(x == "-")
   return true;
   else if(x == "*")
   return true;
   else if(x == "/")
   return true;
   else
   return false;
}

//prints the infix expression
//each if statement is checking for a pattern
//in the binary expression tree for where the parentheses
//needed to be.
void BET::printInfixExpression(BinaryNode *n)
{

bool flag = true;
if(n == 0)
return;
if(( n->element == "*" || n->element == "/") && (isOperator(n->right->element) != flag) 
&& (isOperator(n->left->element) == flag))
cout << "(";


if((n->element == "*" || n->element == "/") && ( n->right->element == "+" || 
n->right->element == "-") && (n->left->element == "*" || n->left->element == "/") )
cout << "(";

if((n->element == "*" || n->element == "/") &&( isOperator(n->left->element) != flag) 
&& (n->right->element == "+" && n->right->element != "-") )
{
cout << "(";
}

if(n->left == 0 && n->right == 0)
cout << n->element << " ";
   else
   {
      printInfixExpression(n->right);

 if((n->element == "*" || n->element == "/") &&( isOperator(n->left->element) != flag)
    && (n->right->element == "+" && n->right->element != "-") )
       cout << ")";

 if((n->element == "*" || n->element == "/") && ( n->right->element == "+" ||
 n->right->element == "-") && (n->left->element == "*" || n->left->element == "/") )
 cout << ")";

      cout << n->element << " ";
     
     if(isOperator(n->element) == flag && isOperator(n->right->element) != flag &&
      isOperator(n->left->element) == flag )
         cout << "(";
    
  printInfixExpression(n->left);
   
   if(isOperator(n->element) == flag && isOperator(n->right->element) != flag &&
      isOperator(n->left->element) == flag )
         cout << ")";
   
   if(( n->element == "*" || n->element == "/") && (isOperator(n->right->element) != flag)
   && (isOperator(n->left->element) == flag))
   cout << ")";
   }
   return;  
}

//deletes each node and makes the root null!
void BET::makeEmpty(BinaryNode * &t)
{
   if(t == 0)
   {
   //job is done already!
   }
   else
   {
      makeEmpty(t->left);
      makeEmpty(t->right);
      delete t;
   }
   t = 0;
}

//clones all the nodes of the param
BET::BinaryNode * BET::clone(BinaryNode *t) const 
{
        if(t != 0)
	return new BinaryNode{ t->element, clone(t->left), clone(t->right)};
	else
	return 0;
}

//prints postfix expression
void BET::printPostfixExpression(BinaryNode * n)
{
   if(n > 0)
   {
      if(n->left == 0 && n->right == 0)
      cout << n->element << " ";
      else
      {
         printPostfixExpression(n->right);
         printPostfixExpression(n->left);
         cout << n->element << " ";
      }  
   }
   
}

//adds up the total size
size_t BET::size(BinaryNode * t)
{

   int null = 0;
   int root = 1;
   if(t == 0)
   return null;
   else if(t->right == 0 && t->left == 0)
   return root;
   else if(t->right == 0)
   {
      return size(t->left) + root;
   }
   else if(t->left == 0)
   {
      return size(t->right) + root;
   }
   else
   {
      return size(t->left) + size(t->right) + root;
   }
}

//adds just the leaf nodes
size_t BET::leaf_nodes(BinaryNode * t)
{
   int null = 0;
   int count = 1;
   if(t == 0)
   return null;
   else if( t->right == 0 && t->left == 0)
   return count;
   else if (t->right == 0)
   return leaf_nodes(t->left);
   else if (t->right == 0)
   return leaf_nodes(t->left);
   else
   return leaf_nodes(t->right) + leaf_nodes(t->left);
}












