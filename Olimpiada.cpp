#include "Olimpiada.h"
#include "Atleta.h"
#include "Treinador.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream> 
#include <limits>  
#include <vector>
#include <algorithm> // Necessário para std::sort
#include <map>
#include <cstdio> // Necessário para printf (usado em exibirQuadroMedalhas)

using namespace std;

// --- FUNÇÕES AUXILIARES (Fora da Classe) ---

// Funcao auxiliar para dividir uma string por delimitador
std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Função para converter o código do evento para string
std::string getNomeEvento(int evento) {
    switch (evento) {
        case 1: return "Olimpiadas";
        case 2: return "Olimpiadas de Inverno";
        case 3: return "Paralimpiedas";
        default: return "Evento Desconhecido";
    }
}


// --- IMPLEMENTAÇÃO DA CLASSE OLIMPIADA ---

bool Olimpiada::cadastrarPais(string nome, string codigo)
{
    if (this->getPais(codigo) != nullptr) {
        std::cerr << "ERRO: Codigo de pais ja cadastrado." << std::endl;
        return false;
    }
    
    Pais *pais = new Pais(nome, codigo, {});
    if (pais == nullptr)
    {
        return false;
    }
    this->paises.push_back(pais);
    return true;
}

void Olimpiada::cadastrarAtleta(string nome, string genero, int anoNascimento, Pais *pais, int participacoes)
{
    Atleta *atleta = new Atleta(nome, genero, anoNascimento, pais, participacoes);
    
    if (pais != nullptr) {
        pais->setAtletas(atleta);
    }

    string codigoMod;
    cout << "\n--- Adicionando Modalidades (Digite '0' para encerrar) ---" << endl;

    do
    {
        this->listarModalidades();
        cout << "Codigo da Modalidade: ";
        cin >> codigoMod;

        if (codigoMod != "0")
        {
            Modalidade *mod = this->getModalidade(codigoMod);
            if (mod)
            {
                atleta->setModalidades(mod);
            }
            else
            {
                cout << "Modalidade invalida.\n";
            }
        }
        if (codigoMod == "0" && atleta->getModalidade().empty())
        {
            cout << "O atleta precisa de pelo menos uma modalidade! Digite novamente.\n";
            codigoMod = "continuar";
        }
        // Chamada de limparBuffer assumida no main
    } while (codigoMod != "0" && codigoMod != "continuar");
    
    this->atletas.push_back(atleta);
    cout << "Atleta cadastrado com sucesso!" << endl;
}

void Olimpiada::cadastrarTreinador(string nome, string genero, int anoNascimento, Pais *pais)
{
    Treinador *treinador = new Treinador(nome, genero, anoNascimento, pais, {}, {});
    
    string codigoMod;
    cout << "\n--- Adicionando Modalidades (Digite '0' para encerrar) ---" << endl;

    do
    {
        this->listarModalidades();
        cout << "Codigo da Modalidade (0 para encerrar): ";
        cin >> codigoMod;

        if (codigoMod != "0")
        {
            Modalidade *mod = this->getModalidade(codigoMod);
            if (mod)
            {
                treinador->setModalidades(mod);
            }
            else
            {
                cout << "Modalidade invalida.\n";
            }
        }
        // Chamada de limparBuffer assumida no main
    } while (codigoMod != "0");
    
    this->treinadores.push_back(treinador);
    cout << "Treinador cadastrado com sucesso!" << endl;
}

void Olimpiada::cadastrarMedalha()
{
    Modalidade *modalidade = nullptr;
    string tipo;
    int ano;
    string codigo;

    cout << "--- CADASTRANDO MEDALHA ---" << endl;
    listarModalidades();
    
    cout << "Qual o codigo da modalidade da medalha: " << endl;
    cin >> codigo;
    
    modalidade = this->getModalidade(codigo);
    while (modalidade == nullptr)
    {
        cout << "Essa modalidade nao existe, digite outro codigo: " << endl;
        cin >> codigo;
        modalidade = this->getModalidade(codigo);
    }
    
    cout << "Qual o tipo da medalha (Ouro, Prata, Bronze): " << endl;
    cin >> tipo;
    cout << "Qual o ano de obtencao da medalha: " << endl;
    cin >> ano;

    Medalha *medalha = new Medalha(tipo, modalidade, ano);
    this->medalhas.push_back(medalha);
    cout << "Medalha cadastrada com sucesso!" << endl;
}

