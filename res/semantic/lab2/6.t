        LOADI 0
        STO 0
        POP
LABEL0:
        LOAD 0
        LOADI 10
        LES
        BRF LABEL1
        LOAD 0
        OUT
        OUTS Hello
        LOAD 0
        LOADI 1
        ADD
        STO 0
        POP
        BR LABEL0
LABEL1:
        STOP
