#include "VarTable.h"
#include <iostream>
#include<string>

int VarTable::set(std::string key)
{
    // 检查是否包含重复元素
    if (varMap.count(key)) {
        throw "重复定义";
        return 22;
    }
    varMap.insert(std::make_pair(key, dataP++));
    return 0;
}


int VarTable::get(std::string key)
{
    std::map <std::string, int> ::iterator itf = varMap.find(key);
    return itf->second;
}

int VarTable::display()
{
    std::cout << "****************【打印符号表】****************" << std::endl;
    std::map<std::string, int>::reverse_iterator iter;
    for (iter = varMap.rbegin(); iter != varMap.rend(); iter++) {
        std::cout << iter->first << " " << iter->second << std::endl;
    }
    std::cout << "****************【结束】****************" << std::endl;
    return 0;
}