#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iterator>
using namespace std;
class Lexem {
public:
	Lexem () {};
	virtual void print() {};
};

class Number : public Lexem {
	int value ;
public:
	Number () {};
	Number (int value) {
		cout << "constructor value "<< value << endl;
	};
//	void print() {cout << value << endl;};
	int getValue ();
};

enum OPERATOR {
	ASSIGN,
	PLUS, MINUS,
	MULTIPLY,
	LBRACKET, RBRACKET
};

int PRIORITY [] = {
	0,
	1, 1,
	2,
	-1, -1
};

class Oper: public Lexem {
	OPERATOR opertype ;
public:
//	Oper () {};
	Oper (string str) {
		cout << "string constructor" << endl;
	}
	OPERATOR getType ();
//	void print() {cout << str << endl;}
	int getPriority ();
	int getValue (const Number & left,
                      const Number & right);
};

vector<Lexem *> parseLexem(
	string input
) {
	vector <Lexem *> infix;
	string opr;
	int size, i = 0, j, value = 0, count = 0;
	size = input.size();
	input += ' ';
	while(i != size && input[i] != ' ') {
		if (input[i] >= '0' && input[i] <= '9') {
			j = i;
			while (input[j] >= '0' && input[j] <= '9') {
				j++;
			//	value = value + (input[i] - '0');
			}
			value = 0;
			while (i < j) {
				value = value + (input[i] - '0') * pow(10, j - i - 1);
				i++;
			}
		//	i++;
			cout << value << endl;
		//	cout << i << endl;
			infix.push_back(new Number(value));
//			infix.print(value);
		}
		else {
			cout << "*operator*" << endl;
			j =  i;
			count = 0;
			while ((input[i] < '0' || input[i] > '9') && input[i] != ' ') {
				i++;
				count++;
		//		cout << "index " << i << endl;
			}
			opr = input.substr(j, count);
			cout << "oper is "<< opr << endl;
			infix.push_back(new Oper(opr));
		}
	}
	return infix;
};

vector<Lexem *> buildPostfix (vector<Lexem *> infix) {

};

int evaluatePostfix(
	vector<Lexem *> poliz
);

int main () {
	string codeline;
	vector <Lexem *> infix;
	vector <Lexem *> postfix;
	int value;
	getline(cin, codeline);
//	while (getline(cin, codeline)) {
		infix = parseLexem (codeline);
//		infix.print();
/*		for (auto i = infix.begin(); i != infix.end(); 
++i);
			cout << *i << ' ';*/
//		postfix = buildPostfix (infix);
//		value = evaluatePostfix (postfix);
//		cout << value << endl;
//	}
	return 0;
}
