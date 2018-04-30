#ifndef  _MACHINE_H_
#define _MACHINE_H_

#include "memory.h"
#include "operations.h"
#include <fstream>
#include <map>
#include <string>
using namespace std;

//Define operation delay
const Time TimeOfAssignment = 3;
const Time TimeOfAddition = 5;
const Time TimeOfMultiplication = 8;
const Time TimeOfExponentiation = 10;




class Machine {

public:
	static Machine* getInstance();
	Machine() {}//
	static void release() { delete instance; instance = nullptr; }//

private:
	static Machine* instance;//
	vector <Operation*> operations;//
	Operation*returnOperation(const string&, const vector<Operation*>&);


private:
	Machine(const Machine&) = delete; //
	Machine(Machine&&) = delete;//
	Machine& operator=(const Machine&) = delete;//
	Machine&& operator=(Machine&&) = delete;//
	void makeOperation(const ID& id, const char& op, const string& ooper1, const string& oper2);//
	Operand* makeOperand(const string&); //
	void operationLoad(const string&);//
public:
	void exec(const string& path);
public:
	static ofstream* finalFile;//

};






#endif // ! _MACHINE_H_
