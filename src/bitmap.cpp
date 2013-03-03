/*
Copyright (C) 2009~  Gaetan Guidet

This file is part of excons.

excons is free software; you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or (at
your option) any later version.

excons is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
USA.
*/

#include "structures.h"

// ---

PyTypeObject FIICCPROFILEType = {
  PyObject_HEAD_INIT(NULL)
  0,
  "fipy.ICCProfile",
  sizeof(FIICCPROFILEObject),
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

PyObject* ICCP_new(PyTypeObject *type, PyObject *, PyObject *) {
  PyObject *self = type->tp_alloc(type, 0);
  FIICCPROFILEObject *o = (FIICCPROFILEObject*) self;
  o->iccp = 0;
  return self;
}

void ICCP_dealloc(PyObject *) {
  // NOOP
}

int ICCP_init(PyObject *pself, PyObject *args, PyObject *) {
  FIICCPROFILEObject *self = (FIICCPROFILEObject*)pself;
  PyObject *o = 0;
  if (!PyArg_ParseTuple(args, "|O", &o)) {
    return -1;
  }
  if (o) {
    if (!PyObject_TypeCheck(o, &FIBITMAPType)) {
      PyErr_SetString(PyExc_TypeError, "Expected a fipy.Bitmap as argument if any");
      return -1;
    }
    FIBITMAPObject *bo = (FIBITMAPObject*) o;
    self->iccp = FreeImage_GetICCProfile(bo->b);
  }
  return 0;
}

PyObject* ICCP_getFlags(PyObject *pself, void*) {
  FIICCPROFILEObject *self = (FIICCPROFILEObject*) pself;
  return PyInt_FromLong(self->iccp->flags);
}
int ICCP_setFlags(PyObject *pself, PyObject *val, void*) {
  FIICCPROFILEObject *self = (FIICCPROFILEObject*) pself;
  self->iccp->flags = (WORD) PyInt_AsLong(val);
  return 0;
}

static PyGetSetDef ICCP_getset[] = {
  {(char*)"flags", ICCP_getFlags, ICCP_setFlags, (char*)"", NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

bool InitICCProfile(PyObject *module) {
  
  FIICCPROFILEType.tp_doc = "FreeImage ICC Profile object";
  FIICCPROFILEType.tp_flags = Py_TPFLAGS_DEFAULT;
  FIICCPROFILEType.tp_new = ICCP_new;
  FIICCPROFILEType.tp_dealloc = ICCP_dealloc;
  FIICCPROFILEType.tp_init = ICCP_init;
  FIICCPROFILEType.tp_getset = ICCP_getset;
  
  if (PyType_Ready(&FIICCPROFILEType) < 0) {
    return false;
  }
  
  Py_INCREF(&FIICCPROFILEType);
  PyModule_AddObject(module, "ICCProfile", (PyObject*)&FIICCPROFILEType);
  
  return true;
}

// ---

PyTypeObject BITMAPINFOHEADERType = {
  PyObject_HEAD_INIT(NULL)
  0,
  "fipy.BitmapInfoHeader",
  sizeof(BITMAPINFOHEADERObject),
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static PyObject* BIH_getSize(PyObject *pself, void*) {
  BITMAPINFOHEADERObject *self = (BITMAPINFOHEADERObject*)pself;
  return PyInt_FromLong(self->bih.biSize);
}
static int BIH_setSize(PyObject *pself, PyObject *val, void*) {
  BITMAPINFOHEADERObject *self = (BITMAPINFOHEADERObject*)pself;
  self->bih.biSize = (DWORD) PyInt_AsLong(val);
  return 0;
}

static PyObject* BIH_getWidth(PyObject *pself, void*) {
  BITMAPINFOHEADERObject *self = (BITMAPINFOHEADERObject*)pself;
  return PyInt_FromLong(self->bih.biWidth);
}
static int BIH_setWidth(PyObject *pself, PyObject *val, void*) {
  BITMAPINFOHEADERObject *self = (BITMAPINFOHEADERObject*)pself;
  self->bih.biWidth = (LONG) PyInt_AsLong(val);
  return 0;
}

static PyObject* BIH_getHeight(PyObject *pself, void*) {
  BITMAPINFOHEADERObject *self = (BITMAPINFOHEADERObject*)pself;
  return PyInt_FromLong(self->bih.biHeight);
}
static int BIH_setHeight(PyObject *pself, PyObject *val, void*) {
  BITMAPINFOHEADERObject *self = (BITMAPINFOHEADERObject*)pself;
  self->bih.biHeight = (LONG) PyInt_AsLong(val);
  return 0;
}

static PyObject* BIH_getPlanes(PyObject *pself, void*) {
  BITMAPINFOHEADERObject *self = (BITMAPINFOHEADERObject*)pself;
  return PyInt_FromLong(self->bih.biPlanes);
}
static int BIH_setPlanes(PyObject *pself, PyObject *val, void*) {
  BITMAPINFOHEADERObject *self = (BITMAPINFOHEADERObject*)pself;
  self->bih.biPlanes = (WORD) PyInt_AsLong(val);
  return 0;
}

static PyObject* BIH_getBitCount(PyObject *pself, void*) {
  BITMAPINFOHEADERObject *self = (BITMAPINFOHEADERObject*)pself;
  return PyInt_FromLong(self->bih.biBitCount);
}
static int BIH_setBitCount(PyObject *pself, PyObject *val, void*) {
  BITMAPINFOHEADERObject *self = (BITMAPINFOHEADERObject*)pself;
  self->bih.biBitCount = (WORD) PyInt_AsLong(val);
  return 0;
}

static PyObject* BIH_getCompression(PyObject *pself, void*) {
  BITMAPINFOHEADERObject *self = (BITMAPINFOHEADERObject*)pself;
  return PyInt_FromLong(self->bih.biCompression);
}
static int BIH_setCompression(PyObject *pself, PyObject *val, void*) {
  BITMAPINFOHEADERObject *self = (BITMAPINFOHEADERObject*)pself;
  self->bih.biCompression = (DWORD) PyInt_AsLong(val);
  return 0;
}

static PyObject* BIH_getSizeImage(PyObject *pself, void*) {
  BITMAPINFOHEADERObject *self = (BITMAPINFOHEADERObject*)pself;
  return PyInt_FromLong(self->bih.biSizeImage);
}
static int BIH_setSizeImage(PyObject *pself, PyObject *val, void*) {
  BITMAPINFOHEADERObject *self = (BITMAPINFOHEADERObject*)pself;
  self->bih.biSizeImage = (DWORD) PyInt_AsLong(val);
  return 0;
}

static PyObject* BIH_getXPelsPerMeter(PyObject *pself, void*) {
  BITMAPINFOHEADERObject *self = (BITMAPINFOHEADERObject*)pself;
  return PyInt_FromLong(self->bih.biXPelsPerMeter);
}
static int BIH_setXPelsPerMeter(PyObject *pself, PyObject *val, void*) {
  BITMAPINFOHEADERObject *self = (BITMAPINFOHEADERObject*)pself;
  self->bih.biXPelsPerMeter = (LONG) PyInt_AsLong(val);
  return 0;
}

static PyObject* BIH_getYPelsPerMeter(PyObject *pself, void*) {
  BITMAPINFOHEADERObject *self = (BITMAPINFOHEADERObject*)pself;
  return PyInt_FromLong(self->bih.biYPelsPerMeter);
}
static int BIH_setYPelsPerMeter(PyObject *pself, PyObject *val, void*) {
  BITMAPINFOHEADERObject *self = (BITMAPINFOHEADERObject*)pself;
  self->bih.biYPelsPerMeter = (LONG) PyInt_AsLong(val);
  return 0;
}

static PyObject* BIH_getClrUsed(PyObject *pself, void*) {
  BITMAPINFOHEADERObject *self = (BITMAPINFOHEADERObject*)pself;
  return PyInt_FromLong(self->bih.biClrUsed);
}
static int BIH_setClrUsed(PyObject *pself, PyObject *val, void*) {
  BITMAPINFOHEADERObject *self = (BITMAPINFOHEADERObject*)pself;
  self->bih.biClrUsed = (DWORD) PyInt_AsLong(val);
  return 0;
}


static PyObject* BIH_getClrImportant(PyObject *pself, void*) {
  BITMAPINFOHEADERObject *self = (BITMAPINFOHEADERObject*)pself;
  return PyInt_FromLong(self->bih.biClrImportant);
}
static int BIH_setClrImportant(PyObject *pself, PyObject *val, void*) {
  BITMAPINFOHEADERObject *self = (BITMAPINFOHEADERObject*)pself;
  self->bih.biClrImportant = (DWORD) PyInt_AsLong(val);
  return 0;
}

static PyGetSetDef BIH_getset[] = {
  {(char*)"biSize", BIH_getSize, BIH_setSize, (char*)"", NULL},
  {(char*)"biWidth", BIH_getWidth, BIH_setWidth, (char*)"", NULL},
  {(char*)"biHeight", BIH_getHeight, BIH_setHeight, (char*)"", NULL},
  {(char*)"biPlanes", BIH_getPlanes, BIH_setPlanes, (char*)"", NULL},
  {(char*)"biBitCount", BIH_getBitCount, BIH_setBitCount, (char*)"", NULL},
  {(char*)"biCompression", BIH_getCompression, BIH_setCompression, (char*)"", NULL},
  {(char*)"biSizeImage", BIH_getSizeImage, BIH_setSizeImage, (char*)"", NULL},
  {(char*)"biXPelsPerMeter", BIH_getXPelsPerMeter, BIH_setXPelsPerMeter, (char*)"", NULL},
  {(char*)"biYPelsPerMeter", BIH_getYPelsPerMeter, BIH_setYPelsPerMeter, (char*)"", NULL},
  {(char*)"biClrUsed", BIH_getClrUsed, BIH_setClrUsed, (char*)"", NULL},
  {(char*)"biClrImportant", BIH_getClrImportant, BIH_setClrImportant, (char*)"", NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

bool InitBitmapInfoHeader(PyObject *module) {
  
  BITMAPINFOHEADERType.tp_new = PyType_GenericNew;
  BITMAPINFOHEADERType.tp_doc = "Bitmap Info Header";
  BITMAPINFOHEADERType.tp_flags = Py_TPFLAGS_DEFAULT;
  BITMAPINFOHEADERType.tp_getset = BIH_getset;
  
  if (PyType_Ready(&BITMAPINFOHEADERType) < 0) {
    return false;
  }
  
  Py_INCREF(&BITMAPINFOHEADERType);
  PyModule_AddObject(module, "BitmapInfoHeader", (PyObject*)&BITMAPINFOHEADERType);
  
  return true;
}

// ---

PyTypeObject BITMAPINFOType = {
  PyObject_HEAD_INIT(NULL)
  0,
  "fipy.BitmapInfo",
  sizeof(BITMAPINFOObject),
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static PyObject* BI_getHeader(PyObject *pself, void*) {
  BITMAPINFOObject *self = (BITMAPINFOObject*) pself;
  PyObject *obj = PyObject_CallObject((PyObject*)&BITMAPINFOHEADERType, NULL);
  BITMAPINFOHEADERObject *bih = (BITMAPINFOHEADERObject*)obj;
  memcpy(&(bih->bih), &(self->bi.bmiHeader), sizeof(BITMAPINFOHEADER));
  return obj;
}
static int BI_setHeader(PyObject *pself, PyObject *val, void*) {
  BITMAPINFOObject *self = (BITMAPINFOObject*) pself;
  if (!PyObject_TypeCheck(val, &BITMAPINFOHEADERType)) {
    PyErr_SetString(PyExc_TypeError, "Expected a fipy.BitmapInfoHeader object");
    return -1;
  }
  BITMAPINFOHEADERObject *bih = (BITMAPINFOHEADERObject*) val;
  memcpy(&(self->bi.bmiHeader), &(bih->bih), sizeof(BITMAPINFOHEADER));
  return 0;
}

static PyObject* BI_getColors(PyObject *pself, void*) {
  BITMAPINFOObject *self = (BITMAPINFOObject*) pself;
  return Py_BuildValue("(i,i,i)", self->bi.bmiColors[0].rgbRed, self->bi.bmiColors[0].rgbGreen, self->bi.bmiColors[0].rgbBlue);
}
static int BI_setColors(PyObject *pself, PyObject *val, void*) {
  BITMAPINFOObject *self = (BITMAPINFOObject*) pself;
  if (!PyTuple_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Expected a rgb tuple");
    return -1;
  }
  if (PyTuple_Size(val) != 3) {
    PyErr_SetString(PyExc_RuntimeError, "Tuple must have 3 elements");
    return -1;
  }
  self->bi.bmiColors[0].rgbRed = PyInt_AsLong(PyTuple_GetItem(val, 0));
  self->bi.bmiColors[0].rgbGreen = PyInt_AsLong(PyTuple_GetItem(val, 1));
  self->bi.bmiColors[0].rgbBlue = PyInt_AsLong(PyTuple_GetItem(val, 2));
  return 0;
}

static PyGetSetDef BI_getset[] = {
  {(char*)"bmiHeader", BI_getHeader, BI_setHeader, (char*)"", NULL},
  {(char*)"bmiColors", BI_getColors, BI_setColors, (char*)"", NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

bool InitBitmapInfo(PyObject *module) {
  
  BITMAPINFOType.tp_new = PyType_GenericNew;
  BITMAPINFOType.tp_doc = "Bitmap Info";
  BITMAPINFOType.tp_flags = Py_TPFLAGS_DEFAULT;
  BITMAPINFOType.tp_getset = BI_getset;
  
  if (PyType_Ready(&BITMAPINFOType) < 0) {
    return false;
  }
  
  Py_INCREF(&BITMAPINFOType);
  PyModule_AddObject(module, "BitmapInfo", (PyObject*)&BITMAPINFOType);
  
  return true;
}

// ---

PyTypeObject FIBITMAPType = {
  PyObject_HEAD_INIT(NULL)
  0,
  "fipy.Bitmap",
  sizeof(FIBITMAPObject),
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

PyObject* Bitmap_new(PyTypeObject *type, PyObject *, PyObject *) {
  FIBITMAPObject *self = (FIBITMAPObject*) type->tp_alloc(type, 0);
  self->own = true;
  self->b = 0;
  return (PyObject*)self;
}

void Bitmap_dealloc(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  if (self->own && self->b) {
    FreeImage_Unload(self->b);
    self->b = 0;
  }
}

int Bitmap_init(PyObject *pself, PyObject *args, PyObject *) {
  // support allocate and load
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  
  Py_ssize_t nargs = PyTuple_Size(args);
  
  PyObject *obj;
  
  if (nargs == 2) {
    obj = PyTuple_GetItem(args, 0);
    if (!PyInt_Check(obj)) {
      PyErr_SetString(PyExc_TypeError, "Expected int as first argument");
      return -1;
    }
    int fif = PyInt_AsLong(obj);
    
    obj = PyTuple_GetItem(args, 1);
    if (!PyString_Check(obj)) {
      PyErr_SetString(PyExc_TypeError, "Expected string as second argument");
      return -1;
    }
    char *filename = PyString_AsString(obj);
    
    self->own = true;
    self->b = FreeImage_Load((FREE_IMAGE_FORMAT)fif, filename);
  
  } else if (nargs >= 3 && nargs <= 6) {
    
    // could still be load with the flags argument of allocated
    obj = PyTuple_GetItem(args, 1);
    if (PyString_Check(obj)) {
      
      char *filename = PyString_AsString(obj);
      
      obj = PyTuple_GetItem(args, 0);
      if (!PyInt_Check(obj)) {
        PyErr_SetString(PyExc_TypeError, "Expected int as first argument");
        return -1;
      }
      int fif = PyInt_AsLong(obj);
      
      obj = PyTuple_GetItem(args, 2);
      if (!PyInt_Check(obj)) {
        PyErr_SetString(PyExc_TypeError, "Expected int as third argument");
        return -1;
      }
      int flags = PyInt_AsLong(obj);
      
      self->own = true;
      self->b = FreeImage_Load((FREE_IMAGE_FORMAT)fif, filename, flags);
      
    } else if (PyInt_Check(obj)) {
      // allocate
      int h = PyInt_AsLong(obj);
      
      obj = PyTuple_GetItem(args, 0);
      if (!PyInt_Check(obj)) {
        PyErr_SetString(PyExc_TypeError, "Expected int as first argument");
        return -1;
      }
      int w = PyInt_AsLong(obj);
      
      obj = PyTuple_GetItem(args, 2);
      if (!PyInt_Check(obj)) {
        PyErr_SetString(PyExc_TypeError, "Expected int as third argument");
        return -1;
      }
      int bpp = PyInt_AsLong(obj);
      
      unsigned int rm=0, gm=0, bm=0;
      
      if (nargs >= 4) {
        obj = PyTuple_GetItem(args, 3);
        if (!PyInt_Check(obj)) {
          PyErr_SetString(PyExc_TypeError, "Expected int as 4th argument");
          return -1;
        }
        rm = PyInt_AsLong(obj);
      }
      
      if (nargs >= 5) {
        obj = PyTuple_GetItem(args, 4);
        if (!PyInt_Check(obj)) {
          PyErr_SetString(PyExc_TypeError, "Expected int as 5th argument");
          return -1;
        }
        gm = PyInt_AsLong(obj);
      }
      
      if (nargs >= 6) {
        obj = PyTuple_GetItem(args, 5);
        if (!PyInt_Check(obj)) {
          PyErr_SetString(PyExc_TypeError, "Expected int as 6th argument");
          return -1;
        }
        bm = PyInt_AsLong(obj);
      }
      
      self->own = true;
      self->b = FreeImage_Allocate(w, h, bpp, rm, gm, bm);
      
    } else {
      PyErr_SetString(PyExc_TypeError, "Expected string or int as second argument");
      return -1;
    }
    
  } else if (nargs == 0) {
    // NOOP
    
  } else {
    
    PyErr_SetString(PyExc_RuntimeError, "Invalid arguments");
    return -1;
  }
  return 0;
}

PyObject* Bitmap_allocate(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  
  int w, h, bpp;
  unsigned int rm=0, gm=0, bm=0;
  
  Py_ssize_t nargs = PyTuple_Size(args);
  
  if (nargs < 3 || nargs > 6) {
    PyErr_SetString(PyExc_RuntimeError, "Expected at least 3 arguments, at most 6");
    return NULL;
  }
  
  PyObject *obj = NULL;
  
  obj = PyTuple_GetItem(args, 0);
  if (!PyInt_Check(obj)) {
    PyErr_SetString(PyExc_RuntimeError, "Expected int as first argument");
    return NULL;
  }
  w = PyInt_AsLong(obj);
  
  obj = PyTuple_GetItem(args, 1);
  if (!PyInt_Check(obj)) {
    PyErr_SetString(PyExc_RuntimeError, "Expected int as second argument");
    return NULL;
  }
  h = PyInt_AsLong(obj);
  
  obj = PyTuple_GetItem(args, 2);
  if (!PyInt_Check(obj)) {
    PyErr_SetString(PyExc_RuntimeError, "Expected int as third argument");
    return NULL;
  }
  bpp = PyInt_AsLong(obj);
  
  if (nargs >= 4) {
    obj = PyTuple_GetItem(args, 3);
    if (!PyInt_Check(obj)) {
      PyErr_SetString(PyExc_RuntimeError, "Expected int as 4th argument");
      return NULL;
    }
    rm = (unsigned int) PyInt_AsLong(obj);
  }
  
  if (nargs >= 5) {
    obj = PyTuple_GetItem(args, 4);
    if (!PyInt_Check(obj)) {
      PyErr_SetString(PyExc_RuntimeError, "Expected int as 5th argument");
      return NULL;
    }
    gm = (unsigned int) PyInt_AsLong(obj);
  }
  
  if (nargs >= 6) {
    obj = PyTuple_GetItem(args, 5);
    if (!PyInt_Check(obj)) {
      PyErr_SetString(PyExc_RuntimeError, "Expected int as 6th argument");
      return NULL;
    }
    bm = (unsigned int) PyInt_AsLong(obj);
  }
  
  if (self->own && self->b) {
    FreeImage_Unload(self->b);
  }
  
  self->own = true;
  self->b = FreeImage_Allocate(w, h, bpp, rm, gm, bm);
  
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* Bitmap_allocateT(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  
  int t, w, h, bpp=8;
  unsigned int rm=0, gm=0, bm=0;
  
  Py_ssize_t nargs = PyTuple_Size(args);
  
  if (nargs < 3 || nargs > 7) {
    PyErr_SetString(PyExc_RuntimeError, "Expected at least 3 arguments, at most 6");
    return NULL;
  }
  
  PyObject *obj = NULL;
  
  obj = PyTuple_GetItem(args, 0);
  if (!PyInt_Check(obj)) {
    PyErr_SetString(PyExc_RuntimeError, "Expected int as first argument");
    return NULL;
  }
  t = PyInt_AsLong(obj);
  
  obj = PyTuple_GetItem(args, 1);
  if (!PyInt_Check(obj)) {
    PyErr_SetString(PyExc_RuntimeError, "Expected int as second argument");
    return NULL;
  }
  w = PyInt_AsLong(obj);
  
  obj = PyTuple_GetItem(args, 2);
  if (!PyInt_Check(obj)) {
    PyErr_SetString(PyExc_RuntimeError, "Expected int as third argument");
    return NULL;
  }
  h = PyInt_AsLong(obj);
  
  if (nargs >= 4) {
    obj = PyTuple_GetItem(args, 3);
    if (!PyInt_Check(obj)) {
      PyErr_SetString(PyExc_RuntimeError, "Expected int as 4th argument");
      return NULL;
    }
    bpp = PyInt_AsLong(obj);
  }
  
  if (nargs >= 5) {
    obj = PyTuple_GetItem(args, 4);
    if (!PyInt_Check(obj)) {
      PyErr_SetString(PyExc_RuntimeError, "Expected int as 5th argument");
      return NULL;
    }
    rm = (unsigned int) PyInt_AsLong(obj);
  }
  
  if (nargs >= 6) {
    obj = PyTuple_GetItem(args, 5);
    if (!PyInt_Check(obj)) {
      PyErr_SetString(PyExc_RuntimeError, "Expected int as 6th argument");
      return NULL;
    }
    gm = (unsigned int) PyInt_AsLong(obj);
  }
  
  if (nargs >= 7) {
    obj = PyTuple_GetItem(args, 6);
    if (!PyInt_Check(obj)) {
      PyErr_SetString(PyExc_RuntimeError, "Expected int as 7th argument");
      return NULL;
    }
    bm = (unsigned int) PyInt_AsLong(obj);
  }
  
  if (self->own && self->b) {
    FreeImage_Unload(self->b);
  }
  
  self->own = true;
  self->b = FreeImage_AllocateT((FREE_IMAGE_TYPE)t, w, h, bpp, rm, gm, bm);
  
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* Bitmap_load(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  
  int fif;
  char *filename;
  int flags=0;
  
  if (!PyArg_ParseTuple(args, "is|i", &fif, &filename, &flags)) {
    return NULL;
  }
  
  if (self->own && self->b) {
    FreeImage_Unload(self->b);
  }
  
  self->own = true;
  self->b = FreeImage_Load((FREE_IMAGE_FORMAT)fif, filename, flags);
  
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* Bitmap_loadU(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  
  int fif;
  Py_UNICODE *filename;
  int flags=0;
  
  if (!PyArg_ParseTuple(args, "iu|i", &fif, &filename, &flags)) {
    return NULL;
  }
  
  if (self->own && self->b) {
    FreeImage_Unload(self->b);
  }
  
  self->own = true;
  self->b = FreeImage_LoadU((FREE_IMAGE_FORMAT)fif, (const wchar_t*)filename, flags);
  
  Py_INCREF(Py_None);
  return Py_None;
}

// TODO: FreeImage_LoadFromHandle

static PyObject* Bitmap_save(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  
  if (!(self->b)) {
    Py_INCREF(Py_False);
    return Py_False;
  }
  
  int fif;
  char *filename;
  int flags=0;
  
  if (!PyArg_ParseTuple(args, "is|i", &fif, &filename, &flags)) {
    return NULL;
  }
  
  if (FreeImage_Save((FREE_IMAGE_FORMAT)fif, self->b, filename, flags)) {
    Py_INCREF(Py_True);
    return Py_True;
  
  } else {
    Py_INCREF(Py_False);
    return Py_False;
  }
}

static PyObject* Bitmap_saveU(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  
  if (!(self->b)) {
    Py_INCREF(Py_False);
    return Py_False;
  }
  
  int fif;
  Py_UNICODE *filename;
  int flags=0;
  
  if (!PyArg_ParseTuple(args, "iu|i", &fif, &filename, &flags)) {
    return NULL;
  }
  
  if (FreeImage_SaveU((FREE_IMAGE_FORMAT)fif, self->b, (const wchar_t*)filename, flags)) {
    Py_INCREF(Py_True);
    return Py_True;
  
  } else {
    Py_INCREF(Py_False);
    return Py_False;
  }
}

// TODO: FreeImage_SaveToHandle

static PyObject* Bitmap_clone(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  
  if (!(self->b)) {
    Py_INCREF(Py_None);
    return Py_None;
  }
  
  PyObject *obj = PyObject_CallObject((PyObject*)&FIBITMAPType, NULL);
  FIBITMAPObject *clone = (FIBITMAPObject*)obj;
  clone->own = true;
  clone->b = FreeImage_Clone(self->b);
  
  return obj;
}

static PyObject* Bitmap_unload(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  if (self->own) {
    if (self->b) {
      FreeImage_Unload(self->b);
    }
  }
  self->b = 0;
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* Bitmap_getImageType(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  if (!(self->b)) {
    return PyInt_FromLong(FIT_UNKNOWN);
  } else {
    return PyInt_FromLong(FreeImage_GetImageType(self->b));
  }
}

static PyObject* Bitmap_getColorsUsed(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  if (!(self->b)) {
    return PyInt_FromLong(0);
  } else {
    return PyInt_FromLong(FreeImage_GetColorsUsed(self->b));
  }
}

static PyObject* Bitmap_getBPP(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  if (!(self->b)) {
    return PyInt_FromLong(0);
  } else {
    return PyInt_FromLong(FreeImage_GetBPP(self->b));
  }
}

static PyObject* Bitmap_getWidth(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  if (!(self->b)) {
    return PyInt_FromLong(0);
  } else {
    return PyInt_FromLong(FreeImage_GetWidth(self->b));
  }
}

static PyObject* Bitmap_getHeight(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  if (!(self->b)) {
    return PyInt_FromLong(0);
  } else {
    return PyInt_FromLong(FreeImage_GetHeight(self->b));
  }
}

static PyObject* Bitmap_getLine(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  if (!(self->b)) {
    return PyInt_FromLong(0);
  } else {
    return PyInt_FromLong(FreeImage_GetLine(self->b));
  }
}

static PyObject* Bitmap_getPitch(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  if (!(self->b)) {
    return PyInt_FromLong(0);
  } else {
    return PyInt_FromLong(FreeImage_GetPitch(self->b));
  }
}

static PyObject* Bitmap_getDIBSize(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  if (!(self->b)) {
    return PyInt_FromLong(0);
  } else {
    return PyInt_FromLong(FreeImage_GetDIBSize(self->b));
  }
}

// GetPalette -> array of 256 rgbquad ->
static PyObject* Bitmap_getPalette(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  if (!(self->b)) {
    Py_INCREF(Py_None);
    return Py_None;
  } else {
    RGBQUAD *pal = FreeImage_GetPalette(self->b);
    if (!pal) {
      Py_INCREF(Py_None);
      return Py_None;
    } else {
      PyObject *obj = PyList_New(256);
      for (unsigned int i=0; i<256; ++i) {
        PyObject *c = Py_BuildValue("BBB", pal[i].rgbRed, pal[i].rgbGreen, pal[i].rgbBlue);
        PyList_SetItem(obj, i, c);
      }
      return obj;
    }
  }
}

static PyObject* Bitmap_getDotsPerMeterX(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  if (!(self->b)) {
    return PyInt_FromLong(0);
  } else {
    return PyInt_FromLong(FreeImage_GetDotsPerMeterX(self->b));
  }
}

static PyObject* Bitmap_getDotsPerMeterY(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  if (!(self->b)) {
    return PyInt_FromLong(0);
  } else {
    return PyInt_FromLong(FreeImage_GetDotsPerMeterY(self->b));
  }
}

static PyObject* Bitmap_setDotsPerMeterX(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  if (self->b) {
    unsigned int res;
    if (!PyArg_ParseTuple(args, "I", &res)) {
      return NULL;
    }
    FreeImage_SetDotsPerMeterX(self->b, res);
  }
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* Bitmap_setDotsPerMeterY(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  if (self->b) {
    unsigned int res;
    if (!PyArg_ParseTuple(args, "I", &res)) {
      return NULL;
    }
    FreeImage_SetDotsPerMeterY(self->b, res);
  }
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* Bitmap_getInfoHeader(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  if (self->b) {
    BITMAPINFOHEADER *bih = FreeImage_GetInfoHeader(self->b);
    PyObject *pobj = PyObject_CallObject((PyObject*)&BITMAPINFOHEADERType, NULL);
    BITMAPINFOHEADERObject *obj = (BITMAPINFOHEADERObject*) pobj;
    memcpy(&(obj->bih), bih, sizeof(BITMAPINFOHEADER));
    return pobj;
  } else {
    Py_INCREF(Py_None);
    return Py_None;
  }
}

static PyObject* Bitmap_getInfo(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  if (self->b) {
    BITMAPINFO *bi = FreeImage_GetInfo(self->b);
    PyObject *pobj = PyObject_CallObject((PyObject*)&BITMAPINFOType, NULL);
    BITMAPINFOObject *obj = (BITMAPINFOObject*) pobj;
    memcpy(&(obj->bi), bi, sizeof(BITMAPINFO));
    return pobj;
  } else {
    Py_INCREF(Py_None);
    return Py_None;
  }
}

static PyObject* Bitmap_getColorType(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  if (self->b) {
    return PyInt_FromLong(FreeImage_GetColorType(self->b));
  } else {
    PyErr_SetString(PyExc_RuntimeError, "No image data");
    return 0;
  }
}

static PyObject* Bitmap_getRedMask(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  if (self->b) {
    return PyInt_FromLong(FreeImage_GetRedMask(self->b));
  } else {
    PyErr_SetString(PyExc_RuntimeError, "No image data");
    return 0;
  }
}

static PyObject* Bitmap_getGreenMask(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  if (self->b) {
    return PyInt_FromLong(FreeImage_GetGreenMask(self->b));
  } else {
    PyErr_SetString(PyExc_RuntimeError, "No image data");
    return 0;
  }
}

static PyObject* Bitmap_getBlueMask(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  if (self->b) {
    return PyInt_FromLong(FreeImage_GetBlueMask(self->b));
  } else {
    PyErr_SetString(PyExc_RuntimeError, "No image data");
    return 0;
  }
}

static PyObject* Bitmap_getTransparencyCount(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  if (self->b) {
    return PyInt_FromLong(FreeImage_GetTransparencyCount(self->b));
  } else {
    return PyInt_FromLong(0);
  }
}

static PyObject* Bitmap_getTransparencyTable(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  if (self->b) {
    //Py_ssize_t count = FreeImage_GetTransparencyCount(self->b);
    Py_ssize_t count = 256;
    BYTE *tt = FreeImage_GetTransparencyTable(self->b);
    if (tt) {
      //PyBuffer_FromMemory((void*)tt, 256)
      PyObject *obj = PyString_FromStringAndSize(NULL, count);
      Py_ssize_t len = 0;
      char *buf = 0;
      PyString_AsStringAndSize(obj, &buf, &len);
      memcpy(buf, tt, len);
      return obj;
    }
  }
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* Bitmap_setTransparencyTable(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  if (self->b) {
    int len;
    char *tt;
    if (!PyArg_ParseTuple(args, "s#i", &tt, &len)) {
      return NULL;
    }
    FreeImage_SetTransparencyTable(self->b, (BYTE*)tt, len);
  }
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* Bitmap_setTransparent(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  if (self->b) {
    PyObject *onoff;
    if (!PyArg_ParseTuple(args, "O", &onoff)) {
      return NULL;
    }
    FreeImage_SetTransparent(self->b, onoff == Py_True);
  }
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* Bitmap_isTransparent(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  if (self->b) {
    if (FreeImage_IsTransparent(self->b)) {
      Py_INCREF(Py_True);
      return Py_True;
    }
  }
  Py_INCREF(Py_False);
  return Py_False;
}

static PyObject* Bitmap_setTransparentIndex(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  if (self->b) {
    int index;
    if (!PyArg_ParseTuple(args, "i", &index)) {
      return NULL;
    }
    FreeImage_SetTransparentIndex(self->b, index);
  }
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* Bitmap_getTransparentIndex(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  if (self->b) {
    return PyInt_FromLong(FreeImage_GetTransparentIndex(self->b));
  }
  return PyInt_FromLong(-1);
}

static PyObject* Bitmap_hasBackgroundColor(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  if (self->b) {
    if (FreeImage_HasBackgroundColor(self->b)) {
      Py_INCREF(Py_True);
      return Py_True;
    }
  }
  Py_INCREF(Py_False);
  return Py_False;
}

static PyObject* Bitmap_getBackgroundColor(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  if (self->b) {
    RGBQUAD col;
    if (FreeImage_GetBackgroundColor(self->b, &col)) {
      return Py_BuildValue("BBB", col.rgbRed, col.rgbGreen, col.rgbBlue);
    }
  }
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* Bitmap_setBackgroundColor(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  if (self->b) {
    PyObject *rgb;
    if (!PyArg_ParseTuple(args, "O", &rgb)) {
      return NULL;
    }
    if (!PyTuple_Check(rgb)) {
      PyErr_SetString(PyExc_TypeError, "Expected a rgb tuple");
      return NULL;
    }
    if (PyTuple_Size(rgb) != 3) {
      PyErr_SetString(PyExc_RuntimeError, "Tuple must have 3 elements");
      return NULL;
    }
    RGBQUAD col;
    PyArg_ParseTuple(rgb, "BBB", &(col.rgbRed), &(col.rgbGreen), &(col.rgbBlue));
    if (FreeImage_SetBackgroundColor(self->b, &col)) {
      Py_INCREF(Py_True);
      return Py_True;
    }
  }
  Py_INCREF(Py_False);
  return Py_False;
}

static PyObject* Bitmap_getBits(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*)pself;
  if (self->b) {
    BYTE *bits = FreeImage_GetBits(self->b);
    if (bits) {
      // ok now try to figure the size, return a string
      Py_ssize_t sz = 0;
      // compute size in bytes
      sz = FreeImage_GetHeight(self->b) * FreeImage_GetPitch(self->b);
      PyObject *pbuf = PyString_FromStringAndSize(NULL, sz);
      Py_ssize_t len;
      char *buf;
      PyString_AsStringAndSize(pbuf, &buf, &len);
      memcpy(buf, bits, len);
      return pbuf;
    }
  }
  Py_INCREF(Py_None);
  return Py_None;
}

// TODO: FreeImage_GetScanline

PyObject* Bitmap_getPixelIndex(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    BYTE idx;
    unsigned int x, y;
    if (!PyArg_ParseTuple(args, "II", &x, &y)) {
      return NULL;
    }
    if (FreeImage_GetPixelIndex(self->b, x, y, &idx)) {
      return PyInt_FromLong(idx);
    }
  }
  return PyInt_FromLong(-1);
}

PyObject* Bitmap_getPixelColor(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    RGBQUAD rgb;
    unsigned int x, y;
    if (!PyArg_ParseTuple(args, "II", &x, &y)) {
      return NULL;
    }
    if (FreeImage_GetPixelColor(self->b, x, y, &rgb)) {
      return Py_BuildValue("BBB", rgb.rgbRed, rgb.rgbGreen, rgb.rgbBlue);
    }
  }
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* Bitmap_setPixelIndex(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    int idx;
    unsigned int x, y;
    if (!PyArg_ParseTuple(args, "IIi", &x, &y, &idx)) {
      return NULL;
    }
    BYTE bidx = (BYTE)idx;
    if (FreeImage_SetPixelIndex(self->b, x, y, &bidx)) {
      Py_INCREF(Py_True);
      return Py_True;
    }
  }
  Py_INCREF(Py_False);
  return Py_False;
}

PyObject* Bitmap_setPixelColor(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    PyObject *o;
    unsigned int x, y;
    if (!PyArg_ParseTuple(args, "IIO", &x, &y, &o)) {
      return NULL;
    }
    if (!PyTuple_Check(o)) {
      PyErr_SetString(PyExc_TypeError, "Expected a rgb tuple as third argument");
      return NULL;
    }
    if (PyTuple_Size(o) != 3) {
      PyErr_SetString(PyExc_RuntimeError, "RGB tuple must have 3 elements");
      return NULL;
    }
    RGBQUAD col;
    PyArg_ParseTuple(o, "BBB", &(col.rgbRed), &(col.rgbGreen), &(col.rgbBlue));
    if (FreeImage_SetPixelColor(self->b, x, y, &col)) {
      Py_INCREF(Py_True);
      return Py_True;
    }
  }
  Py_INCREF(Py_False);
  return Py_False;
}

PyObject* Bitmap_convertTo4Bits(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  PyObject *obj = PyObject_CallObject((PyObject*)&FIBITMAPType, NULL);
  FIBITMAPObject *conv = (FIBITMAPObject*) obj;
  conv->b = FreeImage_ConvertTo4Bits(self->b);
  conv->own = true;
  return obj;
}

PyObject* Bitmap_convertTo8Bits(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  PyObject *obj = PyObject_CallObject((PyObject*)&FIBITMAPType, NULL);
  FIBITMAPObject *conv = (FIBITMAPObject*) obj;
  conv->b = FreeImage_ConvertTo8Bits(self->b);
  conv->own = true;
  return obj;
}

PyObject* Bitmap_convertToGreyscale(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  PyObject *obj = PyObject_CallObject((PyObject*)&FIBITMAPType, NULL);
  FIBITMAPObject *conv = (FIBITMAPObject*) obj;
  conv->b = FreeImage_ConvertToGreyscale(self->b);
  conv->own = true;
  return obj;
}

PyObject* Bitmap_convertTo16Bits555(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  PyObject *obj = PyObject_CallObject((PyObject*)&FIBITMAPType, NULL);
  FIBITMAPObject *conv = (FIBITMAPObject*) obj;
  conv->b = FreeImage_ConvertTo16Bits555(self->b);
  conv->own = true;
  return obj;
}

PyObject* Bitmap_convertTo16Bits565(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  PyObject *obj = PyObject_CallObject((PyObject*)&FIBITMAPType, NULL);
  FIBITMAPObject *conv = (FIBITMAPObject*) obj;
  conv->b = FreeImage_ConvertTo16Bits565(self->b);
  conv->own = true;
  return obj;
}

PyObject* Bitmap_convertTo24Bits(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  PyObject *obj = PyObject_CallObject((PyObject*)&FIBITMAPType, NULL);
  FIBITMAPObject *conv = (FIBITMAPObject*) obj;
  conv->b = FreeImage_ConvertTo24Bits(self->b);
  conv->own = true;
  return obj;
}

PyObject* Bitmap_convertTo32Bits(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  PyObject *obj = PyObject_CallObject((PyObject*)&FIBITMAPType, NULL);
  FIBITMAPObject *conv = (FIBITMAPObject*) obj;
  conv->b = FreeImage_ConvertTo32Bits(self->b);
  conv->own = true;
  return obj;
}

PyObject* Bitmap_colorQuantize(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    int q;
    if (!PyArg_ParseTuple(args, "i", &q)) {
      return NULL;
    }
    PyObject *o = PyObject_CallObject((PyObject*)&FIBITMAPType, NULL);
    FIBITMAPObject *b = (FIBITMAPObject*)o;
    b->own = true;
    b->b = FreeImage_ColorQuantize(self->b, (FREE_IMAGE_QUANTIZE)q);
    return o;
  }
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* Bitmap_colorQuantizeEx(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    int q = int(FIQ_WUQUANT);
    int ps = 256;
    int rs = 0;
    RGBQUAD *rpal = 0;
    PyObject *rp = 0; // rgb tuple list
    if (!PyArg_ParseTuple(args, "|iiO", &q, &ps, &rp)) {
      return NULL;
    }
    if (rp != 0) {
      if (!PyList_Check(rp)) {
        PyErr_SetString(PyExc_TypeError, "Palette must be a list of rgb tuples");
      }
      rs = PyList_Size(rp);
      rpal = new RGBQUAD[rs];
      for (int i=0; i<rs; ++i) {
        PyObject *col = PyList_GetItem(rp, i);
        if (!PyTuple_Check(col)) {
          delete[] rpal;
          PyErr_SetString(PyExc_TypeError, "Palette elements must be rgb tuples");
          return NULL;
        }
        if (PyTuple_Size(col) != 3) {
          delete[] rpal;
          PyErr_SetString(PyExc_TypeError, "RGB tuples must have 3 elements");
          return NULL;
        }
        PyArg_ParseTuple(col, "BBB", &(rpal[i].rgbRed), &(rpal[i].rgbGreen), &(rpal[i].rgbBlue));
      }
    }
    PyObject *o = PyObject_CallObject((PyObject*)&FIBITMAPType, NULL);
    FIBITMAPObject *b = (FIBITMAPObject*)o;
    b->own = true;
    b->b = FreeImage_ColorQuantizeEx(self->b, (FREE_IMAGE_QUANTIZE)q, ps, rs, rpal);
    if (rpal) {
      delete[] rpal;
    }
    return o;
  }
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* Bitmap_threshold(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    int t;
    if (!PyArg_ParseTuple(args, "i", &t)) {
      return NULL;
    }
    PyObject *o = PyObject_CallObject((PyObject*)&FIBITMAPType, NULL);
    FIBITMAPObject *b = (FIBITMAPObject*)o;
    b->own = true;
    b->b = FreeImage_Threshold(self->b, (BYTE)t);
    return o;
  }
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* Bitmap_dither(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    int d;
    if (!PyArg_ParseTuple(args, "i", &d)) {
      return NULL;
    }
    PyObject *o = PyObject_CallObject((PyObject*)&FIBITMAPType, NULL);
    FIBITMAPObject *b = (FIBITMAPObject*)o;
    b->own = true;
    b->b = FreeImage_Dither(self->b, (FREE_IMAGE_DITHER)d);
    return o;
  }
  Py_INCREF(Py_None);
  return Py_None;
}

// TODO: FreeImage_ConvertFromRawBits
// TODO: FreeImage_ConvertToRawBits

PyObject* Bitmap_convertToStandardType(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    PyObject *scaleLin = 0;
    if (!PyArg_ParseTuple(args, "|O", &scaleLin)) {
      return NULL;
    }
    bool sl = true;
    if (scaleLin) {
      if (!PyBool_Check(scaleLin)) {
        PyErr_SetString(PyExc_TypeError, "Expected boolean argument");
        return NULL;
      }
      sl = (scaleLin == Py_True);
    }
    PyObject *o = PyObject_CallObject((PyObject*)&FIBITMAPType, NULL);
    FIBITMAPObject *b = (FIBITMAPObject*)o;
    b->own = true;
    b->b = FreeImage_ConvertToStandardType(self->b, sl);
    return o;
  }
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* Bitmap_convertToType(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    int fit;
    PyObject *scaleLin = 0;
    if (!PyArg_ParseTuple(args, "i|O", &fit, &scaleLin)) {
      return NULL;
    }
    bool sl = true;
    if (scaleLin) {
      if (!PyBool_Check(scaleLin)) {
        PyErr_SetString(PyExc_TypeError, "Expected boolean argument");
        return NULL;
      }
      sl = (scaleLin == Py_True);
    }
    PyObject *o = PyObject_CallObject((PyObject*)&FIBITMAPType, NULL);
    FIBITMAPObject *b = (FIBITMAPObject*)o;
    b->own = true;
    b->b = FreeImage_ConvertToType(self->b, (FREE_IMAGE_TYPE)fit, sl);
    return o;
  }
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* Bitmap_convertToRGBF(PyObject *pself, PyObject *) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    PyObject *o = PyObject_CallObject((PyObject*)&FIBITMAPType, NULL);
    FIBITMAPObject *b = (FIBITMAPObject*)o;
    b->own = true;
    b->b = FreeImage_ConvertToRGBF(self->b);
    return o;
  }
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* Bitmap_toneMapping(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    double firstParam=0.0, secondParam=0.0;
    int tmo;
    if (!PyArg_ParseTuple(args, "i|dd", &tmo, &firstParam, &secondParam)) {
      return NULL;
    }
    PyObject *o = PyObject_CallObject((PyObject*)&FIBITMAPType, NULL);
    FIBITMAPObject *b = (FIBITMAPObject*)o;
    b->own = true;
    b->b = FreeImage_ToneMapping(self->b, (FREE_IMAGE_TMO)tmo, firstParam, secondParam);
    return o;
  }
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* Bitmap_tmoDrago03(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    double gamma=2.2, exposure=0.0;
    if (!PyArg_ParseTuple(args, "|dd", &gamma, &exposure)) {
      return NULL;
    }
    PyObject *o = PyObject_CallObject((PyObject*)&FIBITMAPType, NULL);
    FIBITMAPObject *b = (FIBITMAPObject*)o;
    b->own = true;
    b->b = FreeImage_TmoDrago03(self->b, gamma, exposure);
    return o;
  }
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* Bitmap_tmoReinhard05(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    double intensity=2.2, contrast=0.0;
    if (!PyArg_ParseTuple(args, "|dd", &intensity, &contrast)) {
      return NULL;
    }
    PyObject *o = PyObject_CallObject((PyObject*)&FIBITMAPType, NULL);
    FIBITMAPObject *b = (FIBITMAPObject*)o;
    b->own = true;
    b->b = FreeImage_TmoReinhard05(self->b, intensity, contrast);
    return o;
  }
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* Bitmap_tmoFattal02(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    double sat=0.5, att=0.85;
    if (!PyArg_ParseTuple(args, "|dd", &sat, &att)) {
      return NULL;
    }
    PyObject *o = PyObject_CallObject((PyObject*)&FIBITMAPType, NULL);
    FIBITMAPObject *b = (FIBITMAPObject*)o;
    b->own = true;
    b->b = FreeImage_TmoFattal02(self->b, sat, att);
    return o;
  }
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* Bitmap_getICCProfile(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    PyObject *o = PyObject_CallObject((PyObject*)&FIICCPROFILEType, NULL);
    FIICCPROFILEObject *po = (FIICCPROFILEObject*) o;
    po->iccp = FreeImage_GetICCProfile(self->b);
    return o;
  }
  Py_INCREF(Py_None);
  return Py_None;
}

// TODO: FreeImage_CreateICCProfile(image, void*, size)

PyObject* Bitmap_destroyICCProfile(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    FreeImage_DestroyICCProfile(self->b);
  }
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* Bitmap_getMetaCount(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    int mdl;
    if (!PyArg_ParseTuple(args, "i", &mdl)) {
      return NULL;
    }
    return PyInt_FromLong(FreeImage_GetMetadataCount((FREE_IMAGE_MDMODEL)mdl, self->b));
  }
  return PyInt_FromLong(0);
}

PyObject* Bitmap_getMeta(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    int mdl;
    char *key;
    if (!PyArg_ParseTuple(args, "is", &mdl, &key)) {
      return NULL;
    }
    FITAG *tag = 0;
    if (FreeImage_GetMetadata((FREE_IMAGE_MDMODEL)mdl, self->b, key, &tag)) {
      PyObject *po = PyObject_CallObject((PyObject*)&FITAGType, NULL);
      FITAGObject *o = (FITAGObject*)po;
      o->t = tag;
      o->own = false;
      return po;
    }
  }
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* Bitmap_setMeta(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    int mdl;
    char *key;
    PyObject *pto;
    if (!PyArg_ParseTuple(args, "isO", &mdl, &key, &pto)) {
      return NULL;
    }
    if (!PyObject_TypeCheck(pto, &FITAGType)) {
      PyErr_SetString(PyExc_TypeError, "Expected fipy.Tag as third argument");
      return NULL;
    }
    FITAGObject *to = (FITAGObject*) pto;
    if (FreeImage_SetMetadata((FREE_IMAGE_MDMODEL)mdl, self->b, key, to->t)) {
      Py_INCREF(Py_True);
      return Py_True;
    }
  }
  Py_INCREF(Py_False);
  return Py_False;
}

#if FREEIMAGE_MINOR_VERSION >= 12
PyObject* Bitmap_cloneMeta(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    PyObject *po;
    if (!PyArg_ParseTuple(args, "O", &po)) {
      return NULL;
    }
    if (!PyObject_TypeCheck(po, &FIBITMAPType)) {
      PyErr_SetString(PyExc_TypeError, "Expected fipy.Bitmap as argument");
      return NULL;
    }
    FIBITMAPObject *o = (FIBITMAPObject*) po;
    if (FreeImage_CloneMetadata(self->b, o->b)) {
      Py_INCREF(Py_True);
      return Py_True;
    }
  }
  Py_INCREF(Py_False);
  return Py_False;
}
#endif

PyObject* Bitmap_rotateClassic(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    double angle;
    if (!PyArg_ParseTuple(args, "d", &angle)) {
      return NULL;
    }
    PyObject *po = PyObject_CallObject((PyObject*)&FIBITMAPType, NULL);
    FIBITMAPObject *o = (FIBITMAPObject*) po;
    o->b = FreeImage_RotateClassic(self->b, angle);
    o->own = true;
    return po;
  }
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* Bitmap_rotateEx(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    double angle, x_shift, y_shift, x_origin, y_origin;
    PyObject *useMask;
    if (!PyArg_ParseTuple(args, "dddddO", &angle, &x_shift, &y_shift, &x_origin, &y_origin, &useMask)) {
      return NULL;
    }
    if (!PyBool_Check(useMask)) {
      PyErr_SetString(PyExc_TypeError, "Expected boolean as 6th argument");
      return NULL;
    }
    PyObject *po = PyObject_CallObject((PyObject*)&FIBITMAPType, NULL);
    FIBITMAPObject *o = (FIBITMAPObject*) po;
    o->b = FreeImage_RotateEx(self->b, angle, x_shift, y_shift, x_origin, y_origin, (useMask == Py_True));
    o->own = true;
    return po;
  }
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* Bitmap_flipH(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    if (FreeImage_FlipHorizontal(self->b)) {
      Py_INCREF(Py_True);
      return Py_True;
    }
  }
  Py_INCREF(Py_False);
  return Py_False;
}

PyObject* Bitmap_flipV(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    if (FreeImage_FlipVertical(self->b)) {
      Py_INCREF(Py_True);
      return Py_True;
    }
  }
  Py_INCREF(Py_False);
  return Py_False;
}

PyObject* Bitmap_rescale(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    int dstw, dsth, filter;
    if (!PyArg_ParseTuple(args, "iii", &dstw, &dsth, &filter)) {
      return NULL;
    }
    FIBITMAP *si = FreeImage_Rescale(self->b, dstw, dsth, (FREE_IMAGE_FILTER)filter);
    if (si) {
      PyObject *po = PyObject_CallObject((PyObject*)&FIBITMAPType, NULL);
      FIBITMAPObject *o = (FIBITMAPObject*) po;
      o->b = si;
      o->own = true;
      return po;
    }
  }
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* Bitmap_makeThumbnail(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    int maxPixSize;
    bool convert = true;
    PyObject *pconvert;
    if (!PyArg_ParseTuple(args, "i|O", &maxPixSize, &pconvert)) {
      return NULL;
    }
    if (pconvert) {
      if (!PyBool_Check(pconvert)) {
        PyErr_SetString(PyExc_TypeError, "Expected boolean as second argument");
        return NULL;
      }
      convert = (pconvert == Py_True);
    }
    PyObject *po = PyObject_CallObject((PyObject*)&FIBITMAPType, NULL);
    FIBITMAPObject *o = (FIBITMAPObject*) po;
    o->b = FreeImage_MakeThumbnail(self->b, maxPixSize, convert);;
    o->own = true;
    return po;
  }
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* Bitmap_copy(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    int left, top, right, bottom;
    if (!PyArg_ParseTuple(args, "iiii", &left, &top, &right, &bottom)) {
      return NULL;
    }
    FIBITMAP *bc = FreeImage_Copy(self->b, left, top, right, bottom);
    if (bc) {
      PyObject *po = PyObject_CallObject((PyObject*)&FIBITMAPType, NULL);
      FIBITMAPObject *o = (FIBITMAPObject*) po;
      o->b = bc;
      o->own = true;
      return po;
    }
  }
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* Bitmap_paste(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    PyObject *psrc;
    int left, top, alpha;
    if (!PyArg_ParseTuple(args, "Oiii", &psrc, &left, &top, &alpha)) {
      return NULL;
    }
    if (!PyObject_TypeCheck(psrc, &FIBITMAPType)) {
      PyErr_SetString(PyExc_TypeError, "expected a fipy.Bitmap as second argument");
      return NULL;
    }
    FIBITMAPObject *src = (FIBITMAPObject*) psrc;
    if (FreeImage_Paste(self->b, src->b, left, top, alpha)) {
      Py_INCREF(Py_True);
      return Py_True;
    }
    
  }
  Py_INCREF(Py_False);
  return Py_False;
}

PyObject* Bitmap_preMultAlpha(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    if (FreeImage_PreMultiplyWithAlpha(self->b)) {
      Py_INCREF(Py_True);
      return Py_True;
    }
  }
  Py_INCREF(Py_False);
  return Py_False;
}

PyObject* Bitmap_poissonSolver(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    int cycle = 3;
    if (!PyArg_ParseTuple(args, "|i", &cycle)) {
      return NULL;
    }
    PyObject *po = PyObject_CallObject((PyObject*)&FIBITMAPType, NULL);
    FIBITMAPObject *o = (FIBITMAPObject*) po;
    o->b = FreeImage_MultigridPoissonSolver(self->b, 3);
    o->own = true;
    return po;
  }
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* Bitmap_getChannel(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    int chan;
    if (!PyArg_ParseTuple(args, "i", &chan)) {
      return NULL;
    }
    FIBITMAP *cb = FreeImage_GetChannel(self->b, (FREE_IMAGE_COLOR_CHANNEL)chan);
    if (cb) {
      PyObject *po = PyObject_CallObject((PyObject*)&FIBITMAPType, NULL);
      FIBITMAPObject *o = (FIBITMAPObject*) po;
      o->b = cb;
      o->own = true;
      return po;
    }
  }
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* Bitmap_getComplexChannel(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    int chan;
    if (!PyArg_ParseTuple(args, "i", &chan)) {
      return NULL;
    }
    FIBITMAP *cb = FreeImage_GetComplexChannel(self->b, (FREE_IMAGE_COLOR_CHANNEL)chan);
    if (cb) {
      PyObject *po = PyObject_CallObject((PyObject*)&FIBITMAPType, NULL);
      FIBITMAPObject *o = (FIBITMAPObject*) po;
      o->b = cb;
      o->own = true;
      return po;
    }
  }
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* Bitmap_setChannel(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    PyObject *po;
    int chan;
    if (!PyArg_ParseTuple(args, "Oi", &po, &chan)) {
      return NULL;
    }
    if (!PyObject_TypeCheck(po, &FIBITMAPType)) {
      PyErr_SetString(PyExc_TypeError, "expected a fipy.Bitmap as second argument");
      return NULL;
    }
    FIBITMAPObject *o = (FIBITMAPObject*) po;
    if (FreeImage_SetChannel(self->b, o->b, (FREE_IMAGE_COLOR_CHANNEL)chan)) {
      Py_INCREF(Py_True);
      return Py_True;
    }
  }
  Py_INCREF(Py_False);
  return Py_False;
}

PyObject* Bitmap_setComplexChannel(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    PyObject *po;
    int chan;
    if (!PyArg_ParseTuple(args, "Oi", &po, &chan)) {
      return NULL;
    }
    if (!PyObject_TypeCheck(po, &FIBITMAPType)) {
      PyErr_SetString(PyExc_TypeError, "expected a fipy.Bitmap as second argument");
      return NULL;
    }
    FIBITMAPObject *o = (FIBITMAPObject*) po;
    if (FreeImage_SetComplexChannel(self->b, o->b, (FREE_IMAGE_COLOR_CHANNEL)chan)) {
      Py_INCREF(Py_True);
      return Py_True;
    }
  }
  Py_INCREF(Py_False);
  return Py_False;
}

PyObject* Bitmap_composite(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    bool useFileBg = false;
    RGBQUAD *appBg = NULL;
    FIBITMAP *imgBg = NULL;
    RGBQUAD tmp;
    PyObject *pUseFileBg = 0;
    PyObject *pAppBg = 0;
    PyObject *pImgBg = 0;
    if (!PyArg_ParseTuple(args, "|OOO", &pUseFileBg, &pAppBg, &pImgBg)) {
      return NULL;
    }
    if (pUseFileBg) {
      if (!PyBool_Check(pUseFileBg)) {
        PyErr_SetString(PyExc_TypeError, "Expected boolean as first argument");
        return NULL;
      }
      useFileBg = (pUseFileBg == Py_True);
    }
    if (pAppBg) {
      if (!PyTuple_Check(pAppBg) || PyTuple_Size(pAppBg) != 3) {
        PyErr_SetString(PyExc_TypeError, "Expected a rgb tuple as second argument");
        return NULL;
      }
      PyArg_ParseTuple(pAppBg, "BBB", &(tmp.rgbRed), &(tmp.rgbGreen), &(tmp.rgbBlue));
      appBg = &tmp;
    }
    if (pImgBg) {
      if (!PyObject_TypeCheck(pImgBg, &FIBITMAPType)) {
        PyErr_SetString(PyExc_TypeError, "Expected a fipy.Bitmap as third argument");
        return NULL;
      }
      imgBg = ((FIBITMAPObject*)pImgBg)->b;
    }
    FIBITMAP *cb = FreeImage_Composite(self->b, useFileBg, appBg, imgBg);
    if (cb) {
      PyObject *po = PyObject_CallObject((PyObject*)&FIBITMAPType, NULL);
      FIBITMAPObject *o = (FIBITMAPObject*) po;
      o->b = cb;
      o->own = true;
      return po;
    }
  }
  Py_INCREF(Py_None);
  return Py_None;
}

// TODO: FreeImage_AdjustCurve
// TODO: FreeImage_GetHistogram
// TODO: FreeImage_GetAdjustColorsLookupTable
// TODO: FreeImage_ApplyColorMapping
// TODO: FreeImage_SwapColors
// TODO: FreeImage_ApplyPaletteIndexMapping
// TODO: FreeImage_SwapPaletteIndices

PyObject* Bitmap_adjustGamma(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    double gamma;
    if (!PyArg_ParseTuple(args, "d", &gamma)) {
      return NULL;
    }
    if (FreeImage_AdjustGamma(self->b, gamma)) {
      Py_INCREF(Py_True);
      return Py_True;
    }
  }
  Py_INCREF(Py_False);
  return Py_False;
}

PyObject* Bitmap_adjustBrightness(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    double bright;
    if (!PyArg_ParseTuple(args, "d", &bright)) {
      return NULL;
    }
    if (FreeImage_AdjustBrightness(self->b, bright)) {
      Py_INCREF(Py_True);
      return Py_True;
    }
  }
  Py_INCREF(Py_False);
  return Py_False;
}

PyObject* Bitmap_adjustContrast(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    double cont;
    if (!PyArg_ParseTuple(args, "d", &cont)) {
      return NULL;
    }
    if (FreeImage_AdjustContrast(self->b, cont)) {
      Py_INCREF(Py_True);
      return Py_True;
    }
  }
  Py_INCREF(Py_False);
  return Py_False;
}

PyObject* Bitmap_adjustColors(PyObject *pself, PyObject *args) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    double bright, cont, gamma;
    bool inv = false;
    PyObject *pinv = 0;
    if (!PyArg_ParseTuple(args, "ddd|O", &bright, &cont, &gamma, &pinv)) {
      return NULL;
    }
    if (pinv) {
      if (!PyBool_Check(pinv)) {
        PyErr_SetString(PyExc_TypeError, "Expected a boolean as 4th argument");
        return NULL;
      }
      inv = (pinv == Py_True);
    }
    if (FreeImage_AdjustColors(self->b, bright, cont, gamma, inv)) {
      Py_INCREF(Py_True);
      return Py_True;
    }
  }
  Py_INCREF(Py_False);
  return Py_False;
}