Modalidade *Olimpiada::getModalidade(string codigo)
{
    for (size_t c = 0; c < this->modalidades.size(); c++)
    {
        if (this->modalidades[c]->getCodigo() == codigo)
        {
            return this->modalidades[c];
        }
    }

    return nullptr;
}

Atleta *Olimpiada::getAtleta(string nome)
{
    for (size_t c = 0; c < this->atletas.size(); c++)
    {
        if (this->atletas[c]->getNome() == nome)
        {
            return this->atletas[c];
        }
    }

    return nullptr;
}

Medalha *Olimpiada::getMedalha(string tipo, string codigo, int ano)
{
    for (size_t c = 0; c < this->medalhas.size(); c++)
    {
        if (this->medalhas[c]->getTipo() == tipo && 
            this->medalhas[c]->getModalidade() != nullptr && 
            this->medalhas[c]->getModalidade()->getCodigo() == codigo && 
            this->medalhas[c]->getAno() == ano)
        {
            return this->medalhas[c];
        }
    }

    return nullptr;
}

Pais *Olimpiada::getPais(string codigo)
{
    for (size_t c = 0; c < this->paises.size(); c++)
    {
        if (this->paises[c]->getCodigo() == codigo)
        {
            return this->paises[c];
        }
    }
    return nullptr;
}

bool Olimpiada::cadastrarModalidade(string codigo, string nome, int evento)
{
    if (this->getModalidade(codigo) != nullptr) {
        std::cerr << "ERRO: Codigo de modalidade ja cadastrado." << std::endl;
        return false;
    }
    
    Modalidade *modalidade = new Modalidade(nome, codigo, evento);
    if (modalidade == nullptr)
    {
        return false;
    }
    this->modalidades.push_back(modalidade);
    return true;
}

void Olimpiada::listarAtletas()
{
    for (size_t c = 0; c < this->atletas.size(); c++)
    {
        this->atletas[c]->exibirDados();
    }
}

void Olimpiada::listarAtletasModalidades(string codigo)
{
    vector<Modalidade *> modalidadesAtleta = {};
    bool encontrado = false;
    
    for (size_t c = 0; c < this->atletas.size(); c++)
    {
        modalidadesAtleta = this->atletas[c]->getModalidade();
        for (size_t d = 0; d < modalidadesAtleta.size(); d++)
        {
            if (modalidadesAtleta[d]->getCodigo() == codigo)
            {
                this->atletas[c]->exibirDados();
                encontrado = true;
            }
        }
    }
    
    if (!encontrado) {
        cout << "Nenhum atleta encontrado para a modalidade com codigo: " << codigo << endl;
    }
}

void Olimpiada::premiarAtleta(Atleta *atleta, string tipo, string codigo, int ano)
{
    Medalha *medalha = getMedalha(tipo, codigo, ano);
    
    if (medalha != nullptr) {
        atleta->setMedalhas(medalha);
        cout << "Atleta " << atleta->getNome() << " premiado com sucesso!" << endl;
    } else {
        cout << "ERRO: Medalha nao encontrada para premiacao." << endl;
    }
}

void Olimpiada::listarPaises()
{
    for (size_t c = 0; c < this->paises.size(); c++)
    {
        cout << "Nome: " << this->paises[c]->getNome() << endl;
        cout << "Codigo: " << this->paises[c]->getCodigo() << endl;
        cout << "Num. Atletas: " << this->paises[c]->getAtletas().size() << endl;
        cout << "--------------------" << endl;
    }
}

void Olimpiada::listarModalidades()
{
    for (size_t c = 0; c < this->modalidades.size(); c++)
    {
        cout << "Nome: " << this->modalidades[c]->getNome() << endl;
        cout << "Codigo: " << this->modalidades[c]->getCodigo() << endl;
        cout << "Evento: " << this->modalidades[c]->getEvento() << endl;
        cout << "--------------------" << endl;
    }
}

