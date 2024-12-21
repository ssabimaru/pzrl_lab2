#ifndef OPERATIONS_H
#define OPERATIONS_H

void replace_text(const char *filename, const char *pattern, const char *replacement);
void delete_lines(const char *filename, const char *pattern);
void insert_text(const char *filename, const char *text, int front);

#endif