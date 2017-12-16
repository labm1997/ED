#ifndef IMPLEMENTACAO_LISTAS
#define IMPLEMENTACAO_LISTAS


#define lista_definir_I(tipo) \
\
Lista_##tipo *lista_criar_##tipo(){ \
  Lista_##tipo *novo = (Lista_##tipo *)malloc(sizeof(Lista_##tipo)); \
  novo->primeiro = NULL; \
  novo->ultimo = NULL; \
  novo->tamanho = 0; \
  novo->limparElemento = NULL; \
  novo->ordem = NULL; \
  return novo; \
} \
\
void lista_definirLimpador_##tipo(Lista_##tipo *lista, void (*limpador)(tipo)){ \
  lista->limparElemento = limpador;\
} \
\
void lista_adicionar_##tipo(Lista_##tipo *lista, tipo dado){ \
\
  Lista_elemento_##tipo *tmp = lista->ultimo; \
  \
  lista->ultimo = (Lista_elemento_##tipo *)malloc(sizeof(Lista_elemento_##tipo)); \
  lista->ultimo->dado = dado; \
  lista->ultimo->proximo = NULL; \
  lista->ultimo->antes = tmp; \
  (lista->tamanho)++; \
  \
  if(tmp == NULL) lista->primeiro = lista->ultimo; \
  else tmp->proximo = lista->ultimo; \
  \
}\
\
void lista_definirOrdem_##tipo(Lista_##tipo *lista, bool (*comparador)(tipo,tipo)){ \
  lista->ordem = comparador;\
}\
\
void lista_adicionar_ordem_##tipo(Lista_##tipo *lista, tipo dado){\
  LISTAS_INTEIRO_TAMANHO i=0; \
  Lista_elemento_##tipo *tmp = lista->primeiro; \
  if(lista->ordem != NULL){ \
    for(;tmp!=NULL && lista->ordem(dado,tmp->dado);tmp=tmp->proximo,i++); \
    lista_inserir_##tipo(lista,i,dado); \
  } \
  \
}\
\
Lista_elemento_##tipo *lista_elemento_##tipo(Lista_##tipo *lista, LISTAS_INTEIRO_TAMANHO pos){ \
  Lista_elemento_##tipo *tmp = lista->primeiro; \
  LISTAS_INTEIRO_TAMANHO i = 0; \
  for(;tmp!=NULL&&i!=pos;tmp=tmp->proximo) i++; \
  if(i==pos) return tmp; \
  else return NULL; \
} \
\
tipo *lista_dado_##tipo(Lista_##tipo *lista, LISTAS_INTEIRO_TAMANHO pos){ \
  Lista_elemento_##tipo *tmp = lista_elemento_##tipo(lista,pos); \
  if(tmp != NULL) return &(tmp->dado); \
  else return NULL; \
}\
\
tipo *_##tipo(Lista_##tipo *lista, LISTAS_INTEIRO_TAMANHO pos){ \
  return lista_dado_##tipo(lista,pos); \
}\
\
void lista_remover_##tipo(Lista_##tipo *lista, LISTAS_INTEIRO_TAMANHO pos){ \
  Lista_elemento_##tipo *tmp = lista_elemento_##tipo(lista,pos); \
  Lista_elemento_##tipo *tmpprox; \
  if(tmp != NULL) { \
    tmpprox = tmp->proximo; \
    if(tmp->proximo != NULL) tmp->proximo->antes = tmp->antes; \
    else lista->ultimo = tmp->antes; \
    if(tmp->antes != NULL) tmp->antes->proximo = tmpprox; \
    else lista->primeiro = tmpprox; \
    (lista->tamanho)--; \
    free(tmp);\
  } \
} \
\
void lista_inserir_##tipo(Lista_##tipo *lista, LISTAS_INTEIRO_TAMANHO pos, tipo dado){ \
  Lista_elemento_##tipo *tmp = lista_elemento_##tipo(lista,pos), *novo; \
  \
  if(tmp != NULL) { \
    novo = (Lista_elemento_##tipo *)malloc(sizeof(Lista_elemento_##tipo)); \
    novo->dado = dado; \
    novo->proximo = tmp; \
    novo->antes = tmp->antes; \
    if(tmp->antes != NULL) tmp->antes->proximo = novo; \
    else lista->primeiro = novo; \
    tmp->antes = novo; \
  } \
  else lista_adicionar_##tipo(lista,dado); \
} \
\
void lista_apagar_##tipo(Lista_##tipo **lista){ \
  Lista_elemento_##tipo *tmp = (*lista)->primeiro, *proximo = NULL; \
  for(;tmp!=NULL;tmp=proximo){ \
    proximo = tmp->proximo; \
    if((*lista)->limparElemento != NULL) \
      (*lista)->limparElemento(tmp->dado); \
    free(tmp); \
  } \
  free(*lista); \
  *lista = NULL; \
} \

#define lista_definir(tipo) \
        lista_definir_H(tipo) \
        lista_definir_I(tipo)
        
#endif

