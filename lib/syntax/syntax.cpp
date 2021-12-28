#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include "syntax.h"

#define MaxFileNameLength 100

using namespace std;

// 输入输出文件名
char inputFilename[MaxFileNameLength];
char outputFilename[MaxFileNameLength];

int startSyntaxAnalysis(string in, string out) {
    strcpy(inputFilename, in.c_str());
    strcpy(outputFilename, out.c_str());
    int es = TESTparse();
    getFirstAndFollowSet();
    return es;
}

int row, col;
//============================================
char token[20], token1[40];//token保存单词符号，token1保存单词值
FILE *fp; //用于指向输入输出文件的指针
map<string, int> state_, state_2, if_, while_, for_, read_, write_, fuhe_, express_, do_while;
int F[20];

void getNextLineToken() {
    fscanf(fp, "%s %s %d %d\n", token, token1, &row, &col);
}

//语法分析程序
int TESTparse() {
    int es = 0;
    if ((fp = fopen(inputFilename, "r")) == NULL) {
        printf("\n打开%s错误!\n", inputFilename);
        es = 10;
    }
    if (es == 0) {
        es = program();
    }
    printf("=====语法分析结果!======\n");
    switch (es) {
        case 0:
            printf("语法分析成功!\n");
            break;
        case 10:
            printf("打开文件%s失败!\n", inputFilename);
            break;
        case 1:
            printf("缺少{!\n");
            break;
        case 2:
            printf("缺少}!\n");
            break;
        case 3:
            printf("缺少标识符!\n");
            break;
        case 4:
            printf("少分号!\n");
            break;
        case 5:
            printf("缺少(!\n");
            break;
        case 6:
            printf("缺少)!\n");
            break;
        case 7:
            printf("缺少操作数!\n");
            break;

    }
    fclose(fp);
    return es;
}

//<程序>::={<声明序列><语句序列>}
//program::={<declaration_list><statement_list>}
int program() {
    int es = 0;
//    fscanf(fp, "%s %s\n", token, token1);//fscanf 遇到空格和换行时结束，空格时也结束
    getNextLineToken();
    printf("%s %s\n", token, token1);
    //判断是否'{' 相等就返回0
    if (strcmp(token, "{")) {
        es = 1;
        return es;
    }
//    fscanf(fp, "%s %s\n", &token, &token1);
    getNextLineToken();
    printf("%s %s\n", token, token1);
    es = declaration_list();//声明序列
    if (es > 0) return es;
    es = statement_list();//语句序列
    if (es > 0) return es;
    if (strcmp(token, "}"))//判断是否'}'
    {
        es = 2;
        return es;
    }
    return es;
}

//<声明序列>::=<声明序列><声明语句>|<声明语句>
//<declaration_list>::=
//<declaration_list><declaration_stat>|<declaration_stat>
//改成<declaration_list>::={<declaration_stat>}
int declaration_list() {
    F[2] = 1;
    int es = 0;
    while (strcmp(token, "int") == 0) {
        es = declaration_stat();
        if (es > 0) return es;
    }
    return es;
}

//<声明语句> ::=int <变量>；
//<declaration_stat>::=int ID;
int declaration_stat() {
    int es = 0, flag = 0;
//    fscanf(fp, "%s %s\n", &token, &token1);
    getNextLineToken();
    printf("%s %s\n", token, token1);
    if (strcmp(token, "ID")) return (es = 3);  //不是标识符
//    fscanf(fp, "%s %s\n", &token, &token1);
    getNextLineToken();
    printf("%s %s\n", token, token1);
    //	fscanf(fp,"%s %s\n",&token,&token1);
    //	printf("%s %s\n",token,token1);
    if (strcmp(token, ",") == 0) flag = 1;
    while (strcmp(token, ",") == 0) {
//        fscanf(fp, "%s %s\n", &token, &token1);
        getNextLineToken();
        printf("%s %s\n", token, token1);
        if (strcmp(token, "ID")) return (es = 3);
//        fscanf(fp, "%s %s\n", &token, &token1);
        getNextLineToken();
        printf("%s %s\n", token, token1);
    }//检测到逗号继续执行
//	if(flag==1)
//	{
//		fscanf(fp,"%s %s\n",&token,&token1);
//		printf("%s %s\n",token,token1);
//	}//当有逗号的时候就不必往前读了
    if (strcmp(token, ";")) {
        printf("%s ssas\n", token);
        return (es = 4);
    }    //少分号
//    fscanf(fp, "%s %s\n", &token, &token1);
    getNextLineToken();
    printf("%s %s\n", token, token1);
    return es;
}

