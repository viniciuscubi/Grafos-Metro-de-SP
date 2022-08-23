/* 
Autores:
JOAO AUGUSTO FERNANDES BARBOSA - 11953348
VINICIUS SANTOS CUBI PAULO - 11965693 
*/
#include "funcGeraisCpp.hpp"
#include <string.h>

void erro(int n){
    switch (n){
        case(1):
            cout << "Falha na execução da funcionalidade.";
            break;
        case(2):
            cout << "Não existe caminho entre as estações solicitadas.";
            break;
        case(3):
            cout << "Nao existe um ciclo a partir da estacao de origem.";
            break;
    }
    exit(0);
}

map<int, long> mapearByteOffSet(FILE* Arquivo_bin){
  REGISTER r;
  map<int, long> mapa; //variavel que mapeara os codigos da estacao pelo byeoffset
  fseek(Arquivo_bin, 17, SEEK_SET);
  while(fread(&r.removido,sizeof(char),1,Arquivo_bin) != 0){
        long byteoffset = ftell(Arquivo_bin); //pega o byteoffset da posicao
        binToRegister(Arquivo_bin, &r); //transforma em registro
        if(r.removido != '1'){
          mapa.insert(pair<int, long>(r.codEstacao, byteoffset)); //se a estacao nao for removida insere ela no mapa

        }
}
  return mapa;
}


HEADER ler_cabecalho(FILE *Arquivo_bin){
  HEADER h;
  if(Arquivo_bin == NULL){
        erro(1);
        return h;
    }

    
    fread(&h.status,sizeof(char),1,Arquivo_bin);
    fread(&h.topoLista,sizeof(long int),1,Arquivo_bin);
    fread(&h.nroEstacoes,sizeof(int),1,Arquivo_bin);
    fread(&h.nroParesEstacao,sizeof(int),1,Arquivo_bin);
    
    if(h.status == 0 || h.nroEstacoes == 0){
        erro(1);
    }
    //Le o cabecalho inicialmente e o printa a parte
    
  return h;
}

string byteToString(FILE* Arquivo_bin, map<int, long> mapa, int codEst){ //Recebe um byte, vai no arquivo de texto, ve qual é a string e retorna ela
  long byteoffset = ftell(Arquivo_bin); //salva a pos pra n alterar o ponteiro
  map<int, long>::iterator it;
  it = mapa.find(codEst); //recebe do mapa de byteoffset a posicao referente ao codigo
  long pos = it->second; //pega a posicao
  fseek(Arquivo_bin, pos , SEEK_SET); // vai no registro
  REGISTER r; 
  binToRegister(Arquivo_bin, &r); //le o registro da posicao

  fseek(Arquivo_bin, byteoffset, SEEK_SET); // volta ao save do ponteiro
  return r.nomeEstacao; //retorna o nome
}

