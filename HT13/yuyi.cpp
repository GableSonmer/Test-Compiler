#include <stdio.h>
#include <ctype.h>
#include <string.h>

int TESTparse();
int program();
int compound_Stat();
int statement();
int expression_Stat();
int expression();
int bool_expr();
int additive_expr();
int term();
int factor();
int if_stat();
int while_stat();
int for_stat();
int write_stat();
int read_stat();
int do_while_stat();
int declaration_stat();
int declaration_list();
int statement_list();
int compound_stat();
int expression_stat();

#define MAXVARTABLEP 500 // 定义符号表的容量
#define MAXFILENAME 100  // 文件名最大长度
#define MAXLENGTH 40     // 字符串最大长度

namespace Testparse {
    struct Table {       // 定义符号表结构
        char name[MAXLENGTH];
        int address;
    } vartable[MAXVARTABLEP];
    int vartablep = 0, labelp = 0, datap = 0;

    int wrow;                                       // 错误行号
    FILE *fin, *fout;                               // 输入输出文件的指针
    char token[MAXLENGTH], token1[MAXLENGTH];       // token保存单词符号,token1保存单词值
    char Scanin[MAXFILENAME], Scanout[MAXFILENAME]; // 输入输出文件名
}
using namespace Testparse;

int TESTparse() {
    // system("C:\\Users\\Administrator\\Desktop\\test.exe");
    strcpy(Scanin, "C:\\Users\\Administrator\\Desktop\\out1.txt");
    strcpy(Scanout, "C:\\Users\\Administrator\\Desktop\\out2.txt");


    int es = 0;
    if ((fin = fopen(Scanin, "r")) == NULL) {
        printf("\n打开%s错误!\n", Scanout);
        es = 10;
    }

    if ((fout = fopen(Scanout, "w")) == NULL) {
        printf("\n打开%s错误!\n", Scanout);
        es = 10;
    }

    if (es == 0) es = program();
    printf("=====语法分析结果!======\n");
    switch (es) {
        case 0:
            printf("语义分析成功!\n");
            break;
        case 10:
            printf("打开文件失败!\n");
            break;
        case 1:
            printf("ERROR(%d): \"%s\"前面缺少{\n", wrow, token1);
            break;
        case 2:
            printf("ERROR(%d): \"%s\"前面缺少}\n", wrow, token1);
            break;
        case 3:
            printf("ERROR(%d): \"%s\"前面缺少标识符\n", wrow, token1);
            break;
        case 4:
            printf("ERROR(%d): \"%s\"前面缺少分号\n", wrow, token1);
            break;
        case 5:
            printf("ERROR(%d): \"%s\"前面缺少(\n", wrow, token1);
            break;
        case 6:
            printf("ERROR(%d): \"%s\"前面缺少)\n", wrow, token1);
            break;
        case 7:
            printf("ERROR(%d): \"%s\"前面缺少操作数\n", wrow, token1);
            break;
        case 9:
            printf("ERROR(%d): \"%s\"前面缺少主程序\n", wrow, token1);
            break;
        case 11:
            printf("ERROR(%d): 主程序名错误!\n", wrow);
            break;
        case 12:
            printf("ERROR(%d): \"%s\"前面缺少while\n", wrow, token1);
            break;
        case 21:
            printf("ERROR(%d): 符号表溢出\n", wrow);
            break;
        case 22:
            printf("ERROR(%d): 变量\"%s\"重复定义\n", wrow, token1);
            break;
        case 23:
            printf("ERROR(%d): 变量\"%s\"未声明\n", wrow, token1);
            break;
        case 25:
            printf("ERROR(%d): \"%s\"已超出程序末尾\n", wrow, token1);
            break;
        case 26:
            printf("ERROR(%d): else没有匹配的if\n", wrow);
    }
    fclose(fin);
    fclose(fout);
    return es;
}

// 插入符号表
int name_def(char *name) {
    if (vartablep >= MAXVARTABLEP) return 21; // 符号表溢出
    for (int i = vartablep - 1; i >= 0; i--) {
        if (strcmp(vartable[i].name, name) == 0) {
            return 22; // 变量重复定义
        }
    }
    strcpy(vartable[vartablep].name, name);
    vartable[vartablep++].address = datap++;
    return 0;
}

