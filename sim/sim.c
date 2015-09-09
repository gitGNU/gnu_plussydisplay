/*
	Plussy Display
	Copyright (C) 2015  Christian Carlowitz <chca@cmesh.de>

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <python2.7/Python.h>
#include <stdint.h>

#define LED_NUM 20

#ifndef ANIMATION
#define ANIMATION anim_test
#endif

extern void ANIMATION(uint8_t* data, uint16_t len);

static PyObject* callAnimation(PyObject* self, PyObject* args)
{
	// get list object
	PyObject* dataL = 0;
	Py_ssize_t dataLen = 0;
	if(!PyArg_ParseTuple(args, "O", &dataL))
		return 0;
	dataLen = PyList_Size(dataL);
	
	// extract data
	uint8_t data[LED_NUM*3];
	for(int i = 0; i < (LED_NUM*3); i++)
	{
		if(i < dataLen)
			data[i] = (uint8_t)PyInt_AsLong( PyList_GetItem(dataL, i) );
		else
			data[i] = 0;
	}
	
	// call animation
	ANIMATION(data, LED_NUM*3);
	
	// return data
	for(int i = 0; i < (LED_NUM*3); i++)
	{
		if(i < dataLen)
			PyList_SetItem(dataL, i, PyInt_FromLong(data[i]));
	}
	
	// return
	Py_INCREF(Py_None);
	return Py_None;
}

static PyMethodDef simMethods[] = {
	{"callAnimation", callAnimation, METH_VARARGS, "call animation"},
	{0,0,0,0}
};

PyMODINIT_FUNC
initsim(void)
{
	Py_InitModule("sim", simMethods);
}

