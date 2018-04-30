#ifndef _MEMORY_H_
#define _MEMORY_H_
//#include"operations.h"
#include <fstream>
#include <map>
#include <string>
using namespace std;


class Memory
{
private:
	map<string, double> storage;
	static Memory* instance;

protected:
	Memory() {}
	~Memory() { storage.clear(); }

public:

	static Memory* Instance();
	static void release() { delete instance; instance = nullptr; }
	void addVariable(const string&);
	void setValue(const string& varName, double val) { storage[varName] = val; }
	double getValue(const string& varName);
};





#endif _MEMORY_H_