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

void concat()
{
	strToken += CH;
}

bool isNum(char c)
{
	if ((c >= '0') && (c <= '9'))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isAlpha(char c)
{
	if ((c >= 'a') && (c <= 'z') || (c >= 'A') && (c <= 'Z'))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool underline(char  c)
{
	if (c == '_')
	{
		return true;
	}
	else
	{
		return false;
	}
}

int reserve(string s)
{
	int m, flag = 13;
	for (int i = 0; i < 13; i++)
	{
		m = s.compare(reserveword[i]);
		if (m == 0)
		{
			flag = i;
		}
	}
	return flag;
}

void retract(FILE *fp)
{
	CH = ' ';
	fseek(fp, -1, SEEK_CUR);
}

void getChar(FILE *fp)
{
	CH = getc(fp);
}
