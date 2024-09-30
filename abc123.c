#include <Python.h>
#include <stdio.h>


PyObject *add(PyObject *self, PyObject *args) {
    double x;
    double y;
    PyArg_ParseTuple(args, "dd", &x, &y); // ii corresponds to int, int
    return PyFloat_FromDouble(x + y);
};

static PyMethodDef methods[] = {
    { "add", add, METH_VARARGS, "Adds two numbers" },
    { NULL, NULL, 0, NULL}
};

static struct PyModuleDef abc123 = {
    PyModuleDef_HEAD_INIT,
    "This is the module name",
    "This is the module docstring",
    -1,
    methods,      // Methods
    NULL,      // Slots
    NULL,      // Traverse function
    NULL,      // Clear function
    NULL       // Free function
};

PyMODINIT_FUNC PyInit_abc123() {
    printf("Hello, World!\n");  
    return PyModule_Create(&abc123);
}

// '/Users/ishankoradia/.pyenv/versions/3.11.0/include/python3.11'
// gcc -shared -o abc123.so abc123.c -I/Users/ishankoradia/.pyenv/versions/3.11.0/include/python3.11 -L/Users/ishankoradia/.pyenv/versions/3.11.0/lib -lpython3.11