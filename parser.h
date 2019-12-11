#pragma once
#include"table.h"
#include<map>
#include<stack>
#include<string>
#include<vector>
#include<iostream>
struct production         //产生式
{
	map<char, string> pro;
};
struct check
{
	bool flag;
	production pro;
};
class gammer
{
public:
	gammer();

	~gammer();
private:
	vector<string> ter;		//终结符
	vector<char> notTer;	//非终结符
	map<char, string> pro;	//产生式
};

class parserTable
{
public:
	parserTable();
	void getsynl();
	void creatParserTable();
	void getParserTable();
	check checkList(string cur, string top);	//查表返回true or false与产生式
	stack<char> getSynStack();
	stack<char> getSemStack();
	~parserTable();
private:
	stack<char> synStack;	//分析栈
	stack<char> semStack;	//语义栈
	map<production, string> parserList;	//分析表(产生式，终结符)

};

class LL1Parser
{
public:
	LL1Parser();

	~LL1Parser();

private:
	
	
};

LL1Parser::LL1Parser()
{

}

LL1Parser::~LL1Parser()
{

}

