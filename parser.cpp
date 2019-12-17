#include "parser.h"
#include "lexical.h"
using namespace std;
scannerToken tmp;
void error()
{
	return;
}

check parserTable::checkList(string cur, string top)		//未完
{
	check t;
	bool flag2=false;
	map<int, vector<string>>::iterator it;
	int i = 1;
	for (it = parserList.begin(); it != parserList.end(); it++)  //用迭代器遍历查分析表
	{
		vector<string> t2 = it->second;
		production tmp = pro[it->first];
		//cout << tmp.left << "->" << tmp.right << " " <<endl;
		for (auto u : t2)     //一键多值，遍历产生式对应的终结符vector
		{
			if (u == cur)	//产生式可推出该终结符
			{
				flag2 = true;   
				break;
			}
			else if (match(u, cur))
			{
				flag2 = true;
				break;
			}
		}
		if (flag2 && tmp.left == top)   //L(cur,top)= ?
		{
			t.flag = true;
			t.proIndex = it->first;
			break;
		}
		else
		{
			t.flag = false;
			t.proIndex = -1;
		}
		flag2 = false;
	}
	return t;
}
void parserTable::ins(string left, string right)
{
	production t;
	t.left = left;
	t.right = right;
	pro.push_back(t);
}
void parserTable::creatTerTable() //test
{
	terTable.push_back("int");
	terTable.push_back("char");
	terTable.push_back("float");
	terTable.push_back("id");
}
void parserTable::creatNotTerTable() //test
{
	notTerTable.push_back("E");
	notTerTable.push_back("type");
	notTerTable.push_back("F");
}

void parserTable::creatProduction()  //test
{
	//ins("$", "$");
	ins("E", "F&type");
	ins("type", "int");
	ins("type", "char");
	ins("type","float");
	ins("F", "id");
}
void parserTable::printSynStack()
{
	stack<string> t;
	t = synStack;
	while (!t.empty())
	{
		cout << t.top() << " ";
		t.pop();
	}
}

void parserTable::travelProduction()  //test
{
	for (auto u : pro)
	{
		cout << u.left << "->" << u.right << endl;
	}
}
void parserTable::insL(int key, string value )
{
	t5.push_back(value);
	parserList[key] = t5;
}
void parserTable::creatParserList()  //test
{
	creatProduction();
	insL(0, "int");
	insL(0, "float");
	insL(0, "char");
	t5.clear();
	insL(1, "int");
	insL(2, "float");
	insL(3, "char");
	t5.clear();
	insL(4, "a");
	t5.clear();
}

void parserTable::getToken()
{
	;
}

production parserTable::getProduction(int index)
{
	return pro[index];
}

bool parserTable::isNotTer(string c)
{
	for (auto u : notTerTable)
	{
		if (u == c)
		{
			return true;
		}
	}
	return false;
}
bool parserTable::isConstant(string cur)
{
	vector<constant> t;
	t = tmp.getConslToken();
	for (auto u : t)	//遍历
	{
		if (cur == u.name)
		{
			return true;
		}
	}
	return false;
}

bool parserTable::isString(string cur)
{
	vector<symbolString> t;
	scannerToken tmp;
	t = tmp.getStringToken();
	for (auto u : t)	//遍历
	{
		if (cur == u.name)
		{
			return true;
		}
	}
	return false;
}

bool parserTable::isIdtifier(string cur)
{
	vector<identy> t;
	t = tmp.getIdToken();
	for (auto u : t)   //遍历
	{
		if (cur == u.name)
		{
			return true;
		}
	}
	return false;
}

bool parserTable::isKeyword(string cur)
{
	for (auto u : reserveword)	//遍历
	{
		if (cur == u)
		{
			return true;
		}
	}
	return false;
}

