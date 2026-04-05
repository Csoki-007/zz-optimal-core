#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Now only testing this single function
int get_Line_Index(int a, int b) {
    static const int indexMap[12][12] = {
        // a=0
        {0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        // a=1
        {11, 0, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21},
        // a=2
        {22, 23, 0, 24, 25, 26, 27, 28, 29, 30, 31, 32},
        // a=3
        {33, 34, 35, 0, 36, 37, 38, 39, 40, 41, 42, 43},
        // a=4
        {44, 45, 46, 47, 0, 48, 49, 50, 51, 52, 53, 54},
        // a=5
        {55, 56, 57, 58, 59, 0, 60, 61, 62, 63, 64, 65},
        // a=6
        {66, 67, 68, 69, 70, 71, 0, 72, 73, 74, 75, 76},
        // a=7
        {77, 78, 79, 80, 81, 82, 83, 0, 84, 85, 86, 87},
        // a=8
        {88, 89, 90, 91, 92, 93, 94, 95, 0, 96, 0, 97},
        // a=9
        {98, 99, 100, 101, 102, 103, 104, 105, 106, 0, 107, 108},
        // a=10
        {109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 0, 119},
        // a=11
        {120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 0}
    };
    return indexMap[a][b];
}

int process_line(int *args, int count) {
    if (count != 2) {
        fprintf(stderr, "Hiba: Várható 2 argumentum, de %d érkezett.\n", count);
        return -1;
    }
    return get_Line_Index(args[0], args[1]);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Használat: %s <fájlnév>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Fájl megnyitása sikertelen");
        return 1;
    }

    char line[256];
    int previous_result = -1;
    int line_number = 0;

    while (fgets(line, sizeof(line), file)) {
        line_number++;
        // Trim leading/trailing whitespace
        char *start = line;
        while (*start == ' ' || *start == '\t') start++;
        char *end = start + strlen(start) - 1;
        while (end >= start && (*end == '\n' || *end == '\r' || *end == ' ')) end--;
        *(end + 1) = '\0';

        // Parse up to 2 numbers
        int args[2];
        int count = 0;
        char *token = strtok(start, " ");
        while (token && count < 2) {
            args[count++] = atoi(token);
            token = strtok(NULL, " ");
        }

        int current = process_line(args, count);
        if (current == -1) continue;

        printf("%d\n", current);

        if (previous_result != -1 && current != previous_result + 1) {
            fprintf(stderr,
                "HIBA %d. sorban: Az érték nem 1-gyel nagyobb az előzőnél!\n"
                "  Előző érték: %d\n"
                "  Jelenlegi érték: %d\n",
                line_number, previous_result, current
            );
        }
        previous_result = current;
    }

    fclose(file);
    return 0;
}
