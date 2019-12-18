#include"tableExtern.h"
#include<stack>

using namespace std;


struct reg     //寄存器
{
	bool act;	//标识符，判断当前值是否活跃

	int value;	//当前地址，暂时只处理int
};
reg ax;//单寄存器

string obj;				//目标代码

string ifProcess;//if过程名
int ifProNum;//if过程标号
stack<string> iEndfStack;
stack<string> elseStack;

string whiProcess;//while过程名
int whiProNum;//while过程标号
stack<string> whileEndStack;
stack<string> doStack;

string cmpProcess;//比较产生的过程
int cmpProNum;//比较过程标号

void saveax()		//当要改变ax时，判断ax当前值是否活跃，并判断是否保存
{
	if (ax.act) {	//MOV [ax.value],ax
		obj += "MOV [";
		obj += ax.value;
		obj += "],ax";
	}
}

void setax(int pos)
{
	ax.value = idTable.getAddr(pos);
	ax.act = idTable.isactive(pos);
}

//每次改变ax内容是都要判断是否要保存之前ax中的值。
void opeAxPos(string ope, int pos)   //ope ax,[pos]
{
	int par = idTable.getAddr(pos);
	saveax();
	obj += ope;
	obj += " ax,[";
	obj += par;
	obj += "]\n";
	setax(pos);
}


void opePosAx(string ope, int pos)	//ope [pos],ax
{
	int par = idTable.getAddr(pos);
	obj += ope;
	obj += " [";
	obj += par;
	obj += "],ax\n";
}


void opePosPos(string ope, int pos1, int pos2)//ope [pos1],[pos2]
{
	opeAxPos("MOV",pos1);//MOV  ax,[pos1]
	opeAxPos(ope, pos2);//ope ax,pos2
}

void ope_1(string ope,int pos)//+  -  *  /
{
	int pos1, pos2, pos3;

	fourelement curfour;
	curfour = four[pos];//当前四元式

	//三个参数的地址
	pos1 = curfour.pos1;
	pos2 = curfour.pos2;
	pos3 = curfour.pos3;

	//最后要将ax指向pos3，在改变ax之前根据pos3活跃与否，决定是否将ax写入pos3
	if (ax.value != pos1&&ax.value != pos2) {//ax!=pos1 && ax!=pos2
		opePosPos(ope, pos1, pos2);
	}
	else if (ax.value == pos2) {//ax==pos2    ADD ax,[pos1]
		if (ope == "ADD" | ope == "MUL") {
			opeAxPos(ope, pos1);
		}
		else {
			opePosPos(ope, pos1, pos2);
		}
	}
	else {//ax==pos1	 |	ax==pos&&ax==pos2			ADD ax,[pos2]  
		opeAxPos(ope, pos2);
	}

	setax(pos3);//将ax指向pos3

}

void opeCmp(string ope, int pos)
{
	int pos1, pos2, pos3;
	pos1 = idTable.getAddr( four[pos].pos1), pos2 = idTable.getAddr(four[pos].pos2), pos3 = idTable.getAddr(four[pos].pos3);
	//CMP [pos1],[pos2]
	obj += "CMP ";
	obj += "[", obj += pos1, obj += "],";
	obj += "[", obj += pos2, obj += "]\n";

	//ope cmpProcess1
	obj += ope,obj+=" ", obj += cmpProcess, obj += to_string(cmpProNum);

	//MOV [pos3],1
	obj += "\nMOV [", obj += pos3, obj += "],1\n";

	//JMP cmpProcess2
	obj += "JMP ", obj += cmpProcess, obj += to_string(cmpProNum + 1);

	//cmpProcess1:
	obj += cmpProcess, obj += to_string(cmpProNum), obj += ":\n";

	//MOV t,0
	obj+="MOV [", obj += pos3, obj += "],0\n";

	//cmpProcess2:
	obj += cmpProcess, obj += to_string(cmpProNum + 1), obj += ":\n";

}

