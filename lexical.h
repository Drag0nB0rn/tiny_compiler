#pragma once
#include <SDKDDKVer.h> // 包括 SDKDDKVer.h 将定义可用的最高版本的 Windows 平台。
#include "preProcess.h"

using namespace std;

char CH;
string strToken = "";

const string reserveword[13] = { "if","while","int","double","main","float","char","do","else","return","cout","cin","printf" };

class scannerToken
{
public:
	vector<vector<string>> getToken();
	vector<string> getConslToken();
	vector<string> getIdToken();
	vector<string> getStringToken();

	void setToken(vector<vector<string>> table);
	void setConslToken(vector<string> consl);
	void setIdToken(vector<string> id);
	void setStringToken(vector<string> string);

	scannerToken();
	~scannerToken();
private:
	vector<vector<string>> tableScanner;
	vector<string> conslToken;
	vector<string> idToken;
	vector<string> stringToken;
};

scannerToken::scannerToken()
{
	for (int i = 0; i < 25; i++)
	{
		tableScanner[i].resize(2);
	}
}

scannerToken::~scannerToken()
{
	cout << "token类已被析构" << endl;
}

vector<string> scannerToken::getConslToken()
{
	return conslToken;
}

vector<string> scannerToken::getIdToken()
{

}

vector<string> scannerToken::getStringToken()
{
	return stringToken;
}

vector<vector<string>> scannerToken::getToken()
{
	return tableScanner;
}

void scannerToken::setToken(vector<vector<string>> table)
{
	tableScanner = table;
}

void scannerToken::setConslToken(vector<string> consl)
{
	conslToken = consl;
}

void scannerToken::setIdToken(vector<string> id)
{
	idToken = id;
}

void scannerToken::setStringToken(vector<string> string)
{
	stringToken = string;
}

void concat();

bool isNum(char c);

bool isAlpha(char c);

bool underline(char  c);

int reserve(string s);

void retract(FILE *fp);

void getChar(FILE *fp);

void scanner();
