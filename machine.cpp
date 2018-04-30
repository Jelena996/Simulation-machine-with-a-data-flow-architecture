#include "..\SimulationEngine\Event.h"
#include "exceptions.h"
#include "machine.h"
#include"operations.h"
#include "..\SimulationEngine\Sched.h"
#include "helper.h"
#include <fstream>
#include <iostream>
using namespace std;




Operation* Machine::returnOperation(const string& id, const vector<Operation*>& operations) {
	for (auto it = operations.begin(); it < operations.end(); it++) {
		if ((*it)->getID() == stoi(id.substr(1, 1))) return (*it);
	}
}




Operand* Machine::makeOperand(const string& operand) {

	if (operand.length() > 1) return new Result(operand, this->operations);
	if (isalpha(*operand.begin()))
		return new Variable(operand);
	else return new Constant(operand);
}



void Machine::makeOperation(const ID& id, const char& operator1, const string& oper1, const string& oper2)
{
	switch (operator1)
	{
	case '+':
		this->operations.push_back(new Addition(id, TimeOfAddition, makeOperand(oper1), makeOperand(oper2)));
		break;
	case '*':
		this->operations.push_back(new Multiplication(id, TimeOfMultiplication, makeOperand(oper1), makeOperand(oper2)));
		break;
	case '^':
		this->operations.push_back(new Exponentiation(id, TimeOfExponentiation, makeOperand(oper1), makeOperand(oper2)));
		break;
	case '=':
		Memory::Instance()->addVariable(oper1);
		this->operations.push_back(new Assignment(id, TimeOfAssignment, makeOperand(oper1), makeOperand(oper2)));
		break;
	}
}




void Machine::operationLoad(const string& nameOfFile) {

	fstream* compailedFile = openFile(imf(nameOfFile));
	string  identificator;
	char operator1;
	string operand1, operand2;
	while (compailedFile->peek() != EOF) {
		*compailedFile >> identificator;
		int id = stoi(identificator.substr(1, 1));
		*compailedFile >> operator1;
		*compailedFile >> operand1;
		*compailedFile >> operand2;
		this->makeOperation(id, operator1, operand1, operand2);
	}
	compailedFile->close();
}



ofstream* Machine::finalFile = 0;



void Machine::exec(const string& path) {  //nisam zatvorila fajlove, pogledati gdje se zatvaraju(notify ili ovdje)
	try {

		operationLoad(path);
		while (!operations.empty())
		{
			auto it = operations.begin();
			while (it != operations.end())
			{
				if ((*it)->Isready())
				{
					Event::create(*it, (*it)->getTime(), (*it)->getID());
					it = operations.erase(it);
				}
				else
					++it;
			}
			Scheduler::Instance()->processNow();
		}
		Memory::Instance()->release();
	}

	catch (exception& ex)
	{
		cout << ex.what() << endl;
		Memory::Instance()->release();
	}

}