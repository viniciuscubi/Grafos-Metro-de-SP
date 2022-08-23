/* 
Autores:
JOAO AUGUSTO FERNANDES BARBOSA - 11953348
VINICIUS SANTOS CUBI PAULO - 11965693 
*/
#include "FuncCpp.hpp"

void geraArvMin(Grafo Graph, Grafo *g, string vertice);
void criaGrafoAresta(Grafo *g, pair<string,pair<string,int> > info ); 
void achaMenorDist(Grafo Graph,string *u,string *v, int *distancia, vector<string> vetV); 
void criaGrafoBi(FILE *Arquivo_bin, Grafo *g);
void byteToReg(FILE* Arquivo_bin, map<int, long> mapa, int codEst, REGISTER *r); 

void func_ten(){

  string nome_arquivo_bin, nomeCampo, campo;
  cin >> nome_arquivo_bin >> nomeCampo;
  getline(cin,campo); //Coleta o restante da linha
  campo = campo.erase(0,1).erase(0,1).erase(campo.size()-1,campo.size());  //Retira as aspas 
  FILE *Arquivo_bin = fopen(nome_arquivo_bin.c_str(),"rb");

  if(Arquivo_bin == NULL){
      erro(1); //Verifica se o arquivo foi aberto corretamente
      return;
  }

  Grafo Graph;
  Grafo ArvoreMin;
  criaGrafoBi(Arquivo_bin, &Graph); //Cria o grafo bidirecional
  
  geraArvMin(Graph, &ArvoreMin, campo); //Cria a arvore de geracao minima
  
  
  int nro = 0;
  vector<string> list;
  vector<int> d;

  list.push_back(campo);
  buscaProfundidade(&ArvoreMin, &campo, &nro, &list, &d,false); //Realiza a busca em profundidade no modo de impressao





}

//A partir de um codigo de estacao passado, retorna o registro inteiro da estacao
void byteToReg(FILE* Arquivo_bin, map<int, long> mapa, int codEst, REGISTER *r){
  long byteoffset = ftell(Arquivo_bin);
  map<int, long>::iterator it;
  it = mapa.find(codEst);
  long pos = it->second;
  fseek(Arquivo_bin, pos , SEEK_SET);
  binToRegister(Arquivo_bin, r);
  fseek(Arquivo_bin, byteoffset, SEEK_SET); 
}

