#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <vector>
#include <string>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

class Production {
public:
	Production(char n, char t, string r) :not_ter(n), ter(t), right(r) {};
	char not_ter;
	char ter;
	string right;
};

std::vector<Production>  parser_list;
std::vector<Production>  parser_list2;
char not_ter_table[5] = { 'E','A','T','B','F' };
char ter_table[8] = { 'i','+','-','*','/','(',')','#' };
typedef struct
{
	string type;
	int sequence;
}WORD;
char not_ter_Productionle[6] = { 'E','A','T','B','F' };
char input[255];
char token[255] = "";
int p_input;
int p_token;
int p_string = 0;
int p_constant = 0;
int p_identifier = 0;
int parser = 0;
bool flag;
char ch;
string  reserve_table[30] = { "begin","if","then","while","do","for","end","int","main","float","double","else","float","double","return","cout","cin","printf","scanf","EOF","long","endl","string","finish" };
char delimiter_table[100] = { '=','>','<','+','-','*','/','(',')',';',':','\'','\"','{','}','q' };
string constant_table[100];
string identifier_table[100];
string string_table[100];
stack<char> s;
WORD  scanner();
void showidentifier_table();
void showreserve_table();
void showconstant_table();
void showdelimiter_table();
void initidentifier_table();
void initconstant_table();
void showstring_table();

void E();
void E1();
void F();
void T();
void T1();
void recursion();

void initparser_list();
void initparser_list2();
void printStack();
bool isTer(char x);
bool isNot_ter(char x);
bool getw(char w);
bool digit(char w);
bool letter(char w);
int LL1();
char getCh();

stack<string> semantic_Stack;
stack<string> syntactic_Stack;
struct qt {
	string w;
	string o1;
	string o2;
	string res;
	qt(string a, string b, string c, string d) :w(a), o1(b), o2(c), res(d) {};
};
vector<qt> QT;
int t_index = 1;


void geq(string w);
