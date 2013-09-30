all: ohello.exe

ohello.exe:  ohello.obj tiny/tiny_static.lib
	link /nologo ohello.obj /LIBPATH:tiny tiny_static.lib /OUT:ohello.exe

ohello.obj: ohello.cpp
	cl /nologo /EHsc -c /O2 /WX /Itiny  /D_CRT_SECURE_NO_DEPRECATE /DNDEBUG ohello.cpp

clean:
	del ohello.exe ohello.obj

