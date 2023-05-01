#ifndef LEXER_H

#define LEXER_H 1

#include <unordered_map>
#include <vector>
#include <queue>
#include "common.h"

class lexer {
private:
    std::unordered_map<std::string, std::string> m_rules;
public:
    lexer (std::unordered_map<std::string, std::string> rules) {
        m_rules = rules;
    }
    virtual std::vector<token*> get_tokens (std::string &char_stream) = 0;
};

class lexer_algo1 : public  lexer {
private:
    int get_previous_index_of_char (std::string &str, char before_seing, char ch, int curr_index) {
        while (curr_index >= 0 && str[curr_index] != before_seing) {
            if (str[curr_index] == ch) return curr_index;
            curr_index--;
        }
        return -1;
    }
public:
    int get_longest_match (int index, std::string &stream, std::pair<std::string, std::string> &rule);
    lexer_algo1 (std::unordered_map<std::string, std::string> rules);
    virtual std::vector<token*> get_tokens (std::string &char_stream);
};

#endif