timethis "cl /nologo /EHsc /MD ohello.cpp"
copy ohello.exe mhello1.exe
dir mhello1.exe
timethis "cl /nologo /EHsc ohello.cpp"
copy ohello.exe mhello2.exe
dir mhello2.exe
timethis "cl /nologo /EHsc /Itiny ohello.cpp tiny\tiny_static.lib"
copy ohello.exe mhello3.exe
dir mhello3.exe

