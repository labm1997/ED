#include <check.h>
#include "listas.h"

lista_nomearTipo(int_ptr, int *); /* A lista precisa que não hajam caracteres inválidos como '*' */
lista_definir(int);
lista_definir(int_ptr);

void limpador_intptr(int *dado){
  free(dado);
}

/* Inicia e destroi lista */
START_TEST(inicialiacao){
  Lista(int) *a = lista_criar(int);
  ck_assert(a != NULL);
  ck_assert(a->tamanho == 0);
  ck_assert(a->primeiro == NULL);
  ck_assert(a->ultimo == NULL);
  lista_apagar(int, &a);
  ck_assert(a == NULL);
}
END_TEST

/* Insere 1000 elementos na lista e depois destroi */
START_TEST(inserir){
  Lista(int) *a = lista_criar(int);
  int i=0;
  for(;i<1000;i++) lista_adicionar(int,a,i);
  for(i=0;i<1000;i++) ck_assert_int_eq(*lista_dado(int,a,i), i);
  lista_apagar(int,&a);
  ck_assert(a == NULL);
}
END_TEST

/* Insere 1000 elementos com função de limpeza na lista e depois destroi */
START_TEST(inserirComLimpador){
  Lista(int_ptr) *a = lista_criar(int_ptr);
  int i=0;
  lista_definirLimpador(int_ptr,a,limpador_intptr);
  for(;i<1000;i++) lista_adicionar(int_ptr,a,(int *)malloc(sizeof(int)));
  lista_apagar(int_ptr,&a);
  ck_assert(a == NULL);
}
END_TEST

Suite *testeSuite(void){
  int i=0;
  Suite *s = suite_create("testeLista");
  TCase *tc_core[3] = {
          tcase_create("Teste de inicialização/destruição de uma Lista"),
          tcase_create("Teste de inserção de elementos na lista"),
          tcase_create("Teste de inserção de elementos com função de limpeza na lista")
  };
  static void (*testes[3])() = {
    inicialiacao,
    inserir,
    inserirComLimpador
  };
  for(;i<3;i++) {
    tcase_add_test(tc_core[i], testes[i]);
    suite_add_tcase(s,tc_core[i]);
  }
  return s;
}

int main(void){
  
  int falhos;
  Suite *s = testeSuite();
  SRunner *sr = srunner_create(s);
  
  srunner_set_fork_status(sr,CK_NOFORK); /* Não sei o que isso faz, mas o valgrind fica contente */
  
  srunner_run_all(sr, CK_VERBOSE);
  falhos = srunner_ntests_failed(sr);
  srunner_free(sr);
  
  
  return falhos;
}
