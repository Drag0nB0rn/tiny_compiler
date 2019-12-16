#pragma once
#include <SDKDDKVer.h> // 包括 SDKDDKVer.h 将定义可用的最高版本的 Windows 平台。
#include "preProcess.h"

using namespace std;

char CH;
string strToken = "";

class scannerToken
{
public:
	void getToken();
	scannerToken();
	~scannerToken();
private:
	vector<vector<string>> tableScanner;
};

scannerToken::scannerToken();


scannerToken::~scannerToken();


void concat();

bool isNum(char c);


bool isAlpha(char c);

bool underline(char  c);

int reserve(string s);

void retract(FILE *fp);
