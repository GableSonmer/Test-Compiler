/*(c)求 Fibonacci 数列的前 20 个数。*/
{
    int a,b,i,temp;
    a = 1;
    b = 1;
    write "Fibonacci数列的前20个数:";
    write "=========================";
    for(i=1;i<=20;i=i+1){
        if(i==1){
            write a;
        }else if(i==2){
            write b;
        }else{
            temp = a + b;
            write temp;
            a = b;
            b = temp;
        }
    }
    write "=========================";
}