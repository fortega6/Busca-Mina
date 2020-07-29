section .data               
;Cambiar Nombre y Apellido.
developer db "_Nom_ _Cognom1_",0

;Constantes que también están definidas en C.
DimMatrix    equ 10
SizeMatrix   equ 100	

section .text            
;Variables definidas en Ensamblador.
global developer                        

;Subrutinas de ensamblador que se llaman desde C.
global posCurScreenP2, showMinesP2  , updateBoardP2, moveCursorP2
global mineMarkerP2  , searchMinesP2, checkEndP2   , playP2	 

;Variables globales definidas en C.
extern marks, mines

;Funciones de C que se llaman desde ensamblador
extern clearScreen_C, gotoxyP2_C, getchP2_C, printchP2_C
extern printBoardP2_C, printMessageP2_C


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; ATENCIÓN: Recordad que las variables y los Parámetros de tipo 'char',
;;   en ensamblador se tienen que asignar a registros de tipo BYTE 
;;   (1 byte): al, ah, bl, bh, cl, ch, dl, dh, sil, dil, ...
;;   y los de tipo 'int' se tienen que asignar a registros 
;;   de tipo DWORD (4 bytes): eax, ebx, ecx, edx, esi, edi, ....
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Las subrutinas en ensamblador que tenéis que implementar son:
;;   posCurScreenP2, showMinesP2,  updateBoardP2, moveCursorP2
;;   calcIndexP2, mineMarkerP2, searchMinesP2, checkEndP2
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Situar el cursor en una fila y una columna de la pantalla
; en función de la fila (edi) y de la columna (esi) recibidos como 
; parámetro llamando a la función gotoxyP2_C.
; 
; Variables globales utilizadas:	
; Ninguna
; 
; Parámetros de entrada: 
; rdi(edi): Fila
; rsi(esi): Columna
; 
; Parámetros de salida : 
; Ninguno
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
gotoxyP2:
   push rbp
   mov  rbp, rsp
   ;guardamos el estado de los registros del procesador porque
   ;las funciones de C no mantienen el estado de los registros.
   push rax
   push rbx
   push rcx
   push rdx
   push rsi
   push rdi
   push r8
   push r9
   push r10
   push r11
   push r12
   push r13
   push r14
   push r15

   ; Cuando llamamos a la función gotoxyP2_C(int rowCurScreen, int colCurScreen) 
   ; desde ensamblador el primer parámetro (rowCurScreen) se tiene que 
   ; pasar por el registro rdi(edi), y el segundo  parámetro (colCurScreen)
   ; se tiene que pasar por el registro rsi(esi).
   ;mov dword[rdi], edi
   ;mov dword[rsi], esi
   call gotoxyP2_C
 
   pop r15
   pop r14
   pop r13
   pop r12
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdi
   pop rsi
   pop rdx
   pop rcx
   pop rbx
   pop rax

   mov rsp, rbp
   pop rbp
   ret


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Mostrar un carácter (dil) en pantalla, recibido como parámetro, 
; en la posición donde está el cursor llamando a la función printchP2_C.
; 
; Variables globales utilizadas:	
; Ninguna
; 
; Parámetros de entrada: 
; rdi(dil): carácter que queremos mostrar
; 
; Parámetros de salida : 
; Ninguno
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
printchP2:
   push rbp
   mov  rbp, rsp
   ;guardamos el estado de los registros del procesador porque
   ;las funciones de C no mantienen el estado de los registros.
   push rax
   push rbx
   push rcx
   push rdx
   push rsi
   push rdi
   push r8
   push r9
   push r10
   push r11
   push r12
   push r13
   push r14
   push r15

   ; Cuando llamamos a la función printchP2_C(char c) desde ensamblador, 
   ; el parámetro (c) se tiene que pasar por el registro rdi(dil).
   call printchP2_C
 
   pop r15
   pop r14
   pop r13
   pop r12
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdi
   pop rsi
   pop rdx
   pop rcx
   pop rbx
   pop rax

   mov rsp, rbp
   pop rbp
   ret
   

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Leer una tecla y retornar el carácter asociado (al) sin
; mostrarlo en pantalla, llamando a la función getchP2_C
; 
; Variables globales utilizadas:	
; Ninguna
; 
; Parámetros de entrada: 
; Ninguno
; 
; Parámetros de salida : 
; rax(al): carácter que leemos de teclado
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
getchP2:
   push rbp
   mov  rbp, rsp
   ;guardamos el estado de los registros del procesador porque
   ;las funciones de C no mantienen el estado de los registros.
   push rbx
   push rcx
   push rdx
   push rsi
   push rdi
   push r8
   push r9
   push r10
   push r11
   push r12
   push r13
   push r14
   push r15

   mov rax, 0
   ; llamamos a la función getchP2_C(char c) desde ensamblador, 
   ; retorna sobre el registro rax(al) el carácter leído.
   call getchP2_C
 
   pop r15
   pop r14
   pop r13
   pop r12
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdi
   pop rsi
   pop rdx
   pop rcx
   pop rbx
   
   mov rsp, rbp
   pop rbp
   ret 


