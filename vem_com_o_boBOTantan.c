/*
DUPLA:
 - José Davi Viana Francelino
 - Thiago de Oliveira Cordeiro
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "definitions.h"
#include "functions.h"

FILE *log_file;

// // insertion sort
// void sort_cards(CardArray *card_array){
//     Card aux;
//     for (int i = 1; i < card_array->index; i++){
//         aux = card_array->cards[i];
//         int j = i - 1;
//         while (j >= 0){
//           if (aux.suit > card_array->cards[j].suit)
//             break;
          
//           if (aux.suit < card_array->cards[j].suit)
//             card_array->cards[j + 1] = card_array->cards[j];
//           else if (aux.value < card_array->cards[j].value)
//             card_array->cards[j + 1] = card_array->cards[j];
//           else
//             break;
//           j--;
//         }
//         card_array->cards[j + 1] = aux;
//     }
// }

// void add_card_at(Card *card, CardArray *card_array, int index){
//   if (card_array->length == card_array->index)
//     card_array->cards = realloc(card_array->cards, sizeof(Card) * (card_array->length + 16));
//   for (int j = card_array->index; j > index; j--)
//     card_array->cards[j] = card_array->cards[j - 1];
//   card_array->cards[index] = *card;
  
//   card_array->index++;
// }

// void add_card(Card *card, CardArray *card_array){
//   for (int i = 0; i < card_array->index; i++){
//     if (card->suit == card_array->cards[i].suit){
//       if (card->value <= card_array->cards[i].value){
//         add_card_at(card, card_array, i); 
//         break;
//       }
//     } else if (card->suit < card_array->cards[i].suit){
//       add_card_at(card, card_array, i);
//       break;
//     }
//   }
// }

char* card_to_str(enum value value, enum suit suit){
  char *card_str = malloc(sizeof(char) * 6);

  switch (value){
    case Ace: strcpy(card_str, "A"); break;
    case King: strcpy(card_str, "K"); break;
    case Queen: strcpy(card_str, "Q"); break;
    case Jack: strcpy(card_str, "J"); break;
    case Ten: strcpy(card_str, "10"); break;
    default:
      card_str[0] = value + '2';
      card_str[1] = '\0';
  }

  switch (suit){
    case Diamonds: strcat(card_str, "♦"); break;
    case Heart: strcat(card_str, "♥"); break;
    case Clubs: strcat(card_str, "♣"); break;
    case Spades: strcat(card_str, "♠"); break;
  }

  return card_str;
}

// void meld_new(int suit, int first, int quantity){
//   char to_print[100];
//   sprintf(to_print, "MELD_NEW [ ");

//   for (int i = first; i < first + quantity; i++){
//     strcat(to_print, card_to_str(suit, first));
//     strcat(to_print, " ");
//   }
//   strcat(to_print, "]");

//   printf("%s\n", to_print);
// }

/** * Realiza a ação GET_DISCARD
 * @param my_hand a mão do jogador.
 * @param discard o lixo do jogo.
 * @param set_game ponteiro para o vetor do jogo baixado.
 * @param suit o naipe da carta do topo do lixo.
 * @param first o valor mais baixo das cartas a serem baixadas.
 * @param quantity a quantidade de cartas a serem baixados.
 * @param last_discard o valor do topo do lixo.
 * @param joker ponteiro para o joker a ser baixado junto com o jogo (NULL se não for baixar joker).
 */
void get_discard(int my_hand[4][13], int discard[4][13], SetGame* set_game, int suit, int first, int quantity, Card* last_discard, int joker_suit){
  // string que guarda o comando completo a ser impresso
  char to_print[16 + 6 * quantity];
  sprintf(to_print, "GET_DISCARD [ ");

  set_game->suit = suit;

  // imprime na string o valor do joker se ele não for NULL
  if (joker_suit != -1){
    strcat(to_print, card_to_str(Two, joker_suit));
    strcat(to_print, " ");
    my_hand[joker_suit][Two]--;
    set_game->joker_suit = joker_suit;
  }

  // passa todas as cartas do lixo para a mão
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 13; j++){
      my_hand[i][j] += discard[i][j];
      discard[i][j] = 0;
    }
  }

  for (int i = first; i < first + quantity; i++){
    // se não for o valor do lixo, imprime a carta
    if (i != last_discard->value) {
      strcat(to_print, card_to_str(i, suit));
      strcat(to_print, " ");
      set_game->cards[i]++;
    }
    my_hand[suit][i]--;
  }
  strcat(to_print, "]");
 
  fprintf(log_file, "%s\n", to_print);
  // imprime o comando
  printf("%s\n", to_print);
}

/** * Realiza a ação MELD_NEW
 * @param my_hand a mão do jogador.
 * @param set_game ponteiro para o vetor do jogo baixado.
 * @param suit o naipe da carta do topo do lixo.
 * @param first o valor mais baixo das cartas a serem baixadas.
 * @param quantity a quantidade de cartas a serem baixados.
 * @param skip o valor de alguma carta que não vai ser baixada.
 * @param joker_suit naipe do joker a ser baixado junto com o jogo (-1 se não for baixar joker). 
 */