PyObject* Bitmap_invert(PyObject *pself) {
  FIBITMAPObject *self = (FIBITMAPObject*) pself;
  if (self->b) {
    if (FreeImage_Invert(self->b)) {
      Py_INCREF(Py_True);
      return Py_True;
    }
  }
  Py_INCREF(Py_False);
  return Py_False;
}


static PyMethodDef Bitmap_methods[] = {
  {"Allocate", Bitmap_allocate, METH_VARARGS, "Allocate a new image"},
  {"AllocateT", Bitmap_allocateT, METH_VARARGS, "Allocate a new image of a given type"},
  {"Load", Bitmap_load, METH_VARARGS, "Load image from file"},
  {"LoadU", Bitmap_loadU, METH_VARARGS, "Load image from file (unicode filename)"},
  {"Save", Bitmap_save, METH_VARARGS, "Save image to file"},
  {"SaveU", Bitmap_saveU, METH_VARARGS, "Save image to file (unicode filename)"},
  {"Clone", (PyCFunction)Bitmap_clone, METH_NOARGS, "Clone image"},
  {"Unload", (PyCFunction)Bitmap_unload, METH_NOARGS, "Unload image"},
  {"GetImageType", (PyCFunction)Bitmap_getImageType, METH_NOARGS, ""},
  {"GetColorsUsed", (PyCFunction)Bitmap_getColorsUsed, METH_NOARGS, ""},
  {"GetBPP", (PyCFunction)Bitmap_getBPP, METH_NOARGS, ""},
  {"GetWidth", (PyCFunction)Bitmap_getWidth, METH_NOARGS, ""},
  {"GetHeight", (PyCFunction)Bitmap_getHeight, METH_NOARGS, ""},
  {"GetLine", (PyCFunction)Bitmap_getLine, METH_NOARGS, ""},
  {"GetPitch", (PyCFunction)Bitmap_getPitch, METH_NOARGS, ""},
  {"GetDIBSize", (PyCFunction)Bitmap_getDIBSize, METH_NOARGS, ""},
  {"GetPalette", (PyCFunction)Bitmap_getPalette, METH_NOARGS, ""},
  {"GetDotsPerMeterX", (PyCFunction)Bitmap_getDotsPerMeterX, METH_NOARGS, ""},
  {"GetDotsPerMeterY", (PyCFunction)Bitmap_getDotsPerMeterY, METH_NOARGS, ""},
  {"SetDotsPerMeterX", Bitmap_setDotsPerMeterX, METH_VARARGS, ""},
  {"SetDotsPerMeterY", Bitmap_setDotsPerMeterY, METH_VARARGS, ""},
  {"GetInfoHeader", (PyCFunction)Bitmap_getInfoHeader, METH_NOARGS, ""},
  {"GetInfo", (PyCFunction)Bitmap_getInfo, METH_NOARGS, ""},
  {"GetColorType", (PyCFunction)Bitmap_getColorType, METH_NOARGS, ""},
  {"GetRedMask", (PyCFunction)Bitmap_getRedMask, METH_NOARGS, ""},
  {"GetGreenMask", (PyCFunction)Bitmap_getGreenMask, METH_NOARGS, ""},
  {"GetBlueMask", (PyCFunction)Bitmap_getBlueMask, METH_NOARGS, ""},
  {"GetTransparencyCount", (PyCFunction)Bitmap_getTransparencyCount, METH_NOARGS, ""},
  {"GetTransparencyTable", (PyCFunction)Bitmap_getTransparencyTable, METH_NOARGS, ""},
  {"SetTransparencyTable", Bitmap_setTransparencyTable, METH_VARARGS, ""},
  {"SetTransparent", Bitmap_setTransparent, METH_VARARGS, ""},
  {"IsTransparent", (PyCFunction)Bitmap_isTransparent, METH_NOARGS, ""},
  {"SetTransparentIndex", Bitmap_setTransparentIndex, METH_VARARGS, ""},
  {"GetTransparentIndex", (PyCFunction)Bitmap_getTransparentIndex, METH_NOARGS, ""},
  {"HasBackgroundColor", (PyCFunction)Bitmap_hasBackgroundColor, METH_NOARGS, ""},
  {"GetBackgroundColor", (PyCFunction)Bitmap_getBackgroundColor, METH_NOARGS, ""},
  {"SetBackgroundColor", Bitmap_setBackgroundColor, METH_VARARGS, ""},
  {"SetPixelColor", Bitmap_setPixelColor, METH_VARARGS, ""},
  {"GetPixelColor", Bitmap_getPixelColor, METH_VARARGS, ""},
  {"SetPixelIndex", Bitmap_setPixelIndex, METH_VARARGS, ""},
  {"GetPixelIndex", Bitmap_getPixelIndex, METH_VARARGS, ""},
  {"ConvertTo4Bits", (PyCFunction)Bitmap_convertTo4Bits, METH_NOARGS, ""},
  {"ConvertTo8Bits", (PyCFunction)Bitmap_convertTo8Bits, METH_NOARGS, ""},
  {"ConvertToGreyscale", (PyCFunction)Bitmap_convertToGreyscale, METH_NOARGS, ""},
  {"ConvertTo16Bits555", (PyCFunction)Bitmap_convertTo16Bits555, METH_NOARGS, ""},
  {"ConvertTo16Bits565", (PyCFunction)Bitmap_convertTo16Bits565, METH_NOARGS, ""},
  {"ConvertTo24Bits", (PyCFunction)Bitmap_convertTo24Bits, METH_NOARGS, ""},
  {"ConvertTo32Bits", (PyCFunction)Bitmap_convertTo32Bits, METH_NOARGS, ""},
  {"ConvertToStandardType", Bitmap_convertToStandardType, METH_VARARGS, ""},
  {"ConvertToType", Bitmap_convertToType, METH_VARARGS, ""},
  {"ConvertToRGBF", (PyCFunction)Bitmap_convertToRGBF, METH_NOARGS, ""},
  {"ColorQuantize", Bitmap_colorQuantize, METH_VARARGS, ""},
  {"ColorQuantizeEx", Bitmap_colorQuantize, METH_VARARGS, ""},
  {"Threshold", Bitmap_threshold, METH_VARARGS, ""},
  {"Dither", Bitmap_dither, METH_VARARGS, ""},
  {"ToneMapping", Bitmap_toneMapping, METH_VARARGS, ""},
  {"TmoReinhard05", Bitmap_tmoReinhard05, METH_VARARGS, ""},
  {"TmoFattal02", Bitmap_tmoFattal02, METH_VARARGS, ""},
  {"TmoDrago03", Bitmap_tmoDrago03, METH_VARARGS, ""},
  {"GetICCProfile", (PyCFunction)Bitmap_getICCProfile, METH_NOARGS, ""},
  {"DestroyICCProfile", (PyCFunction)Bitmap_destroyICCProfile, METH_NOARGS, ""},
  {"GetMetadataCount", Bitmap_getMetaCount, METH_VARARGS, ""},
  {"GetMetadata", Bitmap_getMeta, METH_VARARGS, ""},
  {"SetMetadata", Bitmap_setMeta, METH_VARARGS, ""},
  {"RotateClassic", Bitmap_rotateClassic, METH_VARARGS, ""},
  {"RotateEx", Bitmap_rotateEx, METH_VARARGS, ""},
  {"FlipHorizontal", (PyCFunction)Bitmap_flipH, METH_NOARGS, ""},
  {"FlipVertical", (PyCFunction)Bitmap_flipV, METH_NOARGS, ""},
  {"Rescale", Bitmap_rescale, METH_VARARGS, ""},
  {"MakeThumbnail", Bitmap_makeThumbnail, METH_VARARGS, ""},
  {"Copy", Bitmap_copy, METH_VARARGS, ""},
  {"Paste", Bitmap_paste, METH_VARARGS, ""},
  {"PreMultiplyWithAlpha", (PyCFunction)Bitmap_preMultAlpha, METH_NOARGS, ""},
  {"MultigridPoissonSolver", Bitmap_poissonSolver, METH_VARARGS, ""},
  {"GetChannel", Bitmap_getChannel, METH_VARARGS, ""},
  {"GetComplexChannel", Bitmap_getComplexChannel, METH_VARARGS, ""},
  {"SetChannel", Bitmap_setChannel, METH_VARARGS, ""},
  {"SetComplexChannel", Bitmap_setComplexChannel, METH_VARARGS, ""},
  {"Composite", Bitmap_composite, METH_VARARGS, ""},
  {"AdjustGamma", Bitmap_adjustGamma, METH_VARARGS, ""},
  {"AdjustBrightness", Bitmap_adjustBrightness, METH_VARARGS, ""},
  {"AdjustContrast", Bitmap_adjustContrast, METH_VARARGS, ""},
  {"AdjustColors", Bitmap_adjustColors, METH_VARARGS, ""},
  {"Invert", (PyCFunction)Bitmap_invert, METH_NOARGS, ""},
  {"GetBits", (PyCFunction)Bitmap_getBits, METH_NOARGS, ""},
#if FREEIMAGE_MINOR_VERSION >= 12
  {"CloneMetadata", Bitmap_cloneMeta, METH_VARARGS, ""},
#endif
  {NULL, NULL, 0, NULL}
};

