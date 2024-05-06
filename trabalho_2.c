/*
submissão: 
    pasta: projeto/
        bin/ -> executável
        docs/ -> documentação
        lib/ -> .h
        src/ -> .c
guardar os projetos:
    gcc -Wall -Wextra src/*.c
                        V
                busca tds os ficheiros .c
                e aloca em projeto/src/
    gcc -Wall -Wextra -o bin/proj -g
                           V       V
                guarda em proj-   roda e debuga
                eto/bin/proj,     o código
                sendo proj um 
                executável
valgrind --leak-check-full --track-origins-yes ./main
--> vai dizer o que o programa faz, e vai dizer se libertei a 
memória de todas as variáveis e onde estão os erros.
sempre libertar o mesmo tanto que foi feito malloc's

não utilizar scanf, usar o fgets e se quiser numero converter, 
sem utilizar o atoi()
cleanbuffer_removeline <- para remover \n e dps:
e colocar '\0'
Meter um ciclo até o input ser válido e uma mesagem caso seja inválido,
mas sem parar o projeto
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trab_estruturas.h"

// INICIALIZA A LISTA DOENTE ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void init_doente(list_doente_t *list_doente){
    list_doente -> num_elems = 0;
    list_doente -> front_doente = NULL;
}
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// VERIFICA SE O INPUT É UM NÚMERO ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int verifica_numeros(const char *input){ // implementar depois no loop, very raw
    for(int i = 0; input[i] != '\0'; i++){
        if(input[i] < '0' || input[i] > '9') return 0; // não é um número
    } return 1; // é um número
}
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// LIMPA O BUFFER DO INPUT --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void limpar_buffer(char *input){
    int c;
    if(input[strlen(input) -1] == '\n') input[strlen(input) -1] = '\0';
    else{while((c = getchar()) != '\n' && c != EOF);}
}
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ANULA O NODO ATUAL DA LISTA DOENTE ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int empty_doente(list_doente_t *list_doente){
    return list_doente -> front_doente == NULL;
}
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// FAZ PRINT DE TODOS OS ELEMENTOS DA LISTA DOENTE --------------------------------------------------------------------------------------------------------------------------------------------------------------
void print_list_doente(list_doente_t *list_doente){
    node_doente_t *node = list_doente -> front_doente;
    while(node != NULL){
        printf("funcionou");
        node = node -> next;
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// LIMPA A LISTA DOENTE -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void clear_doente(list_doente_t *list_doente){
    node_doente_t *node;
    while(list_doente -> front_doente != NULL){
        node = list_doente -> front_doente;
        list_doente -> front_doente = list_doente -> front_doente -> next;
        free(node);
    }
    init_doente(list_doente);
}
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// PERCORRE TODOS OS NODES DA LISTA DOENTE E ORDENA POR ORDEM ALFABÉTICA ----------------------------------------------------------------------------------------------------------------------------------------
void sort_doente(list_doente_t *list_doente, char *nome, node_doente_t **prev, node_doente_t **cur){
    *prev = NULL;
    *cur = list_doente -> front_doente;
    //while(*cur != NULL && strcmp((*cur) -> nome, nome) < 0){
    while(*cur != NULL){
        if(strcmp((*cur) -> nome, nome) < 0){
            *prev = *cur;
            *cur = (*cur) -> next;
        }else{
            *prev = (*cur) -> next;
            *cur = (*cur) -> next -> next;
        }
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// PESQUISA UM DOENTE POR ID ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void search_doente(list_doente_t *list_doente, int *id, node_doente_t **prev, node_doente_t **cur){
    *prev = NULL;
    *cur = list_doente -> front_doente;
    while(*cur != NULL){
        if((*cur) -> id == *id){
            printf("Informações do utilizador de ID %d\n", *id);
            printf("Nome: %s\n", (*cur) -> nome);
            printf("Contacto: %d\n", (*cur) -> tel);
            printf("Contacto: %d\n", (*cur) -> tel);
            printf("Data de nascimento: %d/%d/%d\n", (*cur) -> dia_nascimento, (*cur) -> mes_nascimento, (*cur) -> ano_nascimento);
            printf("Cartão de cidadão: %s\n", (*cur) -> cc);
            printf("Email: %s\n", (*cur) -> email);
            break;
        }else{
            *prev = (*cur) -> next;
            *cur = (*cur) -> next -> next;
        }
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// INSERIR ELEMENTO NO TOPO DA LISTA ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void insert_doente(list_doente_t *list_doente, int *id, int *tel, int *dia_nascimento, int *mes_nascimento, int *ano_nascimento, char nome[TAMANHO], char cc[TAMANHO], char email[TAMANHO]){
    node_doente_t *node = (node_doente_t*)malloc(sizeof(node_doente_t));
    node_doente_t *prev, *cur;
    if(node != NULL){
        node -> id = *id;
        node -> tel = *tel;
        node -> dia_nascimento = *dia_nascimento;
        node -> mes_nascimento = *mes_nascimento;
        node -> ano_nascimento = *ano_nascimento;
        for(size_t i = 0; i < sizeof(*nome); i++) node -> nome[i] = nome[i];
        search_doente(list_doente, id, &prev, &cur);
        if(prev != NULL){
            prev -> next = node;
            node -> next = cur;
        } else {
            list_doente -> front_doente = node;
            node -> next = cur;
        }
        list_doente -> num_elems++;
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// eliminar o primeiro elemento: list -> front = cur -> next; #o list -> front é sempre o primeiro elemento da lista
// eliminar um elemento no meio da lista: prev -> next = cur -> next;

// REMOVER UM DOENTE DA LISTA -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void remove_node_doente(list_doente_t *list_doente, int id){
    node_doente_t *prev, *cur;
    search_doente(list_doente, &id, &prev, &cur);
    if(cur != NULL && cur -> id == id){
        if(prev != NULL) prev -> next = cur -> next;
        else list_doente -> front_doente = cur -> next;
        free(cur);
        list_doente -> num_elems --;
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// INTRODUZIR INFOS DOENTES -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// FUNÇÃO PRINCIPAL ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(){
    char opcao[5];
    printf("-----TABELA DE AÇÕES-----\n\n");
    printf("0 - SAIR DO MENU\n1 - INTRODUZIR DADOS DE UM NOVO CLIENTE\n2 - ELIMINAR UM DOENTE EXISTENTE\n3 - LISTAR TODOS OS DOENTES POR ORDEM ALFABÉTICA\n4 - LISTAR OS DOENTES COM TENSÕES MÁXIMAS ACIMA DE UM VALOR\n5 - APRESENTAR TODA A INFORMAÇÃO DE UM DETERMINADO DOENTE\n6 - REGISTRAR AS TENSÕES, O PESO E A ALTURA DE UM DETERMINADO DOENTE NUM DETERMINADO DIA\n");
    while(1){
        fgets(opcao, 5, stdin);
        limpar_buffer(opcao);
        if(verifica_numeros(opcao) && '1' <= opcao[0] <= '6'){
            int opcao_num = (int)opcao[0] - '0';
            list_doente_t *list_doente = (list_doente_t*)malloc(sizeof(list_doente_t));
            init_doente(list_doente);
            // FAZER CICLO ATÉ INPUT UTILIZADOR ESCREVER 0
            switch(opcao_num){
                case 1:
                    printf("Introduza o ID do doente: ");
                    char id[5];
                    fgets(id, 5, stdin);
                    limpar_buffer(id);
                    if(verifica_numeros(id)){
                        int id_num = (int)id[0] - '0';
                        printf("Introduza o nome do doente: ");
                        char nome[TAMANHO];
                        fgets(nome, TAMANHO, stdin);
                        limpar_buffer(nome);
                        printf("Introduza o contacto do doente: ");
                        char tel[9];
                        fgets(tel, 9, stdin);
                        limpar_buffer(tel);
                        if(verifica_numeros(tel)){
                            int tel_num = (int)tel[0] - '0';
                            printf("Introduza a data de nascimento do doente por: \n");
                            printf("DIA: ");
                            char dia_nascimento[3], mes_nascimento[3], ano_nascimento[5];
                            // LIMITAR A 2 CARACTERES E NO MÁXIMO ATÉ 31
                            fgets(dia_nascimento, 3, stdin);
                            limpar_buffer(dia_nascimento);
                            printf("MÊS: ");
                            // LIMITAR ATÉ 2 CARACTERES E NO MÁXIMO ATÉ 12
                            fgets(mes_nascimento, 3, stdin);
                            limpar_buffer(mes_nascimento);
                            printf("ANO: ");
                            // LIMITAR A 4 CARACTERES E NO MÁXIMO ATÉ 2023
                            fgets(ano_nascimento, 5, stdin);
                            limpar_buffer(ano_nascimento);
                            if(verifica_numeros(dia_nascimento) && verifica_numeros(mes_nascimento) && verifica_numeros(ano_nascimento)){
                                if(0 < (int)dia_nascimento[0] - '0' <= 31 && 0 < (int)mes_nascimento[0] - '0' <= 12 && 0 < (int)ano_nascimento[0] - '0' <= 2023){
                                    int dia_nascimento_num = (int)dia_nascimento[0] - '0';
                                    int mes_nascimento_num = (int)mes_nascimento[0] - '0';
                                    int ano_nascimento_num = (int)ano_nascimento[0] - '0';
                                    printf("Introduza o cartão de cidadão do doente: ");
                                    char cc[TAMANHO];
                                    fgets(cc, 9, stdin);
                                    limpar_buffer(cc);
                                    // LIMITAR ATÉ 40 CARACTERES
                                    printf("Introduza o email do doente: ");
                                    char email[TAMANHO];
                                    fgets(email, TAMANHO, stdin);
                                    limpar_buffer(email);
                                    insert_doente(list_doente, &id_num, &tel_num, &dia_nascimento_num, &mes_nascimento_num, &ano_nascimento_num, nome, cc, email);
                                }else printf("A data de nascimento introduzida não é válida!\n");
                            }else printf("Apenas números são permitidos!\n");
                        }else printf("Apenas números são permitidos!\n");
                        break;
                        case 2:
                            printf("Introduza o ID do doente que deseja remover: ");
                            char id_remove[5];
                            fgets(id_remove, 5, stdin);
                            limpar_buffer(id_remove);
                            if(verifica_numeros(id_remove)){
                                int id_remove_num = (int)id_remove[0] - '0';
                                remove_node_doente(list_doente, id_remove_num);
                            }else {
                                printf("Apenas números são permitidos!\n");
                            break;
                            }
                    }
            }
            break;
        } else if(verifica_numeros(opcao) && opcao[0] == '0'){
            printf("A sair do menu...\n");
            break;
        }
        else{printf("Selecione apenas uma das opções disponíveis!\n");}
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------