//<语句序列>::=<语句序列><语句>|<语句>
//<statement_list>::=<statement_list><statement>|<statement>
//改成<statement_list>::={<statement>}
int statement_list() {
    int es = 0;
    while (strcmp(token, "}"))//检测到分号就结束
    {
        es = statement();
        if (es > 0) return es;
    }
    return es;
}

//<表达式语句>::=<<表达式>;|;
//<expression_stat>::=<expression>;|;
int expression_stat() {
    F[11] = 1;
    int es = 0;
    if (strcmp(token, ";") == 0) {
//        fscanf(fp, "%s %s\n", &token, &token1);
        getNextLineToken();
        printf("%s %s\n", token, token1);
        return es;
    }
    es = expression();
    if (es > 0) return es;
    if (es == 0 && strcmp(token, ";") == 0) {
//        fscanf(fp, "%s %s\n", &token, &token1);
        getNextLineToken();
        printf("%s %s\n", token, token1);
        return es;
    } else {
        es = 4;
        return es;//少分号
    }
}

//<语句>::=<if语句>|<while语句>|<for语句>|<read语句>
//         |<write语句>|<复合语句>|<表达式语句>
//<statement>::= <if_stat>|<while_stat>|<for_stat>
//               |<compound_stat> |<expression_stat>

int statement() {
    F[1] = 1;
    int es = 0;
    string str1;
    if (es == 0 && strcmp(token, "if") == 0) {
        str1 = token;
        state_[str1] = 1;
        es = if_stat();
    }//<IF语句>
    if (es == 0 && strcmp(token, "while") == 0) {
        str1 = token;
        state_[str1] = 1;
        es = while_stat();
    }//<while语句>
    if (es == 0 && strcmp(token, "for") == 0) {
        str1 = token;
        state_[str1] = 1;
        es = for_stat();
    }//<for语句>
    //可在此处添加do语句调用
    if (es == 0 && strcmp(token, "read") == 0) {
        str1 = token;
        state_[str1] = 1;
        es = read_stat();
    }//<read语句>
    if (es == 0 && strcmp(token, "write") == 0) {
        str1 = token;
        state_[str1] = 1;
        es = write_stat();
    }//<write语句>
    if (es == 0 && strcmp(token, "{") == 0) {
        str1 = token;
        state_[str1] = 1;
        es = compound_stat();
    }//<复合语句>
    if (es == 0 && (strcmp(token, "ID") == 0 || strcmp(token, "NUM") == 0 || strcmp(token, "(") == 0)) {
        str1 = token;
        state_[str1] = 1;
        es = expression_stat();
    }//<表达式语句>
    if (es == 0 && strcmp(token, "do") == 0) {
        str1 = token;
        state_[str1] = 1;
        es = do_while_stat();
    }
    return es;
}
//<IF 语句>::= if (<表达式>) <语句 > [else <语句 >]
//<IF_stat>::= if (<expr>) <statement > [else < statement >]

int if_stat() {
    F[3] = 1;
    int es = 0;  //if
//    fscanf(fp, "%s %s\n", &token, &token1);
    getNextLineToken();
    printf("%s %s\n", token, token1);
    if (strcmp(token, "(")) return (es = 5);  //少左括号
//    fscanf(fp, "%s %s\n", &token, &token1);
    getNextLineToken();
    printf("%s %s\n", token, token1);
    es = expression();
    if (es > 0) return es;
    if (strcmp(token, ")")) return (es = 6); //少右括号
//    fscanf(fp, "%s %s\n", &token, &token1);
    getNextLineToken();
    printf("%s %s\n", token, token1);
    es = statement();
    if (es > 0) return es;
    if (strcmp(token, "else") == 0)//else部分处理
    {
//        fscanf(fp, "%s %s\n", &token, &token1);
        getNextLineToken();
        printf("%s %s\n", token, token1);
        es = statement();
        if (es > 0) return es;
    }
    return es;
}

