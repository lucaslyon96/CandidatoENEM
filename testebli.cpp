#include <iostream>
#include <fstream>
#include<cstdlib>
#define MAX 100
using namespace std;
struct Solucao
{
    int alocacao_dos_candidatos[MAX],medianas[MAX],total_de_alocados[MAX],custo;
};
struct Entrada
{
    int numero_de_locais_disponiveis,numero_de_candidatos,numero_de_medianas,locais[MAX];
    int tempo_medio_para_cada_local_de_prova[MAX][MAX];
};
//funcoes
Solucao saida(Solucao&);
void pertubacao(Solucao&,Entrada&);
double avaliacao(Solucao&,Entrada &);
Entrada leitura(char [MAX]);
void solucao_inicial(Solucao &,Entrada & );
void alocacao_dos_candidatos(Solucao&,Entrada&);
void busca_local(Solucao&,Entrada&);
void salva(Solucao&,Entrada&,char[]);
int main2()
{
    Entrada in;
    Solucao solucao;
    char nome_entrada[MAX],nome_saida[MAX];
    int fim,inicio;
    cout<< " Digite o nome do arquivo que estao os dados : "<<endl;
    cin.getline(nome_entrada,MAX);
    cout<< " Digite o nome do arquivo onde serao impressos os dados :"<<endl;
    cin.getline(nome_saida,MAX);
    inicio=time(NULL);
    cout<<"Digite o tempo necessario para o programa rodar :"<<endl;
    cin>>fim;
    in =leitura(nome_entrada);
    solucao_inicial(solucao,in);
    while(time(NULL)-inicio<fim)
    {
        pertubacao(solucao,in);
        alocacao_dos_candidatos(solucao,in);
        busca_local(solucao,in);
    }
    salva(solucao,in,nome_saida);
    return 0;
}

Entrada leitura(char nome[MAX])
{
    int linha;
    Entrada entrada;
    ifstream le(nome);
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
void solucao_inicial(Solucao & solucao,Entrada & in)
{
    srand(time(NULL));
    int teste[MAX]= {};
    // escolhendo onde serao os locais de provas dentre todos
    for(int i=0; i<in.numero_de_medianas; i++)
    {
        solucao.medianas[i]=rand()%in.numero_de_locais_disponiveis;
        while(teste[solucao.medianas[i]]!=0)
        {
            solucao.medianas[i]=rand()%in.numero_de_locais_disponiveis;
        }
        teste[solucao.medianas[i]]=1;
    }
    alocacao_dos_candidatos(solucao,in);
    solucao.custo=avaliacao(solucao,in);
}
double avaliacao(Solucao &solucao,Entrada & in)
{
    double soma=0;
    for(int i=0; i<in.numero_de_candidatos; i++)
    {
        soma+=in.tempo_medio_para_cada_local_de_prova[i][solucao.alocacao_dos_candidatos[i]];
    }
    return soma;
}
void pertubacao(Solucao&solucao,Entrada &in)
{
    int troca=rand()%in.numero_de_locais_disponiveis;
    int indice=rand()%in.numero_de_medianas;
    for(int i=0; i<in.numero_de_medianas; i++)
        while(solucao.medianas[i]==troca)
        {
            troca=rand()%in.numero_de_locais_disponiveis;
        }
    solucao.medianas[indice]=troca;
    if(solucao.custo>avaliacao(solucao,in))
    {
        solucao.custo=avaliacao(solucao,in);
    }
}
void alocacao_dos_candidatos(Solucao&solucao,Entrada&in)
{
    int loc_sort,vagas[MAX]= {};
    for(int i=0; i<in.numero_de_candidatos; i++)
    {
        loc_sort=rand()%in.numero_de_medianas;
        while(in.locais[solucao.medianas[loc_sort]]==vagas[loc_sort])
        {
            loc_sort=rand()%in.numero_de_medianas;
        }
        vagas[loc_sort]++;
        solucao.alocacao_dos_candidatos[i]=solucao.medianas[loc_sort];
    }
    for(int i=0; i<in.numero_de_medianas; i++)
    {
        solucao.total_de_alocados[i]=vagas[i];
    }
}
void busca_local(Solucao&solucao,Entrada&in)
{
    Solucao novo;
    int troca;
    novo=solucao;
    for(int i=0; i<in.numero_de_candidatos; i++)
    {
        for(int j=i+1; i<in.numero_de_candidatos; i++)
        {
            troca=novo.alocacao_dos_candidatos[i];
            novo.alocacao_dos_candidatos[i]=novo.alocacao_dos_candidatos[j];
            novo.alocacao_dos_candidatos[j]=troca;
            if(avaliacao(novo,in)<solucao.custo)
            {
                solucao=novo;
                if(solucao.custo>avaliacao(solucao,in))
                {
                   // solucao=novo;
                    solucao.custo=avaliacao(solucao,in);
                }
            }
        }
    }
}
void salva(Solucao& solucao,Entrada&in,char salve[])
{
    ofstream escreve(salve);
    if(!escreve.is_open())
    {
        cout<<"falha ao abrir o aqrquivo "<<endl;
        exit(1);
    }
    escreve<<"Alocacao dos candidatos:"<<endl;
    for(int i=0; i<in.numero_de_candidatos; i++)
    {
        escreve<<solucao.alocacao_dos_candidatos[i]<<" ";
    }
    escreve<<endl<<"Medianas:"<<endl;
    for(int i=0; i<in.numero_de_medianas; i++)
    {
        escreve<<solucao.medianas[i]<<" ";
    }
    escreve<<endl<<"total de alocados:"<<endl;;
    for(int i=0; i<in.numero_de_medianas; i++)
    {
        escreve<<solucao.total_de_alocados[i]<<" ";
    }
    escreve<<endl<<"custo = "<<solucao.custo;
    escreve.close();
}
