#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 15

const char HORZ = 196;
const char VERT = 179;
const char TL = 218;
const char TM = 194;
const char TR = 191;
const char BL = 192;
const char BM = 193;
const char BR = 217;
const int numW = 3;   // Width for writing out an integer
const int charW = 1;  // Width for writing out a character
const int numPerLine = 15;
const char VERT_START = 195;
const char VERT_END = 180;
const char VERT_MID = 197;
const char* inputCommand = "Previous move/Next move/Stop [p/n/s]: ";
const char* endOfHistory =
"This is the end of the match.\nPrevious move/Next move/Stop [p/n/s]: ";
const char* startOfGame =
"This is the start of the match.\nPrevious move/Next move/Stop [p/n/s]: ";
const char* invalidInput = "Illegal input, please try again: ";

enum Stone { NA, X, O };

struct Move {
  int row;
  int col;
  enum Stone stone;
};

static char* lineString(char left, char mid, char right, char horz, int wcell,
  int ncell) {
  static char result[100];
  strcpy(result, "");
  char cell[10];
  for (int i = 0; i < wcell; i++) {
    cell[i] = horz;
  }
  cell[wcell] = '\0';
  strncat(result, &left, 1);
  char cellMid[20];
  strcpy(cellMid, cell);
  strncat(cellMid, &mid, 1);
  for (int i = 0; i < ncell - 1; i++) strcat(result, cellMid);
  char cellRight[20];
  strcpy(cellRight, cell);
  strncat(cellRight, &right, 1);
  strcat(result, cellRight);
  return result;
}

void displayBoard(enum Stone arr[][15], int size) {
  // UPPERLINE
  printf("   ");
  for (int i = 0; i < size; i++) {
    printf("  %c ", (char)(i + 'a'));
  }
  printf("\n");
  printf("   %s\n", lineString(TL, TM, TR, HORZ, 3, numPerLine));

  // MIDDLE
  for (int i = 0; i < size; i++) {
    printf("%2d %c", size - i, VERT);
    for (int j = 0; j < size; j++) {
      if (arr[i][j] == NA) printf("   %c", VERT);
      if (arr[i][j] == X) printf(" X %c", VERT);
      if (arr[i][j] == O) printf(" O %c", VERT);
    }
    printf("\n");
    if (i != size - 1)
      printf("   %s\n",
        lineString(VERT_START, VERT_MID, VERT_END, HORZ, 3, numPerLine));
  }

  // UNDERLINE
  printf("   %s\n", lineString(BL, BM, BR, HORZ, 3, numPerLine));
}

void displayBoardSimple(enum Stone arr[][15], int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      printf("%d", arr[i][j]);
    }
  }
  printf("\n");
}
// 95226g 93044a 94997l 56046a 13n 10n 12n 8e 7k
// 11l 8j 10m 9i 6l 10l 11m 12l 12k 9n 11k 11j 12m
// 13m 10k 9k 11n 11o 14k 13k 13l 15j 10o ff

bool makeMove(enum Stone board[][15], int size, char* playerMove,
  bool isFirstPlayerTurn) {
  // BEGIN TODO
  int x_index = 0;
  char y_index;
  int col, row;

  int length = strlen(playerMove);
  if (length > 3 || length < 2) return false;

  int index = 0;

  while ((playerMove[index] >= '0') && (playerMove[index] <= '9')) {
    int now_char = playerMove[index];
    now_char -= '0';
    index += 1;
    x_index = x_index * 10 + now_char;
  };

  if (x_index > 15 || x_index < 1) return false;

  row = abs(x_index - 15);
  // printf("row: %d\n", row);

  if (length == 2)
    y_index = playerMove[1];
  else if (length == 3)
    y_index = playerMove[2];
  if (y_index > 'o' || y_index < 'a') return false;

  if (y_index >= 'a' && y_index <= 'o') {
    col = (int)y_index - 'a';
    // printf("col: %d\n", col);
  };
  // isFirstPlayerTurn = true;
  if (board[row][col] != NA) return false;
  if (isFirstPlayerTurn) {
    board[row][col] = X;
    return true;
  }
  else {
    board[row][col] = O;
    return true;
  }

  // END TODO
}