;;;;;
; Posicionar el cursor en pantalla dentro del tablero, en función del 
; vector (rowcol), posición del cursor dentro del tablero, vector que 
; se recibe como parámetro (fila rowcol[0] y columna rowcol[1]).
; Para calcular la posición del cursor en pantalla utilizar 
; estas fórmulas:
; edi = rowScreen =(rowcol[0]*2)+7
; esi = colScreen =(rowcol[1]*4)+7
; Para posicionar el cursor se tiene que llamar la subrutina gotoxyP2
; implementando correctamente el paso de parámetros.
; 
; Variables globales utilizadas:	
; Ninguna
; 
; Parámetros de entrada : 
; rdi  : Dirección del vector de 2 posiciones donde guardamos la fila 
;        (rowcol[0]) y la columna (rowcol[1]) del cursor dentro del tablero.
; 
; Parámetros de salida: 
; Ninguno
;;;;;  
posCurScreenP2:
	push rbp
	mov  rbp, rsp
	  
	mov rsi, 4		
	mov esi, [rdi+rsi]
	mov edi, [rdi]
	; Calculo de posicion del cursor en pantalla
	IMUL edi, 2
	IMUL esi, 4
	add edi, 7
	add esi, 7
	;mov dword[edi], eax			; Se obtiene y guarda en (eax) la Fila actual del cursor en el tablero (rowcol[0])
	;mov dword[esi], ebx			; Se obtiene y guarda en (ebx) la Columna actual del cursor en el tablero (rowcol[1])
	call gotoxyP2 				; Posicionar cursor en pantalla	
				
	mov rsp, rbp
	pop rbp
	ret


;;;;;
; Convierte el valor del Número de minas que quedan por marcar (numMines)
; que se recibe como parámetro (entre 0 y 99) a dos caracteres ASCII. 
; Se tiene que dividir el valor (numMines) entre 10, el cociente 
; representará las decenas y el residuo las unidades, y después se
; tienen que convertir a ASCII sumando 48, carácter '0'.
; Mostrar los dígitos (carácter ASCII) de las decenas en la fila 27, 
; columna 23 de la pantalla y las unidades en la fila 27, columna 24.
; Para a posicionar el cursor se tiene que llamar a la subrutina gotoxyP2 y 
; para a mostrar los caracteres a la subrutina printchP2, implementando 
; correctamente el paso de parámetros
; 
; Variables globales utilizadas:
; Ninguna
; 
; Parámetros de entrada : 
; rdi(edi) :Número de minas que quedan por marcar.
; 
; Parámetros de salida: 
; Ninguno
;;;;;
showMinesP2:
	push rbp
	mov  rbp, rsp
	
	mov edx, 0	
	mov ecx, 10				; Divisor se guarda en (ch)
	mov eax, edi			; Numero de minas se guarda en (ax)
	DIV ecx					; Dividir numMines/10 (ax/ch) para dividir el numero en dos partes cociente(decena) y residuo(unidad)
	mov edi, eax			; Se guarda el cociente (decena)
	add edi, '0'			; Transformar tipo de dato int a char
	push rdi
	mov edi, 27
	mov esi, 23
	call gotoxyP2			; Posicionar cursor
	pop rdi
	call printchP2			; Imprimir decena (decena)
	mov edi, 27
	mov esi, 24
	call gotoxyP2	; Posicionar cursor
	mov edi, edx 		; Se guarda el residuo (unidad)
	add edi, '0'	; Transformar tipo de dato int a char
	call printchP2	; Imprimir residuo (unidad)
	
	mov rsp, rbp
	pop rbp
	ret