void criaGrafo(FILE *Arquivo_bin, Grafo *g){

    Grafo  Graph = *g;
    HEADER h = ler_cabecalho(Arquivo_bin); //realiza a leitura do header
    REGISTER r;




        
        
        //Criar tabela com codigo da estacao e nome da estacao
        
        map<int, long> MapaOffSet = mapearByteOffSet(Arquivo_bin);
        
        //Volta pro inicio/fim do header

        fseek(Arquivo_bin, 17, SEEK_SET);
        while(fread(&r.removido,sizeof(char),1,Arquivo_bin) != 0){
            binToRegister(Arquivo_bin, &r); //transforma em registro
            if(r.removido != '1'){

                if(Graph.find(r.nomeEstacao) == Graph.end()){ //Esse nó nao foi inserido ainda, então precisa adiciona-lo



                if(r.codProxEstacao != -1){ //Para inserir precisa verificar se a proxEst nao é menos um
                    map<string, Node> Lista; //Cria uma lista
                    string Prox_estacao = byteToString(Arquivo_bin, MapaOffSet, r.codProxEstacao); //Pega o nome da proxEstacao
                    Node novo(r); //Cria um no com o registro
                    Lista.insert(pair<string, Node> (Prox_estacao, novo)); //insere na lista 



                    if(r.codEstIntegra != -1){ //Se tiver tambem uma estacao de integracao

                    string Prox_estacao = byteToString(Arquivo_bin, MapaOffSet, r.codEstIntegra); //pegamos o nome dela
                    Node novo(r); //criamos outro no com ela
                    
                    if(Prox_estacao.compare(r.nomeEstacao)){ //Caso seja de integracao iinserimos ela na lista ja criada
                        Node integracao(r.codEstIntegra);
                        Lista.insert(pair<string, Node> (Prox_estacao, integracao));
                    }   
                    }

                    Graph.insert(pair<string, map<string,Node>>(r.nomeEstacao, Lista)); //Inserimos no grafo o valor ja com a lista
                }

                else{ //Se o codigo de proxEstacao for -1, verificamos apenas a estIntegra

                    map<string, Node> Lista;
                    if(r.codEstIntegra != -1){
                        string Prox_estacao = byteToString(Arquivo_bin, MapaOffSet, r.codEstIntegra);
                        if(Prox_estacao.compare(r.nomeEstacao)){
                            Node integracao(r.codEstIntegra);
                            Lista.insert(pair<string, Node> (Prox_estacao, integracao));
                        }
                    }
                    Graph.insert(pair<string, map<string,Node>>(r.nomeEstacao, Lista));
                }
                }

                else{ //O no ja tinha sido inserido, entao precisamos verificar, ao menos, as arestas
                //Inserir dentro da lista
                    if(r.codProxEstacao != -1){
                    
                      string Prox_estacao = byteToString(Arquivo_bin, MapaOffSet, r.codProxEstacao);
                      Node novo(r);

                    
                  if(Graph[r.nomeEstacao].find(Prox_estacao) == Graph[r.nomeEstacao].end()){
                    //A estacao ja foi inserida mas sem essa aresta
                    Graph[r.nomeEstacao].insert(pair<string, Node> (Prox_estacao, novo));
                    if(r.codEstIntegra != -1){
                      string Prox_estacao = byteToString(Arquivo_bin, MapaOffSet, r.codEstIntegra);           
                      if(Prox_estacao.compare(r.nomeEstacao)){
                        Node integracao(r.codEstIntegra);
                        Graph[r.nomeEstacao].insert(pair<string, Node> (Prox_estacao, integracao));
                      }
            
                      }
                    }
                    else{
                    //A estacao ja foi inserida e com essa aresta
                    //Acessar vetor de linhas e adicionar essa linha

                        auto i = Graph[r.nomeEstacao].find(Prox_estacao);
                        Graph[r.nomeEstacao].find(Prox_estacao)->second.linhas.insert(pair<string, int>(r.nomeLinha, r.codProxEstacao));
                        

                    }               
                    
                    }

                    

                }
                
            }  
        }

        *g = Graph;

}




void scan_quote_string(char *str) {

	char R;

	while((R = getchar()) != EOF && isspace(R)); // ignorar espaços, \r, \n...

	if(R == 'N' || R == 'n') { // campo NULO
		getchar(); getchar(); getchar(); // ignorar o "ULO" de NULO.
		strcpy(str, ""); // copia string vazia
	} else if(R == '\"') {
		if(scanf("%[^\"]", str) != 1) { // ler até o fechamento das aspas
			strcpy(str, "");
		}
		getchar(); // ignorar aspas fechando
	} else if(R != EOF){ // vc tá tentando ler uma string que não tá entre aspas! Fazer leitura normal %s então, pois deve ser algum inteiro ou algo assim...
		str[0] = R;
		scanf("%s", &str[1]);
	} else { // EOF
		strcpy(str, "");
	}
}




