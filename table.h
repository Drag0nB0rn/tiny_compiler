#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<stack>
using namespace std;

/*
enum tokenType {	//token类型
	tokenKeyWord,	//关键字
	tokenIde,			//标识符
	tokenDeli,			//界符
	tokenConst,		//常量
};

struct  token
{
	
	
	

	tokenType type;	//类型
	int position;		//坐标
};
*/

enum synblTval { //类型
	tvalInt,		// 0 整型
	tvalFloat,	// 1 浮点型
	tvalChar,	// 2 字符型
	tvalBool,	// 3 bool
	tvalArry,	// 4 数组型
	tvalStruct, // 5 结构体
	tvalString,	// 6 字符串
};

enum synblCat { //符号种类
	catFun,			// 0 函数
	catConst,		// 1 常量
	catType,		// 2 类型
	catDomain,	// 3 域名
	catV,				// 4 变量
	catVn,			// 5 换名形参
	catVf,			// 6 赋值形参
};

enum delimiter {//界符

};

enum Keyword {	//

};

struct synbl{  //符号表

	string name; //名字
	synblTval type;//类型
	int typePosition;	//类型坐标，好像没啥用？
	synblCat cat;//种类
	int catPos;//种类坐标 
	int addr;		//地址
	int length;		//该标识符所占存储单元
	bool active;	//活跃与否
	stack<bool> activeStack;//四元式中的标识符活跃信息
};

struct tapel //类型表
{
	synblTval tval;//类型
	int position;	//坐标（0开始）
};

struct ainfl   //数组
{
	int low=0;				//数组下界
	int up;					//数组上界

	tapel type;		//类型
	int position;	//坐标
	int arryClen;			//数组长度  字长
};

struct  rinfl //结构体
{
	string rinflId;		//结构的域名
	int rinflOff;			//区距
	//synblTval structType; //类型 指针
	tapel type;			//类型
	int position;		//坐标
};


struct pfinfl  //函数
{
	int pfinflLevel;	//层次号
	int pfinflOff;		//区距
	int pfinflFn;		//参数个数
	int pfinflParam;	//参数表  指针
	int entry;		//入口地址
};

struct consl	//常数
{
	string value;	//常数值
};

struct lenl     //长度表 
{
	int length;
};

struct  vall   //活动记录
{
	//
};

class table//符号表，在语义分析时将标识符的各信息填入词表
{
public:


	table();

	string getFunName(int pos);

	int getAddr(int pos);//获得标识符地址

	synblCat getCat(int pos);//获得标识符种类  是函数？ 常量？ 变量？

	synblTval getTval(int pos);//获得标识符类型   int，float，char，。。。

	int size(); //返回synblTable符号总表的大小，即标识符个数

	bool isactive(int pos);//返回当前标识符活跃标志

	int getValue(int pos);//返回pos标识符的值，仅当pos为变量是有效，若为其他值，返回0

	bool isTmp(int pos);//是否为临时变量

	bool isConst(int pos);//是否为常量

	int getConst(int pos);//返回常量的值

	void setActive(int pos,bool active);//将标识符active设为true

	int insertConst(int curConst);//插入常数
	//~table();
	
	void clear();//初始化各表

	
private:

	vector<synbl> synblTable;	//符号表总表
	vector<tapel> tapelTable;	//类型表
	vector<ainfl> ainflTable;		//数组表
	vector<rinfl> rinflTable;		//结构表
	vector<pfinfl> pfinflTable;	//函数表
	vector<consl> conslTable;	//常数表
	vector<lenl> lenlTable;		//长度表
	vector<vall> vallTable;		//活动记录表

};




/*
暂定：

对于if语句

1	( if , t1 ,  ,addr)	//如果t1为假，则跳转至目标地址addr 此例中为4,即else后的指令地址
2	( =, 2  ,  ,a	)
3	( else ,   ,  ,  addr   )//此处，在t1位true的情况下，应保存以上操作后结果。并跳出else后的操作 addr 为目标地址
4	( =, 3  ,  ,  a)
4	(  ,	,	,	)//此处已跳出if else语句；



*/

//暂时不写带函数的，即只有一张表，后期再添加多函数功能。

struct fourelement
{
	string fix;//运算符 +-*/ > < = if，else fun call endcall
	int pos1=-1, pos2=-1, pos3=-1;//三个目标操作数的地址,全部初始化为-1，-1代表空
	bool active1, active2, active3;//三个操作数的活跃信息
};



/*
//前段
void lex();		//词法分析，逐步解析输入流，每得到一个token就调用语法分析，若分析成功，则继续解析token，否则报错

bool sym();	//语法分析，在一个token到来之后，执行语法分析，至当前符空，并在栈顶为语义动作时，调用语义分析，若成功，则返回true，否则返回false。

bool syant();	//语义分析，在语法分析遇到语义动作后执行语义动作，并填符号表，最终给出四元式；

//后端
void better(); //在语义分析结束后，优化四元式,

void compiler();	//将四元式翻译成汇编，并附带寄存器优化。
*/