void Olimpiada::listarMedalhas()
{
    for (size_t c = 0; c < this->medalhas.size(); c++)
    {
        this->medalhas[c]->exibirDados();
    }
}

// --- FUNÇÕES DE PERSISTÊNCIA (SALVAMENTO) ---

void Olimpiada::salvarPaises() {
    std::ofstream arquivo("paises.csv"); 
    
    if (arquivo.is_open()) {
        arquivo << "Codigo;Nome\n"; 
        
        for (const auto& pais : paises) {
            arquivo << pais->getCodigo() << ";" 
                    << pais->getNome() << "\n";
        }
        
        arquivo.close();
        std::cout << "Paises salvos com sucesso em paises.csv." << std::endl;
    } else {
        std::cerr << "ERRO: Nao foi possivel abrir o arquivo paises.csv para salvar." << std::endl;
    }
}

void Olimpiada::salvarModalidades() {
    std::ofstream arquivo("modalidades.csv"); 

    if (arquivo.is_open()) {
        arquivo << "Codigo;Nome;Evento\n";
        
        for (const auto& modalidade : modalidades) {
            arquivo << modalidade->getCodigo() << ";" 
                    << modalidade->getNome() << ";" 
                    << modalidade->getEvento() << "\n";
        }
        
        arquivo.close();
        std::cout << "Modalidades salvas com sucesso em modalidades.csv." << std::endl;
    } else {
        std::cerr << "ERRO: Nao foi possivel abrir o arquivo modalidades.csv para salvar." << std::endl;
    }
}

void Olimpiada::salvarMedalhas() {
    std::ofstream arquivo("medalhas.csv"); 

    if (arquivo.is_open()) {
        arquivo << "Tipo;Ano;CodigoModalidade\n";
        
        for (const auto& medalha : medalhas) {
            std::string codigo_modalidade = (medalha->getModalidade() != nullptr) ? medalha->getModalidade()->getCodigo() : "NULO";
            
            arquivo << medalha->getTipo() << ";" 
                    << medalha->getAno() << ";" 
                    << codigo_modalidade << "\n";
        }
        
        arquivo.close();
        std::cout << "Medalhas salvas com sucesso em medalhas.csv." << std::endl;
    } else {
        std::cerr << "ERRO: Nao foi possivel abrir o arquivo medalhas.csv para salvar." << std::endl;
    }
}

void Olimpiada::salvarPessoas() {
    std::ofstream arquivo("pessoas.csv"); 

    if (arquivo.is_open()) {
        arquivo << "Tipo;Nome;Genero;AnoNascimento;CodigoPais;Modalidades(Codigos);DadosEspecificos\n";
        
        // --- Salvar Atletas ---
        for (const auto& atleta : atletas) {
            std::string linha;
            std::string cod_pais = (atleta->getPais() != nullptr) ? atleta->getPais()->getCodigo() : "NULO";
            
            linha += "ATLETA;" + atleta->getNome() + ";" + atleta->getGenero() + ";" + std::to_string(atleta->getAnoNascimento()) + ";" + cod_pais + ";";

            std::string modalidades_str = "";
            for (const auto& mod : atleta->getModalidade()) {
                modalidades_str += mod->getCodigo() + ",";
            }
            if (!modalidades_str.empty()) modalidades_str.pop_back(); 
            linha += modalidades_str + ";";

            linha += std::to_string(atleta->getParticipacoes()) + "|"; 
            
            std::string medalhas_str = "";
            for (const auto& med : atleta->getMedalhas()) {
                std::string cod_mod_med = (med->getModalidade() != nullptr) ? med->getModalidade()->getCodigo() : "NULO";
                medalhas_str += med->getTipo() + ":" + std::to_string(med->getAno()) + ":" + cod_mod_med + ",";
            }
            if (!medalhas_str.empty()) medalhas_str.pop_back(); 
            linha += medalhas_str;

            arquivo << linha << "\n";
        }
        
        // --- Salvar Treinadores ---
        for (const auto& treinador : treinadores) {
            std::string linha;
            std::string cod_pais = (treinador->getPais() != nullptr) ? treinador->getPais()->getCodigo() : "NULO";
            
            linha += "TREINADOR;" + treinador->getNome() + ";" + treinador->getGenero() + ";" + std::to_string(treinador->getAnoNascimento()) + ";" + cod_pais + ";";

            std::string modalidades_str = "";
            for (const auto& mod : treinador->getModalidade()) {
                modalidades_str += mod->getCodigo() + ",";
            }
            if (!modalidades_str.empty()) modalidades_str.pop_back();
            linha += modalidades_str + ";";

            std::string atletas_str = "";
            for (const auto& at : treinador->getAtletas()) {
                atletas_str += at->getNome() + ",";
            }
            if (!atletas_str.empty()) atletas_str.pop_back();
            linha += atletas_str;

            arquivo << linha << "\n";
        }

        arquivo.close();
        std::cout << "Pessoas (Atletas e Treinadores) salvas com sucesso em pessoas.csv." << std::endl;
    } else {
        std::cerr << "ERRO: Nao foi possivel abrir o arquivo pessoas.csv para salvar." << std::endl;
    }
}

