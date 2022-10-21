#include <Python.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <cmath>
#include <string>


using namespace std;      

int userInput;            //int and string for userinput and reading a file line
string str;
string fileLine;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode3");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode3");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode3");           //takes function from pythoncode
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}
void UserMenu() {                                                        //displays simple menu for user options
	cout << "---------------------User Menu----------------------\n";
	cout << "1: Produce a list of items purchased with quantites \n";
	cout << "2: Display how many times a specific item was sold \n";
	cout << "3: Produce a histogram of sales data \n";
	cout << "4: Exit the program \n\n";
	cout << "Enter your selection as a number: 1,2,3 or 4.. \n";
	cout << "-----------------------------------------------------\n\n";

	cin >> userInput;                    //takes userinput

	if (userInput == 1)                                 //if option 1 prints txt file list items and quantites
	{
		cout << "\n\nPrinting items and quantites sold today: \n\n";
		CallProcedure("ItemCounter");
		cout << "\n\n";
		return;
	}
	else if (userInput == 2)                                  //if ooption 2 prints item names and sales for said item
	{
		cout << "\n\nPlease enter the item name: \n\n";
		cin >> str;
		cout << "\n\n";
		cout << "Printing the sales for " << str << ":\n\n";
		cout << str << ":" <<
		callIntFunc("SpecificItemCounter", str) << "\n\n";
		return;
	}
	else if (userInput == 3)            // if user chooses 3 shows txt file into a histogram with *//asterics
	{
		cout << "\n\nWriting items and quantites sold today to a file: \n\n";
		CallProcedure("ItemCounterWriter");
		cout << "\n\n";
		ifstream frequencyFile("frequency.dat");      //makes new txt file showing frequency of items taken from cs210_file..txt
		string item;
		int count;
		while (getline(frequencyFile, fileLine))
		{
			istringstream iss(fileLine);
			if (!(iss >> item >> count)) { break; }
			cout << item << " " << string(count, '*') << endl;
		}
		cout << "\n\n";
		return;
	} 
	else if (userInput == 4)                        //if user input is option 4 program exits
	{    
		cout << "\n\nExiting the program....\n\n";
		exit(EXIT_SUCCESS);
	}
	else
	{
		cout << "\n\nPlease enter a valid input choice from menu..\n\n";
		return;
	}
}
int main()        //infinite loop to display menu after every choice
{
	while (1)
	{
		UserMenu();
	}
	return 0;
}
