#include<iostream>
#include<fstream>
#include<stdlib.h>
#define MAX 100
using namespace std;
struct Entrada
{
    int numero_de_locais_disponiveis,numero_de_candidatos,numero_de_medianas,locais[MAX];
    int tempo_medio_para_cada_local_de_prova[MAX][MAX];
};
Entrada leitura(void);
int main(){
    int vetor[MAX]={4 3 3 1 1 1 3 3 3 4  },soma=0;
    Entrada in;
    in=leitura();
    for(int i=0;i<10;i++){
        soma+=in.tempo_medio_para_cada_local_de_prova[i][vetor[i]];
    }
    cout <<soma;
    return 0;
}
Entrada leitura(void)
{
    int linha;
    Entrada entrada;
    ifstream le("dados1.txt");
    if (!le.is_open())
    {
        cout<< "falha ao abrir o arquivo"<<endl;
        exit(1);
    }
    le>>linha;
    entrada.numero_de_locais_disponiveis=linha;
    le>>linha;
    entrada.numero_de_candidatos=linha;
    le>>linha;
    entrada.numero_de_medianas=linha;
    for(int i=0; i<entrada.numero_de_locais_disponiveis; i++)
    {
        le>>linha;
        entrada.locais[i]=linha;
    }
    for(int i=0; i<entrada.numero_de_candidatos; i++)
    {
        for(int j=0; j<entrada.numero_de_locais_disponiveis; j++)
        {
            le>>linha;
            entrada.tempo_medio_para_cada_local_de_prova[i][j]=linha;
        }
    }
    le.close();
    return entrada;
}
