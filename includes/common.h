#ifndef COMMON_H

#define COMMON_H 1

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

struct token {
    std::string name;
    std::string lexeme;
};

struct production {
    char left_side;
    std::vector<char> right_side;
};

struct grammer {
    char start_symbol;
    std::unordered_set<char> terminals;
    std::vector<production*> prods;
};

#endif