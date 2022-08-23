/* 
Autores:
JOAO AUGUSTO FERNANDES BARBOSA - 11953348
VINICIUS SANTOS CUBI PAULO - 11965693 
*/
#include "FuncCpp.hpp"

void func_nine(){


  string nome_arquivo_bin, nomeCampo, campo;
  cin >> nome_arquivo_bin >> nomeCampo;
  getline(cin,campo); //le o restante da linha

  campo = campo.erase(0,1).erase(0,1).erase(campo.size()-1,campo.size()); //Elimina as aspas

  FILE *Arquivo_bin = fopen(nome_arquivo_bin.c_str(),"rb");

  if(Arquivo_bin == NULL){
      erro(1); //Verifica se o arquivo foi aberto corretamente
      return;
  }

  Grafo Graph;
  vector<string> ANT;
  vector<int> D;

  criaGrafo(Arquivo_bin, &Graph); // Cria o grafo

  int distPerc,nroEstPerc;

  distPerc = nroEstPerc = 0;
  ANT.push_back(campo); //Insre o vertice passado no vetor de vertices
  
  buscaProfundidade(&Graph,&campo,&nroEstPerc, &ANT,&D,true); //Realiza a Busca por profundiade no modo para achamento de ciclos

  if(ANT[0] == ANT[ANT.size() -1]){  //Verifica se a Ultima estacao eh igual a primeira, caso nao seja o grafo nao possui um ciclo para retornar para aquela estacao
    cout << "Numero de estacoes que serao percorridas: " << nroEstPerc << "\n";

    for(vector<int>::iterator i = D.begin();i < D.end(); i++){ //Soma as distancias do vetor de distancias
        distPerc = distPerc + *i;
    }
    cout << "Distancia que sera percorrida: " << distPerc << "\n";


    for(vector<string>::iterator i = ANT.begin();i < ANT.end(); i++){ //Imprime o vetor de estacoes

        vector<string>::iterator y = i + 1;

        if(y < ANT.end()){
            cout << *i << ", ";
        }else{
            cout << *i << endl;
        }
    }

  }else{
      erro(3); //Informa que nao ha um ciclo
  }

  fclose(Arquivo_bin);
}