// 查询符号表返回地址
int lookup(char *name, int *paddress) {
    for (int i = 0; i < vartablep; i++) {
        if (strcmp(vartable[i].name, name) == 0) {
            *paddress = vartable[i].address;
            return 0;
        }
    }
    return 23; // 变量未声明
}

// <程序>::={<声明序列><语句序列>}
// program::={<declaration_list><statement_list>}
int program() {
    int es = 0;
    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
    printf("%s %s\n", token, token1);
    es = declaration_list(); // 声明语句
    if (es > 0) return es;

    printf("             符号表\n"); // 符号表输出
    printf("        名字      地址\n");
    for (int i = 0; i < vartablep; i++)
        printf("%10s%10d\n", vartable[i].name, vartable[i].address);

    if (strcmp(token, "main")) return 9; // main区
    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
    printf("%s %s\n", token, token1);
    if (strcmp(token, "ID")) return 11; // 程序名
    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
    printf("%s %s\n", token, token1);
    if (strcmp(token, "{")) return 1; // 判断是否'{'
    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
    printf("%s %s\n", token, token1);
    es = statement_list(); // 语句序列
    if (es > 0) return es;
    if (strcmp(token, "}")) return 2; // 判断是否'}'
    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
    printf("%s %s\n", token, token1);
    if (strcmp(token, "EOF")) return 25; // 超出程序末尾
    fprintf(fout, "        STOP\n"); // 产生停止指令
    return es;
}

// <声明序列>::=<声明序列><声明语句>|<声明语句>
// <declaration_list>::=<declaration_list><declaration_stat>|<declaration_stat>
int declaration_list() {
    int es = 0;
    while (strcmp(token, "int") == 0) {
        es = declaration_stat();
        if (es > 0) return es;
    }
    return es;
}

// <声明语句>::=int<变量>；
// <declaration_stat>::=int ID;
// <declaration_stat>↓vartablep,datap,codep ->int ID↑n@name-def↓n,t;
int declaration_stat() {
    int es = 0;
    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
    printf("%s %s\n", token, token1);
    while (1) { // 支持连续定义
        if (strcmp(token, "ID")) return 3; // 不是标识符
        es = name_def(token1); //插入到符号表
        if (es > 0) return es;
        fscanf(fin, "%d %s %s\n", &wrow, token, token1);
        printf("%s %s\n", token, token1);
        if (strcmp(token, ",") == 0) {
            fscanf(fin, "%d %s %s\n", &wrow, token, token1);
            printf("%s %s\n", token, token1);
        } else break;
    }
    if (strcmp(token, ";")) return 4; // 缺少分号
    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
    printf("%s %s\n", token, token1);
    return es;
}

// <语句序列>::=<语句序列><语句>|<语句>
// <statement_list>::=<statement_list><statement>|<statement>
int statement_list() {
    int es = 0;
    while (strcmp(token, "}")) {
        es = statement();
        if (es > 0) return es;
        if (strcmp(token, "EOF") == 0) {
            return 2; // 缺少}
        }
    }
    return es;
}

// <语句>::=<if语句>|<while语句>|<for语句>|<read语句>|<write语句>|<复合语句>|<表达式语句>
// <statement>::= <if_stat>|<while_stat>|<for_stat>|<compound_stat>|<expression_stat>
int statement() {
    int es = 0;
    if ((strcmp(token, "if") == 0 || strcmp(token, "else") == 0)) es = if_stat(); // <IF语句>
    else if (strcmp(token, "while") == 0) es = while_stat();                      // <while语句>
    else if (strcmp(token, "for") == 0) es = for_stat();                          // <for语句>
    else if (strcmp(token, "do") == 0) es = do_while_stat();                      // do_while语句
    else if (strcmp(token, "read") == 0) es = read_stat();                        // <read语句>
    else if (strcmp(token, "write") == 0) es = write_stat();                      // <write语句>
    else if (strcmp(token, "{") == 0) es = compound_stat();                       // <复合语句>
    else if ((strcmp(token, "ID") == 0 || strcmp(token, "NUM") == 0 || strcmp(token, "(") == 0) ||
             strcmp(token, ";") == 0)
        es = expression_stat(); // <表达式语句>
    return es;
}

