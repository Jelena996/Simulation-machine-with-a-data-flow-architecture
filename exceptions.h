#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

#include<exception>
#include<string>
using namespace std;


class FileNotFoundException : public exception
{
public:
	FileNotFoundException(const string& name) { message = "File is not found" + name; }
	virtual char const* what() const override {
		return message.c_str();
	}

private:
	string message;


};



class VariableNotFoundException : public exception
{
public:
	VariableNotFoundException() {
		message = "Variable is not found";
	}
	virtual char const* what() { return message.c_str(); }
private:
	string message;
};



#endif _EXCEPTIONS_H_H