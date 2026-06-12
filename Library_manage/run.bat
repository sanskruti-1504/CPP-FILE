@echo off
set PATH=C:\bin;%PATH%
gcc -c sqlite3.c -o sqlite3.o -ID:\Git\Library_manage -DSQLITE_WIN32_GETVERSIONEX=0
g++ Library.cpp sqlite3.o -o library.exe -ID:\Git\Library_manage -lws2_32
library.exe