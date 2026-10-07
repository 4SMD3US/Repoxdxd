#include <iostream>   // Para std::cout (salida por consola)
#include <string>     // Para std::string (cadenas de texto)
#include <utility>    // Para std::move (mover objetos en vez de copiarlos)

#ifdef _WIN32         // Si se compila en Windows...
#include <windows.h>  // ...incluye la API de Windows (necesaria para SetConsoleOutputCP)
#endif                // Fin del bloque condicional

// ============================================
// ARMA
// ============================================

class Arma                                                  // Define la clase Arma
{
public:                                                     // Lo siguiente es accesible desde fuera de la clase
    Arma(std::string nombre, int danio)                     // Constructor: recibe nombre y daño
        : nombre(std::move(nombre)), danio(danio) {}        // Lista de inicialización: asigna los atributos (el nombre se mueve, no se copia)

    void atacar() const                                     // Método de ataque; 'const' = no modifica el objeto
    {
        std::cout << "⚔️ Ataque con " << nombre << ": "     // Imprime el texto fijo y el nombre del arma
                  << danio << " puntos de daño\n";          // Imprime el daño y salta de línea
    }

    int getDanio() const { return danio; }                  // Getter del daño (devuelve una copia del entero)
    const std::string& getNombre() const { return nombre; } // Getter del nombre (devuelve referencia constante, evita copiar el texto)

private:                                                    // Lo siguiente solo es accesible dentro de la clase
    std::string nombre;                                     // Atributo: nombre del arma
    int danio;                                              // Atributo: puntos de daño del arma
};                                                          // Fin de la clase (en C++ lleva punto y coma)

// ============================================
// HABILIDAD
// ============================================

class Habilidad                                             // Define la clase Habilidad
{
public:                                                     // Sección pública
    Habilidad(std::string nombre, int poder)                // Constructor: recibe nombre y poder
        : nombre(std::move(nombre)), poder(poder) {}        // Inicializa los atributos con la lista de inicialización

    void usar() const                                       // Método para usar la habilidad; no modifica el objeto
    {
        std::cout << "✨ Se utiliza " << nombre << ": "     // Imprime el texto fijo y el nombre de la habilidad
                  << poder << " puntos de poder\n";         // Imprime el poder y salta de línea
    }

    const std::string& getNombre() const { return nombre; } // Getter del nombre (referencia constante)

private:                                                    // Sección privada
    std::string nombre;                                     // Atributo: nombre de la habilidad
    int poder;                                              // Atributo: puntos de poder
};                                                          // Fin de la clase

// ============================================
// PERSONAJE (composición: contiene un Arma y una Habilidad)
// ============================================

class Personaje                                             // Define la clase Personaje
{
public:                                                     // Sección pública
    Personaje(std::string nombre, int vida, Arma arma, Habilidad habilidad) // Constructor: recibe nombre, vida, arma y habilidad (arma y habilidad llegan por valor, es decir, copiadas)
        : nombre(std::move(nombre)),                        // Inicializa el nombre (movido)
          vida(vida),                                       // Inicializa la vida
          arma(std::move(arma)),                            // Inicializa el arma (movida desde el parámetro)
          habilidad(std::move(habilidad)) {}                // Inicializa la habilidad (movida desde el parámetro)

    void atacar() const                                     // Método de ataque del personaje
    {
        std::cout << nombre << " ataca:\n";                 // Imprime quién ataca
        arma.atacar();                                      // Delega el ataque en el arma que tiene
    }

    void usarHabilidad() const                              // Método para usar la habilidad
    {
        std::cout << nombre << " utiliza una habilidad:\n"; // Imprime quién usa la habilidad
        habilidad.usar();                                   // Delega en la habilidad que tiene
    }

    void cambiarArma(const Arma& nuevaArma)                 // Cambia el arma; recibe referencia constante (sin copiar al pasar)
    {
        arma = nuevaArma;                                   // Reemplaza el arma actual por una copia de la nueva
        std::cout << nombre << " ahora utiliza "            // Imprime quién cambió de arma...
                  << nuevaArma.getNombre() << "\n";         // ...y el nombre de la nueva arma
    }

    void recibirDanio(int danio)                            // Resta vida al personaje (modifica el objeto, por eso no es const)
    {
        vida -= danio;                                      // Resta el daño recibido a la vida (puede quedar negativa)
        std::cout << nombre << " recibió " << danio << " puntos de daño.\n"; // Informa el daño recibido
        std::cout << "Vida restante: " << vida << "\n";     // Informa la vida actual
    }

private:                                                    // Sección privada
    std::string nombre;                                     // Atributo: nombre del personaje
    int vida;                                               // Atributo: puntos de vida
    Arma arma;                                              // Atributo: arma (guardada por valor, el personaje tiene su propia copia)
    Habilidad habilidad;                                    // Atributo: habilidad (también por valor)
};                                                          // Fin de la clase

// ============================================
// MAIN
// ============================================

int main()                                                  // Punto de entrada del programa
{
#ifdef _WIN32                                               // Solo se compila este bloque en Windows
    // La consola de Windows usa por defecto una página de códigos antigua
    // (437/850), no UTF-8. Esto la cambia para este programa.
    SetConsoleOutputCP(CP_UTF8);                            // Configura la salida de la consola en UTF-8
#endif                                                      // Fin del bloque condicional

    // Armas
    Arma espada("Espada de fuego", 30);                     // Crea el arma "espada" con 30 de daño
    Arma arco("Arco mágico", 20);                           // Crea el arma "arco" con 20 de daño

    // Habilidades
    Habilidad curacion("Curación", 25);                     // Crea la habilidad "curación" con poder 25
    Habilidad escudo("Escudo mágico", 15);                  // Crea la habilidad "escudo" con poder 15

    // Composición
    Personaje guerrero("Guerrero", 100, espada, curacion);  // Crea al guerrero con 100 de vida (recibe copias de espada y curación)

    // Jugamos
    guerrero.atacar();                                      // El guerrero ataca con la espada
    guerrero.usarHabilidad();                               // El guerrero usa curación
    guerrero.recibirDanio(20);                              // El guerrero recibe 20 de daño (vida: 100 -> 80)

    // Cambiamos el arma
    guerrero.cambiarArma(arco);                             // El guerrero cambia la espada por el arco
    guerrero.atacar();                                      // El guerrero ataca ahora con el arco

    // Otro personaje
    Personaje arquero("Arquero", 80, arco, escudo);         // Crea al arquero con 80 de vida, arco y escudo
    arquero.atacar();                                       // El arquero ataca con el arco
    arquero.usarHabilidad();                                // El arquero usa el escudo mágico

    return 0;                                               // Indica al sistema que el programa terminó sin errores
}                                                           // Al salir de main, los objetos se destruyen solos (sin delete manual)