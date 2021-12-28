#include "Compiler.h"

int main() {
    int debug = 8;
    // 源代码
    string source = "../res/source/lab3/4.t";
    // 词法分析结果
    string lexical = "../res/lexical/lab3/4.t";
    // 语义分析结果
    string assembly = "../res/semantic/lab3/4.t";
    //词法分析
    Compiler compiler;
    int es = compiler.lexicalAnalysis(source, lexical);
    if (es > 0) {
        printf("词法有错误，编译失败");
    } else {
        printf("词法分析成功，开始进行语法分析.....\n");
        es = compiler.semanticAnalysis(lexical, assembly);
        if (es > 0) {
            printf("语法有错误");
        } else {
            printf("语法分析成功并生成汇编代码，使用虚拟机进行运行.....\n");
            compiler.runMachine(assembly);
        }
    }
    return 0;
}