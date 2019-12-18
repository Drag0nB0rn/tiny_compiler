#include"tableExtern.h"

using namespace std;

extern table idTable;

vector<fourelement> res;	//结果四元式
vector<fourelement> basicBlock;//基本块
vector<fourelement> tmpRes;//优化后的基本块

struct node
{
	int number;//节点编号
	//int value;//如果是常数，则有值
	string fix;//节点操作；
	vector<int> ele;		//节点元素
	int left, right;//左右节点
};

vector<node> father;//记录所有的父节点,每次插入都要遍历该数组

/*



*/
int find(int pos)
{
	for (int i = father.size() - 1; i >= 0; i--) {
		for (int j = 0; j < father[i].ele.size(); j++) {
			if (father[i].ele[j] == pos) {
				return i;
			}
		}
	}
	return -1;
}

int findConst(int curConst)//
{
	for (int i = father.size() - 1; i >= 0; i--) {//如果是常量，就一定是前驱
		if (idTable.isConst(father[i].ele[0])) {
			if (curConst == idTable.getConst(father[i].ele[0]))
				return i;
		}
	}
	return -1;
}


int findCom(int pos)
{
	bool flag = false;
	for (int i = father.size(); i>=0; i--) {
		if (father[i].fix == basicBlock[pos].fix) {
			if (father[i].left != -1) {
				for (auto it : father[father[i].left].ele) {
					if (it == basicBlock[pos].pos1) {
						flag = true;
						break;
					}
				}
				if (flag) {//如果左值相同
					flag = false;
					if (father[i].right != -1) {
						for (auto it : father[father[i].right].ele) {
							if (it == basicBlock[pos].pos2) {
								flag = true;
								break;
							}
						}
					}
					if (flag) {//如果右值也相同
						return i;
					}
				}
			}
		}
	}
	return -1;
}

void dagSwap(int pos)
{
	if (idTable.isTmp(father[pos].ele[0])) {
		for (int i = 1; i < father[pos].ele.size(); i++) {
			if (!idTable.isTmp(father[pos].ele[i])) {
				swap(father[pos].ele[0], father[pos].ele[i]);
				return;
			}
		}
	}
}

bool isCacu(string s)
{
	if (s == "+" | s == "-" | s == "*" | s == "/" | s == ">" | s == "<" |s=="=")
		return true;
	return false;
}

void deleM(int dad,int i)
{
	if (idTable.isTmp(basicBlock[i].pos3)) {
		for (int j = father.size()-1; j>=0, j != dad; j--) {//若A为主标记，不删除
			vector<int>::iterator it = father[j].ele.begin()+1;
			if(!father[i].ele.empty()){
				for (; it != father[j].ele.end(); it++) {
					if ((*it) == basicBlock[i].pos3) {
						father[j].ele.erase(it);
						break;
					}
				}
			}
		}
	}
}


void fourEq(int i)
{
	int dad;
	dad = find(basicBlock[i].pos1);
	if (dad != -1) {//如果找到了B
		father[dad].ele.push_back(basicBlock[i].pos3);
		//if (!idTable.isTmp(basicBlock[i].pos3)) {//如果不是临时变量，则作为主标记
			//swap(father[dad].ele[0], father[dad].ele[father[dad].ele.size() - 1]);
		//}
	}
	else {//如果没找到B
		node newNode;
		newNode.number = father.size();
		newNode.ele.push_back(basicBlock[i].pos1);
		newNode.ele.push_back(basicBlock[i].pos3);
		newNode.left = newNode.right = -1;
		//if (!idTable.isTmp(basicBlock[i].pos3)) {
			//swap(newNode.ele[0], newNode.ele[1]);
		//}
		father.push_back(newNode);
	}
	deleM(dad, i);
}

int CaculateConst(int i)
{
	int resConst=0;
	int  const1 = idTable.getConst(basicBlock[i].pos1), const2 = idTable.getConst(basicBlock[i].pos2);
	if (basicBlock[i].fix == "+") {
		resConst = const1 + const2;
	}
	else if (basicBlock[i].fix == "-") {
		resConst = const1 - const2;
	}
	else if (basicBlock[i].fix == "*") {
		resConst = const1*const2;
	}
	else if (basicBlock[i].fix == "/") {
		resConst = const1 - const2;
	}
	else if (basicBlock[i].fix == ">") {
		resConst = (const1 > const2) ? 1 : 0;
	}
	else if (basicBlock[i].fix == "<") {
		resConst = (const1 < const2) ? 1 : 0;
	}
	return resConst;
}

