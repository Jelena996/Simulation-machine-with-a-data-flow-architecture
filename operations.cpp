#include "operations.h"
#include "exceptions.h"
#include "machine.h"
#include "..\SimulationEngine\Sched.h"
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

#pragma region Operation

Operation::Operation(const ID& id, const Time& time1, Operand* oper1, Operand* oper2) : id(id), time(time1) {
	operands.push_back(oper1);
	operands.push_back(oper2);
}

Assignment::Assignment(const ID& id, const Time& time1, Operand* oper1, Operand* oper2) : Operation(id, time1, oper1, oper2) {};

Addition::Addition(const ID& id, const Time& time1, Operand* oper1, Operand* oper2) : Operation(id, time1, oper1, oper2) {};

Multiplication::Multiplication(const ID& id, const Time& time1, Operand* oper1, Operand* oper2) : Operation(id, time1, oper1, oper2) {};

Exponentiation::Exponentiation(const ID& id, const Time& time1, Operand* oper1, Operand* oper2) : Operation(id, time1, oper1, oper2) {};



void Operation::notify(ID id)
{
	result = calculator();
	if (operandOfDepEq)
		operandOfDepEq->setValue(this);
	*Machine::finalFile << setw(6) << left << "(" + to_string(id) + ")" << Scheduler::Instance()->getCurTime() - getTime() << "ns/" << Scheduler::Instance()->getCurTime() << "ns" << endl;
	delete operands[0];
	delete operands[1];
	operands.clear();
}
bool Assignment::Isready() const
{
	return !(operands[1]->value() == NOTREADY);
}

bool Addition::Isready() const
{
	return (!(operands[0]->value() == NOTREADY) && !(operands[1]->value() == NOTREADY));
}

bool Multiplication::Isready() const
{
	return (!(operands[0]->value() == NOTREADY) && !(operands[1]->value() == NOTREADY));
}

bool Exponentiation::Isready() const
{
	return (!(operands[0]->value() == NOTREADY) && !(operands[1]->value() == NOTREADY));

}




double Assignment::calculator()
{

	Memory::Instance()->setValue(dynamic_cast<Variable*>(operands[0])->getName(), operands[1]->value());
	return operands[1]->value();
}
double Addition::calculator()
{
	return operands[0]->value() + operands[1]->value();
}

double Multiplication::calculator()
{
	return operands[0]->value() * operands[1]->value();
}

double Exponentiation::calculator()
{
	return pow(operands[0]->value(), operands[1]->value());
}

#pragma endregion
#pragma region Operand

Operand::Operand(const double& a) : val(a) {}

Constant::Constant(const string& o) : Operand(stoi(o)) {}

double Variable::value() const
{
	return Memory::Instance()->getValue(name);
};


Variable::Variable(const string& o) : Operand(NOTREADY), name(o) {};

Result::Result(string o, const vector<Operation*>& operations) : Operand(NOTREADY)
{
	val = NOTREADY;
	ID operationID = stoi(o.substr(1, o.length() - 2));
	for (auto it = operations.begin(); it != operations.end(); ++it)
	{
		if ((*it)->getID() == operationID) (*it)->linkWithNewOne(this);
	}
}


#pragma endregion






















