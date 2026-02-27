# TP1POO
Trabalho prático 1 da disciplina Programação Orientada a Objetos

# Sistema de Gerenciamento de Eventos Olímpicos

Desenvolvimento de um sistema em C++ que simule a gestão das Olimpíadas. O sistema deverá administrar informações sobre os países participantes, os atletas, as modalidades esportivas e as medalhas obtidas, com uma interface por linha de comando e persistência de dados em arquivos.

O sistema permite:
1. Cadastro de países
  ● Código, nome, medalhas obtidas, atletas
2. Cadastro de pessoas, sendo:
  ● Atletas: nome, ano de nascimento, gênero, país, modalidade(s), medalhas
obtidas, número de participações nas Olimpíadas
  ● Treinadores: nome, país, modalidade(s), atleta(s) vinculado
3. Criação de medalhas, com:
  ● Modalidade, tipo (ouro, prata ou bronze), ano de obtenção
4. Criação de modalidades, com:
  ● Código, nome, evento (Olímpiadas, Olímpiadas de Inverno ou Paralimpíadas)
5. Associação de atletas a países
6. Associação de atletas a medalhas
7. Associação de medalhas a modalidades
8. Listagem de atletas: ao informar o código da modalidade, exibir o nome e
medalhas dos atletas associados a ela
9. Listagem de países (quadro de medalhas): ao informar o ano e o evento, exibir o
código, nome, medalhas (com separação entre ouro, prata e bronze) e classificação
geral, em ordem decrescente de pontos
10. Salvar e carregar dados automaticamente dos seguintes arquivos (formato CSV):
● pessoas.csv
● medalhas.csv
● paises.csv
● modalidades.csv
