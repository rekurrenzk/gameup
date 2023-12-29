#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define MAP_SIZE 5
#define NUM_WISHES 3
#define NUM_WALLS 3

char map[MAP_SIZE][MAP_SIZE];
int playerRow, playerCol;

void initializeMap() {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            map[i][j] = ' ';
        }
    }
}

void placeWishes() {
    int count = 0;
    while (count < NUM_WISHES) {
        int row = rand() % MAP_SIZE;
        int col = rand() % MAP_SIZE;
        if (map[row][col] == ' ') {
            map[row][col] = '*';
            count++;
        }
    }
}

void placeWalls() {
    int count = 0;
    while (count < NUM_WALLS) {
        int row = rand() % MAP_SIZE;
        int col = rand() % MAP_SIZE;
        if (map[row][col] == ' ') {
            map[row][col] = 'X';
            count++;
        }
    }
}

void printMap() {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (i == playerRow && j == playerCol) {
                printf("@ ");
            } else {
                printf("%c ", map[i][j]);
            }
        }
        printf("\n");
    }
}

void getPlayerInput() {
    printf("Enter your move (w/a/s/d): ");
    char move;
    scanf(" %c", &move);

    int newRow = playerRow;
    int newCol = playerCol;

    switch (move) {
        case 'w':
            newRow--;
            break;
        case 'a':
            newCol--;
            break;
        case 's':
            newRow++;
            break;
        case 'd':
            newCol++;
            break;
        default:
            printf("Invalid move!\n");
            return;
    }

    if (newRow >= 0 && newRow < MAP_SIZE && newCol >= 0 && newCol < MAP_SIZE && map[newRow][newCol] != 'X') {
        playerRow = newRow;
        playerCol = newCol;
    } else {
        printf("Invalid move!\n");
    }
}

void checkWish() {
    if (map[playerRow][playerCol] == '*') {
        map[playerRow][playerCol] = ' ';
        printf("You found a wish! Solve this riddle to make your wish: What comes once in a minute, twice in a moment, but never in a thousand years? (Answer with a single letter)\n");
        char answer;
        scanf(" %c", &answer);
        if (answer == 'm' || answer == 'M') {
            printf("Correct! Your wish is granted.\n");
        } else {
            printf("Incorrect. Better luck next time.\n");
        }
    }
}

void playGame() {
    initializeMap();
    placeWishes();
    placeWalls();
    playerRow = 0;
    playerCol = 0;

    while (true) {
        printMap();
        getPlayerInput();
        checkWish();
    }
}

int main() {
    srand(time(NULL));
    printf("Welcome to the Wish Finder Game!\nNavigate to the stars and make your wishes come true.\n");

    playGame();

    return 0;
}
