        OUTS 请输入x的值:
        IN   
        STO   0
        POP
        OUTS 请输入y的值:
        IN   
        STO   1
        POP
        LOAD 0
        LOAD 1
        LES
        BRF LABEL0
        LOAD 0
        STO 2
        POP
        LOAD 1
        STO 0
        POP
        LOAD 2
        STO 1
        POP
        BR LABEL1
LABEL0:
LABEL1:
LABEL2:
        LOAD 0
        BRF LABEL3
        LOAD 0
        LOAD 1
        MOD
        STO 2
        POP
        LOAD 1
        STO 0
        POP
        LOAD 2
        STO 1
        POP
        BR LABEL2
LABEL3:
        LOAD 1
        OUT
        STOP
