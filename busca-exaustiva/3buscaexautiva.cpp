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

float calculateDistance(Ponto ponto1, Ponto ponto2)
{
    return sqrt(pow(ponto1.x - ponto2.x, 2) +
                pow(ponto1.y- ponto2.y, 2));
}

float calcula_total_dist(vector<Ponto> cidades){
    float total_dist = 0;
    float dist;
    for(int i = 0; i < N-1; i++){
        dist = calculateDistance(cidades[i], cidades[i+1]);
        total_dist += dist;
    }
    // precisa calcular a distancia do ultimo para o final
    dist = calculateDistance(cidades[N], cidades[0]);
    total_dist += dist;
    return total_dist;
}

int main(int argc, char** argv) {
    // processando o arquivo recebido
    cin >> N;
    vector<Ponto> cidades, cidades_naovisitadas;
    
    for (int i = 0; i < N; i++) {
        float x, y;
        cin >> x;
        cin >> y;

        Ponto ponto;
        ponto.x = x;
        ponto.y = y;
        ponto.id = i;

        cidades.push_back(ponto);

        // inicializando as cidades nao visitadas
        cidades_naovisitadas = cidades;
    }

    


    cout << melhor_dist << " " << 0 << endl;
    for(int id = 0; id < melhor_ordem_de_visita.size(); id++){
        cout << melhor_ordem_de_visita[id].id << " ";
    }
    cout << endl;

    return 0;
}