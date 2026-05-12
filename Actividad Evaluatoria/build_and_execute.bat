::compilo el binario
g++ -std=c++17 -Wall -Wpedantic -Werror -I.\include main.cpp src\*.cpp -o actividadEvaluatoria.exe
::limpio los codigos objetos
DEL.*.o
::ejecuto el programa
actividadEvaluatoria.exe