#include "preProcess.h"

char *ScanBuffer;
FILE *fp, *fp_pre;
int capacity;
int BufferFlag;
int op;
int cp;
int preProcessFlag;


void preProcess()
{
	char cur;
	int index;
	int length = 0;
	if (BufferFlag)
	{
		index = capacity / 2;
	}
	else
	{
		index = 0;
	}
	while (!feof(fp))
	{
		cur = getc(fp);
		if (cur == 9 || cur == 10 || cur == 13)
		{
//			continue;
			cur == ' ';
		}
		switch (preProcessFlag)
		{
		case 0:
		{
			if (cur == ' ')
			{
				break;
			}
			if (cur == '/')
			{
				preProcessFlag = 2;
			}
			else
			{
				preProcessFlag = 3;
			}
			break;
		}
		case 1:
		{
			if (cur == ' ')
			{
				preProcessFlag = 0;
			}
			else if (cur == '/')
			{
				preProcessFlag = 2;
			}
			else
			{
				preProcessFlag = 3;
			}
			break;
		}
		case 2:
		{
			if (cur == ' ')
			{
				preProcessFlag = 1;
			}
			else if (cur == '/')
			{
				preProcessFlag = 4;
			}
			else if (cur == '*')
			{
				preProcessFlag = 5;
			}
			else
			{
				preProcessFlag = 3;
			}
			break;
		}
		case 3:
		{
			if (cur == ' ')
			{
				preProcessFlag = 1;
			}
			else if (cur == '/')
			{
				preProcessFlag = 2;
			}
			break;
		}
		}
		if (preProcessFlag == 1 || preProcessFlag == 2 || preProcessFlag == 3)
		{
			ScanBuffer[index++] = cur;
			length++;
		}
		else if (preProcessFlag == 4)
		{
			char buff[1024];
			fgets(buff, 1024, fp);
			length--;
			index--;
			preProcessFlag = 0;
		}
		else if (preProcessFlag == 5)
		{
			char pre;
			while (!feof(fp))
			{
				pre = fgetc(fp);
				if (pre == '*' && (cur = fgetc(fp)) == '/')
				{
					length--;
					index--;
					preProcessFlag = 0;
					break;
				}
			}
		}
		if (length == capacity / 2)
		{
			break;
		}
	}
}

void init()
{
	fp = fopen("source.txt", "a+");
	if (fp == NULL)
	{
		exit(0);
	}
	capacity = 120;
	ScanBuffer = new char[capacity];
	op = cp = 0;
	memset(ScanBuffer, 0, sizeof(ScanBuffer));
	preProcessFlag = 0;
	BufferFlag = 0;
}

void pretxt()
{
	ofstream pre;
	pre.open("preProcess.txt", ios::out);
	if (!pre.is_open())
	{
		exit(0);
	}
	init();
	while (!feof(fp))
	{
		preProcess();
		BufferFlag = BufferFlag ^ 1;
		if (op == capacity)
		{
			op = 0;
		}
		if (op < capacity / 2)
		{
			while (ScanBuffer[op] != -1 && op < capacity / 2)
			{
				pre << ScanBuffer[op++];
			}
		}
		else
		{
			while (ScanBuffer[op] != -1 && op < capacity)
			{
				pre << ScanBuffer[op++];
			}
		}
	}
	pre.close();
	fclose(fp);
	delete ScanBuffer;
}