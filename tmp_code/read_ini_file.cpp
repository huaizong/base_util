#include <fstream>
#include <iterator>
#include <unistd.h>
#include <iostream>
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
        if(isspace(str[start]) == 0) {
            break;
        }
        start++;
    }
    while(start < end) {
        if(isspace(str[end]) == 0) {
            break;
        }
        end--;
    }
    str  = str.substr(start, end-start+1);
    return;
}
    
static bool str_startwiths(const string& str, const char *psz)
{
    if(psz == NULL) {
        return false;
    }
    //fprintf(stdout, "psz: %s, len: %ld, str: %s res: %ld\n", psz, strlen(psz), str.c_str(), strncmp(psz, str.c_str(), strlen(psz)));
    if(strncmp(psz, str.c_str(), strlen(psz)) == 0) {
        //cout << psz << "," << str << " match\n";
        return true;
    }
    return false;
}

bool IniFileOp::load(void)
{
    ifstream fin(m_path.c_str());
    string line;
    while (getline(fin, line)) {
        str_trim(line);
        if(line.length() == 0) {
            continue;
        } else if(str_startwiths(line, ";")) {
            continue;
        } else if(str_startwiths(line, "[") == true 
            && line[line.length()-1] == ']')
            {
                if(m_first_title == false) {
                    m_first_title = true;
                }
                m_cur_title = line.substr(1, line.length()-2);
        } else {
            if(m_first_title == false) {
                break;
            }
            map<string, string>& cur = m_content[m_cur_title];
            ssize_t pos = line.find("=");
            if(pos != -1) {
                string key = line.substr(0, pos);
                string val = line.substr(pos+1, line.length() - pos - 1);
                str_trim(key);
                str_trim(val);
                cur[key] = val;
            }
        }
    }
    m_init_ok = true;
    return m_init_ok;
} 

bool IniFileOp::get_val(const std::string &title, const std::string &sub_title, std::string &val)
{
    if(m_init_ok == false) {
        return false;
    }   
    map<string, map<string, string> >::const_iterator it_title = m_content.find(title);
    if(it_title != m_content.end()) {
        map<string, string>::iterator it_sub = m_content[title].find(sub_title);
        if(it_sub != m_content[title].end()) {
            val = it_sub->second;
            return true;
        }
    }
    return false;
    
}
int main(int argc, char **argv)
{
    IniFileOp ini_file(argv[1]); 
    ini_file.load(); 
    string val;
    ini_file.get_val("name", "name_me", val);
    cout << val << endl;
    return 0;
}
