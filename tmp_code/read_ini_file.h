#pragma once
#include <map>
#include <string>

class IniFileOp {
 public:
    IniFileOp(const char *path);
    bool load(const char *path);
    bool load(void);
    bool get_val(const std::string &title, const std::string &sub_title);
private:
    bool m_init_ok;
    bool m_first_title;
    std::string m_path;
    std::map<std::string, std::map<std::string, std::string> > m_content;
};
