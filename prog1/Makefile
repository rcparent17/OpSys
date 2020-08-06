all: shell cat wc uniq

shell: binDir
	gcc my-shell.c -Wall -Werror -o bin/my-shell

cat: binDir
	gcc my-cat.c -Wall -Werror -o bin/my-cat

wc: binDir
	gcc my-wc.c -Wall -Werror -o bin/my-wc

uniq: binDir
	gcc my-uniq.c -Wall -Werror -o bin/my-uniq

clean:
	rm -rf bin

binDir:
	if [ ! -d "bin" ]; then mkdir bin; fi
