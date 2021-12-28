        OUTS 请输入年份:
        IN   
        STO   0
        POP
        LOAD 0
        LOADI 0
        LE
        BRF LABEL0
        OUTS 输入年份必须是正整数!!!
        BR LABEL1
LABEL0:
        LOAD 0
        LOADI 400
        MOD
        LOADI 0
        EQ
        BRF LABEL2
        LOADI 1
        STO 1
        POP
        BR LABEL3
LABEL2:
        LOAD 0
        LOADI 4
        MOD
        LOADI 0
        EQ
        BRF LABEL4
        LOAD 0
        LOADI 100
        MOD
        LOADI 0
        EQ
        BRF LABEL5
        LOADI 0
        STO 1
        POP
        BR LABEL6
LABEL5:
        LOADI 1
        STO 1
        POP
LABEL6:
        BR LABEL7
LABEL4:
LABEL7:
LABEL3:
        LOAD 1
        LOADI 1
        EQ
        BRF LABEL8
        OUTS 输入年份是闰年/n
        BR LABEL9
LABEL8:
        OUTS 输入年份不是闰年/n
LABEL9:
LABEL1:
        STOP
