# supercompproj

Base para criar os projetos de supercomputação 2022.2


## Heurística

Sua implementação da heurística "Cidade mais próxima" deverá reproduzir os resultados mostrados nos arquivos de entrada/saída desta pasta. Para rodar o verificador de soluções execute

Crie um arquivo .cpp na pasta /heuristico e implemente o seu algoritmo.

$> python3 corretor.py heuristico

### Testes pontuais:

Compilar:

```cpp
g++ -Wall -std=c++11 1heuristica.cpp -o heuristica
```

Rodar:

```cpp
./heuristica < in-N.txt
```

### Teste geral:

```console
python3 corretor.py heuristico
```


## Busca-local

Sua implementação da busca local deverá satisfazer os requisitos apresentados na página de projeto. Para rodar o verificador de soluções execute

Crie um arquivo .cpp na pasta /busca-local e implemente o seu algoritmo.

$> python3 corretor.py local

### Testes pontuais:

Compilar:

```cpp
g++ -Wall -std=c++11 2buscalocal.cpp -o buscaloc
```

Rodar:

```cpp
./buscaloc < in-N.txt
```

### Teste geral:

```console
python3 corretor.py local
```

## Busca-exaustiva

### Testes pontuais:

Compilar:

```cpp
g++ -Wall -std=c++11 3buscaexaustiva.cpp -o buscaex
```

Rodar:

```cpp
./buscaex < in-N.txt
```

### Teste geral:

```console
python3 corretor.py global
```
