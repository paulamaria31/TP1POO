#ifndef Pessoa_h
#define Pessoa_h
#include <string>
#include <vector>
#include "Pais.h"
#include "Modalidade.h"

class Pessoa {
  private: // Atributos são private para acesso apenas pelos getters/setters.
    std::string nome; 
    std::string genero; 
    int anoNascimento;
  protected:
    Pais* pais;
    std::vector<Modalidade*> modalidades;
  public:
    Pessoa(std::string nome = "", std::string genero = "", int anoNascimento = 0, Pais* pais = nullptr, std::vector<Modalidade*> modalidades = {});
    void exibirDados();
    
    // Getters para os atríbutos privados.
    std::string getNome() const { return nome; }
    std::string getGenero() const { return genero; }
    int getAnoNascimento() const { return anoNascimento; }
    
    Pais* getPais() const;
    void setPais(Pais* pais);
    std::vector<Modalidade*> getModalidade() const;
    void setModalidades(Modalidade* modalidade);
    virtual ~Pessoa();
};
#endif