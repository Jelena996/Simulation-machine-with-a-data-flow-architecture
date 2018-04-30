#include "compailer.h"
#include "helper.h"
#include <iostream>
#include <vector>
#include<string>
using namespace std;


Compailer* Compailer::instance = nullptr;
string operators = "+*^";

Compailer* Compailer::getInstance() {
	if (instance == nullptr)
		instance = new Compailer();
	return instance;
}

string& takeRightHandSide(string equation) {
	return equation.substr(3);
}

void Compailer::removeBlanks(string& line)
{
	auto i = line.begin();
	while (i != line.end())
	{
		if (*i == ' ') line.erase(i);
		++i;
	}
}




void Compailer::compaile(const string& name) {

	fstream* fileReceived;
	ofstream* fileCreated;



	fileReceived = openFile(name);
	fileCreated = new ofstream(imf(name), ios::out);
	try {
		while (!fileReceived->eof()) {
			int numOfEquations = 1;
			string equation;
			getline(*fileReceived, equation);
			removeBlanks(equation);
			string rhs = takeRightHandSide(equation);

			for (int i = 0; i < rhs.length(); i++) {
				auto help = operators.find(rhs[i]);
				if (help != string::npos) {
					int j = i + 1; while (!(operators.find(rhs[j]) != string::npos) && (j != rhs.length() - 1)) j++;

					if ((j == rhs.length() - 1) || operators.find(rhs[i]) >= operators.find(rhs[j])) {
						if (j != rhs.length() - 1) j--;
						int m = i - 1;
						while (!(operators.find(rhs[m]) != string::npos) && (m != 0))  m--;
						if (m != 0) m++;
						*fileCreated << "(" << numOfEquations << ") " << rhs.substr(i, 1) << " " << rhs.substr(m, i - m) << " " << rhs.substr(i + 1, j - i) << endl;
						string replacement = "(" + to_string(numOfEquations++) + ")";
						rhs.replace(m, j - m + 1, replacement);
						i = 0; continue;
					}
				}

				else  continue;
			}
			*fileCreated << "(" << numOfEquations << ")" << " = " << equation.substr(0, 1) << " (" << numOfEquations - 1 << ")";
			if (fileReceived->peek() != EOF)
				*fileCreated << endl;

		}

		fileReceived->close();
		fileCreated->close();


	}
	catch (exception& ex) {
		cout << ex.what();
		fileReceived->close();
		fileCreated->close();

	}
}

