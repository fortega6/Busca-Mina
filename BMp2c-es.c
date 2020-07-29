#include <stdio.h>
#include <termios.h>    //termios, TCSANOW, ECHO, ICANON
#include <unistd.h>     //STDIN_FILENO

/**
 * Constantes
 */
#define DimMatrix  10     //dimensión de la matriz
#define SizeMatrix DimMatrix*DimMatrix //=100

extern int developer;	//Variable declarada en ensamblador que indica el nombre del programador.

/**
 * Definición de variables globales
 */
// Matriz 10x10 donde ponemos las minas (Hay 20 minas marcadas)
char mines[DimMatrix][DimMatrix] = { {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                                     {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                                     {' ','*',' ',' ',' ',' ',' ',' ',' ',' '},
                                     {' ',' ',' ','*',' ','*',' ',' ',' ',' '},
                                     {' ','*','*','*','*','*','*','*',' ',' '},
                                     {' ',' ',' ','*',' ','*',' ',' ',' ',' '},
                                     {' ',' ','*','*','*','*','*','*',' ',' '},
                                     {' ',' ',' ','*',' ',' ',' ',' ',' ',' '},
                                     {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                                     {' ',' ',' ',' ',' ',' ',' ',' ',' ','*'} };

// Matriz 10x10 donde se indican las minas marcadas 'M'(Hay 2 minas marcadas)
// y el número de minas de las posiciones abiertas.(Hay 4 posiciones abiertas)              
char marks[DimMatrix][DimMatrix] = { {'0',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                                     {'1',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                                     {'1','M',' ',' ',' ',' ',' ',' ',' ',' '},
                                     {'2',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                                     {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                                     {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                                     {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                                     {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                                     {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                                     {' ',' ',' ',' ',' ',' ',' ',' ',' ','M'} };

           
/**
 * Definición de las subrutinas de ensamblador que se llaman desde C
 */
extern char printMenuP2();
extern void printBoardP2();

extern void posCurScreenP2(int[2]);
extern void showMinesP2(int);
extern void updateBoardP2(int);

extern void moveCursorP2(int[2], char);
extern int  calcIndexP2(int[2]);
extern int  mineMarkerP2(int[2], int);
extern int  searchMinesP2(int[2], int);
extern int  checkEndP2(int, int);
extern int  playP2(int);

/**
 * Definición de las funciones de C
 */
void clearscreen_C();
void gotoxyP2_C(int, int);
void printchP2_C(char);
char getchP2_C();

char printMenuP2_C();
void printBoardP2_C();

void posCurScreenP2_C(int[2]);
void showMinesP2_C(int);
void updateBoardP2_C(int);

void moveCursorP2_C(int[2], char);
int  mineMarkerP2_C(int[2], int);
int  searchMinesP2_C(int[2], int);
int  checkEndP2_C(int, int);

void printMessageP2_C(int);
int  playP2_C(int);


/**
 * Borrar la pantalla
 * 
 * Variables globales utilizadas:	
 * Ninguna
 * 
 * Parámetros de entrada: 
 * Ninguno
 *   
 * Parámetros de salida : 
 * Ninguno
 * 
 * Esta función no es llama desde ensamblador
 * y no hay definida una subrutina de ensamblador equivalente.
 */
void clearScreen_C(){
	
    printf("\x1B[2J");
    
}


/**
 * Situar el cursor en una fila y una columna de la pantalla
 * en función de la fila (rowCurScreen) y de la columna (colCurScreen) 
 * recibidos como parámetro.
 * 
 * Variables globales utilizadas:	
 * Ninguna
 * 
 * Parámetros de entrada: 
 * rowCurScreen  : rdi(edi): Fila
 * colCurScreen  : rsi(esi): Columna
 * 
 * Parámetros de salida : 
 * Ninguno
 * 
 * Se ha definido un subrutina en ensamblador equivalente 'gotoxyP2' 
 * para poder llamar a esta función guardando el estado de los registros 
 * del procesador. Esto se hace porque las funciones de C no mantienen 
 * el estado de los registros.
 * El paso de parámetros es equivalente.
 */
void gotoxyP2_C(int rowCurScreen, int colCurScreen){
	
   printf("\x1B[%d;%dH",rowCurScreen,colCurScreen);
   
}


/**
 * Mostrar un carácter (c) en pantalla, recibido como parámetro, 
 * en la posición donde está el cursor.
 * 
 * Variables globales utilizadas:	
 * Ninguna
 * 
 * Parámetros de entrada: 
 * c        : rdi(dil): Carácter que queremos mostrar.
 * 
 * Parámetros de salida : 
 * Ninguno
 * 
 * Se ha definido un subrutina en ensamblador equivalente 'printchP2' 
 * para llamar a esta función guardando el estado de los registros del 
 * procesador. Esto se hace porque las funciones de C no mantienen 
 * el estado de los registros.
 * El paso de parámetros es equivalente.
 */
void printchP2_C(char c){
	
   printf("%c",c);
   
}


/**
 * Leer una tecla y retornar el carácter asociado 
 * sin mostrarlo en pantalla. 
 * 
 * Variables globales utilizadas:	
 * Ninguna
 * 
 * Parámetros de entrada: 
 * Ninguno
 * 
 * Parámetros de salida : 
 * c        : rax(al): Carácter que leemos de teclado
 * 
 * Se ha definido un subrutina en ensamblador equivalente 'getchP2' para
 * llamar a esta función guardando el estado de los registros del procesador.
 * Esto se hace porque las funciones de C no mantienen el estado de los 
 * registros.
 * El paso de parámetros es equivalente.
 */
char getchP2_C(){

   int c;   

   static struct termios oldt, newt;

   /*tcgetattr obtener los parámetros del terminal
   STDIN_FILENO indica que se escriban los parámetros de la entrada estándard (STDIN) sobre oldt*/
   tcgetattr( STDIN_FILENO, &oldt);
   /*se copian los parámetros*/
   newt = oldt;

    /* ~ICANON para tratar la entrada de teclado carácter a carácter no como línea entera acabada en /n
    ~ECHO para que no se muestre el carácter leído.*/
   newt.c_lflag &= ~(ICANON | ECHO);          

   /*Fijar los nuevos parámetros del terminal para la entrada estándar (STDIN)
   TCSANOW indica a tcsetattr que cambie los parámetros inmediatamente. */
   tcsetattr( STDIN_FILENO, TCSANOW, &newt);

   /*Leer un carácter*/
   c=getchar();                 
    
   /*restaurar los parámetros originales*/
   tcsetattr( STDIN_FILENO, TCSANOW, &oldt);

   /*Retornar el carácter leído*/
   return (char)c;
   
}


/**
 * Mostrar en pantalla el menú del juego y pedir una opción.
 * Sólo acepta una de las opciones correctas del menú ('0'-'9')
 * 
 * Variables globales utilizadas:	
 * developer:((char *)&developer): variable definida en el código ensamblador.
 * 
 * Parámetros de entrada: 
 * Ninguno
 * 
 * Parámetros de salida : 
 * c        : rax(al): Opción escogida del menú, leída de teclado.
 * 
 * Esta función no se llama desde ensamblador
 * y no hay definida una subrutina de ensamblador equivalente.
 */
char printMenuP2_C(){
	char c = ' ';
	
	clearScreen_C();
    gotoxyP2_C(1,1);
    printf("                                     \n");
    printf("            Developed by:            \n");
	printf("         ( %s )   \n",(char *)&developer);
    printf(" ___________________________________ \n");
    printf("|                                   |\n");
    printf("|          MENU MINESWEEPER         |\n");
    printf("|___________________________________|\n");
    printf("|                                   |\n");
    printf("|          1. posCurScreen          |\n");
    printf("|          2. showMines             |\n");
    printf("|          3. updateBoard           |\n");
    printf("|          4. moveCursor            |\n");
    printf("|          5. mineMarker            |\n");
    printf("|          6. searchMines           |\n");
    printf("|          7. checkEnd              |\n");
    printf("|          8. Play Game             |\n");
    printf("|          9. Play Game C           |\n");
    printf("|          0. Exit                  |\n");
    printf("|___________________________________|\n");
    printf("|                                   |\n");
    printf("|             OPTION:               |\n");
    printf("|___________________________________|\n"); 
    
    while (c < '0' || c > '9') {
      gotoxyP2_C(21,23);      //Posicionar el cursor
	  c = getchP2_C();        //Leer una opción
	  printchP2_C(c);         //Mostrar opción 
	}
	return c;
}


/**
 * Mostrar el tablero de juego en pantalla. Las líneas del tablero.
 * 
 * Variables globales utilizadas:	
 * Ninguna
 * 
 * Parámetros de entrada: 
 * Ninguno
 * 
 * Parámetros de salida : 
 * Ninguno
 * 
 * Esta función se llama des de C y desde ensamblador,
 * y no hay definida una subrutina de ensamblador equivalente.
 */
void printBoardP2_C(){

   gotoxyP2_C(1,1);
   printf(" _____________________________________________ \n");	//01
   printf("|                                             |\n");	//02
   printf("|                  MINESWEEPER                |\n");	//03
   printf("|_____________________________________________|\n");	//04
   printf("|     0   1   2   3   4   5   6   7   8   9   |\n");	//05
   printf("|   +---+---+---+---+---+---+---+---+---+---+ |\n");	//06
   printf("| 0 |   |   |   |   |   |   |   |   |   |   | |\n");	//07
   printf("|   +---+---+---+---+---+---+---+---+---+---+ |\n");	//08
   printf("| 1 |   |   |   |   |   |   |   |   |   |   | |\n");	//09
   printf("|   +---+---+---+---+---+---+---+---+---+---+ |\n");	//10
   printf("| 2 |   |   |   |   |   |   |   |   |   |   | |\n");	//11
   printf("|   +---+---+---+---+---+---+---+---+---+---+ |\n");	//12
   printf("| 3 |   |   |   |   |   |   |   |   |   |   | |\n");	//13
   printf("|   +---+---+---+---+---+---+---+---+---+---+ |\n");	//14
   printf("| 4 |   |   |   |   |   |   |   |   |   |   | |\n");	//15
   printf("|   +---+---+---+---+---+---+---+---+---+---+ |\n");	//16
   printf("| 5 |   |   |   |   |   |   |   |   |   |   | |\n");	//17
   printf("|   +---+---+---+---+---+---+---+---+---+---+ |\n");	//18
   printf("| 6 |   |   |   |   |   |   |   |   |   |   | |\n");	//19
   printf("|   +---+---+---+---+---+---+---+---+---+---+ |\n");	//20
   printf("| 7 |   |   |   |   |   |   |   |   |   |   | |\n");	//21
   printf("|   +---+---+---+---+---+---+---+---+---+---+ |\n");	//22
   printf("| 8 |   |   |   |   |   |   |   |   |   |   | |\n");	//23
   printf("|   +---+---+---+---+---+---+---+---+---+---+ |\n");	//24
   printf("| 9 |   |   |   |   |   |   |   |   |   |   | |\n");	//25
   printf("|   +---+---+---+---+---+---+---+---+---+---+ |\n");	//26
   printf("|     Mines to  Mark: __                      |\n");	//27
   printf("|_____________________________________________|\n");	//28
   printf("|   (m)Mark Mine    (Space)Open  (ESC)Exit    |\n"); //29
   printf("|   (i)Up    (j)Left    (k)Down    (l)Right   |\n"); //30
   printf("|_____________________________________________|\n");	//31
   
}


/**
 * Posicionar el cursor en pantalla dentro del tablero, en función del 
 * vector (rowcol), posición del cursor dentro del tablero, vector que 
 * se recibe como parámetro y llamamos (rc) (fila rc[0] y columna rc[1]).
 * Para calcular la posición del cursor en pantalla utilizar 
 * estas fórmulas:
 * rowScreen=(rc[0]*2)+7
 * colScreen=(rc[1]*4)+7
 * Para posicionar el cursor se llama a la función gotoxyP2_C.
 * 
 * Variables globales utilizadas:	
 * Ninguna
 * 
 * Parámetros de entrada : 
 * rc : rdi  : Dirección del vector de 2 posiciones donde guardamos la fila 
 *             (rc[0]) y la columna (rc[1]) del cursor dentro del tablero.
 * 
 * Parámetros de salida: 
 * Ninguno
 * 
 * Esta función no es llama desde ensamblador.
 * En la subrutina de ensamblador equivalente 'posCurScreenP2',
 * el paso de parámetros es equivalente. 
 */
 void posCurScreenP2_C(int rc[2]) {
   
   int rowScreen, colScreen;
   rowScreen=(rc[0]*2)+7;
   colScreen=(rc[1]*4)+7;
   gotoxyP2_C(rowScreen, colScreen);
   
}


/**
 * Convierte el valor del Número de minas que quedan por marcar (nMines)
 * que se recibe como parámetro (entre 0 y 99) a dos caracteres ASCII. 
 * Se tiene que dividir el valor (nMines) entre 10, el cociente 
 * representará las decenas y el residuo las unidades, y después se
 * tienen que convertir a ASCII sumando 48, carácter '0'.
 * Mostrar los dígitos (carácter ASCII) de las decenas en la fila 27, 
 * columna 23 de la pantalla y las unidades en la fila 27, columna 24.
 * Para posicionar el cursor se llama a la función gotoxyP2_C y para 
 * mostrar los caracteres a la función printchP2_C.
 * 
 * Variables globales utilizadas:
 * Ninguna
 * 
 * Parámetros de entrada : 
 * nMines : rdi(edi) : Número de minas que quedan por marcar.
 * 
 * Parámetros de salida: 
 * Ninguno
 * 
 * Esta función no es llama desde ensamblador.
 * En la subrutina de ensamblador equivalente 'showMinesP2',  
 * el paso de parámetros es equivalente.
 */
 void showMinesP2_C(int nMines) {
	
	char digit;
	
	digit = nMines/10;//Decenas
	digit = digit + '0';
	gotoxyP2_C(27, 23);   
	printchP2_C(digit);

	digit = nMines%10;//Unitades
	digit = digit + '0';
	gotoxyP2_C(27, 24);   
	printchP2_C(digit);
	
}


/**
 * Actualizar el contenido del Tablero de Juego con los datos de la 
 * matriz (marks) y el número de minas que quedan por marcar que se 
 * recibe como parámetro y llamamos (nMines).
 * Se tiene que recorrer toda la matriz (marks), y para cada elemento 
 * de la matriz posicionar el cursor en pantalla y mostrar los caracteres 
 * de la matriz. 
 * Después mostrar el valor de (nMines) en la parte inferior del tablero.
 * Para posicionar el cursor se llama la función gotoxyP2_C, 
 * para a mostrar los caracteres se llama la función printchP2_C y para 
 * mostrar el número de minas se llama a la función ShowMinesP2_C.
 * 
 * Variables globales utilizadas:
 * marks  : Matriz con las minas marcadas y las minas de las abiertas.
 * 
 * Parámetros de entrada : 
 * nMines : rsi(esi) : Número de minas que quedan por marcar.
 * 
 * Parámetros de salida: 
 * Ninguno
 *  
 * Esta función no es llama desde ensamblador.
 * En la subrutina de ensamblador equivalente 'updateBoardP2', 
 * el paso de parámetros es equivalente.
 */
void updateBoardP2_C(int nMines){

   int rowScreen, colScreen;
   int i,j;
   
   rowScreen = 7;
   for (i=0;i<DimMatrix;i++){
	  colScreen = 7;
      for (j=0;j<DimMatrix;j++){
         gotoxyP2_C(rowScreen,colScreen);
         printchP2_C(marks[i][j]);
         colScreen = colScreen + 4;
      }
      rowScreen = rowScreen + 2;
   }
   showMinesP2_C(nMines);//Mostrar número de minas que quedan por marcar
   
}


/**
 * Actualizar la posición del cursor en el tablero que tenemos en el 
 * vector (rowcol), que se recibe como parámetro y llamamos (rc) 
 * (fila (rc[0]) y columna (rc[1])) en función de la tecla pulsada, que 
 * también recibimos como parámetro y llamamos (c).
 * Si se sale fuera del tablero no actualizar la posición del cursor.
 * (i:arriba, j:izquierda, k:a bajo, l:derecha)
 * ( rc[0] = rc[0] +/- 1 ) ( rc[1] = rc[1] +/- 1 ) 
 * No se tiene que posicionar el cursor en pantalla.
 *  
 * Variables globales utilizadas::	
 * Ninguna
 * 
 * Parámetros de entrada : 
 * rc : rdi      : Dirección del vector de 2 posiciones donde guardamos la fila 
 *                 (rc[0]) y la columna (rc[1]) del cursor dentro del tablero.
 * c  : rsi(sil) : Carácter leído de teclado 
 * 
 * Parámetros de salida: 
 * Ninguno
 * 
 * Esta función no es llama desde ensamblador.
 * En la subrutina de ensamblador equivalente 'moveCursorP2', 
 * el paso de parámetros es equivalente.
 */
void moveCursorP2_C(int rc[2], char c){
 
   switch(c){
      case 'i': //amunt
         if (rc[0]>0) rc[0]--;
      break;
      case 'j': //esquerra
         if (rc[1]>0) rc[1]--;
      break;
      case 'k': //avall
         if (rc[0]<DimMatrix-1) rc[0]++;
      break;
      case 'l': //dreta
		 if (rc[1]<DimMatrix-1) rc[1]++;
      break;     
	}
	
}


/**
 * Marcar/desmarcar una mina en la matriz (marks) en la posición actual 
 * del cursor, indicada por el vector(rowcol), que es recibe como 
 * parámetro y llamamos (rc) (fila (rc[0]) y columna (rc[1])).
 * Si en aquella posición de la matriz (marks) hay un espacio en blanco
 * y no hemos marcado todas las minas, marcamos una mina poniendo una 
 * 'M' y decrementamos el número de minas que quedan por marcar (numMines), 
 * que se recibe como parámetro y llamamos (nMines), si en aquella 
 * posición de la matriz (marks) hay una 'M', pondremos un espacio (' ')
 * y incrementaremos el número de minas que quedan por marcar (nMines).
 * Si hay otro valor no cambiaremos nada.
 * Retornar el Número de minas que quedan por marcar actualizado (nMines).
 * No se tiene que mostrar la matriz, sólo actualizar la matriz (marks) 
 * y la variable (nMines).
 * 
 * Variables globales utilizadas:
 * marks  : Matriz con las minas marcadas y las minas de las abiertas.
 * 
 * Parámetros de entrada: 
 * rc     : rdi      : Dirección del vector de 2 posiciones donde guardamos la fila 
 *                     (rc[0]) y la columna (rc[1]) del cursor dentro del tablero.
 * nMines : rsi(esi) : Número de minas que quedan por marcar.
 * 
 * Parámetros de salida: 
 * nMines : rax(eax) : Número de minas que quedan por marcar.
 * 
 * Esta función no es llama desde ensamblador.
 * En la subrutina de ensamblador equivalente 'mineMarkerP2', 
 * el paso de parámetros es equivalente.
 */
int mineMarkerP2_C(int rc[2], int nMines) {
	
	int row = rc[0];
	int col = rc[1];
	
	if (marks[row][col] == ' ' && nMines > 0) {
		marks[row][col] = 'M';
		nMines--;
	} else {
		if (marks[row][col] == 'M') {
			marks[row][col] = ' ';
			nMines++;
		}
	}	
	return nMines;
} 
 

/**
 * Abrir casilla. Mirar cuantas minas hay alrededor de la posición 
 * actual del cursor, indicada por el vector (rowcol) que se recibe como 
 * parámetro y llamamos (rc) (fila (rc[0]) y columna (rc[1])), de la 
 * matriz (mines).
 * Si en la posición actual de la matriz (marks) hay un espacio (' ') 
 *   Mirar si en la matriz (mines) hay una mina ('*').
 *   Si hay una mina cambiar el estado (state), que se recibe como 
 *     parámetro y llamamos (status) a 3 "Explosión", para salir.
 *	 Si no, contar cuantas minas hay alrededor de la posición 
 *     actual y actualizar la posición del matriz (marks) con 
 *     el número  de minas (carácter ASCII del valor, para hacerlo, hay 
 *     que sumar 48 ('0') al valor).
 * Si no hay un espacio, quiere decir que hay una mina marcada ('M') o 
 * la casilla ya está abierta (hay el número de minas que ya se ha 
 * calculado anteriormente), no hacer nada.
 * Retornar el estado del juego actualizado (status).
 * No se tiene que mostrar la matriz.
 *  
 * Variables globales utilizadas:
 * marks  : Matriz con las minas marcadas y las minas de las abiertas.
 * mines  : Matriz donde ponemos las minas.
 * 
 * Parámetros de entrada : 
 * rc    : rdi      : Dirección del vector de 2 posiciones donde guardamos la fila 
 *                    (rc[0]) y la columna (rc[1]) del cursor dentro del tablero.
 * status: rsi(esi) : Estado del juego. 
 * 
 * Parámetros de salida: 
 * status : rax(eax) : Estado del juego. 
 *  
 * Esta función no es llama desde ensamblador.
 * En la subrutina de ensamblador equivalente 'searchMinesP2', 
 * el paso de parámetros es equivalente.
 */
int searchMinesP2_C(int rc[2], int status) {
	
	char digit = 0;
	int  row = rc[0];
	int  col = rc[1];
	
	if (marks[row][col]==' ') {
		if (mines[row][col]!=' ') {
			status = 3;
		} else {
			if (row > 0) { 
				if (col > 0) {
					if (mines[row-1][col-1]=='*') digit++; //UpLeft
				}
				if (mines[row-1][col]=='*') digit++;       //UpCenter
				if (col < DimMatrix-1) {
					if (mines[row-1][col+1]=='*') digit++; //UpRight
				}
			}
			if (col > 0) {
				if (mines[row][col-1]=='*') digit++;       //LeftCenter
			}
			if (col < DimMatrix-1) {
				if (mines[row][col+1]=='*') digit++;       //RightCenter
			}
			if (row < DimMatrix-1) { 
				if (col > 0) {
					if (mines[row+1][col-1]=='*') digit++; //DownLeft
				}
				if (mines[row+1][col]=='*') digit++;       //DownCenter
				if (col < DimMatrix-1) {
					if (mines[row+1][col+1]=='*') digit++; //DownRight
				}
			}
			marks[row][col] = digit+'0';
		}
	}
	return status;
} 

 


/**
 * Verificar si hemos marcado todas las minas (numMines=0), que se reciben
 * como parámetro y llamamos (nMines) y hemos abierto o marcado con una 
 * mina todas  las otras casillas y no hay ningún espacio en blanco (' ') 
 * en la matriz (marks), si es así, cambiar el estado (state) que se 
 * recibe como parámetro y llamamos (status), a 2 "Gana la partida".
 * Retornar el estado del juego actualizado (status).
 * 
 * Variables globales utilizadas:	
 * marks  : Matriz con las minas marcadas y las minas de las abiertas.
 * 
 * Parámetros de entrada : 
 * nMines : rdi(edi) : Número de minas que quedan por marcar.
 * staus  : rsi(esi) : Estado del juego. 
 * 
 * Parámetros de salida: 
 * staus  : rax(eax) : Estado del juego. 
 *  
 * Esta función no es llama desde ensamblador.
 * En la subrutina de ensamblador equivalente 'checkEndP2', 
 * el paso de parámetros es equivalente.
 */
int checkEndP2_C(int nMines, int status) {
	
	char notOpenMarks = 0;
	int i,j;
	
	if (nMines == 0) {
		for (i=0;i<DimMatrix;i++){
			for (j=0;j<DimMatrix;j++){
				if (marks[i][j] == ' ') notOpenMarks++;
			}
		}
		if (notOpenMarks == 0) {
			status = 2;
		}
	}
	return status;
} 


/**
 * Mostrar un mensaje debajo del tablero según el valor de la variable 
 * (state) que se recibe como parámetro y llamamos (status).
 * status: 0: Salimos, hemos pulsado la tecla 'ESC' para salir del juego.
 * 		   1: Continuamos jugando.
 * 		   2: Gana la partida, se han marcado todas las minas y se han abierto el resto de posiciones.
 * 		   3: Explosión, se ha abierto una mina.
 * Se espera que se pulse una tecla para continuar.
 *  
 * Variables globales utilizadas:	
 * Ninguna
 * 
 * Parámetros de entrada : 
 * staus  : rsi(esi) : Estado del juego. 
 * 
 * Parámetros de salida: 
 * Ninguno
 *   
 * Esta función se llama des de C y desde ensamblador,
 * y no hay definida una subrutina de ensamblador equivalente.
  */
void printMessageP2_C(int status) {

   gotoxyP2_C(27,30);
   
   switch(status){
      case 0:
         printf("<< EXIT: ESC >>");
        break;
      case 2:
         printf("++ YOU WIN ! ++");
      break;
      case 3:
         printf("-- BOOOM !!! --");
      break;
   }
   getchP2_C();				//Espera que l'usuari premi una tecla.
   
}
 

/**
 * Juego del Buscaminas
 * Función principal del juego
 * Permite jugar al juego del buscaminas llamando a todas las funcionalidades.
 *
 * Pseudo código:
 * Inicializar estado del juego, (state=1)
 * Inicializar fila y columna, posición inicial, (rowcol[0]=4) i (rowcol[1]=4)
 * Mostrar el tablero de juego (llamando la función PrintBoardP2_C).
 * Mientras (state=1) hacer:
 *   Actualizar el contenido del Tablero de Juego y el número de minas
 *     que quedan por marcar (llamar la función updateBoardP2_C).
 *   Posicionar el cursor dentro del tablero (llamar la funció posCurScreenP2_C).
 *   Leer una tecla y guardarla en la variable local (c). 
 *   Según la tecla leída llamaremos a la función correspondiente.
 *     - ['i','j','k' o 'l']       (llamar a la función MoveCursorP2_C).
 *     - 'x'                       (llamar a la función MineMarkerP2_C).
 *     - '<espace>'(codi ASCII 32) (llamar a la función SearchMinesP2_C).
 *     - '<ESC>'  (codi ASCII 27) poner (state = 0) para salir.   
 *   Verificar si hemos marcado todas las minas y si hemos abierto todas  
 *     las otras casillas (llamar a la función CheckEndP2_C).
 * Fin mientras.
 * Salir:  
 *   Actualizar el contenido del Tablero de Juego y el número de minas que 
 *   quedan por marcar (llamar a la subrutina updateBoardP2_C).
 *   Mostrar el mensaje de salida que corresponda (llamar a la función
 *   printMessageP2_C).
 * Se acaba el juego.
 * 
 * Variables globales utilizadas:	
 * Ninguna
 * 
 * Parámetros de entrada : 
 * nMines : rdi(edi) : Número de minas que quedan por marcar.
 * 
 * Parámetros de salida: 
 * nMines : rax(eax) : Número de minas que quedan por marcar.
 */
int playP2_C(int nMines){
/**
 * Definición de variables locales.
 */
   int  rowcol[2];	//vector de dos posiciones de tipo int dondee tenemos 
					//la fila (rowcol[0]) y la columna (rowcol[1]) para 
                    //acceder a las matrices mines y marks y para  
                    //indicar fila y columna del cursor dentro del tablero.


   int numMines = nMines; 	//Número de minas que queden por marcar.
 
   int state = 1;	// 0: Salimos, hemos pulsado la tecla 'ESC' para salir del juego.
                    // 1: Continuamos jugando.
                    // 2: Gana la partida, se han marcado todas las minas y se han abierto el resto de posiciones.
                    // 3: Explosión, se ha abierto una mina.
   char c;

   printBoardP2_C();

   rowcol[0]=  4;	//Posición inicial del cursor.
   rowcol[1] = 4;      
          
   while (state == 1) {  //bucle principal.  
	 updateBoardP2_C(numMines);
	 posCurScreenP2_C(rowcol);
     
     c = getchP2_C();	//leer una tecla y guardarla en la variable c.
	
     if (c>='i' && c<='l') {      //Mover cursor
       moveCursorP2_C(rowcol, c);
     }
     if (c=='m') {                //Marcar mina
       numMines = mineMarkerP2_C(rowcol, numMines);
     }
     if (c==' ') {                //Mirar minas 
       state = searchMinesP2_C(rowcol, state);
     }
     if (c==27) {                 //Salir del programa
       state = 0;
     }
     state = checkEndP2_C(numMines, state);
   }
   updateBoardP2_C(numMines);
   printMessageP2_C(state);	//Mostrar el mensaje para indicar como acaba.
   
   return numMines;
}


/**
 * Programa Principal
 * 
 * ATENCIÓN: En cada opción se llama a una subrutina de ensamblador.
 * Debajo hay comentada la función en C equivalente que os damos hecha 
 * por si queréis ver como funciona.
 */
int main(void){   
/**
 * Definición de variables locales.
 */
   int  rowcol[2];	//vector de dos posiciones de tipo int donde tenemos
					//la fila (rowcol[0]) y la columna (rowcol[1]) para 
                    //acceder a las matrices mines y marks y para inidcar
                    //fila y columna del cursor dentro del tablero.


   int numMines = 18; 	// Número de minas que quedan por marcar.
 
   int state = 1;	// 0: Salimos, hemos pulsado la tecla 'ESC' para salir del juego.
                    // 1: Continuamos jugando.
                    // 2: Gana la partida, se han marcado todas las minas y se han abierto el resto de posiciones.
                    // 3: Explosión, se ha abierto una mina.

   int op=1;
   char c;
     
   while (op!='0') {
	  clearScreen_C();
      op = printMenuP2_C();		  //Mostrar menú y leer opción
      
      switch(op){
         case '1':// Posicionar el cursor en el tablero.
            printf(" %c",op);
            clearScreen_C();  //Borrar la pantalla
            printBoardP2_C(); //Mostrar el tablero
            gotoxyP2_C(27,30);
            printf(" Press any key ");
            //=======================================================
            rowcol[0]=1;  //Fila y columna donde se posiciona el cursor
            rowcol[1]=1;
            posCurScreenP2(rowcol);
            //posCurScreenP2_C(rowcol);
            //=======================================================
            getchP2_C();
         break;
         case '2': //Mostrar número de minas que quedan por marcar
            printf(" %c",op);
            clearScreen_C();  //Borrar la pantalla
            printBoardP2_C(); //Mostrar el tablero
            //=======================================================
            showMinesP2(numMines);
            //showMinesP2_C(numMines);  //Actualizar número de minas
            //=======================================================
            gotoxyP2_C(27,30);
            printf("Press any key ");
            getchP2_C();
         break;
         case '3': //Mostrar el tablero y actualizar el contenido
            printf(" %c",op);
            clearScreen_C();  //Borrar la pantalla
            printBoardP2_C(); //Mostrar el tablero
            //=======================================================
            updateBoardP2(numMines);
            //updateBoardP2_C(numMines);  //Actualitzar el contenido del tablero
            //=======================================================
            gotoxyP2_C(27,30);
            printf("Press any key ");
            getchP2_C();
         break;
         case '4': //Mover el cursor
            clearScreen_C();  //Borrar la pantalla
            printBoardP2_C(); //Mostrar el tablero
            printf("\n    Move cursor: i:Up, j:Left, k:Down, l:Right ");
            rowcol[0]=2;  //Fila y columna donde se posiciona el cursor
            rowcol[1]=2;
            posCurScreenP2_C(rowcol);
            c = getchP2_C();	
            gotoxyP2_C(27,30);
			printf("Press any key ");
	        if (c >= 'i' && c <= 'l') { 
				//===================================================
				moveCursorP2(rowcol, c);
				//moveCursorP2_C(rowcol, c);
				//===================================================
				posCurScreenP2_C(rowcol);
            } else {
				printf("\n       Incorrect option                         ");
			}
            getchP2_C();
         break;
         case '5': //Marcar Mina
            clearScreen_C();  //Borrar la pantalla
            printBoardP2_C(); //Mostrar el tablero
            printf("\n       Mark a Mine: m:mark/unmark");
            updateBoardP2_C(numMines);  
            rowcol[0]=3;      //Fila i columna on es posiciona el cursor
            rowcol[1]=3;
            posCurScreenP2_C(rowcol);
            c = getchP2_C();
   			if (c=='m') {
			    //===================================================
            	numMines = mineMarkerP2(rowcol, numMines);
				//numMines = mineMarkerP2_C(rowcol, numMines);
				//===================================================
                updateBoardP2_C(numMines);  
			} else {
				printf("\n       Incorrect option                         ");
				gotoxyP2_C(27,30);
			    printf("Press any key ");
			}
			gotoxyP2_C(27,30);
			printf("Press any key ");
			getchP2_C();
         break;
         case '6': //Contar cuantas minas hay alrededor de una posición
            clearScreen_C();  //Borrar la pantalla
            printBoardP2_C(); //Mostrar el tablero
            printf("\n    Press SPACE ");
            updateBoardP2_C(numMines); 
            c = getchP2_C();
            if (c==' ') {
			  rowcol[0]=5;  //Fila y columna donde se posiciona el cursor
			  rowcol[1]=4;
			  posCurScreenP2_C(rowcol);
			  //===================================================
			  state = searchMinesP2(rowcol, state);
			  //state = searchMinesP2_C(rowcol, state);
			  //===================================================
			  updateBoardP2_C(numMines);  
			  printMessageP2_C(state);
			} else {
				printf("\n       Incorrect option                         ");
			}
			state=1;
          break;
          case '7': //Verificar si hemos marcado todas las minas y abierto todas las posiciones.
            clearScreen_C();  //Borrar la pantalla
            printBoardP2_C(); //Mostrar el tablero
            updateBoardP2_C(numMines);
 			//===================================================
            state = checkEndP2(numMines, state);
			//state = checkEndP2_C(numMines, state);
			//===================================================
			printMessageP2_C(state);
			state=1;
         break;
          case '8': //Juego completo en ensamblador
            clearScreen_C();  //Borrar la pantalla 
            //=======================================================
            numMines = playP2(numMines);
            //=======================================================
         break;
         case '9': //Juego completo en C
            clearScreen_C();  //Borrar la pantalla 
            //=======================================================
            numMines = playP2_C(numMines);
            //=======================================================
         break;
         case '0':
		 break;	 
      }
   }
   printf("\n\n");
   
   return 0;
}
