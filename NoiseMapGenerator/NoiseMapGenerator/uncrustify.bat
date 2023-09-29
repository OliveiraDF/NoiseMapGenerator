@echo off
set UNC_PATH=uncrustify.exe
set UNC_CFG=ben.cfg
for /r %%i in (*.cpp *.h) do "%UNC_PATH%" -c "%UNC_CFG%" -f "%%i" -o "%%i"