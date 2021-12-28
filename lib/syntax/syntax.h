#include <string>

using namespace std;

void getNextLineToken();

void getFirstAndFollowSet();

int startSyntaxAnalysis(string in, string out);

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

int do_while_stat();

int for_stat();

int write_stat();

int read_stat();

int declaration_stat();

int declaration_list();

int statement_list();

int compound_stat();