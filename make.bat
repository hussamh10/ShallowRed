@echo off
cd /d %~dp0
cd Chess
g++ -Wl,armadillo\lib_win64\blas_win64_MT.lib,armadillo\lib_win64\lapack_win64_MT.lib -Iarmadillo\include *.cpp -std=c++11 -o Chess.exe
md ..\Out
move Chess.exe ..\Out
xcopy armadillo\lib_win64\*.dll ..\Out
