#include "memory.h"
#include"exceptions.h"
#include"operations.h"

Memory* Memory::Instance()
{
	if (instance == nullptr)
		instance = new Memory();
	return instance;
}


void Memory::addVariable(const string& o)
{
	storage[o] = NOTREADY;
}



double Memory::getValue(const string& varName)
{
	for (auto it = storage.begin(); it != storage.end(); ++it)
		if (it->first == varName) return it->second;
	throw VariableNotFoundException();
}
