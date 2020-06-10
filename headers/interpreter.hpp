#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <stack>
#include <map>
#define GREEN   "\x1b[32;1m"
#define RED     "\x1b[31;1m"
#define RESET   "\x1b[0m"
using namespace std;

map <string, int> VarTable;
map <string, string> ArrTable;

enum OPERATOR {
        LBRACKET, RBRACKET,
        ASSIGN,
        OR,
        AND,
        BITOR,
        XOR,
        BITAND,
        EQ, NEQ,
        LEQ, LT,
        GEQ, GT,
        SHL, SHR,
        PLUS, MINUS,
        MULT, DIV, MOD
};

int PRIORITY [] = {
        -1 , -1 ,
        0,
        1,
        2,
        3,
        4,
        5,
        6, 6,
        7, 7,
        7, 7,
        8, 8,
        9, 9,
        10 , 10 , 10,
        -1, -1
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
		cout << "constructor value "<< value << endl;
	};
	string getSubclass() {
		return "Number";};
	void print() {cout << value << endl;};
	int getValue() {return value;};
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
		if (str == ":=")
			opertype = ASSIGN;
		if (str == "/")
			opertype = DIV;
		if (str == "%")
			opertype = MOD;
	}
	OPERATOR getType () {return opertype;};
	void print() {cout << opertype << endl;}
	string getSubclass() {
		return "Oper";
	};
	int getPriority () {
		return PRIORITY[opertype];
	};
	int getValue (const Number & left,
                      const Number & right);
};

class Value: public Lexem {
	string name;
	int value;
public:
	Value () {};
	Value (string val, int num) {
		VarTable.insert(pair<string, int>(val, num));
		cout << "value num" << endl;
	};
        Value (string val) {
                VarTable.insert(pair<string, int>(val, 0));
                cout << "value 0" << endl;
        };
	void set_value (int val) {
		value = val;
	}
};

class Array: public Lexem {
	string name;
	string content;
public:
	Array () {};
	Array (string cnt) {content = cnt;};
	Array (string arr, string cnt) {
		name = arr;
		content = cnt;
	};
	void changeContent() {};
	void printContent() {};
};
