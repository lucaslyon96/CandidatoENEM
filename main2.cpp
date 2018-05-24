#include <iostream>
#include <fstream>>
#define MAX 100
using namespace std;
struct Solucao{
    int alocacao_dos_candidatos[MAX],medianas[MAX],total_de_alocados[MAX],custo;
};
int maim()
{
    char nome_entrada[MAX],nome_saida[MAX];
    int quant_cand,locais_disponiveis;
    cout<< " Digite o nome do arquivo que estao os dados : "<<endl;
    cin.getline(nome_entrada,MAX);
    cout<< " Digite o nome do arquivo onde serao impressos os dados :"<<endl;
    cin.getline(nome_saida,MAX);
    ifstream dados(nome_entrada);
    ofstream saida(nome_saida);
    if (!dados.is_open()){
        cout<< "o arquivo nao pode ser aberto "<<endl;
       // exit(1);
    }

}

