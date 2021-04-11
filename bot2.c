/********************************************************************
  Bot-exemplo
  
  Após receber as informações iniciais do jogo, a cada rodada, esse
  bot irá apenas puxar uma carta e, em seguida, descartá-la.
  Cabe a você agora aprimorar sua estratégia!!!
 ********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "definitions.h"
#include "functions.h"

FILE *log_file;

int main() {
  char line[MAX_LINE];   // dados temporários
  char my_id[ID_SIZE];   // identificador do bot em questão
  Card *my_hand = malloc(sizeof(Card) * 11);

  CardArray discard;
  discard.cards = malloc(sizeof(Card) * 20);
  discard.index = 0;
  discard.length = 20;

  int index_games = 0;
  CardArray *set_games = malloc(sizeof(CardArray) * 10);
  for (int i = 0; i < 10; i++){
    set_games[i].cards = malloc(sizeof(Card) * 20);
    set_games[i].index = 0;
    set_games[i].length = 20;
  }

  log_file = fopen("log", "w");

  setbuf(stdin, NULL);   // stdin, stdout e stderr não terão buffers
  setbuf(stdout, NULL);  // assim, nada é "guardado temporariamente"
  setbuf(stderr, NULL);
  setbuf(log_file, NULL);

  // DADOS DO INÍCIO DA PARTIDA
  read_line(line);               // lê os identificadores dos jogadores
  read_line(line);               // lê o identificador do bot (seu id)
  strncpy(my_id, line, ID_SIZE); // guarda para uso futuro

  // lê as cartas que o bot tem na mão
  read_line(line);
  char* onepiece = strtok(line, "[ ]");
  
  for (int i = 0; i < 11; i++){
    read_card(&my_hand[i], onepiece);
    onepiece = strtok(NULL, "[ ]");
  }

  // lê a carta inicial da pilha de descarte.
  read_line(line);        

  fprintf(log_file, "%s\n", line);
  read_card(&discard.cards[0], line);
  fprintf(log_file, "%d %d\n", discard.cards[0].suit, discard.cards[0].value);


  // DADOS DURANTE A PARTIDA
  while(1) {
    do {                   // lê e descarta os dados até chegar sua vez
      read_line(line);     // sai do laço quando for enviado seu id

      // GESTÃO DO LIXO

    } while (strcmp(line, my_id));    // sai do laço quando for a sua vez!

    printf("GET_STOCK\n");         // envia a ação para puxar uma carta
    read_line(line);               // recebe a carta que puxou
    printf("DISCARD %s\n", line);  // descarta a carta que puxou
  }

  fclose(log_file);

  return 0;
}