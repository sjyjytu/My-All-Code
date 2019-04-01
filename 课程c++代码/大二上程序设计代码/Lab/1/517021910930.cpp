#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stack>
#include <cmath>

using namespace std;
int Factorial(int n)
{
	/*计算阶乘*/
	if (n == 0)
	{
		return 1;
	}
	int result = 1;
	for (int i = 1; i <= n; i++)
	{
		result *= i;
	}
	return result;
}
string doubleToString(double num)
{
	char str[256];
	sprintf_s(str, "%lf", num);
	string result = str;
	return result;
}
void smartPush(stack<char> &stk, double d,int backoff)
{
	string s = doubleToString(d);
	if (backoff==0)
	{
		for (int i = 0; i < s.size(); i++)
		{
			stk.push(s[i]);
		}
	}
	else if (backoff == 1)
	{
		for (int i = s.size()-1; i >= 0; i--)
		{
			stk.push(s[i]);
		}
	}
	else
	{
		/*倒车入库，但是保留N*/
		if (s[0]=='-')
		{
			for (int i = s.size() - 1; i >= 1; i--)
			{
				stk.push(s[i]);
			}
			stk.push('N');
		}
		else
		{
			for (int i = s.size() - 1; i >= 0; i--)
			{
				stk.push(s[i]);
			}
		}
	}
}
void error(string err)
{
	ofstream of("lab1_output.txt", ios::app);
	if (!of)
	{
		cerr << "open output file wrong!";
		exit(1);
	}
	of << "error" << endl;
}
int copeSign(stack<char> &c, bool &illegal)
{
	/*读取符号，可以判别符号是否合法（符号中带除+-外字符的为不合法）*/
	/*数字前可能有一个或多个符号,可处理-+,不可处理N*/
	int sign = 1;  //正负号
	while (!isdigit(c.top()) && c.top()!='N')
	{
		switch (c.top())
		{
		case '+':
			sign *= 1;
			break;
		case '-':
			sign *= (-1);
			break;
		default:
			error("illegal operator before number");
			illegal = 1;
			break;
		}
		c.pop();
	}
	return sign;
}
double inNum(stack<char> &c, bool &illegal, int & intPart,bool &isfloat,int sign = 1)
{
	/*读取数字，当确认top为数字时使用本函数，可能是小数*/
	int intNum = 0;  //整数部分
	int doubleNum = 0;//小数部分
	int doubleLength = 1;  //记录小数部分要除以的数，1，10，100...,
	while (!c.empty()&&isdigit(c.top()))
	{
		intNum = intNum * 10 + (c.top() - '0');
		c.pop();
	}
	intPart = sign * intNum;
	isfloat = 0;  //返回不是小数
	if (c.empty()||c.top() != '.')
		return sign * double(intNum);
	else
	{
		c.pop();  //pop掉'.'
		while (!c.empty() && isdigit(c.top()))
		{
			doubleNum = doubleNum * 10 + (c.top() - '0');
			c.pop();
			doubleLength *= 10;
			if (doubleNum!=0)
				isfloat = 1;  //返回是小数
		}
		double tmp = double(doubleNum) / doubleLength;
		return sign*(double(intNum) + tmp);
	}
}
double inPureNum(stack<char> &c, bool &illegal, int & intPart, bool &isfloat, int sign = 1)
{
	/*读取纯数字，只允许N，不允许+-*/
	if (c.top() == 'N')
	{
		sign *= -1;
		c.pop();
	}
	return inNum(c, illegal, intPart, isfloat, sign);
}

double inSignNum(stack<char> &c, bool &illegal, int & intPart, bool &isfloat)
{
	/*读取带符号数字,允许+-和N*/
	if (c.empty())
	{
		illegal = 1;
		return 1;
	}
	int sign = copeSign(c, illegal);
	if (c.empty())
	{
		illegal = 1;
		return 1;
	}
	return inPureNum(c, illegal, intPart, isfloat, sign);
}

