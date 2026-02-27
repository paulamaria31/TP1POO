#ifndef Medalha_h
#define Medalha_h
#include <string>
#include "Modalidade.h"

class Medalha {
  private:
    std::string tipo;
    Modalidade* modalidade;
    int ano; 
  public:
    Medalha(std::string tipo="", Modalidade* mod=nullptr, int ano = 0);
    void exibirDados();
    
   
    std::string getTipo() const { return tipo; }
    Modalidade* getModalidade() const { return modalidade; }
    int getAno() const { return ano; }
};
#endif