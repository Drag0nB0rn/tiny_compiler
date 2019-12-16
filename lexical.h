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
	void getToken();
	void getConslToken();
	void getIdToken();
	void getStringToken();
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

void scannerToken::getConslToken()
{

}

void scannerToken::getIdToken()
{

}

void scannerToken::getStringToken()
{

}

void scannerToken::getToken()
{

}

void concat();

bool isNum(char c);

bool isAlpha(char c);

bool underline(char  c);

int reserve(string s);

void retract(FILE *fp);

void getChar(FILE *fp);
