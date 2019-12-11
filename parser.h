#pragma once
#include"table.h"
#include<map>
#include<stack>
#include<string>
#include<vector>
#include<iostream>
typedef struct production         //产生式
{
	//map<char, string> pro;
	/*production(char t1, string t2)
	{
		pro[t1] = t2;
	}*/
	char left;
	string right;
};
typedef struct check
{
	bool flag;
	//map<char, string> production;
	production p;
};

class parserTable
{
public:

	void getToken();		//获取token
	void creatParserList();	//建立分析表
	bool isTer(string c);
	bool isNotTer(char c);
	check checkList(string cur);	//查表返回true or false与产生式
	stack<char> getSynStack();
	stack<char> getSemStack();
private:
	vector<string> terTable;
	vector<char> notTerTable;
	vector<production> pro; //产生式
	stack<char> synStack;	//分析栈
	stack<char> semStack;	//语义栈
	map<string,production>parserList; //分析表(当前符，产生式)
};