bool buscaProfundidade(Grafo *g, string *v, int *nro,vector<string> *list, vector<int> *d,bool mode){
    
    pintaVertice(g,v); //Pinta o vertice inicialmente passado
    
    Grafo Graph = *g;
    string vertice;
    bool ret = false; //Flag para informar que deve haver retorno pois detectou um ciclo para o vertice inicial
    
    for(map<string,Node>::iterator sec = Graph[*v].begin(); sec != Graph[*v].end(); ++sec){ //Inicia a varrimento pelos filhos do vertice passado

        
        
        map<string,Node>::iterator ter = Graph[sec->first].begin(); 
       

        if(ter->second.cor == 0){ //Verifica a cor do vertice, se estiver branco (branco = 0) adiciona o vertice ao vetor de vertices

            if(mode == false){
                cout << *v << ", " << sec->first << ", " << sec->second.distancia << endl;
            }

            vertice = sec->first;
            
            list->push_back(sec->first);
            
            ret =  buscaProfundidade(g, &vertice, nro, list, d,mode); //Chama a busca por profundidade de maneira recursiva para se seguir a analise
           
        }
        
        Grafo Graph = *g;
        
        ter = Graph[sec->first].begin();  

        d->push_back(sec->second.distancia); //Adiciona a distancia do vertice ao vetor de distancias
        *nro = *nro + 1;

        if((ter->second.cor == 2 || ret == true) && mode == true){ //Verifica a cor do vertice e se esta no modo para deteccao de ciclos, caso sim para todos os testes, retorna verdadeiro
                        

            if(ter->second.cor == 2){ //Verifica se o vertice eh preto se sim adiciona como ultima estacao visitada
                
                list->push_back(ter->first);
            }

            return true;
        }


        
    }
    pintaVertice(g,v); //Pinta o vertice apos ele ter iterado por todos os filhos e todos terem sido visitados pelo menos uma vez
    return false;
}


bool pintaVertice(Grafo *g, string *v){

    Grafo Graph = *g;
    bool flag = false;

    //Itera por todos os vertices do grafo
    //Devido a forma que o grafo foi programado eh necessario atualizar a informacao da cor em todos os filhos
    for(map<string, map<string,Node> >::iterator it = Graph.begin(); it != Graph.end(); ++it){ 
        
        
        map<string,Node>::iterator pri = it->second.begin();
        
        if(!(it->second.empty())){ //Verifica se o vertice possui filhos
        Node n = pri->second;
        if(*v == it->first){ //Verica se o vertice passado eh igual ao vertice da iteracao
            
            if(n.cor == 0){ //Verifica a cor do vertice, caso seja branca (branco = 0) atualiza a cor para cinza (cinza = 1)
                for(map<string,Node>::iterator sec = it->second.begin(); sec != it->second.end(); ++sec){
                    
                    sec->second.cor = 1; 
                    
                    flag = false;  
                }

            }else{
                if(n.cor == 1){ //Verifica a cor do vertice, caso seja cinza (cinza = 1) e todos os filhos sejam cinza atualiza a cor para preto (preto = 2)
                    
                    bool f = false;

                    for(map<string,Node>::iterator sec = it->second.begin(); sec != it->second.end(); ++sec){ //Itera por todos os filhos para verifica se todos foram visitados pelo menos uma vez
                        

                        map<string,Node>::iterator ter =  Graph[sec->first].begin();
                            if(!(Graph[sec->first].empty())){
                            
                            Node nf = ter->second;

                            if(nf.cor == 1 || nf.cor == 2){
                                f = true;
                            }else{
                                
                                f = false;
                            }
                        }  
                    }

                    if(f == true){ //Caso o vertice seja cinza e todos os seus filhos tenham sido visitados pelo menos uma vez a cor eh atualizada pra preto

                        
                        for(map<string,Node>::iterator sec = it->second.begin(); sec != it->second.end(); ++sec){ 
                            

                            sec->second.cor = 2;   
                            
                            flag = true;
                        }

                    }


                }
            }
        
        }
    }
    }

    *g = Graph;
    return flag;

}