void criaGrafoBi(FILE *Arquivo_bin, Grafo *g){
 
    Grafo  Graph = *g;
    HEADER h = ler_cabecalho(Arquivo_bin);
    REGISTER r;
    REGISTER rr;

    if(h.nroEstacoes == 0){ //Verifica
            erro(1);
            return;
        }


        
        
        //Criar tabela com codigo da estacao e nome da estacao
        
        map<int, long> MapaOffSet = mapearByteOffSet(Arquivo_bin);
        

        fseek(Arquivo_bin, 17, SEEK_SET);
        while(fread(&r.removido,sizeof(char),1,Arquivo_bin) != 0){
            binToRegister(Arquivo_bin, &r); //pega o registro no arquivo
            if(r.removido != '1'){

                if(Graph.find(r.nomeEstacao) == Graph.end()){ //Verifica se o registro ja foi inserido



                if(r.codProxEstacao != -1){ //verifica se eh um codigo valido
                    map<string, Node> Lista; //Cria uma aresta do vertice para o filho
                    map<string, Node> ListaR; //Cria uma aresta do filho para o vertice

                    string Prox_estacao = byteToString(Arquivo_bin, MapaOffSet, r.codProxEstacao); //Pega a o nome da proxima estacao
                    
                    byteToReg(Arquivo_bin, MapaOffSet, r.codProxEstacao,&rr); //Recupera o registro do codigo da estacao passado
                   
                    rr.distProxEstacao = r.distProxEstacao; //Iguala a distancia entre as estacoes

                    //Cria os vertices
                    Node novo(r);
                    Node novoR(rr);
                    //Cria as arestas 
                    Lista.insert(pair<string, Node> (Prox_estacao, novo));
                    ListaR.insert(pair<string, Node> (r.nomeEstacao, novoR));
                    
                    if(r.codEstIntegra != -1){ //Verifica se o codigo da estacao de integracao eh valido

                    string Prox_estacao = byteToString(Arquivo_bin, MapaOffSet, r.codEstIntegra); //Recupera nome da proxima estacao
                    byteToReg(Arquivo_bin, MapaOffSet, r.codEstIntegra,&rr); //Recupera registro da proxima estacao
                    
                    rr.distProxEstacao = r.distProxEstacao; //Iguala as distancias

                    //Cria os vertices
                    Node novo(r);
                    Node novoR(rr);
                    
                    if(Prox_estacao.compare(r.nomeEstacao)){ //Verifica se a estacao atual eh a mesma da proxima estacao
                        //Cria os vertices de integracao
                        Node integracao(r.codEstIntegra);
                        Node integracaoR(rr.codEstIntegra);

                        //Cria as arestas de integracao
                        Lista.insert(pair<string, Node> (Prox_estacao, integracao));
                        ListaR.insert(pair<string, Node> (r.nomeEstacao, integracaoR));
                        
                    }
                        


                    }

                    //Adiciona as arestas no grafo
                    Graph.insert(pair<string, map<string,Node>>(r.nomeEstacao, Lista));
                    //Verifica se o filho ja havia sido adicionado anteriomente e adiciona
                    if(Graph.find(Prox_estacao) == Graph.end()){
                        Graph.insert(pair<string, map<string,Node>>(Prox_estacao, ListaR));
                    }else{
                        Graph[Prox_estacao].insert(pair<string, Node> (r.nomeEstacao, novoR));
                    }



                }
                else{
                    map<string, Node> Lista; //Cria uma aresta do vertice para o filho
                    map<string, Node> ListaR; //Cria uma aresta do filho para o vertice

                    if(r.codEstIntegra != -1){  //Verifica se o codigo da estacao de integracao eh valido
                    string Prox_estacao = byteToString(Arquivo_bin, MapaOffSet, r.codEstIntegra); //Recupera nome da proxima estacao
                    
                    
                    byteToReg(Arquivo_bin, MapaOffSet, r.codEstIntegra,&rr);//Recupera registro da proxima estacao
                  
                    rr.distProxEstacao = r.distProxEstacao; //Iguala a distancia entre as estacoes
                    if(Prox_estacao.compare(r.nomeEstacao)){  //Verifica se a estacao atual e a proxima sao a mesma

                        //Cria vertices
                        Node integracao(r.codEstIntegra);
                        Node integracaoR(rr.codEstIntegra);

                        //Cria arestas
                        Lista.insert(pair<string, Node> (Prox_estacao, integracao));
                        ListaR.insert(pair<string, Node> (r.nomeEstacao, integracaoR));
                        
                    }
                    

                    }
                    //Insere aresta no grafo
                    Graph.insert(pair<string, map<string,Node>>(r.nomeEstacao, Lista)); 
                    
                    if(r.codEstIntegra != -1){  //Verifica se o codigo da estacao de integracao 
                        string Prox_estacao = byteToString(Arquivo_bin, MapaOffSet, r.codEstIntegra);
                        Graph.insert(pair<string, map<string,Node>>(Prox_estacao, ListaR));
                        
                    }
                }
                }

                else{ //Ja foi inserido
                //Inserir dentro da lista
                    if(r.codProxEstacao != -1){ //verifica se eh um codigo valido

                    
                    string Prox_estacao = byteToString(Arquivo_bin, MapaOffSet, r.codProxEstacao); //Recupera nome da proxima estacao

                    byteToReg(Arquivo_bin, MapaOffSet, r.codProxEstacao,&rr); //Recupera registro da proxima estacao
           
                    rr.distProxEstacao = r.distProxEstacao; //Iguala a distancia entre as estacoes

                    //Cria vertices
                    Node novo(r);
                    Node novoR(rr);
                    
                    //Verifica se aquela estacao ja havia sido inserida
                    if(Graph[r.nomeEstacao].find(Prox_estacao) == Graph[r.nomeEstacao].end()){
                    //A estacao ja foi inserida mas sem essa aresta
                    //Liga aquele vertice criado ao outro ja existente criando uma aresta
                    Graph[r.nomeEstacao].insert(pair<string, Node> (Prox_estacao, novo));
                    Graph[Prox_estacao].insert(pair<string, Node> (r.nomeEstacao, novoR));

                    if(r.codEstIntegra != -1){ //Verifica se o codigo da estacao de integracao eh valido
                        string Prox_estacao = byteToString(Arquivo_bin, MapaOffSet, r.codEstIntegra); //Recupera nome da proxima estacao
                        byteToReg(Arquivo_bin, MapaOffSet, r.codEstIntegra,&rr); //Recupera registro da proxima estacao
                      
                        rr.distProxEstacao = r.distProxEstacao; //Iguala as distancias entre as estacoes
                        
                        if(Prox_estacao.compare(r.nomeEstacao)){ //Verifica se o nome das estacoes sao iguais
                          //Cria os vertices
                          Node integracao(r.codEstIntegra);
                          Node integracaoR(rr.codEstIntegra);
                          //Liga aquele vertice criado ao outro ja existente criando uma aresta
                          Graph[r.nomeEstacao].insert(pair<string, Node> (Prox_estacao, integracao));
                          Graph[Prox_estacao].insert(pair<string, Node> (r.nomeEstacao, integracaoR));
                        }

                    }
                    }
                    else{
                    //A estacao ja foi inserida e com essa aresta
                    //Acessar vetor de linhas e adicionar essa linha

                        auto i = Graph[r.nomeEstacao].find(Prox_estacao);
                        auto y = Graph[Prox_estacao].find(r.nomeEstacao);
                        
                        //Insere vertices no grafo
                        Graph[r.nomeEstacao].find(Prox_estacao)->second.linhas.insert(pair<string, int>(r.nomeLinha, r.codProxEstacao));
                        Graph[Prox_estacao].find(r.nomeEstacao)->second.linhas.insert(pair<string, int>(r.nomeLinha, r.codEstacao));
                        
                    }

                        
                    
                    }

                    

                }

                
            }  
        }

        *g = Graph;   
}

