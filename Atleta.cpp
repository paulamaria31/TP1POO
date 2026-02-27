#include "Atleta.h"
#include "Pais.h"
#include <iostream>

using namespace std; 

Atleta::Atleta() : Pessoa() {
    this->participacoes = 0;
}

Atleta::Atleta(string nome, string genero, int ano, Pais* pais, int part) 
    : Pessoa(nome, genero, ano, pais, {}), participacoes(part) {}

int Atleta::getParticipacoes() const {
    return this->participacoes;
}

void Atleta::setParticipacoes(int p){
    this->participacoes = p;
}

Pais* Atleta::getPais() const{
    // Chama o getter da Pessoa
    return Pessoa::getPais(); 
}

void Atleta::setPais(Pais *pais) {
    // Chama o setter da Pessoa
    Pessoa::setPais(pais); 
    
    if (pais != nullptr) {
        // Associação bidirecional
        pais->setAtletas(this); 
    }
}

std::vector<Medalha*> Atleta::getMedalhas() const {
    return this->medalhas;
}

void Atleta::setMedalhas(Medalha* medalha) {
    this->medalhas.push_back(medalha);
}

void Atleta::exibirDados(){
    Pessoa::exibirDados(); // Exibe os dados base
    std::cout << "Participacoes: " << this->participacoes << std::endl;
    if (!this->medalhas.empty()) {
        std::cout << "--- Medalhas do Atleta ---" << std::endl;
        for (Medalha* med : this->medalhas) {
            med->exibirDados();
        }
    }
}

Atleta::~Atleta(){
    this->medalhas.clear();
}