#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>
#include <random>

using namespace std;

// global
int N;

typedef struct {
    float x;
    float y;
    int id;
} Ponto;

float calcula_dist(Ponto ponto1, Ponto ponto2)
{
    return sqrt(pow(ponto1.x - ponto2.x, 2) +
                pow(ponto1.y- ponto2.y, 2));
}

float calcula_total_dist(vector<Ponto> cidades){
    float total_dist = 0;
    float dist;
    for(int i = 0; i < N-1; i++){
        dist = calcula_dist(cidades[i], cidades[i+1]);
        total_dist += dist;
    }
    // precisa calcular a distancia do ultimo para o final
    dist = calcula_dist(cidades[N], cidades[0]);
    total_dist += dist;
    return total_dist;
}

/*
Encontrei uma maneira de permutar sem precisar de recursão do std mesmo
https://cplusplus.com/reference/algorithm/next_permutation/ 

com isso, vamos permutar e ir achando a melhor distância ao mesmo tempo
*/

int main(int argc, char** argv)  {

    cin >> N;
    vector<Ponto> cidades, melhor_ordem_de_visita;
    vector<int> indices;
    float melhor_dist = 100000000000;
    int num_leaf = 0;
    
    for (int i = 0; i < N; i++) {
        float x, y;
        cin >> x;
        cin >> y;

        Ponto ponto;
        ponto.x = x;
        ponto.y = y;
        ponto.id = i;
        indices.push_back(i);

        cidades.push_back(ponto);
    }

    // isso é levemente desnecessário,
    // mas nos exemplos que achei estavam usando para ordenar o vetor antes de criar a arvore
    // https://stackoverflow.com/questions/18002665/using-stdsort-and-stdnext-permutation  
    sort(indices.begin(), indices.end());
    float dist = 0;
    do {
        // cada loop me da um vetor novo de ids
        for (int i = 0; i < indices.size(); i++) {
            // definindo que o novo id da cidade vai ser o indice aleatorio aqui
            cidades[i].id = indices[i];
            cout << indices[i] << endl;

            // cidades nao muda, mas indices sim
            dist = calcula_total_dist(cidades);
            cout << dist << endl; // teste

            if (dist < melhor_dist){
                melhor_dist = dist;
                melhor_ordem_de_visita = cidades;
                num_leaf += 1;
            }
        }

        
    } while(next_permutation(indices.begin(), indices.end()));

    cout << melhor_dist << " " << 1 << endl;
    for(int id = 0; id < melhor_ordem_de_visita.size(); id++){
        cout << melhor_ordem_de_visita[id].id << " ";
    }
    cout << endl;

    cerr << "num leaf " << num_leaf << endl;

    return 0;
}