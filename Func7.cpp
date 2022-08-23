/* 
Autores:
JOAO AUGUSTO FERNANDES BARBOSA - 11953348
VINICIUS SANTOS CUBI PAULO - 11965693 
*/
#include "FuncCpp.hpp"

void imprimeGrafo(Grafo Graph){

    for(Grafo::const_iterator it = Graph.begin(); it != Graph.end(); ++it){
     
      cout << it->first;


    for(map<string,Node>::const_iterator sec = it->second.begin(); sec != it->second.end(); ++sec){

      Node n = sec->second;
      cout << " " << sec->first << " " << n.distancia;
      
      
      for(map<string,int>::const_iterator ter = n.linhas.begin(); ter != n.linhas.end();++ter){
          cout << " " + ter->first;
      }
      
      
    }
    
    cout << endl;
}

}

void func_seven(){
  
  char *nome_arquivo_bin;
  scanf("%ms", &nome_arquivo_bin);

  FILE *Arquivo_bin = fopen(nome_arquivo_bin,"rb");
  
  Grafo Graph;

  criaGrafo(Arquivo_bin, &Graph);
  
  imprimeGrafo(Graph);

  fclose(Arquivo_bin);
   
  }