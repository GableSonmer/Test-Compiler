/*
文件 inyf7.t 测试 do-while
*/
    {
      int i,sum;
      sum=0;
      i=1;
      do
      {
        sum=sum+i;
       i=i+1;
      }while(i<=10);
      write sum;
}