all: shell cat wc uniq

shell:
	if [ ! -d "bin" ]; then mkdir bin; fi
	gcc my-shell.c -Wall -Werror -o bin/my-shell

cat:
	if [ ! -d "bin" ]; then mkdir bin; fi
	gcc my-cat.c -Wall -Werror -o bin/my-cat

wc:
	if [ ! -d "bin" ]; then mkdir bin; fi
	gcc my-wc.c -Wall -Werror -o bin/my-wc

uniq:
	if [ ! -d "bin" ]; then mkdir bin; fi
	gcc my-uniq.c -Wall -Werror -o bin/my-uniq

clean:
	rm -rf bin