void Olimpiada::salvarDados() {
    this->salvarPaises();
    this->salvarModalidades();
    this->salvarMedalhas();
    this->salvarPessoas(); 
    cout << "\nTodos os dados foram salvos com sucesso!" << endl;
}

// --- FUNÇÕES DE PERSISTÊNCIA (CARREGAMENTO) ---

void Olimpiada::carregarModalidades() {
    std::ifstream arquivo("modalidades.csv");
    std::string linha;
    int count = 0;

    if (arquivo.is_open()) {
        std::getline(arquivo, linha); // Ignora o cabeçalho
        
        while (std::getline(arquivo, linha)) {
            std::vector<std::string> campos = split(linha, ';');
            if (campos.size() == 3) {
                std::string codigo = campos[0];
                std::string nome = campos[1];
                int evento = std::stoi(campos[2]);
                
                if (cadastrarModalidade(codigo, nome, evento)) {
                    count++;
                }
            }
        }
        arquivo.close();
        std::cout << "--> " << count << " Modalidades carregadas." << std::endl;
    } else {
        std::cerr << "AVISO: Arquivo modalidades.csv nao encontrado/aberto. Iniciando sem dados de modalidades." << std::endl;
    }
}

void Olimpiada::carregarPaises() {
    std::ifstream arquivo("paises.csv");
    std::string linha;
    int count = 0;

    if (arquivo.is_open()) {
        std::getline(arquivo, linha); // Ignora o cabeçalho
        
        while (std::getline(arquivo, linha)) {
            std::vector<std::string> campos = split(linha, ';');
            if (campos.size() == 2) {
                std::string codigo = campos[0];
                std::string nome = campos[1];
                
                if (cadastrarPais(nome, codigo)) {
                    count++;
                }
            }
        }
        arquivo.close();
        std::cout << "--> " << count << " Paises carregados." << std::endl;
    } else {
        std::cerr << "AVISO: Arquivo paises.csv nao encontrado/aberto. Iniciando sem dados de paises." << std::endl;
    }
}

void Olimpiada::carregarMedalhas() {
    std::ifstream arquivo("medalhas.csv");
    std::string linha;
    int count = 0;

    if (arquivo.is_open()) {
        std::getline(arquivo, linha); // Ignora o cabeçalho
        
        while (std::getline(arquivo, linha)) {
            std::vector<std::string> campos = split(linha, ';');
            if (campos.size() == 3) {
                std::string tipo = campos[0];
                int ano = std::stoi(campos[1]);
                std::string codigo_modalidade = campos[2];
                
                Modalidade* mod = getModalidade(codigo_modalidade);

                if (mod != nullptr) {
                    Medalha *medalha = new Medalha(tipo, mod, ano);
                    this->medalhas.push_back(medalha);
                    count++;
                } else {
                    std::cerr << "AVISO: Medalha ignorada (Modalidade " << codigo_modalidade << " nao encontrada)." << std::endl;
                }
            }
        }
        arquivo.close();
        std::cout << "--> " << count << " Medalhas carregadas." << std::endl;
    } else {
        std::cerr << "AVISO: Arquivo medalhas.csv nao encontrado/aberto. Iniciando sem dados de medalhas." << std::endl;
    }
}

