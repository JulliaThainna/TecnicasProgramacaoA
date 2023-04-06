#include <stdio.h>
#include <stdlib.h> //pra funções de alocação dinâmica

//guarda as informações dos elementos
typedef struct elemento{
  int info;
  struct elemento *prox;
}No;

//Registros -->E se ao invés de por registros, eu não coloque a main por último?
No *adicionarElemento(No *inicio, int n);
No *imprimirElemento(No *inicio);
No *deletarLista(No *inicio);
No *deletarElemento(No *inicio, int n);

int main(){
  No *inicio; //cria o inicio da lista (NUNCA MEXER DIRETAMENTE NELE) -->Não entendo aqui (Por ele ser um ponteiro do tipo no, eu consigo ter os atributos
  //int info e *prox), só pra isso?
  inicio = NULL; //A lista começa vazia
  inicio = adicionarElemento(inicio,4);
  inicio = adicionarElemento(inicio,5);
  inicio = adicionarElemento(inicio,6);
  inicio = imprimirElemento(inicio);
  inicio = deletarElemento(inicio,5);
  inicio = imprimirElemento(inicio);
  inicio = deletarLista(inicio);
  return 0;
}

No *adicionarElemento(No *inicio,int n){
  /*Condições para adicionar elementos na lista:
  1 - A lista estiver vazia (NULL)
  2 - A lista já conter elementos*/

  //nó que será adicionado na lista
  No *node = (No*) malloc(sizeof(No)); //aloca um espaço de memoria na heap para o novo nó
  node->info = n; //NÃO ESQUECER ESSA LINHA, a informação que no vai guardar vai ser um int e nao o seu endereço'
  if(inicio == NULL){ //1a. condição
    inicio = node; //inicio a partir de agora é o novo nó que foi adicionado
    node->prox = NULL; //Como agora nenhum elemento aponta pra NULL, o proximo elemento depois do node aponta pra NULL
    printf("\nPrimeiro elemento adicionado com sucesso!");
    return inicio;
  }
  No *aux;
  aux = inicio; //como inicio não pode ser mexido então cria-se uma var aux para receber seu endereço
  while(aux->prox != NULL){ //2a. condição (tem que percorrer toda a lista para achar o último elemento) -->aux->prox e não só aux ???
    aux = aux->prox;
  }
  //quando aux->prox == NULL
  aux->prox = node;
  node->prox = NULL;
  printf("\nElemento adicionado com sucesso!");
  return inicio;
}

No *imprimirElemento(No *inicio){ //será preciso percorrer toda a lista para printar seus elementos
  No *aux;
  aux = inicio;
  printf("\n\t ELEMENTOS: \n\t");
  while(aux != NULL){
    printf("%d-->",aux->info);
    aux = aux->prox;
  }
  printf("    NULL");
  return inicio; //por que tem que retornar o inicio aqui??? Não pode ser void??
}

No *deletarLista(No *inicio){ //refazer essa função
  No *aux, *prox;
  aux = inicio;
  //percorrer a lista toda, apagando elemento por elemento
  while(aux != NULL){ //enquanto o proximo elemento for diferente de NULL
    //Usa-se aux ao inves de aux->prox porque, se for usado aux->prox o ultimo elemento não vai ser apagado e sobrará memoria ainda
    prox = aux->prox; //prox vai guardar o proximo elemento, porque quando for dado free(aux) aux vai sumir
    free(aux); //libera memoria
    aux = prox; //aux vai receber o proximo que ficou guardado em prox
  }
  inicio = NULL; //quando aux->prox for == NULL, então o inicio == NULL e a lista estará vazia
  printf("\n Lista deletada com sucesso!");
  return inicio;
}

No *deletarElemento(No *inicio, int n){ //refazer essa função
  /*Condições para deletar um elemento:
  1 - Ele ser o primeiro elemento
  2 - Ele ser o último elemento
  3 - Ele estar no meio
  -cheguei na conclusão que a condição 2 e 3 são juntas*/
  No *aux = inicio, *anterior; //o ponteiro aux vai salvar o começo da lista e o anterior vai salvar o elemento anterior
  if(aux != NULL && aux->info == n){ //se o aux não for NULL(fim da lista ou se a lista existir) e a informação da struct estiver igual
    inicio = aux->prox; //inicio vai receber o proximo elemento
    free(aux); //o primeiro elemento será apagado
    return inicio;
  }
  while(aux != NULL && aux->info != n){ //enquanto o aux não for NULL(fim da lista ou se a lista existir) e a informação da struct estiver diferente
    anterior = aux; //o anterior recebe o aux atual
    aux = aux->prox; //o aux atual recebe o proximo
    //exemplo: se 1 é o atual e 2 o proximo, então 1 se torna o anterior e 2 o atual...
  }
  if(aux == NULL){ //se a lista não existir, ou se a lista inteira for percorrida e o elemento não escontrado
    printf("\nElemento nao existe!");
    return inicio;
  }
  /*Explicação importante!
  No while:
  anterior = aux
  aux = aux->prox, pra facilitar vou usar os elementos 4->5->6->NULL
  anterior = 4
  aux(4) = 5
  --Sai do loop
  anterior->prox = aux->prox
  anterior(5) = aux->prox(6)
  */
  anterior->prox = aux->prox; //se no while o aux->info == n, então o anterior do proximo e o proximo do atual se interligam
  free(aux); //e o elemento atual é deletado
  printf("\nElemento deletado com sucesso!");
  return inicio;
}
