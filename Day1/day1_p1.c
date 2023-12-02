#include <ctype.h>
#include <stdio.h>

#define MAX_LINE_LEN 256

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
        if (!isdigit(*line)) {
            line++;
            continue;
        }
        if (first == -1) {
            first = *line - '0';
        }
        last = *line - '0';
        line++;
    }
    return first * 10 + last;
}

