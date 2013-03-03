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

PyTypeObject FITAGType = {
  PyObject_HEAD_INIT(NULL)
  0,
  "fipy.Tag",
  sizeof(FITAGObject),
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

PyObject* Tag_new(PyTypeObject *type, PyObject *, PyObject *) {
  PyObject *po = type->tp_alloc(type, 0);
  FITAGObject *o = (FITAGObject*) po;
  o->t = FreeImage_CreateTag();
  o->own = true;
  return po;
}

int Tag_init(PyObject *, PyObject *, PyObject *) {
  return 0;
}

void Tag_dealloc(PyObject *pself) {
  FITAGObject *self = (FITAGObject*) pself;
  if (self->own && self->t) {
    FreeImage_DeleteTag(self->t);
    self->t = 0;
  }
}

PyObject* Tag_clone(PyObject *pself) {
  FITAGObject *self = (FITAGObject*) pself;
  if (self->t) {
    PyObject *po = PyObject_CallObject((PyObject*)&FITAGType, NULL);
    FITAGObject *o = (FITAGObject*) po;
    o->t = FreeImage_CloneTag(self->t);
    return po;
  } else {
    Py_INCREF(Py_None);
    return Py_None;
  }
}

PyObject* Tag_getKey(PyObject *pself, void*) {
  FITAGObject *self = (FITAGObject*) pself;
  if (self->t) {
    return PyString_FromString(FreeImage_GetTagKey(self->t));
  }
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* Tag_getDesc(PyObject *pself, void*) {
  FITAGObject *self = (FITAGObject*) pself;
  if (self->t) {
    return PyString_FromString(FreeImage_GetTagDescription(self->t));
  }
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* Tag_getID(PyObject *pself, void*) {
  FITAGObject *self = (FITAGObject*) pself;
  if (self->t) {
    return PyInt_FromLong(FreeImage_GetTagID(self->t));
  }
  return PyInt_FromLong(0);
}

PyObject* Tag_getType(PyObject *pself, void*) {
  FITAGObject *self = (FITAGObject*) pself;
  if (self->t) {
    return PyInt_FromLong(FreeImage_GetTagType(self->t));
  }
  return PyInt_FromLong(-1);
}

PyObject* Tag_getCount(PyObject *pself, void*) {
  FITAGObject *self = (FITAGObject*) pself;
  if (self->t) {
    return PyInt_FromLong(FreeImage_GetTagCount(self->t));
  }
  return PyInt_FromLong(0);
}

/*
PyObject* Tag_getLength(PyObject *pself, void*) {
  FITAGObject *self = (FITAGObject*) pself;
  if (self->t) {
    return PyInt_FromLong(FreeImage_GetTagLength(self->t));
  }
  return PyInt_FromLong(0);
}
*/

PyObject* Tag_getValue(PyObject *pself, void*) {
  FITAGObject *self = (FITAGObject*) pself;
  
  if (self->t) {
    
    const void *val = FreeImage_GetTagValue(self->t);
    
    FREE_IMAGE_MDTYPE typ = FreeImage_GetTagType(self->t);
    
    unsigned long cnt = FreeImage_GetTagCount(self->t);
    
    if (cnt == 0) {
      Py_INCREF(Py_None);
      return Py_None;
    }
    
    if (typ == FIDT_NOTYPE) {
      Py_INCREF(Py_None);
      return Py_None;
    
    } else if (typ == FIDT_BYTE) {
      BYTE *data = (BYTE*)val;
      if (cnt > 1) {
        PyObject *lst = PyList_New(cnt);
        for (unsigned long i=0; i<cnt; ++i) {
          PyList_SetItem(lst, i, PyInt_FromLong(data[i]));
        }
        return lst;
        
      } else {
        return PyInt_FromLong(data[0]);
      }
      
    } else if (typ == FIDT_ASCII) {
      char *data = (char*)val;
      if (cnt > 1) {
        PyObject *lst = PyList_New(cnt);
        for (unsigned long i=0; i<cnt; ++i) {
          PyList_SetItem(lst, i, PyString_FromString(data));
          char *end = strchr(data, '\0');
          if (!end) {
            // it was the last string
            if ((i + 1) != cnt) {
              PyErr_SetString(PyExc_RuntimeError, "String count does not match");
              Py_DECREF(lst);
              return NULL;
            }
          } else {
            data = end + 1;
          }
        }
        return lst;
        
      } else {
        return PyString_FromString(data);
      }
      
    } else if (typ == FIDT_SHORT) {
      WORD *data = (WORD*)val;
      if (cnt > 1) {
        PyObject *lst = PyList_New(cnt);
        for (unsigned long i=0; i<cnt; ++i) {
          PyList_SetItem(lst, i, PyInt_FromLong(data[i]));
        }
        return lst;
        
      } else {
        return PyInt_FromLong(data[0]);
      }
      
    } else if (typ == FIDT_LONG || typ == FIDT_IFD) {
      DWORD *data = (DWORD*)val;
      if (cnt > 1) {
        PyObject *lst = PyList_New(cnt);
        for (unsigned long i=0; i<cnt; ++i) {
          PyList_SetItem(lst, i, PyInt_FromLong(data[i]));
        }
        return lst;
        
      } else {
        return PyInt_FromLong(data[0]);
      }
      
    } else if (typ == FIDT_RATIONAL) {
      DWORD *data = (DWORD*)val;
      if (cnt > 1) {
        PyObject *lst = PyList_New(cnt);
        for (unsigned long i=0, j=0; i<cnt; ++i, j+=2) {
          PyList_SetItem(lst, i, Py_BuildValue("kk", data[j], data[j+1]));
        }
        return lst;
        
      } else {
        return Py_BuildValue("kk", data[0], data[1]);
      }
      
    } else if (typ == FIDT_UNDEFINED) {
      unsigned char *data = (unsigned char*)val;
      if (cnt > 1) {
        PyObject *lst = PyList_New(cnt);
        for (unsigned long i=0; i<cnt; ++i) {
          PyList_SetItem(lst, i, PyInt_FromLong(data[i]));
        }
        return lst;
        
      } else {
        return PyInt_FromLong(data[0]);
      }
      
    } else if (typ == FIDT_SBYTE) {
      char *data = (char*)val;
      if (cnt > 1) {
        PyObject *lst = PyList_New(cnt);
        for (unsigned long i=0; i<cnt; ++i) {
          PyList_SetItem(lst, i, PyInt_FromLong(data[i]));
        }
        return lst;
        
      } else {
        return PyInt_FromLong(data[0]);
      }
      
    } else if (typ == FIDT_SSHORT) {
      short *data = (short*)val;
      if (cnt > 1) {
        PyObject *lst = PyList_New(cnt);
        for (unsigned long i=0; i<cnt; ++i) {
          PyList_SetItem(lst, i, PyInt_FromLong(data[i]));
        }
        return lst;
        
      } else {
        return PyInt_FromLong(data[0]);
      }
      
    } else if (typ == FIDT_SLONG) {
      LONG *data = (LONG*)val;
      if (cnt > 1) {
        PyObject *lst = PyList_New(cnt);
        for (unsigned long i=0; i<cnt; ++i) {
          PyList_SetItem(lst, i, PyInt_FromLong(data[i]));
        }
        return lst;
        
      } else {
        return PyInt_FromLong(data[0]);
      }
      
    } else if (typ == FIDT_SRATIONAL) {
      LONG *data = (LONG*)val;
      if (cnt > 1) {
        PyObject *lst = PyList_New(cnt);
        for (unsigned long i=0, j=0; i<cnt; ++i, j+=2) {
          PyList_SetItem(lst, i, Py_BuildValue("ll", data[j], data[j+1]));
        }
        return lst;
        
      } else {
        return Py_BuildValue("ll", data[0], data[1]);
      }
      
    } else if (typ == FIDT_FLOAT) {
      float *data = (float*)val;
      if (cnt > 1) {
        PyObject *lst = PyList_New(cnt);
        for (unsigned long i=0; i<cnt; ++i) {
          PyList_SetItem(lst, i, PyFloat_FromDouble(data[i]));
        }
        return lst;
        
      } else {
        return PyFloat_FromDouble(data[0]);
      }
      
    } else if (typ == FIDT_DOUBLE) {
      double *data = (double*)val;
      if (cnt > 1) {
        PyObject *lst = PyList_New(cnt);
        for (unsigned long i=0; i<cnt; ++i) {
          PyList_SetItem(lst, i, PyFloat_FromDouble(data[i]));
        }
        return lst;
        
      } else {
        return PyFloat_FromDouble(data[0]);
      }
      
    } else if (typ == FIDT_PALETTE) {
      unsigned char *pal = (unsigned char*)val;
      if (cnt > 1) {
        PyObject *lst = PyList_New(cnt);
        for (unsigned long i=0, j=0; i<cnt; ++i, j+=4) {
          PyList_SetItem(lst, i, Py_BuildValue("BBB", pal[j], pal[j+1], pal[j+2]));
        }
        return lst;
        
      } else {
        return Py_BuildValue("BBB", pal[0], pal[1], pal[2]);
      }
      
    } else {
      Py_INCREF(Py_None);
      return Py_None;
    }
  }
  Py_INCREF(Py_None);
  return Py_None;
}

static int Tag_setKey(PyObject *pself, PyObject *val, void*) {
  FITAGObject *self = (FITAGObject*) pself;
  if (self->t) {
    FreeImage_SetTagKey(self->t, PyString_AsString(val));
  }
  return 0;
}

static int Tag_setDesc(PyObject *pself, PyObject *val, void*) {
  FITAGObject *self = (FITAGObject*) pself;
  if (self->t) {
    FreeImage_SetTagDescription(self->t, PyString_AsString(val));
  }
  return 0;
}

static int Tag_setID(PyObject *pself, PyObject *val, void*) {
  FITAGObject *self = (FITAGObject*) pself;
  if (self->t) {
    FreeImage_SetTagID(self->t, PyInt_AsLong(val));
  }
  return 0;
}

static int Tag_setType(PyObject *pself, PyObject *val, void*) {
  FITAGObject *self = (FITAGObject*) pself;
  if (self->t) {
    FreeImage_SetTagType(self->t, (FREE_IMAGE_MDTYPE) PyInt_AsLong(val));
  }
  return 0;
}

static int Tag_setCount(PyObject *pself, PyObject *val, void*) {
  FITAGObject *self = (FITAGObject*) pself;
  if (self->t) {
    FreeImage_SetTagCount(self->t, PyInt_AsLong(val));
  }
  return 0;
}

/*
static int Tag_setLength(PyObject *pself, PyObject *val, void*) {
  FITAGObject *self = (FITAGObject*) pself;
  if (self->t) {
    FreeImage_SetTagLength(self->t, PyInt_AsLong(val));
  }
  return 0;
}
*/

static int Tag_setValue(PyObject *pself, PyObject *pval, void*) {
  FITAGObject *self = (FITAGObject*) pself;
  
  if (self->t) {
    
    unsigned long cnt = FreeImage_GetTagCount(self->t);
    FREE_IMAGE_MDTYPE typ = FreeImage_GetTagType(self->t);
    
    if (cnt > 0 && typ != FIDT_NOTYPE) {
      
      if (cnt > 1) {
        if (!PyList_Check(pval)) {
          PyErr_SetString(PyExc_RuntimeError, "Expected a list argument");
          return -1;
        }
        if (PyList_Size(pval) != (Py_ssize_t)cnt) {
          PyErr_SetString(PyExc_RuntimeError, "Wrong number of argument in list");
          return -1;
        }
      }
      
      if (typ == FIDT_BYTE) {
        BYTE *val = new BYTE[cnt];
        if (cnt > 1) {
          for (unsigned long i=0; i<cnt; ++i) {
            PyObject *po = PyList_GetItem(pval, i);
            if (!PyInt_Check(po)) {
              PyErr_SetString(PyExc_TypeError, "Expected int elements");
              delete[] val;
              return -1;
            }
            val[i] = (BYTE) (PyInt_AsLong(po) & 0x000000FF);
          }
          
        } else {
          if (!PyInt_Check(pval)) {
            PyErr_SetString(PyExc_TypeError, "Expected int argument");
            delete[] val;
            return -1;
          }
          val[0] = (BYTE) (PyInt_AsLong(pval) & 0x000000FF);
        }
        FreeImage_SetTagLength(self->t, cnt * sizeof(BYTE));
        FreeImage_SetTagValue(self->t, (const void*)val);
        delete[] val;
        
      } else if (typ == FIDT_SHORT) {
        WORD *val = new WORD[cnt];
        if (cnt > 1) {
          for (unsigned long i=0; i<cnt; ++i) {
            PyObject *po = PyList_GetItem(pval, i);
            if (!PyInt_Check(po)) {
              PyErr_SetString(PyExc_TypeError, "Expected int elements");
              delete[] val;
              return -1;
            }
            val[i] = (WORD) (PyInt_AsLong(po) & 0x0000FFFF);
          }
          
        } else {
          if (!PyInt_Check(pval)) {
            PyErr_SetString(PyExc_TypeError, "Expected int argument");
            delete[] val;
            return -1;
          }
          val[0] = (WORD) (PyInt_AsLong(pval) & 0x0000FFFF);
        }
        FreeImage_SetTagLength(self->t, cnt * sizeof(WORD));
        FreeImage_SetTagValue(self->t, (const void*)val);
        delete[] val;
        
      } else if (typ == FIDT_LONG || typ == FIDT_IFD) {
        DWORD *val = new DWORD[cnt];
        if (cnt > 1) {
          for (unsigned long i=0; i<cnt; ++i) {
            PyObject *po = PyList_GetItem(pval, i);
            if (!PyInt_Check(po)) {
              PyErr_SetString(PyExc_TypeError, "Expected int elements");
              delete[] val;
              return -1;
            }
            val[i] = (DWORD) (PyInt_AsLong(po) & 0xFFFFFFFF);
          }
          
        } else {
          if (!PyInt_Check(pval)) {
            PyErr_SetString(PyExc_TypeError, "Expected int argument");
            delete[] val;
            return -1;
          }
          val[0] = (DWORD) (PyInt_AsLong(pval) & 0xFFFFFFFF);
        }
        FreeImage_SetTagLength(self->t, cnt * sizeof(DWORD));
        FreeImage_SetTagValue(self->t, (const void*)val);
        delete[] val;
      
      } else if (typ == FIDT_RATIONAL) {
        DWORD *val = new DWORD[2*cnt];
        if (cnt > 1) {
          for (unsigned long i=0, j=0; i<cnt; ++i, j+=2) {
            PyObject *po = PyList_GetItem(pval, i);
            if (!PyTuple_Check(po) || PyTuple_Size(po) != 2) {
              PyErr_SetString(PyExc_TypeError, "Expected 2 elements tuple elements");
              delete[] val;
              return -1;
            }
            val[j] = (DWORD) (PyInt_AsLong(PyTuple_GetItem(po, 0)) & 0xFFFFFFFF);
            val[j+1] = (DWORD) (PyInt_AsLong(PyTuple_GetItem(po, 1)) & 0xFFFFFFFF);
            
          }
          
        } else {
          if (!PyTuple_Check(pval) || PyTuple_Size(pval) != 2) {
            PyErr_SetString(PyExc_TypeError, "Expected tuple of 2 elements as argument");
            delete[] val;
            return -1;
          }
          val[0] = (DWORD) (PyInt_AsLong(PyTuple_GetItem(pval, 0)) & 0xFFFFFFFF);
          val[1] = (DWORD) (PyInt_AsLong(PyTuple_GetItem(pval, 1)) & 0xFFFFFFFF);
        }
        FreeImage_SetTagLength(self->t, cnt * 2 * sizeof(DWORD));
        FreeImage_SetTagValue(self->t, (const void*)val);
        delete[] val;
        
      } else if (typ == FIDT_SBYTE) {
        char *val = new char[cnt];
        if (cnt > 1) {
          for (unsigned long i=0; i<cnt; ++i) {
            PyObject *po = PyList_GetItem(pval, i);
            if (!PyInt_Check(po)) {
              PyErr_SetString(PyExc_TypeError, "Expected int elements");
              delete[] val;
              return -1;
            }
            val[i] = (char) (PyInt_AsLong(po) & 0x000000FF);
          }
          
        } else {
          if (!PyInt_Check(pval)) {
            PyErr_SetString(PyExc_TypeError, "Expected int argument");
            delete[] val;
            return -1;
          }
          val[0] = (char) (PyInt_AsLong(pval) & 0x000000FF);
        }
        FreeImage_SetTagLength(self->t, cnt * sizeof(char));
        FreeImage_SetTagValue(self->t, (const void*)val);
        delete[] val;
        
      } else if (typ == FIDT_SSHORT) {
        short *val = new short[cnt];
        if (cnt > 1) {
          for (unsigned long i=0; i<cnt; ++i) {
            PyObject *po = PyList_GetItem(pval, i);
            if (!PyInt_Check(po)) {
              PyErr_SetString(PyExc_TypeError, "Expected int elements");
              delete[] val;
              return -1;
            }
            val[i] = (short) (PyInt_AsLong(po) & 0x0000FFFF);
          }
          
        } else {
          if (!PyInt_Check(pval)) {
            PyErr_SetString(PyExc_TypeError, "Expected int argument");
            delete[] val;
            return -1;
          }
          val[0] = (short) (PyInt_AsLong(pval) & 0x0000FFFF);
        }
        FreeImage_SetTagLength(self->t, cnt * sizeof(short));
        FreeImage_SetTagValue(self->t, (const void*)val);
        delete[] val;
      
      } else if (typ == FIDT_SLONG) {
        LONG *val = new LONG[cnt];
        if (cnt > 1) {
          for (unsigned long i=0; i<cnt; ++i) {
            PyObject *po = PyList_GetItem(pval, i);
            if (!PyInt_Check(po)) {
              PyErr_SetString(PyExc_TypeError, "Expected int elements");
              delete[] val;
              return -1;
            }
            val[i] = (LONG) (PyInt_AsLong(po) & 0xFFFFFFFF);
          }
          
        } else {
          if (!PyInt_Check(pval)) {
            PyErr_SetString(PyExc_TypeError, "Expected int argument");
            delete[] val;
            return -1;
          }
          val[0] = (LONG) (PyInt_AsLong(pval) & 0xFFFFFFFF);
        }
        FreeImage_SetTagLength(self->t, cnt * sizeof(LONG));
        FreeImage_SetTagValue(self->t, (const void*)val);
        delete[] val;
        
      } else if (typ == FIDT_SRATIONAL) {
        LONG *val = new LONG[2*cnt];
        if (cnt > 1) {
          for (unsigned long i=0, j=0; i<cnt; ++i, j+=2) {
            PyObject *po = PyList_GetItem(pval, i);
            if (!PyTuple_Check(po) || PyTuple_Size(po) != 2) {
              PyErr_SetString(PyExc_TypeError, "Expected 2 elements tuple elements");
              delete[] val;
              return -1;
            }
            val[j] = (LONG) (PyInt_AsLong(PyTuple_GetItem(po, 0)) & 0xFFFFFFFF);
            val[j+1] = (LONG) (PyInt_AsLong(PyTuple_GetItem(po, 1)) & 0xFFFFFFFF);
            
          }
          
        } else {
          if (!PyTuple_Check(pval) || PyTuple_Size(pval) != 2) {
            PyErr_SetString(PyExc_TypeError, "Expected tuple of 2 elements as argument");
            delete[] val;
            return -1;
          }
          val[0] = (LONG) (PyInt_AsLong(PyTuple_GetItem(pval, 0)) & 0xFFFFFFFF);
          val[1] = (LONG) (PyInt_AsLong(PyTuple_GetItem(pval, 1)) & 0xFFFFFFFF);
        }
        FreeImage_SetTagLength(self->t, cnt * 2 * sizeof(LONG));
        FreeImage_SetTagValue(self->t, (const void*)val);
        delete[] val;
        
      } else if (typ == FIDT_FLOAT) {
        float *val = new float[cnt];
        if (cnt > 1) {
          for (unsigned long i=0; i<cnt; ++i) {
            PyObject *po = PyList_GetItem(pval, i);
            if (!PyInt_Check(po)) {
              PyErr_SetString(PyExc_TypeError, "Expected int elements");
              delete[] val;
              return -1;
            }
            val[i] = (float) PyFloat_AsDouble(po);
          }
          
        } else {
          if (!PyInt_Check(pval)) {
            PyErr_SetString(PyExc_TypeError, "Expected int argument");
            delete[] val;
            return -1;
          }
          val[0] = (float) PyFloat_AsDouble(pval);
        }
        FreeImage_SetTagLength(self->t, cnt * sizeof(float));
        FreeImage_SetTagValue(self->t, (const void*)val);
        delete[] val;
        
      } else if (typ == FIDT_DOUBLE) {
        double *val = new double[cnt];
        if (cnt > 1) {
          for (unsigned long i=0; i<cnt; ++i) {
            PyObject *po = PyList_GetItem(pval, i);
            if (!PyInt_Check(po)) {
              PyErr_SetString(PyExc_TypeError, "Expected int elements");
              delete[] val;
              return -1;
            }
            val[i] = PyFloat_AsDouble(po);
          }
          
        } else {
          if (!PyInt_Check(pval)) {
            PyErr_SetString(PyExc_TypeError, "Expected int argument");
            delete[] val;
            return -1;
          }
          val[0] = PyFloat_AsDouble(pval);
        }
        FreeImage_SetTagLength(self->t, cnt * sizeof(double));
        FreeImage_SetTagValue(self->t, (const void*)val);
        delete[] val;
        
      } else if (typ == FIDT_ASCII) {
        size_t totalLen = 0;
        char *val = 0;
        if (cnt > 1) {
          PyObject *po;
          for (unsigned long i=0; i<cnt; ++i) {
            po = PyList_GetItem(pval, i);
            if (!PyString_Check(po)) {
              PyErr_SetString(PyExc_TypeError, "Expected string elements");
              return -1;
            }
            totalLen += (PyString_Size(po) + 1);
          }
          val = new char[totalLen];
          char *cur = val;
          for (unsigned long i=0; i<cnt; ++i) {
            po = PyList_GetItem(pval, i);
            strcpy(cur, PyString_AsString(po));
            cur += PyString_Size(po) + 1;
          }
          
        } else {
          if (!PyString_Check(pval)) {
            PyErr_SetString(PyExc_TypeError, "Expected string argument");
            return -1;
          }
          totalLen = PyString_Size(pval) + 1;
          val = new char[totalLen];
          strcpy(val, PyString_AsString(pval));
        }
        FreeImage_SetTagLength(self->t, totalLen);
        FreeImage_SetTagValue(self->t, (const void*)val);
        delete[] val;
        
      } else if (typ == FIDT_PALETTE) {
        RGBQUAD *pal = new RGBQUAD[cnt];
        
        if (cnt > 1) {
          for (unsigned long i=0; i<cnt; ++i) {
            PyObject *po = PyList_GetItem(pval, i);
            if (!PyTuple_Check(po) || PyTuple_Size(po)!=3) {
              PyErr_SetString(PyExc_TypeError, "Expected a rgb tuple as argument");
              delete[] pal;
              return -1;
            }
            PyArg_ParseTuple(po, "BBB", &(pal[i].rgbRed), &(pal[i].rgbGreen), &(pal[i].rgbBlue));
          }
        
        } else {
          if (!PyTuple_Check(pval) || PyTuple_Size(pval)!=3) {
            PyErr_SetString(PyExc_TypeError, "Expected a rgb tuple as argument");
            delete[] pal;
            return -1;
          }
          PyArg_ParseTuple(pval, "BBB", &(pal[0].rgbRed), &(pal[0].rgbGreen), &(pal[0].rgbBlue));
        }
        
        FreeImage_SetTagLength(self->t, cnt * sizeof(RGBQUAD));
        FreeImage_SetTagValue(self->t, (const void*)pal);
        delete[] pal;
        
      } else if (typ == FIDT_UNDEFINED) {
        unsigned char *val = new unsigned char[cnt];
        if (cnt > 1) {
          for (unsigned long i=0; i<cnt; ++i) {
            PyObject *po = PyList_GetItem(pval, i);
            if (!PyInt_Check(po)) {
              PyErr_SetString(PyExc_TypeError, "Expected int elements");
              delete[] val;
              return -1;
            }
            val[i] = (unsigned char) (PyInt_AsLong(po) & 0x000000FF);
          }
          
        } else {
          if (!PyInt_Check(pval)) {
            PyErr_SetString(PyExc_TypeError, "Expected int argument");
            delete[] val;
            return -1;
          }
          val[0] = (unsigned char) (PyInt_AsLong(pval) & 0x000000FF);
        }
        FreeImage_SetTagLength(self->t, cnt * sizeof(unsigned char));
        FreeImage_SetTagValue(self->t, (const void*)val);
        delete[] val;
      }
    }
  }
  return 0;
}

static PyObject* Tag_toString(PyObject *pself, PyObject *args) {
  FITAGObject *self = (FITAGObject*) pself;
  if (self->t) {
    int mdl;
    char *def=0;
    if (!PyArg_ParseTuple(args, "i|s", &mdl, &def)) {
      return NULL;
    }
    return PyString_FromString(FreeImage_TagToString((FREE_IMAGE_MDMODEL)mdl, self->t, def));
  } else {
    return PyString_FromString("");
  }
}

static PyGetSetDef Tag_getset[] = {
  {(char*)"key", Tag_getKey, Tag_setKey, (char*)"", NULL},
  {(char*)"description", Tag_getDesc, Tag_setDesc, (char*)"", NULL},
  {(char*)"ID", Tag_getID, Tag_setID, (char*)"", NULL},
  {(char*)"type", Tag_getType, Tag_setType, (char*)"", NULL},
  {(char*)"count", Tag_getCount, Tag_setCount, (char*)"", NULL},
  //{(char*)"length", Tag_getLength, Tag_setLength, (char*)"", NULL},
  {(char*)"value", Tag_getValue, Tag_setValue, (char*)"", NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

static PyMethodDef Tag_methods[] = {
  {"Clone", (PyCFunction)Tag_clone, METH_NOARGS, ""},
  {"ToString", Tag_toString, METH_VARARGS, ""},
  {NULL, NULL, 0, NULL}
};

bool InitTag(PyObject *module) {
  
  FITAGType.tp_flags = Py_TPFLAGS_DEFAULT;
  FITAGType.tp_doc = "FreeImage Tag object";
  FITAGType.tp_new = Tag_new;
  FITAGType.tp_init = Tag_init;
  FITAGType.tp_dealloc = Tag_dealloc;
  FITAGType.tp_methods = Tag_methods;
  FITAGType.tp_getset = Tag_getset;
  
  if (PyType_Ready(&FITAGType) < 0) {
    return false;
  }
  
  Py_INCREF(&FITAGType);
  PyModule_AddObject(module, "Tag", (PyObject*)&FITAGType);
  
  return true;
}

// ---

PyTypeObject FIMETADATAType = {
  PyObject_HEAD_INIT(NULL)
  0,
  "fipy.Metadata",
  sizeof(FIMETADATAObject),
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

PyObject* Metadata_new(PyTypeObject *type, PyObject *, PyObject *) {
  PyObject *po = type->tp_alloc(type, 0);
  FIMETADATAObject *o = (FIMETADATAObject*) po;
  o->md = 0;
  o->own = true;
  return po;
}

int Metadata_init(PyObject *, PyObject *, PyObject*) {
  return 0;
}

void Metadata_dealloc(PyObject *pself) {
  FIMETADATAObject *self = (FIMETADATAObject*) pself;
  if (self->own && self->md) {
    FreeImage_FindCloseMetadata(self->md);
    self->md = 0;
  }
}

PyObject* Metadata_first(PyObject *pself, PyObject *args) {
  FIMETADATAObject *self = (FIMETADATAObject*) pself;
  
  PyObject *pb = 0;
  int mdl = 0;
  if (!PyArg_ParseTuple(args, "iO", &mdl, &pb)) {
    return NULL;
  }
  if (!PyObject_TypeCheck(pb, &FIBITMAPType)) {
    PyErr_SetString(PyExc_TypeError, "Expected a fipy.Bitmap object as second argument");
    return NULL;
  }
  FIBITMAPObject *b = (FIBITMAPObject*)pb;
  FITAG *tag = 0;
  FIMETADATA *md = FreeImage_FindFirstMetadata((FREE_IMAGE_MDMODEL)mdl, b->b, &tag);
  if (md) {
    if (self->own && self->md) {
      FreeImage_FindCloseMetadata(self->md);
    }
    self->md = md;
    self->own = true;
    // create tag object    
    PyObject *po = PyObject_CallObject((PyObject*)&FITAGType, NULL);
    FITAGObject *o = (FITAGObject*) po;
    o->t = tag;
    o->own = false;
    return po;
  }
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* Metadata_next(PyObject *pself) {
  FIMETADATAObject *self = (FIMETADATAObject*) pself;
  if (self->md) {
    FITAG *tag = 0;
    if (FreeImage_FindNextMetadata(self->md, &tag)) {
      PyObject *po = PyObject_CallObject((PyObject*)&FITAGType, NULL);
      FITAGObject *o = (FITAGObject*) po;
      o->t = tag;
      o->own = false;
      return po;
    }
  }
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* Metadata_close(PyObject *pself) {
  FIMETADATAObject *self = (FIMETADATAObject*) pself;
  if (self->md) {
    if (self->own) {
      FreeImage_FindCloseMetadata(self->md);
    }
    self->md = 0;
  }
  Py_INCREF(Py_None);
  return Py_None;
}

static PyMethodDef Metadata_methods[] = {
  {"First", Metadata_first, METH_VARARGS, ""},
  {"Next", (PyCFunction)Metadata_next, METH_NOARGS, ""},
  {"Close", (PyCFunction)Metadata_close, METH_NOARGS, ""},
  {NULL, NULL, 0, NULL}
};

bool InitMetadata(PyObject *module) {
  
  FIMETADATAType.tp_flags = Py_TPFLAGS_DEFAULT;
  FIMETADATAType.tp_doc = "FreeImage Metadata object";
  FIMETADATAType.tp_new = Metadata_new;
  FIMETADATAType.tp_dealloc = Metadata_dealloc;
  FIMETADATAType.tp_init = Metadata_init;
  FIMETADATAType.tp_methods = Metadata_methods;
  
  
  if (PyType_Ready(&FIMETADATAType) < 0) {
    return false;
  }
  
  Py_INCREF(&FIMETADATAType);
  PyModule_AddObject(module, "Metadata", (PyObject*)&FIMETADATAType);
  
  return true;
}