bool InitBitmap(PyObject *module) {
  
  FIBITMAPType.tp_flags = Py_TPFLAGS_DEFAULT;
  FIBITMAPType.tp_doc = "FreeImage Bitmap Object";
  FIBITMAPType.tp_new = Bitmap_new;
  FIBITMAPType.tp_dealloc = Bitmap_dealloc;
  FIBITMAPType.tp_init = Bitmap_init;
  FIBITMAPType.tp_methods = Bitmap_methods;
  
  if (PyType_Ready(&FIBITMAPType) < 0) {
    return false;
  }
  
  Py_INCREF(&FIBITMAPType);
  PyModule_AddObject(module, "Bitmap", (PyObject*)&FIBITMAPType);
  
  return true;
}

// ---

// MULTIBITMAP
PyTypeObject FIMULTIBITMAPType = {
  PyObject_HEAD_INIT(NULL)
  0,
  "fipy.MultiBitmap",
  sizeof(FIMULTIBITMAPObject),
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

PyObject* MultiBitmap_new(PyTypeObject *type, PyObject *, PyObject *) {
  FIMULTIBITMAPObject *self = (FIMULTIBITMAPObject*) type->tp_alloc(type, 0);
  self->own = true;
  self->mb = 0;
  return (PyObject*)self;
}

void MultiBitmap_dealloc(PyObject *pself) {
  FIMULTIBITMAPObject *self = (FIMULTIBITMAPObject*)pself;
  if (self->own && self->mb) {
    FreeImage_CloseMultiBitmap(self->mb);
    self->mb = 0;
  }
}

int MultiBitmap_init(PyObject *, PyObject *, PyObject *) {
  // support allocate and load
  return 0;
}

PyObject* MultiBitmap_open(PyObject *pself, PyObject *args) {
  FIMULTIBITMAPObject *self = (FIMULTIBITMAPObject*)pself;
  
  Py_ssize_t nargs = PyTuple_Size(args);
  
  if (nargs < 4 || nargs > 6) {
    PyErr_SetString(PyExc_RuntimeError, "Expected at least 4 arguments, at most 6");
    return NULL;
  }
  
  int fif;
  char *filename;
  bool create;
  bool readOnly;
  bool keepCache=false;
  int flags=0;
  
  PyObject *obj;
  
  obj = PyTuple_GetItem(args, 0);
  if (!PyInt_Check(obj)) {
    PyErr_SetString(PyExc_TypeError, "Expected int as first argument");
    return NULL;
  }
  fif = PyInt_AsLong(obj);
  
  obj = PyTuple_GetItem(args, 1);
  if (!PyString_Check(obj)) {
    PyErr_SetString(PyExc_TypeError, "Expected string as second argument");
    return NULL;
  }
  filename = PyString_AsString(obj);
  
  obj = PyTuple_GetItem(args, 2);
  if (!PyBool_Check(obj)) {
    PyErr_SetString(PyExc_TypeError, "Expected bool as third argument");
    return NULL;
  }
  create = (obj == Py_True);
  
  obj = PyTuple_GetItem(args, 3);
  if (!PyBool_Check(obj)) {
    PyErr_SetString(PyExc_TypeError, "Expected bool as 4th argument");
    return NULL;
  }
  readOnly = (obj == Py_True);
  
  if (nargs >= 5) {
    obj = PyTuple_GetItem(args, 4);
    if (!PyBool_Check(obj)) {
      PyErr_SetString(PyExc_TypeError, "Expected bool as 5th argument");
      return NULL;
    }
    keepCache = (obj == Py_True);
  }
  
  if (nargs >= 6) {
    obj = PyTuple_GetItem(args, 5);
    if (!PyInt_Check(obj)) {
      PyErr_SetString(PyExc_TypeError, "Expected int as 6th argument");
      return NULL;
    }
    flags = PyInt_AsLong(obj);
  }
  
  if (self->own && self->mb) {
    FreeImage_CloseMultiBitmap(self->mb);
  }
  
  self->own = true;
  self->mb = FreeImage_OpenMultiBitmap((FREE_IMAGE_FORMAT)fif, filename, create, readOnly, keepCache, flags);
  
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* MultiBitmap_close(PyObject *pself, PyObject *args) {
  FIMULTIBITMAPObject *self = (FIMULTIBITMAPObject*)pself;
  int flags=0;
  if (!PyArg_ParseTuple(args, "|i", &flags)) {
    return NULL;
  }
  if (!(self->mb)) {
    Py_INCREF(Py_True);
    return Py_True;
  }
  BOOL ret = FreeImage_CloseMultiBitmap(self->mb, flags);
  self->mb = 0;
  if (ret) {
    Py_INCREF(Py_True);
    return Py_True;
  } else {
    Py_INCREF(Py_False);
    return Py_False;
  }
}

PyObject* MultiBitmap_getPageCount(PyObject *pself) {
  FIMULTIBITMAPObject *self = (FIMULTIBITMAPObject*)pself;
  if (self->mb) {
    return PyInt_FromLong(FreeImage_GetPageCount(self->mb));
  } else {
    return PyInt_FromLong(0);
  }
}

PyObject* MultiBitmap_appendPage(PyObject *pself, PyObject *args) {
  FIMULTIBITMAPObject *self = (FIMULTIBITMAPObject*)pself;
  if (self->mb) {
    PyObject *obj;
    if (!PyArg_ParseTuple(args, "O", &obj)) {
      return NULL;
    }
    if (!PyObject_TypeCheck(obj, &FIBITMAPType)) {
      PyErr_SetString(PyExc_TypeError, "Expected a fipy.Bitmap object");
      return NULL;
    }
    FIBITMAPObject *bo = (FIBITMAPObject*) obj;
    FreeImage_AppendPage(self->mb, bo->b);
  }
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* MultiBitmap_insertPage(PyObject *pself, PyObject *args) {
  FIMULTIBITMAPObject *self = (FIMULTIBITMAPObject*)pself;
  if (self->mb) {
    int page;
    PyObject *obj;
    if (!PyArg_ParseTuple(args, "iO", &page, &obj)) {
      return NULL;
    }
    if (!PyObject_TypeCheck(obj, &FIBITMAPType)) {
      PyErr_SetString(PyExc_TypeError, "Expected a fipy.Bitmap object");
      return NULL;
    }
    FIBITMAPObject *bo = (FIBITMAPObject*) obj;
    FreeImage_InsertPage(self->mb, page, bo->b);
  }
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* MultiBitmap_deletePage(PyObject *pself, PyObject *args) {
  FIMULTIBITMAPObject *self = (FIMULTIBITMAPObject*)pself;
  if (self->mb) {
    int page;
    if (!PyArg_ParseTuple(args, "i", &page)) {
      return NULL;
    }
    FreeImage_DeletePage(self->mb, page);
  }
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* MultiBitmap_lockPage(PyObject *pself, PyObject *args) {
  FIMULTIBITMAPObject *self = (FIMULTIBITMAPObject*)pself;
  if (self->mb) {
    int page;
    if (!PyArg_ParseTuple(args, "i", &page)) {
      return NULL;
    }
    PyObject *obj = PyObject_CallObject((PyObject*)&FIBITMAPType, NULL);
    FIBITMAPObject *bo = (FIBITMAPObject*) obj;
    bo->own = false;
    bo->b = FreeImage_LockPage(self->mb, page);
    return obj;
  }
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* MultiBitmap_unlockPage(PyObject *pself, PyObject *args) {
  FIMULTIBITMAPObject *self = (FIMULTIBITMAPObject*)pself;
  if (self->mb) {
    PyObject *bmp, *change;
    if (!PyArg_ParseTuple(args, "OO", &bmp, &change)) {
      return NULL;
    }
    if (!PyObject_TypeCheck(bmp, &FIBITMAPType)) {
      PyErr_SetString(PyExc_TypeError, "Expected a fipy.Bitmap as first argument");
      return NULL;
    }
    if (!PyBool_Check(change)) {
      PyErr_SetString(PyExc_TypeError, "Expected a boolean as second argument");
      return NULL;
    }
    FIBITMAPObject *bo = (FIBITMAPObject*) bmp;
    FreeImage_UnlockPage(self->mb, bo->b, (change == Py_True));
  }
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* MultiBitmap_movePage(PyObject *pself, PyObject *args) {
  FIMULTIBITMAPObject *self = (FIMULTIBITMAPObject*)pself;
  if (self->mb) {
    int target, source;
    if (!PyArg_ParseTuple(args, "ii", &target, &source)) {
      return NULL;
    }
    FreeImage_MovePage(self->mb, target, source);
  }
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* MultiBitmap_getLockedPageNumbers(PyObject *pself) {
  FIMULTIBITMAPObject *self = (FIMULTIBITMAPObject*)pself;
  PyObject *lst = 0;
  if (self->mb) {
    int count;
    FreeImage_GetLockedPageNumbers(self->mb, NULL, &count);
    int *pages = new int[count];
    FreeImage_GetLockedPageNumbers(self->mb, pages, &count);
    lst = PyList_New(count);
    for (int i=0; i<count; ++i) {
      PyList_SetItem(lst, i, PyInt_FromLong(pages[i]));
    }
  } else {
    lst = PyList_New(0);
  }
  return lst;
}

static PyMethodDef MultiBitmap_methods[] = {
  {"Open", MultiBitmap_open, METH_VARARGS, ""},
  {"Close", MultiBitmap_close, METH_VARARGS, ""},
  {"GetPageCount", (PyCFunction)MultiBitmap_getPageCount, METH_NOARGS, ""},
  {"AppendPage", MultiBitmap_appendPage, METH_VARARGS, ""},
  {"InsertPage", MultiBitmap_insertPage, METH_VARARGS, ""},
  {"DeletePage", MultiBitmap_deletePage, METH_VARARGS, ""},
  {"LockPage", MultiBitmap_lockPage, METH_VARARGS, ""},
  {"UnlockPage", MultiBitmap_unlockPage, METH_VARARGS, ""},
  {"MovePage", MultiBitmap_movePage, METH_VARARGS, ""},
  {"GetLockedPageNumbers", (PyCFunction)MultiBitmap_getLockedPageNumbers, METH_NOARGS, ""},
  {NULL, NULL, 0, NULL}
};

bool InitMultiBitmap(PyObject *module) {
  
  FIMULTIBITMAPType.tp_flags = Py_TPFLAGS_DEFAULT;
  FIMULTIBITMAPType.tp_doc = "FreeImage Multi Bitmap Object";
  FIMULTIBITMAPType.tp_new = MultiBitmap_new;
  FIMULTIBITMAPType.tp_dealloc = MultiBitmap_dealloc;
  FIMULTIBITMAPType.tp_init = MultiBitmap_init;
  FIMULTIBITMAPType.tp_methods = MultiBitmap_methods;
  
  if (PyType_Ready(&FIMULTIBITMAPType) < 0) {
    return false;
  }
  
  Py_INCREF(&FIMULTIBITMAPType);
  PyModule_AddObject(module, "MultiBitmap", (PyObject*)&FIMULTIBITMAPType);
  
  return true;
}