//<while语句>::=while(<表达式>) <语句>
//<while_stat>::= while (<expr >) < statement >
int while_stat() {
    F[4] = 1;
    int es = 0;
//    fscanf(fp, "%s %s\n", &token, &token1);
    getNextLineToken();
    printf("%s %s\n", token, token1);
    if (strcmp(token, "(")) return (es = 5);  //少左括号
//    fscanf(fp, "%s %s\n", &token, &token1);
    getNextLineToken();
    printf("%s %s\n", token, token1);
    es = expression();
    if (es > 0) return es;
    if (strcmp(token, ")")) return (es = 6); //少右括号
//    fscanf(fp, "%s %s\n", &token, &token1);
    getNextLineToken();
    printf("%s %s\n", token, token1);
    es = statement();
    return es;
}

// <do_while语句>::do{语句序列}while(表达式)
// <do_while_stat>::do{statement_list}while(expression)
int do_while_stat() {
    F[5] = 1;
    int es = 0;
    getNextLineToken();
    printf("%s %s\n", token, token1);
    es = statement();
    if (es){
        return es;
    }
    getNextLineToken();
    printf("%s %s\n", token, token1);
    //读取while
    if (strcmp(token, "while") == 0) {
        getNextLineToken();
        es = expression();
        if (es > 0) {
            return es;
        }
        //少分号
        if (strcmp(token, ";") != 0) {
            es = 4;
            return es;
        }
        getNextLineToken();
    }
    return es;
}

//<for语句>::=for(<表达式>;<表达式>;<表达式>) <语句 >
//<for_stat>::= for(<expr>,<expr>,<expr>)<statement>
int for_stat() {
    F[6] = 1;
    int es = 0;
//    fscanf(fp, "%s %s\n", &token, &token1);
    getNextLineToken();
    printf("%s %s\n", token, token1);
    if (strcmp(token, "(")) return (es = 5);  //少左括号
//    fscanf(fp, "%s %s\n", &token, &token1);
    getNextLineToken();
    printf("%s %s\n", token, token1);
    es = expression();
    if (es > 0) return es;
    if (strcmp(token, ";")) return (es = 4);  //少分号
//    fscanf(fp, "%s %s\n", &token, &token1);
    getNextLineToken();
    printf("%s %s\n", token, token1);
    es = expression();
    if (es > 0) return es;
    if (strcmp(token, ";")) return (es = 4);  //少分号
//    fscanf(fp, "%s %s\n", &token, &token1);
    getNextLineToken();
    printf("%s %s\n", token, token1);
    es = expression();
    if (es > 0) return es;
    if (strcmp(token, ")")) return (es = 6); //少右括号
//    fscanf(fp, "%s %s\n", &token, &token1);
    getNextLineToken();
    printf("%s %s\n", token, token1);
    es = statement();
    return es;

}

//<write_语句>::=write <表达式>;
//<write_stat>::=write <expression>;
int write_stat() {
    F[7] = 1;
    int es = 0;
//    fscanf(fp, "%s %s\n", &token, &token1);
    getNextLineToken();
    printf("%s %s\n", token, token1);
    if (strcmp(token, "STRING") == 0) {
        getNextLineToken();
        if (strcmp(token, ";")) return (es = 4);
        getNextLineToken();
        printf("%s %s\n", token, token1);
        return es;
    }
    es = expression();
    if (es > 0) return es;
    if (strcmp(token, ";")) return (es = 4);  //少分号
//    fscanf(fp, "%s %s\n", &token, &token1);
    getNextLineToken();
    printf("%s %s\n", token, token1);
    //	printf("%s ssd\n",token);
    return es;
}

//<read_语句>::=read <变量>;
//<read_stat>::=read ID;
int read_stat() {
    F[8] = 1;
    int es = 0;
//    fscanf(fp, "%s %s\n", &token, &token1);
    getNextLineToken();
    printf("%s %s\n", token, token1);
    if (strcmp(token, "ID")) return (es = 3);  //少标识符
//    fscanf(fp, "%s %s\n", &token, &token1);
    getNextLineToken();
    printf("%s %s\n", token, token1);
    if (strcmp(token, ";")) return (es = 4);  //少分号
//    fscanf(fp, "%s %s\n", &token, &token1);
    getNextLineToken();
    printf("%s %s\n", token, token1);
    return es;
}

