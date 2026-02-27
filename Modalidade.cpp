#include "Modalidade.h"
#include <string>
#include <iostream>

Modalidade::Modalidade(std::string nome, std::string codigo, int evento) : nome(nome), codigo(codigo), evento(evento) {}

void Modalidade::exibirDados() {
    std::cout << "--- Exibindo Modalidade ---" << std::endl;
    std::cout << "Nome: " << this->nome << std::endl;
    std::cout << "Codigo: " << this->codigo << std::endl;
    std::cout << "Evento: " << this->evento << std::endl;
}