;;;;;
; Actualizar el contenido del Tablero de Juego con los datos de la 
; matriz (marks) y el número de minas que quedan por marcar que  
; se recibe como parámetro.
; Se tiene que recorrer toda la matriz (marks), y para cada elemento 
; de la matriz posicionar el cursor en pantalla y mostrar los caracteres 
; de la matriz. 
; Después mostrar el valor del número de minar que quedan por marcar 
; en la parte inferior del tablero.
; Para posicionar el cursor se tiene que llamar a la subrutina gotoxyP2,
; para mostrar los caracteres se tiene que llamar a la subrutina printchP2
; y para mostrar el número de minas se tiene que llamar a la subrutina
; ShowMinesP2, implementando correctamente el paso de parámetros.
; 
; Variables globales utilizadas:
; marks  : Matriz con las minas marcadas y las minas de las abiertas.
; 
; Parámetros de entrada : 
; rsi(esi) : Número de minas que quedan por marcar.
; 
; Parámetros de salida: 
; Ninguno
updateBoardP2:
	push rbp
	mov  rbp, rsp
	
	push rdi	; Guardamos el numero minas que quedan por marcar en la pila
				;recorremos la matriz con dos índices para sumarla
	mov r9,0 	;ebp será el índice de la columna
	mov r8,0 	;esp será el índice de la fila
	mov edi, 7		; Fila
	mov esi, 7		; Columna
loop_marks:
	call gotoxyP2
	push rdi
	mov dil, byte[marks+r8+r9] ; Posicion en la matriz
	;mov [charac], al			; Se guarda el caracter de la matriz en (charac)
	call printchP2				; Se imprime caracter en la matriz
	pop rdi
	add esi, 4					; Movemos el cursor a siguiente columna en la matriz 
	inc r9 					; Incrementamos en una unidad el indice de columna (esi)
	cmp r9, DimMatrix 			; Comparamos con 10 porque son la cantodad elementos de una fila.
	jl loop_marks
	mov r9, 0					; Indice de la columna inicializado en cero
	mov esi, 7					; Primera columna 
	add edi, 2					; Siguiente fila en la matriz
	add r8, DimMatrix 			; Cada fila ocupa 10 bytes, 10 elementos de 1 byte.
	cmp r8, SizeMatrix 		; Comparamos con 100 para saber cuando llegamos a la ultima posicion de la matriz
	jl loop_marks
	pop rdi
	call showMinesP2
		
	mov rsp, rbp
	pop rbp
	ret


;;;;;		
; Actualizar la posición del cursor en el tablero que tenemos en el 
; vector (rowcol), que se recibe como parámetro (la fila rowcol[0]) y 
; la columna (rowcol[1]) en función de la tecla pulsada, que 
; también recibimos como parámetro.
; Si se sale fuera del tablero no actualizar la posición del cursor.
; (i:arriba, j:izquierda, k:a bajo, l:derecha)
; ( rowcol[0] = rowcol[0] +/- 1 ) ( rowcol[1] = rowcol[1] +/- 1 ) 
; No se tiene que posicionar el cursor en pantalla.
;  
; Variables globales utilizadas:
; Ninguna
; 
; Parámetros de entrada : 
; rdi      : Dirección del vector de 2 posiciones donde guardamos la fila 
;            (rowcol[0]) y la columna (rowcol[1]) del cursor dentro del tablero.
; rsi(sil) : Carácter leído de teclado 
; 
; Parámetros de salida: 
; Ninguno
;;;;;
moveCursorP2:
	push rbp
	mov  rbp, rsp
	push rsi
	
	mov rax, DimMatrix
	dec eax
	cmp sil, 'i'  	; Si la tecla pulsada es igual a i:arriba 
	je 	amunt			   	; Saltamos a la etiqueta amunt
	cmp sil, 'j'	; Si la tecla pulsada es igual a j:izquierda
	je 	esquerra			; Saltamos a la equitata esquerra
	cmp sil, 'k' 	; Si la tecla pulsada es igual a k:a bajo
	je 	avall				; Saltamos a la equitata evall
	cmp sil, 'l' 	; Si la tecla pulsada es igual a l:derecha
	je 	dreta				; Saltamos a la equitata dreta
	jmp end					; Si no se cumple ninguna de las igualdades saltamos a la etiqueta end
amunt:						; Mover cursor arriba
	cmp rdi, 0	; Condición si nos encotramos posicionado en la primera fila del tablero
	je end					; Nos encotramos en un limite del tablero saltamos a la etiqueta end
	dec qword[rdi]
	jmp end
