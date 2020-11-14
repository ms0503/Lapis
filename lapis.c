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

#define LAST_MODIFY_YEAR 2020

void main(int argc, char **argv) {
    int opt;

    while((opt = getopt(argc, argv, "f:h")) != -1) {
        switch(opt) {
            case 'f':
                run(optarg);
                exit(EXIT_SUCCESS);
            case 'h':
                showHelp();
                exit(EXIT_SUCCESS);
            case ':':
                printf("Err: option needs a value.\n");
                exit(EXIT_SUCCESS);
            case '?':
                printf("Wrn: unknown option: %c\n", optopt);
                break;
        }
    }
    interpreter();
}

void interpreter() {
    printf("Lapis  Copyright (C) %d  Sora Tonami\n", LAST_MODIFY_YEAR);
    printf("This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.\n");
    printf("This is free software, and you are welcome to redistribute it\n");
    printf("under certain conditions; type `show c' for details.\n");
    char *str;
    printf("> ");
    while(scanf("%s", &str) == 1) {
        switch(str) {
            case "show c":
                printf("IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING\n");
                printf("WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MODIFIES AND/OR CONVEYS\n");
                printf("THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES, INCLUDING ANY\n");
                printf("GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE\n");
                printf("USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED TO LOSS OF\n");
                printf("DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY YOU OR THIRD\n");
                printf("PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER PROGRAMS),\n");
                printf("EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE POSSIBILITY OF\n");
                printf("SUCH DAMAGES.\n");
                break;
            case "show w":
                printf("THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY\n");
                printf("APPLICABLE LAW. EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT\n");
                printf("HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM “AS IS” WITHOUT WARRANTY\n");
                printf("OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,\n");
                printf("THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR\n");
                printf("PURPOSE. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM\n");
                printf("IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF\n");
                printf("ALL NECESSARY SERVICING, REPAIR OR CORRECTION.\n");
                break;
        }
        printf("> ");
    }
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
