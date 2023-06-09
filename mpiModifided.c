#include <mpi.h>
#include <stdio.h>
#include <string.h>

#define MESSTAG 0
#define MAXLEN 100

int main(int argc, char **argv) {
  //----(1) INICIO DEL ENTORNO----//
  MPI_Init(&argc, &argv);

  //----(2) CAPTURA DE DATOS DEL COMUNICADOR----//
  int rank, num;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num);

  //----(3) PARTE 3 DISTRIBUCION DEL TRABAJO----//
  if (rank % 2 == 0) {
    char mess[] = "Hello Andres Emilio Quinto 18288";
    printf("%i sent %s\n", rank, mess);
    MPI_Send(mess, strlen(mess) + 1, MPI_CHAR, rank + 1, MESSTAG, MPI_COMM_WORLD);
  } else {
    char mess[MAXLEN];
    MPI_Status status;
    MPI_Recv(mess, MAXLEN, MPI_CHAR, rank - 1, MESSTAG, MPI_COMM_WORLD, &status);
    printf("%i received %s\n", rank, mess);
  }

  //----(4) FINALIZACION DEL ENTORNO----//
  MPI_Finalize();
  return 0;
}
