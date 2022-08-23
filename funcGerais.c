/* 
Autores:
JOAO AUGUSTO FERNANDES BARBOSA - 11953348
VINICIUS SANTOS CUBI PAULO - 11965693 
*/
#include <stdio.h>
#include "string.h"
#include <stdlib.h>
#include "define.h"

char *strParser(char *str, char limitador, int pos){

	if(str == NULL){
		return NULL;
	}

	char *tmp = (char *) malloc(strlen(str) * sizeof(char));

	int unsigned long i = 0;
	int j = 0;
	int k = 0;
	
	while(i != strlen(str) && j < pos){
		       
		if(str[i] == limitador){
			j++;
			tmp[k++] = '\0';
			k = 0;
		}else{
			tmp[k] = str[i];
			k++;	
		}
		
		i++;
    
	}
	
	if(str[i] == '\0'){
		tmp[k++] = '\0';

    }
    if(strlen(tmp) == 0 || tmp[0]  == '\r' || tmp[0]  == '\n'){ 
        strcpy(tmp,"-1");
    }
    
	return tmp;
}


void binToRegister(FILE *fp, REGISTER *r){

        fread(&r->tamanhoRegistro,sizeof(int),1,fp);
        fread(&r->proxLista,sizeof(long int),1,fp);
        fread(&r->codEstacao,sizeof(int),1,fp);
        fread(&r->codLinha,sizeof(int),1,fp);
        fread(&r->codProxEstacao,sizeof(int),1,fp);
        fread(&r->distProxEstacao,sizeof(int),1,fp);
        fread(&r->codLinhaIntegra,sizeof(int),1,fp);
        fread(&r->codEstIntegra,sizeof(int),1,fp);
        char tmp[r->tamanhoRegistro - 32]; //Quis evitar de criar um vetor estatico entao joguei ele num dinamico para posteriormente separalo novamente pela funcao strparse
        fgets(tmp,(r->tamanhoRegistro -32), fp);
        
        char pipe[1];
        fread(pipe,sizeof(char),1,fp);
        
        r->nomeEstacao = strParser(tmp,'|',1);
 // Pegamos cada uma das partes separadas pelo pipe atraves da funcao e adicionamo-as no registro
        
        r->nomeLinha = strParser(tmp,'|',2);
        

}

void insert_DataInReg(char *mensagem, REGISTER* target){
    
    char *tmp;

    target->removido = '0';
    target->tamanhoRegistro = 0;
    target->proxLista = -1;

    tmp = strParser(mensagem, ',', 1);
    target->codEstacao = atoi(tmp);
    free(tmp);
    
    tmp = strParser(mensagem, ',', 3);
    target->codLinha = atoi(tmp);
    free(tmp);
    
    tmp = strParser(mensagem, ',', 5);
    target->codProxEstacao = atoi(tmp);
    free(tmp);

    tmp = strParser(mensagem, ',', 6);
    target->distProxEstacao = atoi(tmp);
    free(tmp);

    tmp = strParser(mensagem, ',', 7);
    target->codLinhaIntegra = atoi(tmp);
    free(tmp);

    tmp = strParser(mensagem, ',', 8);
    target->codEstIntegra = atoi(tmp);
    free(tmp);

    tmp = strParser(mensagem, ',', 2);
    target->nomeEstacao = (char *) malloc(sizeof(char) * strlen(tmp));
    strcpy(target->nomeEstacao, (tmp));
    free(tmp);

    tmp = strParser(mensagem, ',', 4);
    target->nomeLinha =(char *) malloc(sizeof(char) * strlen(tmp));
 
    if(strcmp(tmp, "-1") == 0){
        free(target->nomeLinha);
        target->nomeLinha = NULL;
    }
    else{
        strcpy(target->nomeLinha, tmp);
    }
    
    free(tmp);

        target->tamanhoRegistro = 32 + strlen(target->nomeEstacao) + strlen(target->nomeLinha) + 2;
    
      
}

