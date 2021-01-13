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
        struct node *actualNode = head;

        while (actualNode != 0) {
            actualNode = actualNode -> next;
            size++;
        }
    }
    return size;
}

void inserirInicio(int valor) {
    struct node *newNode = (struct node*)(malloc(sizeof(struct node)));
    newNode -> valor = valor;

    if (head == 0) {
        head = newNode;
        head -> next = 0;
    } else {
        newNode -> next = head;
        head = newNode;
    }
}

void inserirFim(int valor) {
    struct node *newNode = (struct node*)(malloc(sizeof(struct node)));
    newNode -> valor = valor;

    if (head == 0) {
        head = newNode;
        head -> next = 0;
    } else {
        struct node *actualNode = head;

        while (actualNode -> next != 0) {
            actualNode = actualNode -> next;
        }
        actualNode -> next = newNode;
        newNode -> next = 0;
    }
}

void inserirMeio(int index, int valor) {
    int size = length();

    if (index < 0 || index > size) {
        printf("Invalid position.\n");
    } else {
        if (index == 0) {
            inserirInicio(valor);
        } else if (index == size) {
            inserirFim(valor);
        } else {
            struct node *newNode = (struct node*)(malloc(sizeof(struct node)));
            newNode -> valor = valor;
            struct node *prevNode;
            struct node *actualNode = head;

            while (index > 0) {
                prevNode = actualNode;
                actualNode = actualNode -> next;
                index--;
            }
            newNode -> next = actualNode;
            prevNode -> next = newNode;
        }
    }
}



int removerInicio() {
    if (head != 0) {
        struct node *pointerNode = head;
        int valor = head -> valor;
        head = head -> next;

        free(pointerNode);
        return valor;
    }
    return -1;
}

int removerFinal() {
    if (head != 0) {
        struct node *prevNode;
        struct node *actualNode = head;

        while (actualNode -> next != 0) {
            prevNode = actualNode;
            actualNode = actualNode -> next;
        }
        int valor = actualNode -> valor;
        
        if (prevNode != 0) {
            prevNode -> next = 0;
        }
        free(actualNode);
        return valor;
    }
    return -1;
}

int removerMeio(int index) {
    if (head != 0) {
        int size = length();

        if (index < 0 && index >= size) {
            printf("Invalid Index");
        } else {
            if (index == 0) {
                return removerInicio();
            } else if (index == size - 1) {
                return removerFinal();
            } else {
                int valor = 0;
                struct node *prevNode;
                struct node *actualNode = head;

                while (index > 0) {
                    prevNode = actualNode;
                    actualNode = actualNode -> next;
                    index--;
                }
                valor = actualNode -> valor;
                prevNode -> next = actualNode -> next;
                free(actualNode);

                return valor;
            }
        }
    }
    return -1;
}

void reverse() {
    if (head != 0) {
        struct node *actualNode = head;
        struct node *nextNode = head;
        struct node *prev;

        while (actualNode != 0) {
            nextNode = nextNode -> next;
            actualNode -> next = prev;
            prev = actualNode;
            actualNode = nextNode;
        }
        head = prev;
    }
}

void imprimirLista() {
    if (head != 0) {
        struct node *actualNode = head;

        while (actualNode != 0) {
            printf("%d ", actualNode -> valor);
            actualNode = actualNode -> next;
        }
        printf("\n");
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