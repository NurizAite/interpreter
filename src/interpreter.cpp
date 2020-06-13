#include "interpreter.hpp"

int if_flag = 0, while_flag = 0;

string getOper(string input, int i) {
	string opr;
	//cout << "*operator*" << endl;
	count = 0;
	if (input.substr(i, i + 2) == "if") {
		opr = "if";
		opr += '/0';
		i += 2;
		return opr;
	}
        if (input.substr(i, i + 4) == "then") {
                opr = "then";
                opr += '/0';
		i += 4;
                return opr;
	}
        if (input.substr(i, i + 4) == "else") {
                opr = "else";
                opr += '/0';
		i += 4;
                return opr;
	}
	if (input.substr(i, i + 5) == "endif") {
                opr = "endif";
                opr += '/0';
		i += 5;
                return opr;
	}
	if (input.substr(i, i + 5) == "while") {
                opr = "while";
                opr += '/0';
		i += 5;
                return opr;
	}
        if (input.substr(i, i + 8) == "endwhile") {
                opr = "endwhile";
                opr += '/0';
		i += 8;
                return opr;
	}
	if (input.substr(i, i + 2) == ":=") {
                opr = ":=";
                opr += '/0';
		i += 2;
                return opr;
	}
        if (input.substr(i, i + 2) == "==") {
                opr = "==";
                opr += '/0';
		i += 2;
                return opr;
        }
        if (input.substr(i, i + 2) == "!=") {
                opr = "!=";
                opr += '/0';
                i += 2;
                return opr;
        }
        if (input.substr(i, i + 2) == ">=") {
                opr = ">=";
                opr += '/0';
                i += 2;
                return opr;
        }
        if (input.substr(i, i + 2) == "<=") {
                opr = "<=";
                opr += '/0';
                i += 2;
                return opr;
        }
        if (input.substr(i, i + 1) == ">") {
                opr = ">";
                opr += '/0';
                i++;
                return opr;
        }
        if (input.substr(i, i + 1) == "<") {
                opr = "<";
                opr += '/0';
                i++;
		return opr;
        }
        if (input.substr(i, i + 1) == "+") {
                opr = "+";
                opr += '/0';
                i++;
                return opr;
        }
        if (input.substr(i, i + 1) == "-") {
                opr = "-";
                opr += '/0';
                i++;
                return opr;
        }
        if (input.substr(i, i + 1) == "*") {
                opr = "*";
                opr += '/0';
                i++;
                return opr;
        }
        if (input.substr(i, i + 1) == "/") {
                opr = "/";
                opr += '/0';
                i++;
                return opr;
        }
        if (input.substr(i, i + 1) == "%") {
                opr = "%";
                opr += '/0';
                i++;
                return opr;
        }
	else
		return "NOTOPER";
}

int getNum(string input, int i) {
	int j = i;
        while (input[j] >= '0' && input[j] <= '9') {
            j++;
        }
        int value = 0;
        while (i < j) {
            value = value + (input[i] - '0') * pow(10, j - i - 1);
            i++;
        }
	return value;
}

string getArray(string input, int i) {
	string arr;
	do {
		arr += input[i];
		i++;
	}
	while (input[i] != ']')
	arr += '/0';
	return arr;
}

string getVar(string input, int i) {
        string var;
	while (input[i] != "[" && input[i] >='a' && input[i] <='z' && input[i] >= "A" && input[i] <= "Z") {
                var += input[i];
                i++;
        }
	if (input[i] == "[")
		return "NOTVAR";
	else
        	return var;
}

vector<Lexem *> parseLexem(
	string input
) {
	vector <Lexem *> infix;
	string opr, arr;
	int size, i = 0, j, value = 0, count = 0;
	size = input.size();
	input += ' ';
	while(i != size) {
		while (input[i] == " ")
			i++;
		opr = getOper(input, i);
		if (opr != "NOTOPER")
			infix.push_back(new Oper(opr));
		var = getVar(input, i);
		if (opr == "NOTOPER" && var != "NOTVAR")
			infix.push_back(new Variable(var));
		if (input)
		arr = getArr(input, i);
                if (opr == "NOTOPER" && var == "NOTVAR")
			arr = getArr(input, i);
			infix.push_back(new Array(arr));
                if (opr == "NOTOPER" && var == "NOTVAR" && arr == "NOTARR")
			if (input[i] >= '0' && input[i] <= '9') {
				value = getNum(input, i);
                        	infix.push_back(new Number(value));
			}
		}
	}
	infix.push_back(NULL);
	return infix;
};

