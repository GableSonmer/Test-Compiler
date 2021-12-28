#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

#define KEYWORDNUM 9    // 关键字个数
#define MAXLENGTH 39    // 标识符最大长度
#define MAXFILENAME 100 // 文件名最大长度

namespace Testscan {
    FILE *fin, *fout;
    char Scanin[MAXFILENAME], Scanout[MAXFILENAME];
    char *keyword[KEYWORDNUM] = {"if", "else", "for", "while", "do", "int", "read", "write", "main"};
    char singleword[] = "+-*%(){};,:";
    char doubleword[] = "><=!";
    char token[MAXLENGTH + 2]; // 存放识别单词
    int frow, brow;            // 符号起止行标记
    int i, j, k, es;           // 临时整型变量
    char ch, ch1;              // 临时字符变量
}

using namespace Testscan;

/*****************************
错误列表：
打开输入文件出错
打开输出文件出错
标识符过长
标识符命名不合法
******************************/

int Init() {
    // printf("请输入源程序文件名（包括路径）：\n");
    // scanf("%s", Scanin);
    // printf("请输入词法分析输出文件名（包括路径）：\n");
    // scanf("%s", Scanout);

    strcpy(Scanin, "C:\\Users\\Administrator\\Desktop\\in.txt");
    strcpy(Scanout, "C:\\Users\\Administrator\\Desktop\\out1.txt");

    if ((fin = fopen(Scanin, "r")) == NULL) {
        printf("打开词法分析输入文件出错！\n");
        return 1;
    }
    if ((fout = fopen(Scanout, "w")) == NULL) {
        printf("创建词法分析输出文件出错！\n");
        return 2;
    }
    return 0;
}

char getNextChar() {
    char ch = getc(fin);
    if (ch == '\n') frow++;
    return ch;
}

int TESTscan() {
    int es = Init();
    if (es > 0) return es;

    frow = brow = 1;
    ch = getNextChar();
    while (ch != EOF) {
        while (ch == ' ' || ch == '\n' || ch == '\t') {
            ch = getNextChar();
        }

        brow = frow;
        if (ch == EOF) break;

        if (isalpha(ch)) { // 字母
            j = 0;
            token[j++] = ch;
            bool isLong = false; // 超长标记
            ch = getNextChar();
            while (isalnum(ch)) { // 字母+数字
                token[j++] = ch;
                ch = getNextChar();
                if (j > MAXLENGTH) {
                    isLong = true;
                    while (isalnum(ch)) { // 超长自动截断
                        ch = getNextChar();
                    }
                }
            }
            token[j] = '\0';
            if (isLong == true) { // 标识符太长
                es = 3;
                printf("ERROR(%d): 标识符\"%s\"超长\n", brow, token);
                fprintf(fout, "%d\t%s\t%s\n", brow, "ERROR", token);
                continue;
            }

            k = 0;
            char str[MAXLENGTH + 2];
            for (i = 0; i < strlen(token); i++) { // 小写化
                str[i] = tolower(token[i]);
            }
            str[i] = '\0';
            while (k < KEYWORDNUM && strcmp(str, keyword[k]))
                k++;
            if (k >= KEYWORDNUM)
                fprintf(fout, "%d\t%s\t%s\n", brow, "ID", token);
            else
                fprintf(fout, "%d\t%s\t%s\n", brow, str, token);
        } else if (isdigit(ch)) { // 数字
            j = 0;
            token[j++] = ch;
            ch = getNextChar();
            while (isdigit(ch)) {
                token[j++] = ch;
                ch = getNextChar();
            }
            token[j] = '\0';
            fprintf(fout, "%d\t%s\t%s\n", brow, "NUM", token);
        } else if (strchr(singleword, ch) > 0) { // 单分界符
            token[0] = ch;
            token[1] = '\0';
            fprintf(fout, "%d\t%s\t%s\n", brow, token, token);
            ch = getNextChar();
        } else if (strchr(doubleword, ch) > 0) { // 双分界符
            token[0] = ch;
            ch = getNextChar();
            if (ch == '=') {
                token[1] = ch;
                token[2] = '\0';
                ch = getNextChar();
            } else token[1] = '\0';
            fprintf(fout, "%d\t%s\t%s\n", brow, token, token);
        } else if (ch == '/') { // 注释
            ch = getNextChar();
            if (ch == '*') {
                ch1 = getNextChar();
                do { // 删除注释
                    ch = ch1;
                    ch1 = getNextChar();
                } while ((ch != '*' || ch1 != '/') && ch1 != EOF);
                ch = getNextChar();
            } else {
                token[0] = '/';
                token[1] = '\0';
                fprintf(fout, "%d\t%s\t%s\n", brow, token, token);
            }
        } else if (ch == '\"') { // 字符串
            j = 0;
            ch = getNextChar();
            while (ch != '\"') {
                token[j++] = ch;
                ch = getNextChar();
            }
            token[j] = '\0';
            fprintf(fout, "%d\t%s\t%s\n", brow, "STR", token);
            ch = getNextChar();
        } else { // 命名不规范
            token[0] = ch;
            token[1] = '\0';
            if (ch < 0) { //中文处理
                ch = getNextChar();
                token[1] = ch;
                token[2] = '\0';
            }
            es = 4;
            fprintf(fout, "%d\t%s\t%s\n", brow, "ERROR", token);
            printf("ERROR(%d): 符号\"%s\"不规范\n", brow, token);
            ch = getNextChar();
        }
    }
    fprintf(fout, "%d\tEOF\tEOF\n", brow);
    fclose(fin);
    fclose(fout);
    return es;
}