#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int IDOrden;
typedef struct Nodo { // holly, Dio
  int ID;
  char nombre[25];
  // char artista;
  struct Nodo *sig;
  struct Nodo *ant;
} Nodo;

Nodo *buscar(Nodo *NodoAct, int dato) { // holly, Dio
  while (NodoAct != NULL) {
    if (NodoAct->ID == dato)
      return NodoAct;
    NodoAct = NodoAct->sig;
  }
  return NULL;
}
/* Eliminar lista simple
  int eliminar(Nodo **lista, int dato) {
  Nodo *elem;
  if (!(elem = buscar(*lista, dato)))
    return 0; // no se encontro el dato a eliminar

  Nodo *temp = elem;
  elem = temp->sig;
  free(temp);
  return 1; // Verdadero, lo logro eliminar
} */

// Eliminar lista simple
int eliminarNodo(Nodo **lista, int dato) {
  Nodo *nodoBuscado = buscar(*lista, dato); //* nos da un dato Nodo *

  // Si el nodo a eliminar es el primero de la lista, es necesario eliminarlo de
  // esta manera
  if (nodoBuscado == *lista) {
    *lista = (*lista)->sig;
    (*lista)->ant = NULL;
  } else {
    nodoBuscado->ant->sig = nodoBuscado->sig;
    if (nodoBuscado->sig)
      nodoBuscado->sig->ant = nodoBuscado->ant;
  }

  free(nodoBuscado);
  return 0;
}

void insert(Nodo **lista, int X, char *nombreCan) { // holly, Dio
  Nodo *newElem = (Nodo *)malloc(sizeof(Nodo));

  newElem->ID = X;
  strcpy(newElem->nombre, nombreCan);
  newElem->ant = NULL;
  if (*lista)
    (*lista)->ant = newElem;

  newElem->sig = *lista;
  *lista = newElem;
}

int Reproducir(Nodo *lista, int pos) { // Dio

  if (!lista) {
    printf("\033[31mNo hay Nodo a mostrar");
    return 0;
  }
  for (int cont = 0; cont < 10; cont++, lista = lista->ant) {
    if (pos == lista->ID) {
      printf("Estás escuchando\n%d.- %s\n", lista->ID, lista->nombre);
      return 1;
    }
  }
  printf("La canción seleccionada no está en la lista");
  return 0;
}

void paginaSig(Nodo *temp, int *datoSig, int *datoAnt, int n) {

  if (!temp) {
    printf("\033[31mNo hay Nodo a mostrar");
    return;
  }
  int cont = 0;
  *datoAnt = temp->ID;
  while (cont < n) {
    printf("%d.- %s\n", temp->ID, temp->nombre);
    if (temp->ant == NULL) {
      printf("\n No hay Nodo siguientes\n");
      *datoSig = *datoAnt;
      break;
    }

    temp = temp->ant;
    cont++;
    *datoSig = temp->ID;
  }
}

void paginaAnt(Nodo *temp, int *datoSig, int *datoAnt, int n) {

  int cont = 0;
  if (!temp->sig) {
    printf("\033[31m\nNo hay Nodo anteriores");
    return;
  }
  *datoSig = temp->ID;
  for (int cont = 0; cont < n; cont++, temp = temp->sig) {
  }
  cont = 0;
  *datoAnt = temp->ID;
  for (int cont = 0; cont < n; cont++, temp = temp->ant)
    printf("%d.- %s\n", temp->ID, temp->nombre);
}

int main() {
  Nodo *lista = NULL;
  char cadena[2];
  int menup = 0, auxsig, auxant, n = 10, op;

  FILE *archivo;
  char nombreCan[15];
  archivo = fopen("Song.txt", "rt");
  if (archivo == NULL) {
    printf("Error en la apertura del archivo\n");
  } else {
    int i = 1;
    while (!feof(archivo) || i <= 10) {
      fscanf(archivo, "%s", nombreCan);
      insert(&lista, i, nombreCan);
      i++;
    }
  }
  fclose(archivo);

  /*int selec; // holly:D
  printf("1. Explorar Géneros\n");
  printf("2. Explorar Nodo\n");
  printf("3. Explorar Reproductor\n");
  printf("4. salir\n");
  printf("selecciona una opción: \n");
  scanf("%d", &selec);

  switch (selec) {
  case 1:
    printf("Estos son los Géneros: \n");
    break;
  case 2:
    printf("Estas son las Nodo: \n");
    //mostrarCan(lista);
    break;
  case 3:
    printf("Reproductor: ");
    break;
  case 4:
    break;
  default:
    printf("No existe esa opción ");
    break;
  }*/
  Nodo *aux = buscar(lista, 1);
  paginaSig(aux, &auxsig, &auxant, n);

  while (menup == 0) {

    printf("\n----------\n");
    printf(" \033[32mp: Regresar al menu principal\n");
    printf(" \033[33ma: 10 Nodo anteriores\n");
    printf("\033[34m d: 10 Nodo siguientes\n");
    printf("\033[35m q: Agregar a la cola una cancion de la lista\n");
    printf("\033[36m r: Reproducir una cancion\n");
    scanf("%s", cadena);
    int pos;
    switch (cadena[0]) {
    case 'q':
      printf("opción q");
      break;
    case 'r':
      printf("seleccione la canción: ");
      scanf("%d", &pos);
      op = Reproducir(aux, pos);
      while (op != 0) {
        printf("\n1: Anterior     2: Siguiente\n  0: Salir del reproductor\n");
        scanf("%d", &op);
        n = 1;
        switch (op) {
        case 1:
          pos--;
          if (pos <= 1) {
            pos = 1;
            printf("\nNo hay Nodo anteriores");
          }
          aux = buscar(lista, pos);
          printf("\nEstás escuchando:\n%d.- %s\n", aux->ID, aux->nombre);
          break;
        case 2:
          pos++;
          if (aux->ant == NULL) {
            pos = aux->ID;
            printf("\nNo hay Nodo siguientes");
          }
          aux = buscar(lista, pos);
          printf("\nEstás escuchando:\n%d.- %s\n", aux->ID, aux->nombre);
          break;
        default:
          printf("está opción no existe\n");
          break;
        }
      }
      break;
    case 'p':
      menup = 1;
      break;
    case 'a':
      n = 10;
      printf("\033[33m opción a \n");
      aux = buscar(lista, auxant);
      paginaAnt(aux, &auxsig, &auxant, n);
      break;

    case 'd':
      n = 10;
      printf("\033[34mOpción d \n");
      aux = buscar(lista, auxsig);
      paginaSig(aux, &auxsig, &auxant, n);
      break;

    default:
      printf("\033[31mNo existe esa opción");
      break;
    }
  }
  return 0;
}