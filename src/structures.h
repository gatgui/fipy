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

#ifndef __structures_h_
#define __structures_h_

#include <Python.h>
#include <FreeImage.h>

typedef struct {
  PyObject_HEAD
  FIBITMAP *b;
  bool own;
} FIBITMAPObject;

typedef struct {
  PyObject_HEAD
  FIMULTIBITMAP *mb;
  bool own;
} FIMULTIBITMAPObject;

typedef struct {
  PyObject_HEAD
  BITMAPINFOHEADER bih;
} BITMAPINFOHEADERObject;

typedef struct {
  PyObject_HEAD
  BITMAPINFO bi;
} BITMAPINFOObject;

typedef struct {
  PyObject_HEAD
  FIICCPROFILE *iccp;
} FIICCPROFILEObject;

typedef struct {
  PyObject_HEAD
  FITAG *t;
  bool own;
} FITAGObject;

typedef struct {
  PyObject_HEAD
  FIMETADATA *md;
  bool own;
} FIMETADATAObject;

extern PyTypeObject FIBITMAPType;
extern PyTypeObject FIMULTIBITMAPType;
extern PyTypeObject BITMAPINFOHEADERType;
extern PyTypeObject BITMAPINFOType;
extern PyTypeObject FIICCPROFILEType;
extern PyTypeObject FITAGType;
extern PyTypeObject FIMETADATAType;

#undef Py_INCREF
#undef Py_DECREF

/*
Original Macros

#define Py_INCREF(op) (                 \
  _Py_INC_REFTOTAL  _Py_REF_DEBUG_COMMA \
  ((PyObject*)(op))->ob_refcnt++)

#define Py_DECREF(op)                       \
  if (_Py_DEC_REFTOTAL  _Py_REF_DEBUG_COMMA \
      --((PyObject*)(op))->ob_refcnt != 0)  \
      _Py_CHECK_REFCNT(op)                  \
  else                                      \
      _Py_Dealloc((PyObject*)(op))
*/

#define Py_INCREF(op)               \
  { void *_tmp = (void*) op;        \
    ((PyObject*)_tmp)->ob_refcnt++; }

#define Py_DECREF(op)                        \
  { void *_tmp = (void*) op;                 \
    if (--((PyObject*)_tmp)->ob_refcnt == 0) \
      _Py_Dealloc((PyObject*)_tmp);          }

#endif