esquerra:					; Mover cursor a la izquierda
	mov rsi,4
	cmp QWORD[rdi+rsi], 0; Condición si nos encotramos posicionados en la primera columna del tablero
	je end					; Nos encotramos en un limite del tablero saltamos a la etiqueta end
	dec QWORD[rdi+rsi]
	jmp end
avall:						; Mover cursor abajo
	cmp rdi, rax	; Condición si nos encotramos posicionado en la ultima fila del tablero
	je end					; Nos encotramos en un limite del tablero saltamos a la etiqueta end
	inc qword[rdi]
	jmp end
dreta:							; Mover cursor a la derecha
	mov rsi,4
	cmp QWORD[rdi+rsi], rax	; Condición si nos encotramos posicionado en la ultima columna del tablero
	je end						; Nos encotramos en un limite del tablero saltamos a la etiqueta end
	inc QWORD[rdi+rsi]
	jmp end
end:
	
	pop rsi
	mov rsp, rbp
	pop rbp
	ret


;;;;;  
; Calcular el valor del índice para acceder a la matriz marks y mines  
; (10x10) que guardaremos en el registro eax para retornarlo, a partir
; de los valores de la posición actual del cursor, indicados por el
; vector: (rowcol): vector con la fila (rowcol[0]) y la columna (rowcol[1]) 
; del cursor dentro del tablero.
; eax=(rowcol[0]*DimMatrix)+([rowcol[1]).
; El índice se retornar sobre el registro eax.
;
; Esta subrutina no tiene una función en C equivalente.
;
; Variables globales utilizadas:	
; Ninguna
; 
; Parámetros de entrada : 
; rdi      : Dirección del vector de 2 posiciones donde guardamos la fila 
;            (rowcol[0]) y la columna (rowcol[1]) del cursor dentro del tablero.
; 
; Parámetros de salida: 
; rax(eax) : índice para acceder a las matrices mines y marks.
;;;;;  
calcIndexP2:
	push rbp
	mov  rbp, rsp
	
	push rbx
	push rcx
	push rdx
	push rsi
	push rdi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
   
	mov rsi, 4			 	; Indice para acceder a la posicion uno del vector rowcol
	mov rax, 0 	; Incializar en cero indexMat
	mov eax, [rdi]		; Se obtiene y guarda en (eax) la fila actual del cursor en el tablero (rowcol[0])
	mov ebx, [rdi+rsi]	; Se obtiene y guarda en (ebx) la Columna actual del cursor en el tablero (rowcol[1])
	IMUL eax, DimMatrix		; Calcular posicion inicial en la fila (rowcol[0]*DimMatrix)
	;add dword[rax], eax; Sumamos el valor a indexMat
	add eax, ebx; Se suma el indice de la columna (indexMat=(rowcol[0]*DimMatrix)+(rowcol[1])) 
							; para obtener el valor del índice para acceder a la matriz (marks) y (mines)
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rdi
	pop rsi
	pop rdx
	pop rcx
	pop rbx
   		
	mov rsp, rbp
	pop rbp
	ret


;;;;;  
; Marcar/desmarcar una mina en la matriz (marks) en la posición actual 
; del cursor, indicada por el vector(rowcol), que es recibe como 
; parámetro (fila (rowcol[0]) i columna (rowcol[1])).
; Si en aquella posición de la matriz (marks) hay un espacio en blanco
; y no hemos marcado todas las minas, marcamos una mina poniendo una 
; 'M' y decrementamos el número de minas que quedan por marcar (numMines), 
; que se recibe como parámetro, si en aquella posición de la matriz 
; (marks) hay una 'M', pondremos un espacio (' ') y incrementaremos el
; número de minas que quedan por marcar.
; Si hay otro valor no cambiaremos nada.
; Retornar el número de minas que quedan por marcar actualizado.
; Calcular el valor del índice, que se deja en el registre eax, para 
; acceder a la matriz (marks) a partir de los valores de la fila y la 
; columna (posición actual del cursor) que tenemos en (rowcol), llamando
; a la subrutina calcIndexP2. (eax=(rowcol[0]*DimMatrix)+(rowcol[1]))
; No se tiene que mostrar la matriz.
; 
; Variables globales utilizadas:
; marks    : Matriz con las minas marcadas y las minas de las abiertas.
; 
; Parámetros de entrada: 
; rdi      : Dirección del vector de 2 posiciones donde guardamos la fila 
;            (rowcol[0]) y la columna (rowcol[1]) del cursor dentro del tablero.
; rsi(esi) : Número de minas que quedan por marcar.
; 
; Parámetros de salida: 
; rax(eax) : Número de minas que quedan por marcar.
;;;;;  
mineMarkerP2:
	push rbp
	mov  rbp, rsp
	
	call calcIndexP2	; Calcular el valor del índice, para acceder a la matriz (marks)

	;mov esi, [indexMat]	; Se pasa el valor de "indexMat" a el registro "esi"
marcar:							; Marcar posicion de la matriz
	cmp byte[marks + eax], ' '	; Comparar posicion en la matriz (marks) 
	jne desmarcar				; Si la posicion no es igual a ' ' saltamos a la etiqueta (desmarcar)
	cmp esi, 0					; Verificamos la cantidad de minas marcadas (numMines)
	je desmarcar				; Si el numero de minas que faltan por marcar es igual a cero saltamos a la etiqueta (desmarcar)
	mov byte[marks + eax], 'M'	; Se coloca como marcada (M) la posición
	dec esi						; Se decrementa el numero de minas (numMines)
	;call showMinesP1			; Mostrar el numero de minas (numMines)
	jmp end2
desmarcar:						; Desmarcar posicion de la matriz
	cmp byte[marks + eax], 'M'	; Comparar posicion en la matriz (marks) 
	jne end2					; Si la posicion no es igual a 'M' saltamos a la etiqueta (end2) y finaliza la funcion
	inc esi						; Se incrementa el numero de minas (numMines)
	mov byte[marks + eax], ' '	; Se coloca como desmarcada (' ') la posición
	;call showMinesP1			; Mostrar el numero de minas (numMines)
end2:
	mov eax, esi
	mov rsp, rbp
	pop rbp
	ret
		

;;;;;  
; Abrir casilla. Mirar cuantas minas hay alrededor de la posición 
; actual del cursor, indicada por el vector (rowcol) que se recibe como 
; parámetro (fila (rowcol[0]) y columna (rowcol[1])), de la 
; matriz (mines).
; Si en la posición actual de la matriz (marks) hay un espacio (' ') 
;   Mirar si en la matriz (mines) hay una mina ('*').
;   Si hay una mina cambiar el estado (state), que se recibe como 
;     parámetro a 3 "Explosión", para salir.
;	 Si no, contar cuantas minas hay alrededor de la posición 
;     actual y actualizar la posición del matriz (marks) con 
;     el número  de minas (carácter ASCII del valor, para hacerlo, hay 
;     que sumar 48 ('0') al valor).
; Si no hay un espacio, quiere decir que hay una mina marcada ('M') o 
; la casilla ya está abierta (hay el número de minas que ya se ha 
; calculado anteriormente), no hacer nada.
; Retornar el estado del juego actualizado.
; No se tiene que mostrar la matriz.
;  
; Variables globales utilizadas:
; marks  : Matriz con las minas marcadas y las minas de las abiertas.
; mines  : Matriz donde ponemos las minas.
; 
; Parámetros de entrada : 
; rdi      : Dirección del vector de 2 posiciones donde guardamos la fila 
;            (rowcol[0]) y columna (rowcol[1])) del cursor dentro del tablero.
; rsi(esi) : Estado del juego. 
; 
; Parámetros de salida: 
; rax(eax) : Estado del juego. 
;;;;;  
searchMinesP2:
	push rbp
	mov  rbp, rsp
	
	push rdi
	
	call calcIndexP2	; Calcular el valor del índice, para acceder a la matriz (marks)
