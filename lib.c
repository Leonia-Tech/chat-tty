#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include "lib.h"

pid_t proc_find(const char* name)
{
    DIR* dir;
    struct dirent* ent;
    char* endptr;
    char buf[512];

    if (!(dir = opendir("/proc"))) {
        perror("can't open /proc");
        return -1;
    }

    while((ent = readdir(dir)) != NULL) {
        /* if endptr is not a null character, the directory is not
         * entirely numeric, so ignore it */
        long lpid = strtol(ent->d_name, &endptr, 10);
        if (*endptr != '\0') {
            continue;
        }

        /* try to open the cmdline file */
        snprintf(buf, sizeof(buf), "/proc/%ld/cmdline", lpid);
        FILE* fp = fopen(buf, "r");

        if (fp) {
            if (fgets(buf, sizeof(buf), fp) != NULL) {
                /* check the first token in the file, the program name */
                char* first = strtok(buf, " ");
                if (!strcmp(first, name)) {
                    fclose(fp);
                    closedir(dir);
                    return (pid_t)lpid;
                }
            }
            fclose(fp);
        }

    }

    closedir(dir);
    return -1;
}

void empty(char* buff, int size)
{
	for(int i = 0; i < size; i++)
		buff[size] = 0;
}

void refresh(const char* filename)
{
	char chr;
	FILE* File;

	fputs(CLEAR, stdout);

	File = fopen(filename, "r");
	if(!File)
		return;

	while((chr = getc(File)) != EOF)
		putchar(chr);

	fclose(File);
}

int streq(char* str1, char* str2, int size)
{
    for(int i = 0; i < size; i++)
        if(str1[i] != str2[i])
            return 0;
    else return 1;
}