
/*
----------------------------------------------------
-- Datos Generales ---------------------------------
----------------------------------------------------
   Nombre:
   Alberto Jesus Tepale Diagas
----------------------------------------------------
-- Documentaci�n -----------------------------------
----------------------------------------------------
   Se contempla un maximo aproximado de 65 figuras
   Numero maximo de vertices por figura es 4
   Numero maximo de vertices por figura es 3
   Se necesitan por lo menos 2 fuguras
   El limite de vertices es 260
----------------------------------------------------
*/



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#define LIM_VERTICES 260




//------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------- Definicion de una estructura de tipo Objeto
//------------------------------------------------------------------------------------------------------------------------------------

struct objeto{
	int x[4];
	int y[4];
	int numVertices;
} typedef Objeto;

struct nodo {
	char nombre[2];
	int x;
	int y;
} typedef Nodo;

struct Grafo{
	bool iniciado;
	int numNodos;
	Nodo nodo[LIM_VERTICES];
	char arista[LIM_VERTICES][LIM_VERTICES];
} typedef Grafo;




//------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------- Menu de opciones
//------------------------------------------------------------------------------------------------------------------------------------

int menu () {
	system("cls");

	int opc;

	pintar_encabezado("Menu de opciones en el presente programa");
	printf(" 01) Crear o complementar mapa\n");
	printf(" 02) Agregar un objeto al mapa\n");
	printf(" 03) Imprimir el mapa actual\n");
	printf(" 04) Crear grafo con el mapa dado\n");
	printf(" 05) Imprimir nodos grafo actual\n");
	printf(" 06) Imprimir lista de adyacencia\n");
	printf(" 07) Mostrar camino respecto al grafo\n");
	printf(" 10) Salir del menu de opciones\n");
	pintar_linea_primaria();
	printf(" Digita la opcion: ");
	scanf ("%d", &opc);

	return opc;
}




//------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------- Funciones de apoyo en formato de escritura
//------------------------------------------------------------------------------------------------------------------------------------

void pintar_linea_primaria () {
	printf ("-----------------------------------------------------------\n");
}

void pintar_linea_primaria_validar (int limite, int pos_actual) {

	if (pos_actual+1 == limite) {
		return;
	}

	printf ("-----------------------------------------------------------\n");
}

