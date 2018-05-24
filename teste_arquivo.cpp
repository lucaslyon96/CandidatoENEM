#include <iostream>
#include <fstream>
#define MAX 80
using namespace std;
int main()
{
    int linha;
    int numero_de_locais_disponiveis,numero_de_candidatos,numero_de_medianas,locais[MAX];
    int tempo_medio_para_cada_local_de_prova[MAX][MAX];
    ifstream le("dados1.txt");
    if (!le.is_open())
    {
        cout<< "falha ao abrir o a rquivo"<<endl;
        return(1);
    }
    le>>linha;
    numero_de_locais_disponiveis=linha;
    le>>linha;
    numero_de_candidatos=linha;
    le>>linha;
    numero_de_medianas=linha;
    cout<<numero_de_locais_disponiveis<<" "<<numero_de_candidatos<< " "<< numero_de_medianas<<endl;
    for(int i=0;i<numero_de_locais_disponiveis;i++)
    {
        le>>linha;
        locais[i]=linha;
        cout<<locais[i]<< " ";
    }
    cout<<endl;
    for(int i=0; i<numero_de_candidatos;i++)
    {
        for(int j=0; j<numero_de_locais_disponiveis;j++)
        {
            le>>linha;
            tempo_medio_para_cada_local_de_prova[i][j]=linha;
            cout<<tempo_medio_para_cada_local_de_prova[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

        le.close();
    return 0;
}
