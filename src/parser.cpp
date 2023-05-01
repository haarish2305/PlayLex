#include "../includes/parser.h"
#include <iostream>

parser* parser_factory::get_parser(grammer *grammer, const unsigned int parser_type) {

}

ll1_parser::ll1_parser(grammer *grammer) : parser(grammer) {}

void ll1_parser::compute_first (char symbol) {
    std::unordered_set<char> symbols;
    bool contains_epsilon = false;
    for (production *prod: m_grammer->prods) {
        if (prod->left_side != symbol) continue;
        int i = 0;
        while (i < prod->right_side.size()) {
            if (m_grammer->terminals.find(prod->right_side[i]) != m_grammer->terminals.end()) {
                first[symbol].insert(prod->right_side[i]);
                break;
            }

            if (prod->right_side[i] == 'e') {
                contains_epsilon = true;
                break;
            }

            compute_first(prod->right_side[i]);
            symbols.insert(prod->right_side[i]);
            
            if (first[prod->right_side[i]].find('e') != first[prod->right_side[i]].end()) {
                if (i == prod->right_side.size() - 1) contains_epsilon = true;
                i++;
            }
            else break;
        }
    }

    for (char ch: symbols) {
        for (char c: first[ch]) {
            if (c == 'e') continue;
            first[symbol].insert(c);
        }
    }

    if (contains_epsilon) first[symbol].insert('e');
}

bool ll1_parser::check_if_ll1_grammer () {

}