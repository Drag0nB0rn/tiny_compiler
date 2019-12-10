#include"head.h"
char getCh()
{
	ch = input[p_input];
	p_input++;
	return ch;
}

void getBc()
{
	while (ch == ' ' || ch == 10)
	{
		ch = input[p_input];
		p_input++;
	}
}
void concat()
{
	token[p_token] = ch;
	p_token++;
	token[p_token] = '\0';
}


bool isLetter()
{
	if (ch >= 'a'&&ch <= 'z' || ch >= 'A'&&ch <= 'Z')
		return true;
	else
		return false;
}

bool isDigit()
{
	if (ch >= '0'&&ch <= '9')
		return true;
	else
		return false;
}
bool isRadix_point()
{
	if (ch == '.')
		return true;
	else
		return false;
}
bool isNegative_sign()
{
	if (ch == '-')
		return true;
	else
		return false;
}
int reserve()
{
	int i = 0;
	while (strcmp(reserve_table[i].c_str(), "finish"))
	{
		if (!strcmp(reserve_table[i].c_str(), token))
			return i;
		i++;
	}
	return 777;
}
int delimiter()
{
	for (int i = 0; delimiter_table[i] != 'q'; i++)
	{
		if (token[0] == delimiter_table[i])
		{
			return i;
		}
	}
	return 4396;
}
void initidentifier_table()
{
	for (int i = 0; i < 100; i++)
	{
		identifier_table[i] = "clearlove";
	}
}
int existIdentifier()
{
	int i = 0;
	while (identifier_table[i] != "clearlove")
	{
		if (token == identifier_table[i])
			return i;
		i++;
	}
	return -1;
}
int existConstant()
{
	int i = 0;
	while (constant_table[i] != "clearlove")
	{
		if (token == constant_table[i])
			return i;
		i++;
	}
	return -1;
}
int insertIdentifier()
{
	int temp = p_identifier;
	if (identifier_table[temp] == "clearlove")
	{
		identifier_table[temp] = token;
		p_identifier++;
		return temp;
	}
}

void initconstant_table()
{
	for (int i = 0; i < 100; i++)
	{
		constant_table[i] = "clearlove";
	}
}
int insertConstant()
{
	int temp = p_constant;
	if (constant_table[temp] == "clearlove")
	{
		constant_table[temp] = token;
		p_constant++;
		return temp;
	}
}
void insertString()
{
	int i = p_string;
	string_table[i] = token;
}

void retract()
{
	p_input--;
}
void showreserve_table()
{
	cout << "\nReserve Productionle:\n";
	int i = 0;
	while (reserve_table[i] != "finish")
	{
		cout << i << "\t" << reserve_table[i] << endl;
		i++;
	}
}

void showdelimiter_table()
{
	cout << "\nDelimiter Productionle:\n";
	int i = 0;
	while (delimiter_table[i] != 'q')
	{
		cout << i << "\t" << delimiter_table[i] << endl;
		i++;
	}
}
void showconstant_table()
{
	cout << "\nConstant Productionle:\n";
	int i = 0;
	while (constant_table[i] != "clearlove")
	{
		cout << i << "\t" << constant_table[i] << endl;
		i++;
	}
}
void showidentifier_table()
{
	cout << "\nIdentifier Productionle:\n";
	int i = 0;
	while (identifier_table[i] != "clearlove")
	{
		cout << i << "\t" << identifier_table[i] << endl;
		i++;
	}
}
void showstring_table()
{
	cout << "\nString Productionle:\n";
	for (int i = 0; i < p_string; i++)
	{
		cout << i << "\t" << string_table[i] << endl;
	}
}

