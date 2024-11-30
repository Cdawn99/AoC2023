#define DAWN_IMPLEMENTATION
#include "../dawn_utils.h"

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    size_t length;
    size_t capacity;
    char **items;
} Lines;

bool is_adjacent_to_symbol(Lines lines, size_t line_len, size_t i, size_t j) {
    bool is_adjacent = false;
    for (int k = -1; k <= 1; k++) {
        for (int l = -1; l <= 1; l++) {
            if (k == 0 && l == 0) continue;
            int idx1 = (int)i + k;
            int idx2 = (int)j + l;
            if (idx1 < 0 || idx2 < 0 || (size_t)idx1 >= lines.length || (size_t)idx2 >= line_len) continue;
            is_adjacent = is_adjacent || (!isdigit(lines.items[idx1][idx2]) && lines.items[idx1][idx2] != '.');
        }
    }
    return is_adjacent;
}

size_t sum_part_numbers(Lines lines, size_t line_len) {
    size_t sum = 0;
    for (size_t i = 0; i < lines.length; i++) {
        for (size_t j = 0; j < line_len; j++) {
            if (!isdigit(lines.items[i][j])) continue;

            size_t num = 0;
            bool is_part_num = false;
            while (isdigit(lines.items[i][j])) {
                is_part_num = is_part_num || is_adjacent_to_symbol(lines, line_len, i, j);
                num *= 10;
                num += lines.items[i][j] - '0';
                j++;
            }

            if (is_part_num) sum += num;
        }
    }
    return sum;
}

int main(int argc, char **argv) {
    char *program = dawn_shift_args(&argc, &argv);
    if (argc == 0) {
        printf("Usage: %s <schematic>\n", program);
        return 0;
    }

    char *fp = dawn_shift_args(&argc, &argv);

    DawnStringBuilder schematic = {0};
    if (!dawn_read_entire_file(fp, &schematic)) {
        return 1;
    }
    DAWN_SB_APPEND_BUF(&schematic, "", 1);

    Lines lines = {0};

    char delim[] = "\n";
    char *line = strtok(schematic.items, delim);
    do {
        DAWN_DA_APPEND(&lines, line);
        line = strtok(NULL, delim);
    } while (line);

    size_t line_len = strlen(lines.items[0]);

    size_t sum = sum_part_numbers(lines, line_len);

    printf("Sum of part numbers: %zu\n", sum);

    DAWN_SB_FREE(schematic);
    DAWN_SB_FREE(lines);

    return 0;
}