string pureCal(stack<char> &operate, bool &illegal)
{
	/*不带括号的纯运算*/
	/*本函数自带报错功能*/
	/*优先级是 !> / * % > + -                          */

	/*这里借助两个临时的stack分别存储数字和运算符,边储存边运算*/
	stack<double> Num;
	stack<char> Oper;

	/*先处理阶乘*/
	stack<char> reverseOperate;  //反向operate
	int firintPart = 0;  //记录前面数字的整数部分，方便！操作
	bool isfloat = 0;  //记录是否是小数，方便！操作
	while (!operate.empty() && !illegal)
	{
		if (operate.top() == '!')
		{
			if (reverseOperate.empty()||!isdigit(reverseOperate.top()))
			{
				/*n! n<0  n+! 等情况都会导致这个触发*/
				error("something not expected before !");
				illegal = 1;
				break;
			}
			else
			{
				operate.pop();
				double n1 = inPureNum(reverseOperate, illegal, firintPart, isfloat);
				if (isfloat)
				{
					illegal = 1;
					error("double number for operator!");
				}
				else
				{
					int result = Factorial(firintPart);
					smartPush(reverseOperate, result,1);  //string(result)要倒车入库
				}
			}
		}
		else if (isdigit(operate.top())|| operate.top()=='N')
		{
			char t5 = operate.top();
			double temp = inPureNum(operate, illegal, firintPart, isfloat);
			smartPush(reverseOperate, temp, 2);  //倒车入库，方便阶乘取出来
			/*但也要注意，待会反转的时候，数字是整数小数颠倒的*/
		}
		else
		{
			//是其他操作符
			reverseOperate.push(operate.top());
			operate.pop();
		}
	}
	/*将reverseOper反转到operate中*/
	while (!reverseOperate.empty() && !illegal)
	{
		if (isdigit(reverseOperate.top()) || reverseOperate.top() == 'N')
		{
			double temp = inPureNum(reverseOperate, illegal, firintPart, isfloat);
			smartPush(operate, temp, 2);
		}
		else
		{
			operate.push(reverseOperate.top());
			reverseOperate.pop();
		}
	}

	/*处理乘除*/
	/*经过前面的处理，第一个和最后一个一定是数*/
	double frontNum = 0;
	double backNum = 1;
	double result = 0;
	while (!operate.empty() && !illegal)
	{
		/*读一个纯数字和一个字符*/
		Num.push(inPureNum(operate, illegal, firintPart, isfloat));
		if (!operate.empty())
		{
			Oper.push(operate.top());
			operate.pop();
			switch (Oper.top())
			{
			case '+':
				if (!isdigit(operate.top()) && operate.top() != 'N')
				{
					int sign = copeSign(operate, illegal);  //处理+-+-++--之类的情况
					if (sign == -1)
					{
						Oper.pop();
						Oper.push('-');
					}
				}
				break;
			case '-' :
				if (!isdigit(operate.top()) && operate.top() != 'N')
				{
					int sign = copeSign(operate, illegal);
					if (sign == -1)
					{
						Oper.pop();
						Oper.push('+');
					}
				}
				break;
			case '*' :
				Oper.pop();
				frontNum = Num.top();
				Num.pop();
				backNum = inSignNum(operate, illegal, firintPart, isfloat);
				result = frontNum * backNum;
				smartPush(operate, result, 2);
				break;
			case '/' :
				Oper.pop();
				frontNum = Num.top();
				Num.pop();
				backNum = inSignNum(operate, illegal, firintPart, isfloat);
				result = frontNum / backNum;
				smartPush(operate, result, 2);
				break;
			case '%' :
				Oper.pop();
				frontNum = Num.top();
				Num.pop();
				if (isfloat)
				{
					illegal = 1;
					error("the number before % is float");
				}
				backNum = inSignNum(operate, illegal, firintPart, isfloat);
				if (isfloat)
				{
					illegal = 1;
					error("the number after % is float");
				}
				result = fmod(frontNum ,backNum);
				smartPush(operate, result, 2);
				break;
			default:
				error("illegal character");
				illegal = 1;
				break;
			}
		}
	}
	/*乘除算完了，现在Oper中只剩+-了*/
	/*注意！此时的Oper和Num是从右到左的，应该反一反*/
	stack<double> rNum;
	stack<char> rOper;
	while (!Oper.empty() && !illegal)
	{
		rOper.push(Oper.top());
		Oper.pop();
	}
	while (!Num.empty()&&!illegal)
	{
		rNum.push(Num.top());
		Num.pop();
	}
	while (!rOper.empty() && !illegal)
	{
		if (rOper.top() == '+')
		{
			rOper.pop();
			double rNum1 = rNum.top();
			rNum.pop();
			double rNum2 = rNum.top();
			rNum.pop();
			rNum.push(rNum1 + rNum2);
		}
		else
		{
			rOper.pop();
			double rNum1 = rNum.top();
			rNum.pop();
			double rNum2 = rNum.top();
			rNum.pop();
			rNum.push(rNum1 - rNum2);
		}
	}
	/*最后Num中只有一个元素，就是这个小式子的运算结果*/
	if (!illegal)
	{
		string str = doubleToString(rNum.top());
		if (str[0] == '-')
			str[0] = 'N';
		return str;
	}
	else
		return "0";  //如果式子不合法，就返回"0"
}
string calculate(string expression)
{
	/*传入表达式，对其进行判断是否规范以及进行运算*/
	/*从左到右读取expression到bracket中，提出一对括号中的内容到operate中进行运算，
	结果再push进bracket*/
	if (expression[0] == '+' || expression[0] == '-')
		expression = '0' + expression;
	bool illegal = 0;  //合法性
	int leftbracketNum = 0;  //左括号数
	stack<char> bracket;  //读取表达式的所有东西，但主要用于处理括号
	stack<char> operate;  //临时处理数字和+-*/的运算
	for (int i = 0; i <= expression.size() - 1; i++)
	{
		char test = expression[i];
		if (illegal == 1)
		{
			break;
		}
		if (expression[i] == ' ')
			continue;
		else if (expression[i] == '(')
		{
			leftbracketNum++;
			bracket.push(expression[i]);
		}
		else if (expression[i] >= '0'&&expression[i] <= '9' || expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/' || expression[i] == '.' || expression[i] == '!' || expression[i] == '%')
		{
			bracket.push(expression[i]);
		}
		
		/* 读到')'且leftbracketNum>0和 读到';'且leftbracketNum = 0 会产生一次运算*/
		else if (expression[i] == ')')
		{
			if (leftbracketNum>0)
			{
				/*找到一个要进行运算的表达式*/
				leftbracketNum--;
				while (bracket.top() != '(')
				{
					char tmp;
					tmp = bracket.top();
					bracket.pop();
					operate.push(tmp);  //注意！这样得来的operate是bracket的倒序版
										//而bracket又是string的倒序，所以operate是正序
				}
				bracket.pop();  //除去(
				/*开始运算*/
				string result = pureCal(operate, illegal);
				if (!illegal)
				{
					for (int i = 0; i < result.size(); i++)
					{
						bracket.push(result[i]);
					}
				}
			}
			else
			{
				error("expect a (");
				break;
			}
		}
		else if (expression[i] == ';')
		{
			if (leftbracketNum == 0)
			{
				/*找到一个要进行运算的表达式*/
				while (!bracket.empty())
				{
					char tmp;
					tmp = bracket.top();
					bracket.pop();
					operate.push(tmp);  //注意！这样得来的operate是原本的倒序版
				}
				/*开始运算*/
				string ANS = pureCal(operate, illegal);  //最终结果
				ofstream of("lab1_output.txt", ios::app);
				if (!of)
				{
					cerr << "open output file wrong!";
					exit(1);
				}
				if (!illegal)
				{
					/*将结果输出到文件，这里的作用是将string类型的结果转为double*/
					/*以便省去小数部分多余的零，如果是整数，则只输出整数部分*/
					/*实现方法是先将结果倒入tmp中，再利用inPureNum取到result*/
					stack<char> tmp;
					for (int i = ANS.size() - 1; i >= 0; i--)
					{
						tmp.push(ANS[i]);
					}
					int intPart = 0;
					bool isFloat = 0;
					bool illegal = 0;
					double result = inPureNum(tmp, illegal, intPart, isFloat);
					of << result << endl;
					return ANS;  //ANS的值(string类型)
				}
			}
			else
			{
				error("expect a )");
				break;
			}
		}
		else
		{
			error("appear illegal character!");
			break;
		}
	}
	return "0";  //有异常就返回0，ANS也置零
}
void convertANS(const string ans, string & expr)
{
	while (expr.find('A')!=-1)
	{
		int i = expr.find('A');
		expr.replace(i, 3, ans);
	}
}
int main()
{
	ifstream file("lab1_input.txt", ios::in);
	if (!file)
	{
		cerr << "Error: fail to open the file";
		exit(1);
	}
	//stringstream ss;
	string expression = "";
	string ANS = "0";
	while (getline(file,expression))
	{
		convertANS(ANS,expression);  //将所有ANS转换为具体数字
		ANS = calculate(expression);
	}
	return 0;
}