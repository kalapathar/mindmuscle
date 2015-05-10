#include "PyInstall/include/python2.7/Python.h"
#include <pthread.h>
#include <string>
#include <iostream>
using namespace std;

#include "MindInterface.h"


MindInterface::MindInterface(){
	Py_Initialize();

	//Initialize thread support
	PyEval_InitThreads();

	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append(\"./py\")");//Add py/ in our system path


	pName = PyString_FromString("parsepackets");
	pModule = PyImport_Import(pName);
	pDict = PyModule_GetDict(pModule);

	state = 0;
	counter = 0;
}

MindInterface::~MindInterface(){
	disconnect();//Disconnect headset

	// Clean up
    Py_DECREF(pModule);
    Py_DECREF(pName);


	Py_Finalize();
}

void MindInterface::update(){
	if(state == 0){
		//Has not attempted to connect yet
		init_connect();
		state = 1;
		counter = 60;
	}
	if(state == 1){
		//Opened initial connection
		//Keep trying to connect until get_status returns 2
		if(counter < 0){
			counter = 60;
			if(get_status() != 2){
				if(get_status() != 1) attempt_connect();//Don't attempt to reconnect when status is "scanning"
			} else {
				state = 2;
				//Connected!
				cout << "Connected!" << endl;
			}
		}
	}
	if(state == 2){
		//Keep updating the focus
		if(counter < 0){
			counter = 10;
			get_focus();
			cout << focusValue << endl;
		}
	}
	counter --;
}

void MindInterface::init_connect(){
	PyObject *pFunc = PyDict_GetItemString(pDict, "init_connect");
	PyObject_CallObject(pFunc, NULL);
}

void MindInterface::attempt_connect(){
	PyObject *pFunc = PyDict_GetItemString(pDict, "attempt_connect");
	PyObject_CallObject(pFunc, NULL);
}

void MindInterface::get_focus(){
	PyObject *pFunc = PyDict_GetItemString(pDict, "get_focus");
	PyObject * pValue = PyObject_CallObject(pFunc, NULL);
	if(pValue != NULL){
		focusValue = PyInt_AsLong(pValue);
	}
}

int MindInterface::get_status(){
	PyObject *pFunc = PyDict_GetItemString(pDict, "get_status");
	PyObject * pValue = PyObject_CallObject(pFunc, NULL);
	if(pValue != NULL){
		long status = PyInt_AsLong(pValue);
		return status;
	}
	return -1;
}

void MindInterface::disconnect(){
	PyObject *pFunc = PyDict_GetItemString(pDict, "disconnect");
	PyObject_CallObject(pFunc, NULL);
}