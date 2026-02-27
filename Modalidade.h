#ifndef Modalidade_h
#define Modalidade_h
#include <string>

class Modalidade {
  private:
    std::string nome;
    std::string codigo; 
    int evento; 
  public:
    Modalidade(std::string nome, std::string codigo, int evento);
    void exibirDados();
    
  
    std::string getNome() const { return nome; }
    std::string getCodigo() const { return codigo; }
    int getEvento() const { return evento; }
};
#endif