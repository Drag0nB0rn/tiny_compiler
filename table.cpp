#include "table.h"

table idTable;	//标识符表，即符号表

vector<fourelement> four;			//四元式序列

void table::clear()//各表初始化
{
	synblTable.clear();
	tapelTable.clear();
	ainflTable.clear();
	rinflTable.clear();
	pfinflTable.clear();
	conslTable.clear();
	lenlTable.clear();
	vallTable.clear();
}

table::table()
{

	clear();


}

string table::getFunName(int pos)
{
	return synblTable[pos].name;
}

int table::getAddr(int pos)
{
	return synblTable[pos].addr;
}

synblCat table::getCat(int pos)
{

	return synblTable[pos].cat;
}

synblTval table::getTval(int pos)
{
	return synblTable[pos].type;
}

int table::size()
{
	return synblTable.size();
}

bool table::isactive(int pos)
{
	return synblTable[pos].active;
}

int table::getValue(int pos)
{
	if (synblTable[pos].type == tvalInt) {//应返回值，暂时返回地址，后期修改
		return synblTable[pos].addr;
	}
	return 0;
}

bool table::isTmp(int pos)
{
	return false;
}
