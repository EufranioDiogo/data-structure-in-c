#include <stdio.h>
#include <stdlib.h>


struct node {
    int valor;
    struct node *anterior;
    struct node *proximo;
} node;

struct node *head;

int length() {
    int size = 0;

    if (head != 0) {
        struct node *auxNode = head;

        while (auxNode != 0) {
            auxNode = auxNode -> proximo;
            size++;
        }
    }
    return size;
}

void addBegin(int valor) {
    struct node *newNode = (struct node*)(malloc(sizeof(struct node)));
    newNode -> valor = valor;

    if (head != 0) {
        newNode -> proximo = head;
        head -> anterior = newNode;
    } else {
        newNode -> proximo = 0;
    }
    newNode -> anterior = 0;
    head = newNode;
}

void addEnd(int valor) {
    if (head == 0) {
        addBegin(valor);
    } else {
        struct node *newNode = (struct node*)(malloc(sizeof(struct node)));
        newNode -> valor = valor;

        struct node *auxNode = head;

        while (auxNode -> proximo != 0) {
            auxNode = auxNode -> proximo;
        }
        auxNode -> proximo = newNode;
        newNode -> anterior = auxNode;
        newNode -> proximo = 0;
    }
}

void addPos(int valor, int pos) {
    if (pos > -1) {
        if (pos == 0) {
            addBegin(valor);
        } else if (pos >= length()) {
            addEnd(valor);
        } else {
            struct node *newNode = (struct node*)(malloc(sizeof(struct node)));
            newNode -> valor = valor;
            struct node *auxNode = head;

            while (pos > 0) {
                auxNode = auxNode -> proximo;
                pos--;
            }

            newNode -> proximo = auxNode;
            newNode -> anterior = auxNode -> anterior;
            auxNode -> anterior -> proximo = newNode;
            auxNode -> anterior = newNode;
        }
    }
}

int deleteBegin() {
    int result = -1;

    if (head != 0) {
        struct node *auxNode = head;
        result = head -> valor;

        head = head -> proximo;
        head -> anterior = 0;
        free(auxNode);
    }
    return result;
}

int deleteEnd() {
    int result = -1;

    if (head != 0) {
        struct node *auxNode = head;
        
        while(auxNode -> proximo != 0) {
            auxNode = auxNode -> proximo;
        }
        result = auxNode -> valor;
        struct node *auxPointerTail = auxNode;

        auxNode = auxNode -> anterior;

        if (auxNode != 0) {
            auxNode -> proximo = 0;
        }
        free(auxPointerTail);
    }
    return result;
}

int deletePos(int pos) {
    if (head != 0) {
        if (pos == 0) {
            return deleteBegin();
        } else if (pos >= length() - 1) {
            return deleteEnd();
        } else {
            struct node *auxNode = head;

            while (pos > 0) {
                auxNode = auxNode -> proximo;
                pos--;
            }
            int result = auxNode -> valor;

            auxNode -> anterior -> proximo = auxNode -> proximo;
            auxNode -> proximo -> anterior = auxNode -> anterior;
            auxNode -> proximo = 0;
            auxNode -> anterior = 0;
            free(auxNode);
            return result;
        }
    }
    return -1;
}

void printList() {
    if (head != 0) {
        struct node *auxNode = head;

        while (auxNode != 0) {
            printf("%d ", auxNode -> valor);
            auxNode = auxNode -> proximo;
        }
    }
}

void reverse() {
    if (head != 0) {
        struct node *currentNode = head;
        struct node *nextNode = currentNode;

        while (currentNode != 0) {
            nextNode = currentNode -> proximo;

            currentNode -> proximo = currentNode -> anterior;
            currentNode -> anterior = nextNode;

            if (nextNode == 0) {
                head = currentNode;
            }
            currentNode = nextNode;
        }

        /*
        struct node *currentNode = head;
        struct node *auxNode = head -> proximo;
        struct node *swapAux;

        while (currentNode != 0) {
            swapAux = currentNode -> proximo;
            currentNode -> proximo = currentNode -> anterior;
            currentNode -> anterior = swapAux;

            currentNode = auxNode;
            if (currentNode != 0) {
                auxNode = currentNode -> proximo;
            }
        }
        head = currentNode -> anterior;*/
    }
}


void printMenu() {
    printf("1 -> Adicionar elemento no inicio.\n");
    printf("2 -> Adicionar elemento no fim.\n");
    printf("3 -> Adicionar elemento em qualquer posicao.\n");
    printf("4 -> Remover elemento no inicio.\n");
    printf("5 -> Remover elemento no fim.\n");
    printf("6 -> Remover elemento em qualquer posicao.\n");
    printf("7 -> Imprimir lista.\n");
    printf("8 -> Tamanho lista.\n");
    printf("9 -> Inverter Lista.\n");
    printf("10 -> Terminar execucao.\n");
}

int main() {
    int decision = 0;
    int flagStop = 0;
    int valor;
    int index;

    while (!flagStop) {
        printMenu();
        scanf("%d", &decision);

        while(decision < 0 || decision > 11) {
            printMenu();
            scanf("%d", &decision);
        }

        printf("\n");
        if (decision > 0 && decision < 4) {
            printf("Valor: ");
            scanf("%d", &valor);

            if (decision == 1) {
                addBegin(valor);
            } else if (decision == 2) {
                addEnd(valor);
            } else {
                printf("Index: ");
                scanf("%d", &index);
                addPos(valor, index);
            }
        } else if (decision > 3 && decision < 7) {
            if (decision == 4) {
                printf("\nElemento removido: %d", deleteBegin());
            } else if (decision == 5) {
                printf("\nElemento removido: %d", deleteEnd());
            } else {
                int posicao = 0;
                int elementoRemovido = 0;

                printf("\nPosição: ");
                scanf("%d", &posicao);

                elementoRemovido = deletePos(posicao);

                if (elementoRemovido == -1) {
                    printf("\nPosição inválida");
                } else {
                    printf("\nElemento removido: %d", elementoRemovido);
                }
            }
        } else if (decision == 7) {
            printList();
        } else if (decision == 8) {
            printf("Tamanho: %d", length());
        } else if (decision == 9) {
            reverse();
        } else {
            flagStop = 1;
        }
        printf("\n");
    }
    printf("Execução terminada\n");
}