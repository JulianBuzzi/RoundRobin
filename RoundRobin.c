#include <stdio.h>
#include <stdlib.h>

#define CANTIDAD 5

struct PCB {
  int PID;
  int TS;
};

void roundRobin(struct PCB L[], int Q) {
    int ti = Q / 4; // Tiempo de intercambio
    int r = 0;      // Reloj
    int sumatoria = 0; // Sumatoria de TS
    struct PCB pAnt = {0, 0}; // Proceso anterior
    int *tiemposDeRetorno = (int *)calloc(CANTIDAD, sizeof(int));
    int *tiemposDeEspera = (int*)calloc(CANTIDAD, sizeof(int));

    for (int i = 0; i < CANTIDAD; i++) {
        sumatoria += L[i].TS;
        tiemposDeEspera[i] = L[i].TS;
    }

    while (sumatoria > 0) {
        for (int i = 0; i < CANTIDAD; i++) {
            if (L[i].TS > 0) {
                if (pAnt.TS != 0 && pAnt.PID != L[i].PID) {
                    r = r + (ti / 2);
                }

                int tiempoEjecucion = (L[i].TS > Q) ? Q : L[i].TS;
                L[i].TS -= tiempoEjecucion;
                r += tiempoEjecucion;
                sumatoria -= tiempoEjecucion;

                tiemposDeRetorno[i] = r; 

                printf("L[%d], R: %d - TS: %d - Tiempo de Retorno: %d\n", L[i].PID, r, L[i].TS, tiemposDeRetorno[i]);
                pAnt = L[i]; 
            }
        }
    }
    float sumaPromedio = 0;
    float sumaEspera = 0;
    for (int i = 0; i < CANTIDAD; i++){
      sumaPromedio += tiemposDeRetorno[i];
      sumaEspera += (tiemposDeRetorno[i] - tiemposDeEspera[i]);
    }

    printf("El promedio de todos los tiempos de retorno es: %.2f\n", sumaPromedio/CANTIDAD);
    printf("El promedio de todos los tiempos de espera es: %.2f\n", sumaEspera/CANTIDAD);
    free(tiemposDeRetorno);
}


int main(){
  struct PCB round[CANTIDAD] = {
    {1, 8}, {3, 1}, {5, 6}, {4, 9}, {2, 4}
  };

  roundRobin(round, 3);
  return 0;
}