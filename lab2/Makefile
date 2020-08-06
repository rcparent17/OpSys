all: shell sort chat

chat: binDir
	gcc chat/server.c -Wall -Werror -o bin/server
	gcc chat/client.c -Wall -Werror -o bin/client

shell: binDir
	gcc myshell.c -Wall -Werror -o bin/myshell

sort: binDir
	gcc mysort.c -Wall -Werror -o bin/mysort

clean: 
	rm -rf bin/

binDir:
	if [ ! -d "bin" ]; then mkdir bin; fi
