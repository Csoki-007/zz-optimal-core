#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


int get_0_Index() {
    return 0;
}

int get_2_Index(int a, int b) {
    return a * (2 * 12 - a - 1) / 2 + (b - a - 1);
}

int get_4_Index(int a, int b, int c, int d) {
    return
        495
        - ((12 - a) * (11 - a) * (10 - a) * ( 9 - a) / 24)  // - C(12-a,4)
        + ((11 - a) * (10 - a) * ( 9 - a)           /  6)  // + C(11-a,3)
        - ((12 - b) * (11 - b) * (10 - b)           /  6)  // - C(12-b,3)
        + ((11 - b) * (10 - b)                     /  2)  // + C(11-b,2)
        - ((12 - c) * (11 - c)                     /  2)  // - C(12-c,2)
        + (d - c - 1);                                   // + C(d-c-1,1)
}

int get_6_Index(int a, int b, int c, int d, int e, int f) {
    return
        924
      - ((12 - a) * (11 - a) * (10 - a) * ( 9 - a) * ( 8 - a) * ( 7 - a) / 720)  // - C(12-a,6)
      + ((11 - a) * (10 - a) * ( 9 - a) * ( 8 - a) * ( 7 - a)           / 120)  // + C(11-a,5)
      - ((12 - b) * (11 - b) * (10 - b) * ( 9 - b) * ( 8 - b)           / 120)  // - C(12-b,5)
      + ((11 - b) * (10 - b) * ( 9 - b) * ( 8 - b)                      /  24)  // + C(11-b,4)
      - ((12 - c) * (11 - c) * (10 - c) * ( 9 - c)                      /  24)  // - C(12-c,4)
      + ((11 - c) * (10 - c) * ( 9 - c)                                 /   6)  // + C(11-c,3)
      - ((12 - d) * (11 - d) * (10 - d)                                 /   6)  // - C(12-d,3)
      + ((11 - d) * (10 - d)                                            /   2)  // + C(11-d,2)
      - ((12 - e) * (11 - e)                                            /   2)  // - C(12-e,2)
      +  (11 - e)                                                         // + C(11-e,1)
      -  (12 - f)                                                         // - C(12-f,1)
    ;
}

int get_8_Index(int a, int b, int c, int d, int e, int f, int g, int h) {
    uint16_t mask = (1u<<a)|(1u<<b)|(1u<<c)|(1u<<d)|(1u<<e)|(1u<<f)|(1u<<g)|(1u<<h);
    uint16_t rem = (~mask) & 0x0FFF;
    int m0 = __builtin_ctz(rem);        rem &= rem - 1;
    int m1 = __builtin_ctz(rem);        rem &= rem - 1;
    int m2 = __builtin_ctz(rem);        rem &= rem - 1;
    int m3 = __builtin_ctz(rem);
    return 494 - get_4_Index(m0, m1, m2, m3);
}

int get_10_Index(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j) {
    uint16_t mask = (1u<<a)|(1u<<b)|(1u<<c)|(1u<<d)|(1u<<e)|(1u<<f)|(1u<<g)|(1u<<h)|(1u<<i)|(1u<<j);
    uint16_t rem = (~mask) & 0x0FFF;
    int v = __builtin_ctz(rem);
    int u = __builtin_ctz(rem & (rem - 1));
    return 65 - get_2_Index(v, u);
}

int get_12_Index(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k, int l) {
    (void)a; (void)b; (void)c; (void)d;
    (void)e; (void)f; (void)g; (void)h;
    (void)i; (void)j; (void)k; (void)l;
    return 0;
}




int process_line(const char *function, int *args, int count) {
    int result = -1;
    if (strcmp(function, "get_2_Index") == 0 && count == 2) {
        result = get_2_Index(args[0], args[1]);
    } else if (strcmp(function, "get_4_Index") == 0 && count == 4) {
        result = get_4_Index(args[0], args[1], args[2], args[3]);
    } else if (strcmp(function, "get_6_Index") == 0 && count == 6) {
        result = get_6_Index(args[0], args[1], args[2], args[3], args[4], args[5]);
    } else if (strcmp(function, "get_8_Index") == 0 && count == 8) {
        result = get_8_Index(args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7]);
    } else if (strcmp(function, "get_10_Index") == 0 && count == 10) {
        result = get_10_Index(args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8], args[9]);
    } else if (strcmp(function, "get_12_Index") == 0 && count == 12) {
        result = get_12_Index(args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8], args[9], args[10], args[11]);
    } else {
        fprintf(stderr, "Hiba: Érvénytelen függvény vagy argumentumszám.\n");
        return -1;
    }
    printf("%d\n", result);
    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Használat: %s <függvény> <fájlnév>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[2], "r");
    if (!file) {
        perror("Fájl megnyitása sikertelen");
        return 1;
    }

    char line[256];
    int previous_result = -1;
    int line_number = 0;

    while (fgets(line, sizeof(line), file)) {
        line_number++;
        // Sor tisztítása
        char *start = line;
        while (*start == ' ' || *start == '\t') start++;
        char *end = start + strlen(start) - 1;
        while (end >= start && (*end == '\n' || *end == '\r' || *end == ' ')) end--;
        *(end + 1) = '\0';

        // Számok kinyerése
        int args[12], count = 0;
        char *token = strtok(start, " ");
        while (token && count < 12) {
            args[count++] = atoi(token);
            token = strtok(NULL, " ");
        }

        // Függvény hívása és eredmény ellenőrzése
        int current_result = process_line(argv[1], args, count);
        if (current_result == -1) continue;  // Hibás sor kihagyása

        // Értékek összehasonlítása
        if (previous_result != -1 && current_result != previous_result + 1) {
            fprintf(stderr, 
                "HIBA %d. sorban: Az érték nem 1-gyel nagyobb az előzőnél!\n"
                "  Előző érték: %d\n"
                "  Jelenlegi érték: %d\n",
                line_number, previous_result, current_result
            );
        }
        previous_result = current_result;
    }

    fclose(file);
    return 0;
}

// Command to run after compiling:
// EO_Tester.exe get_6_Index 6.txt