// <IF语句>::=if(<表达式>)<语句>[else<语句>]
// <IF_stat>::=if(<expr>)<statement>[else<statement>]
// if (<expression>)@BRF↑label1 <statement > @BR↑label2 @SETlabel↓label1
// [ else < statement >] @SETlabel↓label2
//  其中动作符号的含义如下
//  @BRF↑label1 ：输出 BRF label1,
//  @BR↑label2：输出 BR label2,
//  @SETlabel↓label1：设置标号label1
//  @SETlabel↓label2：设置标号label2
int if_stat() {
    if (strcmp(token, "else") == 0) return 26; // else未匹配if
    int es = 0, label1, label2;
    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
    printf("%s %s\n", token, token1);
    if (strcmp(token, "(")) return 5; // 缺少左括号
    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
    printf("%s %s\n", token, token1);
    es = expression();
    if (es > 0) return es;
    if (strcmp(token, ")")) return 6; // 缺少右括号
    label1 = labelp++; // 用label1记住条件为假时要转向的标号
    fprintf(fout, "        BRF LABEL%d\n", label1);

    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
    printf("%s %s\n", token, token1);
    es = statement(); // 语句
    if (es > 0) return es;

    label2 = labelp++; // 用label2记住要转向的标号
    fprintf(fout, "        BR LABEL%d\n", label2);
    fprintf(fout, "LABEL%d:\n", label1); // 设置label1记住的标号

    if (strcmp(token, "else") == 0) { // else部分处理
        fscanf(fin, "%d %s %s\n", &wrow, token, token1);
        printf("%s %s\n", token, token1);
        es = statement();
        if (es > 0) return es;
    }
    fprintf(fout, "LABEL%d:\n", label2); // 设置label2记住的标号
    return es;
}

// <复合语句>::={<语句序列>}
// <compound_stat>::={<statement_list>}
int compound_stat() {
    int es = 0;
    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
    printf("%s %s\n", token, token1);
    es = statement_list(); // 语句序列
    if (es > 0) return es;
    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
    printf("%s %s\n", token, token1);
    return es;
}

// <do_whilie语句>::do{语句序列}while(表达式)
// <do_whilie_stat>::do{statment_list}while(expression)
int do_while_stat() {
    int es = 0, label1, label2;
    label1 = labelp++;
    fprintf(fout, "LABEL%d:\n", label1); // 设置label1标号
    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
    printf("%s %s\n", token, token1);
    if (strcmp(token, "{")) return 1; // 缺少左括号
    es = statement(); // 语句
    if (es > 0) return es;
    printf("%s %s\n", token, token1);
    if (strcmp(token, "while")) return 12; //缺少while

    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
    printf("%s %s\n", token, token1);
    if (strcmp(token, "(")) return 5; // 缺少左括号
    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
    printf("%s %s\n", token, token1);

    es = expression(); // 表达式
    if (es > 0) return es;
    label2 = labelp++;
    fprintf(fout, "        BRF LABEL%d\n", label2);
    fprintf(fout, "        BR LABEL%d\n", label1);

    if (strcmp(token, ")")) return 6; // 缺少右括号
    if (es > 0) return es;
    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
    printf("%s %s\n", token, token1);
    fprintf(fout, "LABEL%d:\n", label2); // 设置label2标号
    return es;
}

