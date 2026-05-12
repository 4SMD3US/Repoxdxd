#include "menues.hpp"
#include "consola.hpp"
#include "operaciones.hpp"
#include <iostream>

using namespace std;

void mostrarMenuPrincipal()
{
    int opcion;
    bool repetir = true;

    do
    {
        clearConsole();

        cout << "\n\n\t\t\tMENU PRINCIPAL" << endl;
        cout << "\t\t\t--------------" << endl;
        cout << "\n\t1. Operaciones basicas" << endl;
        cout << "\t2. Operaciones variadas" << endl;
        cout << "\t0. SALIR" << endl;

        cout << "\n\tIngrese una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
            case 1:
                mostrarMenuOperacionesBasicas();
                break;

            case 2:
                mostrarMenuOperacionesVariadas();
                break;

            case 0:
                repetir = false;
                break;
        }
    } while (repetir);
}

// Definiciones de las funciones
void mostrarMenuOperacionesBasicas()
{
    int opcion;
    bool repetir = true;

    do
    {
        clearConsole();

        cout << "\n\n\t\t\tMENU OPERACIONES BASICAS" << endl;
        cout << "\t\t\t------------------------" << endl;
        cout << "\n\t1. Sumar" << endl;
        cout << "\t2. Restar" << endl;
        cout << "\t3. Multiplicar" << endl;
        cout << "\t4. Dividir" << endl;
        cout << "\t0. REGRESAR" << endl;

        cout << "\n\tIngrese una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
            case 1:
                sumar();
                break;

            case 2:
                restar();
                break;

            case 3:
                multiplicar();
                break;

            case 4:
                dividir();
                break;

            case 0:
                repetir = false;
                break;
        }
    } while (repetir);
}

void mostrarMenuOperacionesVariadas()
{
    int opcion;
    bool repetir = true;

    do
    {
        clearConsole();

        cout << "\n\n\t\t\tMENU OPERACIONES VARIADAS" << endl;
        cout << "\t\t\t-------------------------" << endl;
        cout << "\n\t1. Numero y dia" << endl;
        cout << "\t2. Suma de los primeros n numeros naturales" << endl;
        cout << "\t3. Factorial de un numero" << endl;
        cout << "\t4. Invertir un numero de 4 cifras" << endl;
        cout << "\t0. REGRESAR" << endl;

        cout << "\n\tIngrese una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
            case 1:
                convertirNumeroADia();
                break;

            case 2:
                sumarPrimerosNumeros();
                break;

            case 3:
                factorial();
                break;

            case 4:
                invertirNumero4Cifras();
                break;

            case 0:
                repetir = false;
                break;
        }
    } while (repetir);
}