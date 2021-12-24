#include "tools/lexical.h"
#include "tools/syntax.h"
#include "tools/semantic.h"

using namespace std;

class Compiler {
public:
    int lexicalAnalysis(string src, string output);

    int syntaxAnalysis(string in, string out);

    int semanticAnalysis(string in, string out);
};