int main () {
	string codeline;
	vector <Lexem *> infix;
	vector <Lexem *> postfix;
	int value, global_count = 1;
        cout << GREEN "In [" << global_count << "]: " RESET << endl;
	while (getline(cin, codeline)) {
		global_count++;
		if (codeline == "exit" || codeline == "quit")
			return 0;
		infix = parseLexem (codeline);
		for (int i = 0; infix[i] != NULL; i++) {
			infix[i] -> print();
		}
		postfix = buildPostfix(infix);
		printf("\n POSTFIX \n");
		for (int i = 0; postfix[i] != NULL; i++) {
                        postfix[i] -> print();
                }
		value = evaluatePostfix (postfix);
		cout << value << endl;
                cout << RED "Out [" << value << "]: " RESET << endl;
                cout << GREEN "In [" << global_count << "]: " RESET << endl;
	}
	return 0;
}
