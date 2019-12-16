#include"tableExtern.h"

using namespace std;

extern table idTable;

vector<fourelement> res;	//结果四元式

struct node
{
	string value;//节点值
	string ope;//节点操作；
	vector<int> ele;		//节点元素
	node *left, *right;//左右节点
};

vector<node*> father;//记录所有的父节点,每次插入都要遍历该数组

