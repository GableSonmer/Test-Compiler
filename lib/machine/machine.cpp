#include "machine.h"

#define INF 0x3f3f3f3f
#define MAXFILENAME 100
#define MAXCODENUM 1000
#define MAXCODELENGTH 100
#define MAXDATANUM 1000
#define MAXLABELNUM 100
#define MAXSTACK 1000
//FILE *input;                              // 用于指向输入文件的指针
char assemblyFile[MAXFILENAME];               // 用于接收输入的文件名

int i, j, es;

int run(string in) {
    strcpy(assemblyFile, in.c_str());
    return TESTmachine();
}

int TESTmachine() {
    FILE *fin;
    char code[MAXCODENUM][MAXCODELENGTH];   // 代码存放数组
    int data[MAXDATANUM];                   // data[i]表示i地址的数值
    int label[MAXLABELNUM];                 // LABEL数组
    int stack[MAXSTACK], stacktop;          // 操作栈
    char lno[10];
    int codecnt;
    es = 0, i = 0, j = 0, stacktop = 0;
    memset(data, -INF, sizeof(data));
    if ((fin = fopen(assemblyFile, "r")) == NULL) {
        printf("\n打开%s错误!\n", assemblyFile);
        return 10;
    }
    codecnt = 0;
    i = fscanf(fin, "%s", code[codecnt]);
    while (!feof(fin)) { // 读入
        i = strlen(code[codecnt]) - 1;
        strncpy(lno, code[codecnt], 5);
        lno[5] = '\0';
        if (strcmp(lno, "OUTS") == 0) { // 带空格字符串处理
            codecnt++;
            getc(fin); // 跳过空格
            fgets(code[codecnt], 1024, fin);
            i = strlen(code[codecnt]) - 1;
            code[codecnt][i] = '\0';
        } else if (code[codecnt][i] == ':') { // LABEL，已消除":"冲突
            i = i - 5;
            strncpy(lno, &code[codecnt][5], i);
            lno[i] = '\0';
            label[atoi(lno)] = codecnt; // 用label数组记住每个标号的地址
            code[codecnt][0] = ':';
            code[codecnt][1] = '\0';
            strcat(code[codecnt], lno);
            j++;
        }
        codecnt++;
        i = fscanf(fin, "%s", &code[codecnt]);
    }
    fclose(fin);

    for (i = 0; i < codecnt; i++) { // 处理
        int l = strlen(code[i]);
        // printf("%d  %s  %d\n",i,code[i],l);
        if ((l > 1) && (code[i][1] == 'A')) {
            strncpy(lno, &code[i][5], l - 5);
            lno[i] = '\0';
            sprintf(code[i], "%d", label[atoi(lno)]);
//            itoa(label[atoi(lno)], code[i], 10);
        }
    }

    i = 0;
    while (i < codecnt) { // 运行
        if (strcmp(code[i], "LOAD") == 0) {        // LOAD D将D中的内容加载到操作数栈
            i++;
            stack[stacktop] = data[atoi(code[i])];
            stacktop++;
        } else if (strcmp(code[i], "LOADI") == 0) { // LOADI a将常量a压入操作数栈
            i++;
            stack[stacktop] = atoi(code[i]);
            stacktop++;
        } else if (strcmp(code[i], "STO") == 0) {   // STO D将操作数栈栈顶单元内容存入D，且栈顶单元内容保持不变
            i++;
            data[atoi(code[i])] = stack[stacktop - 1];
        } else if (strcmp(code[i], "STI") == 0) {   // STI D 将操作数栈栈顶单元内容存入D，且栈顶单元内容出栈
            i++;
            data[atoi(code[i])] = stack[stacktop - 1];
            stacktop--;
        } else if (strcmp(code[i], "POP") == 0) {   // POP出栈
            stacktop--;
        } else if (strcmp(code[i], "ADD") == 0) {   // ADD将次栈顶单元与栈顶单元内容出栈并相加，和置于栈顶
            stack[stacktop - 2] = stack[stacktop - 2] + stack[stacktop - 1];
            stacktop--;
        } else if (strcmp(code[i], "SUB") == 0) {   // SUB将次栈顶单元减去栈顶单元内容并出栈，差置于栈顶
            stack[stacktop - 2] = stack[stacktop - 2] - stack[stacktop - 1];
            stacktop--;
        } else if (strcmp(code[i], "MULT") == 0) {  // MULT将次栈顶单元与栈顶单元内容出栈并相乘，积置于栈顶
            stack[stacktop - 2] = stack[stacktop - 2] * stack[stacktop - 1];
            stacktop--;
        } else if (strcmp(code[i], "DIV") == 0) {   // DIV将次栈顶单元与栈顶单元内容出栈并相除，商置于栈顶
            stack[stacktop - 2] = stack[stacktop - 2] / stack[stacktop - 1];
            stacktop--;
        } else if (strcmp(code[i], "MOD") == 0) {   // MOD将次栈顶单元模栈顶单元内容并出栈，余数置于栈顶
            stack[stacktop - 2] = stack[stacktop - 2] % stack[stacktop - 1];
            stacktop--;
        } else if (strcmp(code[i], "BR") == 0) {    // BR lab无条件转移到lab
            i++;
            i = atoi(code[i]);
        } else if (strcmp(code[i], "BRF") == 0) {   // BRF lab检查栈顶单元逻辑值，若为假则转移到lab
            i++;
            if (stack[stacktop - 1] == 0) i = atoi(code[i]);
            stacktop--;
        } else if (strcmp(code[i], "EQ") == 0) {    // EQ将栈顶两单元做等于比较，并将结果真或假置于栈顶
            stack[stacktop - 2] = stack[stacktop - 2] == stack[stacktop - 1];
            stacktop--;
        } else if (strcmp(code[i], "NOTEQ") == 0) { // NOTEQ将栈顶两单元做不等于比较，并将结果真或假置于栈顶
            stack[stacktop - 2] = stack[stacktop - 2] != stack[stacktop - 1];
            stacktop--;
        } else if (strcmp(code[i], "GT") == 0) {    // GT次栈顶大于栈顶操作数，则栈顶置1，否则置0
            stack[stacktop - 2] = stack[stacktop - 2] > stack[stacktop - 1];
            stacktop--;
        } else if (strcmp(code[i], "LES") == 0) {   // LES次栈顶小于栈顶操作数，则栈顶置1，否则置0
            stack[stacktop - 2] = stack[stacktop - 2] < stack[stacktop - 1];
            stacktop--;
        } else if (strcmp(code[i], "GE") == 0) {    // GE次栈顶大于等于栈顶操作数，则栈顶置1，否则置0
            stack[stacktop - 2] = stack[stacktop - 2] >= stack[stacktop - 1];
            stacktop--;
        } else if (strcmp(code[i], "LE") == 0) {    // LE 次栈顶小于等于栈顶操作数，则栈顶置1，否则置0
            stack[stacktop - 2] = stack[stacktop - 2] <= stack[stacktop - 1];
            stacktop--;
        } else if (strcmp(code[i], "AND") == 0) {   // AND 将栈顶两单元做逻辑与运算，并将结果真或假置于栈顶
            stack[stacktop - 2] = stack[stacktop - 2] && stack[stacktop - 1];
            stacktop--;
        } else if (strcmp(code[i], "OR") == 0) {    // OR将栈顶两单元做逻辑或运算，并将结果真或假置于栈顶
            stack[stacktop - 2] = stack[stacktop - 2] || stack[stacktop - 1];
            stacktop--;
        } else if (strcmp(code[i], "NOT") == 0) {   // NOT将栈顶的逻辑值取反
            stack[stacktop - 1] = !stack[stacktop - 1];
        } else if (strcmp(code[i], "IN") == 0) {    // IN从标准输入设备读入一个整型数据，并入栈
            scanf("%d", &stack[stacktop]);
            stacktop++;
        } else if (strcmp(code[i], "OUT") == 0) {   // OUT将栈顶单元内容出栈，并输出到标准输出
            printf("%d\n", stack[stacktop - 1]);
//            printf("%d", stack[stacktop - 1]);
            stacktop--;
        } else if (strcmp(code[i], "OUTS") == 0) {  // OUTS 字符串输出
            i++;
            printf("%s\n", code[i]);
//            printf("%s", code[i]);
        } else if (strcmp(code[i], "STOP") == 0) {  // STOP 停止执行
            break;
        }
        i++;
    }
    return es;
}