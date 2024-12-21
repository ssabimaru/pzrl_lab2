#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "operations.h"

#define MAX_LINE_LENGTH 1024

void replace_text(const char *filename, const char *pattern, const char *replacement) {
    FILE *file = fopen(filename, "r+"), *temp;
    if (!file) {
        perror("Error opening file");
        return;
    }

    temp = tmpfile();
    if (!temp) {
        perror("Error creating temporary file");
        fclose(file);
        return;
    }

    regex_t regex;
    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        fprintf(stderr, "Error compiling regex\n");
        fclose(file);
        fclose(temp);
        return;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        char output[MAX_LINE_LENGTH] = "";
        regmatch_t match;
        char *cursor = line;

        while (!regexec(&regex, cursor, 1, &match, 0)) {
            strncat(output, cursor, match.rm_so);
            strcat(output, replacement);
            cursor += match.rm_eo;
        }

        strcat(output, cursor);
        fputs(output, temp);
    }

    fclose(file);
    rewind(temp);

    file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file for writing");
        fclose(temp);
        return;
    }

    while (fgets(line, sizeof(line), temp)) {
        fputs(line, file);
    }

    fclose(file);
    fclose(temp);
    regfree(&regex);
}

void delete_lines(const char *filename, const char *pattern) {
    FILE *file = fopen(filename, "r+"), *temp;
    if (!file) {
        perror("Error opening file");
        return;
    }

    temp = tmpfile();
    if (!temp) {
        perror("Error creating temporary file");
        fclose(file);
        return;
    }

    regex_t regex;
    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        fprintf(stderr, "Error compiling regex\n");
        fclose(file);
        fclose(temp);
        return;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        if (regexec(&regex, line, 0, NULL, 0)) {
            fputs(line, temp);
        }
    }

    fclose(file);
    rewind(temp);

    file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file for writing");
        fclose(temp);
        return;
    }

    while (fgets(line, sizeof(line), temp)) {
        fputs(line, file);
    }

    fclose(file);
    fclose(temp);
    regfree(&regex);
}

void insert_text(const char *filename, const char *text, int front) {
    FILE *file = fopen(filename, "r+"), *temp;
    if (!file) {
        perror("Error opening file");
        return;
    }

    temp = tmpfile();
    if (!temp) {
        perror("Error creating temporary file");
        fclose(file);
        return;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        if (front) {
            fprintf(temp, "%s%s", text, line);
        } else {
            line[strcspn(line, "\n")] = '\0';
            fprintf(temp, "%s%s\n", line, text);
        }
    }

    fclose(file);
    rewind(temp);

    file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file for writing");
        fclose(temp);
        return;
    }

    while (fgets(line, sizeof(line), temp)) {
        fputs(line, file);
    }

    fclose(file);
    fclose(temp);
}