void Olimpiada::carregarPessoas() {
    std::ifstream arquivo("pessoas.csv");
    std::string linha;
    int count_atletas = 0;
    int count_treinadores = 0;

    if (arquivo.is_open()) {
        std::getline(arquivo, linha); // Ignora o cabeçalho
        
        while (std::getline(arquivo, linha)) {
            std::vector<std::string> campos = split(linha, ';');
            if (campos.size() >= 6) { 
                std::string tipo = campos[0];
                std::string nome = campos[1];
                std::string genero = campos[2];
                int anoNascimento = std::stoi(campos[3]);
                std::string codigoPais = campos[4];
                
                Pais* pais = getPais(codigoPais);
                if (pais == nullptr && codigoPais != "NULO") {
                    std::cerr << "AVISO: Pessoa " << nome << " ignorada (Pais " << codigoPais << " nao encontrado)." << std::endl;
                    continue; 
                }
                
                // 1. Associação de Modalidades 
                std::vector<Modalidade*> mods_pessoa;
                std::vector<std::string> cod_mods = split(campos[5], ',');
                for (const auto& cod : cod_mods) {
                    if (!cod.empty()) {
                         Modalidade* mod = getModalidade(cod);
                        if (mod != nullptr) {
                            mods_pessoa.push_back(mod);
                        }
                    }
                }

                if (tipo == "ATLETA" && campos.size() >= 7) {
                    // Dados Específicos: Participacoes|Medalhas
                    std::vector<std::string> dados_esp = split(campos[6], '|');
                    int participacoes = std::stoi(dados_esp[0]);
                    
                    Atleta* atleta = new Atleta(nome, genero, anoNascimento, pais, participacoes);
                    
                    for (Modalidade* mod : mods_pessoa) {
                        atleta->setModalidades(mod);
                    }
                    
                    // Adicionar Medalhas (dados_esp[1])
                    if (dados_esp.size() > 1 && !dados_esp[1].empty()) {
                        std::vector<std::string> medalha_data = split(dados_esp[1], ',');
                        for (const auto& med_str : medalha_data) {
                            // Formato: Tipo:Ano:CodigoMod
                            std::vector<std::string> detalhes = split(med_str, ':');
                            if (detalhes.size() == 3) {
                                Medalha* medalha = getMedalha(detalhes[0], detalhes[2], std::stoi(detalhes[1]));
                                if (medalha != nullptr) {
                                    atleta->setMedalhas(medalha);
                                }
                            }
                        }
                    }
                    
                    this->atletas.push_back(atleta);
                    if (pais != nullptr) { pais->setAtletas(atleta); }
                    count_atletas++;

                } else if (tipo == "TREINADOR" && campos.size() >= 7) {
                    // Dados Específicos: Atletas Vinculados (nomes separados por vírgula)
                    Treinador* treinador = new Treinador(nome, genero, anoNascimento, pais, mods_pessoa, {});
                    
                    // Adicionar Atletas Vinculados (campos[6])
                    std::vector<std::string> nomes_atletas = split(campos[6], ',');
                    for (const auto& nome_atleta : nomes_atletas) {
                        if (!nome_atleta.empty()) {
                            Atleta* at_vinculado = getAtleta(nome_atleta);
                            if (at_vinculado != nullptr) {
                                treinador->setAtleta(at_vinculado);
                            }
                        }
                    }
                    
                    this->treinadores.push_back(treinador);
                    count_treinadores++;
                }
            }
        }
        arquivo.close();
        std::cout << "--> " << count_atletas << " Atletas e " << count_treinadores << " Treinadores carregados." << std::endl;
    } else {
        std::cerr << "AVISO: Arquivo pessoas.csv nao encontrado/aberto. Iniciando sem dados de pessoas." << std::endl;
    }
}

