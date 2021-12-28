#include "string"
#include <cstdio>
#include <string>

#define MAXVARTABLEP 500 // 定义符号表的容量
#define MAXFILENAME 100  // 文件名最大长度
#define MAXLENGTH 40     // 字符串最大长度

using namespace std;

int name_def(char *name);

int lookup(char *name, int *paddress);

void getNextLineToken();

int startSemanticAnalysis(string in, string out);

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