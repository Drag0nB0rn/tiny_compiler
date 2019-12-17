#pragma once
#include <SDKDDKVer.h> // 包括 SDKDDKVer.h 将定义可用的最高版本的 Windows 平台。
#include<string>
#include<vector>
#include<map>
using namespace std;

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
	vector<token> getToken()
	{
		return tableScanner;
	}
	vector<constant> getConslToken()
	{
		return conslToken;
	}
	vector<identy> getIdToken()
	{
		return idToken;
	}
	vector<symbolString> getStringToken()
	{
		return stringToken;
	}
	vector<del>getDelimiterToken()
	{
		return delimiterToken;
	}
	vector<key>getKeywordToken();


	void setToken(string T, string S, int pos);
	void setConslToken(string T, string S, int pos);
	void setIdToken(string T, string S, int pos);
	void setStringToken(string T, string S, int pos);
	void setDelimiterToken(string T, string S, int pos);
	void setKeywordToken(string T, string S, int pos);
	void insId(string a, string b, int c)
	{
		identy t;
		t.name = a;
		t.type = b;
		t.position = c;
		idToken.push_back(t);
	}
	void insToken(string a, string b, int c)
	{
		token t;
		t.name = a;
		t.type=b;
		t.position = c;
		tableScanner.push_back(t);
	}

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
