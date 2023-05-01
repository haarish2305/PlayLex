#ifndef PARSER_H

#define PARSER_H 1
#define LL1_PARSER 2
#include "common.h"

class parser {
protected:
    grammer *m_grammer;
public:
    parser (grammer *grammer) { m_grammer = grammer; }
};

class ll1_parser : public parser {
private:
public:
    ll1_parser(grammer *grammer);
    std::unordered_map<char, std::unordered_set<char>> first, follow;
    void compute_first (char symbol);
    void compute_follow (char symbol);
    bool check_if_ll1_grammer ();
};

class parser_factory {
public:
    static parser* get_parser(grammer *grammer, const unsigned int parser_type);
};

#endif