#pragma once

#include <string>
#include <map>

class AssemblyMap {
private:
    // 汇编转换关系
    std::map<std::string, std::string> assembly;
public:
    int set(std::string key, std::string value);

    std::string get(std::string key);
};

