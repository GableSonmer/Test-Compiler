/*
文件 incf5.t 测试无词法错
*/
{
    int a;
    a=-123;
    if if(a>5) a=a+10;
     else a=a-10;
    write a;
}