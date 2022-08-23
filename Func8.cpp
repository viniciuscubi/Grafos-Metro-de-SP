/* 
Autores:
JOAO AUGUSTO FERNANDES BARBOSA - 11953348
VINICIUS SANTOS CUBI PAULO - 11965693 
*/
#include <queue>
#include "FuncCpp.hpp"
#define INFINITY 99999


void DijkstrasAlgorithm(string start, Grafo Graph, string end){

    map<string, bool> visited;
    map<string, int> distance;
    map<string, string> antecessor;
    
    //Cria um mapa de visitados, todos sao inicialmente falsos
    //Mapa com distancia infinita
    //Mapa com antecessores "Null"

    for(Grafo::const_iterator it = Graph.begin(); it != Graph.end(); ++it){
        visited.insert(pair<string, bool>(it->first, false));
        distance.insert(pair<string, int>(it->first, INFINITY));
        antecessor.insert(pair<string, string>(it->first, ""));

    }

    if(visited.find(start) == visited.end() || visited.find(end) == visited.end()){
        erro(1);
        return;
    }
    

    distance[start] = 0;
    //O no inicial tem distancia zero

    Grafo::iterator it;
    typedef pair<int, string> elem;
    priority_queue <elem, vector<elem>, greater<elem>> priority_q; //Fila com prioridade "invertida" pq tem q ser menor distancia
    priority_q.push(pair<int, string>(0, start)); //Pusho o primeiro elemento

    
    while(!priority_q.empty()){ //Enquanto a fila for vazia
            
            pair<int , string> next = priority_q.top(); //Pego o primeiro elemento
            it = Graph.find(next.second); //Jogo ele pra ser analisado pelo nome
            priority_q.pop();   
            visited[it->first] = true;  //Seto de visitado

            
            for(map<string,Node>::iterator sec = it->second.begin(); sec != it->second.end(); ++sec){
                
                
                    if(visited[sec->first] == false){
                        int alt = distance[it->first] + sec->second.distancia;
                        if(alt < distance[sec->first]){        //Se a distancia for menor que as salva no mapa, atualizo os valores
                            distance[sec->first] = alt;
                            antecessor[sec->first] = it->first;
                            priority_q.push(pair<int, string>(distance[sec->first], sec->first));
                            
                        }
                    }
            }
        
        
         
    }
    vector<string> path;
    if(distance[end] != INFINITY){ //Como eu so tenho os valores dos antecessores, preciso invertelos. Para isso, joguei num vector. Aproveito e ja pego o size
        string value = antecessor[end];
        do{
            path.insert(path.begin(), value);
            value = antecessor[value];

        }while(value != "");

        cout << "Numero de estacoes que serao percorridas: " << path.size() << endl;
        cout << "Distancia que sera percorrida: " << distance[end] << endl;
        for(string i : path)
            cout << i << ", ";
        cout << end << endl;
        }
    else{
        //Se a distancia for infinito
        erro(2);
    }
}


void func_eight(){

    char *nome_arquivo_bin;
    scanf("%ms", &nome_arquivo_bin);

    FILE *Arquivo_bin = fopen(nome_arquivo_bin,"rb");  
    Grafo Graph;

    criaGrafo(Arquivo_bin, &Graph);

    string lixoOrigem, lixoDestino;
    char *startComAspas = (char *) malloc(sizeof(char) * 100);
    char *endComAspas = (char *) malloc(sizeof(char) * 100);

    

    cin >> lixoOrigem;
    scan_quote_string(startComAspas);


    cin >> lixoDestino;
    scan_quote_string(endComAspas);
  
    string start = string(startComAspas);
    string end = string(endComAspas);

    DijkstrasAlgorithm(start, Graph, end);
}