void geraArvMin(Grafo Graph, Grafo *g, string vertice){

    vector<string> vetV; //Vetor de Vertices
    vector<pair<string,pair<string,int> > > vetA; //Vetor de Arestas (u,(v,distancia))
    string u,v; //Cria arestas u e v
    int distancia = 0;
    vetA.clear(); //Limpa vertor de arestas
    vetV.push_back(vertice); //Inicia o vetor de vertices com o vertic
    u = vertice;
    v = "";

    //Realiza operacao enquanto os vertices nao forem iguais 
    while(v != u){

        //verifica aresta de menor peso, tal que u pertence a vetV e v pertence a aresta(v-u)
        achaMenorDist(Graph, &u, &v, &distancia, vetV);

        //Insere a aresta no vetor de arestas
        vetA.push_back(pair<string,pair<string,int> > (u,pair<string,int>(v,distancia)));

        //Insere o vertice no vetor de vertices
        vetV.push_back(v);

    }

    //Retira a ultima insercao, que eh invalida
    vetA.pop_back();
    vetV.pop_back();

    for(vector<pair<string,pair<string,int> > >::iterator i = vetA.begin(); i != vetA.end(); ++i){

        //Insere aresta no novo grafo de arvore minima
        criaGrafoAresta(g, *i );
        pair<string,int> j = i->second;
    }


}

