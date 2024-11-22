#include "libmx.h"
char **mx_strsplit(const char *s, char c) {
    if (s == NULL)
        return NULL;

    // Count words, considering empty segments as separate entries
    int word_count = 0;
    int in_word = 0;
    for (const char *ptr = s; *ptr; ptr++) {
        if (*ptr == c) {
            if (in_word) {
                word_count++;
                in_word = 0;
            }
        } else {
            if (!in_word)
                in_word = 1;
        }
    }
    if (in_word)
        word_count++; // Add last word if present

    // Allocate memory for result array
    char **res = (char **)malloc((word_count + 1) * sizeof(char *));
    if (res == NULL)
        return NULL;

    int i = 0;
    const char *start = NULL;
    while (*s) {
        if (*s != c && !start) {
            start = s; // Mark start of a segment
        } else if (*s == c || *(s + 1) == '\0') {
            if (start) {
                // Allocate and copy non-empty segment
                int word_len = (s - start) + (*s != c);
                res[i] = (char *)malloc((word_len + 1) * sizeof(char));
                if (res[i] == NULL)
                    return NULL; // Handle allocation failure

                for (int j = 0; j < word_len; j++) {
                    res[i][j] = start[j];
                }
                res[i][word_len] = '\0';
                i++;
                start = NULL;
            } else {
                // Insert "0" for consecutive delimiters
                res[i] = (char *)malloc(2 * sizeof(char));
                if (res[i] == NULL)
                    return NULL;
                res[i][0] = '0';
                res[i][1] = '\0';
                i++;
            }
        }
        s++;
    }

    res[i] = NULL; // Null-terminate the result array
    return res;
}
