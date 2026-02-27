#ifndef Olimpiada_h
#define Olimpiada_h
#include "Pais.h"
#include "Atleta.h"
#include "Treinador.h"
#include "Medalha.h"
#include "Modalidade.h"
using namespace std;
#include <vector>

class Olimpiada
{
private:
    vector<Pais*> paises;
    vector<Atleta*> atletas;
    vector<Treinador*> treinadores;
    vector<Medalha*> medalhas;
    vector<Modalidade*> modalidades;

public:
    bool cadastrarPais(string nome, string codigo);
    void cadastrarAtleta(string nome, string genero, int anoNascimento, Pais *pais, int participacoes);
    void cadastrarTreinador(string nome, string genero, int anoNascimento, Pais *pais);
    void cadastrarMedalha();
    bool cadastrarModalidade(string codigo, string nome, int evento);
    void listarAtletas();
    void listarPaises();
    void listarModalidades();
    void listarMedalhas();
    Modalidade *getModalidade(string codigo);
    Atleta* getAtleta(string nome);
    Pais* getPais(string codigo);
    Medalha* getMedalha(string tipo, string codigo, int ano);
    void premiarAtleta(Atleta* atleta, string tipo, string codigo, int ano);
    void listarAtletasModalidades(string codigo);
    
    // FUNÇÕES DE PERSISTÊNCIA
    void salvarDados();
    void salvarPaises();
    void salvarModalidades();
    void salvarMedalhas();
    void salvarPessoas();
    void carregarDados();
    void carregarPaises();
    void carregarModalidades();
    void carregarMedalhas();
    void carregarPessoas();
    
    // FUNÇÕES FALTANTES IMPLEMENTADAS
    void exibirQuadroMedalhas(int ano, int evento); // Ajustando para usar int para evento
    void gerarRelatorios();
    
    ~Olimpiada();
};

#endif