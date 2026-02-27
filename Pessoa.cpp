#include "Pessoa.h"
#include <iostream>
#include <string>
#include "Pais.h" 
#include "Modalidade.h" 


Pessoa::Pessoa(std::string nome, std::string genero, int anoNascimento, Pais* pais, std::vector<Modalidade*> modalidades) 
    : nome(nome), genero(genero), anoNascimento(anoNascimento), pais(pais), modalidades(modalidades) {};

void Pessoa::exibirDados() {
    std::cout << "--- Dados da Pessoa ---" << std::endl;
    // Acesso direto, pois está dentro da própria classe (atributos private)
    std::cout << "Nome: " << this->nome << std::endl; 
    std::cout << "Genero: " << this->genero <<std::endl;
    std::cout << "Ano de nascimento: " << this->anoNascimento <<std::endl;
    
    if (this->pais != nullptr) {
        // Uso do getter do País
        std::cout << "Pais: " << this->pais->getNome() << std::endl; 
    } else {
        std::cout << "Pais: (Nao informado)" << std::endl;
    }
    
    if (!this->modalidades.empty()) {
        std::cout << "Modalidades:" << std::endl;
        for (Modalidade* mod : this->modalidades) {
            // Uso do getter da Modalidade
            std::cout << " - " << mod->getNome() << std::endl; 
        }
    } else {
        std::cout << "Modalidades: (Nenhuma modalidade cadastrada)" << std::endl;
    }
}

Pais* Pessoa::getPais() const {
    return this->pais;
}

void Pessoa::setPais(Pais* pais) {
    this->pais = pais;
}

std::vector<Modalidade*> Pessoa::getModalidade() const {
    return this->modalidades;
}

void Pessoa::setModalidades(Modalidade* modalidade) {
    this->modalidades.push_back(modalidade);
}

Pessoa::~Pessoa() {
    this->modalidades.clear();
    this->pais = nullptr;
}