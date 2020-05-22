/* NOMBRE:DAVID UZIEL GUEVARA HERNANDEZ
 * FECHA:05-04-2020
 * PROYECTO
 */

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#define TURNO_O 0
#define TURNO_X 1
#define true 1
#define false 0

struct Tablero{
  int turno;
  char tabla[8][8];
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
      } if (i == 9 && j == 9) {
        printf("╚════════╝");
      }
      if(i > 0 && j > 0 && i < 9 && j < 9){
	if (j-1 == cursor[0] && i-1 == cursor[1]) {
	  printf("#");
	} else {
	  printf("%c", tablero[j-1][i-1]);
	}
      }
    }
    printf("\n");
  }
}

int busquedaX(struct Tablero tablero, int direccion){
  int movimientoX = 0;
  char YO, ENEMIGO; //FICHAS DEL ENEMIGO Y PROPIAS, RESPECTIVAMENTE
  int cursor;
  if (tablero.turno == TURNO_O){
    YO = 'O';
    ENEMIGO = 'X';
  }
  if (tablero.turno == TURNO_X){
    YO = 'X';
    ENEMIGO = 'O';
  }
  for (int i = tablero.cursor[0]+direccion; i <= 8 && i >= -1; i+=direccion) {
    if (i == 8 || i == -1) {
      movimientoX = 0;
      break;
    }
    if (tablero.tabla[i][tablero.cursor[1]] == ENEMIGO){
      movimientoX++;
    } else{
      if (tablero.tabla[i][tablero.cursor[1]] == YO) {
	break;
      } else if(tablero.tabla[i][tablero.cursor[1]] == ' '){
	movimientoX = 0;
	break;
      } else{
	movimientoX = 0;
	break;
      }
    }
  }
  return movimientoX;
}

int busquedaY(struct Tablero tablero, int direccion){
  int movimientoY = 0;
  char YO, ENEMIGO; //FICHAS DEL ENEMIGO Y PROPIAS, RESPECTIVAMENTE
  if (tablero.turno == TURNO_O){
    YO = 'O';
    ENEMIGO = 'X';
  }
  if (tablero.turno == TURNO_X){
    YO = 'X';
    ENEMIGO = 'O';
  }
  for (int i = tablero.cursor[1]+direccion;i <= 8 && i >= -1; i+=direccion) {
    if (i == 8 || i == -1) {
      movimientoY = 0;
      break;
    }
    if (tablero.tabla[tablero.cursor[0]][i] == ENEMIGO){
      movimientoY++;
    } else {
      if (tablero.tabla[tablero.cursor[0]][i] == YO) {
	break;
      } else if(tablero.tabla[tablero.cursor[0]][i] == ' '){
	movimientoY = 0;
	break;
      } else{
	movimientoY = 0;
	break;
      }
    }
  }
  return movimientoY;
}

int buscarDiagonal(struct Tablero tablero, int direccionX, int direccionY){
  int movimientoXY = 0;
  int cursorX = tablero.cursor[0];
  int cursorY = tablero.cursor[1];
  char YO, ENEMIGO; //FICHAS DEL ENEMIGO Y PROPIAS, RESPECTIVAMENTE
  if (tablero.turno == TURNO_O){
    YO = 'O';
    ENEMIGO = 'X';
  }
  if (tablero.turno == TURNO_X){
    YO = 'X';
    ENEMIGO = 'O';
  }
  int i = cursorX+direccionX;
  int j = cursorY+direccionY;
  while((i<=8 && i >= -1)&&(j<=8 && j>=-1)){
    if (i == 8 || j == -1){
      movimientoXY = 0;
      break;
    }
    if (tablero.tabla[i][j] == ENEMIGO){
      movimientoXY++;
    } else {
      if (tablero.tabla[i][j] == YO) {
	break;
      } else if(tablero.tabla[i][j] == ' '){
	movimientoXY = 0;
	break;
      } else{
	movimientoXY = 0;
	break;
      }
    }
    i+=direccionX;
    j+=direccionY;
  }
  return movimientoXY;
}

