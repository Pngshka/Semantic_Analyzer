#pragma once
#include <map>
#include <queue>
#include <stack>
#include <set>
#include <fstream>

using namespace std;
ofstream ofst("C://e//output.txt");

void clearQ(queue<string>& q)
{
	queue<string> empty;
	swap(q, empty);
}
void clearS(stack<string>& q)
{
	stack<string> empty;
	swap(q, empty);
}

class CountAndFalse {
public:
	int Count;
	bool Pr;

	CountAndFalse() {
		this->Pr = false;
	}
};

class analyzer {
public:
	string str;
	string str2;
	int p;

	map <string, CountAndFalse> peremen;
	set <string> metki;
	stack <string> STACK;
	queue <string> QUEUE;
	bool proverka = true;

	analyzer(string& str) {
		this->str = str;
		p = 0;
	}

	void scan();
	void begin();
	bool type();
	void descriptions();
	void descr();
	void operators();
	void op();
	bool id(bool);
	bool Mark(bool);
	void expr(string);
	void ReverseExpr(string);
	bool FunctionName();
	bool Const();
	void end();
};

void analyzer::scan() {
	begin();
	p += 5;
	descriptions();
	operators();
	end();
	//if (proverka) cout << "True" << endl; else cout << "False" << endl;
	return;
}

void analyzer:: begin() {
	type();
	FunctionName();
	return;
}

bool analyzer::type() {
	string h;
	string q;
	while (str[p] != ' ' && str[p] != ' ') {
		h += str[p];
		p++;
	}

	q = h;
	q += str[p];
	if (q == "int ") {
		//cout << "int" << endl;
		return true;
	}
	else {
		//proverka = false;
		return false;
	}
}

bool analyzer::FunctionName() {
	p++;
	string n;
	bool t = true;
	while (str[p] != '(') {
		if (isdigit(str[p])) {
			proverka = false;
			t = false;
		}
		n += str[p];
		p++;
	}
	return t;
}

void analyzer::descriptions() {
	while (p+1 != str.size()) {
		if (str[p] == 'g' && str[p + 1] == 'o' && str[p + 2] == 't' && str[p + 3] == 'o' && str[p + 4] == ' ') {
			return;
		}
		else {
			if (str[p] == 'i' && str[p + 1] == 'n' && str[p + 2] == 't' && str[p + 3] == ' ') {
				descr();
			}
			else {
				int u = p;
				while (str[u] != ' ') {
					u++;
				}
				u++;
				if (str[u] == '=' || str[u] == ':') {
					return;
				}
				else {
					proverka = false;
					cerr << "ERROR in INT" << endl;
					descr();
				}
			}
		}
	}
}

void analyzer::descr() {
	if (!type()) proverka = false;
	p++;
	while (str[p] != ';') {
		if (str[p] == ',') {
			p += 2;
		}
		if (!id(true)) {
			proverka = false;
		}
		if (str[p] != ',' && str[p] != ';') {
				proverka = false;

				break;
		}
	}
	p += 2;
	return;
}

bool analyzer::id(bool Y) {
	string h;
	map <string, CountAndFalse> ::iterator it;
	bool t = true;
	while (str[p] != ',' && str[p] != ';' && str[p] != ' ') {
		h += str[p];
		p++;
	}
	str2 = h;
	//cout<<str2 << endl;
	if (peremen.find(h) == peremen.end() && Y) {
		peremen[h];
		t = false;
	}
	/*if (Y) {
		it = peremen.begin();
		for (int i = 0; it != peremen.end(); it++, i++) {
			if (peremen.find(h)->second.Pr == true) cout << i << ")  " << it->first << " | " << it->second.Count << endl; else  cout << i << ")  " << it->first << endl;
		}
	}*/
	return t;
}

bool analyzer::Mark(bool Y) {
	string h;
	bool t = true;
	set <string> ::iterator it;
	while (str[p] != ',' && str[p] != ';' && str[p] != ' ') {
		//if (str[p]=='.') t = false;
		h += str[p];
		p++;
	}
	if (metki.find(h) == metki.end()) {
		if (Y) metki.insert(h);
		t = false;
	}
	/*if (Y) {
		it = metki.begin();
		for (int i = 0; it != metki.end(); it++, i++) {
			cout << i << ")  " << *it << endl;
		}
	}*/
	return t;
}

