#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<map>

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
	//catKeyWord	// 7 关键字
};

enum delimiter {//界符

};

enum Keyword {	//

};

struct synbl{  //符号表

	string name; //名字
	synblTval type;//类型
	int typePosition;	//类型坐标   
	synblCat cat;//种类
	int addr;		//地址
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

struct lenl     //长度
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



	~table();
	
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


