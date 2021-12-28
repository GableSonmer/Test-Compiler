/**
 * 词法分析主程序
 */
#include "lexical.h"
#include "../tools/HashMap.h"
#include "cstdio"
#include "iostream"
#include "cstring"

#define MaxFilenameLength 100
#define KeywordNumber 9
#define MaxIDLength 39

char inPath[MaxFilenameLength], outPath[MaxFilenameLength];
FILE *in, *out;
//单分界符号
char singleword[] = "+-*%(){};,:";
//双分解符号
char doubleword[] = "><=!";
//列标号和行标号
int rowNumber, colNumber;
//存放识别的单词
static char token[1000];
HashMap map;

int startLexicalAnalysis(string input, string output) {
    strcpy(inPath, input.c_str());
    strcpy(outPath, output.c_str());
    return TESTScan();
}

/**
 * 0 - 分析没有错误
 * 错误编号
 * 1-打开输入文件错误
 * 2-打开输出文件错误
 * 3-超出标识符最大长度
 * 4-词法错误
 */
int init() {
//    cout << "请输入测试的源程序文件名: ";
//    cin >> filename1;
//    cout << "请输入输出分析结果文件名: ";
//    cin >> filename2;
    //使用自定义哈希表存放关键字
    string keywords[8] =
            {"if", "else", "for", "while", "do", "int", "read", "write"};
    for (auto s: keywords) {
        map.insert(s);
    }
//    显示哈希表
//    map.print();
    in = fopen(inPath, "r");
    out = fopen(outPath, "wt+");
    if (in == nullptr) {
        printf("打开输入文件错误\n");
        return 1;
    }
    if (out == nullptr) {
        printf("打开输出文件错误\n");
        return 2;
    }
    return 0;
}

/**
 * 从文件输入流读取下一个字符
 * 对行列标号进行修改
 * @return 读取的字符
 */
char getNextChar() {
    char ch = getc(in);
    if (ch == '\n') {
        rowNumber++;
        colNumber = 0;
    } else if (ch == '\t') {
        colNumber += 4;
    } else {
        colNumber += 1;
    }
    return ch;
}

/**
 * 词法分析主程序
 * @return
 */
int TESTScan() {
    int es = init();
    if (es > 0) {
        return es;
    }
    rowNumber = 1;
    colNumber = 0;
    char ch = getNextChar();
    while (ch != EOF) {
        while (ch == ' ' || ch == '\n' || ch == '\t') {
            ch = getNextChar();
        }
        if (ch == EOF) {
            break;
        }
        //标识符
        if (isalpha(ch)) {
            int i = 0;
            token[i++] = ch;
            ch = getNextChar();
            while (isalnum(ch)) {
                token[i++] = ch;
                ch = getNextChar();
            }
            token[i] = '\0';
            int col = colNumber - strlen(token);
            //使用哈希表查询标识符
            if (map.get(token) == 1) {
                //查询成功，为保留字
                fprintf(out, "%s %s %d %d\n", token, token, rowNumber, col);
            } else {
                //查询失败，为标识符
                //判断标识符长度，如果超过最大长度直接报错
                if (strlen(token) <= MaxIDLength) {
                    fprintf(out, "ID %s %d %d\n", token, rowNumber, col);
                } else {
                    printf("ERROR(%d行,%d列): 标识符%s长度(%lu)超出最大限制(%d)\n",
                           rowNumber, col, token, strlen(token), MaxIDLength);
                    es = 3;
                    fprintf(out, "ERROR %s %d %d\n", token, rowNumber, col);
                }
            }
        } else if (isdigit(ch)) {
            int i = 0;
            token[i++] = ch;
            ch = getNextChar();
            while (isdigit(ch)) {
                token[i++] = ch;
                ch = getNextChar();
            }
            token[i] = '\0';
            int col = colNumber - strlen(token) - 1;
            fprintf(out, "NUM %s %d %d\n", token, rowNumber, col);
        } else if (strchr(singleword, ch) != NULL) {
            token[0] = ch;
            token[1] = '\0';
            int col = colNumber - strlen(token);
            fprintf(out, "%s %s %d %d\n", token, token, rowNumber, col);
            ch = getNextChar();
        } else if (strchr(doubleword, ch) != NULL) {
            token[0] = ch;
            ch = getNextChar();
            if (ch == '=') {
                token[1] = ch;
                token[2] = '\0';
                ch = getNextChar();
            } else {
                token[1] = '\0';
            }
            int col = colNumber - strlen(token);
            fprintf(out, "%s %s %d %d\n", token, token, rowNumber, col);
        } else if (ch == '/') {
            ch = getNextChar();
            if (ch == '*') {
                char ch1 = getNextChar();
                do {
                    ch = ch1;
                    ch1 = getNextChar();
                } while ((ch != '*' || ch1 != '/') && ch1 != EOF);
                ch = getNextChar();
            } else {
                token[0] = '/';
                token[1] = '\0';
                int col = colNumber - strlen(token);
                fprintf(out, "%s %s %d %d\n", token, token, rowNumber, col);
            }
        } else if (ch == '\"') {
            int i = 0;
            ch = getNextChar();
            while (ch != '\"') {
                token[i++] = ch;
                ch = getNextChar();
            }
            token[i] = '\0';
            int col = colNumber - strlen(token);
            fprintf(out, "STRING %s %d %d\n", token, rowNumber, col);
            ch = getNextChar();
        } else {
            token[0] = ch;
            token[1] = '\0';
            if (ch < 0) { //中文处理
                ch = getNextChar();
                token[1] = ch;
                token[2] = '\0';
            }
            es = 4;
            int col = colNumber - strlen(token);
            fprintf(out, "ERROR %s %d %d\n", token, rowNumber, col);
            printf("ERROR(行:%d,列:%d): 符号\"%s\"错误\n", rowNumber, col, token);
            ch = getNextChar();
        }
    }
    fprintf(out, "EOF EOF %d %d\n", rowNumber, colNumber);
    fclose(in);
    fclose(out);
    return es;
}