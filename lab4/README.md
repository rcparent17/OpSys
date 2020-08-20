This lab is an extension of lab 3. A list of changes is below.

* Priority scheduling has been implemented instead of round robin
* The scheduler no longer prints what processes it selects
* A new command (`chpr`, or "change priority") has been added
    * You run the command like `chpr pid priority`, where pid is the process ID of the process you want to change the priority of and priority is the priority value (ints 1-20, 1 is the highest priority and 20 is the lowest) you want to give the process. 
