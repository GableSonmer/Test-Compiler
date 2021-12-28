/*
文件 inyf5.t 测试 if、负操作、整数越界
*/
{
int a;
  a= - -123;
  if(if(a>100) a=a*a*a*a*a;)
    else { a=a/10; b=a/100; }
  write a;
write - - -b; }
