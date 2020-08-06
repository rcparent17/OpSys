### Lab 2
#### Reilly Parent

This lab assignment has 3 files, all described below:

`Makefile`:
* Running a simple `make` command will compile myshell, mysort, and both chat source files.
* You can also run `make shell`, `make sort`, or `make chat` to compile them individually.
* Running `make clean` will delete the binary directory.

`myshell.c`:
* Pretty much, it's a really basic shell. You can run 2 commands right now:
    * `sort`, which runs `mysort.c` assuming it's in the same directory. (example syntax: `sort numberfile.txt`)
    * `quit`, which exits the shell.
* You can redirect the output of sort by using the ">" operator and specifying a file. For example, `sort needsSorted.txt > sorted.txt`
    * If the command above were run, it would only execute if `sorted.txt` didn't already exist.

`mysort.c`:
* This program reads in a text file containing numbers (assumes no empty lines), and prints out that list, sorted
* Uses bubble sort.

chat:
Chat is composed of 2 files. When both files are ran on 2 seperate terminals at the same time (start `server` first), they will function as a chat application between 2 users. This is accomplished with a FIFO (named pipe) file.
* `server.c`:
    * First listens for a message from `client` by reading from the FIFO file, displays it, and lets the user then type in a message to send back from the client. Loops until the user enters 'quit'.
* `client.c`:
    * Lets the user type in a message, and sends it to `server` by writing to the FIFO file. Then listens for a message from `server` and displays it. Loops until the user enters 'quit'.
