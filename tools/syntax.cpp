#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <string>
#include "syntax.h"

#define MAXFILENAME 100 // 文件名最大长度
#define MAXLENGTH 40    // 字符串最大长度
int wrow;                                       // 错误行号
FILE *fin, *fout;                               // 输入输出文件的指针
char token[1000], token1[1000];     // token保存单词符号，token1保存单词值
char Scanin[MAXFILENAME], Scanout[MAXFILENAME]; // 输入输出文件名
using namespace std;


int startSyntaxAnalysis(string in, string out){
    return 888;
    strcpy(Scanin, in.c_str());
    strcpy(Scanout, "output.txt");
    return TESTparse();
}
//
//int TESTparse() {
//    int es = 0;
//    if ((fin = fopen(Scanin, "r")) == NULL) {
//        printf("\n打开%s错误!\n", Scanout);
//        es = 10;
//    }
//
//    if ((fout = fopen(Scanout, "w")) == NULL) {
//        printf("\n打开%s错误!\n", Scanout);
//        es = 10;
//    }
//
//    if (es == 0) es = program();
//    printf("=====语法分析结果!======\n");
//    switch (es) {
//        case 0:
//            printf("语法分析成功!\n");
//            break;
//        case 10:
//            printf("打开文件失败!\n");
//            break;
//        case 1:
//            printf("ERROR(%d): \"%s\"前面缺少{\n", wrow, token1);
//            break;
//        case 2:
//            printf("ERROR(%d): \"%s\"前面缺少}\n", wrow, token1);
//            break;
//        case 3:
//            printf("ERROR(%d): \"%s\"前面缺少标识符\n", wrow, token1);
//            break;
//        case 4:
//            printf("ERROR(%d): \"%s\"前面缺少分号\n", wrow, token1);
//            break;
//        case 5:
//            printf("ERROR(%d): \"%s\"前面缺少(\n", wrow, token1);
//            break;
//        case 6:
//            printf("ERROR(%d): \"%s\"前面缺少)\n", wrow, token1);
//            break;
//        case 7:
//            printf("ERROR(%d): \"%s\"前面缺少操作数\n", wrow, token1);
//            break;
//        case 9:
//            printf("ERROR(%d): \"%s\"前面缺少主程序\n", wrow, token1);
//            break;
//        case 11:
//            printf("ERROR(%d): 主程序名错误!\n", wrow);
//            break;
//        case 12:
//            printf("ERROR(%d): \"%s\"前面缺少while\n", wrow, token1);
//            break;
//        case 25:
//            printf("ERROR(%d): \"%s\"已超出程序末尾\n", wrow, token1);
//            break;
//        case 26:
//            printf("ERROR(%d): else没有匹配的if\n", wrow);
//    }
//    fclose(fin);
//    fclose(fout);
//    return es;
//}
//
//// <程序>::={<声明序列><语句序列>}
//// program::={<declaration_list><statement_list>}
//int program() {
//    int es = 0;
//    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//    printf("%s %s\n", token, token1);
//    es = declaration_list(); // 声明语句
//    if (es > 0) return es;
//
//    if (strcmp(token, "main")) return 9; // main区
//    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//    printf("%s %s\n", token, token1);
//    if (strcmp(token, "ID")) return 11; // 程序名
//    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//    printf("%s %s\n", token, token1);
//    if (strcmp(token, "{")) return 1; // 判断是否'{'
//    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//    printf("%s %s\n", token, token1);
//    es = statement_list(); // 语句序列
//    if (es > 0) return es;
//    if (strcmp(token, "}")) return 2; // 判断是否'}'
//    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//    printf("%s %s\n", token, token1);
//    if (strcmp(token, "EOF")) return 25; // 超出程序末尾
//    return es;
//}
//
//// <声明序列>::=<声明序列><声明语句>|<声明语句>
//// <declaration_list>::=<declaration_list><declaration_stat>|<declaration_stat>
//int declaration_list() {
//    int es = 0;
//    while (strcmp(token, "int") == 0) {
//        es = declaration_stat();
//        if (es > 0) return es;
//    }
//    return es;
//}
//
//// <声明语句>::=int<变量>；
//// <declaration_stat>::=int ID;
//int declaration_stat() {
//    int es = 0;
//    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//    printf("%s %s\n", token, token1);
//    while (1) { // 支持连续定义
//        if (strcmp(token, "ID")) return 3; // 不是标识符
//        fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//        printf("%s %s\n", token, token1);
//        if (strcmp(token, ",") == 0) {
//            fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//            printf("%s %s\n", token, token1);
//        } else break;
//    }
//    if (strcmp(token, ";")) return 4; // 缺少分号
//    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//    printf("%s %s\n", token, token1);
//    return es;
//}
//
//// <语句序列>::=<语句序列><语句>|<语句>
//// <statement_list>::=<statement_list><statement>|<statement>
//int statement_list() {
//    int es = 0;
//    while (strcmp(token, "}")) {
//        es = statement();
//        if (es > 0) return es;
//        if (strcmp(token, "EOF") == 0) {
//            return 2; // 缺少}
//        }
//    }
//    return es;
//}
//
//// <语句>::=<if语句>|<while语句>|<for语句>|<read语句>|<write语句>|<复合语句>|<表达式语句>
//// <statement>::= <if_stat>|<while_stat>|<for_stat>|<compound_stat>|<expression_stat>
//int statement() {
//    int es = 0;
//    if ((strcmp(token, "if") == 0 || strcmp(token, "else") == 0)) es = if_stat(); // <IF语句>
//    else if (strcmp(token, "while") == 0) es = while_stat();                      // <while语句>
//    else if (strcmp(token, "for") == 0) es = for_stat();                          // <for语句>
//    else if (strcmp(token, "do") == 0) es = do_while_stat();                      // do_while语句
//    else if (strcmp(token, "read") == 0) es = read_stat();                        // <read语句>
//    else if (strcmp(token, "write") == 0) es = write_stat();                      // <write语句>
//    else if (strcmp(token, "{") == 0) es = compound_stat();                       // <复合语句>
//    else if ((strcmp(token, "ID") == 0 || strcmp(token, "NUM") == 0 || strcmp(token, "(") == 0) ||
//             strcmp(token, ";") == 0)
//        es = expression_stat();                                                   // <表达式语句>
//    return es;
//}
//
//// <IF语句>::=if(<表达式>)<语句>[else<语句>]
//// <IF_stat>::=if(<expr>)<statement>[else<statement>]
//int if_stat() {
//    if (strcmp(token, "else") == 0) return 26; // else未匹配if
//    int es = 0;
//    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//    printf("%s %s\n", token, token1);
//    if (strcmp(token, "(")) return 5; // 缺少左括号
//    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//    printf("%s %s\n", token, token1);
//    es = expression();
//    if (es > 0) return es;
//    if (strcmp(token, ")")) return 6; // 缺少右括号
//
//    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//    printf("%s %s\n", token, token1);
//    es = statement(); // 语句
//    if (es > 0) return es;
//
//    if (strcmp(token, "else") == 0) { // else部分处理
//        fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//        printf("%s %s\n", token, token1);
//        es = statement();
//        if (es > 0) return es;
//    }
//    return es;
//}
//
//// <复合语句>::={<语句序列>}
//// <compound_stat>::={<statement_list>}
//int compound_stat() {
//    int es = 0;
//    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//    printf("%s %s\n", token, token1);
//    es = statement_list(); // 语句序列
//    if (es > 0) return es;
//    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//    printf("%s %s\n", token, token1);
//    return es;
//}
//
//// <do_whilie语句>::do{语句序列}while(表达式)
//// <do_whilie_stat>::do{statment_list}while(expression)
//int do_while_stat() {
//    int es = 0;
//    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//    printf("%s %s\n", token, token1);
//    if (strcmp(token, "{")) return 1; // 缺少左括号
//    es = statement(); //语句
//    if (es > 0) return es;
//    printf("%s %s\n", token, token1);
//    if (strcmp(token, "while")) return 12; // 缺少while
//
//    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//    printf("%s %s\n", token, token1);
//    if (strcmp(token, "(")) return 5; // 缺少左括号
//    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//    printf("%s %s\n", token, token1);
//
//    es = expression(); // 表达式
//    if (es > 0) return es;
//
//    if (strcmp(token, ")")) return 6; // 缺少右括号
//    if (es > 0) return es;
//    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//    printf("%s %s\n", token, token1);
//    return es;
//}
//
//// <while语句>::=while(<表达式>)<语句>
//// <while_stat>::=while(<expr>)<statement >
//int while_stat() {
//    int es = 0;
//    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//    printf("%s %s\n", token, token1);
//    if (strcmp(token, "(")) return 5; // 缺少左括号
//    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//    printf("%s %s\n", token, token1);
//    es = expression();
//    if (es > 0) return es;
//    if (strcmp(token, ")")) return 6; // 缺少右括号
//
//    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//    printf("%s %s\n", token, token1);
//    es = statement();
//    if (es > 0) return es;
//    return es;
//}
//
//// <for语句>::=for(<表达式>;<表达式>;<表达式>)<语句>
//// <for_stat>::=for(<expr>,<expr>,<expr>)<statement>
//// <for_stat>::=for (<expression>;
//int for_stat() {
//    int es = 0;
//    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//    printf("%s %s\n", token, token1);
//    if (strcmp(token, "(")) return 5; // 缺少左括号
//    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//    printf("%s %s\n", token, token1);
//    es = expression();
//    if (es > 0) return es;
//    if (strcmp(token, ";")) return 4; // 缺少分号
//
//    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//    printf("%s %s\n", token, token1);
//    es = expression();
//    if (es > 0) return es;
//    if (strcmp(token, ";")) return 4; // 缺少分号
//
//    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//    printf("%s %s\n", token, token1);
//    es = expression();
//    if (es > 0) return es;
//    if (strcmp(token, ")")) return 6; // 缺少右括号
//
//    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//    printf("%s %s\n", token, token1);
//    es = statement();
//    if (es > 0) return es;
//    return es;
//}
//
//// <read_语句>::=read<变量>;
//// <read_stat>::=read ID;
//int read_stat() {
//    int es = 0;
//    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//    printf("%s %s\n", token, token1);
//    if (strcmp(token, "ID")) return 3; // 缺少标识符
//
//    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//    printf("%s %s\n", token, token1);
//    if (strcmp(token, ";")) return 4; // 缺少分号
//    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//    printf("%s %s\n", token, token1);
//    return es;
//}
//
//// <write_语句>::=write <表达式>;
//// <write_stat>::=write <expression>;
//// <write_STR>::write <STR>;
//int write_stat() {
//    int es = 0;
//    fscanf(fin, "%d %s ", &wrow, token);
//    printf("%s ", token);
//    if (strcmp(token, "STR") == 0) { // 输出字符串
//        fgets(token1, 1024, fin);
//        printf("%s", token1);
//        fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//        printf("%s %s\n", token, token1);
//        if (strcmp(token, ";")) return 4; // 缺少分号
//        fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//        printf("%s %s\n", token, token1);
//        return es;
//    }
//    fscanf(fin, "%s", &token1);
//    printf("%s\n", token1);
//    es = expression();
//    if (es > 0) return es;
//    if (strcmp(token, ";")) return 4; // 缺少分号
//    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//    printf("%s %s\n", token, token1);
//    return es;
//}
//
//// <表达式语句>::=<<表达式>;|;
//// <expression_stat>::=<expression>;|;
//int expression_stat() {
//    int es = 0;
//    if (strcmp(token, ";") == 0) {
//        fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//        printf("%s %s\n", token, token1);
//        return es;
//    }
//    es = expression();
//    if (es > 0) return es;
//    if (strcmp(token, ";") == 0) {
//        fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//        printf("%s %s\n", token, token1);
//        return es;
//    } else {
//        return 4; // 缺少分号
//    }
//}
//
//// <表达式>::=<标识符>=<布尔表达式>|<布尔表达式>
//// <expr>::=ID=<bool_expr>|<bool_expr>
//int expression() {
//    int es = 0, fileadd;
//    char token2[MAXLENGTH + 2], token3[MAXLENGTH + 2];
//    if (strcmp(token, "ID") == 0) {
//        fileadd = ftell(fin); // 记住当前文件位置
//        fscanf(fin, "%d %s %s\n", &wrow, token2, token3);
//        printf("%s %s\n", token2, token3);
//
//        if (strcmp(token2, "=") == 0) { //'='
//            fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//            printf("%s %s\n", token, token1);
//            es = bool_expr();
//            if (es > 0) return es;
//        } else { // "=="
//            fseek(fin, fileadd, 0); // 若非'='则文件指针回到'='前的标识符
//            es = bool_expr();
//            if (es > 0) return es;
//        }
//    } else {
//        es = bool_expr();
//    }
//    return es;
//}
//
//// <布尔表达式>::=<算术表达式>|<算术表达式>(>|<|>=|<=|==|!=)<算术表达式>
//// <bool_expr>::=<additive_expr>|< additive_expr >(>|<|>=|<=|==|!=)< additive_expr >
//int bool_expr() {
//    int es = 0;
//    es = additive_expr();
//    if (es > 0) return es;
//    if (strcmp(token, ">") == 0 || strcmp(token, ">=") == 0 || strcmp(token, "<") == 0 ||
//        strcmp(token, "<=") == 0 || strcmp(token, "==") == 0 || strcmp(token, "!=") == 0) {
//        char token2[MAXLENGTH + 2];
//        strcpy(token2, token); // 保存运算符
//        fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//        printf("%s %s\n", token, token1);
//        es = additive_expr();
//        if (es > 0) return es;
//    }
//    return es;
//}
//
//// <算术表达式>::=<项>{(+|-)<项>}
//// <additive_expr>::=<term>{(+|-)< term >}
//// < additive_expr>::=<term>{(+< term >@ADD |-<项>@SUB)}
//int additive_expr() {
//    int es = 0;
//    es = term();
//    if (es > 0) return es;
//    while (strcmp(token, "+") == 0 || strcmp(token, "-") == 0) {
//        char token2[MAXLENGTH + 2];
//        strcpy(token2, token);
//        fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//        printf("%s %s\n", token, token1);
//        es = term();
//        if (es > 0) return es;
//    }
//    return es;
//}
//
//// <项>::=<因子>{(*|/)<因子>}
//// < term >::=<factor>{(*| /)< factor >}
//// < term >::=<factor>{(*< factor >@MULT | /< factor >@DIV)}
//int term() {
//    int es = 0;
//    es = factor();
//    if (es > 0) return es;
//    while (strcmp(token, "*") == 0 || strcmp(token, "/") == 0 || strcmp(token, "%") == 0) {
//        char token2[MAXLENGTH + 2];
//        strcpy(token2, token);
//        fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//        printf("%s %s\n", token, token1);
//        es = factor();
//        if (es > 0) return es;
//    }
//    return es;
//}
//
//// <因子>::=(<算术表达式>)|<标识符>|<无符号整数>
//// < factor >::=(<additive_expr>)| ID|NUM
//int factor() {
//    int es = 0;
//    if (strcmp(token, "(") == 0) {
//        fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//        printf("%s %s\n", token, token1);
//        es = expression(); // 表达式
//        if (es > 0) return es;
//        if (strcmp(token, ")")) return 6; // 缺少右括号
//        fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//        printf("%s %s\n", token, token1);
//    } else {
//        if (strcmp(token, "ID") == 0) {
//            fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//            printf("%s %s\n", token, token1);
//            return es;
//        } else if (strcmp(token, "NUM") == 0) {
//            fscanf(fin, "%d %s %s\n", &wrow, token, token1);
//            return es;
//        } else {
//            return 7; // 缺少操作数
//        }
//    }
//    return es;
//}