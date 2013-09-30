CXX=cl /nologo /EHsc /c /I. /O2 /WX /D_CRT_SECURE_NO_DEPRECATE /DNDEBUG
all: tiny_static.lib

tiny_static.lib:  string.obj iostream.obj
  lib /nologo string.obj iostream.obj /OUT:tiny_static.lib

string.obj: string.cpp string
   $(CXX) string.cpp

iostream.obj: iostream.cpp iostream
  $(CXX) iostream.cpp

clean:
  del *.obj *.lib

