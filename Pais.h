#ifndef Pais_h
#define Pais_h
#include <string>
#include <vector>
#include "Medalha.h"
#include <map>

class Atleta;

class Pais {
  private:
    std::string nome;
    std::string codigo;
    std::vector<Atleta*> atletas;
  public:
    Pais(std::string nome = "", std::string codigo = "", std::vector<Atleta*> atletas = {});
    
    std::string getNome() const { return nome; }
    std::string getCodigo() const;
    
    std::vector<Atleta*> getAtletas() const;
    std::vector<Medalha*> getMedalhas() const;
    void setAtletas(Atleta* atleta);
    
  
    std::map<std::string, int> getMedalhasPorTipo(int ano, int evento) const;
    int getClassificacao(int ano, int evento) const;
    
    ~Pais();
};
#endif