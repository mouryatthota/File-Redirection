#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <unistd.h>

char *getinput(char *buffer, size_t buflen)
{
    printf("$$ ");
    return fgets(buffer, buflen, stdin);
}

void do_file_io(char *operation, char *file_name)
{
    FILE *fptr1, *fptr2;
    if (strcmp(operation, "read") == 0)
    {
        fptr1 = fopen(file_name, "r");
        if (fptr1 == NULL)
        {
            printf("Cannot open file %s \n", file_name);
            exit(EX_OK);
        }
        else
        {
            fptr2 = fopen("temp.txt", "w");
            char c = (char) fgetc(fptr1);
            while (c != EOF)
            {
                fputc(c, fptr2);
                c = (char) fgetc(fptr1);
            }
            fclose(fptr1);
            fclose(fptr2);
        }
    }

    if (strcmp(operation, "write") == 0)
    {
        fptr1 = fopen("temp.txt", "r");
        if (fptr1 == NULL)
        {
            printf("Cannot open file %s \n", file_name);
            exit(EX_OK);
        }
        else
        {
            fptr2 = fopen(file_name, "w");
            char c = (char) fgetc(fptr1);
            while (c != EOF)
            {
                fputc(c, fptr2);
                c = (char) fgetc(fptr1);
            }
            fclose(fptr1);
            fclose(fptr2);
        }
    }

    if (strcmp(operation, "append") == 0)
    {
        fptr1 = fopen("temp.txt", "r");
        if (fptr1 == NULL)
        {
            printf("Cannot open file %s \n", file_name);
            exit(EX_OK);
        }
        else
        {
            fptr2 = fopen(file_name, "a");
            char c = (char) fgetc(fptr1);
            while (c != EOF)
            {
                fputc(c, fptr2);
                c = (char) fgetc(fptr1);
            }
            fclose(fptr1);
            fclose(fptr2);
        }
    }

}
int main(int argc, char **argv)
{
    char buf[1024];
    pid_t pid;
    int status;

    char *split_buf[20], *pipe_split[30];
    char **next;

    while (getinput(buf, sizeof(buf)))
    {
        buf[strlen(buf) - 1] = '\0';

        if (strcmp(buf, "exit") == 0)
        {
            exit(EX_OK);
        }
        /* Place your code to check "exit". If so, then exit */

        if ((pid = fork()) == -1)
        {
            fprintf(stderr, "shell: can't fork: %s\n", strerror(errno));
            continue;
        }
        else if (pid == 0)
        {
            next = pipe_split;
            char *cmds = strtok(buf, "|");
            while(cmds != NULL)
            {
                *next++ = cmds;
                cmds = strtok(NULL, "|");
            }
            *next = NULL;
            free(cmds);

            for(int i = 0; pipe_split[i] != NULL; i++)
            {
                next = split_buf;
                char *tokens = strtok(pipe_split[i], " ");
                while (tokens != NULL)
                {
                    *next++ = tokens;
                    tokens = strtok(NULL, " ");
                }
                *next = NULL;
                free(tokens);

                // For read operation
                if (strcmp(split_buf[0], "read") == 0)
                {
                    if (strcmp(split_buf[1], "<") == 0)
                    {
                        do_file_io(split_buf[0], split_buf[2]);
                    }
                }

                if (strcmp(split_buf[0], "write") == 0)
                {
                    if (strcmp(split_buf[1], ">") == 0)
                    {
                        do_file_io(split_buf[0], split_buf[2]);
                    }
                }

                if (strcmp(split_buf[0], "append") == 0)
                {
                    if (strcmp(split_buf[1], ">>") == 0)
                    {
                        do_file_io(split_buf[0], split_buf[2]);
                    }
                }
            }
            exit(EX_OK);
        }

        if ((pid = waitpid(pid, &status, 0)) < 0)
        {
            fprintf(stderr, "shell: waitpid error: %s\n", strerror(errno));
        }
    }
    exit(EX_OK);
}

