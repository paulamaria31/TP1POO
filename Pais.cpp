#include "Pais.h"
#include <iostream>
#include <string>
#include "Atleta.h"
#include <map>
#include "Medalha.h"
#include "Modalidade.h"

Pais::Pais(std::string nome, std::string codigo, std::vector<Atleta *> atletas) : nome(nome), codigo(codigo), atletas(atletas) {};

std::string Pais::getCodigo() const
{
    return this->codigo;
}

std::vector<Atleta *> Pais::getAtletas() const
{
    return this->atletas;
}

std::vector<Medalha*> Pais::getMedalhas() const
{
    std::vector<Medalha *> medalhasOriginais;
    if (!this->atletas.empty())
    {
        for (Atleta *atleta : this->atletas)
        {
            std::vector<Medalha*> medalhasDoAtleta = atleta->getMedalhas();
            for (Medalha *medalha : medalhasDoAtleta)
            {
                medalhasOriginais.push_back(medalha);
            }
        }
    }
    return medalhasOriginais;
}

void Pais::setAtletas(Atleta *atleta)
{
    this->atletas.push_back(atleta);
}

// Conta medalhas de Ouro/Prata/Bronze para o País em um ano/evento específico
std::map<std::string, int> Pais::getMedalhasPorTipo(int ano, int evento) const {
    std::map<std::string, int> contagem;
    contagem["Ouro"] = 0;
    contagem["Prata"] = 0;
    contagem["Bronze"] = 0;

    for (Atleta* atleta : this->atletas) {
        for (Medalha* medalha : atleta->getMedalhas()) {
            // Verifica se a medalha é do ano e evento corretos
            if (medalha->getAno() == ano && 
                medalha->getModalidade() != nullptr &&
                medalha->getModalidade()->getEvento() == evento) 
            {
                std::string tipo = medalha->getTipo();
                if (contagem.count(tipo)) {
                    contagem[tipo]++;
                }
            }
        }
    }
    return contagem;
}

//Calcula a pontuação total do País (usada para classificação)
int Pais::getClassificacao(int ano, int evento) const
{
    std::map<std::string, int> medalhas = getMedalhasPorTipo(ano, evento);
    
    // Regra de pontuação: Ouro = 3, Prata = 2, Bronze = 1 (exemplo)
    int pontos = (medalhas["Ouro"] * 3) + 
                 (medalhas["Prata"] * 2) + 
                 (medalhas["Bronze"] * 1);
                 
    return pontos;
}

Pais::~Pais(){
    this->atletas.clear();
}