void analyzer::operators() {
	//p += 2;
	//cout << str[p] << endl;
	string q;
	while (q+str[p]+str[p+1]+str[p+2] + str[p + 3] + str[p + 4] + str[p + 5] !="return"&&str[p]!=str.size()) {
		op();
	}
	if (str[p] == str.size()) {
		cerr << "Not return" << endl;
		proverka = false;
	}
	return;
}

void analyzer::op() {
	//p += 2;
	if (str[p] == 'g' && str[p + 1] == 'o' && str[p + 2] == 't' && str[p + 3] == 'o'&& str[p+4]==' ') {
		p += 5;
		if (!Mark(false)) cout << "No Mark" << endl;
		p += 2;
		return;
	}
	else {
		int u = p;
		//cout << str[p] << endl;
		while (str[u] != ' ') {
			u++;
		}
		u++;
		if (str[u] == '=') {
		
			if (!id(false)) {
				//ошибка: переменная не объявлена
				cout << "Variable not declared: "<<str2 << endl;
			}
			p++;
			p += 2;
			expr(str2);
			return;
		}
		else {
			if (str[u] == ':') {
				Mark(true);
				p++;
				p += 2;
				op();
				return;
			}
		} 
	}
}

void analyzer::expr(string str3) {
	clearQ(QUEUE);
	clearS(STACK);
	string STR;
	bool proverkaID=true;
	int proverkaIDint=0;
	while (str[p] != ';') {
		if (isalpha(str[p])||isdigit(str[p])) {
			if (isalpha(str[p])) {
				id(false);
				//if (peremen.find(str2) == peremen.end()) cout << "Variable not declared: " << str2 << endl;
				/*if (peremen.find(str2) != peremen.end() && peremen.find(str2)->second.Pr == true) {
					proverkaIDint += peremen.find(str2)->second.Count;
				} else proverkaID = false;*/
			}
			else {
				if (!Const()) cout<<"Not int"<<endl;
				//proverkaIDint += stoi(str2);
			}
			if (str2!="-1") QUEUE.push(str2);
			STR += str2;
			p++;
		}
		if (str[p] == '+' || str[p] == '-') {
			if (STACK.empty() || STACK.top() == "(") {
				if (str[p] == '+') STACK.push("+"); else STACK.push("-");
			}
			else {
				while (!STACK.empty() && STACK.top() != "(") {
					QUEUE.push(STACK.top());
					STR += STACK.top();
					STACK.pop();
				}
			}
			p += 2;
		}
		if (str[p] == '(') {
			STACK.push("(");
			p += 2;
		}
		if (str[p] == ')') {
			//Прописать ошибку while (!STACK.empty() || STACK.top() != "(") {
			while (STACK.top() != "(") {
				QUEUE.push(STACK.top());
				STR += STACK.top();
				STACK.pop();
			}
			STACK.pop();
			p += 2;
		}
	}
	while (!STACK.empty()) {
		QUEUE.push(STACK.top());
		STR += STACK.top();
		STACK.pop();
	}
	cout << STR << endl;
	ofst << STR << endl;
	p += 2;
	ReverseExpr(str3);
	return;
}

bool analyzer::Const() {
	string h;
	bool t = true;
	while (str[p] != ',' && str[p] != ';' && str[p] != ' ') {
		if (!isdigit(str[p])) t = false;
		h += str[p];
		p++;
	}
	//if (!t) str2 = "-1"; else 
		str2 = h;

	return t;
}

void analyzer::end() {
	p += 7;
	if (!Const()) cout<<"Not Const"<<endl;
	return;
}