bool hasWon(enum Stone board[][15], int size, bool isFirstPlayerTurn) {
  // BEGIN TODO
  int so_X = 0, so_O = 0;
  // Kiemtradong
  for (int i = 0; i < size; i++) {
    // int so_X = 0, so_O = 0;
    for (int j = 0; j < size; j++) {
      if (board[i][j] == X)
        so_X++;
      else {
        if (board[i][j] == NA) {
          if (so_X == 5)
            return so_X = 5;
          else
            so_X = 0;
        }
        if (board[i][j] == O) {
          if (so_X == 5 && board[i][j - so_X - 1] != O)
            return so_X = 5;
          else
            so_X = 0;
        }
      }
      if (board[i][j] == O)
        so_O++;
      else {
        if (board[i][j] == NA) {
          if (so_O == 5)
            return so_O = 5;
          else
            so_O = 0;
        }
        if (board[i][j] == X) {
          if (so_O == 5 && board[i][j - so_O - 1] != X)
            return so_O = 5;
          else
            so_O = 0;
        }
      }
    }
    if (so_O == 5 || so_X == 5) return true;
  }

  ///
  // kt cot
  for (int j = 0; j < size; j++) {
    // int so_X = 0, so_O = 0;
    for (int i = 0; i < size; i++) {
      if (board[i][j] == X)
        so_X++;
      else {
        if (board[i][j] == NA) {
          if (so_X == 5)
            return so_X = 5;
          else
            so_X = 0;
        }
        if (board[i][j] == O) {
          if (so_X == 5 && board[i - so_X - 1][j] != O)
            return so_X = 5;
          else
            so_X = 0;
        }
      }
      if (board[i][j] == O)
        so_O++;
      else {
        if (board[i][j] == NA) {
          if (so_O == 5)
            return so_O = 5;
          else
            so_O = 0;
        }
        if (board[i][j] == X) {
          if (so_O == 5 && board[i - so_O - 1][j] != X)
            return so_O = 5;
          else
            so_O = 0;
        }
      }
    }
    if (so_O == 5 || so_X == 5) return true;
  }
  ///
  // kt chinh
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (i == j) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X &&
          board[i + 6][j + 6] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O &&
          board[i + 6][j + 6] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }
      // kt phu
      if (i + j == size - 1) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X &&
          board[i + 6][j + 6] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O &&
          board[i + 6][j + 6] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }
      // tren cheo chinh
      if (j - i == 1) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X &&
          board[i + 6][j + 6] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O &&
          board[i + 6][j + 6] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }

      if (j - i == 2) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X &&
          board[i + 6][j + 6] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O &&
          board[i + 6][j + 6] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }

      if (j - i == 3) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X &&
          board[i + 6][j + 6] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O &&
          board[i + 6][j + 6] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }

      if (j - i == 4) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X &&
          board[i + 6][j + 6] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O &&
          board[i + 6][j + 6] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }

      if (j - i == 5) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X &&
          board[i + 6][j + 6] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O &&
          board[i + 6][j + 6] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }

      if (j - i == 6) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X &&
          board[i + 6][j + 6] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O &&
          board[i + 6][j + 6] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }

      if (j - i == 7) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X &&
          board[i + 6][j + 6] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O &&
          board[i + 6][j + 6] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }

      if (j - i == 8) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X &&
          board[i + 6][j + 6] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O &&
          board[i + 6][j + 6] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }

      if (j - i == 9) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }
      if (j - i == 10) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }
      // duoi cheo chinh
      if (i - j == 1) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X &&
          board[i + 6][j + 6] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O &&
          board[i + 6][j + 6] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }
      if (i - j == 2) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X &&
          board[i + 6][j + 6] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O &&
          board[i + 6][j + 6] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }
      if (i - j == 3) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X &&
          board[i + 6][j + 6] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O &&
          board[i + 6][j + 6] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }
      if (i - j == 4) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X &&
          board[i + 6][j + 6] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O &&
          board[i + 6][j + 6] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }
      if (i - j == 5) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X &&
          board[i + 6][j + 6] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O &&
          board[i + 6][j + 6] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }
      if (i - j == 6) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X &&
          board[i + 6][j + 6] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O &&
          board[i + 6][j + 6] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }
      if (i - j == 7) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X &&
          board[i + 6][j + 6] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O &&
          board[i + 6][j + 6] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }
      if (i - j == 8) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X &&
          board[i + 6][j + 6] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O &&
          board[i + 6][j + 6] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }
      if (i - j == 9) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }
      if (i - j == 10) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }
      // tren cheo phu
      if (i + j == 13) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X &&
          board[i + 6][j + 6] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O &&
          board[i + 6][j + 6] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }

      if (i + j == 12) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X &&
          board[i + 6][j + 6] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O &&
          board[i + 6][j + 6] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }
      if (i + j == 11) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X &&
          board[i + 6][j + 6] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O &&
          board[i + 6][j + 6] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }
      if (i + j == 10) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X &&
          board[i + 6][j + 6] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O &&
          board[i + 6][j + 6] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }
      if (i + j == 9) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X &&
          board[i + 6][j + 6] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O &&
          board[i + 6][j + 6] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }
      if (i + j == 8) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X &&
          board[i + 6][j + 6] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O &&
          board[i + 6][j + 6] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }
      if (i + j == 7) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X &&
          board[i + 6][j + 6] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O &&
          board[i + 6][j + 6] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }
      if (i + j == 6) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X &&
          board[i + 6][j + 6] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O &&
          board[i + 6][j + 6] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }
      if (i + j == 5) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }
      if (i + j == 4) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }
      // duoi cheo phu
      if (i + j == 15) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X &&
          board[i + 6][j + 6] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O &&
          board[i + 6][j + 6] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }

      if (i + j == 16) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X &&
          board[i + 6][j + 6] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O &&
          board[i + 6][j + 6] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }
      if (i + j == 17) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X &&
          board[i + 6][j + 6] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O &&
          board[i + 6][j + 6] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }
      if (i + j == 18) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X &&
          board[i + 6][j + 6] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O &&
          board[i + 6][j + 6] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }
      if (i + j == 19) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X &&
          board[i + 6][j + 6] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O &&
          board[i + 6][j + 6] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }
      if (i + j == 20) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X &&
          board[i + 6][j + 6] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O &&
          board[i + 6][j + 6] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }
      if (i + j == 21) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X &&
          board[i + 6][j + 6] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O &&
          board[i + 6][j + 6] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }
      if (i + j == 22) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X &&
          board[i + 6][j + 6] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O &&
          board[i + 6][j + 6] == X)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }
      if (i + j == 23) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X && board[i + 5][j + 5] == X)
          return false;
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O && board[i + 5][j + 5] == O)
          return false;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }
      if (i + j == 24) {
        if (board[i][j] == X && board[i + 1][j + 1] == X &&
          board[i + 2][j + 2] == X && board[i + 3][j + 3] == X &&
          board[i + 4][j + 4] == X)
          return true;
        if (board[i][j] == O && board[i + 1][j + 1] == O &&
          board[i + 2][j + 2] == O && board[i + 3][j + 3] == O &&
          board[i + 4][j + 4] == O)
          return true;
      }
    }
  }

  // END TODO
  return false;
}

