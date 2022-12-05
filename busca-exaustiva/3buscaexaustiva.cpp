#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>
#include <random>
#include <algorithm>
#include <omp.h>

// testes pontuais:
// compilar:
// g++ -Wall -std=c++11 3buscaexaustiva.cpp -o buscaex
// rodar:
// ./buscaex < in-N.txt
// teste geral:
// python3 corretor.py global

using namespace std;

// global
int N;

typedef struct {
    float x;
    float y;
    int id;
} Ponto;

// calcula distância simples entre duas cidades
float calcula_dist(Ponto ponto1, Ponto ponto2)
{
    return sqrt(pow(ponto1.x - ponto2.x, 2) +
                pow(ponto1.y- ponto2.y, 2));
}

// calcula a distância total entre todas as cidades
// cuidado! a ordem importa
float calcula_total_dist(vector<Ponto> cidades){
    float total_dist = 0;
    float dist;
    for(int i = 0; i < N-1; i++){
        dist = calcula_dist(cidades[i], cidades[i+1]);
        total_dist += dist;
    }
    // precisa calcular a distancia do ultimo para o inicial
    dist = calcula_dist(cidades[N-1], cidades[0]);
    total_dist += dist;
    return total_dist;
}

// juntei os prints nessa função para não poluir a main
void print_organizado(float melhor_dist, vector<Ponto> melhor_ordem, int num_leaf){
    // número de vezes que encontrou uma melhor solução
    cerr << "num leaf " << num_leaf << endl;

    cout << melhor_dist << " " << 1 << endl;
    for(int id = 0; id < melhor_ordem.size(); id++){
        cout << melhor_ordem[id].id << " ";
    }
    cout << endl;
}

/*
Inicialmente fiz uma série de funções com recursão, mas a lógica estava muito confusa
(as funções comentadas no final do código são as que não deram certo)

Encontrei uma maneira de permutar sem precisar de recursão do std mesmo
https://cplusplus.com/reference/algorithm/next_permutation/ 

com isso, vamos permutar e ir achando a melhor distância ao mesmo tempo
*/

int main(int argc, char** argv)  {

    cin >> N;
    vector<Ponto> cidades, melhor_ordem_de_visita, atual_ordem_de_visita;
    vector<int> indices;
    float melhor_dist = 100000000000; // um número bem grande para não ter risco
    int num_leaf = 0;
    
    // lendo as infos recebidas
    for (int i = 0; i < N; i++) {
        float x, y;
        cin >> x;
        cin >> y;

        Ponto ponto;
        ponto.x = x;
        ponto.y = y;
        ponto.id = i;
        indices.push_back(i);

        // criando o vetor de cidades
        cidades.push_back(ponto);
    }

    // inicializando esse vetor cópia, já que se atualizássemos o valor
    // no próprio cidade, poderia não achar mais a sua própria referência
    atual_ordem_de_visita = cidades;

    // isso é levemente desnecessário,
    // mas nos exemplos que achei estavam usando para ordenar o vetor antes de criar a arvore
    // https://stackoverflow.com/questions/18002665/using-stdsort-and-stdnext-permutation  
    // https://www.geeksforgeeks.org/stdnext_permutation-prev_permutation-c/ 

    sort(indices.begin(), indices.end());
    double init_time, final_time;
    init_time = omp_get_wtime();
    do {
        // cada loop me da um vetor novo de ids
        for (int i = 0; i < indices.size(); i++) {
            // definindo que o novo id da cidade vai ser o indice aleatorio aqui
            atual_ordem_de_visita[i] = cidades[indices[i]];
        }

        // inicializando a distância toda vez para não ter problema de printar a distância antiga
        float dist = calcula_total_dist(atual_ordem_de_visita);

        // encontrando as melhores distâncias
        // e suas respectivas ordens de cidades
        if (dist < melhor_dist){
            melhor_dist = dist;
            melhor_ordem_de_visita = atual_ordem_de_visita;
            num_leaf += 1;
        }
    
    // next permutation nos dá a árvore de combinações de cidades (e nesse caso a ordem importa)
    // idealmente a lógica seria feita usando uma função recursiva
    } while(next_permutation(indices.begin(), indices.end()));
    final_time = omp_get_wtime() - init_time;

    // printa o erro e a saída esperada
    cout << "Calculated in " << final_time << " secs\n";
    print_organizado(melhor_dist,melhor_ordem_de_visita,num_leaf);

    return 0;
}

/*
Raciocínio:

vetor com as cidades ainda nao percorridas
vai tirando do vetor conforme for calculando a melhor opção

vai calcular a distancia de todas as possibilidades de cidades
a melhor das possibilidades vai voltando
*/

// float encontra_melhor_caminho1(Ponto origem, vector<Ponto> cidades_nao_visitadas, float dist){
//     // fixando a origem porque não tem necessidade de escolher a origem também
//     // e facilita a nossa busca, otimizando o nosso programa

//     float dist_retornada;
//     float melhor_dist = 1000000000;
//     vector<Ponto> melhor_ordem_de_visita;

//     for(int i = 0; i < cidades_nao_visitadas.size() - 1; i++) {
//         // tirando a cidade que acabou de ser usada
//         cidades_nao_visitadas.erase(cidades_nao_visitadas.begin()+i);
//         // calculando a distancia entre os dois pontos para se somar à já calculada
//         dist += calcula_dist(cidades_nao_visitadas[i],cidades_nao_visitadas[i+1]);
//         // guardando a distancia retornada daquela branch
//         dist_retornada = encontra_melhor_caminho1(origem, cidades_nao_visitadas, dist);

//         if (dist_retornada < melhor_dist){
//             melhor_dist = dist_retornada;
//             //melhor_ordem_de_visita = cidades_nao_visitadas;

//         }
//         return melhor_dist;
//     }
// }

// float encontra_melhor_caminho(vector<Ponto> cidades){
//     float melhor_dist = 100000000, dist;
//     vector<Ponto> cidades_nao_visitadas = cidades, cidades_melhor_caminho;

//     for(int i = 0; i < cidades_nao_visitadas.size(); i++){
//         cidades_nao_visitadas[i]; // cidade um - se for origem 
//     }
// }

// void arvore_possibilidades(vector<Ponto> cidades, vector<Ponto> cidades_nao_percorridas, int indice){
//     int size = cidades.size();
//     float melhor_dist, dist;

//     if (indice == size){
// 		for (int j = 0; j < size; j++){
// 		    cout << cidades_nao_percorridas[j] << " ";
//         }
// 		cout << endl;
// 		return;
//     }

// 	for (int i = 0; i <= size; i++)
// 	{
// 		cidades_nao_percorridas[indice] = cidades[i];
// 		arvore_possibilidades(cidades, cidades_nao_percorridas, indice+1);
// 	}
// }