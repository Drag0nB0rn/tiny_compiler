#include "lexical.h"
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>

using namespace std;

char CH;
string strToken = "";
int keywordLen = size(reserveword);

vector<constant> scannerToken::getConslToken()
{
	return conslToken;
}

vector<identy> scannerToken::getIdToken()
{
	return idToken;
}

vector<symbolString> scannerToken::getStringToken()
{
	return stringToken;
}

vector<token> scannerToken::getToken()
{
	return tableScanner;
}

vector<key>scannerToken::getKeywordToken()
{
	return keywordToken;
}

vector<del>scannerToken::getDelimiterToken()
{
	return delimiterToken;
}


void scannerToken::setToken(string T, string S)
{
	token table;
	table.type = T;
	table.name = S;
	tableScanner.push_back(table);
}

void scannerToken::setConslToken(string T, string S, int pos)
{
	constant consl;	
	consl.type = T;
	consl.name = S;
	consl.position = pos;
	conslToken.push_back(consl);
}

void scannerToken::setIdToken(string T, string S, int pos)
{
	identy id;	
	id.type = T;
	id.name = S;
	id.position = pos;
	idToken.push_back(id);
}

void scannerToken::setStringToken(string T, string S, int pos)
{
	symbolString string;
	string.type = T;
	string.name = S;
	string.position = pos;
	stringToken.push_back(string);
}

void scannerToken::setDelimiterToken(string T, string S, int pos)
{
	del deli;
	deli.type = T;
	deli.name = S;
	deli.position = pos;
	delimiterToken.push_back(deli);
}

void scannerToken::setKeywordToken(string T, string S, int pos)
{
	key keyWord;
	keyWord.type = T;
	keyWord.name = S;
	keyWord.position = pos;
	keywordToken.push_back(keyWord);
}


void scannerToken::insertConslToken(vector<constant> &ex)
{
	ex.assign(conslToken.begin(), conslToken.end());
}

void scannerToken::insertIdToken(vector<identy> &ex)
{
	ex.assign(idToken.begin(), idToken.end());
}

void scannerToken::insertStringToken(vector<symbolString> &ex)
{
	ex.assign(stringToken.begin(), stringToken.end());
}

void scannerToken::insertDelimiterToken(vector<del> &ex)
{
	ex.assign(delimiterToken.begin(), delimiterToken.end());
}

void scannerToken::insertKeywordToken(vector<key> &ex)
{
	ex.assign(keywordToken.begin(), keywordToken.end());
}


void scannerToken::popConslToken()
{
	conslToken.pop_back();
}

void scannerToken::popIdToken()
{
	idToken.pop_back();
}

void scannerToken::popStringToken()
{
	stringToken.pop_back();
}

void scannerToken::popDelimiterToken()
{
	delimiterToken.pop_back();
}