space:
	cmp byte[marks + eax], ' '	; Comparar posicion en la matriz (marks) 
	jne notSpace				; Si la posicion no es igual a ' ' saltamos a la etiqueta (desmarcar)
	cmp byte[mines + eax], '*'	; Comparar posicion en la matriz (marks)
	jne countMines
	mov esi, 3
	jmp end3
countMines:
	push rsi
	push rdi			; Posicion actual			
	push rax			; Indice
	mov rsi, 0
	mov r8, 4
upper:
	dec qword[rdi]
	call calcIndexP2
	cmp byte[mines + eax], '*'
	jne upperRight
	inc rsi
upperRight:
	inc qword[rdi+r8]
	call calcIndexP2
	cmp byte[mines + eax], '*'
	jne right
	inc rsi
right:	
	inc qword[rdi]
	call calcIndexP2
	cmp byte[mines + eax], '*'
	jne lowerRight
	inc rsi
lowerRight:
	inc qword[rdi]
	call calcIndexP2
	cmp byte[mines + eax], '*'
	jne lower
	inc rsi
lower:
	dec qword[rdi+r8]
	call calcIndexP2
	cmp byte[mines + eax], '*'
	jne lowerLeft
	inc rsi
lowerLeft:	
	dec qword[rdi+r8]
	call calcIndexP2
	cmp byte[mines + eax], '*'
	jne left
	inc rsi
