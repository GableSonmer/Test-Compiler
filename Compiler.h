#include "iostream"
#include "lib/lexical/lexical.h"
//#include "lib/syntax/syntax.h"
#include "lib/semantic/semantic.h"
#include "lib/machine/machine.h"

using namespace std;

class Compiler {
public:
    int lexicalAnalysis(string src, string output);

    int syntaxAnalysis(string in, string out);

    int semanticAnalysis(string in, string out);

    int runMachine(string assembly);
};