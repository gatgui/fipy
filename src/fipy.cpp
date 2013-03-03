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

static PyObject* FI_Init(PyObject *, PyObject *args) {
  PyObject *localPlugins = NULL;
  if (!PyArg_ParseTuple(args, "|O", &localPlugins)) {
    return NULL;
  }
  bool loadLocalPlugins = (localPlugins ? (localPlugins == Py_True) : false);
  FreeImage_Initialise(loadLocalPlugins);
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* FI_DeInit(PyObject *) {
  FreeImage_DeInitialise();
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* FI_GetVersion(PyObject *) {
  return PyString_FromString(FreeImage_GetVersion());
}

static PyObject* FI_GetCopyright(PyObject *) {
  return PyString_FromString(FreeImage_GetCopyrightMessage());
}

// TODO: FreeImage_SetOutputMessage( OutputMessageFunc(FIF, msg) )

static PyObject* FI_GetFileType(PyObject *, PyObject *args) {
  char *filename;
  int sz=0;
  if (!PyArg_ParseTuple(args, "s|i", &filename, &sz)) {
    return NULL;
  }
  return PyInt_FromLong(FreeImage_GetFileType(filename, sz));
}

static PyObject* FI_GetFileTypeU(PyObject *, PyObject *args) {
  Py_UNICODE *filename;
  int sz=0;
  if (!PyArg_ParseTuple(args, "u|i", &filename, &sz)) {
    return NULL;
  }
  return PyInt_FromLong(FreeImage_GetFileTypeU((const wchar_t*)filename, sz));
}

// not supported: FreeImage_GetFileTypeFromHandle
// not supported: FreeImage_GetFileTypeFromMemory

static PyObject* FI_GetFIFCount(PyObject *) {
  return PyInt_FromLong(FreeImage_GetFIFCount());
}

static PyObject* FI_IsPluginEnabled(PyObject *, PyObject *args) {
  int fif;
  if (PyArg_ParseTuple(args, "i", &fif)) {
    return NULL;
  }
  if (FreeImage_IsPluginEnabled((FREE_IMAGE_FORMAT)fif)) {
    Py_INCREF(Py_True);
    return Py_True;
  } else {
    Py_INCREF(Py_False);
    return Py_False;
  }
}

static PyObject* FI_SetPluginEnabled(PyObject *, PyObject *args) {
  int fif;
  PyObject *o;
  if (PyArg_ParseTuple(args, "iO", &fif, &o)) {
    return NULL;
  }
  if (!PyBool_Check(o)) {
    PyErr_SetString(PyExc_TypeError, "Expected boolean as second argument");
    return NULL;
  }
  int rv = FreeImage_SetPluginEnabled((FREE_IMAGE_FORMAT)fif, o == Py_True);
  return PyInt_FromLong(rv);
}

static PyObject* FI_GetFIFFromFormat(PyObject *, PyObject *args) {
  char *fmt;
  if (!PyArg_ParseTuple(args, "s", &fmt)) {
    return NULL;
  }
  return PyInt_FromLong(FreeImage_GetFIFFromFormat(fmt));
}

static PyObject* FI_GetFIFFromMime(PyObject *, PyObject *args) {
  char *mime;
  if (!PyArg_ParseTuple(args, "s", &mime)) {
    return NULL;
  }
  return PyInt_FromLong(FreeImage_GetFIFFromMime(mime));
}

static PyObject* FI_GetFIFMimeType(PyObject *, PyObject *args) {
  int fif;
  if (!PyArg_ParseTuple(args, "i", &fif)) {
    return NULL;
  }
  return PyString_FromString(FreeImage_GetFIFMimeType((FREE_IMAGE_FORMAT)fif));
}

static PyObject* FI_GetFormatFromFIF(PyObject *, PyObject *args) {
  int fif;
  if (!PyArg_ParseTuple(args, "i", &fif)) {
    return NULL;
  }
  return PyString_FromString(FreeImage_GetFormatFromFIF((FREE_IMAGE_FORMAT)fif));
}

static PyObject* FI_GetFIFExtensionList(PyObject *, PyObject *args) {
  int fif;
  if (!PyArg_ParseTuple(args, "i", &fif)) {
    return NULL;
  }
  return PyString_FromString(FreeImage_GetFIFExtensionList((FREE_IMAGE_FORMAT)fif));
}

static PyObject* FI_GetFIFDescription(PyObject *, PyObject *args) {
  int fif;
  if (!PyArg_ParseTuple(args, "i", &fif)) {
    return NULL;
  }
  return PyString_FromString(FreeImage_GetFIFDescription((FREE_IMAGE_FORMAT)fif));
}

static PyObject* FI_GetFIFRegExpr(PyObject *, PyObject *args) {
  int fif;
  if (!PyArg_ParseTuple(args, "i", &fif)) {
    return NULL;
  }
  return PyString_FromString(FreeImage_GetFIFRegExpr((FREE_IMAGE_FORMAT)fif));
}

static PyObject* FI_GetFIFFromFilename(PyObject *, PyObject *args) {
  char *filename;
  if (!PyArg_ParseTuple(args, "s", &filename)) {
    return NULL;
  }
  return PyInt_FromLong(FreeImage_GetFIFFromFilename(filename));
}

static PyObject* FI_GetFIFFromFilenameU(PyObject *, PyObject *args) {
  Py_UNICODE *filename;
  if (!PyArg_ParseTuple(args, "u", &filename)) {
    return NULL;
  }
  return PyInt_FromLong(FreeImage_GetFIFFromFilenameU((const wchar_t*)filename));
}

static PyObject* FI_FIFSupportsReading(PyObject *, PyObject *args) {
  int fif;
  if (!PyArg_ParseTuple(args, "i", &fif)) {
    return NULL;
  }
  if (FreeImage_FIFSupportsReading((FREE_IMAGE_FORMAT)fif)) {
    Py_INCREF(Py_True);
    return Py_True;
  } else {
    Py_INCREF(Py_False);
    return Py_False;
  }
}

static PyObject* FI_FIFSupportsWriting(PyObject *, PyObject *args) {
  int fif;
  if (!PyArg_ParseTuple(args, "i", &fif)) {
    return NULL;
  }
  if (FreeImage_FIFSupportsWriting((FREE_IMAGE_FORMAT)fif)) {
    Py_INCREF(Py_True);
    return Py_True;
  } else {
    Py_INCREF(Py_False);
    return Py_False;
  }
}

static PyObject* FI_FIFSupportsICCProfiles(PyObject *, PyObject *args) {
  int fif;
  if (!PyArg_ParseTuple(args, "i", &fif)) {
    return NULL;
  }
  if (FreeImage_FIFSupportsICCProfiles((FREE_IMAGE_FORMAT)fif)) {
    Py_INCREF(Py_True);
    return Py_True;
  } else {
    Py_INCREF(Py_False);
    return Py_False;
  }
}

static PyObject* FI_FIFSupportsExportType(PyObject *, PyObject *args) {
  int fif, typ;
  if (!PyArg_ParseTuple(args, "ii", &fif, &typ)) {
    return NULL;
  }
  if (FreeImage_FIFSupportsExportType((FREE_IMAGE_FORMAT)fif, (FREE_IMAGE_TYPE)typ)) {
    Py_INCREF(Py_True);
    return Py_True;
  } else {
    Py_INCREF(Py_False);
    return Py_False;
  }
}

static PyObject* FI_FIFSupportsExportBPP(PyObject *, PyObject *args) {
  int fif, bpp;
  if (!PyArg_ParseTuple(args, "ii", &fif, &bpp)) {
    return NULL;
  }
  if (FreeImage_FIFSupportsExportBPP((FREE_IMAGE_FORMAT)fif, bpp)) {
    Py_INCREF(Py_True);
    return Py_True;
  } else {
    Py_INCREF(Py_False);
    return Py_False;
  }
}

// TODO: FreeImage_RegisterLocalPlugin

#if FREEIMAGE_MINOR_VERSION >= 12 && defined(_WIN32)
static PyObject* FI_RegisterExternalPlugin(PyObject *, PyObject *args) {
  char *path;
  char *fmt = 0;
  char *desc = 0;
  char *exts = 0;
  char *regexp = 0;
  if (!PyArg_ParseTuple(args, "s|ssss", &path, &fmt, &desc, &exts, &regexp)) {
    return NULL;
  }
  return PyInt_FromLong(FreeImage_RegisterExternalPlugin(path, fmt, desc, exts, regexp));
}
#endif

// TODO: FreeImage_ZLibCompress
// TODO: FreeImage_ZLibUncompress
// TODO: FreeImage_ZLibGZip
// TODO: FreeImage_ZLibCRC32
// TODO: FreeImage_ZLibGUnzip

static PyObject* FI_IsLittleEndian(PyObject *) {
  if (FreeImage_IsLittleEndian()) {
    Py_INCREF(Py_True);
    return Py_True;
  } else {
    Py_INCREF(Py_False);
    return Py_False;
  }
}

static PyObject* FI_LookupX11Color(PyObject *, PyObject *args) {
  char *cname;
  if (!PyArg_ParseTuple(args, "s", &cname)) {
    return NULL;
  }
  unsigned char r, g, b;
  FreeImage_LookupX11Color(cname, &r, &g, &b);
  return Py_BuildValue("(i,i,i)", r, g, b);
}

static PyObject* FI_LookupSVGColor(PyObject *, PyObject *args) {
  char *cname;
  if (!PyArg_ParseTuple(args, "s", &cname)) {
    return NULL;
  }
  unsigned char r, g, b;
  FreeImage_LookupSVGColor(cname, &r, &g, &b);
  return Py_BuildValue("(i,i,i)", r, g, b);
}

#if !defined(FEDORA_BUILD)
PyObject* FI_JPEGCrop(PyObject *, PyObject *args) {
  char *src, *dst;
  int top, left, right, bottom;
  if (!PyArg_ParseTuple(args, "ssiiii", &src, &dst, &left, &top, &right, &bottom)) {
    return NULL;
  }
  if (FreeImage_JPEGCrop(src, dst, left, top, right, bottom)) {
    Py_INCREF(Py_True);
    return Py_True;
  } else {
    Py_INCREF(Py_False);
    return Py_False;
  }
}
#endif

static PyMethodDef FI_Methods[] = {
  {"Initialise", FI_Init, METH_VARARGS, "Initialise FreeImage library"},
  {"DeInitialise", (PyCFunction)FI_DeInit, METH_NOARGS, "DeInitialise FreeImage library"},
  {"GetVersion", (PyCFunction)FI_GetVersion, METH_NOARGS, "FreeImage library version"},
  {"GetCopyrightMessage", (PyCFunction)FI_GetCopyright, METH_NOARGS, "FreeImage copyright message"},
  {"GetFileType", FI_GetFileType, METH_VARARGS, ""},
  {"GetFileTypeU", FI_GetFileTypeU, METH_VARARGS, ""},
  {"IsLittleEndian", (PyCFunction)FI_IsLittleEndian, METH_NOARGS, ""},
  {"LookupX11Color", FI_LookupX11Color, METH_VARARGS, ""},
  {"LookupSVGColor", FI_LookupSVGColor, METH_VARARGS, ""},
  {"GetFIFCount", (PyCFunction)FI_GetFIFCount, METH_NOARGS, ""},
  {"IsPluginEnabled", FI_IsPluginEnabled, METH_VARARGS, ""},
  {"SetPluginEnabled", FI_SetPluginEnabled, METH_VARARGS, ""},
  {"GetFIFFromFormat", FI_GetFIFFromFormat, METH_VARARGS, ""},
  {"GetFIFFromMime", FI_GetFIFFromMime, METH_VARARGS, ""},
  {"GetFIFMimeType", FI_GetFIFMimeType, METH_VARARGS, ""},
  {"GetFormatFromFIF", FI_GetFormatFromFIF, METH_VARARGS, ""},
  {"GetFIFExtensionList", FI_GetFIFExtensionList, METH_VARARGS, ""},
  {"GetFIFDescription", FI_GetFIFDescription, METH_VARARGS, ""},
  {"GetFIFRegExpr", FI_GetFIFRegExpr, METH_VARARGS, ""},
  {"GetFIFFromFilename", FI_GetFIFFromFilename, METH_VARARGS, ""},
  {"GetFIFFromFilenameU", FI_GetFIFFromFilenameU, METH_VARARGS, ""},
  {"FIFSupportsReading", FI_FIFSupportsReading, METH_VARARGS, ""},
  {"FIFSupportsWriting", FI_FIFSupportsWriting, METH_VARARGS, ""},
  {"FIFSupportsExportType", FI_FIFSupportsExportType, METH_VARARGS, ""},
  {"FIFSupportsExportBPP", FI_FIFSupportsExportBPP, METH_VARARGS, ""},
  {"FIFSupportsICCProfiles", FI_FIFSupportsICCProfiles, METH_VARARGS, ""},
#if FREEIMAGE_MINOR_VERSION >= 12 && defined(_WIN32)
  {"RegisterExternalPlugin", FI_RegisterExternalPlugin, METH_VARARGS, ""},
#endif
#if !defined(FEDORA_BUILD)
  {"JPEGCrop", FI_JPEGCrop, METH_VARARGS, ""},
#endif
  {NULL, NULL, 0, NULL}
};

// ---

extern bool InitBitmap(PyObject *module);
extern bool InitMultiBitmap(PyObject *module);
extern bool InitBitmapInfoHeader(PyObject *module);
extern bool InitBitmapInfo(PyObject *module);
extern bool InitICCProfile(PyObject *module);
extern bool InitTag(PyObject *module);
extern bool InitMetadata(PyObject *module);

extern "C" {
  
#ifdef _WIN32
  __declspec(dllexport)
#else
  __attribute__ ((visibility("default")))
#endif
  void initfipy(void) {
    PyObject *fipy = Py_InitModule("fipy", FI_Methods);
    
    if (!InitTag(fipy)) {
      PyErr_SetString(PyExc_RuntimeError, "Could not initialise fipy.Tag class");
      return;
    }
    
    if (!InitMetadata(fipy)) {
      PyErr_SetString(PyExc_RuntimeError, "Could not initialise fipy.Metadata class");
      return;
    }
    
    if (!InitICCProfile(fipy)) {
      PyErr_SetString(PyExc_RuntimeError, "Could not initialise fipy.ICCProfile class");
      return;
    }
    
    if (!InitBitmap(fipy)) {
      PyErr_SetString(PyExc_RuntimeError, "Could not initialise fipy.Bitmap class");
      return;
    }
    
    if (!InitMultiBitmap(fipy)) {
      PyErr_SetString(PyExc_RuntimeError, "Could not initialise fipy.MultiBitmap class");
      return;
    }
    
    if (!InitBitmapInfoHeader(fipy)) {
      PyErr_SetString(PyExc_RuntimeError, "Could not initialise fipy.BitmapInfoHeader class");
      return;
    }
    
    if (!InitBitmapInfo(fipy)) {
      PyErr_SetString(PyExc_RuntimeError, "Could not initialise fipy.BitmapInfo class");
      return;
    }
    
    // define constants here
    PyModule_AddIntConstant(fipy, "FI_RGBA_RED", FI_RGBA_RED);
    PyModule_AddIntConstant(fipy, "FI_RGBA_GREEN", FI_RGBA_GREEN);
    PyModule_AddIntConstant(fipy, "FI_RGBA_BLUE", FI_RGBA_BLUE);
    PyModule_AddIntConstant(fipy, "FI_RGBA_ALPHA", FI_RGBA_ALPHA);
    PyModule_AddIntConstant(fipy, "FI_RGBA_RED_MASK", FI_RGBA_RED_MASK);
    PyModule_AddIntConstant(fipy, "FI_RGBA_GREEN_MASK", FI_RGBA_GREEN_MASK);
    PyModule_AddIntConstant(fipy, "FI_RGBA_BLUE_MASK", FI_RGBA_BLUE_MASK);
    PyModule_AddIntConstant(fipy, "FI_RGBA_ALPHA_MASK", FI_RGBA_ALPHA_MASK);
    PyModule_AddIntConstant(fipy, "FI_RGBA_RED_SHIFT", FI_RGBA_RED_SHIFT);
    PyModule_AddIntConstant(fipy, "FI_RGBA_GREEN_SHIFT", FI_RGBA_GREEN_SHIFT);
    PyModule_AddIntConstant(fipy, "FI_RGBA_BLUE_SHIFT", FI_RGBA_BLUE_SHIFT);
    PyModule_AddIntConstant(fipy, "FI_RGBA_ALPHA_SHIFT", FI_RGBA_ALPHA_SHIFT);
    PyModule_AddIntConstant(fipy, "FI_RGBA_RGB_MASK", FI_RGBA_RGB_MASK);
    
    PyModule_AddIntConstant(fipy, "FI16_555_RED_MASK", FI16_555_RED_MASK);
    PyModule_AddIntConstant(fipy, "FI16_555_GREEN_MASK", FI16_555_GREEN_MASK);
    PyModule_AddIntConstant(fipy, "FI16_555_BLUE_MASK", FI16_555_BLUE_MASK);
    PyModule_AddIntConstant(fipy, "FI16_555_RED_SHIFT", FI16_555_RED_SHIFT);
    PyModule_AddIntConstant(fipy, "FI16_555_GREEN_SHIFT", FI16_555_GREEN_SHIFT);
    PyModule_AddIntConstant(fipy, "FI16_555_BLUE_SHIFT", FI16_555_BLUE_SHIFT);
    PyModule_AddIntConstant(fipy, "FI16_565_RED_MASK", FI16_565_RED_MASK);
    PyModule_AddIntConstant(fipy, "FI16_565_GREEN_MASK", FI16_565_GREEN_MASK);
    PyModule_AddIntConstant(fipy, "FI16_565_BLUE_MASK", FI16_565_BLUE_MASK);
    PyModule_AddIntConstant(fipy, "FI16_565_RED_SHIFT", FI16_565_RED_SHIFT);
    PyModule_AddIntConstant(fipy, "FI16_565_GREEN_SHIFT", FI16_565_GREEN_SHIFT);
    PyModule_AddIntConstant(fipy, "FI16_565_BLUE_SHIFT", FI16_565_BLUE_SHIFT);
    
    PyModule_AddIntConstant(fipy, "FIICC_DEFAULT", FIICC_DEFAULT);
    PyModule_AddIntConstant(fipy, "FIICC_COLOR_IS_CMYK", FIICC_COLOR_IS_CMYK);
    
    // Image format
    PyModule_AddIntConstant(fipy, "FIF_UNKNOWN", FIF_UNKNOWN);
    PyModule_AddIntConstant(fipy, "FIF_BMP", FIF_BMP);
    PyModule_AddIntConstant(fipy, "FIF_ICO", FIF_ICO);
    PyModule_AddIntConstant(fipy, "FIF_JPEG", FIF_JPEG);
    PyModule_AddIntConstant(fipy, "FIF_JNG", FIF_JNG);
    PyModule_AddIntConstant(fipy, "FIF_KOALA", FIF_KOALA);
    PyModule_AddIntConstant(fipy, "FIF_LBM", FIF_LBM);
    PyModule_AddIntConstant(fipy, "FIF_IFF", FIF_IFF);
    PyModule_AddIntConstant(fipy, "FIF_MNG", FIF_MNG);
    PyModule_AddIntConstant(fipy, "FIF_PBM", FIF_PBM);
    PyModule_AddIntConstant(fipy, "FIF_PBMRAW", FIF_PBMRAW);
    PyModule_AddIntConstant(fipy, "FIF_PCD", FIF_PCD);
    PyModule_AddIntConstant(fipy, "FIF_PCX", FIF_PCX);
    PyModule_AddIntConstant(fipy, "FIF_PGM", FIF_PGM);
    PyModule_AddIntConstant(fipy, "FIF_PGMRAW", FIF_PGMRAW);
    PyModule_AddIntConstant(fipy, "FIF_PNG", FIF_PNG);
    PyModule_AddIntConstant(fipy, "FIF_PPM", FIF_PPM);
    PyModule_AddIntConstant(fipy, "FIF_PPMRAW", FIF_PPMRAW);
    PyModule_AddIntConstant(fipy, "FIF_RAS", FIF_RAS);
    PyModule_AddIntConstant(fipy, "FIF_TARGA", FIF_TARGA);
    PyModule_AddIntConstant(fipy, "FIF_TIFF", FIF_TIFF);
    PyModule_AddIntConstant(fipy, "FIF_WBMP", FIF_WBMP);
    PyModule_AddIntConstant(fipy, "FIF_PSD", FIF_PSD);
    PyModule_AddIntConstant(fipy, "FIF_CUT", FIF_CUT);
    PyModule_AddIntConstant(fipy, "FIF_XBM", FIF_XBM);
    PyModule_AddIntConstant(fipy, "FIF_XPM", FIF_XPM);
    PyModule_AddIntConstant(fipy, "FIF_DDS", FIF_DDS);
    PyModule_AddIntConstant(fipy, "FIF_GIF", FIF_GIF);
    PyModule_AddIntConstant(fipy, "FIF_HDR", FIF_HDR);
#if !defined(FEDORA_BUILD)
    PyModule_AddIntConstant(fipy, "FIF_FAXG3", FIF_FAXG3);
#endif
    PyModule_AddIntConstant(fipy, "FIF_SGI", FIF_SGI);
    PyModule_AddIntConstant(fipy, "FIF_EXR", FIF_EXR);
    PyModule_AddIntConstant(fipy, "FIF_J2K", FIF_J2K);
    PyModule_AddIntConstant(fipy, "FIF_JP2", FIF_JP2);
#if FREEIMAGE_MINOR_VERSION >= 12
    PyModule_AddIntConstant(fipy, "FIF_PFM", FIF_PFM);
#endif
        
    // Image type
    PyModule_AddIntConstant(fipy, "FIT_UNKNOWN", FIT_UNKNOWN);
    PyModule_AddIntConstant(fipy, "FIT_BITMAP", FIT_BITMAP);
    PyModule_AddIntConstant(fipy, "FIT_UINT16", FIT_UINT16);
    PyModule_AddIntConstant(fipy, "FIT_INT16", FIT_INT16);
    PyModule_AddIntConstant(fipy, "FIT_UINT32", FIT_UINT32);
    PyModule_AddIntConstant(fipy, "FIT_INT32", FIT_INT32);
    PyModule_AddIntConstant(fipy, "FIT_FLOAT", FIT_FLOAT);
    PyModule_AddIntConstant(fipy, "FIT_DOUBLE", FIT_DOUBLE);
    PyModule_AddIntConstant(fipy, "FIT_COMPLEX", FIT_COMPLEX);
    PyModule_AddIntConstant(fipy, "FIT_RGB16", FIT_RGB16);
    PyModule_AddIntConstant(fipy, "FIT_RGBA16", FIT_RGBA16);
    PyModule_AddIntConstant(fipy, "FIT_RGBF", FIT_RGBF);
    PyModule_AddIntConstant(fipy, "FIT_RGBAF", FIT_RGBAF);
    
    // Color type
    PyModule_AddIntConstant(fipy, "FIC_MINISWHITE", FIC_MINISWHITE);
    PyModule_AddIntConstant(fipy, "FIC_MINISBLACK", FIC_MINISBLACK);
    PyModule_AddIntConstant(fipy, "FIC_RGB", FIC_RGB);
    PyModule_AddIntConstant(fipy, "FIC_PALETTE", FIC_PALETTE);
    PyModule_AddIntConstant(fipy, "FIC_RGBALPHA", FIC_RGBALPHA);
    PyModule_AddIntConstant(fipy, "FIC_CMYK", FIC_CMYK);
    
    // Quamtize
    PyModule_AddIntConstant(fipy, "FIQ_WUQUANT", FIQ_WUQUANT);
    PyModule_AddIntConstant(fipy, "FIQ_NNQUANT", FIQ_NNQUANT);
    
    // Dither
    PyModule_AddIntConstant(fipy, "FID_FS", FID_FS);
    PyModule_AddIntConstant(fipy, "FID_BAYER4x4", FID_BAYER4x4);
    PyModule_AddIntConstant(fipy, "FID_BAYER8x8", FID_BAYER8x8);
    PyModule_AddIntConstant(fipy, "FID_CLUSTER6x6", FID_CLUSTER6x6);
    PyModule_AddIntConstant(fipy, "FID_CLUSTER8x8", FID_CLUSTER8x8);
    PyModule_AddIntConstant(fipy, "FID_CLUSTER16x16", FID_CLUSTER16x16);
    PyModule_AddIntConstant(fipy, "FID_BAYER16x16", FID_BAYER16x16);
    
    // JPEG operation
#if !defined(FEDORA_BUILD)
    PyModule_AddIntConstant(fipy, "FIJPEG_OP_NONE", FIJPEG_OP_NONE);
    PyModule_AddIntConstant(fipy, "FIJPEG_OP_FLIP_H", FIJPEG_OP_FLIP_H);
    PyModule_AddIntConstant(fipy, "FIJPEG_OP_FLIP_V", FIJPEG_OP_FLIP_V);
    PyModule_AddIntConstant(fipy, "FIJPEG_OP_TRANSPOSE", FIJPEG_OP_TRANSPOSE);
    PyModule_AddIntConstant(fipy, "FIJPEG_OP_TRANSVERSE", FIJPEG_OP_TRANSVERSE);
    PyModule_AddIntConstant(fipy, "FIJPEG_OP_ROTATE_90", FIJPEG_OP_ROTATE_90);
    PyModule_AddIntConstant(fipy, "FIJPEG_OP_ROTATE_180", FIJPEG_OP_ROTATE_180);
    PyModule_AddIntConstant(fipy, "FIJPEG_OP_ROTATE_270", FIJPEG_OP_ROTATE_270);
#endif
    
    // Tone mapping
    PyModule_AddIntConstant(fipy, "FITMO_DRAGO03", FITMO_DRAGO03);
    PyModule_AddIntConstant(fipy, "FITMO_REINHARD05", FITMO_REINHARD05);
    PyModule_AddIntConstant(fipy, "FITMO_FATTAL02", FITMO_FATTAL02);
    
    // Filters
    PyModule_AddIntConstant(fipy, "FILTER_BOX", FILTER_BOX);
    PyModule_AddIntConstant(fipy, "FILTER_BICUBIC", FILTER_BICUBIC);
    PyModule_AddIntConstant(fipy, "FILTER_BILINEAR", FILTER_BILINEAR);
    PyModule_AddIntConstant(fipy, "FILTER_BSPLINE", FILTER_BSPLINE);
    PyModule_AddIntConstant(fipy, "FILTER_CATMULLROM", FILTER_CATMULLROM);
    PyModule_AddIntConstant(fipy, "FILTER_LANCZOS3", FILTER_LANCZOS3);
    
    // Color channels
    PyModule_AddIntConstant(fipy, "FICC_RGB", FICC_RGB);
    PyModule_AddIntConstant(fipy, "FICC_RED", FICC_RED);
    PyModule_AddIntConstant(fipy, "FICC_GREEN", FICC_GREEN);
    PyModule_AddIntConstant(fipy, "FICC_BLUE", FICC_BLUE);
    PyModule_AddIntConstant(fipy, "FICC_ALPHA", FICC_ALPHA);
    PyModule_AddIntConstant(fipy, "FICC_BLACK", FICC_BLACK);
    PyModule_AddIntConstant(fipy, "FICC_REAL", FICC_REAL);
    PyModule_AddIntConstant(fipy, "FICC_IMAG", FICC_IMAG);
    PyModule_AddIntConstant(fipy, "FICC_MAG", FICC_MAG);
    PyModule_AddIntConstant(fipy, "FICC_PHASE", FICC_PHASE);
    
    // Metadata support
    PyModule_AddIntConstant(fipy, "FIDT_NOTYPE", FIDT_NOTYPE);
    PyModule_AddIntConstant(fipy, "FIDT_BYTE", FIDT_BYTE);
    PyModule_AddIntConstant(fipy, "FIDT_ASCII", FIDT_ASCII);
    PyModule_AddIntConstant(fipy, "FIDT_SHORT", FIDT_SHORT);
    PyModule_AddIntConstant(fipy, "FIDT_LONG", FIDT_LONG);
    PyModule_AddIntConstant(fipy, "FIDT_RATIONAL", FIDT_RATIONAL);
    PyModule_AddIntConstant(fipy, "FIDT_SBYTE", FIDT_SBYTE);
    PyModule_AddIntConstant(fipy, "FIDT_UNDEFINED", FIDT_UNDEFINED);
    PyModule_AddIntConstant(fipy, "FIDT_SSHORT", FIDT_SSHORT);
    PyModule_AddIntConstant(fipy, "FIDT_SLONG", FIDT_SLONG);
    PyModule_AddIntConstant(fipy, "FIDT_SRATIONAL", FIDT_SRATIONAL);
    PyModule_AddIntConstant(fipy, "FIDT_FLOAT", FIDT_FLOAT);
    PyModule_AddIntConstant(fipy, "FIDT_DOUBLE", FIDT_DOUBLE);
    PyModule_AddIntConstant(fipy, "FIDT_IFD", FIDT_IFD);
    PyModule_AddIntConstant(fipy, "FIDT_PALETTE", FIDT_PALETTE);
    
    PyModule_AddIntConstant(fipy, "FIMD_NODATA", FIMD_NODATA);
    PyModule_AddIntConstant(fipy, "FIMD_COMMENTS", FIMD_COMMENTS);
    PyModule_AddIntConstant(fipy, "FIMD_EXIF_MAIN", FIMD_EXIF_MAIN);
    PyModule_AddIntConstant(fipy, "FIMD_EXIF_EXIF", FIMD_EXIF_EXIF);
    PyModule_AddIntConstant(fipy, "FIMD_EXIF_GPS", FIMD_EXIF_GPS);
    PyModule_AddIntConstant(fipy, "FIMD_EXIF_MAKERNOTE", FIMD_EXIF_MAKERNOTE);
    PyModule_AddIntConstant(fipy, "FIMD_EXIF_INTEROP", FIMD_EXIF_INTEROP);
    PyModule_AddIntConstant(fipy, "FIMD_IPTC", FIMD_IPTC);
    PyModule_AddIntConstant(fipy, "FIMD_XMP", FIMD_XMP);
    PyModule_AddIntConstant(fipy, "FIMD_GEOTIFF", FIMD_GEOTIFF);
    PyModule_AddIntConstant(fipy, "FIMD_ANIMATION", FIMD_ANIMATION);
    PyModule_AddIntConstant(fipy, "FIMD_CUSTOM", FIMD_CUSTOM);
    
    // Load/Save flag constants
    PyModule_AddIntConstant(fipy, "BMP_DEFAULT", BMP_DEFAULT);
    PyModule_AddIntConstant(fipy, "BMP_SAVE_RLE", BMP_SAVE_RLE);
    PyModule_AddIntConstant(fipy, "CUT_DEFAULT", CUT_DEFAULT);
    PyModule_AddIntConstant(fipy, "DDS_DEFAULT", DDS_DEFAULT);
    PyModule_AddIntConstant(fipy, "EXR_DEFAULT", EXR_DEFAULT);
    PyModule_AddIntConstant(fipy, "EXR_FLOAT", EXR_FLOAT);
    PyModule_AddIntConstant(fipy, "EXR_NONE", EXR_NONE);
    PyModule_AddIntConstant(fipy, "EXR_ZIP", EXR_ZIP);
    PyModule_AddIntConstant(fipy, "EXR_PIZ", EXR_PIZ);
    PyModule_AddIntConstant(fipy, "EXR_PXR24", EXR_PXR24);
    PyModule_AddIntConstant(fipy, "EXR_B44", EXR_B44);
    PyModule_AddIntConstant(fipy, "EXR_LC", EXR_LC);
    PyModule_AddIntConstant(fipy, "FAXG3_DEFAULT", FAXG3_DEFAULT);
    PyModule_AddIntConstant(fipy, "GIF_DEFAULT", GIF_DEFAULT);
    PyModule_AddIntConstant(fipy, "GIF_LOAD256", GIF_LOAD256);
    PyModule_AddIntConstant(fipy, "GIF_PLAYBACK", GIF_PLAYBACK);
    PyModule_AddIntConstant(fipy, "HDR_DEFAULT", HDR_DEFAULT);
    PyModule_AddIntConstant(fipy, "ICO_DEFAULT", ICO_DEFAULT);
    PyModule_AddIntConstant(fipy, "ICO_MAKEALPHA", ICO_MAKEALPHA);
    PyModule_AddIntConstant(fipy, "IFF_DEFAULT", IFF_DEFAULT);
    PyModule_AddIntConstant(fipy, "J2K_DEFAULT", J2K_DEFAULT);
    PyModule_AddIntConstant(fipy, "JP2_DEFAULT", JP2_DEFAULT);
    PyModule_AddIntConstant(fipy, "JPEG_DEFAULT", JPEG_DEFAULT);
    PyModule_AddIntConstant(fipy, "JPEG_FAST", JPEG_FAST);
    PyModule_AddIntConstant(fipy, "JPEG_ACCURATE", JPEG_ACCURATE);
    PyModule_AddIntConstant(fipy, "JPEG_CMYK", JPEG_CMYK);
#if FREEIMAGE_MINOR_VERSION >= 12
    PyModule_AddIntConstant(fipy, "JPEG_EXIFROTATE", JPEG_EXIFROTATE);
#endif
    PyModule_AddIntConstant(fipy, "JPEG_QUALITYSUPERB", JPEG_QUALITYSUPERB);
    PyModule_AddIntConstant(fipy, "JPEG_QUALITYGOOD", JPEG_QUALITYGOOD);
    PyModule_AddIntConstant(fipy, "JPEG_QUALITYNORMAL", JPEG_QUALITYNORMAL);
    PyModule_AddIntConstant(fipy, "JPEG_QUALITYAVERAGE", JPEG_QUALITYAVERAGE);
    PyModule_AddIntConstant(fipy, "JPEG_QUALITYBAD", JPEG_QUALITYBAD);
    PyModule_AddIntConstant(fipy, "JPEG_PROGRESSIVE", JPEG_PROGRESSIVE);
#if FREEIMAGE_MINOR_VERSION >= 12
    PyModule_AddIntConstant(fipy, "JPEG_SUBSAMPLING_411", JPEG_SUBSAMPLING_411);
    PyModule_AddIntConstant(fipy, "JPEG_SUBSAMPLING_420", JPEG_SUBSAMPLING_420);
    PyModule_AddIntConstant(fipy, "JPEG_SUBSAMPLING_422", JPEG_SUBSAMPLING_422);
    PyModule_AddIntConstant(fipy, "JPEG_SUBSAMPLING_444", JPEG_SUBSAMPLING_444);
#endif
    PyModule_AddIntConstant(fipy, "KOALA_DEFAULT", KOALA_DEFAULT);
    PyModule_AddIntConstant(fipy, "LBM_DEFAULT", LBM_DEFAULT);
    PyModule_AddIntConstant(fipy, "MNG_DEFAULT", MNG_DEFAULT);
    PyModule_AddIntConstant(fipy, "PCD_DEFAULT", PCD_DEFAULT);
    PyModule_AddIntConstant(fipy, "PCD_BASE", PCD_BASE);
    PyModule_AddIntConstant(fipy, "PCD_BASEDIV4", PCD_BASEDIV4);
    PyModule_AddIntConstant(fipy, "PCD_BASEDIV16", PCD_BASEDIV16);
    PyModule_AddIntConstant(fipy, "PCX_DEFAULT", PCX_DEFAULT);
#if FREEIMAGE_MINOR_VERSION >= 12
    PyModule_AddIntConstant(fipy, "PFM_DEFAULT", PFM_DEFAULT);
#endif
    PyModule_AddIntConstant(fipy, "PNG_DEFAULT", PNG_DEFAULT);
    PyModule_AddIntConstant(fipy, "PNG_IGNOREGAMMA", PNG_IGNOREGAMMA);
#if FREEIMAGE_MINOR_VERSION >= 12
    PyModule_AddIntConstant(fipy, "PNG_Z_BEST_SPEED", PNG_Z_BEST_SPEED);
    PyModule_AddIntConstant(fipy, "PNG_Z_DEFAULT_COMPRESSION", PNG_Z_DEFAULT_COMPRESSION);
    PyModule_AddIntConstant(fipy, "PNG_Z_BEST_COMPRESSION", PNG_Z_BEST_COMPRESSION);
    PyModule_AddIntConstant(fipy, "PNG_Z_NO_COMPRESSION", PNG_Z_NO_COMPRESSION);
    PyModule_AddIntConstant(fipy, "PNG_INTERLACED", PNG_INTERLACED);
#endif
    PyModule_AddIntConstant(fipy, "PNM_DEFAULT", PNM_DEFAULT);
    PyModule_AddIntConstant(fipy, "PNM_SAVE_RAW", PNM_SAVE_RAW);
    PyModule_AddIntConstant(fipy, "PNM_SAVE_ASCII", PNM_SAVE_ASCII);
    PyModule_AddIntConstant(fipy, "PSD_DEFAULT", PSD_DEFAULT);
    PyModule_AddIntConstant(fipy, "RAS_DEFAULT", RAS_DEFAULT);
    PyModule_AddIntConstant(fipy, "SGI_DEFAULT", SGI_DEFAULT);
    PyModule_AddIntConstant(fipy, "TARGA_DEFAULT", TARGA_DEFAULT);
    PyModule_AddIntConstant(fipy, "TARGA_LOAD_RGB888", TARGA_LOAD_RGB888);
    PyModule_AddIntConstant(fipy, "TIFF_DEFAULT", TIFF_DEFAULT);
    PyModule_AddIntConstant(fipy, "TIFF_CMYK", TIFF_CMYK);
    PyModule_AddIntConstant(fipy, "TIFF_PACKBITS", TIFF_PACKBITS);
    PyModule_AddIntConstant(fipy, "TIFF_DEFLATE", TIFF_DEFLATE);
    PyModule_AddIntConstant(fipy, "TIFF_ADOBE_DEFLATE", TIFF_ADOBE_DEFLATE);
    PyModule_AddIntConstant(fipy, "TIFF_NONE", TIFF_NONE);
    PyModule_AddIntConstant(fipy, "TIFF_CCITTFAX3", TIFF_CCITTFAX3);
    PyModule_AddIntConstant(fipy, "TIFF_CCITTFAX4", TIFF_CCITTFAX4);
    PyModule_AddIntConstant(fipy, "TIFF_LZW", TIFF_LZW);
    PyModule_AddIntConstant(fipy, "TIFF_JPEG", TIFF_JPEG);
    PyModule_AddIntConstant(fipy, "WBMP_DEFAULT", WBMP_DEFAULT);
    PyModule_AddIntConstant(fipy, "XBM_DEFAULT", XBM_DEFAULT);
    PyModule_AddIntConstant(fipy, "XPM_DEFAULT", XPM_DEFAULT);
  }
}
