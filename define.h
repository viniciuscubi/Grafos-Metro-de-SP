/* 
Autores:
JOAO AUGUSTO FERNANDES BARBOSA - 11953348
VINICIUS SANTOS CUBI PAULO - 11965693 
*/

//Criamos um HEADER e um REGISTER com os dados passados de acordo com o pdf do trabalho
#ifndef _define_
#define _define_

#define ERROR 1
#define SUCCESS 0

typedef struct{

  char status;
  long int topoLista;
  int nroEstacoes;
  int nroParesEstacao;

}HEADER;


typedef struct{

  char removido;
  int tamanhoRegistro;
  long int proxLista;

  int codEstacao;
  int codLinha;
  int codProxEstacao;
  int distProxEstacao;
  int codLinhaIntegra;
  int codEstIntegra;
  char *nomeEstacao;
  char *nomeLinha;

}REGISTER;

#endif
