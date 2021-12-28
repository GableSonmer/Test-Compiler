/*
文件 inyf81.t 测试 for,文件尾 */
{
    int i, j, sum;
     read i;
     read j;
sum=0;
      if(i>j) j=i;
      for(i=1;i<j;i=i+1){
      sum=sum+i;
      write i;
      }
      write sum;
      }
