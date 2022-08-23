/* 
Autores:
JOAO AUGUSTO FERNANDES BARBOSA - 11953348
VINICIUS SANTOS CUBI PAULO - 11965693 
*/
#ifndef FUNCGERAISCPP_H
#define FUNCGERAISCPP_H

#include "define.h"
#include "func.h"
#include "Node.hpp"
#include <vector>
#include <climits>
#include <algorithm> 


map<int, long> mapearByteOffSet(FILE* Arquivo_bin);
HEADER ler_cabecalho(FILE *Arquivo_bin);
string byteToString(FILE* Arquivo_bin, map<int, long> mapa, int codEst);
void criaGrafo(FILE *Arquivo_bin, Grafo *g);
void imprimeGrafo(Grafo Graph);
void scan_quote_string(char *str);


bool buscaProfundidade(Grafo *g, string *v, int *nro, vector<string> *list, vector<int> *d,bool mode);//ok
bool pintaVertice(Grafo *g, string *v); //ok





#endif