// 2
// 27
// 13m10m12m8d7j9d12l12k11l10d7d10k11k10j10l13l9m12j8l9l10n11o11m13k11j11i11n
// n n n n n p n p p p n n n p n p n p n n p n p n n n n n n n n n p n p n n n n
// n p n n n n n n
//  n n n n p n p n n p n n n n n n n p p n n n n n p p n n n n n n n n p n p n
//  n p p p n n p n n p p n p p p s

void displayHistory(char* history, int numOfMoves) {
  // BEGIN TODO
  enum Stone game[15][15];
  char option;
  for (int i = 0; i < MAX_SIZE; i++) {
    for (int j = 0; j < MAX_SIZE; j++) {
      game[i][j] = NA;
    }
  }
  displayBoard(game, MAX_SIZE);

  int prevCol = 0, prevRow = 0;
  int head = 0, tail = 0;
  char playerMove[4];
  bool isFirstPlayerTurn = true;
  int count = 0;
  int prevHead, prevTail;
  int prevCount = 0;
  int row, col;
  //[][0] = row; [][1] = col
  int historyNums[255][2];

  for (int i = 0; i < numOfMoves; i++) {
    head = tail;
    while (!(history[tail] >= 'a' && history[tail] <= 'o')) tail++;
    strncpy(playerMove, history + head, tail + 1 - head);
    playerMove[tail + 1 - head] = '\0';
    prevHead = head;
    prevTail = ++tail;
    char tempRow[3];
    char tempCol[2];

    strncpy(tempRow, playerMove, strlen(playerMove) - 1);
    tempRow[strlen(playerMove) - 1] = '\0';
    strncpy(tempCol, playerMove + strlen(playerMove) - 1, 1);
    tempCol[1] = '\0';

    prevCol = tempCol[0] - 97;
    prevRow = abs(atoi(tempRow) - 15);

    historyNums[i][0] = prevRow;
    historyNums[i][1] = prevCol;
  }

  while (true) {
    printf("Previous move/Next move/Stop [p/n/s]: ");
    while (getchar() != '\n')
      ;
    scanf("%c", &option);

    if (option == 'p') {
      if (count == 0)
        printf("This is the start of the match.\n");
      else {
        row = historyNums[count - 1][0];
        col = historyNums[count - 1][1];
        game[row][col] = NA;
        count--;
        displayBoard(game, MAX_SIZE);
        isFirstPlayerTurn = !isFirstPlayerTurn;
      }
    }
    else if (option == 'n') {
      if (count == numOfMoves)
        printf("This is the end of the match.\n");
      else {
        row = historyNums[count][0];
        col = historyNums[count][1];
        game[row][col] = isFirstPlayerTurn ? X : O;
        count++;
        displayBoard(game, MAX_SIZE);
        isFirstPlayerTurn = !isFirstPlayerTurn;
      }
    }
    else
      return;
  }

  // END TODO
}

