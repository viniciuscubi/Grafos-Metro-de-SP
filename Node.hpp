/* 
Autores:
JOAO AUGUSTO FERNANDES BARBOSA - 11953348
VINICIUS SANTOS CUBI PAULO - 11965693 
*/
#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <map>

#include "define.h"
using namespace std;



class Node

{	
	public:
		int distancia;
		int cor; // 0 = branco, 1 = cinza, 2 = preto
		map<string, int> linhas;
		Node(REGISTER r);
		Node(int estInt);
		Node(int dist,int c);

};

typedef map<string, map<string, Node>> Grafo;



#endif