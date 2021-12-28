/*(b)输入一个整数，判断该整数代表的年份是否为闰年。*/
{
    int year;
    int flag;
    write "请输入年份:";
    read year;
    if(year<=0){
        write "输入年份必须是正整数!!!";
    }else{
        if(year%400==0){
            flag=1;
        }else{
            if(year%4 == 0){
                if(year%100==0){
                    flag = 0;
                }else{
                    flag = 1;
                }
            }
        }
        if(flag == 1){
            write "输入年份是闰年";
        }else{
            write "输入年份不是闰年";
        }
    }
}