void pintar_linea_secundaria () {
	printf ("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
}

void pintar_saltos (int numero_saltos) {
	int i=0;
	while (i<numero_saltos){
		printf("\n");
		i++;
	}
}

void pintar_encabezado (char descripcion[]) {
	pintar_linea_primaria();
	printf (" %s\n", descripcion);
	pintar_linea_primaria();
}

void pintar_mensaje_error (char descripcion[]) {
	pintar_linea_primaria();
	printf (" ERROR: %s ...\n", descripcion);
	pintar_linea_primaria();
	pintar_saltos(3);
	system ("pause");
}

void pintar_mensaje_exito (char descripcion[]) {
	pintar_linea_primaria();
	printf (" EXITO: %s ...\n", descripcion);
	pintar_linea_primaria();
	pintar_saltos(3);
	system ("pause");
}

void pintar_solicitar (char descripcion[]) {
	printf (" %s: ", descripcion);
}




//------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------- Funciones de apoyo en funciones de menu
//------------------------------------------------------------------------------------------------------------------------------------

bool dentro_del_limite (int lim, int val){
	if(val < lim){
		return true;
	}else{
		return false;
	}
}

int numero_vertices_objetos_en_mapa (Objeto mapa[], int limiteObjetos) {

	int contador=0, i;

	for (i=0; i<limiteObjetos; i++) {
		contador = contador+mapa[i].numVertices;
	}

	return contador;
}

Grafo inicializar_grafo_matriz(Grafo grafo, int nodos){

	grafo.numNodos = nodos;
	grafo.iniciado = true;

	int i, j;

	for(i=0; i<nodos; i++){
		for(j=0; j<nodos; j++){
			grafo.arista[i][j] = 0;
		}
	}

	return grafo;
}

Grafo nombrar_nodos_grafo (Grafo grafo, int nodos) {

	char cst[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	char csn[] = {'0','1','2','3','4','5','6','7','8','9'};

	int i=0, x=0, j=0;

	while (x<nodos && i<26) {
		j=0;
		while (x<nodos && j<10) {
			grafo.nodo[x].nombre[0] = cst[i];
			grafo.nodo[x].nombre[1] = csn[j];
			x++;
			j++;
		}
		i++;
	}

	return grafo;
}

Grafo ubicar_nodos_grafo (Objeto mapa[], int lim_objetos, Grafo grafo) {

	int i, j, pos=0;

	for (i=0; i<lim_objetos; i++) {
		for (j=0; j<mapa[i].numVertices; j++) {
			switch (j) {
				case 0:
					grafo.nodo[pos].x = mapa[i].x[j]-1;
					grafo.nodo[pos].y = mapa[i].y[j]-1;
					break;
				case 1:
					grafo.nodo[pos].x = mapa[i].x[j]+1;
					grafo.nodo[pos].y = mapa[i].y[j]-1;
					break;
				case 2:
					grafo.nodo[pos].x = mapa[i].x[j]+1;
					grafo.nodo[pos].y = mapa[i].y[j]+1;
					break;
				case 3:
					grafo.nodo[pos].x = mapa[i].x[j]-1;
					grafo.nodo[pos].y = mapa[i].y[j]+1;
					break;
			}
			pos++;
		}
	}

	return grafo;
}

int posicionNodo(Grafo grafo, char nodo[]) {

	int i, pos=-1;

	for (i=0; i<grafo.numNodos; i++){
		if (strcmp(grafo.nodo[i].nombre, nodo)==0) {
			pos = i;
			break;
		}
	}

	return pos;
}

bool existeNodoEnGrafo (Grafo grafo, char nodo[]) {

	bool existe = false;
	int i;

	for (i=0; i<grafo.numNodos; i++){
		if (strcmp(grafo.nodo[i].nombre, nodo)==0) {
			existe = true;
			break;
		}
	}

	return existe;

}



Grafo crearAdyacencia (Grafo grafo, char origen[], char destino[]) {

	int posOrigen = posicionNodo(grafo, origen);
	int posDestino = posicionNodo(grafo, destino);

	grafo.arista[posOrigen][posDestino] = 1;
	grafo.arista[posDestino][posOrigen] = 1;

	return grafo;
}

Grafo crearAdyacenciasInternas (Objeto mapa[], int objetos_lim, Grafo grafo) {

	int i, j, pos=0;

	for (i=0; i<objetos_lim; i++) {
		for (j=0; j<mapa[i].numVertices; j++) {

			if (mapa[i].numVertices == j+1) {
				grafo = crearAdyacencia(grafo, grafo.nodo[pos].nombre, grafo.nodo[pos-j].nombre);
			}else{
				grafo = crearAdyacencia(grafo, grafo.nodo[pos].nombre, grafo.nodo[pos+1].nombre);
			}

			pos++;
		}
	}

	return grafo;

}

float determinarDistanciaEntreDosNodos (Nodo origen, Nodo destino) {

	float distancia = sqrt(pow ((destino.x-origen.x), 2) + (pow ((destino.y-origen.y), 2)));

	return distancia;
}

Grafo crearAdyacenciasExternas (Objeto mapa[], int lim_objetos, Grafo grafo) {

	int i, j, k, pvf1=0, pvf2=0, pOrigen, pDestino;
	float distancia, minDistancia;

	for (i=0; i<lim_objetos-1; i++) {

		pvf2 = pvf1 + mapa[i].numVertices;

		minDistancia = determinarDistanciaEntreDosNodos(grafo.nodo[pvf1], grafo.nodo[pvf2]);
		pOrigen = pvf1;
		pDestino = pvf2;

		for (j=0; j<mapa[i].numVertices; j++) {

			for (k=0; k<mapa[i+1].numVertices; k++) {

				//Vertice origen: pvf1    Vertice destino pvf2+k

				distancia = determinarDistanciaEntreDosNodos(grafo.nodo[pvf1], grafo.nodo[pvf2+k]);

				if (distancia<minDistancia) {
					minDistancia = distancia;
					pOrigen = pvf1;
					pDestino = pvf2 + k;
				}

			}

			pvf1++;
		}

		//printf ("Distancia minima: %d con %d = %f\n\n", pOrigen, pDestino, minDistancia);

		grafo = crearAdyacencia(grafo, grafo.nodo[pOrigen].nombre, grafo.nodo[pDestino].nombre);

	}

	return grafo;
}




//------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------- Funciones operacionales - principales en menu
//------------------------------------------------------------------------------------------------------------------------------------

Objeto agregar_objeto_al_mapa () {

	Objeto newObjeto;

	//Solicitamos el numero de vertices, y validamos que no sobre pase de 4
	int lim_vertices;
	pintar_solicitar("Ingresa el numero de vertices");
	scanf("%d", &lim_vertices);
	pintar_linea_secundaria();

	if (lim_vertices>4) {
		lim_vertices = 4;
	}
	if(lim_vertices<3){
		lim_vertices = 3;
	}

	//Asignamos la cantidad de vertices al objeto
	newObjeto.numVertices = lim_vertices;

	//Solicitamos los puntos (x,y) de los vertices
	int i;
	for (i=0; i<lim_vertices; i++) {
		printf("  Vertice [%d] X : ", i+1);
		scanf("%d", &newObjeto.x[i]);
		printf("  Vertice [%d] Y : ", i+1);
		scanf("%d", &newObjeto.y[i]);
	}

	return newObjeto;
}

void imprimir_objeto_de_mapa (Objeto objeto) {

	printf (" EL numero de vertices es: %d \n", objeto.numVertices);

	pintar_linea_secundaria();

	int i;

	for (i=0; i<objeto.numVertices; i++) {
		printf ("  Vertice [%d] (x,y) - (%d, %d) \n", i+1, objeto.x[i], objeto.y[i]);
	}

}

void imprimir_nodos_grafo (Grafo grafo) {

	printf ("Numero de nodos en el grafo: %d \n", grafo.numNodos);

	pintar_linea_secundaria();

	int i;
	for (i=0; i<grafo.numNodos; i++) {
		printf(" %s (%d, %d) \n", grafo.nodo[i].nombre, grafo.nodo[i].x, grafo.nodo[i].y);
	}

}

void imprimir_lista_adyacencias (Grafo grafo) {

	printf ("Numero de nodos en el grafo: %d \n", grafo.numNodos);

	pintar_linea_secundaria();

	int i, j;
	for (i=0; i<grafo.numNodos; i++) {

		printf (" [%s] ", grafo.nodo[i].nombre);

		for (j=0; j<grafo.numNodos; j++) {
			if (grafo.arista[i][j] == 1) {
				printf ("--> [%s] ", grafo.nodo[j].nombre);
			}
		}
		printf("\n");
	}

}

void imprimirCamino (Grafo grafo, char origen[], char destino[]) {

	//Determinamos posicion de los vertices
	int posOrigen = posicionNodo (grafo, origen);
	int posDestino = posicionNodo (grafo, destino);

	//Asiganar a variables, para no perder los valores iniciales
	int i=posOrigen, j = posDestino;
	int lista [grafo.numNodos], listados = 0;

	bool destinoHallado = false, posListada;
	int i2, i3;

	while (!destinoHallado) {

		if (grafo.arista[i][j] == 1) {
			lista[listados] = i;
			listados ++;
			destinoHallado = true;
		}else{

			lista[listados] = i;
			listados ++;

			if (posOrigen > posDestino) {
				//DESCENDENTE..
				posListada = false;
				for (i2=0; i2<grafo.numNodos; i2++) {

					if (grafo.arista[i][i2] == 1) {
						posListada = false;
						for (i3=0; i3<listados; i3++) {
							if (lista[i3] == i2) {
								posListada = true;
								break;
							}
						}

						if (!posListada && (posDestino-i2<=3)) {
							i = i2;
							break;
						}
					}

				}
			}else{
				//ASCENDENTE..
				posListada = false;
				for (i2=grafo.numNodos; i2>=0; i2--) {

					if (grafo.arista[i][i2] == 1) {
						posListada = false;
						for (i3=0; i3<listados; i3++) {
							if (lista[i3] == i2) {
								posListada = true;
								break;
							}
						}

						if (!posListada) {
							i = i2;
							break;
						}
					}
				}
			}
		}
	}

	//Agregamos el destino al camino
	lista[listados] = posDestino;
	listados ++;

	pintar_linea_secundaria();

	for (i=0; i<listados; i++) {
		printf ("%s --> ", grafo.nodo[lista[i]].nombre);
	}

	printf("\n");

	pintar_mensaje_exito("Se imprimio el camino con exito");

}


//------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------- Funcion main - ejecucion de las dem�s
//------------------------------------------------------------------------------------------------------------------------------------

int main(int argc, char *argv[]) {

	//Solicitamos el numero de objetos que contendr� el mapa
	int objetos_lim;

	pintar_encabezado("Solicitud de informacion inicial");
	pintar_solicitar ("Ingresa el numero de objetos en el mapa");
	scanf("%d", &objetos_lim);

	if (objetos_lim < 2) {
		objetos_lim = 2;
	}

	pintar_linea_primaria();

	//Un mapa es un conjunto de objetos en un plano 2D
	Objeto mapa[objetos_lim];
	int objetos_cont = 0;

	//Variable de uso general
	int opc, i, var;
	char val1[5], val2[5];

	//Datos para la creacion del grafo
	Grafo grafo;
	grafo.iniciado = false;

	do {
		opc = menu();

		pintar_saltos(3);

		switch (opc){
			case 1:
				pintar_encabezado("Ingresa los vertices de las figuras");

				if (!dentro_del_limite(objetos_lim, objetos_cont)){
					pintar_mensaje_error("Ya no se encuentra dentro del limite");
				}else{
					for (i=objetos_cont; i<objetos_lim; i++) {
						mapa[i] = agregar_objeto_al_mapa();
						pintar_linea_primaria_validar(objetos_lim, i);
					}
					objetos_cont=objetos_lim;
					pintar_mensaje_exito("Se ha creado correctamente el mapa");
				}

				break;
			case 2:
				pintar_encabezado("Ingresa los vertices del objeto");

				if (!dentro_del_limite(objetos_lim, objetos_cont)){
					pintar_mensaje_error("Ya no se encuentra dentro del limite");
				}else{
					mapa[objetos_cont] = agregar_objeto_al_mapa();
					objetos_cont++;
					pintar_mensaje_exito("Se ha agregado el objeto");
				}

				break;
			case 3:
				pintar_encabezado("Imprimiendo los objetos del mapa actual");

				if(objetos_cont <= 0){
					pintar_mensaje_error("No hay objetos en el mapa");
				}else{
					for (i=0; i<objetos_cont; i++){
						imprimir_objeto_de_mapa(mapa[i]);
						pintar_linea_primaria_validar(objetos_cont, i);
					}
					pintar_mensaje_exito("Se imprimio correctamente el mapa");
				}

				break;

			case 4:
				pintar_encabezado("Crear grafo a partir de los objetos en el mapa");

				if (!(objetos_cont < objetos_lim)) {

					var = numero_vertices_objetos_en_mapa (mapa, objetos_lim);

					grafo = inicializar_grafo_matriz(grafo, var);
					grafo = nombrar_nodos_grafo(grafo, var);
					grafo = ubicar_nodos_grafo(mapa, objetos_lim, grafo);
					grafo = crearAdyacenciasInternas (mapa, objetos_lim, grafo);
					grafo = crearAdyacenciasExternas (mapa, objetos_lim, grafo);

					pintar_mensaje_exito("Se ha generado el grafo");

				}else{
					pintar_mensaje_error("No se han ingresado todos los objetos");
				}

				break;
			case 5:
				pintar_encabezado("Imprimir nodos grafo creado");

				if (!(objetos_cont < objetos_lim)) {

					if(grafo.iniciado){
						imprimir_nodos_grafo(grafo);
						pintar_mensaje_exito("Se imprimio el grafo con exito");
					}else{
						pintar_mensaje_error("No se ha creado el grafo");
					}

				}else{
					pintar_mensaje_error("No se han ingresado todos los objetos");
				}

				break;
			case 6:
				pintar_encabezado("Imprimir lista de adyacencia");

				if (!(objetos_cont < objetos_lim)) {

					if(grafo.iniciado){
						imprimir_lista_adyacencias(grafo);
						pintar_mensaje_exito("Se imprimio la lista con exito");
					}else{
						pintar_mensaje_error("No se ha creado el grafo");
					}

				}else{
					pintar_mensaje_error("No se han ingresado todos los objetos");
				}

				break;
			case 7:
				pintar_encabezado("Imprimir camino (Origen, Destino)");

				if (!(objetos_cont < objetos_lim)) {

					if(grafo.iniciado){

						printf(" Ingresa nombre origen: ");
						scanf("%s", val1);

						printf(" Ingresa nombre destino: ");
						scanf("%s", val2);

						if (existeNodoEnGrafo(grafo, val1) && existeNodoEnGrafo(grafo, val2)) {

							if (strcmp(val1, val2)!=0) {

								imprimirCamino (grafo, val1, val2);

							}else{
								pintar_mensaje_error("El origen y destino es el mismo");
							}

						}else{
							pintar_mensaje_error("No existe un nodo o los dos");
						}

					}else{
						pintar_mensaje_error("No se ha creado el grafo");
					}

				}else{
					pintar_mensaje_error("No se han ingresado todos los objetos");
				}

				break;
			default:
				pintar_mensaje_error("No se ha encontrado la opcion digitada");
				break;
		}

	} while (opc != 10);

	return 0;
}