// <while语句>::=while(<表达式>)<语句>
// <while_stat>::=while(<expr>)<statement >
// <while_stat>::=while @SET↑labellabel1(<expression>) @BRF↑label2
//                 <statement >@BR↓label1 @SETlabel↓label2
// 动作解释如下：
// @SETlabel↑label1：设置标号label1
// @BRF↑label2 ：输出 BRF label2,
// @BR↓label1：输出 BR label1,
// @SETlabel↓label2：设置标号label2
int while_stat() {
    int es = 0, label1, label2;
    label1 = labelp++;
    fprintf(fout, "LABEL%d:\n", label1); // 设置label1标号
    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
    printf("%s %s\n", token, token1);
    if (strcmp(token, "(")) return 5; // 缺少左括号
    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
    printf("%s %s\n", token, token1);
    es = expression();
    if (es > 0) return es;
    if (strcmp(token, ")")) return 6; // 缺少右括号

    label2 = labelp++;
    fprintf(fout, "        BRF LABEL%d\n", label2);
    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
    printf("%s %s\n", token, token1);
    es = statement();
    if (es > 0) return es;
    fprintf(fout, "        BR LABEL%d\n", label1);
    fprintf(fout, "LABEL%d:\n", label2); // 设置label2标号
    return es;
}

// <for语句>::=for(<表达式>;<表达式>;<表达式>)<语句>
// <for_stat>::=for(<expr>,<expr>,<expr>)<statement>
// <for_stat>::=for (<expression>;
// @SETlabel↑label1< expression >@BRF↑label2@BR↑label3;
// @SETlabel↑label4 < expression >@BR↓label1)
// @SETlabel↓label3 <语句 >@BR↓label4@SETlabel↓label2
// 动作解释：
//    @SETlabel↓label1：设置标号label1
//    @BRF↑label2 ：输出 BRF label2,
//    @BR↑label3：输出 BR label3,
//    @SETlabel↓label4：设置标号label4
//    @BR↑label1：输出 BR label1,
//    @SETlabel↓label3：设置标号label3
//    @BR↑label4：输出 BR label4,
//    @SETlabel↓label2：设置标号label2
int for_stat() {
    int es = 0, label1, label2, label3, label4;
    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
    printf("%s %s\n", token, token1);
    if (strcmp(token, "(")) return 5; // 缺少左括号
    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
    printf("%s %s\n", token, token1);
    es = expression();
    if (es > 0) return es;
    if (strcmp(token, ";")) return 4; //缺少分号

    label1 = labelp++;
    fprintf(fout, "LABEL%d:\n", label1); // 设置label1标号
    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
    printf("%s %s\n", token, token1);
    es = expression();
    if (es > 0) return es;
    label2 = labelp++;
    fprintf(fout, "        BRF LABEL%d\n", label2);
    label3 = labelp++;
    fprintf(fout, "        BR LABEL%d\n", label3);
    if (strcmp(token, ";")) return 4; // 缺少分号

    label4 = labelp++;
    fprintf(fout, "LABEL%d:\n", label4); // 设置label4标号
    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
    printf("%s %s\n", token, token1);
    es = expression();
    if (es > 0) return es;
    fprintf(fout, "        BR LABEL%d\n", label1);
    if (strcmp(token, ")")) return 6; // 缺少右括号

    fprintf(fout, "LABEL%d:\n", label3); // 设置label3标号
    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
    printf("%s %s\n", token, token1);
    es = statement();
    if (es > 0) return es;
    fprintf(fout, "        BR LABEL%d\n", label4);
    fprintf(fout, "LABEL%d:\n", label2); // 设置label2标号
    return es;
}

// <read_语句>::=read<变量>;
// <read_stat>::=read ID;
// <read_stat>::=read ID↑n LOOK↓n↑d @IN@STI↓d;
// 动作解释：
// @LOOK↓n↑d:查符号表n，给出变量地址d; 没有，变量没定义
// @IN：输出IN
// @STI↓d：输出指令代码STI d
int read_stat() {
    int es = 0, address;
    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
    printf("%s %s\n", token, token1);
    if (strcmp(token, "ID")) return 3; // 缺少标识符

    es = lookup(token1, &address);
    if (es > 0) return es;
    fprintf(fout, "        IN   \n");
    fprintf(fout, "        STO   %d\n", address);
    fprintf(fout, "        POP\n");

    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
    printf("%s %s\n", token, token1);
    if (strcmp(token, ";")) return 4; // 缺少分号
    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
    printf("%s %s\n", token, token1);
    return es;
}