void meld_new(int my_hand[4][13], SetGame* set_game, int suit, int first, int quantity, int skip, int joker_suit){
  // string que guarda o comando completo a ser impresso
  char to_print[16 + 6 * quantity];
  sprintf(to_print, "MELD_NEW [ ");
  
  set_game->suit = suit;

  // imprime na string o valor do joker se ele não for NULL
  if (joker_suit != -1){
    strcat(to_print, card_to_str(Two, joker_suit));
    strcat(to_print, " ");
    my_hand[joker_suit][Two]--;
    set_game->joker_suit = joker_suit;
  }

  for (int i = first; i < first + quantity; i++){
    // se não for o valor que vai ser pulado, imprime a carta
    if (i != skip) {
      strcat(to_print, card_to_str(i, suit));
      strcat(to_print, " ");
      my_hand[suit][i]--;
      set_game->cards[i]++;
    }
  }
  strcat(to_print, "]");

  fprintf(log_file, "%s\n", to_print);
  // imprime o comando
  printf("%s\n", to_print);
}

void print_array(int array[4][13]){
  char to_print[400] = "";
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 13; j++){
      for (int k = array[i][j]; k > 0; k--)
        sprintf(to_print, "%s %s", to_print, card_to_str(j, i));
    }
  }
  fprintf(log_file, "%s\n", to_print);
}

