// Tarea1_Programacion_Pararela_A01794465.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <omp.h>
#include <math.h>

#define N 10000         // Cantidad de elementos en el arreglo
#define chunk 100       // Cantidad de secciones a procesar por cada hilo
#define mostrar 10      // Cantidad de datos a visualizar

void imprimeArreglo(float* d);      // Prototipo de función para visualizar datos

int main()
{
    // Verificar que OPENMP está en funcionamiento
    std::cout << "--- Verificando la ejecucion de las directivas OMP ---\n\n";

    // Si OPENMP está activo se imprime el mensaje OMP disponible y funcionando
    #ifdef _OPENMP
        std::cout << "--- OMP disponible y funcionando ---\n" << std::endl;
    #endif 

    std::cout << "--- Sumando arreglos en paralelo --- \n\n";
    float a[N], b[N], c[N];
    int i;


    // Crear los arreglos a y b de forma aleatoria
    for (i = 0; i < N; i++)
    {
        a[i] = i*i* 5.2;
        b[i] = 10 * sin(3 * i);
    }
    int pedazos = chunk;

    // Indicar que la instruccion for se ejecuta en paralelo
    // Se indica que los arreglos estan en el área de memoria compartida y el tamaño de los pedazos
    // que cada hilo tomara del arreglo principal
    // Se indica que la variable i es privada, para que los arreglos con confundan dicha variable
    // Se indica la planificación como estática y el tamaño de cada planificación de hilo
    #pragma omp parallel for \
        shared(a,b,c,pedazos) \
        private(i) \
        schedule(static,pedazos)

    for (i = 0; i < N; i++)
        c[i] = a[i] + b[i];

    // Imprimir los 10 primeros valores del arreglo a
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a:" << std::endl;
    imprimeArreglo(a);
    // Imprimir los 10 primeros valores del arreglo b
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b:" << std::endl;
    imprimeArreglo(b);
    // Imprimir los 10 primeros valores de la suma de a y b
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c:" << std::endl;
    imprimeArreglo(c);
    
}

// Funcion para imrpimir los primeros elementos del arreglo
void imprimeArreglo(float* d)
{
    for (int x = 0; x < mostrar; x++)
        std::cout << d[x] << ", ";
    std::cout <<"\n" << std::endl;
}
