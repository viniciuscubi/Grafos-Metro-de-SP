/* 
Autores:
JOAO AUGUSTO FERNANDES BARBOSA - 11953348
VINICIUS SANTOS CUBI PAULO - 11965693 
*/
#include "FuncCpp.hpp"
#define INFINITY 99999

void recursiveBFS(Grafo Graph, string start, string end, map<string, bool>& visited, vector<string>& path, int& path_index, map<string, int>& distance, map<string, string>& antecessor, vector<vector<string>>& print, vector<int>& print_distance){
    visited[start] = true;
    path.insert(path.begin() + path_index , start);
    path_index++;

/*
[[a,b,c] #i
[c,d,e]  #i  - > #print
[h,j,k]] #i 

[b,c,d] #newPath
//Representação "grafica" do que pensei. O metodo de print era bem chato, entao fiz meio que um vector organizado de strings para poder ja ficar na posicao correta

*/
    if(Graph.find(start)->first.compare(Graph.find(end)->first) == 0){ //verifica se o no atual é o no final, se for, printamos
        vector<string> newPath; //Criamos um vetor de string com o novo caminho
        int flag = 0;
        
        for (int i = 0; i < path_index; i++){
            newPath.insert(newPath.end(), path[i]); //adicionamos cada antecessor nesse vetor
        }

        int counter = 0;
        if(print.size() == 0){ //se nao tiver nenhum vetor adicionado no print, inserimos ele primeiro
            print.insert(print.begin(), newPath);
            print_distance.insert(print_distance.begin(), distance[end]);
        }
        else{ //se ja tiver
            
            for(auto i : print){ //Comparamos o tamanho de cada um, se for menor, adicionamos na nova posiçao. Sempre que um valor é inserido, atualizamos também a distancia dele num vetor correspondente printDistance
                if(newPath.size() < i.size()){
                 print.insert(print.begin() + counter, newPath);
                 print_distance.insert(print_distance.begin() + counter, distance[end]);
                 flag = 1;
                 break;
                }
                
                else{ 
                    if(newPath.size() == i.size()){ //se o tamanho for maior
                        int wrong = 0;
                        for(int pos = 0; pos < i.size(); pos++){ 
                            if(newPath[pos].compare(i[pos]) > 0){//verificamos se alguma das cidades da nova estaçao é maior q atual
                                wrong = 1; //se for maior setamos o wrong como 1
                                break;
                            }
                        }
                        if(wrong == 1){
                            counter++;
                            continue; //caso tenha alguma alguma maior, breakamos
                        }

                        else{//caso nao, inseriremos na nova posicao
                            print.insert(print.begin() + counter, newPath);
                            print_distance.insert(print_distance.begin() + counter, distance[end]);
                            flag = 1;
                            break;
                        }
                }
                }
                counter++;
            }
            if(flag == 0){ //caso a flag seja zero, é pq o novo valor deve ser adicionado ao final, por ser o maior
                print.insert(print.end(), newPath);
                print_distance.insert(print_distance.end(), distance[end]);
            }
        }
    }

    else{
        //Se nao for, atualizamos a lista de adjacencia a ser analisada e chamamos recursivamente o bfs, decrescendo o pathindex para atualizar o vetor do path
        Grafo::const_iterator it = Graph.find(start);
        for(map<string,Node>::const_iterator sec = it->second.begin(); sec != it->second.end(); ++sec){
            if(visited[sec->first] == false){
                antecessor[sec->first] = start;
                distance[sec->first] = distance[it->first] + sec->second.distancia;
                recursiveBFS(Graph, sec->first, end, visited, path, path_index, distance, antecessor, print, print_distance);
                
            }
        }

    }
    path_index--;
    visited[start] = false;

}



void AllPathsAlgorithm(Grafo Graph, string start, string end){
    map<string, bool> visited; 
    map<string, int> distance;
    map<string, string> antecessor;
    //Semelhante a oito, refaço o mesmo processo com mapas
    for(Grafo::const_iterator it = Graph.begin(); it != Graph.end(); ++it){
        visited.insert(pair<string, bool>(it->first, false));
        distance.insert(pair<string, int>(it->first, INFINITY));
        antecessor.insert(pair<string, string>(it->first, ""));
    }
    distance[start] = 0;

    if(visited.find(start) == visited.end() || visited.find(end) == visited.end()){
        erro(1);
    }

    vector<string> path;
    vector<vector<string>> print;
    vector<int> print_distance;
    int path_index = 0;
    recursiveBFS(Graph, start, end, visited, path, path_index, distance, antecessor, print, print_distance);

    int i = 0;
    
    if(distance[end] == INFINITY){
        erro(2);
    }

    //Aqui entra a representaçao esquematica no inicio do arquivo. Fica mais tranquilo de entender como é feiot a logica do print
    for(auto a: print){
        cout << "Numero de estacoes que serao percorridas: " << a.size() - 1 << endl;
        cout << "Distancia que sera percorrida: " << print_distance[i]<< endl;
        for(int pos = 0 ; pos < a.size(); pos++){
            string c = a[pos];
            cout << c;
            if(pos < a.size() - 1){
                cout << ", ";
            }
        }
        i++;
        cout << endl << endl;
    }
    
}


void func_eleven(){
        
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

   
 
    AllPathsAlgorithm(Graph, start, end);
}