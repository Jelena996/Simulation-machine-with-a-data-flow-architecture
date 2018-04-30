#include "helper.h"
#include "exceptions.h"



fstream* openFile(const string& name)
{
	fstream* file = new fstream(name, ios::in);
	if (file->good()) return file;
	else
		throw FileNotFoundException(name);

}


string imf(string name)
{
	return name.replace(name.end() - 3, name.end(), ".imf");
}


string log(string name)
{
	return name.replace(name.end() - 3, name.end(), "log");
}