int toggleTurno(int turnoActual){
  if (turnoActual == TURNO_O) return TURNO_X;
  else return TURNO_O;
}

struct Tablero buscarReemplazar(struct Tablero tablero){
  const int ADELANTE = 1;
  const int ATRAS = -1;
  char YO;
  if (tablero.turno == TURNO_O) YO = 'O';
  if (tablero.turno == TURNO_X) YO = 'X';

  int i = 0, j = 0;
  int flagMovimientoValido = false;
  int cursorX = tablero.cursor[0];
  int cursorY = tablero.cursor[1]; 
  int incrementoX = busquedaX(tablero, ADELANTE);
  int decrementoX = busquedaX(tablero, ATRAS);
  int incrementoY = busquedaY(tablero, ADELANTE);
  int decrementoY = busquedaY(tablero, ATRAS);
  int diagonalPP = buscarDiagonal(tablero, ADELANTE, ADELANTE);
  int diagonalPN = buscarDiagonal(tablero, ADELANTE, ATRAS);
  int diagonalNP = buscarDiagonal(tablero, ATRAS, ADELANTE);
  int diagonalNN = buscarDiagonal(tablero, ATRAS, ATRAS);
  if (incrementoX > 0) {
    for (int i = cursorX; i <= cursorX+incrementoX; ++i) {
      tablero.tabla[i][cursorY] = YO;
    }
    flagMovimientoValido = true;
  }
  if (decrementoX > 0) {
    for (int i = cursorX; i >= cursorX-decrementoX; --i) {
      tablero.tabla[i][cursorY] = YO;
    }
    flagMovimientoValido = true;
  }
  if (incrementoY > 0) {
    for (int i = cursorY; i <= cursorY+incrementoY; ++i) {
      tablero.tabla[cursorX][i] = YO;
    }
    flagMovimientoValido = true;
  }
  if (decrementoY > 0) {
    for (int i = cursorY; i >= cursorY-decrementoY; --i) {
      tablero.tabla[cursorX][i] = YO;
    }
    flagMovimientoValido = true;
  }
  if (diagonalPP > 0) {
    i = cursorX;
    j = cursorY;
    while ((i<=cursorX+diagonalPP)&&(j<=cursorY+diagonalPP)){
      tablero.tabla[i][j] = YO;
      i++;
      j++;
    }
    flagMovimientoValido = true;
  }
  if (diagonalNP > 0) {
    i = cursorX;
    j = cursorY;
    while ((i>=cursorX-diagonalNP)&&(j<=cursorY+diagonalNP)){
      tablero.tabla[i][j] = YO;
      i--;
      j++;
    }
    flagMovimientoValido = true;
  }
  if (diagonalPN > 0) {
    i = cursorX;
    j = cursorY;
    while ((i<=cursorX+diagonalPN)&&(j>=cursorY-diagonalPN)){
      tablero.tabla[i][j] = YO;
      i++;
      j--;
    }
    flagMovimientoValido = true;
  }
  if (diagonalNN > 0) {
    i = cursorX;
    j = cursorY;
    while ((i>=cursorX-diagonalNN)&&(j>=cursorY-diagonalNN)){
      tablero.tabla[i][j] = YO;
      i--;
      j--;
    }
    flagMovimientoValido = true;
  }
  if(flagMovimientoValido == true) tablero.turno = toggleTurno(tablero.turno);
  return tablero;
}

struct Tablero realizarJugada(struct Tablero tablero){
  // "Si estas encima de una ficha, no hagas nada"
  if (tablero.tabla[tablero.cursor[0]][tablero.cursor[1]] == 'X')  return tablero; 
  if (tablero.tabla[tablero.cursor[0]][tablero.cursor[1]] == 'O')  return tablero;
  tablero = buscarReemplazar(tablero);
  return tablero;
}