void startGame() {
  enum Stone game[15][15];
  for (int i = 0; i < MAX_SIZE; i++) {
    for (int j = 0; j < MAX_SIZE; j++) {
      game[i][j] = NA;
    }
  }
  displayBoard(game, MAX_SIZE);
  char playerMove[50];
  bool player1Turn = true;
  printf("Player 1 turn: ");
  while (true) {
    scanf("%s", playerMove);
    if (strcmp(playerMove, "ff") == 0) {
      printf("%s", ((player1Turn) ? "Player 2 won " : "Player 1 won "));
      break;
    }
    else if (makeMove(game, MAX_SIZE, playerMove, player1Turn)) {
      if (hasWon(game, MAX_SIZE, player1Turn)) {
        displayBoard(game, MAX_SIZE);
        printf("%s", ((player1Turn) ? "Player 1 won " : "Player 2 won "));
        return;
      }
      player1Turn = !player1Turn;
      displayBoard(game, MAX_SIZE);
      printf("%s", ((player1Turn) ? "Player 1 turn: " : "Player 2 turn: "));
    }
    else {
      printf("Illegal move, please try again: ");
    }
  }
}

int main() {
  printf("Welcome to Gomoku!\n");
  printf("1. Play game\n");
  printf("2. History\n");
  printf("3. Exit\n");
  printf("Please select mode [1/2/3]: ");
  int mode;
  while (true) {
    scanf("%d", &mode);
    if (mode == 1) {
      startGame();
      return 0;
    }
    else if (mode == 2) {
      int numOfMoves;
      printf("Please enter number of moves: ");
      scanf("%d", &numOfMoves);
      char history[700];
      printf("Please enter history: ");
      scanf("%s", history);
      displayHistory(history, numOfMoves);
      return 0;
    }
    else if (mode == 3) {
      return 0;
    }
    else {
      int c;
      while ((c = getchar()) != '\n' && c != EOF)
        ;
      printf("Invalid mode, please try again: ");
    }
  }

  return 0;
}
