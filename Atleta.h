#ifndef Atleta_h
#define Atleta_h
#include <string>
#include <vector>
#include "Modalidade.h"
#include "Medalha.h"
#include "Pessoa.h"
using namespace std;
#include <iostream>

class Pais;

class Atleta : public Pessoa
{
private:
  int participacoes;
  vector<Medalha *> medalhas;

public:
  Atleta();
  Atleta(std::string nome, std::string genero, int nascimento, Pais *pais, int participacoes);
  int getParticipacoes() const;
  void setParticipacoes(int p);
  // O getPais/setPais é herdado de Pessoa
  Pais *getPais() const; 
  void setPais(Pais *pais);
  vector<Medalha *> getMedalhas() const;
  void setMedalhas(Medalha *medalha);
  void exibirDados();
  ~Atleta();
};
#endif