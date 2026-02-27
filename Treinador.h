#ifndef Treinador_h
#define Treinador_h
#include "Pessoa.h"
#include "Atleta.h"
#include <string>

class Treinador : public Pessoa {
    private:
        std::vector<Atleta*> atletas;
    public:
        Treinador(std::string nome = "", std::string genero = "", int anoNascimento = 0, Pais* pais = nullptr, std::vector<Modalidade*> modalidades = {}, std::vector<Atleta*> atletas = {}); // Construtor movido para o .cpp
        std::vector<Atleta*> getAtletas() const;
        void setAtleta(Atleta* atleta);
        void exibirDados();
        ~Treinador();
};
#endif