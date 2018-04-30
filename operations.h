#ifndef _OPERATIONS_H_
#define _OPERATIONS_H_
#include "..\SimulationEngine\Types.h"
#include "..\SimulationEngine\Interfaces.h"
#include <vector>
#include<string>
#include "memory.h"

using namespace std;

const double NOTREADY = -3.14;

class Operand;
class Result;


class Operation : public ITimedElement
{
private:
	Time time;
	ID id;

protected:
	double result = NOTREADY;
	Result* operandOfDepEq = nullptr;
	vector<Operand*> operands;
	virtual double calculator() = 0;

public:
	Operation(const ID& id, const Time& time, Operand* oper1, Operand* oper2);
	ID getID() const { return id; }
	Time getTime() const { return time; }
	double getResult() const { return result; }
	void linkWithNewOne(Result* const res) { operandOfDepEq = res; }; //ova metoda samo postavlja pokazivac, odnosno veze dvije zavisne operacije, a to se naredjuje kada s epravi rezultat, (5) + 2 (3), tada se jedan operand  operacie (5) pravi kao rezultat, a na njega pokazuje i opeacija (3)
	virtual bool Isready() const;
	void notify(ID id);

};


class Assignment : public Operation
{
public:
	Assignment(const ID& id, const Time& time, Operand* oper1, Operand* oper2);
	bool Isready() const;
	double calculator();
};

class Addition : public Operation
{
public:
	Addition(const ID& id, const Time& time, Operand* oper1, Operand* oper2);
	bool Isready() const;
	double calculator();
};

class Multiplication : public Operation
{
public:
	Multiplication(const ID& id, const Time& time, Operand* oper1, Operand* oper2);
	bool Isready() const;
	double calculator();
};

class Exponentiation : public Operation
{
public:
	Exponentiation(const ID& id, const Time& time, Operand* oper1, Operand* oper2);
	bool Isready() const;
	double calculator();
};





// NEW CLASS OPERAND 
class Operand
{
protected:
	double val;
public:
	Operand(const double& oper);
	virtual double value() const = 0;

};

class Constant : public Operand
{
public:
	Constant(const string& oper);
	double value() const { return val; }

};

class Variable : public Operand
{
private:
	string name;
public:

	Variable(const string& oper);
	string getName() const { return name; }
	double value() const;
};

class Result : public Operand
{
public:
	Result(string o, const vector<Operation*>& operations);
	double value() const { return val; }
	void setValue(Operation* operation) { val = operation->getResult(); };
};



#endif _OPERATIONS_H_