int main() {
  char line[MAX_LINE];   // dados temporários
  char my_id[ID_SIZE];   // identificador do bot em questão

  // my_hand[x][y] - quantidade de cartas de naipe x
  // e valor y na mão
  int my_hand[4][13] = {0};

  // CardArray my_hand;
  // my_hand.cards = malloc(sizeof(Card) * 16);
  // my_hand.index = 0;
  // my_hand.length = 16;

  int discard[4][13] = {0};
  Card last_discard;

  // CardArray discard;
  // discard.cards = malloc(sizeof(Card) * 20);
  // discard.index = 0;
  // discard.length = 20;

 // vetor do struct set_games
  int game_index = 0;
  SetGame *set_games = calloc(50, sizeof(SetGame));

  setbuf(stdin, NULL);   // stdin, stdout e stderr não terão buffers
  setbuf(stdout, NULL);  // assim, nada é "guardado temporariamente"
  setbuf(stderr, NULL);

  // DADOS DO INÍCIO DA PARTIDA
  read_line(line);               // lê os identificadores dos jogadores
  read_line(line);               // lê o identificador do bot (seu id)
  strncpy(my_id, line, ID_SIZE); // guarda para uso futuro

  log_file = fopen(line, "w");
  setbuf(log_file, NULL);

  // lê as cartas que o bot tem na mão
  read_line(line);
  char* piece = strtok(line, "[ ]");
  
  for (int i = 0; i < 11; i++){
    Card card;
    read_card(&card, piece);
    my_hand[card.suit][card.value]++;
    piece = strtok(NULL, "[ ]");
  }
  print_array(my_hand);

  // lê a carta inicial da pilha de descarte.
  read_line(line);        

  read_card(&last_discard, line);
  discard[last_discard.suit][last_discard.value]++;

  // DADOS DURANTE A PARTIDA
  while(1) {
    do {                   // lê e descarta os dados até chegar sua vez
      read_line(line);     // sai do laço quando for enviado seu id

      int res = strncmp(line, "GET_DISCARD", 10);

      if (res == 0)
        memset(discard, 0, sizeof(discard));

      res = strncmp(line, "DISCARD", 7);

      if (res == 0) {
        char card_str[6];
        sscanf(line, "DISCARD %s", card_str);
        read_card(&last_discard, card_str);
        discard[last_discard.suit][last_discard.value]++;
      }
    
    } while (strcmp(line, my_id));    // sai do laço quando for a sua vez!
 
    // CHECAR SE DAR PRA PUXAR O LIXO (CP2)

    fprintf(log_file, "Minha vez!\n");

    int suit = last_discard.suit;
    int value = last_discard.value;
    // int get_discard = 0;
    // int first_value;
    // char to_print[30];
    
    fprintf(log_file, "lixo: ");
    print_array(discard);
    if (value >= 2 && my_hand[suit][value - 1] > 0 && my_hand[suit][value - 2] > 0){
      // Primeiro caso: o bot tem as duas cartas antecessoras do lixo na mão
      // sprintf(to_print, "GET_DISCARD [ %s %s ]", card_to_str(value - 2, suit), card_to_str(value - 1, suit));
      // first_value = value - 2;
      // get_discard = 1;
      get_discard(my_hand, discard, &set_games[game_index], suit, value - 2, 3, &last_discard, -1);
      game_index++;
    } else if (value >= 1 && value < 12 && my_hand[suit][value - 1] > 0 && my_hand[suit][value + 1] > 0){
      // Segundo caso: o bot tem a carta antecessora e sucessora do lixo na mão
      // sprintf(to_print, "GET_DISCARD [ %s %s ]", card_to_str(value - 1, suit), card_to_str(value + 1, suit));
      // first_value = value - 1;
      // get_discard = 1;
      get_discard(my_hand, discard, &set_games[game_index], suit, value - 1, 3, &last_discard, -1);
      game_index++;
    } else if (value < 11 && my_hand[suit][value + 1] > 0 && my_hand[suit][value + 2] > 0){
      // Terceiro caso: o bot tem as duas cartas sucessoras do lixo na mão
      // sprintf(to_print, "GET_DISCARD [ %s %s ]", card_to_str(value + 1, suit), card_to_str(value + 2, suit));
      // first_value = value;
      // get_discard = 1;
      get_discard(my_hand, discard, &set_games[game_index], suit, value, 3, &last_discard, -1);
      game_index++;
    }

    // AINDA PRECISA DE CASOS ESPECIAIS PRA O ÁS

    // if (get_discard){
    //   fprintf(log_file, "%s\n", to_print);
    //   printf("%s\n", to_print);

    //   set_games[game_index].suit = suit;
    //   set_games[game_index].cards[first_value]++;
    //   set_games[game_index].cards[first_value + 1]++;
    //   set_games[game_index].cards[first_value + 2]++;
    //   set_games[game_index].joker_suit = -1;
    //   game_index++;
    //   for (int i = 0; i < 4; i++)
    //     for (int j = 0; j < 13; j++)
    //       my_hand[i][j] += discard[i][j];

    //   memset(discard, 0, sizeof(discard)); 

    //   my_hand[suit][first_value]--;
    //   my_hand[suit][first_value + 1]--;
    //   my_hand[suit][first_value + 2]--;
    else if (value == Two){
        printf("GET_STOCK\n");         // envia a ação para puxar uma carta
        read_line(line);               // recebe a carta que puxou
        fprintf(log_file, "GET_STOCK %s\n", line);
    
        Card new_card;
        read_card(&new_card, line);
        my_hand[new_card.suit][new_card.value]++;
        // Caso o lixo seja o número 2 (joker)
        // for(int i = 0; i < 4; i++) {
        //   for(int j = 0; j < 13; j++) {
        //     if(my_hand[i][j] >= 1 && my_hand[i][j + 1] >= 1) {
        //       // THIAGO -- AQUI OLHAAAAA
        //       // Adptar os valores
        //       // ver a posição de acordo com o valor da carta!
        //       set_games[game_index].suit = i;
        //       set_games[game_index].cards[<valor da carta no jogo>]++;
        //       set_games[game_index].cards[]++;
        //       set_games[game_index].cards[]++;
        //       set_games[game_index].joker_suit = -1;
        //       game_index++;
        //       for (int i = 0; i < 4; i++)
        //         for (int j = 0; j < 13; j++)
        //           my_hand[i][j] += discard[i][j];

        //       memset(discard, 0, sizeof(discard)); 

        //       my_hand[suit][first_value]--;
        //       my_hand[suit][first_value + 1]--;
        //       my_hand[suit][first_value + 2]--;
        //             }
        //   }
        // }
    } else { 
      printf("GET_STOCK\n");         // envia a ação para puxar uma carta
      read_line(line);               // recebe a carta que puxou
      fprintf(log_file, "GET_STOCK %s\n", line);
  
      Card new_card;
      read_card(&new_card, line);
      my_hand[new_card.suit][new_card.value]++;
    }
    fprintf(log_file, "mão: ");
    print_array(my_hand);
    // CHECAR SE O JOGADOR TEM JOGO (CP2)

    int joker_suit = -1;
    for (int i = 0; i < 4; i++){
      if (my_hand[i][Two] > 0){
        joker_suit = i;
        break;
      }
    }
    for (int i = 0; i < 4; i++){
      int streak = 0;
      int skip = -1;
      int first;
      for (int j = 0; j < 13; j++){
        if (my_hand[i][j] > 0){
          if (streak == 0)
            first = j;
          streak++;
        } else if (joker_suit != -1 && skip == -1)
          skip = j;
        else {
          streak = 0;
          skip = -1;
        }
      }
      if (streak >= 3){
        fprintf(log_file, "mão: ");
        print_array(my_hand);
        meld_new(my_hand, &set_games[game_index], i, first, streak, skip, joker_suit);
        game_index++;
        joker_suit = -1;
      }
    }
    // DECIDIR SE BAIXA O JOGO (CP3)

    // DECIDIR QUAL CARTA DESCARTAR (CP2)

    char card_str[6];
    for (int i = 0; i < 4; i++){
      int to_break = 0;
      for (int j = 0; j < 13; j++){
        if (my_hand[i][j] > 0){
          printf("DISCARD %s\n", card_to_str(j, i));
          fprintf(log_file, "DISCARD %s\n", card_to_str(j, i));
          my_hand[i][j]--;
          discard[i][j]++;
          last_discard.suit = i;
          last_discard.value = j;
          to_break = 1;
          fprintf(log_file, "mão: ");
          print_array(my_hand);
          break;
        }
      }
      if (to_break)
        break;
    }
  }

  fclose(log_file);

  return 0;
}