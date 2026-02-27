#include <iostream>
#include <string>
#include <limits>
#include "Olimpiada.h"

/*
Trabalho POO

Bernardo Fernandes Costa
João Pedro Cavalcante
Maria Paula Miranda de Souza Montovani Gasparini
Mateus Lima de Araújo
Vítor de Sousa Costa Lopes

*/

using namespace std;


void limparBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main()
{
    Olimpiada olimpiada;
    int op = 0;
    
    // REQUISITO: Carregar dados automaticamente dos arquivos CSV na inicialização
    olimpiada.carregarDados();

    do
    {
        cout << "\n====================================" << endl;
        cout << "--- GESTÃO DE EVENTOS OLÍMPICOS ---" << endl;
        cout << "1 - CADASTRAR PAÍS" << endl;
        cout << "2 - CADASTRAR PESSOA (ATLETA/TREINADOR)" << endl;
        cout << "3 - CRIAR MODALIDADE" << endl;
        cout << "4 - CRIAR MEDALHA" << endl;
        cout << "5 - PREMIAR ATLETA COM MEDALHA" << endl;
        cout << "6 - EXIBIR QUADRO DE MEDALHAS" << endl;
        cout << "7 - LISTAR ATLETAS DE UMA MODALIDADE" << endl;
        cout << "8 - GERAR RELATÓRIOS E ESTATÍSTICAS" << endl;
        cout << "9 - SALVAR DADOS E SAIR" << endl;
        cout << "====================================" << endl;
        cout << "Escolha uma opção: ";
        
        if (!(cin >> op)) {
            cout << "Entrada invalida. Por favor, digite um numero." << endl;
            cin.clear();
            limparBuffer();
            continue;
        }

        switch (op)
        {
        case 1: // CADASTRAR PAÍS
        {
            string codigo;
            string nome;
            limparBuffer(); 
            cout << "--- CADASTRANDO PAIS ---" << endl;
            cout << "Digite o nome do país: ";
            getline(cin, nome);
            cout << "Digite o codigo do país (ex: BRA): ";
            cin >> codigo;
            
            if (olimpiada.cadastrarPais(nome, codigo))
            {
                cout << "País cadastrado com sucesso" << endl;
            }
            else
            {
                cout << "Não foi possível cadastrar o país (verifique o código)" << endl;
            }
            limparBuffer();
            break;
        }
        case 2: // CADASTRAR PESSOA (ATLETA/TREINADOR)
        {
            int tipo_pessoa;
            string nome, genero, codigoPais;
            int nascimento;
            Pais *pais;

            cout << "\n--- CADASTRANDO PESSOA ---" << endl;
            cout << "1 - Cadastrar Atleta" << endl;
            cout << "2 - Cadastrar Treinador" << endl;
            cout << "Escolha o tipo de pessoa: ";
            if (!(cin >> tipo_pessoa) || (tipo_pessoa != 1 && tipo_pessoa != 2)) {
                cout << "Opcao invalida." << endl;
                cin.clear();
                limparBuffer();
                break;
            }
            limparBuffer(); 

            cout << "Qual o nome? ";
            getline(cin, nome);
            cout << "Qual genero? ";
            getline(cin, genero);
            cout << "Qual o ano de nascimento? ";
            cin >> nascimento;
            limparBuffer(); 

            cout << "\n--- PAÍS VINCULADO ---" << endl;
            olimpiada.listarPaises();
            cout << "Qual o codigo do pais da pessoa? ";
            cin >> codigoPais;
            limparBuffer(); 
            
            pais = olimpiada.getPais(codigoPais);
            while (pais == nullptr)
            {
                cout << "Esse pais não existe, digite outro codigo: ";
                cin >> codigoPais;
                limparBuffer();
                pais = olimpiada.getPais(codigoPais);
            }

            if (tipo_pessoa == 1) { // Atleta
                int participacoes;
                cout << "Quantas participacoes o atleta tem? ";
                cin >> participacoes;
                limparBuffer();
                olimpiada.cadastrarAtleta(nome, genero, nascimento, pais, participacoes);
            } else if (tipo_pessoa == 2) { // Treinador
                olimpiada.cadastrarTreinador(nome, genero, nascimento, pais);
            }
        }
        break;
        case 3: // CRIAR MODALIDADE
        {
            string codigo;
            string nome;
            int evento;

            limparBuffer();
            cout << "--- CADASTRANDO MODALIDADE ---" << endl;
            cout << "Qual o codigo (ex: FUTE): ";
            getline(cin, codigo);
            cout << "Qual o nome: ";
            getline(cin, nome);
            cout << "Qual o evento: " << endl;
            cout << "1 - Olimpiadas" << endl;
            cout << "2 - Olimpiadas de Inverno" << endl;
            cout << "3 - Paralimpaidas" << endl;
            cout << "Opcao: ";
            cin >> evento;
            limparBuffer();
            
            if (olimpiada.cadastrarModalidade(codigo, nome, evento))
            {
                cout << "Modalidade cadastrada com sucesso" << endl;
            }
            else
            {
                cout << "Não foi possível cadastrar a modalidade (verifique o código)" << endl;
            }
        }
        break;
        case 4: // CRIAR MEDALHA
        {
            limparBuffer(); 
            olimpiada.cadastrarMedalha();
            limparBuffer();
            break;
        }
        case 5: // PREMIAR ATLETA COM MEDALHA
        {
            string nomeAtleta, tipo, codigo;
            int ano;
            cout << "--- PREMIANDO ATLETA COM MEDALHA ---" << endl;
            limparBuffer();
            olimpiada.listarAtletas();
            cout << "Qual o nome do atleta que voce quer premiar? ";
            getline(cin, nomeAtleta);
            
            Atleta *atleta = olimpiada.getAtleta(nomeAtleta);
            while (atleta == nullptr)
            {
                cout << "Esse atleta nao existe, digite o nome novamente: ";
                getline(cin, nomeAtleta);
                atleta = olimpiada.getAtleta(nomeAtleta);
            }
            
            olimpiada.listarMedalhas();
            cout << "--- SELECIONAR MEDALHA EXISTENTE ---" << endl;
            cout << "Digite o tipo da medalha (Ouro/Prata/Bronze): ";
            cin >> tipo;
            cout << "Digite o codigo da modalidade da medalha: ";
            cin >> codigo;
            cout << "Digite o ano da medalha: ";
            cin >> ano;
            limparBuffer();

            olimpiada.premiarAtleta(atleta, tipo, codigo, ano);
        }
        break;
        case 6: // EXIBIR QUADRO DE MEDALHAS
        {
            int ano, evento;
            cout << "--- EXIBIR QUADRO DE MEDALHAS ---" << endl;
            cout << "Qual o ano do evento? ";
            cin >> ano;
            cout << "Qual o tipo de evento: " << endl;
            cout << "1 - Olimpiadas" << endl;
            cout << "2 - Olimpiadas de Inverno" << endl;
            cout << "3 - Paralimpaidas" << endl;
            cout << "Opcao: ";
            cin >> evento;
            limparBuffer();

            if (evento >= 1 && evento <= 3) {
                olimpiada.exibirQuadroMedalhas(ano, evento);
            } else {
                cout << "Opcao de evento invalida." << endl;
            }
        }
        break;
        
        case 7: // LISTAR ATLETAS DE UMA MODALIDADE
        {
            string codigo;
            olimpiada.listarModalidades();
            cout << "Qual o codigo da modalidade que voce quer saber os atletas? ";
            cin >> codigo;
            limparBuffer();
            olimpiada.listarAtletasModalidades(codigo);
        }
            break;
            
        case 8: // GERAR RELATÓRIOS E ESTATÍSTICAS
            olimpiada.gerarRelatorios();
            break;
            
        case 9: // SALVAR DADOS E SAIR
            olimpiada.salvarDados();
            break;

        default:
            cout << "Não existe essa opção" << endl;
            break;
        }
    } while (op != 9);

    return 0;
}