bool parserTable::isDelimiter(string cur)
{
	vector<del> t;
	t = tmp.getDelimiterToken();
	for (auto u : t)
	{
		if (cur == u.name)
		{
			return true;
		}
	}
	return false;
}
bool parserTable::match(string cur, string top)
{
	if (cur == top)
	{
		return true;
	}
	else if (top == "cons"&&isConstant(cur))
	{
		return true;
	}
	else if (top == "str"&&isString(cur))
	{
		return true;
	}
	else if (top == "id"&&isIdtifier(cur))
	{
		return true;
	}
	else if (top == "key"&&isKeyword(cur))
	{
		return true;
	}
	else if (top == "del"&&isDelimiter(cur))
	{
		return true;
	}

}

bool parserTable::isTer(string c)
{
	for (auto u : terTable)
	{
		if (u == c)
		{
			return true;
		}
	}
	return false;
}

string parserTable::getNextCur()  //test
{
	string t;
	t = token1[p_token];
	p_token++;
	return t;

}
string parserTable::getNext(vector<token> Token)		//未完
{
	string t;
	if (Token[p].type == "constant")   //查对应表再返回单词
	{
		t = Token[p].name;
		p++;
		return t;

	}
	else if (Token[p].type == "symbolString")
	{
		t = Token[p].name;
		p++;
		return t;
	}
	else if (Token[p].type == "identy")
	{ 
		t = Token[p].name;
		p++;
		return t;
	}
	else if (Token[p].type == "key")
	{
		t = Token[p].name;
		p++;
		return t;
	}
	else if (Token[p].type == "del")
	{
		t = Token[p].name;
		p++;
		return t;
	}

}
bool parserTable::LL1Parser()  //未完
{
	vector<token> Token;
	Token = tmp.getToken();
	bool flag = false;
	int num = 0;
	creatNotTerTable();
	creatTerTable();
	synStack.push("#");
	synStack.push("E");
	string cur, top;
	cur = getNext(Token);
	while (!synStack.empty())
	{
		cout << num << " ";
		num++;
		printSynStack();
		top = synStack.top();
		synStack.pop();
		if (isTer(top))
		{
			cout << top << "," << cur << "\t";
			/*if (cur == "#"&&top == "#")
			{
				flag = true;
				break;
			}*/
			if (top == cur || match(cur, top))
			{
				cout << "macth!\n";
				cur = getNext(Token);
			}
			else
			{
				flag = false;
				cout << "error1";
				break;
			}
		}
		else if (top == "#")
		{
			cout << top << "," << cur << "\t";
			if (cur == top)
			{
				flag = true;
				break;
			}
			else
			{
				flag = false;
				break;
			}
		}
		else if (!isTer(top))
		{
			if (isNotTer(top))
			{
				cout << "check(" << top << "," << cur << ")\t";
				check t;
				t = checkList(cur, top);
				if (t.flag)
				{
					production tmp;
					tmp = pro[t.proIndex];
					string stmp = "";
					for (int i = 0; i <= tmp.right.length() - 1; i++)  //产生式右部(已逆序)压栈
					{
						if (tmp.right[i] != '&')
						{
							stmp += tmp.right[i];
						}
						else
						{
							synStack.push(stmp);
							stmp = "";
						}
					}
					synStack.push(stmp);
					continue;
				}
				else
				{
					flag = false;
					cout << "error2";
					break;
				}
			}
			else if (!isNotTer(top))
			{
				if (cur == "#")
				{
					flag = true;
					break;
				}
				else
				{
					flag = false;
					cout << "error3";
					break;
				}
			}
		}
	}
	return flag;
}
int main()
{
	tmp.insId("a", "identy", 0);
	tmp.insToken("float", "key", 0);
	tmp.insToken("a", "identy", 0);
	tmp.insToken("#", "identy", 0); //token(float a #)
	parserTable table;
	table.creatParserList();
	table.travelProduction();
	/*check t = table.checkList("int","E");
	if (t.flag)
	{
		cout << "true" << endl;
		production tmp = table.getProduction(t.proIndex);
		cout << tmp.left << "->" << tmp.right;
	}
	else
		cout << "false" << endl;
	return 0;*/
	cout << "\nres:" << table.LL1Parser();
}
