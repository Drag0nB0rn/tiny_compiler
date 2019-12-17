#pragma once
#include <SDKDDKVer.h> // 包括 SDKDDKVer.h 将定义可用的最高版本的 Windows 平台。
#include "preProcess.h"
#include "table.h"

using namespace std;

char CH;
string strToken = "";

const string reserveword[13] = { "if","while","int","double","main","float","char","do","else","return","cout","cin","printf" };

struct token
{
	string type;
	string name;
	int position;
};

struct identy
{
	string type;
	string name;
	int position;
};

struct constant
{
	string type;
	string name;
	int position;
};

struct symbolString
{
	string type;
	string name;
	int position;
};

struct key
{
	string type;
	string name;
	int position;
};

struct del
{
	string type;
	string name;
	int position;
};

class scannerToken
{
public:
	vector<token> getToken();
	vector<constant> getConslToken();
	vector<identy> getIdToken();
	vector<symbolString> getStringToken();
	vector<del>getDelimiterToken();
	vector<key>getKeywordToken();


	void setToken(string T,string S,int pos);
	void setConslToken(string T, string S, int pos);
	void setIdToken(string T, string S, int pos);
	void setStringToken(string T, string S, int pos);
	void setDelimiterToken(string T, string S, int pos);
	void setKeywordToken(string T, string S, int pos);

private:
	vector<token> tableScanner;
	vector<constant> conslToken;
	vector<identy> idToken;
	vector<symbolString> stringToken;
	vector<del> delimiterToken;
	vector<key> keywordToken;
};



void concat();

bool isNum(char c);

bool isAlpha(char c);

bool underline(char  c);

int reserve(string s);

void retract(FILE *fp);

void getChar(FILE *fp);

void scanner();
