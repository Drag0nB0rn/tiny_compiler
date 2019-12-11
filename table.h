#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<map>

using namespace std;

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
	catKeyWord	// 7 关键字
};

struct synbl   //符号表
{
	string name; //名字
	synblTval type;//类型
	int typePosition;	//类型坐标
	synblCat cat;//种类
	int addr;		//地址
};

struct typel //类型表
{
	synblTval tval;//类型
	int position;	//坐标（0开始）
};



struct arryTval   //数组
{
	int low=0;				//数组下界
	int up;					//数组上界

	//synblTval arrtCtp;	//数组类型 指针

	typel type;		//类型
	int position;	//坐标
	int arryClen;			//数组长度  字长
};

struct  rinflTval //结构体
{
	string rinflId;		//结构的域名
	int rinflOff;			//区距
	//synblTval structType; //类型 指针
	typel type;			//类型指针
	int position;		//坐标
};


struct pfinfl  //函数
{
	int pfinflLevel;	//层次号
	int pfinflOff;		//区距
	int pfinflFn;		//参数个数
	int pfinflParam;	//参数表  指针
	//auto pfinflEntry;	//入口地址
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


class table
{
public:


	table();

	~table();
	
	void init();


private:
	vector<synbl> synblTable;



};

table::~table()
{
}

