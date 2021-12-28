/**(a)输入两个整数 x,y，输出其最大公约数。*/
{
    int x,y,temp;
    write "请输入x的值:";
    read x;
    write "请输入y的值:";
    read y;
    if(x < y){
        temp = x;
        x = y;
        y = temp;
    }
    /*辗转相除法*/
    while(x){
        temp = x%y;
        x = y;
        y = temp;
    }
    write y;
}