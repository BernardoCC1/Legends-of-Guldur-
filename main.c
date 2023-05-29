#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lib.h"

#define MAX_INIMIGOS 10

int main() {
  srand(time(NULL));
  personagem *head = NULL;
  inimigo *headI = NULL;

  // Declaração dos personagens
  inserirH(&head, 100, 55, 100, "Guerreiro Infernal");
  inserirH(&head, 80, 32, 140, "Mago de Gelo");
  inserirH(&head, 90, 40, 120, "Arqueira florestal");

  // Declaração dos inimigos
  inserirI(&headI, 140, 4, 15, 1, "Lamina das Sombras");
  inserirI(&headI, 100, 8, 12, 2, "Cavaleiro Espectral");
  inserirI(&headI, 170, 6, 20, 3, "Servo do Abismo");
  inserirI(&headI, 200, 24, 40, 4, "Arauto do Crepúsculo");
  inserirI(&headI, 400, 2, 6, 5, "Guardião das Trevas");
  inserirI(&headI, 220, 24, 17, 6, "Artorias");
  inserirI(&headI, 230, 27, 16, 7, "Espreitador sombrio");
  inserirI(&headI, 240, 26, 18, 8, "Legião ardente");
  inserirI(&headI, 250, 29, 19, 9, "Soldado do desespero");
  inserirI(&headI, 270, 30, 20, 10, "Lorde das cinzas gwyn");



  
  printf("Lista de Personagens:\n");
  imprimirH(head);
  
  int aux;
  personagem *personagemAtual = NULL;
  inimigo *inimigoAtual;
  inimigoAtual = escolherInimigoAleatorio(headI);
 int escolha;
  do {
    int aux = 0;
    printf("Escolha o seu personagem:\n");
    printf("1. Personagem 1\n");
    printf("2. Personagem 2\n");
    printf("3. Personagem 3\n");
    printf("0. Sair\n");
    scanf("%d", &escolha);

    switch (escolha) {
      case 1:
        personagemAtual = escolherPersonagem(1);
        break;
      case 2:
        personagemAtual = escolherPersonagem(2);
        break;
      case 3:
        personagemAtual = escolherPersonagem(3);
        break;
      case 0:
        printf("Encerrando o jogo.\n");
        break;
      default:
        printf("Escolha inválida. Tente novamente.\n");
        aux = 1;
        break;
    }
  } while (aux);
  printf("\nPersonagem escolhido: %s\n", personagemAtual->nome);

  int inimigosBatalhados[MAX_INIMIGOS];
  int numInimigosBatalhados = 0;

  while (personagemAtual->hp > 0) {
    printf("\nOpções de ação:\n");
    printf("1. Atacar\n");
    printf("2. Atacar com poder mágico\n");
    printf("3. Defender\n");
    printf("Opção: ");
    scanf("%d", &escolha);

    switch (escolha) {
      case 1: {
        if (personagemAtual->hp > 0) {
          int confirmacao;
          printf("Você escolheu atacar. Confirme a ação (1 para confirmar, 0 para cancelar): ");
          scanf("%d", &confirmacao);
          if (confirmacao == 1) {
            ataque(personagemAtual, inimigoAtual);
            if (inimigoAtual->hp <= 0) {
              inimigosBatalhados[numInimigosBatalhados] = inimigoAtual->id;
              numInimigosBatalhados++;
              removerI(&headI, inimigoAtual->id);
              free(inimigoAtual);
              inimigoAtual = escolherInimigoAleatorio(headI);
              if (headI == NULL) {
                printf("\nTodos os inimigos foram derrotados!\n");
                break;
              }
            }
            printf("\nPersonagem: %s (HP: %d)\n", personagemAtual->nome, personagemAtual->hp);
            printf("Inimigo: %s (HP: %d)\n", inimigoAtual->nome, inimigoAtual->hp);
          } else {
            printf("Ação cancelada.\n");
          }
        } else {
          printf("\nO personagem não pode atacar. Sua vida atual é 0.\n");
        }
        break;
      }
      case 2: {
        if (personagemAtual->hp > 0) {
          int confirmacao;
          printf("Você escolheu atacar com poder mágico. Confirme a ação (1 para confirmar, 0 para cancelar): ");
          scanf("%d", &confirmacao);
          if (confirmacao == 1) {
            ataqueMagico(personagemAtual, inimigoAtual);
            if (inimigoAtual->hp <= 0) {
              inimigosBatalhados[numInimigosBatalhados] = inimigoAtual->id;
              numInimigosBatalhados++;
              removerI(&headI, inimigoAtual->id);
              free(inimigoAtual);
              inimigoAtual = escolherInimigoAleatorio(headI);
              if (headI == NULL) {
                printf("\nTodos os inimigos foram derrotados!\n");
                break;
              }
            }
            printf("\nPersonagem: %s (HP: %d)\n", personagemAtual->nome, personagemAtual->hp);
            printf("Inimigo: %s (HP: %d)\n", inimigoAtual->nome, inimigoAtual->hp);
          } else {
            printf("Ação cancelada.\n");
          }
        } else {
          printf("\nO personagem não pode atacar com poder mágico. Sua vida atual é 0.\n");
        }
        break;
      }
      case 3: {
        if (personagemAtual->hp > 0) {
          int confirmacao;
          printf("Você escolheu defender. Confirme a ação (1 para confirmar, 0 para cancelar): ");
          scanf("%d", &confirmacao);
          if (confirmacao == 1) {
            defesa(personagemAtual, inimigoAtual);
            printf("\nPersonagem: %s (HP: %d)\n", personagemAtual->nome, personagemAtual->hp);
            printf("Inimigo: %s (HP: %d)\n", inimigoAtual->nome, inimigoAtual->hp);
          } else {
            printf("Ação cancelada.\n");
          }
        } else {
          printf("\nO personagem não pode defender. Sua vida atual é 0.\n");
        }
        break;
      }
      default:
        printf("\nOpção inválida. Tente novamente.\n");
        break;
    }
  }

  if (personagemAtual->hp <= 0) {
    printf("\nO personagem foi derrotado. Fim de jogo.\n");
  } else {
    printf("\nParabéns! Você derrotou todos os inimigos. Fim de jogo.\n");
  }

  printf("\nLista de inimigos batalhados:\n");
  for (int i = 0; i < numInimigosBatalhados; i++) {
    inimigo *inimigoBatalhado = buscarI(headI, inimigosBatalhados[i]);
    printf("%d. %s\n", i + 1, inimigoBatalhado->nome);
  }

  liberarMemoriaH(head);
  liberarMemoriaI(headI);

  return 0;
}
