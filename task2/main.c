#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <signal.h>

#define MAX(a, b) (((a)>(b))?(a):(b))

char *filename;
struct Users {
    char *name;
    char *num;
    int exist;
    int user_id;
};

struct Users *book;
size_t size;
size_t maxid;
int stop;

void write_to_book(int id, char *name, char *num);

int compare_name(char *name1, char *name2);

int compare_number(char *num, char *num1);


char *stristr(char *str1, const char *str2) {
    char *p1 = str1;
    const char *p2 = str2;
    char *r = *p2 == 0 ? str1 : 0;

    while (*p1 != 0 && *p2 != 0) {
        if (tolower(*p1) == tolower(*p2)) {
            if (r == 0) {
                r = p1;
            }
            p2++;
        } else {
            p2 = str2;
            if (tolower(*p1) == tolower(*p2)) {
                r = p1;
                p2++;
            } else {
                r = 0;
            }
        }
        p1++;
    }
    return *p2 == 0 ? r : 0;
}

char *read_str(FILE *fp) {
    int c;
    int nch = 0;
    size_t size = 16;
    char *buf = malloc(size);
    if (buf == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    while ((c = fgetc(fp)) != '\n') {
        if (nch >= size - 1) {
            size *= 2;
            buf = realloc(buf, size);
            if (buf == NULL) {
                fprintf(stderr, "out of memory\n");
                exit(1);
            }
        }
        if (nch != 0 || c != ' ') {
            buf[nch++] = c;
        }

    }
    buf[nch] = '\0';
    return buf;
}


int read_file(char *filename) {
    FILE *fp;

    fp = fopen(filename, "r+");
    if (fp == NULL) {
        return -1;
    }
    int id;
    while (fscanf(fp, "%d", &id) != EOF) {
        char *name = read_str(fp);
        char *num = read_str(fp);
        write_to_book(id, name, num);
        maxid = MAX(maxid, id);
    }
    fclose(fp);
    return 0;
}

struct Users *find(int id, char *name, char *num, int need_print) {
    for (int i = 0; i < size; i++) {
        if (id != -1) {
            if (id == book[i].user_id) {
                if (need_print) {
                    printf("%d %s %s\n", book[i].user_id, book[i].name, book[i].num);
                } else {
                    return &book[i];
                }
            }
        } else if (name != NULL) {
            if (compare_name(book[i].name, name)) {
                if (need_print) {
                    printf("%d %s %s\n", book[i].user_id, book[i].name, book[i].num);
                } else {
                    return &book[i];
                }
            }
        } else if (num != NULL) {
            if (compare_number(num, book[i].num)) {
                if (need_print) {
                    printf("%d %s %s\n", book[i].user_id, book[i].name, book[i].num);
                } else {
                    return &book[i];
                }
            }
        }
    }
    return NULL;
}

char *skip_syms(char *num) {
    char *ptr1 = num;
    while (*ptr1 == '+' || *ptr1 == '-' || *ptr1 == '(' || *ptr1 == ')' || *ptr1 == ' ') {
        ptr1 += sizeof(char);
    }
    return ptr1;
}

int compare_number(char *num, char *num1) {
    char *ptr1 = num;
    char *ptr2 = num1;
    while (*ptr1 != '\0' && *ptr2 != '\0') {
        ptr1 = skip_syms(ptr1);
        ptr2 = skip_syms(ptr2);
        if (*ptr1 != *ptr2) {
            return 0;
        }
        ptr1 += sizeof(char);
        ptr2 += sizeof(char);
    }
    ptr1 = skip_syms(ptr1);
    ptr2 = skip_syms(ptr2);
    if (*ptr1 == '\0' && *ptr2 == '\0') {
        return 1;
    }
    return 0;
}

int compare_name(char *name, char *namepart) {
    if (stristr(name, namepart) != NULL) {
        return 1;
    } else {
        return 0;
    };
}

void write_book_to_file(char *filename) {
    FILE *fp;

    fp = fopen(filename, "w");

    for (int i = 0; i < size; i++) {
        if (book[i].exist) {
            fprintf(fp, "%d %s\n%s\n", book[i].user_id, book[i].name, book[i].num);
        }
    }
    fclose(fp);
}

void stop_program(int t) {
    stop = 1;
    write_book_to_file(filename);
    for (int i = 0; i < size; i++) {
        free(book[i].name);
        free(book[i].num);
    }
    free(book);
    exit(0);
}

void write_to_book(int id, char *name, char *num) {
    size_t t = sizeof(struct Users);
    book = (struct Users *) realloc(book, (size + 1) * sizeof(struct Users));
    book[size].user_id = id;
    book[size].exist = 1;
    book[size].name = name;
    book[size].num = num;
    size++;
}

int main(int argc, char *argv[]) {

    signal(SIGINT, stop_program);
    filename = argv[1];
    size = 0;
    stop = 0;
    maxid = 0;
    book = (struct Users *) malloc(sizeof(struct Users) * size);
    read_file(filename);
    char *command;
    while (!stop) {
        command = read_str(stdin);
        char *ptr = strtok(command, " ");;

        if (!strcmp(ptr, "find")) {
            ptr = strtok(NULL, " ");
            find(-1, ptr, NULL, 1);
            find(-1, NULL, ptr, 1);
        } else if (!strcmp(ptr, "delete")) {
            ptr = strtok(NULL, " ");
            int id = atoi(ptr);
            struct Users *user1 = find(id, NULL, NULL, 0);
            user1->exist = 0;
        } else if (!strcmp(ptr, "create")) {
            maxid += 1;
            char *name = strtok(NULL, " ");
            char *num = strtok(NULL, " ");
            write_to_book(maxid, name, num);
        } else if (!strcmp(ptr, "change")) {
            ptr = strtok(NULL, " ");
            int id = atoi(ptr);
            struct Users *user1 = find(id, NULL, NULL, 0);
            ptr = strtok(NULL, " ");
            if (!strcmp(ptr, "name")) {
                user1->name = strtok(NULL, " ");
            } else if (!strcmp(ptr, "number")) {
                user1->num = strtok(NULL, " ");
            } else {
                printf("Unknown field %s\n", ptr);
            }
        } else if (!strcmp(ptr, "exit")) {
            stop_program(1);
            return 0;
        } else {
            printf("Unknown command %s\n", ptr);
        }
        fflush(stdout);
    }
    return 0;
}