#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>
#include <random>

/*
Raciocínio:

shuffle no vetor recebido
*/

using namespace std;

// global
int N;

typedef struct {
    float x;
    float y;
    int id;
} Ponto;

float calculateDistance(Ponto ponto1, Ponto ponto2)
{
    return sqrt(pow(ponto1.x - ponto2.x, 2) +
                pow(ponto1.y- ponto2.y, 2));
}

float calcula_total_dist(vector<Ponto> cidades){
    float total_dist = 0;
    float dist;
    for(int i = 0; i < N-1; i++){
        // Ponto cidade_origem = cidades[i];
        // Ponto cidade_destino = cidades[i+1];
        dist = calculateDistance(cidades[i], cidades[i+1]);
        total_dist += dist;
        // cout << "Total Dist---------" << endl;
        // cout << total_dist << endl;
    }
    // precisa calcular a distancia do ultimo para o final
    dist = calculateDistance(cidades[N], cidades[0]);
    total_dist += dist;
    return total_dist;
}

int main(int argc, char** argv) {
    // processando o arquivo recebido
    cin >> N;
    vector<Ponto> cidades, melhor_ordem_de_visita, atual_ordem_de_visita;
    
    for (int i = 0; i < N; i++) {
        float x, y;
        cin >> x;
        cin >> y;

        Ponto ponto;
        ponto.x = x;
        ponto.y = y;
        ponto.id = i;

        cidades.push_back(ponto);
    }

    float dist;
    float melhor_dist = 100000;
    // int num_vezes = 0;

    atual_ordem_de_visita = cidades;

    default_random_engine generator;
    shuffle(begin(atual_ordem_de_visita), end(atual_ordem_de_visita), generator); // fixar uma seed
    //random_shuffle(cidades.begin(), cidades.end());

    for (int i = 0; i < 10; i++) {
        // calcula a distancia do vetor gerado
        dist = calcula_total_dist(atual_ordem_de_visita);

        if (dist < melhor_dist){
            melhor_dist = dist;
            melhor_ordem_de_visita = atual_ordem_de_visita;
        }

        // fazer n vezes
        for (int j = 0; j < N-1; j++){
            iter_swap(atual_ordem_de_visita.begin()+j ,atual_ordem_de_visita.begin()+j+1);

            dist = calcula_total_dist(atual_ordem_de_visita);
            if (dist < melhor_dist){
                melhor_dist = dist;
                melhor_ordem_de_visita = atual_ordem_de_visita;
            }

            // printa como erro só o melhor de todos esses casos
            cerr << "local: " << dist << " ";
            for(int id = 0; id < atual_ordem_de_visita.size(); id++){
                cerr << atual_ordem_de_visita[id].id << " ";
            }
            cerr << endl;
            // num_vezes++;
        }
        // num_vezes++;
    }
    // cout << num_vezes << endl;

    cout << melhor_dist << " " << 0 << endl;
    for(int id = 0; id < melhor_ordem_de_visita.size(); id++){
        cout << melhor_ordem_de_visita[id].id << " ";
    }
    cout << endl; 

    return 0;
}

// saída esperada de erros