left:
	dec qword[rdi]
	call calcIndexP2
	cmp byte[mines + eax], '*'
	jne upperLest
	inc rsi
upperLest:
	dec qword[rdi]
	call calcIndexP2
	cmp byte[mines + eax], '*'
	jne updateMarks
	inc rsi
updateMarks
	pop rax			; Indice
	pop rdi			; Posicion actual
	add sil, '0'
	mov byte[marks + eax], sil
	pop rsi
	jmp end3
notSpace:
end3:
	mov eax, esi
	
	pop rdi
	mov rsp, rbp
	pop rbp
	ret


;;;;;  
; Verificar si hemos marcado todas las minas (numMines=0), que se reciben
; como parámetro y hemos abierto o marcado con una mina todas las otras 
; casillas y no hay ningún espacio en blanco (' ') en la matriz (marks),
; si es así, cambiar el estado (state) que se recibe como parámetro, a 
; 2 "Gana la partida".
; Retornar el estado del juego actualizado.
; 
; Variables globales utilizadas:	
; marks  : Matriz con las minas marcadas y las minas de las abiertas.
; 
; Parámetros de entrada : 
; rdi(edi) : Número de minas que quedan por marcar.
; rsi(esi) : Estado del juego. 
; 
; Parámetros de salida: 
; rax(eax) : Estado del juego. 
; 
;;;;;  
checkEndP2:
	push rbp
	mov  rbp, rsp

	push rdi	; Guardamos el numero minas que quedan por marcar en la pila
	push rsi
				;recorremos la matriz con dos índices para sumarla
	mov esi,0 	;ebp será el índice de la columna
	mov edi,0 	;esp será el índice de la fila
	mov r8, 0
loop_marks1:
	cmp byte[marks+edi+esi], ' ' ; Posicion en la matriz
	jne mark
	inc r8