void Olimpiada::carregarDados() {
    std::cout << "\n--- CARREGANDO DADOS DO SISTEMA ---" << std::endl;
    
    // Ordem crucial para resolver dependências
    this->carregarModalidades();
    this->carregarPaises();
    this->carregarMedalhas();
    this->carregarPessoas();
    
    std::cout << "--- CARGA DE DADOS FINALIZADA ---" << std::endl;
}

// Comparador para ordenar Países por pontuação (para exibirQuadroMedalhas)
struct PaisComparator {
    int ano;
    int evento;
    PaisComparator(int a, int e) : ano(a), evento(e) {}
    
    // Sobrecarga do operador () para comparação
    bool operator()(Pais* a, Pais* b) const {
        // Classificação por pontos (decrescente)
        int pontosA = a->getClassificacao(ano, evento);
        int pontosB = b->getClassificacao(ano, evento);
        
        if (pontosA != pontosB) {
            return pontosA > pontosB;
        }
        
        // Em caso de empate, usar o número de Ouro (decrescente)
        int ouroA = a->getMedalhasPorTipo(ano, evento)["Ouro"];
        int ouroB = b->getMedalhasPorTipo(ano, evento)["Ouro"];
        
        if (ouroA != ouroB) {
            return ouroA > ouroB;
        }
        
        // Em caso de novo empate, usar Prata (decrescente)
        int prataA = a->getMedalhasPorTipo(ano, evento)["Prata"];
        int prataB = b->getMedalhasPorTipo(ano, evento)["Prata"];

        return prataA > prataB;
    }
};

// Exibe o Quadro de Medalhas (Requisito 9)
void Olimpiada::exibirQuadroMedalhas(int ano, int evento) {
    
    // 1. Cria uma cópia da lista de países para ordenação
    std::vector<Pais*> ranking = this->paises;
    
    // 2. Ordena usando o comparator personalizado
    std::sort(ranking.begin(), ranking.end(), PaisComparator(ano, evento));
    
    std::cout << "\n==========================================================================" << std::endl;
    std::cout << "--- QUADRO DE MEDALHAS - " << getNomeEvento(evento) << " " << ano << " ---" << std::endl;
    std::cout << "==========================================================================" << std::endl;
    std::cout << "POS | COD | PAÍS                          | OURO | PRATA | BRONZE | PONTOS" << std::endl;
    std::cout << "--------------------------------------------------------------------------" << std::endl;

    int posicao = 1;
    for (Pais* pais : ranking) {
        int pontos = pais->getClassificacao(ano, evento);
        if (pontos >= 0) {
            std::map<std::string, int> medalhas = pais->getMedalhasPorTipo(ano, evento);
            
            // Formatando a saída usando printf para melhor alinhamento
            printf("%3d | %3s | %-30s | %4d | %5d | %6d | %6d\n",
                   posicao, 
                   pais->getCodigo().c_str(), 
                   pais->getNome().c_str(), 
                   medalhas["Ouro"], 
                   medalhas["Prata"], 
                   medalhas["Bronze"], 
                   pontos);
            
            posicao++;
        }
    }
    
    if (posicao == 1) {
        std::cout << "Nenhum país obteve medalhas neste evento/ano." << std::endl;
    }
    std::cout << "==========================================================================" << std::endl;
}


