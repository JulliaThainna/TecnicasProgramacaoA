#include <stdio.h>
#include <stdlib.h>

typedef struct elemento{
	int info;
	struct elemento *prox;
}No;

No* adicionaLista(No *inicio, int num);
No* imprimeLista(No *inicio);
No* deletaLista(No *inicio);

int main(){
	No *inicio;
	inicio = NULL;
	inicio = adicionaLista(inicio,5);
	inicio = adicionaLista(inicio,6);
	inicio = imprimeLista(inicio);
	inicio = deletaLista(inicio);
	inicio = imprimeLista(inicio);

	return 0;
}

No* adicionaLista(No *inicio, int num){
	/*Se a lista estiver vazia (NULL), então adiciona um elemento e o prox aponta pra NULL
	Se a lista já tiver elementos, percorrer a lista até achar o ultimo elemento que aponta para NULL,
	podendo assim adicionar um novo elemento a lista*/
	No* node = (No*) malloc(sizeof(No));
	node->info = num;
	if(inicio == NULL){
		inicio = node;
		inicio->prox = NULL;
		printf("Lista criada");
		return inicio;
	}
	No *aux;
	aux = inicio;
	while(aux->prox != NULL){
		aux = aux->prox;
	}
	aux->prox = node;
	node->prox = NULL;
	printf("\nElemento adicionado");
	return inicio;
}

No* imprimeLista(No *inicio){
	No *aux;
	aux = inicio;
	while(aux != NULL){
		printf("\n%d ",aux->info);
		aux = aux->prox;
	}
	return inicio;
}

No* deletaLista(No *inicio){
	No *aux,*prox;
	aux = inicio;
	while(aux != NULL){ //aux->prox
		prox = aux->prox;
		free(aux);
		aux = prox;
	}
	inicio = NULL;
	return inicio;
}
