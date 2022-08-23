/* 
Autores:
JOAO AUGUSTO FERNANDES BARBOSA - 11953348
VINICIUS SANTOS CUBI PAULO - 11965693 
*/
#include "Node.hpp"  

Node::Node(REGISTER r)
{ 

	distancia = r.distProxEstacao;
	cor = 0;
	linhas.insert(pair< string, int> (r.nomeLinha, r.codProxEstacao));
    
}

Node::Node(int estInt)
{ 

	distancia = 0;
	cor = 0;
	linhas.insert(pair< string, int> ("Integracao", estInt));
    
}


Node::Node(int dist,int c)
{
	distancia = dist;
	cor = c;
	linhas.insert(pair< string, int> ("", 0));
}