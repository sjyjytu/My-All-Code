#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stack>
#include <cmath>

using namespace std;
int Factorial(int n)
{
	/*����׳�*/
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
		/*������⣬���Ǳ���N*/
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
	/*��ȡ���ţ������б�����Ƿ�Ϸ��������д���+-���ַ���Ϊ���Ϸ���*/
	/*����ǰ������һ����������,�ɴ���-+,���ɴ���N*/
	int sign = 1;  //������
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
	/*��ȡ���֣���ȷ��topΪ����ʱʹ�ñ�������������С��*/
	int intNum = 0;  //��������
	int doubleNum = 0;//С������
	int doubleLength = 1;  //��¼С������Ҫ���Ե�����1��10��100...,
	while (!c.empty()&&isdigit(c.top()))
	{
		intNum = intNum * 10 + (c.top() - '0');
		c.pop();
	}
	intPart = sign * intNum;
	isfloat = 0;  //���ز���С��
	if (c.empty()||c.top() != '.')
		return sign * double(intNum);
	else
	{
		c.pop();  //pop��'.'
		while (!c.empty() && isdigit(c.top()))
		{
			doubleNum = doubleNum * 10 + (c.top() - '0');
			c.pop();
			doubleLength *= 10;
			if (doubleNum!=0)
				isfloat = 1;  //������С��
		}
		double tmp = double(doubleNum) / doubleLength;
		return sign*(double(intNum) + tmp);
	}
}
double inPureNum(stack<char> &c, bool &illegal, int & intPart, bool &isfloat, int sign = 1)
{
	/*��ȡ�����֣�ֻ����N��������+-*/
	if (c.top() == 'N')
	{
		sign *= -1;
		c.pop();
	}
	return inNum(c, illegal, intPart, isfloat, sign);
}

double inSignNum(stack<char> &c, bool &illegal, int & intPart, bool &isfloat)
{
	/*��ȡ����������,����+-��N*/
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
	/*�������ŵĴ�����*/
	/*�������Դ�������*/
	/*���ȼ��� !> / * % > + -                          */

	/*�������������ʱ��stack�ֱ�洢���ֺ������,�ߴ��������*/
	stack<double> Num;
	stack<char> Oper;

	/*�ȴ���׳�*/
	stack<char> reverseOperate;  //����operate
	int firintPart = 0;  //��¼ǰ�����ֵ��������֣����㣡����
	bool isfloat = 0;  //��¼�Ƿ���С�������㣡����
	while (!operate.empty() && !illegal)
	{
		if (operate.top() == '!')
		{
			if (reverseOperate.empty()||!isdigit(reverseOperate.top()))
			{
				/*n! n<0  n+! ��������ᵼ���������*/
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
					smartPush(reverseOperate, result,1);  //string(result)Ҫ�������
				}
			}
		}
		else if (isdigit(operate.top())|| operate.top()=='N')
		{
			char t5 = operate.top();
			double temp = inPureNum(operate, illegal, firintPart, isfloat);
			smartPush(reverseOperate, temp, 2);  //������⣬����׳�ȡ����
			/*��ҲҪע�⣬���ᷴת��ʱ������������С���ߵ���*/
		}
		else
		{
			//������������
			reverseOperate.push(operate.top());
			operate.pop();
		}
	}
	/*��reverseOper��ת��operate��*/
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

	/*����˳�*/
	/*����ǰ��Ĵ�����һ�������һ��һ������*/
	double frontNum = 0;
	double backNum = 1;
	double result = 0;
	while (!operate.empty() && !illegal)
	{
		/*��һ�������ֺ�һ���ַ�*/
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
					int sign = copeSign(operate, illegal);  //����+-+-++--֮������
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
	/*�˳������ˣ�����Oper��ֻʣ+-��*/
	/*ע�⣡��ʱ��Oper��Num�Ǵ��ҵ���ģ�Ӧ�÷�һ��*/
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
	/*���Num��ֻ��һ��Ԫ�أ��������Сʽ�ӵ�������*/
	if (!illegal)
	{
		string str = doubleToString(rNum.top());
		if (str[0] == '-')
			str[0] = 'N';
		return str;
	}
	else
		return "0";  //���ʽ�Ӳ��Ϸ����ͷ���"0"
}
string calculate(string expression)
{
	/*������ʽ����������ж��Ƿ�淶�Լ���������*/
	/*�����Ҷ�ȡexpression��bracket�У����һ�������е����ݵ�operate�н������㣬
	�����push��bracket*/
	if (expression[0] == '+' || expression[0] == '-')
		expression = '0' + expression;
	bool illegal = 0;  //�Ϸ���
	int leftbracketNum = 0;  //��������
	stack<char> bracket;  //��ȡ���ʽ�����ж���������Ҫ���ڴ�������
	stack<char> operate;  //��ʱ�������ֺ�+-*/������
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
		
		/* ����')'��leftbracketNum>0�� ����';'��leftbracketNum = 0 �����һ������*/
		else if (expression[i] == ')')
		{
			if (leftbracketNum>0)
			{
				/*�ҵ�һ��Ҫ��������ı��ʽ*/
				leftbracketNum--;
				while (bracket.top() != '(')
				{
					char tmp;
					tmp = bracket.top();
					bracket.pop();
					operate.push(tmp);  //ע�⣡����������operate��bracket�ĵ����
										//��bracket����string�ĵ�������operate������
				}
				bracket.pop();  //��ȥ(
				/*��ʼ����*/
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
				/*�ҵ�һ��Ҫ��������ı��ʽ*/
				while (!bracket.empty())
				{
					char tmp;
					tmp = bracket.top();
					bracket.pop();
					operate.push(tmp);  //ע�⣡����������operate��ԭ���ĵ����
				}
				/*��ʼ����*/
				string ANS = pureCal(operate, illegal);  //���ս��
				ofstream of("lab1_output.txt", ios::app);
				if (!of)
				{
					cerr << "open output file wrong!";
					exit(1);
				}
				if (!illegal)
				{
					/*�����������ļ�������������ǽ�string���͵Ľ��תΪdouble*/
					/*�Ա�ʡȥС�����ֶ�����㣬�������������ֻ�����������*/
					/*ʵ�ַ������Ƚ��������tmp�У�������inPureNumȡ��result*/
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
					return ANS;  //ANS��ֵ(string����)
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
	return "0";  //���쳣�ͷ���0��ANSҲ����
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
		convertANS(ANS,expression);  //������ANSת��Ϊ��������
		ANS = calculate(expression);
	}
	return 0;
}