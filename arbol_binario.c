//
// Created by khrisna on 22/11/2023.
//
#include <stdio.h>
#include <stdlib.h>

struct Nodo {
    int valor;
    struct Nodo* der;
    struct Nodo* izq;
};


struct Nodo* crear_nodo(int value){
    //Asigna el espacio en la memoria del tamano de la estructura;
    struct Nodo* nodo = (struct Nodo*) malloc(sizeof (struct Nodo));
    nodo ->valor = value;
    nodo ->der = nodo ->izq = NULL;
    return nodo;
}
struct Nodo* Insert(struct Nodo* tree, int n){
    if(tree == NULL){
        return crear_nodo(n);
    }
    if(n < tree->valor){
        tree->izq=Insert(tree->izq,n);
    } else{
        tree->der=Insert(tree->der,n);
    }
    return tree;
}
struct Nodo * faketree(struct Nodo* tree){
    //# region arbol erroneo example
//    tree = Insert(tree,1);
//    Insert(tree,10);
//    Insert(tree,3);
//
//    Insert(tree,3);
//    Insert(tree,5);
//
//    Insert(tree,6);
//    Insert(tree,7);
//# endregion

    tree = Insert(tree,10);
    Insert(tree, 7);
    Insert(tree, 6);
    Insert(tree, 8);
    Insert(tree, 15);
    Insert(tree, 13);
    Insert(tree, 16);
    Insert(tree, 17);
    //arbol correcto example
}
int validate(struct Nodo* tree, int Min, int Max){
    if (tree == NULL){
        return 1;
    }
    if(tree->valor<Min||tree->valor>Max){
        return 0;
    }
    return validate(tree->izq,Min,tree->valor - 1) && validate(tree->der,tree->valor+1, Max);
};
void resultado(struct Nodo *tree){
    if(validate(tree,6,17)==1){//el min es el valor minimo que esta en el arbol binario y el maximo el es
        printf("That is a correct binary search tree\n");
    }else{
        printf("That is incorrect binary search tree\n");
    }
}

void inOrder(struct Nodo *tree){
    if(tree == NULL){
        return;
    }else{
        inOrder(tree->izq);
        printf("%d,",tree->valor);
        inOrder(tree->der);
    }
}
void preOrder(struct Nodo *tree){
    if(tree == NULL){
        return;
    }else{
        printf("%d,",tree->valor);
        preOrder(tree->izq);
        preOrder(tree->der);
    }
}

void postOrder(struct Nodo *tree){
    if(tree == NULL){
        return;
    }else{
        postOrder(tree->izq);
        postOrder(tree->der);
        printf("%d,",tree->valor);
    }
}
struct Node* Find(struct Nodo *tree,int valor){
    if(tree== NULL || tree->valor == valor){
        return tree;
    }
    if(valor < tree->valor){
        Find(tree->izq,valor);
    } else{
        Find(tree->der,valor);
    }
}
struct Nodo* addNodes(struct Nodo* tree){
    int value;
    printf("Enter a value:\n");
    scanf("%d",&value);
    tree = Insert(tree,value);
    int choice;
    printf("Do you want to enter another node Yes(1)/ No(2)\n");
    scanf("%d",&choice);
    if(choice==1){
        addNodes(tree);
    }
    return tree;
}
int Cont_Nodes = 0;//es el numero total de nodos
//Este es el menu del programa
void Menu(struct Nodo* raiz, struct Nodo* node_find){
    int orden;
    int option;
    int bool;
    int search;
    printf("What id you want to do?\n");
    printf("1.Insert\n2.Display\n3.Find\n");
    scanf("%d",&option);
    switch (option) {
        case 1:
            raiz = faketree(raiz);
            resultado(raiz);
            //arbol dinamico
            //raiz= addNodes(raiz);
            break;
        case 2:
            printf("1.Preorder\n2.Inorder\n3.Postorder\n");
            scanf("%d",&orden);
            switch (orden){
                case 1:
                    preOrder(raiz);
                    printf("\n");
                    break;
                case 2:
                    inOrder(raiz);
                    printf("\n");
                    break;
                case 3:
                    postOrder(raiz);
                    printf("\n");
                    break;
                default:
                    printf("Incorrect Option");
                    break;
            }
            break;
        case 3:
            printf("Enter the find value:\n");
            scanf("%d",&search);//asigno trae el valor a la memoria
            node_find = Find(raiz,search);
            if(node_find != NULL){
                printf("Dir.Memoria:=%p, Search value=%d, Izq=%d, Der=%d\n",(void*)node_find,node_find->valor,
                       (node_find->izq != NULL) ? node_find->izq->valor : -1,
                       (node_find->der != NULL) ? node_find->der->valor : -1);
            } else{
                printf("Not exist");
            }
            break;
        case 4:
            break;
        default:
            printf("Incorrect Option");
            break;
    }
    printf("Continue  SI|(1)|, NO|(2)|\n");
    scanf("%d",&option);
    if (option==1){
        Menu(raiz,node_find);
    }
    return;
}
int main() {
    printf("Arbol Binario de Busqueda \n");
    struct Nodo* raiz = NULL;
    struct Nodo* node_find = NULL;
    Menu(raiz,node_find);
    return 0;
}
