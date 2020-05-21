/* NOMBRE:DAVID UZIEL GUEVARA HERNANDEZ
 * FECHA:05-04-2020
 * PROYECTO
 */

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#define TURNO_O 0
#define TURNO_X 1

struct Tablero{
  char tabla[8][8];
  char fichasO[64][2];
  char fichasX[64][2];
  int cursor[2];
}tablero; 

void dibujarTablero(char tablero[8][8], int cursor[2]){ //aqui se dibuja el tablero gg
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      if (i == 0 && j == 0){
	printf("╔════════╗");
      }
      if (i < 9){
	if ((i != 0 && j == 0) || (i != 0 && j == 9)){
	  printf("║");
	}
      }
      if (i == 9 && j == 9) {
        printf("╚════════╝");
      }
      if(i > 0 && j > 0 && i < 9 && j < 9){
	if (i-1 == cursor[0] && j-1 == cursor[1]) {
	  printf("#");
	} else {
	  
	printf("%c", tablero[i-1][j-1]);
	}
      }
    }
    printf("\n");
  }
}

struct Tablero realizarJugada(struct Tablero tablero){
  int cursor[2] = *tablero.cursor;
  return tablero;
}

int main(){
  setlocale(LC_ALL, "es_ES");
  int indiceO = 0;
  int fin = 0;
  char opc; 
  int turno = TURNO_O;
  tablero.cursor[0] = 0;
  tablero.cursor[1] = 0;
  for (int i = 0; i < 9; ++i) { // se llena el tablero de espacios en blanco
    for (int j = 0; j < 9; ++j) {
      tablero.tabla[i][j] = ' ';
    }
  }
  char especial;
  tablero.tabla[3][3] = 'X'; //Se pone en el tablero las piezas iniciales
  tablero.tabla[4][4] = 'X';
  tablero.tabla[3][4] = 'O';
  tablero.tabla[4][3] = 'O';
  while (opc != 'q') {
    system("cls");
    if (turno == TURNO_O) { // Aqui solo se imprime de quien es el turno
      printf("TURNO DE O\n");
    } else {
      printf("TURNO DE X\n");
    }
    dibujarTablero(tablero.tabla, tablero.cursor);
    printf("mover:wasd, seleccionar:e, salir:q\n");
    scanf(" %c", &opc);
    switch(opc){ //Este switch controla el movimiento del cursor
      case 's':
	if (tablero.cursor[0] < 7) {
	  tablero.cursor[0]++;
	}
	break;
      case 'w':
	if (tablero.cursor[0] > 0) {
	  tablero.cursor[0]--;
	}
	break;
      case 'a':
	if (tablero.cursor[1] > 0) {
	  tablero.cursor[1]--;
	}
	break;
      case 'd':
	if (tablero.cursor[1] < 7) {
	  tablero.cursor[1]++;
	}
	break;
      case 'e':
	tablero = realizarJugada(tablero);
      case 'q':
	break;
      default:break;
    }
  }
  return 0;
}
