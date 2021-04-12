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

// insertion sort
void sort_cards(CardArray *card_array){
    Card aux;
    for (int i = 1; i < card_array->index; i++){
        aux = card_array->cards[i];
        int j = i - 1;
        while (j >= 0){
          if (aux.suit > card_array->cards[j].suit)
            break;
          
          if (aux.suit < card_array->cards[j].suit)
            card_array->cards[j + 1] = card_array->cards[j];
          else if (aux.value < card_array->cards[j].value)
            card_array->cards[j + 1] = card_array->cards[j];
          else
            break;
          j--;
        }
        card_array->cards[j + 1] = aux;
    }
}

void add_card_at(Card *card, CardArray *card_array, int index){
  if (card_array->length == card_array->index)
    card_array->cards = realloc(card_array->cards, sizeof(Card) * (card_array->length + 16));
  for (int j = card_array->index; j > index; j--)
    card_array->cards[j] = card_array->cards[j - 1];
  card_array->cards[index] = *card;
  
  card_array->index++;
}

void add_card(Card *card, CardArray *card_array){
  for (int i = 0; i < card_array->index; i++){
    if (card->suit == card_array->cards[i].suit){
      if (card->value <= card_array->cards[i].value){
        add_card_at(card, card_array, i); 
        break;
      }
    } else if (card->suit < card_array->cards[i].suit){
      add_card_at(card, card_array, i);
      break;
    }
  }
}

int main() {
  char line[MAX_LINE];   // dados temporários
  char my_id[ID_SIZE];   // identificador do bot em questão

  CardArray my_hand;
  my_hand.cards = malloc(sizeof(Card) * 16);
  my_hand.index = 0;
  my_hand.length = 16;

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
  char* piece = strtok(line, "[ ]");
  
  for (int i = 0; i < 11; i++){
    read_card(&my_hand.cards[i], piece);
    piece = strtok(NULL, "[ ]");
  }
  my_hand.index = 11;

  // ORDENAR MÃO (CP2)
  sort_cards(&my_hand);

  // lê a carta inicial da pilha de descarte.
  read_line(line);        

  fprintf(log_file, "%s\n", line);
  read_card(&discard.cards[0], line);
  fprintf(log_file, "%d %d\n", discard.cards[0].suit, discard.cards[0].value);


  // DADOS DURANTE A PARTIDA
  while(1) {
    do {                   // lê e descarta os dados até chegar sua vez
      read_line(line);     // sai do laço quando for enviado seu id

      int res = strncmp(line, "GET_DISCARD", 10);

      if (res == 0) {
        discard.index = 0;
      }

      int res_d = strncmp(line, "DISCARD", 7);

      if (res_d == 0) {
        int counter = 0;
        char card_str[6];
        sscanf(line, "DISCARD %s", card_str);
        read_card(&discard.cards[discard.index], card_str);
        discard.index++;
      }
    
    } while (strcmp(line, my_id));    // sai do laço quando for a sua vez!

    for (int i = 0; i < my_hand.index - 1; i++) {
      // Caso 1: valor do lixo forma sequencia com as duas primeiras cartas
      if(discard.cards[discard.index - 1].suit ==  my_hand.cards[i].suit) {
        // Primeiro caso: lixo do mesmo naipe e as duas cartas posteriores tem mesmo naipe e são sucessivas do valor do lixo
        if(discard.cards[discard.index - 1].suit == my_hand.cards[i + 1].suit) {
          if (discard.cards[discard.index - 1].value + 1 == my_hand.cards[i].value && discard.cards[discard.index - 1].value + 2 == my_hand.cards[i + 1].value) {
            // descartar o jogo e pegar as demais cartas do lixo
          }
        }

        // Caso com o número 2 (joker) e caso de valores posteriores de mesmo naipe e valores sucessivos (próximos casos)
      }
      
      // Caso 2
    }

    // CHECAR SE DAR PRA PUXAR O LIXO (CP2)

    

    printf("GET_STOCK\n");         // envia a ação para puxar uma carta
    read_line(line);               // recebe a carta que puxou

    Card new_card;
    read_card(&new_card, line);
    add_card(&new_card, &my_hand);

    for (int i = 0; i < my_hand.index; i++)
      fprintf(log_file, "carta %d: %d %d\n", i + 1, my_hand.cards[i].suit, my_hand.cards[i].value);

    // CHECAR SE O JOGADOR TEM JOGO (CP2)

    // DECIDIR SE BAIXA O JOGO (CP3)

    // DECIDIR QUAL CARTA DESCARTAR (CP2)

    printf("DISCARD %s\n", line);  // descarta a carta que puxou
  }

  fclose(log_file);

  return 0;
}