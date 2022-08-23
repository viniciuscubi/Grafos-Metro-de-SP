/* 
Autores:
JOAO AUGUSTO FERNANDES BARBOSA - 11953348
VINICIUS SANTOS CUBI PAULO - 11965693 
*/
#ifndef _func_
#define _func_
#include <stdio.h>

char *strParser(char *str, char limitador, int pos);
void binToRegister(FILE *fp, REGISTER *r);
int compara_reg(REGISTER r, int num_campos, char **nome_campo, char **valor_campo);
void imprime_reg(REGISTER target);
void insert_DataInReg(char *mensagem, REGISTER* target);

#endif