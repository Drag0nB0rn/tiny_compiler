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
	production getProduction(int index);   //获取产生式
	void creatProduction(); //写入产生式
	void travelProduction(); //遍历
	void creatParserList();	//建立分析表
	bool isTer(string c);
	bool isNotTer(char c);
	check checkList(string cur,string top);	//查表返回true or false与产生式序号
	stack<string> getSynStack();
	stack<string> getSemStack();
private:
	vector<string> terTable;
	vector<char> notTerTable;
	vector<production> pro; //产生式
	stack<string> synStack;	//分析栈
	stack<string> semStack;	//语义栈
	map<int,string>parserList; //分析表(产生式序号，当前符)
};