mark	
	inc esi 					; Incrementamos en una unidad el indice de columna (esi)
	cmp esi, DimMatrix 			; Comparamos con 10 porque son la cantodad elementos de una fila.
	jl loop_marks1
	mov esi, 0					; Indice de la columna inicializado en cero
	add edi, DimMatrix 			; Cada fila ocupa 10 bytes, 10 elementos de 1 byte.
	cmp edi, SizeMatrix 		; Comparamos con 100 para saber cuando llegamos a la ultima posicion de la matriz
	jl loop_marks1
	
	pop rsi
	pop rdi
	cmp edi, 0  		;if (numMines == 0) {	
	jne checkEndP2_End
	cmp r8, 0  		;if (notOpenMarks == 0) {	
	jne checkEndP2_End
	
	mov rsi, 2     ;state = 2;
	mov eax, esi
	checkEndP2_End:
	mov rsp, rbp
	pop rbp
	ret


;;;;;
; Juego del Buscaminas
; Subrutina principal del juego
; Esta subrutina se da hecha. NO LA PODÉIS MODIFICAR.
; Permite jugar al juego del buscaminas llamando a todas las funcionalidades.
;
; Pseudo código:
; Inicializar estado del juego, (state=1)
; Inicializar fila y columna, posición inicial, (rowcol[0]=4) i (rowcol[1]=4)
; Mostrar el tablero de juego (llamando la función PrintBoardP2_C).
; Mientras (state=1) hacer:
;   Actualizar el contenido del Tablero de Juego y el número de minas
;     que quedan por marcar (llamar la subrutina updateBoardP2).
;   Posicionar el cursor dentro del tablero (llamar la subrutina posCurScreenP2).
;   Leer una tecla.
;   Según la tecla leída llamaremos a la función correspondiente.
;     - ['i','j','k' o 'l']       (llamar a la subrutina MoveCursorP2).
;     - 'x'                       (llamar a la subrutina MineMarkerP2).
;     - '<espace>'(codi ASCII 32) (llamar a la subrutina SearchMinesP2).
;     - '<ESC>'  (codi ASCII 27) poner (state = 0) para salir.   
;   Verificar si hemos marcado todas las minas y si hemos abierto todas  
;     las otras casillas (llamar a la subrutina CheckEndP2).
; Fin mientras.
; Salir:
;   Actualizar el contenido del Tablero de Juego y el número de minas que 
;   quedan por marcar (llamar a la subrutina updateBoardP2_C).
;   Mostrar el mensaje de salida que corresponda (llamar a la función
;   printMessageP2_C).
; Se acaba el juego.
; 
; Variables globales utilizadas:	
; Ninguna
; 
; Parámetros de entrada : 
; nMines : rdi(edi) : Número de minas que quedan por marcar.
; 
; Parámetros de salida: 
; nMines : rax(eax) : Número de minas que quedan por marcar.
;;;;;  
playP2:
   push rbp
   mov  rbp, rsp

   push rdi
   call printBoardP2_C   ;printBoard2_C();
   pop  rdi
   
		            ;Declaración de variable local.
   sub rsp, 8       ;Reservamos 8 bytes para el vector rowcol formado por 
                    ;dos posiciones de tipo int (4 bytes cada una)
                    ;rsp: contiene la dirección del vector.
   mov rbx, rsp     ;guardamos la dirección del vector rowcol.
                    ;int  rowcol[2];
                    ;El resto de variables se almacena sobre registros.
   push rbx
   push rcx
   push rdx
   push rdi
   push rsi

   mov DWORD[rbx+0], 4   ;rowcol[0]=  4; //Posición inicial del cursor.
   mov DWORD[rbx+4], 4   ;rowcol[1] = 4; 
   mov ecx, edi          ;int numMines = nMines; 
   mov edx, 1            ;int state = 1; 

   playP2_Loop:          ;bucle principal del juego
   cmp  edx, 1
   jne  playP2_PrintMessage

   mov  edi, ecx
   call updateBoardP2    ;updateBoardP2_C(numMines);

   mov  rdi, rbx
   call posCurScreenP2   ;posCurScreenP2_C(rowcol); 

   call getchP2     ; Leer una tecla y dejarla en el registro al.
		
   cmp al, 'i'		; mover cursor arriba
   je  playP2_MoveCursor
   cmp al, 'j'		; mover cursor izquierda
   je  playP2_MoveCursor
   cmp al, 'k'		; mover cursor derecha
   je  playP2_MoveCursor
   cmp al, 'l'		; mover cursor a bajo
   je  playP2_MoveCursor
   cmp al, 'm'		; Marcar una mina
   je  playP2_MineMarker
   cmp al, ' '		; Mirar minas
   je  playP2_SearchMines
   cmp al, 27		; Salir del programa
   je  playP2_Exit
   jmp playP2_Check  
    
   playP2_MoveCursor:
   mov  rdi, rbx
   mov  sil, al 
   call moveCursorP2     ;moveCursorP2_C(rowcol, c);
   jmp  playP2_Check

   playP2_MineMarker:
   mov  rdi, rbx
   mov  esi, ecx
   call mineMarkerP2     ;numMines = mineMarkerP2_C(rowcol, numMines);
   mov  ecx, eax
   jmp  playP2_Check

   playP2_SearchMines:
   mov  rdi, rbx
   mov  esi, edx
   call searchMinesP2    ;state = searchMinesP2_C(rowcol, state);
   mov  edx, eax
   jmp  playP2_Check

   playP2_Exit:
   mov  edx, 0            ;state = 0;
 
   playP2_Check:
   mov  edi, ecx
   mov  esi, edx
   call checkEndP2       ;state = checkEndP2_C(numMines, state);
   mov  edx, eax
   
   jmp  playP2_Loop

   playP2_PrintMessage:
   mov  edi, ecx
   call updateBoardP2    ;updateBoardP2_C(numMines);

   mov  edi, edx
   push rcx
   call printMessageP2_C ;printMessageP2_C(state);
   pop  rcx
   
   playP2_End:
   mov  eax, ecx

   pop  rdi
   pop  rsi
   pop  rdx
   pop  rcx
   pop  rbx
   
   mov rsp, rbp
   pop rbp
   ret