void scannerToken::popKeywordToken()
{
	keywordToken.pop_back();
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
	int m, flag = keywordLen;
	for (int i = 0; i < keywordLen; i++)
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

int tokenPos = 0, conslPos = 0, idPos = 0, keywordPos = 0, delPos = 0, strPos = 0;

scannerToken scanner()
{
	scannerToken myToken;
	ofstream fc;
	FILE *fp;
	pretxt();
	fc.open("scanner.txt", ios::ate);
	if (!fc.is_open())
	{
		exit(0);
	}
	fp = fopen("preProcess.txt", "r");
	if (fp == NULL)
	{
		exit(0);
	}
	while (!feof(fp))
	{
		strToken.clear();
		getChar(fp);

		if (isAlpha(CH)) //字母，判断关键字和标识符
		{
			int c, flag = -1;
			while (isNum(CH) || isAlpha(CH) || underline(CH))
			{
				concat();
				getChar(fp);
			}
			if (!feof(fp))
			{
				retract(fp);
				c = reserve(strToken);
				if (c < 13)
				{
					myToken.setToken("key", strToken);
					myToken.setKeywordToken("key",strToken, keywordPos++);
					vector<key> example;
					myToken.insertKeywordToken(example);
					if (example.size() > 0)
					{
						for (int i = 0; i<example.size() - 1; i++)
						{
							if (example[i].name == strToken)
							{
								flag = example[i].position;
								break;
							}
						}
					}
					if (flag == -1)
					{
						fc << "<" << "key" << "," << example.back().position << ">" << endl;
						cout << "<" << "key" << "," << example.back().position << ">" << endl;
					}
					else
					{
						myToken.popKeywordToken();
						fc << "<" << "key" << "," << flag <<">"<< endl;
						cout << "<" << "key" << "," << flag <<">"<< endl;
					}
				}
				else
				{
					myToken.setToken("identy", strToken);
					myToken.setIdToken("identy", strToken,idPos++);
					vector<identy> example;
					myToken.insertIdToken(example);

					if (example.size() > 0)
					{
						for (int i = 0; i<example.size() - 1; i++)
						{
							if (example[i].name == strToken)
							{
								flag = example[i].position;
								break;
							}
						}
					}

					if (flag == -1)
					{
						fc << "<" << "identy" << "," << example.back().position << ">" << endl;
						cout << "<" << "identy" << "," << example.back().position << ">" << endl;
					}
					else
					{
						myToken.popIdToken();
						fc << "<" << "identy" << "," << flag <<">"<< endl;
						cout<<"<" << "identy" << "," << flag <<">"<< endl;
					}
				}
			}
			else if (feof(fp))
			{
				c = reserve(strToken);
				if (c < 13)
				{
					myToken.setToken("key", strToken);
					myToken.setKeywordToken("key", strToken, keywordPos++);
					vector<key> example;
					myToken.insertKeywordToken(example);
					if (example.size() > 0)
					{
						for (int i = 0; i<example.size() - 1; i++)
						{
							if (example[i].name == strToken)
							{
								flag = example[i].position;
								break;
							}
						}
					}
					if (flag == -1)
					{
						fc << "<" << "key" << "," << example.back().position << ">" << endl;
						cout << "<" << "key" << "," << example.back().position << ">" << endl;
					}
					else
					{
						myToken.popKeywordToken();
						fc << "<" << "key" << "," << flag << ">" << endl;
						cout << "<" << "key" << "," << flag << ">" << endl;
					}
				}
				else
				{
					myToken.setToken("identy", strToken);
					myToken.setIdToken("identy", strToken, idPos++);
					vector<identy> example;
					myToken.insertIdToken(example);
					if (example.size() > 0)
					{
						for (int i = 0; i<example.size() - 1; i++)
						{
							if (example[i].name == strToken)
							{
								flag = example[i].position;
								break;
							}
						}
					}
					if (flag == -1)
					{
						fc << "<" << "identy" << "," << example.back().position << ">" << endl;
						cout << "<" << "identy" << "," << example.back().position << ">" << endl;
					}
					else
					{
						myToken.popIdToken();
						fc << "<" << "identy" << "," << flag <<">"<< endl;
						cout << "<" << "identy" << "," << flag <<">"<< endl;
					}
				}
			}
		}

		else if (isNum(CH))
		{
			int flag_c = -1, flag_e = -1, flag_f = -1;
			while (isNum(CH))
			{
				concat();
				getChar(fp);
			}
			if (CH == 'e') //判断指数
			{
				concat();
				getChar(fp);
				while (isNum(CH))
				{
					concat();
					getChar(fp);
				}
				if (!feof(fp))
				{
					retract(fp);
					myToken.setConslToken("constant", strToken, conslPos++);
					myToken.setToken("constant", strToken);
					vector<constant> example;
					myToken.insertConslToken(example);
					if (example.size() > 0)
					{
						for (int i = 0; i<example.size() - 1; i++)
						{
							if (example[i].name == strToken)
							{
								flag_e = example[i].position;
								break;
							}
						}
					}
					if (flag_e == -1)
					{
						fc << "<" << "constant" << "," << example.back().position <<">"<< endl;
						cout << "<" << "constant" << "," << example.back().position <<">"<< endl;
					}
					else
					{
						myToken.popConslToken();
						fc << "<" << "constant" << "," << flag_e <<">"<< endl;
						cout << "<" << "constant" << "," << flag_e <<">"<< endl;
					}
				}

				else if (feof(fp))
				{
					myToken.setConslToken("constant", strToken, conslPos++);
					myToken.setToken("constant", strToken);
					vector<constant> example;
					myToken.insertConslToken(example);
					if (example.size() > 0)
					{
						for (int i = 0; i<example.size() - 1; i++)
						{
							if (example[i].name == strToken)
							{
								flag_e = example[i].position;
								break;
							}
						}
					}
					if (flag_e == -1)
					{
						fc << "<" << "constant" << "," << example.back().position <<">"<< endl;
						cout << "<" << "constant" << "," << example.back().position <<">"<< endl;
					}
					else
					{
						myToken.popConslToken();
						fc << "<" << "constant" << "," << flag_e <<">"<< endl;
						cout << "<" << "constant" << "," << flag_e <<">"<< endl;
					}
				}
			}

			else if (CH == '.') //判断小数
			{
				concat();
				getChar(fp);
				while (isNum(CH))
				{
					concat();
					getChar(fp);
				}
				if (!feof(fp))
				{
					retract(fp);
					myToken.setConslToken("constant", strToken, conslPos++);
					myToken.setToken("constant", strToken);
					vector<constant> example;
					myToken.insertConslToken(example);
					if (example.size() > 0)
					{
						for (int i = 0; i<example.size() - 1; i++)
						{
							if (example[i].name == strToken)
							{
								flag_f = example[i].position;
								break;
							}
						}
					}
					if (flag_f == -1)
					{
						fc << "<" << "constant" << "," << example.back().position <<">" <<endl;
						cout << "<" << "constant" << "," << example.back().position <<">"<< endl;
					}
					else
					{
						myToken.popConslToken();
						fc << "<" << "constant" << "," << flag_f <<">"<< endl;
						cout << "<" << "constant" << "," << flag_f <<">"<< endl;
					}
				}

				else if (feof(fp))
				{
					myToken.setConslToken("constant", strToken, conslPos++);
					myToken.setToken("constant", strToken);
					vector<constant> example;
					myToken.insertConslToken(example);
					if (example.size() > 0)
					{
						for (int i = 0; i<example.size() - 1; i++)
						{
							if (example[i].name == strToken)
							{
								flag_f = example[i].position;
								break;
							}
						}
					}
					if (flag_f == -1)
					{
						fc << "<" << "constant" << "," << example.back().position <<">"<< endl;
						cout << "<" << "constant" << "," << example.back().position <<">"<< endl;
					}
					else
					{
						myToken.popConslToken();
						fc << "<" << "constant" << "," << flag_f <<">"<< endl;
						cout << "<" << "constant" << "," << flag_f <<">"<< endl;
					}
				}
			}

			else  //判断整数
			{
				if (!feof(fp))
				{
					retract(fp);
					myToken.setConslToken("constant", strToken, conslPos++);
					myToken.setToken("constant", strToken);
					vector<constant> example;
					myToken.insertConslToken(example);
					if (example.size() > 0)
					{
						for (int i = 0; i<example.size() - 1; i++)
						{
							if (example[i].name == strToken)
							{
								flag_c = example[i].position;
								break;
							}
						}
					}
					if (flag_c == -1)
					{
						fc << "<" << "constant" << "," << example.back().position <<">"<< endl;
						cout << "<" << "constant" << "," << example.back().position <<">"<< endl;
					}
					else
					{
						myToken.popConslToken();
						fc << "<" << "constant" << "," << flag_c <<">"<< endl;
						cout << "<" << "constant" << "," << flag_c <<">"<< endl;
					}
				}

				else if (feof(fp))
				{
					myToken.setConslToken("constant", strToken, conslPos++);
					myToken.setToken("constant", strToken);
					vector<constant> example;
					myToken.insertConslToken(example);
					if (example.size() > 0)
					{
						for (int i = 0; i<example.size() - 1; i++)
						{
							if (example[i].name == strToken)
							{
								flag_c = example[i].position;
								break;
							}
						}
					}
					if (flag_c == -1)
					{
						fc << "<" << "constant" << "," << example.back().position <<">"<< endl;
						cout << "<" << "constant" << "," << example.back().position <<">"<< endl;
					}
					else
					{
						myToken.popConslToken();
						fc << "<" << "constant" << "," << flag_c <<">"<< endl;
						cout << "<" << "constant" << "," << flag_c <<">"<< endl;
					}
				}
			}
		}

		else if (CH == '-')
		{		
			getChar(fp);
			if (isNum(CH))
			{
				int flagNe = -1, flagNc = -1, flagNf = -1;
				retract(fp);
				retract(fp);
				if (ftell(fp) == 0)
				{
					getChar(fp);
					concat();
					getChar(fp);
					while (isNum(CH))
					{
						concat();
						getChar(fp);
					}
					if (CH == 'e') //判断负指数
					{
						concat();
						getChar(fp);
						while (isNum(CH))
						{
							concat();
							getChar(fp);
						}
						if (!feof(fp))
						{
							retract(fp);
							myToken.setConslToken("constant", strToken, conslPos++);
							myToken.setToken("constant", strToken);
							vector<constant> example;
							myToken.insertConslToken(example);
							if (example.size() > 0)
							{
								for (int i = 0; i<example.size() - 1; i++)
								{
									if (example[i].name == strToken)
									{
										flagNe = example[i].position;
										break;
									}
								}
							}
							if (flagNe == -1)
							{
								fc << "<" << "constant" << "," << example.back().position <<">"<< endl;
								cout << "<" << "constant" << "," << example.back().position <<">"<< endl;
							}
							else
							{
								myToken.popConslToken();
								fc << "<" << "constant" << "," << flagNe <<">"<< endl;
								cout << "<" << "constant" << "," << flagNe <<">"<< endl;
							}
						}
					}

					else if (CH == '.')//判断负小数
					{
						concat();
						getChar(fp);
						while (isNum(CH))
						{
							concat();
							getChar(fp);
						}
						if (!feof(fp))
						{
							retract(fp);
							myToken.setConslToken("constant", strToken, conslPos++);
							myToken.setToken("constant", strToken);
							vector<constant> example;
							myToken.insertConslToken(example);
							if (example.size() > 0)
							{
								for (int i = 0; i<example.size() - 1; i++)
								{
									if (example[i].name == strToken)
									{
										flagNf = example[i].position;
										break;
									}
								}
							}
							if (flagNf == -1)
							{
								fc << "<" << "constant" << "," << example.back().position <<">"<< endl;
								cout << "<" << "constant" << "," << example.back().position <<">"<< endl;
							}
							else
							{
								myToken.popConslToken();
								fc << "<" << "constant" << "," << flagNf <<">"<< endl;
								cout << "<" << "constant" << "," << flagNf <<">"<< endl;
							}
						}

						else if (feof(fp))
						{
							myToken.setConslToken("constant", strToken, conslPos++);
							myToken.setToken("constant", strToken);
							vector<constant> example;
							myToken.insertConslToken(example);
							if (example.size() > 0)
							{
								for (int i = 0; i<example.size() - 1; i++)
								{
									if (example[i].name == strToken)
									{
										flagNf = example[i].position;
										break;
									}
								}
							}
							if (flagNf == -1)
							{
								fc << "<" << "constant" << "," << example.back().position <<">"<< endl;
								cout << "<" << "constant" << "," << example.back().position <<">"<< endl;
							}
							else
							{
								myToken.popConslToken();
								fc << "<" << "constant" << "," << flagNf <<">"<< endl;
								cout << "<" << "constant" << "," << flagNf <<">"<< endl;
							}
						}
					}

					else //判断负整数
					{
						if (!feof(fp))
						{
							retract(fp);
							myToken.setConslToken("constant", strToken, conslPos++);
							myToken.setToken("constant", strToken);
							vector<constant> example;
							myToken.insertConslToken(example);
							if (example.size() > 0)
							{
								for (int i = 0; i<example.size() - 1; i++)
								{
									if (example[i].name == strToken)
									{
										flagNc = example[i].position;
										break;
									}
								}
							}
							if (flagNc == -1)
							{
								fc << "<" << "constant" << "," << example.back().position <<">"<< endl;
								cout << "<" << "constant" << "," << example.back().position <<">"<< endl;
							}
							else
							{
								myToken.popConslToken();
								fc << "<" << "constant" << "," << flagNc <<">"<< endl;
								cout << "<" << "constant" << "," << flagNc <<">"<< endl;
							}
						}

						else if (feof(fp))
						{
							myToken.setConslToken("constant", strToken, conslPos++);
							myToken.setToken("constant", strToken);
							vector<constant> example;
							myToken.insertConslToken(example);
							if (example.size() > 0)
							{
								for (int i = 0; i<example.size() - 1; i++)
								{
									if (example[i].name == strToken)
									{
										flagNc = example[i].position;
										break;
									}
								}
							}
							if (flagNc == -1)
							{
								fc << "<" << "constant" << "," << example.back().position <<">"<< endl;
								cout << "<" << "constant" << "," << example.back().position <<">"<< endl;
							}
							else
							{
								myToken.popConslToken();
								fc << "<" << "constant" << "," << flagNc <<">"<< endl;
								cout << "<" << "constant" << "," << flagNc <<">"<< endl;
							}
						}
					}
				}
				else if (ftell(fp) != 0)
				{
					retract(fp);
					getChar(fp);
					if ((!isNum(CH)) && (!isAlpha(CH)) && (!underline(CH)))
					{
						getChar(fp);
						concat();
						getChar(fp);
						while (isNum(CH))
						{
							concat();
							getChar(fp);
						}
						if (CH == 'e') //判断负指数
						{
							concat();
							getChar(fp);
							while (isNum(CH))
							{
								concat();
								getChar(fp);
							}
							if (!feof(fp))
							{
								retract(fp);
								myToken.setConslToken("constant", strToken, conslPos++);
								myToken.setToken("constant", strToken);
								vector<constant> example;
								myToken.insertConslToken(example);
								if (example.size() > 0)
								{
									for (int i = 0; i<example.size() - 1; i++)
									{
										if (example[i].name == strToken)
										{
											flagNe = example[i].position;
											break;
										}
									}
								}
								if (flagNe == -1)
								{
									fc << "<" << "constant" << "," << example.back().position <<">"<< endl;
									cout << "<" << "constant" << "," << example.back().position <<">"<< endl;
								}
								else
								{
									myToken.popConslToken();
									fc << "<" << "constant" << "," << flagNe <<">"<< endl;
									cout << "<" << "constant" << "," << flagNe <<">"<< endl;
								}
							}
						}

						else if (CH == '.')//判断负小数
						{
							concat();
							getChar(fp);
							while (isNum(CH))
							{
								concat();
								getChar(fp);
							}
							if (!feof(fp))
							{
								retract(fp);
								myToken.setConslToken("constant", strToken, conslPos++);
								myToken.setToken("constant", strToken);
								vector<constant> example;
								myToken.insertConslToken(example);
								if (example.size() > 0)
								{
									for (int i = 0; i<example.size() - 1; i++)
									{
										if (example[i].name == strToken)
										{
											flagNf = example[i].position;
											break;
										}
									}
								}
								if (flagNf == -1)
								{
									fc << "<" << "constant" << "," << example.back().position <<">"<< endl;
									cout << "<" << "constant" << "," << example.back().position <<">"<< endl;
								}
								else
								{
									myToken.popConslToken();
									fc << "<" << "constant" << "," << flagNf <<">"<< endl;
									cout << "<" << "constant" << "," << flagNf <<">"<< endl;
								}
							}

							else if (feof(fp))
							{
								myToken.setConslToken("constant", strToken, conslPos++);
								myToken.setToken("constant", strToken);
								vector<constant> example;
								myToken.insertConslToken(example);
								if (example.size() > 0)
								{
									for (int i = 0; i<example.size() - 1; i++)
									{
										if (example[i].name == strToken)
										{
											flagNf = example[i].position;
											break;
										}
									}
								}
								if (flagNf == -1)
								{
									fc << "<" << "constant" << "," << example.back().position <<">"<< endl;
									cout << "<" << "constant" << "," << example.back().position <<">"<< endl;
								}
								else
								{
									myToken.popConslToken();
									fc << "<" << "constant" << "," << flagNf <<">"<< endl;
									cout << "<" << "constant" << "," << flagNf <<">"<< endl;
								}
							}
						}

						else //判断负整数
						{
							if (!feof(fp))
							{
								retract(fp);
								myToken.setConslToken("constant", strToken, conslPos++);
								myToken.setToken("constant", strToken);
								vector<constant> example;
								myToken.insertConslToken(example);
								if (example.size() > 0)
								{
									for (int i = 0; i<example.size() - 1; i++)
									{
										if (example[i].name == strToken)
										{
											flagNc = example[i].position;
											break;
										}
									}
								}
								if (flagNc == -1)
								{
									fc << "<" << "constant" << "," << example.back().position <<">"<< endl;
									cout << "<" << "constant" << "," << example.back().position <<">"<< endl;
								}
								else
								{
									myToken.popConslToken();
									fc << "<" << "constant" << "," << flagNc <<">"<< endl;
									cout << "<" << "constant" << "," << flagNc <<">"<< endl;
								}
							}

							else if (feof(fp))
							{
								myToken.setConslToken("constant", strToken, conslPos++);
								myToken.setToken("constant", strToken);
								vector<constant> example;
								myToken.insertConslToken(example);
								if (example.size() > 0)
								{
									for (int i = 0; i<example.size() - 1; i++)
									{
										if (example[i].name == strToken)
										{
											flagNc = example[i].position;
											break;
										}
									}
								}
								if (flagNc == -1)
								{
									fc << "<" << "constant" << "," << example.back().position <<">"<< endl;
									cout << "<" << "constant" << "," << example.back().position <<">"<< endl;
								}
								else
								{
									myToken.popConslToken();
									fc << "<" << "constant" << "," << flagNc <<">"<< endl;
									cout << "<" << "constant" << "," << flagNc <<">"<< endl;
								}
							}
						}
					}

					else
					{
						getChar(fp);
						int flag = -1;
						myToken.setToken("del", "-");
						myToken.setDelimiterToken("del", "-", delPos++);
						vector<del>example;
						myToken.insertDelimiterToken(example);
						if (example.size() > 0)
						{
							for (int i = 0; i<example.size() - 1; i++)
							{
								if (example[i].name == "-");
								{
									flag = example[i].position;
									break;
								}
							}
						}
						if (flag == -1)
						{
							fc << "<" << "delimiter" << "," << example.back().position <<">"<< endl;
							cout << "<" << "delimiter" << "," << example.back().position <<">"<< endl;
						}
						else
						{
							myToken.popDelimiterToken();
							fc << "<" << "constant" << "," << flag <<">"<< endl;
							cout << "<" << "constant" << "," << flag <<">"<< endl;
						}
					}
				}

			}
			else
			{
				int flag = -1;
				retract(fp);
				retract(fp);
				getChar(fp);
				myToken.setToken("del", "-");
				myToken.setDelimiterToken("del", "-", delPos++);
				vector<del>example;
				myToken.insertDelimiterToken(example);
				if (example.size() > 0)
				{
					for (int i = 0; i<example.size() - 1; i++)
					{
						if (example[i].name == "-");
						{
							flag = example[i].position;
							break;
						}
					}
				}
				if (flag == -1)
				{
					fc << "<" << "delimiter" << "," << example.back().position <<">"<< endl;
					cout << "<" << "delimiter" << "," << example.back().position <<">"<< endl;
				}
				else
				{
					myToken.popDelimiterToken();
					fc << "<" << "constant" << "," << flag <<">"<< endl;
					cout << "<" << "constant" << "," << flag <<">"<< endl;
				}
			}
		}

		else if (CH == '\"')//判断字符串
		{
			int flag = -1;
			myToken.setToken("delimiter", "\"");
			myToken.setDelimiterToken("delimiter", "\"", delPos++);
			vector<del>example;
			myToken.insertDelimiterToken(example);
			if (example.size() > 0)
			{
				for (int i = 0; i<example.size() - 1; i++)
				{
					if (example[i].name == "\"")
					{
						flag = example[i].position;
						break;
					}
				}
			}

			if (flag == -1)
			{
				fc << "<" << "delimiter" << "," << delPos-1<< endl;
				cout << "<" << "delimiter" << "," << delPos - 1 <<">"<< endl;
			}
			else
			{
				myToken.popDelimiterToken();
				fc << "<" << "delimiter" << "," << flag <<">"<< endl;
				cout << "<" << "delimiter" << "," << flag <<">"<< endl;
			}

			getChar(fp); //读字符串
			if (CH != '\"')
			{
				while (CH != '\"')
				{
					concat();
					getChar(fp);
				}

				if (CH == '\"')
				{
					int flagCon = -1, flag = -1;
					myToken.setToken("symbolString", "\"");
					myToken.setConslToken("symbolString", "\"", strPos++);
					vector<symbolString> example;
					myToken.insertStringToken(example);
					if (example.size() > 0)
					{
						for (int i = 0; i<example.size() - 1; i++)
						{
							if (example[i].name == strToken)
							{
								flagCon = example[i].position;
								break;
							}
						}
					}

					if (flagCon == -1)
					{
						fc << "<" << "symbolString" << "," << strPos - 1 <<">"<< endl;
						cout << "<" << "symbolString" << "," << strPos - 1 <<">"<< endl;
					}
					else
					{
						myToken.popConslToken();
						fc << "<" << "symbolString" << "," << flag <<">"<< endl;
						cout << "<" << "symbolString" << "," << flag <<">"<< endl;
					}

					myToken.setToken("delimiter", "\"");  //读入字符串后继续输出双引号
					myToken.setDelimiterToken("delimiter", "\"", delPos++);
					vector<del>exampleDel;
					myToken.insertDelimiterToken(exampleDel);
					if (exampleDel.size() > 0)
					{
						for (int i = 0; i<exampleDel.size() - 1; i++)
						{
							if (exampleDel[i].name == "\"")
							{
								flag = exampleDel[i].position;
								break;
							}
						}
					}
					myToken.popDelimiterToken();
					fc << "<" << "delimiter" << "," << flag <<">"<< endl;
					cout << "<" << "delimiter" << "," << flag <<">"<< endl;
				}

				else if (feof(fp))
				{
					cout << "输入错误,双引号不匹配" << endl;
					system("pause");
					exit(1);
				}
			}

			else  //两个双引号相邻
			{
				int flag;
				myToken.setToken("delimiter", "\"");
				myToken.setDelimiterToken("delimiter", "\"", delPos++);
				vector<del>example;
				myToken.insertDelimiterToken(example);
				if (example.size() > 0)
				{
					for (int i = 0; i<example.size() - 1; i++)
					{
						if (example[i].name == "\"")
						{
							flag = example[i].position;
							break;
						}
					}
				}

				myToken.popDelimiterToken();
				fc << "<" << "delimiter" << "," << flag <<">"<< endl;
				cout << "<" << "delimiter" << "," << flag <<">"<< endl;
			}
		}

		else if (CH == '\'') //判断字符，单引号
		{
			int flag = -1;
			myToken.setToken("delimiter", "\'");
			myToken.setDelimiterToken("delimiter", "\'", delPos++);
			vector<del>example;
			myToken.insertDelimiterToken(example);
			if (example.size() > 0)
			{
				for (int i = 0; i<example.size() - 1; i++)
				{
					if (example[i].name == "\'")
					{
						flag = example[i].position;
						break;
					}
				}
			}

			if (flag == -1)
			{
				fc << "<" << "delimiter" << "," << delPos - 1 <<">"<< endl;
				cout << "<" << "delimiter" << "," << delPos - 1 <<">"<< endl;
			}
			else
			{
				myToken.popDelimiterToken();
				fc << "<" << "delimiter" << "," << flag <<">"<< endl;
				cout << "<" << "delimiter" << "," << flag <<">"<< endl;
			}

			//继续读入，判断单个字符，如果两个单引号之间有多个字符，则报错
			getChar(fp);
			if (CH != '\'')
			{
				concat();
				int flag = -1;
				myToken.setToken("constant", strToken);
				myToken.setConslToken("constant", strToken, conslPos++);
				vector<constant> example = myToken.getConslToken();
				if (example.size() > 0)
				{
					for (int i = 0; i<example.size() - 1; i++)
					{
						if (example[i].name == strToken)
						{
							flag = example[i].position;
							break;
						}
					}
				}

				if (flag == -1)
				{
					fc << "<" << "constant" << "," << conslPos - 1 <<">"<< endl;
					cout << "<" << "constant" << "," << conslPos - 1 <<">"<< endl;
				}
				else
				{
					myToken.popConslToken();
					fc << "<" << "constant" << "," << flag <<">"<< endl;
					cout << "<" << "constant" << "," << flag <<">"<< endl;
				}

				//继续读入，判断是否匹配，如果不匹配，则报错
				getChar(fp);
				if (CH == '\'')
				{
					int flag;
					myToken.setToken("delimiter", "\'");
					myToken.setDelimiterToken("delimiter", "\'", delPos++);
					vector<del>example = myToken.getDelimiterToken(); 
					if(example.size()>0)
					{
						for (int i = 0; i<example.size() - 1; i++)
						{
							if (example[i].name == "\'")
							{
								flag = example[i].position;
								break;
							}
						}
					}

					myToken.popDelimiterToken();
					fc << "<" << "delimiter" << "," << flag <<">"<< endl;
					cout << "<" << "delimiter" << "," << flag <<">"<< endl;
				}

				else if (feof(fp))
				{
					cout << "单引号不匹配，输入错误" << endl;
					system("pause");
					exit(1);
				}
			}

			else if(CH=='\'')
			{
				int flag;
				myToken.setToken("delimiter", "\'");
				myToken.setDelimiterToken("delimiter", "\'", delPos++);
				vector<del>example;
				myToken.insertDelimiterToken(example);
				if (example.size() > 0)
				{
					for (int i = 0; i<example.size() - 1; i++)
					{
						if (example[i].name == "\'")
						{
							flag = example[i].position;
							break;
						}
					}
				}

				myToken.popDelimiterToken();
				fc << "<" << "delimiter" << "," << flag <<">"<< endl;
				cout << "<" << "delimiter" << "," << flag <<">"<< endl;
			}
		}

		else if (CH == '+')
		{
			int flag = -1;
			myToken.setToken("delimiter", "+");
			myToken.setDelimiterToken("delimiter", "+", delPos++);
			vector<del>example;
			myToken.insertDelimiterToken(example);
			if (example.size() > 0)
			{
				for (int i = 0; i<example.size() - 1; i++)
				{
					if (example[i].name == "+")
					{
						flag = example[i].position;
						break;
					}
				}
			}

			if (flag == -1)
			{
				fc << "<" << "delimiter" << "," << delPos - 1 <<">"<< endl;
				cout << "<" << "delimiter" << "," << delPos - 1 <<">"<< endl;
			}
			else
			{
				myToken.popDelimiterToken();
				fc << "<" << "delimiter" << "," << flag <<">"<< endl;
				cout << "<" << "delimiter" << "," << flag <<">"<< endl;
			}
		}

		else if (CH == '*')
		{
			int flag = -1;
			myToken.setToken("delimiter", "*");
			myToken.setDelimiterToken("delimiter", "*", delPos++);
			vector<del>example;
			myToken.insertDelimiterToken(example);
			if (example.size() > 0)
			{
				for (int i = 0; i<example.size() - 1; i++)
				{
					if (example[i].name == "*")
					{
						flag = example[i].position;
						break;
					}
				}
			}
			if (flag == -1)
			{
				fc << "<" << "delimiter" << "," << delPos - 1 <<">"<< endl;
				cout << "<" << "delimiter" << "," << delPos - 1 <<">"<< endl;
			}
			else
			{
				myToken.popDelimiterToken();
				fc << "<" << "delimiter" << "," << flag <<">"<< endl;
				cout << "<" << "delimiter" << "," << flag <<">"<< endl;
			}
		}

		else if (CH == '/')
		{
			int flag = -1;
			myToken.setToken("delimiter", "\'");
			myToken.setDelimiterToken("delimiter", "\'", delPos++);
			vector<del>example;
			myToken.insertDelimiterToken(example);
			if (example.size() > 0)
			{
				for (int i = 0; i<example.size() - 1; i++)
				{
					if (example[i].name == "/")
					{
						flag = example[i].position;
						break;
					}
				}
			}
			if (flag == -1)
			{
				fc << "<" << "delimiter" << "," << delPos - 1 <<">"<< endl;
				cout << "<" << "delimiter" << "," << delPos - 1 <<">"<< endl;
			}
			else
			{
				myToken.popDelimiterToken();
				fc << "<" << "delimiter" << "," << flag <<">"<< endl;
				cout << "<" << "delimiter" << "," << flag <<">"<< endl;
			}
		}

		else if (CH == '{')
		{
			int flag = -1;
			myToken.setToken("delimiter", "{");
			myToken.setDelimiterToken("delimiter", "{", delPos++);
			vector<del>example;
			myToken.insertDelimiterToken(example);
			if (example.size() > 0)
			{
				for (int i = 0; i<example.size() - 1; i++)
				{
					if (example[i].name == "{")
					{
						flag = example[i].position;
						break;
					}
				}
			}
			if (flag == -1)
			{
				fc << "<" << "delimiter" << "," << delPos - 1 <<">"<< endl;
				cout << "<" << "delimiter" << "," << delPos - 1 <<">"<< endl;
			}
			else
			{
				myToken.popDelimiterToken();
				fc << "<" << "delimiter" << "," << flag <<">"<< endl;
				cout << "<" << "delimiter" << "," << flag <<">"<< endl;
			}
		}

		else if (CH == '}')
		{
			int flag = -1;
			myToken.setToken("delimiter", "}");
			myToken.setDelimiterToken("delimiter", "}", delPos++);
			vector<del>example;
			myToken.insertDelimiterToken(example);
			if (example.size() > 0)
			{
				for (int i = 0; i<example.size() - 1; i++)
				{
					if (example[i].name == "}")
					{
						flag = example[i].position;
						break;
					}
				}
			}
			if (flag == -1)
			{
				fc << "<" << "delimiter" << "," << delPos - 1 <<">"<< endl;
				cout << "<" << "delimiter" << "," << delPos - 1 <<">"<< endl;
			}
			else
			{
				myToken.popDelimiterToken();
				fc << "<" << "delimiter" << "," << flag <<">"<< endl;
				cout << "<" << "delimiter" << "," << flag <<">"<< endl;
			}
		}

		else if (CH == '(')
		{
			int flag = -1;
			myToken.setToken("delimiter", "(");
			myToken.setDelimiterToken("delimiter", "(", delPos++);
			vector<del>example;
			myToken.insertDelimiterToken(example);
			if (example.size() > 0)
			{
				for (int i = 0; i<example.size() - 1; i++)
				{
					if (example[i].name == "(")
					{
						flag = example[i].position;
						break;
					}
				}
			}
			if (flag == -1)
			{
				fc << "<" << "delimiter" << "," << delPos - 1 <<">"<< endl;
				cout << "<" << "delimiter" << "," << delPos - 1 <<">"<< endl;
			}
			else
			{
				myToken.popDelimiterToken();
				fc << "<" << "delimiter" << "," << flag <<">"<< endl;
				cout << "<" << "delimiter" << "," << flag <<">"<< endl;
			}
		}

		else if (CH == ')')
		{
			int flag = -1;
			myToken.setToken("delimiter", ")");
			myToken.setDelimiterToken("delimiter", ")", delPos++);
			vector<del>example;
			myToken.insertDelimiterToken(example);
			if (example.size() > 0)
			{
				for (int i = 0; i<example.size() - 1; i++)
				{
					if (example[i].name == ")")
					{
						flag = example[i].position;
						break;
					}
				}
			}
			if (flag == -1)
			{
				fc << "<" << "delimiter" << "," << delPos - 1 <<">"<< endl;
				cout << "<" << "delimiter" << "," << delPos - 1 <<">"<< endl;
			}
			else
			{
				myToken.popDelimiterToken();
				fc << "<" << "delimiter" << "," << flag <<">"<< endl;
				cout << "<" << "delimiter" << "," << flag <<">"<< endl;
			}
		}

		else if (CH == ';')
		{
			int flag = -1;
			myToken.setToken("delimiter", ";");
			myToken.setDelimiterToken("delimiter", ";", delPos++);
			vector<del>example;
			myToken.insertDelimiterToken(example);
			if (example.size() > 0)
			{
				for (int i = 0; i<example.size() - 1; i++)
				{
					if (example[i].name == ";")
					{
						flag = example[i].position;
						break;
					}
				}
			}
			if (flag == -1)
			{
				fc << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
				cout << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
			}
			else
			{
				myToken.popDelimiterToken();
				fc << "<" << "delimiter" << "," << flag << ">" << endl;
				cout << "<" << "delimiter" << "," << flag << ">" << endl;
			}
		}

		else if (CH == ',')
		{
			int flag = -1;
			myToken.setToken("delimiter", ",");
			myToken.setDelimiterToken("delimiter", ",", delPos++);
			vector<del>example;
			myToken.insertDelimiterToken(example);
			if (example.size() > 0)
			{
				for (int i = 0; i<example.size() - 1; i++)
				{
					if (example[i].name == ",")
					{
						flag = example[i].position;
						break;
					}
				}
			}
			if (flag == -1)
			{
				fc << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
				cout << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
			}
			else
			{
				myToken.popDelimiterToken();
				fc << "<" << "delimiter" << "," << flag << ">" << endl;
				cout << "<" << "delimiter" << "," << flag << ">" << endl;
			}
		}

		else if (CH == '.')
		{
			int flag = -1;
			myToken.setToken("delimiter", ".");
			myToken.setDelimiterToken("delimiter", ".", delPos++);
			vector<del>example;
			myToken.insertDelimiterToken(example);
			if (example.size() > 0)
			{
				for (int i = 0; i<example.size() - 1; i++)
				{
					if (example[i].name == ".")
					{
						flag = example[i].position;
						break;
					}
				}
			}
			if (flag == -1)
			{
				fc << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
				cout << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
			}
			else
			{
				myToken.popDelimiterToken();
				fc << "<" << "delimiter" << "," << flag << ">" << endl;
				cout << "<" << "delimiter" << "," << flag << ">" << endl;
			}
		}

		else if (CH == '#')
		{
			int flag = -1;
			myToken.setToken("delimiter", "#");
			myToken.setDelimiterToken("delimiter", "#", delPos++);
			vector<del>example;
			myToken.insertDelimiterToken(example);
			if (example.size() > 0)
			{
				for (int i = 0; i<example.size() - 1; i++)
				{
					if (example[i].name == "#")
					{
						flag = example[i].position;
						break;
					}
				}
			}
			if (flag == -1)
			{
				fc << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
				cout << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
			}
			else
			{
				myToken.popDelimiterToken();
				fc << "<" << "delimiter" << "," << flag << ">" << endl;
				cout << "<" << "delimiter" << "," << flag << ">" << endl;
			}
		}

		else if (CH == '!')
		{
			int flag = -1;
			myToken.setToken("delimiter", "!");
			myToken.setDelimiterToken("delimiter", "!", delPos++);
			vector<del>example;
			myToken.insertDelimiterToken(example);
			if (example.size() > 0)
			{
				for (int i = 0; i<example.size() - 1; i++)
				{
					if (example[i].name == "!")
					{
						flag = example[i].position;
						break;
					}
				}
			}
			if (flag == -1)
			{
				fc << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
				cout << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
			}
			else
			{
				myToken.popDelimiterToken();
				fc << "<" << "delimiter" << "," << flag << ">" << endl;
				cout << "<" << "delimiter" << "," << flag << ">" << endl;
			}
		}

		else if (CH == '@')
		{
			int flag = -1;
			myToken.setToken("delimiter", "@");
			myToken.setDelimiterToken("delimiter", "@", delPos++);
			vector<del>example;
			myToken.insertDelimiterToken(example);
			if (example.size() > 0)
			{
				for (int i = 0; i<example.size() - 1; i++)
				{
					if (example[i].name == "@")
					{
						flag = example[i].position;
						break;
					}
				}
			}
			if (flag == -1)
			{
				fc << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
				cout << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
			}
			else
			{
				myToken.popDelimiterToken();
				fc << "<" << "delimiter" << "," << flag << ">" << endl;
				cout << "<" << "delimiter" << "," << flag << ">" << endl;
			}
		}

		else if (CH == '%')
		{
			int flag = -1;
			myToken.setToken("delimiter", "%");
			myToken.setDelimiterToken("delimiter", "%", delPos++);
			vector<del>example;
			myToken.insertDelimiterToken(example);
			if (example.size() > 0)
			{
				for (int i = 0; i<example.size() - 1; i++)
				{
					if (example[i].name == "%")
					{
						flag = example[i].position;
						break;
					}
				}
			}
			if (flag == -1)
			{
				fc << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
				cout << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
			}
			else
			{
				myToken.popDelimiterToken();
				fc << "<" << "delimiter" << "," << flag << ">" << endl;
				cout << "<" << "delimiter" << "," << flag << ">" << endl;
			}
		}

		else if (CH == '^')
		{
			int flag = -1;
			myToken.setToken("delimiter", "^");
			myToken.setDelimiterToken("delimiter", "^", delPos++);
			vector<del>example;
			myToken.insertDelimiterToken(example);
			if (example.size() > 0)
			{
				for (int i = 0; i<example.size() - 1; i++)
				{
					if (example[i].name == "^")
					{
						flag = example[i].position;
						break;
					}
				}
			}
			if (flag == -1)
			{
				fc << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
				cout << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
			}
			else
			{
				myToken.popDelimiterToken();
				fc << "<" << "delimiter" << "," << flag << ">" << endl;
				cout << "<" << "delimiter" << "," << flag << ">" << endl;
			}
		}

		else if (CH == '&')
		{
			int flag = -1;
			myToken.setToken("delimiter", "&");
			myToken.setDelimiterToken("delimiter", "&", delPos++);
			vector<del>example;
			myToken.insertDelimiterToken(example);
			if (example.size() > 0)
			{
				for (int i = 0; i<example.size() - 1; i++)
				{
					if (example[i].name == "&")
					{
						flag = example[i].position;
						break;
					}
				}
			}
			if (flag == -1)
			{
				fc << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
				cout << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
			}
			else
			{
				myToken.popDelimiterToken();
				fc << "<" << "delimiter" << "," << flag << ">" << endl;
				cout << "<" << "delimiter" << "," << flag << ">" << endl;
			}
		}

		else if (CH == '<')
		{
			int flag = -1;
			myToken.setToken("delimiter", "<");
			myToken.setDelimiterToken("delimiter", "<", delPos++);
			vector<del>example;
			myToken.insertDelimiterToken(example);
			if (example.size() > 0)
			{
				for (int i = 0; i<example.size() - 1; i++)
				{
					if (example[i].name == "<")
					{
						flag = example[i].position;
						break;
					}
				}
			}
			if (flag == -1)
			{
				fc << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
				cout << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
			}
			else
			{
				myToken.popDelimiterToken();
				fc << "<" << "delimiter" << "," << flag << ">" << endl;
				cout << "<" << "delimiter" << "," << flag << ">" << endl;
			}
		}

		else if (CH == '>') 
		{
			int flag = -1;
			myToken.setToken("delimiter", ">");
			myToken.setDelimiterToken("delimiter", ">", delPos++);
			vector<del>example;
			myToken.insertDelimiterToken(example);
			if (example.size() > 0)
			{
				for (int i = 0; i<example.size() - 1; i++)
				{
					if (example[i].name == ">")
					{
						flag = example[i].position;
						break;
					}
				}
			}
			if (flag == -1)
			{
				fc << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
				cout << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
			}
			else
			{
				myToken.popDelimiterToken();
				fc << "<" << "delimiter" << "," << flag << ">" << endl;
				cout << "<" << "delimiter" << "," << flag << ">" << endl;
			}
		}

		else if (CH == '$')
		{
			int flag = -1;
			myToken.setToken("delimiter", "$");
			myToken.setDelimiterToken("delimiter", "$", delPos++);
			vector<del>example;
			myToken.insertDelimiterToken(example);
			if (example.size() > 0)
			{
				for (int i = 0; i<example.size() - 1; i++)
				{
					if (example[i].name == "$")
					{
						flag = example[i].position;
						break;
					}
				}
			}
			if (flag == -1)
			{
				fc << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
				cout << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
			}
			else
			{
				myToken.popDelimiterToken();
				fc << "<" << "delimiter" << "," << flag << ">" << endl;
				cout << "<" << "delimiter" << "," << flag << ">" << endl;
			}
		}

		else if (CH == '~')
		{
			int flag = -1;
			myToken.setToken("delimiter", "~");
			myToken.setDelimiterToken("delimiter", "~", delPos++);
			vector<del>example;
			myToken.insertDelimiterToken(example);
			if (example.size() > 0)
			{
				for (int i = 0; i<example.size() - 1; i++)
				{
					if (example[i].name == "~")
					{
						flag = example[i].position;
						break;
					}
				}
			}
			if (flag == -1)
			{
				fc << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
				cout << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
			}
			else
			{
				myToken.popDelimiterToken();
				fc << "<" << "delimiter" << "," << flag << ">" << endl;
				cout << "<" << "delimiter" << "," << flag << ">" << endl;
			}
		}

		else if (CH == '[')
		{
			int flag = -1;
			myToken.setToken("delimiter", "[");
			myToken.setDelimiterToken("delimiter", "[", delPos++);
			vector<del>example;
			myToken.insertDelimiterToken(example);
			if (example.size() > 0)
			{
				for (int i = 0; i<example.size() - 1; i++)
				{
					if (example[i].name == "[")
					{
						flag = example[i].position;
						break;
					}
				}
			}
			if (flag == -1)
			{
				fc << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
				cout << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
			}
			else
			{
				myToken.popDelimiterToken();
				fc << "<" << "delimiter" << "," << flag << ">" << endl;
				cout << "<" << "delimiter" << "," << flag << ">" << endl;
			}
		}

		else if (CH == ']')
		{
			int flag = -1;
			myToken.setToken("delimiter", "]");
			myToken.setDelimiterToken("delimiter", "]", delPos++);
			vector<del>example;
			myToken.insertDelimiterToken(example);
			if (example.size() > 0)
			{
				for (int i = 0; i<example.size() - 1; i++)
				{
					if (example[i].name == "]")
					{
						flag = example[i].position;
						break;
					}
				}
			}
			if (flag == -1)
			{
				fc << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
				cout << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
			}
			else
			{
				myToken.popDelimiterToken();
				fc << "<" << "delimiter" << "," << flag << ">" << endl;
				cout << "<" << "delimiter" << "," << flag << ">" << endl;
			}
		}

		else if (CH == '=')
		{
			int flag = -1;
			myToken.setToken("delimiter", "=");
			myToken.setDelimiterToken("delimiter", "=", delPos++);
			vector<del>example;
			myToken.insertDelimiterToken(example);
			if (example.size() > 0)
			{
				for (int i = 0; i<example.size() - 1; i++)
				{
					if (example[i].name == "=")
					{
						flag = example[i].position;
						break;
					}
				}
			}
			if (flag == -1)
			{
				fc << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
				cout << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
			}
			else
			{
				myToken.popDelimiterToken();
				fc << "<" << "delimiter" << "," << flag << ">" << endl;
				cout << "<" << "delimiter" << "," << flag << ">" << endl;
			}
		}

		else if (CH == '|')
		{
			int flag = -1;
			myToken.setToken("delimiter", "|");
			myToken.setDelimiterToken("delimiter", "|", delPos++);
			vector<del>example;
			myToken.insertDelimiterToken(example);
			if (example.size() > 0)
			{
				for (int i = 0; i<example.size() - 1; i++)
				{
					if (example[i].name == "|")
					{
						flag = example[i].position;
						break;
					}
				}
			}
			if (flag == -1)
			{
				fc << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
				cout << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
			}
			else
			{
				myToken.popDelimiterToken();
				fc << "<" << "delimiter" << "," << flag << ">" << endl;
				cout << "<" << "delimiter" << "," << flag << ">" << endl;
			}
		}

		else if (CH == '\\')
		{
			int flag = -1;
			myToken.setToken("delimiter", "\\");
			myToken.setDelimiterToken("delimiter", "\\", delPos++);
			vector<del>example;
			myToken.insertDelimiterToken(example);
			if (example.size() > 0)
			{
				for (int i = 0; i<example.size() - 1; i++)
				{
					if (example[i].name == "\\")
					{
						flag = example[i].position;
						break;
					}
				}
			}
			if (flag == -1)
			{
				fc << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
				cout << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
			}
			else
			{
				myToken.popDelimiterToken();
				fc << "<" << "delimiter" << "," << flag << ">" << endl;
				cout << "<" << "delimiter" << "," << flag << ">" << endl;
			}
		}

		else if (CH == '_')
		{
			int flag = -1;
			myToken.setToken("delimiter", "_");
			myToken.setDelimiterToken("delimiter", "_", delPos++);
			vector<del>example;
			myToken.insertDelimiterToken(example);
			if (example.size() > 0)
			{
				for (int i = 0; i<example.size() - 1; i++)
				{
					if (example[i].name == "_")
					{
						flag = example[i].position;
						break;
					}
				}
			}
			if (flag == -1)
			{
				fc << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
				cout << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
			}
			else
			{
				myToken.popDelimiterToken();
				fc << "<" << "delimiter" << "," << flag << ">" << endl;
				cout << "<" << "delimiter" << "," << flag << ">" << endl;
			}
		}

		else if (CH == ':')
		{
			int flag = -1;
			myToken.setToken("delimiter", ":");
			myToken.setDelimiterToken("delimiter", ":", delPos++);
			vector<del>example;
			myToken.insertDelimiterToken(example);
			if (example.size() > 0)
			{
				for (int i = 0; i<example.size() - 1; i++)
				{
					if (example[i].name == ":")
					{
						flag = example[i].position;
						break;
					}
				}
			}
			if (flag == -1)
			{
				fc << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
				cout << "<" << "delimiter" << "," << delPos - 1 << ">" << endl;
			}
			else
			{
				myToken.popDelimiterToken();
				fc << "<" << "delimiter" << "," << flag << ">" << endl;
				cout << "<" << "delimiter" << "," << flag << ">" << endl;
			}
		}

	}
	fclose(fp);
	fc.close();
	return myToken;
}

/*int main()
{
	scanner();
	return 0;
}*/