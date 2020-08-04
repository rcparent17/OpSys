### Lab 2
#### Reilly Parent

This lab assignment has 3 files, all described below:

`Makefile`:
* Running a simple `make` command will compile myshell and mysort.
* You can also run `make shell` or `make sort` to compile them individually.
* Running `make clean` will delete the mysort and myshell binaries if they exist.

`myshell.c`:
* Pretty much, it's a really basic shell. You can run 2 commands right now:
    * `sort`, which runs `mysort.c` assuming it's in the same directory. (example syntax: `sort numberfile.txt`)
    * `quit`, which exits the shell.
* You can redirect the output of sort by using the ">" operator and specifying a file. For example, `sort needsSorted.txt > sorted.txt`
    * If the command above were run, it would only execute if `sorted.txt` didn't already exist.

`mysort.c`:
* This program reads in a text file containing numbers (assumes no empty lines), and prints out that list, sorted
* Uses bubble sort.
