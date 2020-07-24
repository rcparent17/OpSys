shell:
	if [ ! -d "bin" ]; then mkdir bin; fi
	gcc myShell.c -o bin/myShell

cat:
	if [ ! -d "bin" ]; then mkdir bin; fi
	gcc myCat.c -o bin/myCat

wc:
	if [ ! -d "bin" ]; then mkdir bin; fi
	gcc myWC.c -o bin/myWC

uniq:
	if [ ! -d "bin" ]; then mkdir bin; fi
	gcc myUniq.c -o bin/myUniq

all: shell cat wc uniq

clean:
	rm -f bin/*
