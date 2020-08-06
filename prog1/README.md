### Program 1
#### Reilly Parent

This is the first program for CS-451 (Operating Systems). Below are descriptions of the source files and what they do.

* `Makefile`
  * Running `make` will compile all of the programs and put them in the bin/ directory (it will be made if it doesn't exist).
  * You can also compile certain elements individually with the commands `make shell`, `make wc`, `make cat`, or `make uniq`.
* `my-shell.c`
  * A really simple shell program. It has 3 commands that it can run:
    * my-cat - runs `my-cat.c` - behaves like the linux command 'cat'. Takes in a file as a command line argument and prints the contents of that file onto the terminal.
    * my-uniq - runs `my-uniq.c` - behaves similar to my-cat, but will not print consecutive identical lines, so it only prints the unique lines.
    * my-wc - runs `my-wc.c` - takes in a file as a command line argument and prints out how many words and lines are in the file.
  * Piping (|) is also something you can do in my-shell. It behaves exactly like piping in linux, but there is a limit to 2 pipes per command (however, a 2nd pipe causes the program to hang right now).