vector<Lexem *> buildPostfix (vector<Lexem *> infix) {
	vector<Lexem *> postfix;
	stack<Lexem *>  stackOper;
	int pr = -2, count = 0;
	for (int i = 0; infix[i] != NULL; i++) {
		if ((infix[i] -> getSubclass()) == "Number" || infix[i] -> getSubclass()) == "Var" ||infix[i] -> getSubclass()) == "Array") {
			postfix.push_back(infix[i]);
		//	cout << "NUM ";
		}
		if ((infix[i] -> getSubclass()) == "Oper") {
			if (infix[i] -> getType() == RBRACKET) {
				while (stackOper.top() -> getType() != LBRACKET) {
                                        postfix.push_back(stackOper.top());
                                        stackOper.pop();
                                        count--;
                                }
				stackOper.pop();
				count--;
                        }
                        else {
                        //        stackOper.push(infix[i] -> getType());

			if ((infix[i] -> getPriority()) < pr) {
				cout << "#####PRIORITY    " << endl;
				postfix.push_back(stackOper.top());
				stackOper.pop();
				count--;
			}
                        stackOper.push(infix[i]);
                        count++;
			}
			pr = infix[i] -> getPriority();
			cout << "###PR " << pr << endl;
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

Lexem *assign_operation(Lexem *left, Lexem *right) {
        Lexem *result;
        int number = ((Number *)right)->get_value();
        ((Variable *)left)->set_value(number);
        result = new Number(number);
        return result;
}

int evaluatePostfix (vector<Lexem *> poliz) {
	stack<int> nums;
	int a, b, result;
	int count = 0;
	for (int i = 0; poliz[i] != NULL; i++) {
		if (poliz[i] -> getType() == IF && if_flag == 1) {
			while (poliz[i] -> getType() != ENDIF)
				i++;
		}
		if (poliz[i] -> getType() == WHILE && while_flag == 1) {
			while (poliz[i] -> getType() != ENDWHILE)
				i++;
		}
		if (poliz[i] -> getSubclass() == "Number") {
			nums.push(poliz[i] -> getValue());
			count++;
        		cout << "COUNT " << count << endl;
		}
                if (poliz[i] -> getSubclass() == "Var") {
                        nums.push(poliz[i] -> getValue());
                        count++;
                        cout << "COUNT " << count << endl;
                }
                if (poliz[i] -> getSubclass() == "Array") {
                        nums.push(poliz[i] -> getValue());
                        count++;
                        cout << "COUNT " << count << endl;
                }
		else {
			a = nums.top();
			nums.pop();
			b = nums.top();
			nums.pop();
			count -= 2;
			cout << "COUNT " << count << endl;
			if (poliz[i] -> getType() == PLUS) {
				cout << "*** " << b + a << endl;
				nums.push(b + a);
			}
                        if (poliz[i] -> getType() == MINUS) {
                                cout << "*** " << b - a << endl;
				nums.push(b - a);
                        }
			if (poliz[i] -> getType() == MULTIPLY) {
                                cout << "*** " << b * a << endl;
                                nums.push(b * a);
			}
                        if (poliz[i] -> getType() == DIV) {
                                cout << "*** " << b / a << endl;
                                nums.push(b / a);
                        }
                        if (poliz[i] -> getType() == MOD) {
                                cout << "*** " << b % a << endl;
                                nums.push(b % a);
                        }

			count++;
		    cout << "COUNT " << count << endl;
		}
	}
	result = nums.top();
	nums.pop();
	count--;
	cout << "FINAL COUNT " << count << endl;
	return result;
};
