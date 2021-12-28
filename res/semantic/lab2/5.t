        IN   
        STO   0
        POP
        IN   
        STO   1
        POP
        LOADI 0
        STO 2
        POP
        LOAD 0
        LOAD 1
        GT
        BRF LABEL0
        LOAD 0
        STO 1
        POP
        BR LABEL1
LABEL0:
LABEL1:
        LOADI 1
        STO 0
        POP
LABEL2:
        LOAD 0
        LOAD 1
        LES
        BRF LABEL3
        BR LABEL4
LABEL5:
        LOAD 0
        LOADI 1
        ADD
        STO 0
        POP
        BR LABEL2
LABEL4:
        LOAD 2
        LOAD 0
        ADD
        STO 2
        POP
        LOAD 0
        OUT
        BR LABEL5
LABEL3:
        LOAD 2
        OUT
        STOP
