#include <map>
#include <string>
class VarTable
{
private:
    std::map<std::string, int> varMap;
    int labelP = 0;
    int dataP = 0;
public:
    int set(std::string key);
    int get(std::string key);
    int display();
};

