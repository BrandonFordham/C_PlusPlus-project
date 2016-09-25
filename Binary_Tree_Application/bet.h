#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <sstream>
#include <algorithm>
//#include <ctype.h>
#include <cctype>
using namespace std;




class BET
{

public:
BET();
BET(const string postfix);
BET(const BET & );
~BET();
bool buildFromPostfix(const string postfix);
const BET & operator=(const BET & );
void printInfixExpression();
void printPostfixExpression();
size_t size();
size_t leaf_nodes();
bool empty();

struct BinaryNode
{
string element;
BinaryNode *left;
BinaryNode *right;

BinaryNode(const string & theElement = string{}, BinaryNode *lt = 0, BinaryNode *rt = 0)
:element{theElement}, left{lt}, right{rt} {}

BinaryNode(string && theElement, BinaryNode * lt, BinaryNode *rt)
:element{std::move(theElement)}, left{lt}, right{rt} {}
};

private:

BinaryNode * root;

void printInfixExpression(BinaryNode * n);
void makeEmpty(BinaryNode* &t);
BinaryNode * clone(BinaryNode *t) const;
void printPostfixExpression(BinaryNode * n);
size_t size(BinaryNode * t);
size_t leaf_nodes(BinaryNode * t);





};

#include "bet.hpp"