void objGen()
{


	//以下为汇编初始化
	ax.act = false, ax.value = -1;



	int pos = 0;	//指示器
	ifProcess += "ifProc";
	whiProcess += "whiProc";
	cmpProcess += "cmpProc";

	ifProNum = 1;
	whiProNum = 1;
	cmpProNum = 1;
	//进行目标代码生成
	int len = four.size();
	fourelement curfour;
	while (pos < len)
	{

		curfour = four[pos];//当前四元式


		if (curfour.fix == "+") {
			ope_1("ADD", pos);
		}
		else if (curfour.fix == "-") {
			ope_1("SUB", pos);
		}
		else if (curfour.fix == "*") {
			ope_1("MUL", pos);
		}
		else if (curfour.fix == "/") {
			ope_1("DIV", pos);
		}
		else if (curfour.fix == "=") {  //(=,  a,   ,t   )
			if (ax.value == idTable.getAddr(curfour.pos1)) {//MOV [pos3],ax
				opePosAx("MOV", curfour.pos3);
			}
			else {// MOV ax,[pos1];   MOV [pos3],ax
				opeAxPos("MOV", curfour.pos1);
				opePosAx("MOV", curfour.pos3);
			}
		}
		else if (curfour.fix == ">") {//cmp pos1,pos2;   
			opeCmp("JB",pos);
		}
		else if (curfour.fix == "<") {
			opeCmp("JA", pos);
		}
		else if (curfour.fix == "if") { //( if , t,  ,_pos )如果t为假，则跳到_pos,否则顺序执行

			/*
			if(){
				 ifProcess0
				JMP ifProcess2
			}
			else{
				ifProcess1
			}
			ifProcess2
			*/

			//若if判定为假，则进入过程1  CMP 0,[pos1]
			obj += "CMP 0,[";
			obj += idTable.getAddr(four[pos].pos1);
			obj += "]\n";

			//JE ifProcess1
			obj += "JE ";
			obj += ifProcess;
			obj += to_string(ifProNum);
			obj += "\n";
			string tmp = ifProcess;
			tmp += to_string(ifProNum);
			elseStack.push(tmp);//process1压栈
			tmp.clear();
			tmp = ifProcess;
			tmp += to_string(ifProNum + 1);
			elseStack.push(tmp);//process2压栈
			iEndfStack.push(tmp);//process2压栈；
			ifProNum += 2;
		}
		else if (curfour.fix == "else") {
			//JMP ifProcess2
			obj += "JMP ";//若执行ifProcess0，则需结束过程后跳转至pocess2，也就是ifelse结束
			obj += elseStack.top(), elseStack.pop();
			obj += "\n";

			//ifProcess1:
			obj += elseStack.top(), elseStack.pop();
			obj += ":\n";
		}
		else if (curfour.fix == "ifEnd") {//结束else之后，跳出ifelse的程序段标识
			//ifProcess2:
			obj += iEndfStack.top(), iEndfStack.pop();//ifProcess2:
			obj += ":\n";
		}
		else if (curfour.fix == "while") {//while开始

			/*
			pro1:		 while
			//运算
			CMP t1,1		do
			JNZ	pro2
			//运算
			JMP pro1; endwhile
			pro2:
			*/
			obj += whiProcess;
			obj += to_string(whiProNum);
			obj += ":\n";
			string tmp = whiProcess;
			tmp += to_string(whiProNum+1);
			whileEndStack.push(tmp);//process2压栈
			doStack.push(tmp);//process2压栈
			tmp.clear();
			tmp = whiProcess;
			tmp += to_string(whiProNum);
			whileEndStack.push(tmp);//process1压栈
			whiProNum += 2;
		}
		else if (curfour.fix == "do") {//判断条件  (do, t,,)
			obj += "CMP [";
			obj += idTable.getAddr(curfour.pos1);
			obj += "],1\n";
			obj += "JNZ ";
			obj += doStack.top(), doStack.pop();
		}
		else if (curfour.fix == "whileEnd") {//while结束标志，根据判定条件决定是否要结束
			obj += "JMP ";
			obj += whileEndStack.top(), whileEndStack.pop();
			obj += "\n";
			obj += whileEndStack.top(), whileEndStack.pop();
			obj += ":\n";
		}
		else if (curfour.fix == "call") {//调用函数

		}
		else if (curfour.fix == "return") {//函数返回

		}
		else if (curfour.fix == "funStart") {//函数定义开始
			obj+=idTable.getFunName(curfour.pos1);
			obj += " PROC NEAR\n";
		}
		else if (curfour.fix == "funEnd") {//函数定义结束
			obj += "RET\n";
			obj += idTable.getFunName(curfour.pos1);
			obj += " ENDP\n";
		}

	}

	
}


