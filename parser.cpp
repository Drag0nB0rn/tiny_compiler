#include "table.h"
#include "parser.h"
using namespace std;
void error()
{
	return;
}

check parserTable::checkList(string cur,string top)		//未完
{
	check t;
	map<int, string>::iterator it;
	for (it = parserList.begin(); it != parserList.end(); it++)  //用迭代器遍历查分析表
	{
		production tmp = pro[it->first];
		//cout << tmp.left << "->" << tmp.right << " " << it->second<<endl;
		if (it->second == cur && tmp.left == top)   //L(cur,top)= ?
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
	terTable.push_back("a");
}
void parserTable::creatNotTerTable() //test
{
	notTerTable.push_back("E");
	notTerTable.push_back("type");
	notTerTable.push_back("F");
}

void parserTable::creatProduction()  //test
{
	ins("E", "F&type");
	ins("type", "int");
	ins("F", "a");
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

void parserTable::creatParserList()  //test
{
	creatProduction();
	parserList[0] = "int";
	parserList[1] = "int";
	parserList[2] = "a";
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
bool parserTable::match(string cur, string top)
{
	if (cur == top)
	{
		return true;
	}
	

}
string parserTable::getNextCur()  //test
{
	string t;
	t = token[p_token];
	p_token++;
	return t;

}
bool parserTable::LL1Parser()  //未完
{
	bool flag=false;
	int num = 0;
	creatNotTerTable();
	creatTerTable();
	synStack.push("#");
	synStack.push("E");
	string cur, top;
	cur = getNextCur();
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
			if (top == cur||match(cur,top))
			{
				cur = getNextCur();
				cout << "macth!\n";
				continue;
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
	parserTable table;
	table.creatParserList();
	table.travelProduction();
	/*check t = table.checkList("i","E");
	if (t.flag)
	{
		cout << "true" << endl;
		production tmp = table.getProduction(t.proIndex);
		cout << tmp.left << "->" << tmp.right;
	}
	else
		cout << "false" << endl;
	return 0;*/
	cout <<"\nres:"<< table.LL1Parser();
}