// <write_语句>::=write <表达式>;
// <write_stat>::=write <expression>;
// <write_STR>::write <STR>;
// 动作解释：
// @ OUT：输出 OUT
int write_stat() {
    int es = 0;
    fscanf(fin, "%d %s ", &wrow, token);
    printf("%s ", token);
    if (strcmp(token, "STR") == 0) { // 输出字符串
        fgets(token1, 1024, fin);
        printf("%s", token1);
        fprintf(fout, "        OUTS %s", token1); // 由于字符串不参与运算，单独考虑，定义OUTS为输出字符串指令
        fscanf(fin, "%d %s %s\n", &wrow, token, token1);
        printf("%s %s\n", token, token1);
        if (strcmp(token, ";")) return 4; // 缺少分号
        // fprintf(fout,"        OUT\n");
        fscanf(fin, "%d %s %s\n", &wrow, token, token1);
        printf("%s %s\n", token, token1);
        return es;
    }
    fscanf(fin, "%s", &token1);
    printf("%s\n", token1);
    es = expression();
    if (es > 0) return es;
    if (strcmp(token, ";")) return 4; // 缺少分号
    fprintf(fout, "        OUT\n");
    fscanf(fin, "%d %s %s\n", &wrow, token, token1);
    printf("%s %s\n", token, token1);
    return es;
}

// <表达式语句>::=<<表达式>;|;
// <expression_stat>::=<expression>;|;
int expression_stat() {
    int es = 0;
    if (strcmp(token, ";") == 0) {
        fscanf(fin, "%d %s %s\n", &wrow, token, token1);
        printf("%s %s\n", token, token1);
        return es;
    }
    es = expression();
    if (es > 0) return es;
    if (strcmp(token, ";") == 0) {
        fscanf(fin, "%d %s %s\n", &wrow, token, token1);
        printf("%s %s\n", token, token1);
        return es;
    } else {
        return 4; //缺少分号
    }
}

// <表达式>::=<标识符>=<布尔表达式>|<布尔表达式>
// <expr>::=ID=<bool_expr>|<bool_expr>
// <expression>::=ID↑n@LOOK↓n↑d@ASSIGN=<bool_expr>@STO↓d |<bool_expr>
int expression() {
    int es = 0, fileadd;
    char token2[MAXLENGTH + 2], token3[MAXLENGTH + 2];
    if (strcmp(token, "ID") == 0) {
        fileadd = ftell(fin); // 记住当前文件位置
        fscanf(fin, "%d %s %s\n", &wrow, token2, token3);
        printf("%s %s\n", token2, token3);

        if (strcmp(token2, "=") == 0) { //'='
            int address;
            es = lookup(token1, &address);
            if (es > 0) return es;
            fscanf(fin, "%d %s %s\n", &wrow, token, token1);
            printf("%s %s\n", token, token1);
            es = bool_expr();
            if (es > 0) return es;
            fprintf(fout, "        STO %d\n", address);
            fprintf(fout, "        POP\n");
        } else { //"=="
            fseek(fin, fileadd, 0); // 若非'='则文件指针回到'='前的标识符
            es = bool_expr();
            if (es > 0) return es;
        }
    } else {
        es = bool_expr();
    }
    return es;
}

