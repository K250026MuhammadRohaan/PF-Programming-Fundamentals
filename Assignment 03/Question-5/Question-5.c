#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define INITIAL_CAPACITY 8
#define READ_CHUNK 128

static char **lines = NULL;
static size_t lineCount = 0;
static size_t capacity = 0;

static void allocFail(const char *msg) {
    fprintf(stderr, "Memory allocation failed: %s (%s)\n", msg, strerror(errno));
    exit(EXIT_FAILURE);
}

static char *readLineFromStream(FILE *stream) {
    size_t cap = READ_CHUNK;
    size_t len = 0;
    char *buf = malloc(cap);
    if (!buf) allocFail("readLine buffer malloc");
    int c;
    while ((c = fgetc(stream)) != EOF) {
        if (c == '\r') continue;
        if (c == '\n') break;
        if (len + 1 >= cap) {
            cap *= 2;
            char *tmp = realloc(buf, cap);
            if (!tmp) { free(buf); allocFail("readLine buffer realloc"); }
            buf = tmp;
        }
        buf[len++] = (char)c;
    }
    if (len == 0 && c == EOF) {
        free(buf);
        return NULL;
    }
    buf[len] = '\0';

    char *final = realloc(buf, len + 1);
    if (!final) {
        final = buf;
    }
    return final;
}

static void ensureCapacity(size_t newCap) {
    if (capacity >= newCap) return;
    size_t target = capacity ? capacity : INITIAL_CAPACITY;
    while (target < newCap) target *= 2;
    char **tmp = realloc(lines, target * sizeof(char *));
    if (!tmp) allocFail("lines array realloc");
    lines = tmp;
    capacity = target;
}

int insertLine(size_t index, const char *text) {
    if (index > lineCount) return 0;
    ensureCapacity(lineCount + 1);
    if (index < lineCount) {
        memmove(&lines[index + 1], &lines[index], (lineCount - index) * sizeof(char *));
    }
    size_t len = strlen(text);
    char *copy = malloc(len + 1);
    if (!copy) allocFail("line copy malloc");
    memcpy(copy, text, len + 1);
    lines[index] = copy;
    lineCount++;
    return 1;
}

int deleteLine(size_t index) {
    if (index >= lineCount) return 0;
    free(lines[index]);
    if (index + 1 < lineCount) {
        memmove(&lines[index], &lines[index + 1], (lineCount - index - 1) * sizeof(char *));
    }
    lineCount--;
    return 1;
}

void printAllLines(void) {
    for (size_t i = 0; i < lineCount; ++i) {
        printf("%zu: %s\n", i + 1, lines[i]);
    }
    if (lineCount == 0) printf("[buffer empty]\n");
}

void freeAll(void) {
    if (lines) {
        for (size_t i = 0; i < lineCount; ++i) {
            free(lines[i]);
        }
        free(lines);
    }
    lines = NULL;
    lineCount = 0;
    capacity = 0;
}

int shrinkToFit(void) {
    if (lineCount == 0) {
        free(lines);
        lines = NULL;
        capacity = 0;
        return 1;
    }
    char **tmp = realloc(lines, lineCount * sizeof(char *));
    if (!tmp) return 0;
    lines = tmp;
    capacity = lineCount;
    return 1;
}

int saveToFile(const char *filename) {
    FILE *f = fopen(filename, "w");
    if (!f) {
        fprintf(stderr, "Failed to open file for writing: %s (%s)\n", filename, strerror(errno));
        return 0;
    }
    for (size_t i = 0; i < lineCount; ++i) {
        if (fprintf(f, "%s\n", lines[i]) < 0) {
            fprintf(stderr, "Write error to file: %s\n", filename);
            fclose(f);
            return 0;
        }
    }
    fclose(f);
    return 1;
}

int loadFromFile(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr, "Failed to open file for reading: %s (%s)\n", filename, strerror(errno));
        return 0;
    }
    freeAll();
    
    char *ln;
    while ((ln = readLineFromStream(f)) != NULL) {
        ensureCapacity(lineCount + 1);
        lines[lineCount++] = ln;
    }
    fclose(f);
    return 1;
}


static void printMenu(void) {
    puts("\nSimple Line Editor");
    puts("1) Insert line at index");
    puts("2) Delete line at index");
    puts("3) Print all lines");
    puts("4) Shrink-to-fit buffer");
    puts("5) Save to file");
    puts("6) Load from file (replaces buffer)");
    puts("7) Free all and exit");
    puts("8) Append line");
    printf("Enter choice: ");
}

static long promptIndex(const char *prompt) {
    printf("%s", prompt);
    fflush(stdout);
    char *line = readLineFromStream(stdin);
    if (!line) return -1;
    char *endptr = NULL;
    errno = 0;
    long idx = strtol(line, &endptr, 10);
    free(line);
    if (endptr == line || errno != 0) return -1;
    return idx;
}

int main(void) {
    for (;;) {
        printMenu();
        char *choiceLine = readLineFromStream(stdin);
        if (!choiceLine) break;
        int choice = (int)strtol(choiceLine, NULL, 10);
        free(choiceLine);
        if (choice == 1) {
            long idx = promptIndex("Insert at index (1..n+1): ");
            if (idx < 1 || (size_t)idx > lineCount + 1) {
                printf("Invalid index.\n");
                continue;
            }
            printf("Enter text: ");
            char *text = readLineFromStream(stdin);
            if (!text) text = strdup("");
            if (!insertLine((size_t)idx - 1, text)) {
                printf("Insert failed.\n");
                free(text);
            } else {
                free(text);
            }
        } else if (choice == 2) {
            long idx = promptIndex("Delete index (1..n): ");
            if (idx < 1 || (size_t)idx > lineCount) {
                printf("Invalid index.\n");
                continue;
            }
            if (!deleteLine((size_t)idx - 1)) printf("Delete failed.\n");
        } else if (choice == 3) {
            printAllLines();
        } else if (choice == 4) {
            if (shrinkToFit()) printf("Shrink-to-fit done. Capacity=%zu\n", capacity);
            else printf("Shrink-to-fit failed (not enough memory).\n");
        } else if (choice == 5) {
            printf("Filename to save: ");
            char *fname = readLineFromStream(stdin);
            if (!fname) { printf("No filename provided.\n"); continue; }
            if (saveToFile(fname)) printf("Saved to %s\n", fname);
            else printf("Save failed.\n");
            free(fname);
        } else if (choice == 6) {
            printf("Filename to load: ");
            char *fname = readLineFromStream(stdin);
            if (!fname) { printf("No filename provided.\n"); continue; }
            if (loadFromFile(fname)) printf("Loaded from %s\n", fname);
            else printf("Load failed or file not found.\n");
            free(fname);
        } else if (choice == 7) {
            freeAll();
            puts("Buffer freed. Exiting.");
            break;
        } else if (choice == 8) {
            printf("Enter text to append: ");
            char *text = readLineFromStream(stdin);
            if (!text) text = strdup("");
            if (!insertLine(lineCount, text)) {
                printf("Append failed.\n");
                free(text);
            } else {
                free(text);
            }
        } else {
            printf("Unknown choice.\n");
        }
    }
    freeAll();
    return 0;
}
