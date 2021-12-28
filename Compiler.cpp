#include "Compiler.h"

int Compiler::lexicalAnalysis(string src, string output) {
    return startLexicalAnalysis(src, output);
}

int Compiler::syntaxAnalysis(string src, string out) {
    return 1;
//    return startSyntaxAnalysis(src, out);
}

int Compiler::semanticAnalysis(string src, string out) {
    return startSemanticAnalysis(src, out);
}

int Compiler::runMachine(string assembly) {
    return run(assembly);
}