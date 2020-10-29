/*
 * This file is part of Lapis.
 *
 * Lapis is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Lapis is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Lapis.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file lapis.c
 * @author Sora Tonami (ms0503@outlook.com)
 * @brief LapisLang Interpreter and CodeRunner
 * @version 0.1.0
 * @date 2020-10-28
 * 
 * @copyright Copyright (C) 2020 Sora Tonami
 */

#include <regex.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "errnum.h"

void main(int argc, char **argv) {
    int opt;

    while((opt = getopt(argc, argv, "f:h")) != -1) {
        switch(opt) {
            case 'f':
                run(optarg);
                break;
            case 'h':
                showHelp();
                break;
            case ':':
                printf("Err: option needs a value.\n");
                break;
            case '?':
                printf("Wrn: unknown option: %c\n", optopt);
                break;
        }
    }
    interpreter();

    exit(EXIT_SUCCESS);
}

void interpreter() {
    exit(EXIT_SUCCESS);
}

void run(char *filepath) {
    FILE *file;
    bool isMain = false;
    bool mainExists = false;
    char *buf;
    regex_t **ptn_buf;
    regmatch_t *match_buf;

    if(regcomp(ptn_buf[0], "fnc +main\\() +void", REG_EXTENDED | REG_NEWLINE) != 0) {
        printf("Err: Regex compile failed\n");
        exit(EXIT_CODERUNNER_FAILURE);
    }
    if(regcomp(ptn_buf[1], "end", REG_EXTENDED | REG_NEWLINE) != 0) {
        printf("Err: Regex compile failed\n");
        exit(EXIT_CODERUNNER_FAILURE);
    }
    if((file = fopen_s(filepath, "r")) == NULL) {
        printf("Err: Cannot open %s\n", filepath);
        exit(EXIT_CODERUNNER_FAILURE);
    }
    while(fscanf_s(file, "%s", buf) != EOF) {
        if(regexec(ptn_buf[0], buf, ptn_buf[0]->re_nsub + 1, match_buf, 0) == 0) {
            isMain = true;
            mainExists = true;
        }
        if(regexec(ptn_buf[1], buf, ptn_buf[1]->re_nsub + 1, match_buf, 0) == 0) isMain = false;
    }
    fclose_s(file);
    if(isMain) {
        printf("Err: No such 'end' keyword\n");
        exit(EXIT_CODERUNNER_FAILURE);
    }
    if(!mainExists) {
        printf("Err: No such 'main' function\n");
        exit(EXIT_CODERUNNER_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

void showHelp() {
    exit(EXIT_SUCCESS);
}