void dag()
{
	tmpRes.clear();
	father.clear();
	int left, right,dad;
	for (int i = 0; i < basicBlock.size(); i++)//构造基本块内的DAG
	{
		if (basicBlock[i].fix == "=") {
			fourEq(i);
		}
		else if (isCacu(basicBlock[i].fix)) {
			if (idTable.isConst(basicBlock[i].pos1) && idTable.isConst(basicBlock[i].pos2)) {//如果是常数表达式
				int  resConst=CaculateConst(i);
				int constPos = findConst(resConst);
				if (constPos != -1) {//如果找到对应常量
					father[constPos].ele.push_back(basicBlock[i].pos3);
				}
				else {//如果没有，则在符号表中插入该常数，并新建节点
					node newNode;
					int pos = idTable.insertConst(resConst);//在符号表中插入新的常量
					newNode.left = newNode.right = -1;
					newNode.number = father.size();
					newNode.ele.push_back(pos);
					newNode.ele.push_back(basicBlock[i].pos3);
					father.push_back(newNode);
					constPos = father.size() - 1;
				}
				deleM(constPos, i);
			}
			else {//如果是常规表达式
				int pos = findCom(i);
				if (pos != -1) {//如果存在公共表达式
					father[pos].ele.push_back(basicBlock[i].pos3);
				}
				else {//如果不存在
					node newNode;
					newNode.fix = basicBlock[i].fix;
					int leftPos, rightPos;
					leftPos = find(basicBlock[i].pos1);//寻找是否有左子树节点
					if (leftPos == -1) {//若左子树节点不存在，则创建左子树节点
						node leftNode;
						leftNode.left = leftNode.right = -1;
						leftNode.ele.push_back(basicBlock[i].pos1);
						leftPos=leftNode.number = father.size();
						father.push_back(leftNode);
					}
					rightPos = find(basicBlock[i].pos2);//寻找右子树结点
					if (rightPos == -1) {//若右子树节点不存在
						node rightNode;
						rightNode.left = rightNode.right = -1;
						rightNode.ele.push_back(basicBlock[i].pos1);
						rightPos= rightNode.number = father.size();
						father.push_back(rightNode);
					}
					newNode.left = leftPos;
					newNode.right = rightPos;
					newNode.number = father.size();
					newNode.fix = basicBlock[i].fix;
					newNode.ele.push_back(basicBlock[i].pos3);
					father.push_back(newNode);
					pos = father.size() - 1;
				}
				deleM(pos, i);//删除其他节点中的pos3
			}
		}
	}

	fourelement tmp;
	if (!isCacu(basicBlock[0].fix)) {
		tmpRes.push_back(basicBlock[0]);
	}

	for (int i = 0; i < father.size(); i++) {
		tmp.fix = father[i].fix;
		if (father[i].left == -1 && father[i].right == -1) {//如果是叶节点
			tmp.pos1 = father[i].ele[0];
			if (!father[i].ele.empty()) {
				for (int j = 1; j < father[i].ele.size(); j++) {
					if (!idTable.isTmp(father[i].ele[j])) {
						tmp.pos3 = father[i].ele[j];
						tmpRes.push_back(tmp);
					}
				}
			}
		}
		else {//不是叶节点
			if (!father[i].ele.empty()) {
				if (father[i].left != -1) {
					tmp.pos1 = father[father[i].left].ele[0];
				}
				if (father[i].right != -1) {
					tmp.pos2 = father[father[i].right].ele[0];
				}
				tmpRes.push_back(tmp);
				for (int j = 1; j < father[i].ele.size(); j++) {
					if (!idTable.isTmp(father[i].ele[j])) {
						tmp.fix = "=";
						tmp.pos1 = father[i].ele[0];
						tmp.pos3 = father[i].ele[j];
						tmpRes.push_back(tmp);
					}
				}
			}
		}
	}

	if (!isCacu(basicBlock[basicBlock.size() - 1].fix)) {
		tmpRes.push_back(basicBlock[basicBlock.size() - 1]);
	}

	for (int i = 0; i < tmpRes.size(); i++)//保存结果四元式
		res.push_back(tmpRes[i]);
}
int divedBlock(int start)
{
	basicBlock.clear();
	tmpRes.clear();
	int pos = start;
	string fix;
	while (pos<four.size())
	{
		fix = four[pos].fix;
		if ((fix == "if") | (fix == "ifEnd") | (fix == "else") | (fix == "elseEnd")) {//碰到 if ifEnd else elseEnd则一个基本块结束
			tmpRes.push_back(four[pos]);
			pos++;
			break;
		}
		if ((fix == "while")|(fix=="funStart")) {//
			break;
		}
		if ((fix == "do") | (fix == "endWhile")|(fix=="funEnd")) {//
			tmpRes.push_back(four[pos]);
			pos++;
			break;
		}
		if (fix == "call") {
			tmpRes.push_back(four[pos]);
			pos++;
			break;
		}
		tmpRes.push_back(four[pos]);
		pos++;
	}
	basicBlock = tmpRes;
	return pos;
}

void activeSet()//设置活跃信息变量
{
	for (int i = 0; i < idTable.size(); i++) {
		if (idTable.isTmp(i)) {
			idTable.setActive(i, false);
		}
		else {
			idTable.setActive(i, true);
		}
	}
	for (int i = res.size(); i >= 0; i--) {
		res[i].active3 = idTable.isactive(res[i].pos3);
		idTable.setActive(res[i].pos3, false);
		res[i].active2 = idTable.isactive;
		idTable.setActive(res[i].pos2, true);
		res[i].active1 = idTable.isactive(res[i].pos1);
		idTable.setActive(res[i].pos1, true);
	}
}

void optimize()
{
	int pos = 0;
	while (pos < four.size()) {
		pos=divedBlock(pos);
		dag();
	}
	activeSet();//设置活跃信息变量

}
