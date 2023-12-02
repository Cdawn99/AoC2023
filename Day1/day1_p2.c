#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LEN 256

#define MAX_NAME_LEN 6
const char digit_names[][MAX_NAME_LEN] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int read_calibration_val(const char* line);

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s path-to-file\n", argv[0]);
        return 1;
    }

    FILE *data = fopen(argv[1], "r");
    if (!data) {
        perror("fopen");
        return 1;
    }

    char line[MAX_LINE_LEN];
    // int count = 1;
    int sum = 0;
    while (fgets(line, MAX_LINE_LEN, data)) {
        int val = read_calibration_val(line);
        sum += val;
        // printf("Read %dth calibration value: %d\n", count++, val);
    }

    printf("sum of calibration values: %d\n", sum);

    if (fclose(data)) {
        perror("fclose");
        return 1;
    }

    return 0;
}

int read_calibration_val(const char* line) {
    int first = -1;
    int last = -1;
    while (*line != '\0') {
        if (isdigit(*line)) {
            int digit = *line - '0';
            if (first == -1) {
                first = digit;
            }
            last = digit;
            line++;
            continue;
        }
        int digit = -1;
        for (int i = 0; i < 9; i++) {
            size_t digit_len = strlen(digit_names[i]);
            if (strncmp(line, digit_names[i], digit_len) == 0) {
                digit = i + 1;
                if (first == -1) {
                    first = digit;
                }
                last = digit;
                break;
            }
        }
        line++;
    }
    return first * 10 + last;
}

