#pragma once
#include "preProcess.h"

using namespace std;

const string reserveword[13] = { "if","while","int","double","main","float","char","do","else","return","cout","cin","printf" };

struct token
{
	string type;
	string name;
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


	void setToken(string T,string S);
	void setConslToken(string T, string S, int pos);
	void setIdToken(string T, string S, int pos);
	void setStringToken(string T, string S, int pos);
	void setDelimiterToken(string T, string S, int pos);
	void setKeywordToken(string T, string S, int pos);
	void popConslToken();
	void popIdToken();
	void popStringToken();
	void popDelimiterToken();
	void popKeywordToken();
	void insertConslToken(vector<constant> &ex);
	void insertIdToken(vector<identy> &ex);
	void insertStringToken(vector<symbolString> &ex);
	void insertDelimiterToken(vector<del> &ex);
	void insertKeywordToken(vector<key> &ex);

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

scannerToken scanner();
