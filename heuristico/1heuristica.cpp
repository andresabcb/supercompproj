#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>

// testes pontuais:
// compilar:
// g++ -Wall -std=c++11 1heuristica.cpp -o heuristica
// rodar:
// ./heuristica < in-N.txt
// teste geral:
// python3 corretor.py heuristico

using namespace std;
float total_dist = 0;

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

int id_cidade_com_menor_distancia(Ponto cidade_origem, vector<Ponto> cidades){
    // inicializar o menor como o primeiro calculado
    float menor_dist = 10000000;
    int id_cidade_mais_proxima = 0;

    // conferir se tem que ter igual
    for(int j = 0; j < cidades.size(); j++){
        Ponto cidade_destino = cidades[j];
        float dist = calculateDistance(cidade_origem, cidade_destino);

        if (dist < menor_dist){
            menor_dist = dist;
            id_cidade_mais_proxima = j;
        }
    }
    total_dist += menor_dist;
    return id_cidade_mais_proxima;
}

int main(int argc, char** argv) {
    // processando o arquivo recebido
    int N;
    cin >> N;
    vector<Ponto> coordenadas, ordem_de_visita;
    
    for (int i = 0; i < N; i++) {
        float x, y;
        cin >> x;
        cin >> y;

        Ponto ponto;
        ponto.x = x;
        ponto.y = y;
        ponto.id = i;

        coordenadas.push_back(ponto);
    }

    // variável de controle do loop
    bool tudo_percorrido = false;

    // definindo o ponto de partida
    Ponto ponto_de_partida = coordenadas[0];

    // inicializando a origem atual e o id do destino
    // vamos usar o id do destino para apagar
    Ponto origem_atual = ponto_de_partida;
    int id_cidade_destino;
    ordem_de_visita.push_back(ponto_de_partida); // para printar

    // apagando do vetor a cidade ponto de partida
    coordenadas.erase(coordenadas.begin()+0);

    while (tudo_percorrido != true) {
        
        id_cidade_destino = id_cidade_com_menor_distancia(origem_atual, coordenadas);

        // atualizando a origem agora e retirando do vetor essa cidade
        origem_atual = coordenadas[id_cidade_destino];
        ordem_de_visita.push_back(origem_atual); // para printar
        coordenadas.erase(coordenadas.begin()+id_cidade_destino);

        // quando percorrer tudo, vai sair do loop
        if (coordenadas.size() == 0){
            tudo_percorrido = true;
        }
    }

    // vai da última origem para o ponto de partida e contabiliza isso
    float dist = calculateDistance(origem_atual, ponto_de_partida);
    total_dist += dist;

    cout << total_dist << " ";
    cout << 0 << endl;
    for(int id = 0; id < ordem_de_visita.size(); id++){
        cout << ordem_de_visita[id].id << " ";
    }
    cout << endl;

    return 0;
}
