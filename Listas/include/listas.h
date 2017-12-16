#ifndef HEADER_LISTAS
#define HEADER_LISTAS

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define LISTAS_INTEIRO_TAMANHO uint32_t
#define lista_nomearTipo(novoNome,tipo) typedef tipo novoNome;

#define lista_definir_H(tipo) \
\
typedef struct Lista_elemento_##tipo { \
  tipo dado; \
  struct Lista_elemento_##tipo *proximo; \
  struct Lista_elemento_##tipo *antes; \
} Lista_elemento_##tipo; \
\
typedef struct Lista_##tipo { \
  LISTAS_INTEIRO_TAMANHO tamanho; \
  Lista_elemento_##tipo *primeiro; \
  Lista_elemento_##tipo *ultimo; \
  void (*limparElemento)(tipo);\
} Lista_##tipo; \
\
Lista_##tipo *lista_criar_##tipo(); \
void lista_adicionar_##tipo(Lista_##tipo *, tipo); \
Lista_elemento_##tipo *lista_elemento_##tipo(Lista_##tipo *, LISTAS_INTEIRO_TAMANHO); \
tipo *lista_dado_##tipo(Lista_##tipo *, LISTAS_INTEIRO_TAMANHO); \
void lista_remover_##tipo(Lista_##tipo *, LISTAS_INTEIRO_TAMANHO); \
void lista_inserir_##tipo(Lista_##tipo *, LISTAS_INTEIRO_TAMANHO, tipo); \
void lista_apagar_##tipo(Lista_##tipo **); \
void lista_definirLimpador_##tipo(Lista_##tipo *, void (*)(tipo));

#define Lista(tipo) Lista_##tipo

#define lista_criar(tipo) lista_criar_##tipo()
#define lista_adicionar(tipo,lista,dado) lista_adicionar_##tipo(lista,dado)
#define lista_elemento(tipo,lista,pos) lista_elemento_##tipo(lista,pos)
#define lista_dado(tipo,lista,pos) lista_dado_##tipo(lista,pos)
#define lista_remover(tipo,lista,pos) lista_remover_##tipo(lista,pos)
#define lista_inserir(tipo,lista,pos) lista_inserir_##tipo(lista,pos)
#define lista_apagar(tipo,lista) lista_apagar_##tipo(lista)
#define lista_definirLimpador(tipo,lista,limpador) lista_definirLimpador_##tipo(lista,limpador)


#endif

#include "../src/listas.c"
