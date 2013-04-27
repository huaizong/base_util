#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>

bool load(const char *file_path)
{
    FILE *fp = fopen(file_path, "r");
    char *line = NULL;
    size_t linecap = 0;
    ssize_t linelen;
    while ((linelen = getline(&line, &linecap, fp)) > 0) {
        fwrite(line, linelen, 1, stdout);
    }
    if(line) {
        free(line);
        line = NULL;
    }
    fclose(fp);
    return false;
} 

int main(int argc, char **argv)
{
    load(argv[1]); 
    return 0;
}
