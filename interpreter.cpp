#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <stack>
using namespace std;

enum OPERATOR {
        ASSIGN,
        PLUS, MINUS,
        MULTIPLY,
        LBRACKET, RBRACKET
};

class Lexem {
public:
	Lexem () {};
	virtual void print() {};
	virtual string getSubclass() {};
	virtual int getValue() {};
	virtual OPERATOR getType() {};
	virtual int getPriority() {};
};

class Number : public Lexem {
	int value ;
public:
	Number () {};
	Number (int num) {
		value = num;
	//	cout << "constructor value "<< value << endl;
	};
	string getSubclass() {
		return "Number";};
	void print() {cout << value << " ";};
	int getValue() {return value;};
};

int PRIORITY [] = {
	0,
	1, 2,
	3,
	-1, -1
};

class Oper: public Lexem {
	OPERATOR opertype ;
public:
	Oper () {};
	Oper (string str) {
		if (str == "+")
			opertype = PLUS;
		if (str == "-")
			opertype = MINUS;
		if (str == "*")
			opertype = MULTIPLY;
		if (str == "(")
			opertype = LBRACKET;
        if (str == ")")
            opertype = RBRACKET;
	}
	OPERATOR getType () {return opertype;};
	void print() {cout << opertype << " ";}
	string getSubclass() {
		return "Oper";
	};
	int getPriority () {
		return PRIORITY[opertype];
	};
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
			}
			value = 0;
			while (i < j) {
				value = value + (input[i] - '0') * pow(10, j - i - 1);
				i++;
			}
			//cout << value << endl;
			infix.push_back(new Number(value));
		}
		else {
			if (input[i] != ')' && input[i] != '(') {
				j =  i;
				count = 0;
				while ((input[i] < '0' || input[i] > '9') && input[i] != ' ' 
					   && input[i] != ')' && input[i] != '(') {
					i++;
					count++;
				}
				opr = input.substr(j, count);
				infix.push_back(new Oper(opr));
			}
			else {
				opr = input[i];
				infix.push_back(new Oper(opr));
				i++;
			}
		}
	}
	infix.push_back(NULL);
	return infix;
};

vector<Lexem *> buildPostfix (vector<Lexem *> infix) {
	vector<Lexem *> postfix;
	stack<Lexem *>  stackOper;
	//cout << "BUILD POSTFIX" << endl;
	int pr = -2, count = 0;
	for (int i = 0; infix[i] != NULL; i++) {
		if ((infix[i] -> getSubclass()) == "Number") {
			postfix.push_back(infix[i]);
		}
		if ((infix[i] -> getSubclass()) == "Oper") {
			if (infix[i] -> getType() != RBRACKET) {
				if (infix[i] -> getType() != LBRACKET) {
					if ((infix[i] -> getPriority()) < pr) {
						postfix.push_back(stackOper.top());
						stackOper.pop();
						count--;
					}
	                stackOper.push(infix[i]);
	                count++;
					pr = infix[i] -> getPriority();
				}
				else {
					stackOper.push(infix[i]);
	                count++;
					pr = -2;
				}
			}
			else {
				while (stackOper.top() -> getType() != LBRACKET) {
					postfix.push_back(stackOper.top());
					stackOper.pop();
					count--;
				}
				stackOper.pop();
				count--;
			}
		}
	}
	while (count != 0) {		
		postfix.push_back(stackOper.top());
		stackOper.pop();
		count--;
	}
	postfix.push_back(NULL);
	return postfix;
};

int evaluatePostfix (vector<Lexem *> poliz) {
	stack<int> nums;
	int a, b, result;
	int count = 0;
	for (int i = 0; poliz[i] != NULL; i++) {
		if (poliz[i] -> getSubclass() == "Number") {
			nums.push(poliz[i] -> getValue());
			count++;
		}
		else {
			a = nums.top();
			nums.pop();
			b = nums.top();
			nums.pop();
			count -= 2;
			if (poliz[i] -> getType() == PLUS) {
				nums.push(b + a);
			}
                        if (poliz[i] -> getType() == MINUS) {
				nums.push(b - a);
                        }
			if (poliz[i] -> getType() == MULTIPLY) {
                                nums.push(b * a);
			}
			count++;
		}
	}
	result = nums.top();
	nums.pop();
	count--;
	return result;
};

int main () {
	string codeline;
	vector <Lexem *> infix;
	vector <Lexem *> postfix;
	int value;
	getline(cin, codeline);
//	while (getline(cin, codeline)) {
		infix = parseLexem (codeline);
		/*for (int i = 0; infix[i] != NULL; i++) {
			infix[i] -> print();
		}*/
		postfix = buildPostfix(infix);
        /*cout << "POSTFIX" << endl;;
		for (int i = 0; postfix[i] != NULL; i++) {
                        postfix[i] -> print();
        }
        cout << endl << "END OF POSTFIX" << endl;*/
		value = evaluatePostfix (postfix);
		cout << value << endl;
//	}
	return 0;
}