// <布尔表达式>::=<算术表达式>|<算术表达式>(>|<|>=|<=|==|!=)<算术表达式>
// <bool_expr>::=<additive_expr>|< additive_expr >(>|<|>=|<=|==|!=)< additive_expr >
// <bool_expr>::=<additive_expr>
// |< additive_expr >><additive_expr>@GT
// |< additive_expr ><<additive_expr>@LES
// |< additive_expr >>=<additive_expr >@GE
// |< additive_expr ><=< additive_expr >@LE
// |< additive_expr >==< additive_expr >@EQ
// |< additive_expr >!=< additive_expr >@NOTEQ
int bool_expr() {
    int es = 0;
    es = additive_expr();
    if (es > 0) return es;
    if (strcmp(token, ">") == 0 || strcmp(token, ">=") == 0 || strcmp(token, "<") == 0 ||
        strcmp(token, "<=") == 0 || strcmp(token, "==") == 0 || strcmp(token, "!=") == 0) {
        char token2[MAXLENGTH + 2];
        strcpy(token2, token); // 保存运算符
        fscanf(fin, "%d %s %s\n", &wrow, token, token1);
        printf("%s %s\n", token, token1);
        es = additive_expr();
        if (es > 0) return es;

        if (strcmp(token2, ">") == 0) fprintf(fout, "        GT\n");
        if (strcmp(token2, ">=") == 0) fprintf(fout, "        GE\n");
        if (strcmp(token2, "<") == 0) fprintf(fout, "        LES\n");
        if (strcmp(token2, "<=") == 0) fprintf(fout, "        LE\n");
        if (strcmp(token2, "==") == 0) fprintf(fout, "        EQ\n");
        if (strcmp(token2, "!=") == 0) fprintf(fout, "        NOTEQ\n");
    }
    return es;
}

// <算术表达式>::=<项>{(+|-)<项>}
// <additive_expr>::=<term>{(+|-)< term >}
// < additive_expr>::=<term>{(+< term >@ADD |-<项>@SUB)}
int additive_expr() {
    int es = 0;
    es = term();
    if (es > 0) return es;
    while (strcmp(token, "+") == 0 || strcmp(token, "-") == 0) {
        char token2[MAXLENGTH + 2];
        strcpy(token2, token);
        fscanf(fin, "%d %s %s\n", &wrow, token, token1);
        printf("%s %s\n", token, token1);
        es = term();
        if (es > 0) return es;

        if (strcmp(token2, "+") == 0) fprintf(fout, "        ADD\n");
        if (strcmp(token2, "-") == 0) fprintf(fout, "        SUB\n");
    }
    return es;
}

// <项>::=<因子>{(*|/)<因子>}
// < term >::=<factor>{(*| /)< factor >}
// < term >::=<factor>{(*< factor >@MULT | /< factor >@DIV)}
int term() {
    int es = 0;
    es = factor();
    if (es > 0) return es;
    while (strcmp(token, "*") == 0 || strcmp(token, "/") == 0 || strcmp(token, "%") == 0) {
        char token2[MAXLENGTH + 2];
        strcpy(token2, token);
        fscanf(fin, "%d %s %s\n", &wrow, token, token1);
        printf("%s %s\n", token, token1);
        es = factor();
        if (es > 0) return es;

        if (strcmp(token2, "*") == 0) fprintf(fout, "        MULT\n");
        if (strcmp(token2, "/") == 0) fprintf(fout, "        DIV\n");
        if (strcmp(token2, "%") == 0) fprintf(fout, "        MOD\n");
    }
    return es;
}

// <因子>::=(<算术表达式>)|<标识符>|<无符号整数>
// < factor >::=(<additive_expr>)| ID|NUM
// < factor >::=(< expression >)| ID↑n@LOOK↓n↑d@LOAD↓d |NUM↑i@LOADI↓i
int factor() {
    int es = 0;
    if (strcmp(token, "(") == 0) {
        fscanf(fin, "%d %s %s\n", &wrow, token, token1);
        printf("%s %s\n", token, token1);
        es = expression(); // 表达式
        if (es > 0) return es;
        if (strcmp(token, ")")) return 6; // 缺少右括号
        fscanf(fin, "%d %s %s\n", &wrow, token, token1);
        printf("%s %s\n", token, token1);
    } else {
        if (strcmp(token, "ID") == 0) {
            int address;
            es = lookup(token1, &address); // 查符号表获取地址
            if (es > 0) return es; // 变量没声明
            fprintf(fout, "        LOAD %d\n", address);
            fscanf(fin, "%d %s %s\n", &wrow, token, token1);
            printf("%s %s\n", token, token1);
            return es;
        } else if (strcmp(token, "NUM") == 0) {
            fprintf(fout, "        LOADI %s\n", token1);
            fscanf(fin, "%d %s %s\n", &wrow, token, token1);
            return es;
        } else {
            return 7; // 缺少操作数
        }
    }
    return es;
}