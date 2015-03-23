run:	euler1xmm.s euler1long.s mini-c-unit.c
	gcc euler1xmm.s euler1long.s mini-c-unit.c
	./a.out

benchmark: euler1xmm.s euler1long.s benchmark.c
	gcc -Wall euler1xmm.s euler1long.s benchmark.c
	./a.out
