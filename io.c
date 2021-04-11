#include <stdio.h>
#include <string.h>
#include "definitions.h"

/** * Lê uma linha da entrada padrão e remove o '\n' se necessário.
 * @param line string a ser alterada com o conteúdo da entrada-padrão.
 */
void read_line(char *line) {
  fgets(line, MAX_LINE, stdin);
  int l = strlen(line) - 1;
  if(line[l] == '\n') {
    line[l] = '\0';
  }
}

void read_card(Card* card, char *line){
  char suit_char[4], value_char;

  if (line[0] == '1')
    sscanf(line, "%c%*c%s", &value_char, suit_char);
  else
    sscanf(line, "%c%s", &value_char, suit_char);

  switch (value_char){
    case 'A': card->value = Ace; break;
    case 'K': card->value = King; break;
    case 'Q': card->value = Queen; break;
    case 'J': card->value = Jack; break;
    case '1': card->value = Ten; break;
    default: card->value = value_char - '0';
  }

  if (strcmp(suit_char, "♦") == 0)
    card->suit = Diamonds;
  else if (strcmp(suit_char, "♥") == 0)
    card->suit = Heart;
  else if (strcmp(suit_char, "♣") == 0)
    card->suit = Clubs;
  else if (strcmp(suit_char, "♠") == 0)
    card->suit = Spades;
}