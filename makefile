.PHONY: mmv lnl
all: mmv lnl
mmv: mmv.c
	${CC} -o mmv mmv.c
lnl: lnl.c
	${CC} -o lnl lnl.c