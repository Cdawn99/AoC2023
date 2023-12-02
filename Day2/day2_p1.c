#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_LINE_LEN 256

typedef struct {
    int red;
    int blue;
    int green;
} ball_count_t;

enum colours {RED = 3, BLUE = 4, GREEN = 5};
const ball_count_t BAG = {.red = 12, .blue = 14, .green = 13};

bool game_is_valid(char *game);
int extract_count(char **game);
bool valid_draw(const ball_count_t *current_draw);

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s path/to/file\n", argv[0]);
        return 1;
    }

    FILE *data = fopen(argv[1], "r");
    if (!data) {
        perror("fopen");
        return 1;
    }

    char game[MAX_LINE_LEN];
    int id = 1;
    int id_sum = 0;
    while (fgets(game, MAX_LINE_LEN, data)) {
        char *current_game = game;
        while (*current_game != ':') {
            current_game++;
        }
        if (game_is_valid(current_game)) {
            printf("Game %d is valid\n", id);
            id_sum += id;
        }
        id++;
    }

    printf("Sum of IDs: %d\n", id_sum);

    return 0;
}

bool game_is_valid(char *game) {
    while (*game != '\0') {
        game++;
        ball_count_t current_draw = {0};
        while (*game != ';' && *game != '\n' && *game != '\0') {
            int count = extract_count(&game);
            switch (*game) {
            case 'r':
                current_draw.red += count;
                game += RED;
                break;
            case 'b':
                current_draw.blue += count;
                game += BLUE;
                break;
            case 'g':
                current_draw.green += count;
                game += GREEN;
                break;
            }
        }
        printf("r: %d, g: %d, b: %d; ", current_draw.red, current_draw.green, current_draw.blue);
        if (!valid_draw(&current_draw)) {
            printf("\n");
            return false;
        }
    }
    printf("\n");
    return true;
}

int extract_count(char **game) {
    while (!isdigit(**game)) {
        (*game)++;
    }
    int count = 0;
    while (isdigit(**game)) {
        count *= 10;
        count += **game - '0';
        (*game)++;
    }
    (*game)++;
    return count;
}

bool valid_draw(const ball_count_t *current_draw) {
    return current_draw->red <= BAG.red && current_draw->green <= BAG.green && current_draw->blue <= BAG.blue;
}

