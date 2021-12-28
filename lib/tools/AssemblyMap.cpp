#include "assemblyMap.h"
#include <map>
#include <string>


int AssemblyMap::set(std::string key, std::string value)
{
    assembly.insert(std::make_pair(key, value));
    return 0;
}


std::string AssemblyMap::get(std::string key)
{
    std::map <std::string, std::string> ::iterator itf = assembly.find(key);
    return itf->second;
}