//<复合语句>::={<语句序列>}
//<compound_stat>::={<statement_list>}
int compound_stat() {   //复合语句函数
    F[9] = 1;
    int es = 0;
//    fscanf(fp, "%s %s\n", &token, &token1);
    getNextLineToken();
    printf("%s %s\n", token, token1);
    es = statement_list();
    return es;
}


//<表达式>::=<标识符>=<布尔表达式>|<布尔表达式>
//<expr>::=ID=<bool_expr>|<bool_expr>

int expression() {
    F[10] = 1;
    int es = 0, fileadd;
    char token2[20], token3[40];
    int r, c;
    //	printf("%s\n",token);重复表示
    if (strcmp(token, "ID") == 0) {
        fileadd = ftell(fp);   //记住当前文件位置
        fscanf(fp, "%s %s %d %d\n", token2, token3, &r, &c);
        if (strcmp(token2, "=") == 0) printf("%s %s\n", token2, token3);//修改位

        if (es > 0) return es;
        if (strcmp(token2, "=") == 0)  //'='
        {
//            fscanf(fp, "%s %s\n", &token, &token1);
            getNextLineToken();
            printf("%s %s\n", token, token1);
            es = bool_expr();
        } else {
            fseek(fp, fileadd, 0); //若非'='则文件指针回到'='前的标识符
//			printf("%s %s\n",token,token1);
            es = bool_expr();
            if (es > 0) return es;
        }
    } else es = bool_expr();
    return es;
}

//<布尔表达式>::=<算术表达式>|<算术表达式>(>|<|>=|<=|==|!=)<算术表达式>
//<bool_expr>::=<additive_expr>
//           |< additive_expr >(>|<|>=|<=|==|!=)< additive_expr >

int bool_expr() {
    F[12] = 1;
    int es = 0;
    es = additive_expr();
    if (es > 0) return es;
    if (strcmp(token, ">") == 0 || strcmp(token, ">=") == 0
        || strcmp(token, "<") == 0 || strcmp(token, "<=") == 0
        || strcmp(token, "==") == 0 || strcmp(token, "!=") == 0) {
//        fscanf(fp, "%s %s\n", &token, &token1);
        getNextLineToken();
        printf("%s %s\n", token, token1);
        es = additive_expr();
        if (es > 0) return es;
    }
    return es;
}

//<算术表达式>::=<项>{(+|-)<项>}
//<additive_expr>::=<term>{(+|-)< term >}
int additive_expr() {
    F[13] = 1;
    int es = 0;
    es = term();
    if (es > 0) return es;
    while (strcmp(token, "+") == 0 || strcmp(token, "-") == 0) {
//        fscanf(fp, "%s %s\n", &token, &token1);
        getNextLineToken();
        printf("%s %s\n", token, token1);
        es = term();
        if (es > 0) return es;
    }
    return es;
}

//<项>::=<因子>{(*|/)<因子>}
//< term >::=<factor>{(*| /)< factor >}
int term() {
    F[14] = 1;
    int es = 0;
    es = factor();
    if (es > 0) return es;
    while (strcmp(token, "*") == 0 || strcmp(token, "/") == 0) {
//        fscanf(fp, "%s %s\n", &token, &token1);
        getNextLineToken();
        printf("%s %s\n", token, token1);
        es = factor();
        if (es > 0) return es;
    }
    return es;
}
//<因子>::=(<算术表达式>)|<标识符>|<无符号整数>
//< factor >::=(<additive_expr>)| ID|NUM

int factor() {
    F[15] = 1;
    int es = 0;

    if (strcmp(token, "(") == 0) {
//        fscanf(fp, "%s %s\n", &token, &token1);
        getNextLineToken();
        printf("%s %s\n", token, token1);
        es = expression();
        if (es > 0) return es;
        if (strcmp(token, ")")) return (es = 6); //少右括号
//        fscanf(fp, "%s %s\n", &token, &token1);
        getNextLineToken();
        printf("%s %s\n", token, token1);
    } else {

        if (strcmp(token, "ID") == 0 || strcmp(token, "NUM") == 0) {
//            fscanf(fp, "%s %s\n", &token, &token1);
            getNextLineToken();
            printf("%s %s\n", token, token1);
            return es;
        } else {
            es = 7;//缺少操作数
            return es;
        }
    }
    return es;
}

