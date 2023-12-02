#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))

#define MAX_LINE_LEN 256

typedef struct {
    int red;
    int blue;
    int green;
} ball_count_t;

enum colours {RED = 3, BLUE = 4, GREEN = 5};
const ball_count_t BAG = {.red = 12, .blue = 14, .green = 13};

int get_power(char *game);
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
    int power_sum = 0;
    while (fgets(game, MAX_LINE_LEN, data)) {
        char *current_game = game;
        while (*current_game != ':') {
            current_game++;
        }
        power_sum += get_power(current_game);
    }

    printf("Sum of powers: %d\n", power_sum);

    return 0;
}

int get_power(char *game) {
    ball_count_t min_bag = {0};
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
        min_bag.red = MAX(min_bag.red, current_draw.red);
        min_bag.green = MAX(min_bag.green, current_draw.green);
        min_bag.blue = MAX(min_bag.blue, current_draw.blue);
    }
    return min_bag.red * min_bag.green * min_bag.blue;
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

