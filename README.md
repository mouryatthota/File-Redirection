# File-Redirection

Compile the file using gcc "filename"
1. When the command is "exit", then the program terminates with exit(0).

2. The "read" command will do a file-redirection for a file to be read and to be written to a temporary file. For example, "read < hello.c" will read a file "hello.c" and write it to a temporary file ("temp.txt").

3. The "write" command will do a file-redirection for a file ("temp.txt") to be read and written to a file. For example, "write > out1.c" will read the save temp file "temp.txt" and write it to the file ("out1.c"). 

4. The "append" command has a file-redirection for a file (temp.txt) to be appended to a file. For example, "append >> out2.c" will read the save temp file "temp.txt" and write it to the file ("out2.c"). 

5. You may have two commands with a pipe. For example, "read < hello.c | write > hello2.c" will read hello.c file and write it to hello2.c via temp.txt file.

