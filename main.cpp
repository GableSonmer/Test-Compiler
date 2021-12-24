#include "iostream"
#include "Compiler.h"

using namespace std;

int main() {
    // 源代码
    string source = "res/source/incf1.T";
    // 词法分析结果
    string lexical = "res/lexical/incf1.T";
    // 语义分析结果
    string outFileName = "res/semantic/incf1.T";
    //词法分析
    Compiler compiler;
    cout << compiler.lexicalAnalysis(source, lexical) << endl;
    cout << compiler.syntaxAnalysis(source, lexical) << endl;
    cout << compiler.semanticAnalysis(source, lexical) << endl;
    return 0;
}