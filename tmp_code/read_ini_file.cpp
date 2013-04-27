#include <fstream>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include "read_ini_file.h"

using namespace std;
IniFileOp::IniFileOp(const char *path):
m_path(path),
m_first_title(true)
{

}

bool IniFileOp::load(const char *path)
{
    m_path = path;
    return load();
}

static void str_trim(string &str)
{
    if(str.length() < 1) {
        return;
    }
    long start = 0;
    long end = str.length() - 1;
    while(start < end) {
        if(isblank(str[start]) == 0) {
            break;
        }
        start++;
    }
    while(start < end) {
        if(isblank(str[end]) == 0) {
            break;
        }
        end--;
    }
    str  = str.substr(start, end-start);
    return;
}
    
static bool str_startwiths(const string& str, const char *psz)
{
    if(psz == NULL) {
        return false;
    }
    if(strncmp(psz, str.c_str(), strlen(psz) == 0)) {
        return true;
    }
    return false;
}

bool IniFileOp::load(void)
{
    FILE *fp = fopen(m_path.c_str(), "r");
    char *line = NULL;
    size_t linecap = 0;
    ssize_t linelen;
    while ((linelen = getline(&line, &linecap, fp)) > 0) {
        string tmp =  line;
        str_trim(tmp);
        //fwrite(line, linelen, 1, stdout);
        fwrite(tmp.c_str(), tmp.length(), 1, stdout);
        tmp = "\n";
        fwrite(tmp.c_str(), tmp.length(), 1, stdout);
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
    IniFileOp ini_file(argv[1]); 
    ini_file.load(); 
    return 0;
}
