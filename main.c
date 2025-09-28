#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* Prototypes from convert.c */
void oct_to_bin(const char *oct, char *out);
void oct_to_hex(const char *oct, char *out);
void hex_to_bin(const char *hex, char *out);
void to_sign_magnitude(int32_t n, char *out);
void to_ones_complement(int32_t n, char *out);
void to_twos_complement(int32_t n, char *out);

#define MAX_LINE 256
#define MAX_OUT 520

int main(void) {
    FILE *fp = fopen("a2_test.txt", "r");
    if (!fp) {
        perror("Error opening a2_test.txt");
        return 1;
    }

    FILE *out_fp = fopen("output.txt", "w");
    if (!out_fp) {
        perror("Error creating output.txt");
        fclose(fp);
        return 1;
    }

    char line[MAX_LINE];
    char func[50], input[100], expected[MAX_OUT];
    char actual[MAX_OUT];
    int test_num = 0, passed = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (line[0] == '#' || strlen(line) < 3)
            continue; // skip comments or blank lines

        if (sscanf(line, "%49s %99s %519s", func, input, expected) != 3)
            continue;

        actual[0] = '\0';

        if (strcmp(func, "oct_to_bin") == 0)
            oct_to_bin(input, actual);
        else if (strcmp(func, "oct_to_hex") == 0)
            oct_to_hex(input, actual);
        else if (strcmp(func, "hex_to_bin") == 0)
            hex_to_bin(input, actual);
        else if (strcmp(func, "to_sign_magnitude") == 0)
            to_sign_magnitude(atoi(input), actual);
        else if (strcmp(func, "to_ones_complement") == 0)
            to_ones_complement(atoi(input), actual);
        else if (strcmp(func, "to_twos_complement") == 0)
            to_twos_complement(atoi(input), actual);
        else
            strcpy(actual, "[Unknown function]");

        test_num++;
        int ok = strcmp(expected, actual) == 0;
        if (ok) passed++;

        fprintf(out_fp, "Test %d: %s(\"%s\") -> Expected: \"%s\", Got: \"%s\" [%s]\n",
                test_num, func, input, expected, actual, ok ? "PASS" : "FAIL");
    }

    fprintf(out_fp, "Summary: %d/%d tests passed\n", passed, test_num);

    fclose(fp);
    fclose(out_fp);

    printf("Tests completed. Check output.txt for results.\n");
    return 0;
}
