#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 30
#define HEIGHT 30
#define NUM_MONSTERS 5

typedef struct {
    int x;
    int y;
} Monster;

char map[HEIGHT][WIDTH];
int playerX = 1;
int playerY = 1;
int score = 0;
Monster monsters[NUM_MONSTERS];

void initializeMap() {
    srand(time(NULL));

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == 0 || x == WIDTH - 1) map[y][x] = '|';
            else if (y == 0 || y == HEIGHT - 1) map[y][x] = '_';
            else map[y][x] = ' ';
        }
    }

    for (int i = 0; i < 10; i++) {
        int randX = rand() % (WIDTH - 2) + 1;
        int randY = rand() % (HEIGHT - 2) + 1;
        map[randY][randX] = (i < 5) ? '#' : '*';
    }

    map[playerY][playerX] = '0';

    for (int i = 0; i < NUM_MONSTERS; i++) {
        monsters[i].x = rand() % (WIDTH - 2) + 1;
        monsters[i].y = rand() % (HEIGHT - 2) + 1;
        map[monsters[i].y][monsters[i].x] = 'M';
    }
}

void printMap() {
    system("clear");
    for (int i = 0; i < (10 - HEIGHT / 2); i++) printf("\n"); // Centering
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%c", map[y][x]);
        }
        printf("\n");
    }
    printf("Score: %d\n", score);
}

void movePlayer(int dx, int dy) {
    int newX = playerX + dx;
    int newY = playerY + dy;

    if (map[newY][newX] == ' ' || map[newY][newX] == '*') {
        if (map[newY][newX] == '*') score++;
        map[playerY][playerX] = ' ';
        playerY = newY;
        playerX = newX;
        map[playerY][playerX] = '0';
    }
}

void destroyObstacle() {
    int dx[4] = {0, -1, 0, 1};
    int dy[4] = {-1, 0, 1, 0};

    for (int i = 0; i < 4; i++) {
        int newX = playerX + dx[i];
        int newY = playerY + dy[i];
        if (map[newY][newX] == '#') {
            map[newY][newX] = ' ';
            break;
        }
    }
}

void moveMonsters() {
    for (int i = 0; i < NUM_MONSTERS; i++) {
        map[monsters[i].y][monsters[i].x] = ' ';

        int dx = (rand() % 3) - 1; // -1, 0, or 1
        int dy = (rand() % 3) - 1; // -1, 0, or 1

        int newX = monsters[i].x + dx;
        int newY = monsters[i].y + dy;

        if (newX > 0 && newX < WIDTH - 1 && newY > 0 && newY < HEIGHT - 1 && map[newY][newX] == ' ') {
            monsters[i].x = newX;
            monsters[i].y = newY;
        }

        map[monsters[i].y][monsters[i].x] = 'M';
    }
}

int main() {
    initializeMap();
    char input;
    do {
        printMap();
        scanf(" %c", &input);
        switch (input) {
            case 'w': movePlayer(0, -1); break;
            case 'a': movePlayer(-1, 0); break;
            case 's': movePlayer(0, 1); break;
            case 'd': movePlayer(1, 0); break;
            case 'k': destroyObstacle(); break;
        }
        moveMonsters();
    } while (input != 'q');
    return 0;
}
