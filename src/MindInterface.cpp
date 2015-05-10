#include "PyInstall/include/python2.7/Python.h"

#include <string>
#include <iostream>
using namespace std;

#include "MindInterface.h"


MindInterface::MindInterface(){
	cout << "Hello Python!" << endl;
	Py_Initialize();

	// PyObject *pName, *pModule, *pDict, *pFunc, *pValue;
	// pName = PyString_FromString("py/embed");
	// pModule = PyImport_Import(pName);
	// pDict = PyModule_GetDict(pModule);
	//pFunc = PyDict_GetItemString(pDict, "helloPython");

	//  if (PyCallable_Check(pFunc)) 
 //    {
 //        PyObject_CallObject(pFunc, NULL);
 //    } else 
 //    {
 //        PyErr_Print();
 //    }

 //    // Clean up
 //    Py_DECREF(pModule);
 //    Py_DECREF(pName);

	Py_Finalize();
}

MindInterface::~MindInterface(){
	cout << "Goodbye" << endl;

}