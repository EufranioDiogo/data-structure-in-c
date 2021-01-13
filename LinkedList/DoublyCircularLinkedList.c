#include <stdio.h>
#include <stdlib.h>


struct node {
    struct node *prev;
    int valor;
    struct node *next;
} node;

struct node *head, *tail;

int length() {
    int size = 0;

    if (head != 0) {
        struct node *currentNode = head;

        while (currentNode != tail) {
            currentNode = currentNode -> next;
            size++;
        }
        size++;
        return size;
    }
    return size;
}

void inserirInicio(int valor) {
    struct node *newNode = (struct node*)(malloc(sizeof(struct node)));

    newNode -> valor = valor;

    if (head == 0) {
        head = newNode;
        tail = newNode;
        head -> next = tail;
        head -> prev = tail;
        tail -> next = head;
        tail -> prev = head;
    } else {
        newNode -> next = head;
        newNode -> prev = tail;
        head -> prev = newNode;
        tail -> next = newNode;
        head = newNode;
    }
}

void inserirFim(int valor) {
    struct node *newNode = (struct node*)(malloc(sizeof(struct node)));

    newNode -> valor = valor;

    if (head == 0) {
        head = newNode;
        tail = newNode;
        head -> next = tail;
        head -> prev = tail;
        tail -> next = head;
        tail -> prev = head;
    } else {
        newNode -> next = head;
        newNode -> prev = tail;
        tail -> next = newNode;
        head -> prev = newNode;
        tail = newNode;
    }
}

void inserirMeio(int valor, int index) {
    if (head != 0) {
        int size = length();

        if (index < 0 || index > size) {
            printf("Invalid Index");
        } else {
            if (index == 0) {
                inserirInicio(valor);
            } else if (index == size) {
                inserirFim(valor);
            } else {
                struct node *newNode = (struct node*)(malloc(sizeof(struct node)));
                newNode -> valor = valor;
                struct node *currentNode = head;

                while(index > 0) {
                    currentNode = currentNode -> next;
                    index--;
                }
                newNode -> prev = currentNode -> prev;
                newNode -> next = currentNode;

                currentNode -> prev -> next = newNode;
                currentNode -> prev = newNode;
            }
        }
    }
}

int removerInicio() {
    int valor = -1;

    if (head != 0) {
        struct node *auxPointer = head;
        valor = head -> valor;
        tail -> next = head -> next;

        head = head -> next;
        head -> prev = tail;
        free(auxPointer);
    }
    return valor;
}

int removerFinal() {
    int valor = -1;

    if (head != 0) {
        struct node *auxPointer = tail;
        valor = tail -> valor;

        head -> prev = tail -> prev;
        tail = tail -> prev;
        tail -> next = head;
        free(auxPointer);
    }
    return valor;
}

int removerMeio(int index) {
    if (head != 0) {
        int size = length();
        if (index < 0 || index > size) {
            printf("Invalid Index");
        } else {
            if (index == 0) {
                return removerInicio();
            } else if (index == size - 1) {
                return removerFinal();
            } else {
                int valor;
                struct node *currentNode = head;

                while (index > 0) {
                    currentNode = currentNode -> next;
                    index--;
                }
                valor = currentNode -> valor;

                currentNode -> prev -> next = currentNode -> next;
                currentNode -> next -> prev = currentNode -> prev;
                free(currentNode);
                return valor;
            }
        }
    }
    return -1;
}

void imprimirLista() {
    if (head != 0) {
        struct node *currentNode = head;

        while (currentNode != tail) {
            printf("%d ", currentNode -> valor);
            currentNode = currentNode -> next;
        }
        printf("%d \n", currentNode -> valor);
    }
}

void reverse() {

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
                inserirInicio(valor);
            } else if (decision == 2) {
                inserirFim(valor);
            } else {
                printf("Index: ");
                scanf("%d", &index);
                inserirMeio(valor, index);
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
    return 0;
}