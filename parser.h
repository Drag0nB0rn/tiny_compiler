#pragma once
#include"table.h"
#include<map>
#include<stack>
#include<string>
#include<vector>
#include<iostream>
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
	synbl getNext();		
	production getProduction(int index);   //获取产生式
	void creatProduction(); //写入产生式
	void travelProduction(); //遍历
	void ins(string left,string right);
	void creatParserList();	//建立分析表
	void creatTerTable();
	void creatNotTerTable();
	void printSynStack();
	bool isTer(string c);
	bool isNotTer(string c);
	bool isConstan(string cur);		//当前符是否在常数表中
	bool isString(string cur);		//同上
	bool isIdtifier(string cur);	//同上
	bool isKeyword(string cur);		//同上
	bool LL1Parser();
	bool match(string cur,string top);   //eg：cur="1"，top="i"; i代表常数，match("1","i")==true;
	string getNextCur();
	check checkList(string cur,string top);	//查表返回true or false与产生式序号
	stack<string> getSynStack();
	stack<string> getSemStack();
private:
	vector<string> terTable;	//终结符表
	vector<string> notTerTable;	//非终结符表
	vector<production> pro; //产生式
	stack<string> synStack;	//分析栈
	stack<string> semStack;	//语义栈
	map<int,string>parserList; //分析表(产生式序号，当前符)
	string cur;	//当前符
	string token[6] = { "int","a","#" };
	int p_token = 0;
};
