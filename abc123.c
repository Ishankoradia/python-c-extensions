#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <numpy/arrayobject.h>
#include <stdio.h>


PyObject *add(PyObject *self, PyObject *args) {
    double x;
    double y;
    PyArg_ParseTuple(args, "dd", &x, &y); // ii corresponds to int, int
    return PyFloat_FromDouble(x + y);
};

static PyObject *sum(PyObject *self, PyObject *args) {
    PyArrayObject *arr;
    PyArg_ParseTuple(args, "O!", &PyArray_Type, &arr);
    if (PyErr_Occurred()) {
        return NULL;
    }

    if(!PyArray_Check(arr)) {
        PyErr_SetString(PyExc_TypeError, "Argument must be a numeric numpy array");
        return NULL;
    }
    // double *data = PyArray_DATA(arr);
    int64_t size = PyArray_SIZE(arr);
    double *data;
    npy_intp dims[] = {[0] = size};
    PyArray_AsCArray((PyObject **)&arr, &data, dims, 1, PyArray_DescrFromType(NPY_DOUBLE));
    if (PyErr_Occurred()) {
        return NULL;
    }

    double total = 0;
    for (int i=0; i<size; ++i) {
        total += data[i];
    }
    return PyFloat_FromDouble(total);
};


static PyObject *double_arr(PyObject *self, PyObject *args) {
    PyArrayObject *arr;
    PyArg_ParseTuple(args, "O!", &PyArray_Type, &arr);
    if (PyErr_Occurred()) {
        return NULL;
    }

    if(!PyArray_Check(arr)) {
        PyErr_SetString(PyExc_TypeError, "Argument must be a numeric numpy array");
        return NULL;
    }
    // double *data = PyArray_DATA(arr);
    int64_t size = PyArray_SIZE(arr);
    double *data;
    npy_intp dims[] = {[0] = size};
    PyArray_AsCArray((PyObject **)&arr, &data, dims, 1, PyArray_DescrFromType(NPY_DOUBLE));
    if (PyErr_Occurred()) {
        return NULL;
    }

    PyObject *result = PyArray_SimpleNew(1, dims, NPY_DOUBLE);
    if (PyErr_Occurred()) { // it is possible that the memory is full and its not able to create an array
        return NULL;
    }
    double *result_data = PyArray_DATA((PyArrayObject *)result);
    for (int i=0; i<size; ++i) {
        result_data[i] = (2 * data[i]);   
    }
    return result;
};

static PyMethodDef methods[] = {
    { "add", add, METH_VARARGS, "Adds two numbers" },
    { "sum", sum, METH_VARARGS, "Calculate sum of numpy array"},
    { "double", double_arr, METH_VARARGS, "Double elements in numpy array"},
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
    PyObject *module = PyModule_Create(&abc123);
    import_array();
    return module;
}