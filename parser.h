#pragma once
#include"lexical.h"
#include<map>
#include<stack>
#include<string>
#include<vector>
#include<iostream>
using namespace std;
typedef struct production         //产生式
{
	string left;
	string right;
};
typedef struct check
{
	bool flag;
	//map<char, string> production;
	int proIndex; //产生式序号
};

class parserTable
{
public:

	void getToken();		//获取token
	production getProduction(int index);   //获取产生式
	void creatProduction(); //写入产生式
	void travelProduction(); //遍历
	void ins(string left, string right);
	void insL(int key, string value);
	void creatParserList();	//建立分析表
	void creatTerTable();
	void creatNotTerTable();
	void printSynStack();
	bool isTer(string c);
	bool isNotTer(string c);
	bool isConstant(string cur);		//当前符是否在常数表中
	bool isString(string cur);		//同上
	bool isIdtifier(string cur);	//同上
	bool isKeyword(string cur);		//同上
	bool isDelimiter(string cur);
	bool LL1Parser();
	bool match(string cur, string top);   //eg：cur="1"，top="i"; i代表常数，match("1","i")==true;
	string getNextCur();
	string getNext(vector<token> Token);
	check checkList(string cur, string top);	//查表返回true or false与产生式序号
	stack<string> getSynStack();
	stack<string> getSemStack();
private:
	vector<string> t5;
	vector<string> terTable;	//终结符表
	vector<string> notTerTable;	//非终结符表
	vector<production> pro; //产生式
	stack<string> synStack;	//分析栈
	stack<string> semStack;	//语义栈
	map<int, vector<string>>parserList; //分析表(产生式序号，终结符集) 一个产生式可推出多个终结符，因此map的值用vector<string>存储
	string cur;	//当前符
	string token1[6] = { "char","a","#" };
	int p_token = 0;
	int p = 0;
};
