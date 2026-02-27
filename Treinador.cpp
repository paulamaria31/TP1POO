#include "Treinador.h"
#include "Atleta.h"
#include <iostream>
#include <vector>

Treinador::Treinador(std::string nome, std::string genero, int anoNascimento, Pais* pais, std::vector<Modalidade*> modalidades, std::vector<Atleta*> atletas)
    : Pessoa(nome, genero, anoNascimento, pais, modalidades), atletas(atletas) {}
    
std::vector<Atleta*> Treinador::getAtletas() const {
    return this->atletas;
}

void Treinador::setAtleta(Atleta* atleta) {
    this->atletas.push_back(atleta);
}

void Treinador::exibirDados() {
    Pessoa::exibirDados(); // Exibe os dados base da Pessoa
    std::cout<< "\n--- Atletas Vinculados ---" <<std::endl;
    if (!this->atletas.empty()) {
        for (Atleta* atleta : this->atletas) {
            // Uso dos getters da Atleta/Pessoa
            std::cout << " - Nome: " << atleta->getNome() << std::endl; 
            std::cout << " - Nasc.: " << atleta->getAnoNascimento() << std::endl; 
            std::cout << " - Genero: " << atleta->getGenero() << std::endl; 
            std::cout << " ---" << std::endl;
        }
    } else {
        std::cout << "(Nenhum atleta vinculado)" << std::endl;
    }
}

Treinador::~Treinador() {
    this->atletas.clear();
}