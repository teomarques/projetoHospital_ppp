#ifndef TRAB_ESTRUTURAS_H
#define TRAB_ESTRUTURAS_H

#include <stddef.h> 

#define TAMANHO 40

typedef struct node_doente{
    int id, tel, dia_nascimento, mes_nascimento, ano_nascimento;
    char nome[TAMANHO], cc[TAMANHO], email[TAMANHO];
    struct node_doente *next; // Fix the struct declaration
}node_doente_t;

typedef struct node_registro{
    int tmax, tmin, peso, altura, dia_registro, mes_registro, ano_registro;
    struct node_registro *next; // Fix the struct declaration
}node_registro_t;

typedef struct list_doente{
    size_t num_elems;
    node_doente_t *front_doente; // Fix the struct declaration
    node_registro_t *front_registro; // Fix the struct declaration
}list_doente_t;

#endif