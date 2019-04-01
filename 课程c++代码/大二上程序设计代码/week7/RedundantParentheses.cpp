#include <iostream>
#include <stack>
#include <string>

using namespace std;
int main()
{
	/*reduce parentheses situation:*/
	/*1.inside parenthese operation contains + or - and fore operation is + or null,
	and back operation is + or - or null.  for example: a+(b/c-d)-e  */
	/*2.inside parenthese operation doesn't contain + or -, but contains * or /
	and fore operation is not /   for example a+(b*c)*d, a*(b*c/d*e)/f  */
	/*3.inside parenthese operation is null.  for example (a) */
	while (true)
	{
		string line = "";
		stack<char> expression;
		getline(cin, line);

		while (!line.empty())
		{
			int i = 0;
			for (; i < line.size() && line[i] != ')'; i++)
			{
				expression.push(line[i]);
			}
			if (i >= line.size())
				break;
			//now line[i] = ')'
			expression.push(line[i]);
			line.erase(0, i + 1);

			string parentheseExpr;
			while (expression.top() != '(')
			{
				parentheseExpr += expression.top();
				expression.pop();
			}
			//take out the '('
			parentheseExpr += expression.top();
			expression.pop();

			reverse(parentheseExpr.begin(), parentheseExpr.end());
			char fore = '(';  //default (, record the fore char
			if (!expression.empty())
				fore = expression.top();

			bool containOper[4] = { 0 };  //record what inside parenthese opr contain
			i = 0;
			for (; i < parentheseExpr.size(); i++)
			{
				switch (parentheseExpr[i])
				{
				case '+':
					containOper[0] = 1;
					break;
				case '-':
					containOper[1] = 1;
					break;
				case '*':
					containOper[2] = 1;
					break;
				case '/':
					containOper[3] = 1;
					break;
				default:
					break;
				}
			}
			char back = ')';
			if (!line.empty())
				back = line[0];

			//okay,the prepare work is done
			bool reducePar = 0;  //judge whether we need to reduce the parenthese
			if (containOper[0] == 1 || containOper[1] == 1)
			{
				if ((fore == '+' || fore == '(') && (back == '+' || back == '-' || back == ')'))
					reducePar = 1;
			}
			else if (containOper[3] == 1 || containOper[4] == 1)
			{
				if (fore != '/')
					reducePar = 1;
			}
			else
			{
				reducePar = 1;
			}

			if (reducePar)
			{
				//reduce the parentheses
				parentheseExpr.erase(0, 1);
				parentheseExpr.pop_back();
			}
			else
			{
				//replace '()' with '[]'
				parentheseExpr[0] = '[';
				parentheseExpr[parentheseExpr.size() - 1] = ']';
			}

			//push the result parenthese expression in stack
			for (int i = 0; i < parentheseExpr.size(); i++)
				expression.push(parentheseExpr[i]);
		}

		string result = "";
		//get the result out of stack
		while (!expression.empty())
		{
			result += expression.top();
			expression.pop();
		}
		reverse(result.begin(), result.end());

		//replace the [] with ()
		for (int i = 0; i < result.size(); i++)
		{
			if (result[i] == '[')
				result[i] = '(';
			if (result[i] == ']')
				result[i] = ')';
		}
		cout << result;
		system("pause");
	}
	
	return 0;
}