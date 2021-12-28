        LOADI 1
        STO 0
        POP
        LOADI 1
        STO 1
        POP
        OUTS Fibonacci数列的前20个数:
        OUTS =========================
        LOADI 1
        STO 2
        POP
LABEL0:
        LOAD 2
        LOADI 20
        LE
        BRF LABEL1
        BR LABEL2
LABEL3:
        LOAD 2
        LOADI 1
        ADD
        STO 2
        POP
        BR LABEL0
LABEL2:
        LOAD 2
        LOADI 1
        EQ
        BRF LABEL4
        LOAD 0
        OUT
        BR LABEL5
LABEL4:
        LOAD 2
        LOADI 2
        EQ
        BRF LABEL6
        LOAD 1
        OUT
        BR LABEL7
LABEL6:
        LOAD 0
        LOAD 1
        ADD
        STO 3
        POP
        LOAD 3
        OUT
        LOAD 1
        STO 0
        POP
        LOAD 3
        STO 1
        POP
LABEL7:
LABEL5:
        BR LABEL3
LABEL1:
        OUTS =========================
        STOP
