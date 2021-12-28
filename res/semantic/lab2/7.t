        LOADI 10
        STO 0
        POP
        LOADI 0
        STO 3
        POP
        LOADI 1
        STO 3
        POP
LABEL0:
        LOAD 3
        LOAD 0
        LES
        BRF LABEL1
        BR LABEL2
LABEL3:
        LOAD 3
        LOADI 1
        ADD
        STO 3
        POP
        BR LABEL0
LABEL2:
        OUTS sos
        BR LABEL3
LABEL1:
        STOP
