#ifndef _COMPILER_H_
#define _COMPILER_H_

#include <fstream>
using namespace std;


class Compailer {

public:
	static Compailer* getInstance();
	Compailer() {}
	static void release() { delete instance; instance = nullptr; }
private:
	static Compailer* instance;

private:
	void removeBlanks(string&);
	string& takeRightHandSide(string equation);
	void compaile(const string& name);
	Compailer(const Compailer&) = delete;
	Compailer(Compailer&&) = delete;
	Compailer& operator= (const Compailer&) = delete;
	Compailer& operator=(Compailer&&) = delete;


};