void getFirstAndFollowSet() {
    //program
    cout << "--<program>规则的FIRST集合：{ '{' }" << endl;
    cout << "--<program>规则的FOLLOW集合：{ '#' } " << endl;
    //statement
    if (F[1] == 1) {
        cout << "--<statement>规则的FIRST集合：{ ";
        map<string, int>::iterator iter;
        iter = state_.begin();
        for (iter = state_.begin(); iter != state_.end(); iter++) {
            cout << iter->first << " ";
        }
        cout << " }" << endl;
        cout << "--<statement>规则的FOLLOE集合：{ '}','#',';' }" << endl;
    }
    //int_stat
    if (F[2] == 1) {
        cout << "--<int_stat>规则的FIRST集合：{ 'int' }" << endl;
        cout << "--<int_stat>规则的FOLLOW集合：{ '}','#',';' } " << endl;
    }
    //if_stat
    if (F[3] == 1) {
        cout << "--<if_stat>规则的FIRST集合：{ 'if' }" << endl;
        cout << "--<if_stat>规则的FOLLOW集合：{ '}','#' ,';'} " << endl;
    }
    //while_stat
    if (F[4] == 1) {
        cout << "--<while_stat>规则的FIRST集合：{ 'while' }" << endl;
        cout << "--<while_stat>规则的FOLLOW集合：{ '}','#' ,';'} " << endl;
    }
    //do_while_stat
    if (F[5] == 1) {
        cout << "--<do_stat>规则的FIRST集合：{ 'do' }" << endl;
        cout << "--<do_stat>规则的FOLLOW集合：{'}', '#' ,';'} " << endl;
    }
    //for_stat
    if (F[6] == 1) {
        cout << "--<for_stat>规则的FIRST集合：{ 'for' }" << endl;
        cout << "--<for_stat>规则的FOLLOW集合：{ '}','#' ,';'} " << endl;
    }
    //write_stat
    if (F[7] == 1) {
        cout << "--<write_stat>规则的FIRST集合：{ 'write' }" << endl;
        cout << "--<write_stat>规则的FOLLOW集合：{'}' '#' ,';'} " << endl;
    }
    //read_stat
    if (F[8] == 1) {
        cout << "--<read_stat>规则的FIRST集合：{ 'read' }" << endl;
        cout << "--<read_stat>规则的FOLLOW集合：{ '}','#',';' } " << endl;
    }
    //compound_stat
    if (F[9] == 1) {
        cout << "--<compound_stat>规则的FIRST集合：{ '{' }" << endl;
        cout << "--<compound_stat>规则的FOLLOW集合：{ '}','#' } " << endl;
    }
    //expression_stat
    if (F[11] == 1) {
        cout << "--<expression_stat>规则的FIRST集合：{ '(','ID','NUM',';' }" << endl;
        cout << "--<expression_stat>规则的FOLLOW集合：{ '}','#',';' } " << endl;
    }
    //expression
    if (F[10] == 1) {
        cout << "--<expression>规则的FIRST集合：{ '(','ID','NUM' }" << endl;
        cout << "--<expression>规则的FOLLOW集合：{ ';' } " << endl;
    }
    //bool_expr
    if (F[12] == 1) {
        cout << "--<bool_expr>规则的FIRST集合：{'(','ID','NUM' }" << endl;
        cout << "--<bool_expr>规则的FOLLOW集合：{ ';' } " << endl;
    }
    //additive_expr
    if (F[13] == 1) {
        cout << "--<expression_stat>规则的FIRST集合：{ '(','ID','NUM' }" << endl;
        cout << "--<expression_stat>规则的FOLLOW集合：{ ';','>','<,','>=','<=','==','!=' } " << endl;
    }
    //term
    if (F[14] == 1) {
        cout << "--<term>规则的FIRST集合：{'(','ID','NUM'}" << endl;
        cout << "--<term>规则的FOLLOW集合：{ ';','>','<,','>=','<=','==','!=' ,'+','-' } " << endl;
    }
    //factor
    if (F[15] == 1) {
        cout << "--<factor>规则的FIRST集合：{'(','ID','NUM'}" << endl;
        cout << "--<factor>规则的FOLLOW集合：{';','>','<,','>=','<=','==','!=' ,'+','-','*','/','%'} " << endl;
    }
}