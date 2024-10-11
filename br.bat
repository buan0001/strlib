@echo off
gcc -c *.c
gcc -o runnable *.o
rm *.o
.\runnable.exe