void analyzer::ReverseExpr(string str3) {
	clearS(STACK);
	bool proverkaExpr = true;

	while (!QUEUE.empty()) {

		if (isdigit(QUEUE.front()[0])) {
			string ProvStr = QUEUE.front();
			int ProvStrInt = 0;
			bool ProvStrBool = true;
			while (ProvStrInt < ProvStr.size()) {
				if (!isdigit(ProvStr[ProvStrInt])) {
					ProvStrBool = false;
					break;
				}
				ProvStrInt++;
			}
			if (!ProvStrBool) {
				proverkaExpr = false;
				break;
			}
		}


		if (isdigit(QUEUE.front()[0])||isalpha(QUEUE.front()[0])) {
			STACK.push(QUEUE.front());
			QUEUE.pop();
		}
		else {
			if (QUEUE.front() == "+") {
				int Second = 0;
				int First = 0;
				if (isdigit(STACK.top()[0])) {
					
					Second = stoi(STACK.top());
				}
				else {
					if (peremen.find(STACK.top()) != peremen.end() && peremen.find(STACK.top())->second.Pr == true) {
						Second = peremen.find(STACK.top())->second.Count;
					}
					else {
						//Ошибка: нет значения
						proverkaExpr = false;
						if (peremen.find(STACK.top()) == peremen.end()) cout << "Not declared and not initialized: " << STACK.top() << endl; else cout << "Not initialized: " << STACK.top() << endl;
					}
				}
				STACK.pop();
				if (isdigit(STACK.top()[0])) {
					First = stoi(STACK.top());
				}
				else {
					if (peremen.find(STACK.top()) != peremen.end() && peremen.find(STACK.top())->second.Pr == true) {
						First = peremen.find(STACK.top())->second.Count;
					}
					else {
						//Ошибка: нет значения
						proverkaExpr = false;
						if (peremen.find(STACK.top()) == peremen.end()) cout << "Not declared and not initialized: " << STACK.top() << endl; else cout << "Not initialized: " << STACK.top() << endl;
					}
				}
				STACK.pop();
				STACK.push(to_string(First + Second));
				QUEUE.pop();
			}
			else {
				if (QUEUE.front() == "-") {
					int Second = 0;
					int First = 0;
					if (isdigit(STACK.top()[0])) {
						Second = stoi(STACK.top());
					}
					else {
						if (peremen.find(STACK.top()) != peremen.end() && peremen.find(STACK.top())->second.Pr == true) {
							Second = peremen.find(STACK.top())->second.Count;
						}
						else {
							//Ошибка: нет значения
							proverkaExpr = false;
							if (peremen.find(STACK.top()) == peremen.end()) cout << "Not declared and not initialized: "<< STACK.top() << endl; else cout << "Not initialized: " << STACK.top() << endl;
						}
					}
					STACK.pop();
					if (isdigit(STACK.top()[0])) {
						First = stoi(STACK.top());
					}
					else {
						if (peremen.find(STACK.top()) != peremen.end() && peremen.find(STACK.top())->second.Pr == true) {
							First = peremen.find(STACK.top())->second.Count;
						}
						else {
							//Ошибка: нет значения
							proverkaExpr = false;
							if (peremen.find(STACK.top()) == peremen.end()) cout << "Not declared and not initialized: " << STACK.top() << endl; else cout << "Not initialized: " << STACK.top() << endl;
						}
					}
					STACK.pop();
					STACK.push(to_string(First - Second));
					QUEUE.pop();
				}
			}
		}
	}
	if (proverkaExpr) {
		peremen[str3].Pr = true;

	/*
		string ProvStr = STACK.top();
		int ProvStrInt = 0;
		bool ProvStrBool = true;
		while (ProvStrInt < ProvStr.size()) {
			if (!isdigit(ProvStr[ProvStrInt])) {
				ProvStrBool = false;
				break;
			}
			ProvStrInt++;
		}
		if (!ProvStrBool) {
			cout << "No value" << endl;
		}
		else {
		*/
		try {
			if (stoll(STACK.top()) > 2147483647) {
				cout << "Not int" << endl;
				peremen[str3].Count = -1;
			}
			else {
				peremen[str3].Count = stoi(STACK.top());
				cout << "=: " << STACK.top() << endl;
			}
		}
		catch (const std::exception& ex) {
			cout << "No value" << endl;
		}
		
		//}
	} else cout << "No value" << endl;
	cout << endl;
	clearS(STACK);
	return;
}