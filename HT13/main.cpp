//#include <stdio.h>
//
//extern int TESTscan();
//
//extern int TESTparse();
//
//extern int TESTmachine();
//
//int main() {
//    int es = 0;
//    es = TESTscan();
//    if (es > 0) {
//        printf("词法分析有错，编译停止！\n");
//    } else {
//        printf("词法分析成功！\n");
//        es = TESTparse();
//        if (es > 0) {
//            printf("语义分析有错，编译停止！\n");
//        } else {
//            printf("语义分析成功！\n");
//            es = TESTmachine();
//            if (es > 0) {
//                printf("启动模拟机失败\n");
//            }
//        }
//    }
//}