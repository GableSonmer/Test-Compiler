        LOADI 0
        STO 1
        POP
        LOADI 1
        STO 0
        POP
LABEL0:
        LOAD 1
        LOAD 0
        ADD
        STO 1
        POP
        LOAD 0
        LOADI 1
        ADD
        STO 0
        POP
        LOAD 0
        LOADI 10
        LE
        BRF LABEL1
        BR LABEL0
LABEL1:
        LOAD 1
        OUT
        STOP
