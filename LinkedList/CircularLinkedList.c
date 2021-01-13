#include <stdio.h>
#include <stdlib.h>

struct node {
    int valor;
    struct node *next;
} node;

struct node *head;

int length() {
    int size = 0;

    if (head != 0) {
        struct node *auxNode = head;

        while (auxNode -> next != head) {
            size += 1;
            auxNode = auxNode -> next;
        }
        size += 1;
    }
    return size;
}

struct node* getLastNode(){
    struct node *auxNode = head;

    while(auxNode -> next != head) {
        auxNode = auxNode -> next;
    }
    return auxNode;
}

void inserirFim(int valor) {
    struct node *newNode = (struct node*)(malloc(sizeof(struct node)));
    newNode -> valor = valor;

    if (head == 0) {
        head = newNode;
        head -> next = head;
    } else {
        struct node *auxNode = head;
 
        while (auxNode -> next != head) {
            auxNode = auxNode -> next;
        }
        newNode -> next = head;
        auxNode -> next = newNode;
    }
}


void inserirInicio(int valor) {
    struct node *newNode = (struct node*)(malloc(sizeof(struct node)));
    newNode -> valor = valor;

    if (head == 0) {
        head = newNode;
        head -> next = head;
    } else {
        struct node *tail = getLastNode();

        newNode -> next = head;
        tail -> next = newNode;
        head = newNode;
    }
}

void inserirMeio(int index, int valor) {
    if (index <= 0) {
        inserirInicio(valor);
    } else if (index >= length()) {
        inserirFim(valor);
    } else {
        struct node *auxNode = head;
        struct node *previous;
        struct node *newNode = (struct node*)(malloc(sizeof(struct node)));

        newNode -> valor = valor;

        while (index > 0) {
            previous = auxNode;
            auxNode = auxNode -> next;
            index--;
        }
        previous -> next = newNode;
        newNode -> next = auxNode;
    }
}

void imprimirLista() {
    if (head != 0) {
        struct node *auxNode = head;

        while (auxNode -> next != head) {
            printf("%d ", auxNode -> valor);
            auxNode = auxNode -> next;
        }

        printf("%d ", auxNode -> valor);
        printf("\n");
    }
}

int removerInicio() {
    if (head != 0) {
        struct node *nodeFinal = getLastNode();
        struct node *auxNode = head;
        int valor = auxNode -> valor;

        if (head == head -> next) {
            head -> next = 0;
            head = 0;
        } else {
            head = head -> next;
            nodeFinal -> next = head;
        }
        free(auxNode);
        return valor;
    }
    return -1;
}


int removerFinal() {
    if (head != 0) {
        struct node *auxNode = head;
        int valor = head -> valor;

        if (head == head -> next) {
            head -> next = 0;
            head = 0;
        } else {
            while (auxNode -> next -> next != head) {
                auxNode = auxNode -> next;
            }

            struct node *finalAux = auxNode -> next;
            valor = finalAux -> valor;

            auxNode -> next = head;
            free(finalAux);
        }
        return valor;
    }
    return -1;
}

int removerMeio(int index) {
    if (head != 0) {
        if (index == 0) {
            return removerInicio();
        } else if (index >= length() - 1) {
            return removerFinal();
        } else {
            struct node *previous;
            struct node *actualNode = head;

            while (index > 0) {
                previous = actualNode;
                actualNode = actualNode -> next;
                index--;
            }
            int valor = actualNode -> valor;

            previous -> next = actualNode -> next;
            free(actualNode);
            return valor;
        }
    }
    return -1;
}

void reverse() {
    if (head != 0) {
        /*
        struct node *previous = getLastNode(), *currentNode = head, *nextNode = head;

        while (currentNode -> next != head) {
            nextNode = nextNode -> next;

            currentNode -> next = previous;
            previous = currentNode;
            currentNode = nextNode;
        }
        currentNode -> next = previous;
        head = currentNode;*/

        struct node *previous, *currentNode = head, *nextNode = head -> next;

        while (nextNode != head) {
            previous = currentNode;
            currentNode = nextNode;
            nextNode = nextNode -> next;
            currentNode -> next = previous;
        }
        nextNode -> next = currentNode;
        head = currentNode;
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

        while(decision < 0 || decision > 10) {
            printMenu();
            scanf("%d", &decision);
        }

        printf("\n");
        if (decision > 0 && decision < 4) {
            printf("Valor: ");
            scanf("%d", &valor);

            if (decision == 1) {
                inserirInicio(valor);
            } else if (decision == 2) {
                inserirFim(valor);
            } else {
                printf("Index: ");
                scanf("%d", &index);
                inserirMeio(index, valor);
            }
        } else if (decision > 3 && decision < 7) {
            if (decision == 4) {
                printf("\nElemento removido: %d", removerInicio());
            } else if (decision == 5) {
                printf("\nElemento removido: %d", removerFinal());
            } else {
                int posicao = 0;
                int elementoRemovido = 0;

                printf("\nPosição: ");
                scanf("%d", &posicao);

                elementoRemovido = removerMeio(posicao);

                if (elementoRemovido == -1) {
                    printf("\nPosição inválida");
                } else {
                    printf("\nElemento removido: %d", elementoRemovido);
                }
            }
        } else if (decision == 7) {
            imprimirLista();
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