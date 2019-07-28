@echo off
del .\bin\Nula-Lilio.exe
C:\MingW\bin\g++.exe .\src\main.cpp -IC:\Software\SDL2\i686-w64-mingw32\include\SDL2 -LC:\Software\SDL2\i686-w64-mingw32\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -lSDL2_Image -lSDL2_ttf -o bin\Nula-Lilio
.\bin\Nula-Lilio.exe
