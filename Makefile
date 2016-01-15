spp:	euler1.spp euler6.spp euler7.spp euler10.spp euler25.spp sine.spp cond.spp mini-c-unit.c
	/usr/local/bin/node ../avxscript/main.js euler1.spp
	/usr/local/bin/node ../avxscript/main.js euler6.spp
	/usr/local/bin/node ../avxscript/main.js euler7.spp
	/usr/local/bin/node ../avxscript/main.js euler10.spp
	/usr/local/bin/node ../avxscript/main.js euler25.spp
	/usr/local/bin/node ../avxscript/main.js sine.spp
	/usr/local/bin/node ../avxscript/main.js cond.spp
	gcc euler1.s euler6.s euler7.s euler10.s euler25.s sine.s cond.s mini-c-unit.c
	./a.out

run:	sqrt.s mini-c-unit.c
	gcc sqrt.s mini-c-unit.c
	./a.out

benchmark: euler1xmm.s euler1long.s benchmark.c
	/usr/local/bin/node ../avxscript/main.js absolute.spp
	gcc -Wall absolute.s benchmark.c
	./a.out

intel: euler1intel.s benchmark2.c
	gcc -Wall euler1intel.c benchmark2.c
	./a.out