void criaGrafoAresta(Grafo *g, pair<string,pair<string,int> > info ){
 
    Grafo  Graph = *g;
    REGISTER r;
    REGISTER rr;
    string nomeEstacao = info.first;
    string Prox_estacao = info.second.first;
    int distProxEstacao = info.second.second;

        
    if(Graph.find(nomeEstacao) == Graph.end()){ //Verifica se o vertice ja foi inserido

            
            map<string, Node> Lista;
            map<string, Node> ListaR;

            //Cria vertices
            Node novo(distProxEstacao,0);
            Node novoR(distProxEstacao,0);

            //Cria arestas
            Lista.insert(pair<string, Node> (Prox_estacao, novo));
            ListaR.insert(pair<string, Node> (nomeEstacao, novoR));
            
            //Insre arestas no grafo
            Graph.insert(pair<string, map<string,Node>>(nomeEstacao, Lista));
            Graph.insert(pair<string, map<string,Node>>(Prox_estacao, ListaR));

        }
        else{ //Ja foi inserido
        //Inserir dentro da lista

            //Cria vertices
            Node novo(distProxEstacao,0);
            Node novoR(distProxEstacao,0);
            
            if(Graph[nomeEstacao].find(Prox_estacao) == Graph[nomeEstacao].end()){
            //A estacao ja foi inserida mas sem essa aresta

            //Liga aquele vertice criado ao outro ja existente criando uma aresta
            Graph[nomeEstacao].insert(pair<string, Node> (Prox_estacao, novo));
            Graph[Prox_estacao].insert(pair<string, Node> (nomeEstacao, novoR));

            }
            else{
            //A estacao ja foi inserida e com essa aresta
            //Acessar vetor de linhas e adicionar essa linha

                auto i = Graph[nomeEstacao].find(Prox_estacao);
                auto y = Graph[Prox_estacao].find(nomeEstacao);
                
                //Liga aquele vertice criado ao outro ja existente criando uma aresta
                Graph[nomeEstacao].find(Prox_estacao)->second.linhas.insert(pair<string, int>("", 0));
                Graph[Prox_estacao].find(r.nomeEstacao)->second.linhas.insert(pair<string, int>("", 0));
            }

    }
                
        *g = Graph;   
}

void achaMenorDist(Grafo Graph,string *u,string *v, int *distancia, vector<string> vetV){

    //Inicia variaveis da menor aresta
    string mV = "";
    string mU = "";
    int mDist = INT_MAX;

    for(vector<string>::iterator ver = vetV.begin(); ver != vetV.end(); ++ver){ //Itera pelo vetor de vertices

        map<string,Node> mp = Graph[*ver]; //Itera por todos os filhos do vertice
        for(map<string,Node>::iterator sec = mp.begin(); sec != mp.end(); ++sec){

            //Verifica se a aresta analizada possui uma distancia menor que a salva atualmente (verifica se nao eh uma aresta presente no vetor de arestas)
            if((sec->second.distancia < mDist) && ( find( vetV.begin(), vetV.end(), sec->first) == vetV.end() ) ){
                
                //Se sim atualiza a aresta de menor distancia
                mU = *ver;
                mV = sec->first;
                mDist = sec->second.distancia;
            }else{
                //Se nao verifica se a aresta possui uma distancia igual
              if((sec->second.distancia == mDist) && ( find( vetV.begin(), vetV.end(), sec->first) == vetV.end() ) ){
                  
                  //Se sim verifica se o vertice salvo atualmente precede o filho que esta sendo analisado de maneira alfabetica
                  if(mU.compare(*ver) > 0){
                    mU = *ver;
                    mV = sec->first;
                    mDist = sec->second.distancia;
                  }else{
                    //Se nao verifica se sao a mesmo nome
                    if(mU.compare(*ver) == 0){
                      
                        //Se sim verifica se o filho da aresta salva precede o filho do vertice analisado de maneira alfabetica
                        if(mV.compare(*ver) > 0){

                          mU = *ver;
                          mV = sec->first;
                          mDist = sec->second.distancia;

                        }

                    }
                  }
              }
            
            }
            
 
                          
        }
    }

    *u = mU;
    *v = mV;
    *distancia = mDist;

}