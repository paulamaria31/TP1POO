#include "Medalha.h"
#include <iostream>
#include <string>

Medalha::Medalha(std::string tipo, Modalidade* modalidade, int ano) : tipo(tipo), modalidade(modalidade), ano(ano) {}

void Medalha::exibirDados() {
    std::cout << "--- Dados da Medalha ---" << std::endl;
    std::cout << "Tipo: " << this->tipo <<std::endl;
    
    if(this->modalidade != nullptr) {
        std::cout << "Modalidade:" << std::endl;
        // Uso do getter da Modalidade
        this->modalidade->exibirDados();
    } else {
        std::cout << "Modalidade não existe" << std::endl;
    }
    std::cout << "Ano: " << this->ano << std::endl;
}