// Menu e Relatórios Estatísticos (Tarefa Extra)
void Olimpiada::gerarRelatorios() {
    int sub_op;
    std::cout << "\n====== RELATÓRIOS E ESTATÍSTICAS ======" << std::endl;
    std::cout << "1. Paises com mais medalhas (Ranking Geral)" << std::endl;
    std::cout << "2. Atletas com mais medalhas" << std::endl;
    std::cout << "3. Atletas com mais participacoes" << std::endl;
    std::cout << "4. Modalidades com mais atletas" << std::endl;
    std::cout << "Escolha uma opcao: ";
    if (!(cin >> sub_op)) {
        cin.clear();
        // Não usa limparBuffer aqui, pois o cin falhou antes do newline
        return;
    }
    // Limpar buffer assumido no main

    switch(sub_op) {
        case 1: {
            // Ranking Geral de Países (Todos os anos/eventos)
            std::cout << "\n--- 1. RANKING GERAL DE MEDALHAS POR PAÍS ---" << std::endl;
            std::map<Pais*, int> pontuacaoTotal;
            for (Pais* pais : this->paises) {
                 int pontos = 0;
                 for (Atleta* atleta : pais->getAtletas()) {
                     for (Medalha* med : atleta->getMedalhas()) {
                         if (med->getTipo() == "Ouro") pontos += 3;
                         else if (med->getTipo() == "Prata") pontos += 2;
                         else if (med->getTipo() == "Bronze") pontos += 1;
                     }
                 }
                 pontuacaoTotal[pais] = pontos;
            }
            
            std::vector<std::pair<Pais*, int>> sorted_ranking(pontuacaoTotal.begin(), pontuacaoTotal.end());
            std::sort(sorted_ranking.begin(), sorted_ranking.end(), 
                [](const auto& a, const auto& b) {
                    return a.second > b.second; 
                });
                
            int pos = 1;
            for(const auto& par : sorted_ranking) {
                if (par.second > 0) {
                    std::cout << pos++ << ". " << par.first->getNome() << " (" << par.first->getCodigo() << ") - " << par.second << " Pontos" << std::endl;
                }
            }
            break;
        }
        case 2: {
            // Atletas com mais medalhas
            std::cout << "\n--- 2. ATLETAS COM MAIS MEDALHAS ---" << std::endl;
            std::vector<Atleta*> rankingAtletas = this->atletas;
            std::sort(rankingAtletas.begin(), rankingAtletas.end(), 
                [](const Atleta* a, const Atleta* b) {
                    return a->getMedalhas().size() > b->getMedalhas().size(); 
                });
            
            int pos = 1;
            for(Atleta* atleta : rankingAtletas) {
                if (atleta->getMedalhas().size() > 0) {
                    std::cout << pos++ << ". " << atleta->getNome() << " - " << atleta->getMedalhas().size() << " medalhas." << std::endl;
                }
            }
            break;
        }
        case 3: {
            // Atletas com mais participações
            std::cout << "\n--- 3. ATLETAS COM MAIS PARTICIPAÇÕES ---" << std::endl;
            std::vector<Atleta*> rankingParticipacoes = this->atletas;
            std::sort(rankingParticipacoes.begin(), rankingParticipacoes.end(), 
                [](const Atleta* a, const Atleta* b) {
                    return a->getParticipacoes() > b->getParticipacoes(); 
                });
            
            int pos = 1;
            for(Atleta* atleta : rankingParticipacoes) {
                if (atleta->getParticipacoes() > 0) {
                    std::cout << pos++ << ". " << atleta->getNome() << " - " << atleta->getParticipacoes() << " participações." << std::endl;
                }
            }
            break;
        }
        case 4: {
            // Modalidades com mais atletas
            std::cout << "\n--- 4. MODALIDADES COM MAIS ATLETAS ---" << std::endl;
            std::map<std::string, int> contagemModalidades;
            for (Atleta* atleta : this->atletas) {
                for (Modalidade* mod : atleta->getModalidade()) {
                    contagemModalidades[mod->getNome()]++;
                }
            }

            std::vector<std::pair<std::string, int>> sorted_modalidades(contagemModalidades.begin(), contagemModalidades.end());
            std::sort(sorted_modalidades.begin(), sorted_modalidades.end(), 
                [](const auto& a, const auto& b) {
                    return a.second > b.second; 
                });
                
            int pos = 1;
            for(const auto& par : sorted_modalidades) {
                std::cout << pos++ << ". " << par.first << " - " << par.second << " atletas." << std::endl;
            }
            break;
        }
        default:
            std::cout << "Opcao de relatorio invalida." << std::endl;
    }
}


// --- DESTRUTOR ---

Olimpiada::~Olimpiada()
{
    for (auto p : paises)
        delete p;
    for (auto a : atletas)
        delete a;
    for (auto t : treinadores)
        delete t;
    for (auto m : modalidades)
        delete m;
    for (auto med : medalhas)
        delete med;
}