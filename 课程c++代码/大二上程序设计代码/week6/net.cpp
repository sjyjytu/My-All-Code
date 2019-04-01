#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<ctime>
#include<cmath>

using std::cout;
using std::string;
using std::vector;
using std::ofstream;
using std::stringstream;

class Calc {
public:
	Calc() {};
	void print_result() const;
	bool run(const int src[], size_t sz, double n = 24.0,
		bool expr_calc = true, bool show = true);
	const string& get_expr() const { return expr; }
	size_t get_count_expr() const { return count_expr; }
	size_t get_count_func() const { return count_func; }

private:
	Calc(const Calc&);
	Calc& operator=(const Calc&);
	bool init(const int src[], size_t sz, double n);
	bool calc(size_t step);
	inline bool calc2(size_t step, size_t pos2, double na, double nb, int op);
	void calc_expr();

	void add_parentheses(string& str) {
		string tmp;  tmp.reserve(str.size() + 2);
		tmp += '(';  tmp += str;  tmp += ')';
		str.swap(tmp);
	}

	char get_op_char(int op) { return char(op >> RSHIFT); }
	int get_opv(int op) { return op & OPV_MASK; }

	//0-2位表示操作符的优先级 加减: 1 乘除2  初始值4
	//+3位，即RFLAG标志，表示对减除法，交换两个操作数后再计算
	//4-7位表示操作符，8-15位表示该操作符的ascii值
	enum {
		OP_NULL = 4, RFLAG = 8, RSHIFT = 8, OPV_MASK = 7,
		FLAG_ADD = 0x10, FLAG_SUB = 0x20, FLAG_MUL = 0x40, FLAG_DIV = 0x80,
		ADD = '+' << RSHIFT | FLAG_ADD | 1, SUB = '-' << RSHIFT | FLAG_SUB | 1,
		MUL = '*' << RSHIFT | FLAG_MUL | 2, DIV = '/' << RSHIFT | FLAG_DIV | 2,
		RSUB = SUB | RFLAG, RDIV = DIV | RFLAG,
	};

	struct Info_step {              //记录每一步取两个数所进行的计算
		size_t first;                 //第一个操作数位置
		size_t second;                //第二个操作数位置
		int op;                       //操作符
	};

	size_t size;
	string expr;                    //得到的表达式

	double result;                  //要得到的结果值
	size_t count_expr;              //处理的表达式总数
	size_t count_func;              //函数被调用次数
	vector<int> old_number;         //要计算的数
	vector<double> number;          //中间计算结果
	vector<int> ops;               //上一次计算所用的操作符,初始值要设为OP_NULL
	vector<Info_step> info_step;
};

bool Calc::init(const int src[], size_t sz, double n)
{
	if (sz == 0 || src == NULL) return false;
	size = sz;
	expr.clear();
	result = n;
	count_expr = 0;
	count_func = 0;
	old_number.assign(src, src + sz);
	number.assign(src, src + sz);
	ops.assign(sz, OP_NULL);
	info_step.clear();
	info_step.resize(sz);
	return true;
}

bool Calc::run(const int src[], size_t sz, double n, bool expr_calc, bool show)
{
	if (!init(src, sz, n)) return false;
	bool ret = calc(sz);
	if (ret && expr_calc) calc_expr();
	if (show) print_result();
	return ret;
}


void Calc::calc_expr()
{
	const size_t sz = size;
	static vector<string> str;
	static vector<int> op_prev;
	static stringstream ss;
	str.resize(sz);
	op_prev.assign(sz, OP_NULL);    //初始值
	for (size_t i = 0; i < sz; ++i) {
		ss << old_number[i];
		getline(ss, str[i]);
		ss.clear();
	}
	for (size_t k = sz; k-- > 1; ) {
		size_t i = info_step[k].first;
		size_t j = info_step[k].second;
		int op = info_step[k].op;
		int opv = get_opv(op);
		int op1v, op2v;
		if (op & RFLAG) {
			str[i].swap(str[j]);
			op1v = get_opv(op_prev[j]);
			op2v = get_opv(op_prev[i]);
		}
		else {
			op1v = get_opv(op_prev[i]);
			op2v = get_opv(op_prev[j]);
		}

		if (opv > op1v) add_parentheses(str[i]);
		if (opv > op2v || (opv == op2v && (op & (FLAG_SUB | FLAG_DIV))))
			add_parentheses(str[j]);
		op_prev[i] = op;
		op_prev[j] = op_prev[k];
		str[i].reserve(str[i].size() + str[j].size() + 1);
		str[i] += get_op_char(op);
		str[i] += str[j];
		str[j].swap(str[k]);
	}
	expr.swap(str[0]);
}

bool Calc::calc(size_t step)
{
	++count_func;
	if (step <= 1) {
		++count_expr;
		const double zero = 1e-9;
		if (fabs(result - number[0]) < zero) return true;
		return false;
	}
	--step;
	for (size_t i = 0; i < step; i++) {
		info_step[step].first = i;
		for (size_t j = i + 1; j <= step; j++) {
			info_step[step].second = j;
			double na = number[i];
			double nb = number[j];
			int op1 = ops[i];
			int op2 = ops[j];
			number[j] = number[step];
			ops[j] = ops[step];
			int tt = op1 | op2;
			bool ba = true, bb = true;
			if (tt & FLAG_SUB) ba = false;
			if (tt & FLAG_DIV) bb = false;

			if (ba) {
				if (calc2(step, i, na, nb, ADD)) return true;
				if (nb != 0 && calc2(step, i, na, nb, SUB)) return true;
				if (na != nb && na != 0 && calc2(step, i, na, nb, RSUB)) return true;
			}

			if (bb) {
				double nmul = na * nb;
				if (calc2(step, i, na, nb, MUL)) return true;
				if (na != 0 && nb != 0) {
					double ndiv = na / nb;
					if (nmul != ndiv && calc2(step, i, na, nb, DIV)) return true;
					double nrdiv = nb / na;
					if (nrdiv != ndiv && nrdiv != nmul && calc2(step, i, na, nb, RDIV))
						return true;
				}
			}
			number[i] = na;
			number[j] = nb;
			ops[i] = op1;
			ops[j] = op2;
		}
	}
	return false;
}

inline bool Calc::calc2(size_t step, size_t pos2, double na, double nb, int op)
{
	info_step[step].op = op;
	ops[pos2] = op;
	switch (op) {
	case ADD:   number[pos2] = na + nb; break;
	case SUB:   number[pos2] = na - nb; break;
	case MUL:   number[pos2] = na * nb; break;
	case DIV:   number[pos2] = na / nb; break;
	case RSUB:  number[pos2] = nb - na; break;
	case RDIV:  number[pos2] = nb / na; break;
	default: break;
	}
	return calc(step);
}

void Calc::print_result() const
{
	if (old_number.empty()) return;
	cout << "number: ";
	for (size_t i = 0; i < old_number.size(); ++i)
		cout << old_number[i] << " ";
	cout << "\n";
	if (!expr.empty()) std::cout << "result: YES\n";
	if (expr.empty())std::cout << "result:NO\n";
}

int main()
{
	Calc calc;
	int i, N, r[100];
	std::cin >> N;
	for (i = 0; i<N; ++i)
	{
		std::cin >> r[i];
	}
	calc.run(r, N);
}