WORD  scanner()
{
	WORD  myword;
	myword.sequence = 0;
	myword.type = "";
	p_token = 0;
	getCh();
	getBc();
	if (isLetter())
	{
		while (isLetter() || isDigit())
		{
			concat();
			getCh();
		}
		retract();
		if (reserve() != 777)
		{
			myword.type = "reserve";
			myword.sequence = reserve();
		}
		if (reserve() == 777)
		{
			myword.type = "identifier";
			if (existIdentifier() >= 0)
				myword.sequence = existIdentifier();
			else
				myword.sequence = insertIdentifier();
		}
		return myword;
	}
	else if (isDigit() || isNegative_sign())
	{
		int radix_flag = 0;
		int negative_flag = 0;
		while (isDigit() || isNegative_sign())
		{
			concat();
			getCh();
			if (isNegative_sign() && negative_flag < 1)
			{
				concat();
				getCh();
				negative_flag++;
			}
			if (isRadix_point() && radix_flag < 1)
			{
				concat();
				getCh();
				radix_flag++;
			}
		}
		retract();
		myword.type = "constant";
		if (existConstant() >= 0)
			myword.sequence = existConstant();
		else
			myword.sequence = insertConstant();
		return(myword);
	}
	if (ch == '\"')
	{

		getCh();
		while (true)
		{
			getCh();
			if (ch == '\"')
			{
				getCh();
				break;
			}
			concat();
		}
		retract();
		myword.type = "string";
		myword.sequence = p_string;
		insertString();
		p_string++;
		return myword;
	}
	if (isDigit() == false && isLetter() == false)
	{
		concat();
		getCh();
		retract();
		myword.type = "delimiter";
		myword.sequence = delimiter();
		return myword;
	}
}
void recursion()
{
	p_input = 0;
	getCh();
	E();
}
//递归子程序
void error()
{
	return;
}
void E()
{
	T();
	E1();
	if (ch == '#'&&parser == 0)
	{
		flag == true;
		printf("\ntrue\n");
		return;
	}
	if (parser != 0)
	{
		printf("%d", parser);
		flag = false;
		printf("\nfalse\n");
		return;
	}
}
void E1()
{
	if (ch == '+' || ch == '-')
	{
		printf("%c", ch);
		getCh();
		T();
		E1();
		return;
	}
	else if (ch == '$')
	{
		return;
	}
}
void T()
{
	F();
	T1();
	return;
}
void T1()
{
	if (ch == '*' || ch == '/')
	{
		printf("%c", ch);
		getCh();
		F();
		T1();
		return;
	}
	else if (ch == '$')
	{
		return;
	}
}
void F()
{
	if (isDigit()||isLetter())
	{
		while (isDigit()||isLetter())
		{
			printf("%c", ch);
			getCh();
		}
		return;
	}
	if (ch == '(')
	{
		printf("%c", ch);
		getCh();
		E();
		if (ch == ')')
		{
			printf("%c", ch);
			getCh();
			return;
		}
		else if (ch != ')')
		{
			parser++;
			error();
		}
	}
	else if (ch != '(')
	{
		parser++;
		error();
	}
}
//
// LL(1)
void initparser_list()
{
	parser_list.push_back(Production('E', 'i', "TA"));
	parser_list.push_back(Production('E', '(', "TA"));
	parser_list.push_back(Production('A', '+', "+TA"));
	parser_list.push_back(Production('A', '-', "-TA"));
	parser_list.push_back(Production('A', ')', "$"));
	parser_list.push_back(Production('A', '#', "$"));
	parser_list.push_back(Production('T', 'i', "FB"));
	parser_list.push_back(Production('T', '(', "FB"));
	parser_list.push_back(Production('B', '*', "*FB"));
	parser_list.push_back(Production('B', '/', "/FB"));
	parser_list.push_back(Production('B', '+', "$"));
	parser_list.push_back(Production('B', '-', "$"));
	parser_list.push_back(Production('B', ')', "$"));
	parser_list.push_back(Production('B', '#', "$"));
	parser_list.push_back(Production('F', 'i', "i"));
	parser_list.push_back(Production('F', '(', "(E)"));
}
bool isTer(char x)
{
	for (int i = 0; i < 8; i++)
	{
		if (x == ter_table[i])
		{
			return true;
		}
	}
	if (x >= '0'&&x <= '9')
	{
		return true;
	}
	if (x >= 'a'&& x<= 'z')
	{
		return true;
	}
	return false;
}
bool isNot_ter(char x)
{
	for (int i = 0; i < 5; i++)
	{
		if (x == not_ter_table[i])
		{
			return true;
		}
	}
	return false;
}
void printStack()
{
	stack<char>tmp = s;
	while (!tmp.empty())
	{
		printf("%c ", tmp.top());
		tmp.pop();
	}
	printf("\t");
}
void printStack1()
{
	stack<string>tmp = syntactic_Stack;
	while (!tmp.empty())
	{
		cout << tmp.top() ;
		tmp.pop();
	}
	printf("\t");
}
bool digit(char w)
{
	if (w >= '0'&&w <= '9')
	{
		return true;
	}
	else return false;

}
bool letter(char w)
{
	if (w >= 'a'&&w <= 'z')
	{
		return true;
	}
	else return false;
}
bool isoperator(char x)
{
	if (x == '+' || x == '-' || x == '*' || x == '/')
	{
		return true;
	}
	else return false;
}
char getw()
{
	char w;
	w = token[p_token];
	p_token++;
	return w;
}
int LL1()
{
	initparser_list();
	printf("\nLL(1)analysis:\n");
	scanner();
	p_token = 0;
	int num = 0;
	s.push('#');
	s.push('E');
	char w;
	w = getw();
	bool flag = true;
	while (flag)
	{
		printf("%d\t", num++);
		printStack();
		char x;
		if (s.size() != 0)
		{
			x = s.top();
			s.pop();
		}
		if (isTer(x))
		{
			printf("%c,%c \t", x, w);
			if (x == '#'&&w == '#')
			{
				flag = false;
			}
			if (x == w)
			{
				scanner();
				p_token = 0;
				w = getw();
				printf("match is successful!\n");
				continue;
			}
			if (x == 'i'&&(digit(w)||letter(w)))
			{
				scanner();
				p_token = 0;
				w = getw();
				printf("match is successful!\n");
				continue;
			}
			else
			{
				printf("%c", w);
				printf("error1\n");
				return 0;
			}
		}
		else if (x == '#')
		{
			if (x == w)
			{
				flag = false;
			}
			else
			{
				printf("error2\n");
				return 0;
			}
		}
		else if (isNot_ter(x) && isTer(w))
		{
			//cout << " " << x << w << " ";
			int type = 0;
			string tmp;
			for (auto u : parser_list)
			{
				if (u.not_ter == x && u.ter == w)
				{
					tmp = u.right;
					cout << x << "->" << tmp << endl;
					if (tmp == "$")
					{
						type = 1;
						break;
					}
					else
					{
						for (int i = tmp.size() - 1; i >= 0; i--)
						{
							s.push(tmp[i]);
						}
						type = 1;
						break;
					}
				}
				if (digit(w) && u.not_ter == x)
				{
					tmp = u.right;
					cout << x << "->" << tmp << endl;
					if (tmp == "$")
					{
						type = 1;
						break;
					}
					else
					{
						for (int i = tmp.size() - 1; i >= 0; i--)
						{
							s.push(tmp[i]);
						}
						type = 1;
						break;
					}
				}
				if (letter(w) && u.not_ter == x)
				{
					tmp = u.right;
					cout << x << "->" << tmp << endl;
					if (tmp == "$")
					{
						type = 1;
						break;
					}
					else
					{
						for (int i = tmp.size() - 1; i >= 0; i--)
						{
							s.push(tmp[i]);
						}
						type = 1;
						break;
					}
				}
			}
			if (type != 1)
			{
				printf("error3!\n");
				return 0;
			}
		}
		else
		{
			printf("%c %c\n", w, x);
			printf("error4!\n");
			return 0;
		}

	}
	return 1;
}
//
//
void initparser_list2()
{
	parser_list2.push_back(Production('E', 'i', "TA"));
	parser_list2.push_back(Production('E', '(', "TA"));
	parser_list2.push_back(Production('A', '+', "+TAGEQ(+)"));
	parser_list2.push_back(Production('A', '-', "-TAGEQ(-)"));
	parser_list2.push_back(Production('A', ')', "$"));
	parser_list2.push_back(Production('A', '#', "$"));
	parser_list2.push_back(Production('T', 'i', "FB"));
	parser_list2.push_back(Production('T', '(', "FB"));
	parser_list2.push_back(Production('B', '*', "*FBGEQ(*)"));
	parser_list2.push_back(Production('B', '/', "/FBGEQ(/)"));
	parser_list2.push_back(Production('B', '+', "$"));
	parser_list2.push_back(Production('B', '-', "$"));
	parser_list2.push_back(Production('B', ')', "$"));
	parser_list2.push_back(Production('B', '#', "$"));
	parser_list2.push_back(Production('F', 'i', "iPUSH(i)"));
	parser_list2.push_back(Production('F', '(', "(E)"));
}
void geq(string w)
{
	string tmp1;
	string tmp2;
	tmp2 = semantic_Stack.top();
	semantic_Stack.pop();
	tmp1 = semantic_Stack.top();
	semantic_Stack.pop();
	string ti = "t" + to_string(t_index);
	QT.push_back(qt(w, tmp1, tmp2, ti));
	++t_index;
	semantic_Stack.push(ti);
}
void printStack2()
{
	stack<string> t = semantic_Stack;
	while (!t.empty())
	{
		cout << t.top() << endl;
		t.pop();
	}

}
int CreatQuta()
{
	initparser_list2();
	printf("\nLL(1) Quta:\n");
	scanner();
	p_token = 0;
	int num = 0;
	syntactic_Stack.push("#");
	syntactic_Stack.push("E");
	char w;
	w = getw();
	bool flag = true;
	while (flag)
	{
		printf("%d\t", num++);
		printStack1();
		string x;
		if (syntactic_Stack.size() != 0)
		{
			
			x = syntactic_Stack.top();
			syntactic_Stack.pop();
		}
		if (x[0] == 'P')
		{
			while (syntactic_Stack.top()!=")")
			{
				syntactic_Stack.pop();
			}
			syntactic_Stack.pop();
			x = syntactic_Stack.top();
			cout << endl;
			continue;
		}
		if (x[0] == 'G')
		{
			stack<string> tmp = syntactic_Stack;
			string t1 = "G";
			while (tmp.top()!=")")
			{
				t1 += tmp.top();
				tmp.pop();
			}
			t1 += tmp.top();
			cout << '[' << t1 << ']';
			string t = "";
			t = t + t1[4];
			geq(t);
			while (syntactic_Stack.top() != ")")
			{
				syntactic_Stack.pop();
			}
			syntactic_Stack.pop();
			x = syntactic_Stack.top();
			cout << endl;
			continue;

		}
		if (isTer(x[0]))
		{
			cout << " " << x << " " << w << "\t";
			//printf("L(%c,%c) \t", x, w);
			if (x[0] == '#'&&w == '#')
			{
				flag = false;
			}
			if (x[0] == w)
			{
				scanner();
				p_token = 0;
				w = getw();
				printf("match is successful!\n");
				continue;
			}
			if (x[0] == 'i' && (digit(w) || letter(w)))
			{
				scanner();
				p_token = 0;
				string t = "";
				t = t + w;
				semantic_Stack.push(t);
				//cout << "[" << semantic_Stack.top() << "]";
				w = getw();
				printf("match is successful!\n");
				continue;
			}
			else
			{
				printf("%c", w);
				printf("error1\n");
				return 0;
			}
		}
		else if (x[0] == '#')
		{
			cout << " " << x << " " << w << "\t";
			if (x[0] == w)
			{
				flag = false;
			}
			else
			{
				printf("error2\n");
				return 0;
			}
		}
		else if (isNot_ter(x[0]) && isTer(w))
		{
			cout << " " << x << " " << w << "\t";
			//cout << " " << x << w << " ";
			int type = 0;
			string tmp;
			for (auto u : parser_list2)
			{
				if (u.not_ter == x[0] && u.ter == w)
				{
					tmp = u.right;
					cout << x << "->" << tmp << endl;
					if (tmp == "$")
					{
						type = 1;
						break;
					}
					else
					{
						for (int i = tmp.size() - 1; i >= 0; i--)
						{
							string t = "";
							t = tmp[i] + t;
							syntactic_Stack.push(t);
						}
						type = 1;
						break;
					}
				}
				if (digit(w) && u.not_ter == x[0])
				{
					tmp = u.right;
					cout << x << "->" << tmp << endl;
					if (tmp == "$")
					{
						type = 1;
						break;
					}
					else
					{
						for (int i = tmp.size() - 1; i >= 0; i--)
						{
							string t = "";
							t = tmp[i] + t;
							syntactic_Stack.push(t);
						}
						type = 1;
						break;
					}
				}
				if (letter(w) && u.not_ter == x[0])
				{
					tmp = u.right;
					cout << x << "->" << tmp << endl;
					if (tmp == "$")
					{
						type = 1;
						break;
					}
					else
					{
						for (int i = tmp.size() - 1; i >= 0; i--)
						{
							string t = "";
							t = tmp[i] + t;
							syntactic_Stack.push(t);
						}
						type = 1;
						break;
					}
				}
			}
			if (type != 1)
			{
				printf("error3!\n");
				return 0;
			}
		}
		else
		{
		cout << " " << x << " " << w << "\t";
			printf("error4!\n");
			return 0;
		}

	}
	return 1;
}
void printQT()
{
	for(auto u:QT)
	{

		cout << "(" << u.w << "," << u.o1 << "," << u.o2 << "," << u.res << ")\n";
	}
}
int main()
{
	WORD oneword;
	oneword.type = "null";
	initidentifier_table();
	initconstant_table();
	fstream file("data.txt");
	if (!file.is_open()) {
		cout << "Error opening file" << endl;
		return 0;
	}
	stringstream ss;
	ss << file.rdbuf();
	string str = ss.str();
	cout << "codes:  \n" << str << endl << endl;
	p_input = 0;
	int i = str.length();
	int j = 0;
	int cnt = 0;
	while (i--)
	{
		if (str.c_str()[j] != '\n')
		{
			input[cnt] = str.c_str()[j];
			++cnt;
		}
		j++;
	}
	input[cnt + 1] = '^';
	p_input = 0;
	if (LL1())
	{
		cout << "\ttrue\n";
		p_input = 0;
		CreatQuta();
		printQT();
	}
	else
	{
		cout << "\tfalse\n";
	}
	return 0;

}
