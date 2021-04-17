#ifndef DEF
#define DEF

/** Tamanho máximo do identificador do bot */
#define ID_SIZE 50

/** Tamanho máximo de uma linha da entrada-padrão */
#define MAX_LINE 200

enum suit {
  Diamonds,
  Heart,
  Clubs,
  Spades
};

enum value {
  Two,
  Three,
  Four,
  Five,
  Six,
  Seven,
  Eight,
  Nine,
  Ten,
  Jack,
  Queen,
  King,
  Ace
};

typedef struct {
  enum suit suit;
  enum value value;
} Card;

typedef struct {
  Card* cards;
  int index;
  int length;
} CardArray;

typedef struct {
  enum suit suit;
  int cards[13];
  enum suit joker_suit;
} SetGame;
#endif