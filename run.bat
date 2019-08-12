@echo off
del .\bin\Nula-Lilio.exe
C:\MingW\bin\g++.exe .\src\main.cpp -IC:\Software\SDL2\i686-w64-mingw32\include\SDL2 -LC:\Software\SDL2\i686-w64-mingw32\lib -w -lmingw32 -lSDL2main -lSDL2 -lSDL2_Image -lSDL2_ttf  -static-libstdc++ -g -o bin\Nula-Lilio
REM  -Wl,-subsystem,windows
.\bin\Nula-Lilio.exe