void end(struct Tablero tablero) {
  int fichaO = 0;
  int fichaX = 0;
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      if(tablero.tabla[i][j] == 'O'){
	fichaO++;
      }
      if (tablero.tabla[i][j] == 'X') {
        fichaX++;
      }
    }
  }
  system("cls");
  if (fichaO > fichaX) {
    printf("FELICIDADES \'O\' GANASTE\n");
  }
  if (fichaX > fichaO) {
    printf("FELICIDADES \'X\' GANASTE\n");
  }
  if (fichaX == fichaO) {
    printf("EMPATARON\n");
  }
  printf("PRESIONA ENTER PARA CONTINUAR\n");
  getchar();
  getchar();
}

int juego(){
  setlocale(LC_ALL, "es_ES");
  int indiceO = 0;
  int fin = 0;
  char opc; 
  tablero.turno = TURNO_O;
  for (int i = 0; i < 9; ++i) { // se llena el tablero de espacios en blanco
    for (int j = 0; j < 9; ++j) {
      tablero.tabla[i][j] = ' ';
    }
  }
  tablero.tabla[3][3] = 'X'; //Se pone en el tablero las piezas iniciales
  tablero.tabla[4][4] = 'X';
  tablero.tabla[3][4] = 'O';
  tablero.tabla[4][3] = 'O';
  tablero.cursor[0] = 0;
  tablero.cursor[1] = 0;
  while (opc != 'q') {
    system("cls");
    if (tablero.turno == TURNO_O) { // Aqui solo se imprime de quien es el turno
      printf("TURNO DE O\n");
    } else {
      printf("TURNO DE X\n");
    }
    dibujarTablero(tablero.tabla, tablero.cursor);
    printf("mover:w(arriba),a(izquierda),s(abajo),d(derecha), seleccionar:e, salir:q\n");
    scanf(" %c", &opc);
    switch(opc){ //Este switch controla el movimiento del cursor
      case 'a':
	if (tablero.cursor[0] > 0) {
	  tablero.cursor[0]--;
	}
	break;
      case 'd':
	if (tablero.cursor[0] < 7) {
	  tablero.cursor[0]++;
	}
	break;
      case 's':
	if (tablero.cursor[1] < 7) {
	  tablero.cursor[1]++;
	}
	break;
      case 'w':
	if (tablero.cursor[1] > 0) {
	  tablero.cursor[1]--;
	}
	break;
      case 'e':
	tablero = realizarJugada(tablero);
	break;
      case 'q':
	printf("Esta seguro de que desea terminar? (s/n)\n");
	scanf(" %c", &opc);
	if (opc == 's' || opc == 'S') {
	  opc = 'q';
	  end(tablero);
	  break;
	} else {
	  opc = ' ';
	  break;
	}
	break;
      default:break;
    }
  }
  return 0;
}

void instrucciones() {
  system("cls");
  printf("El juego se controla utilizando un cursor en forma de #\n");
  printf("cada jugador tiene fichas (O o X)\n");
  printf("el objetivo del juego es convertir las fichas de tu oponente en tus fichas\n");
  printf("para convertir fichas enemigas, debes de posicionar con el cursor una nueva ficha\n");
  printf("adyacente a una ficha enemiga\n");
  printf("que componga una linea (horizontal, vertical o diagonal) que atraviese fichas");
  printf("enemigas, empezando con la nueva ficha\n");
  printf("y finalizando con una ficha tuya existente, despues, se pasara el turno al otro jugador\n");
  printf("TURNO O          TURNO X \n");
  printf("1.      2.       3.       4.  \n");
  printf("                 #        X   \n");
  printf("#XO     OOO      OOO      OXO \n");
  printf(" OX      OX       OX       OX \n");
  printf("                              \n");
  printf("El turno solo se pasa si realizas una jugada valida\n");
  getchar();
  getchar();
}

int main(){
  int opc = 0;
  while(opc != 3){
    system("cls");
    printf("MENU\n");
    printf("1. Jugar\n");
    printf("2. Como Jugar?\n");
    printf("3. Salir\n");
    scanf("%i", &opc);
    switch(opc){
      case 1:
	juego();
	break;
      case 2:
	instrucciones();
	break;
      case 3:
	break;
      default:break;
    }
  }
  return 0;
}
