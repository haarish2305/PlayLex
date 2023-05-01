#include "../includes/lexer.h"
#include <iostream>

lexer_algo1::lexer_algo1 (std::unordered_map<std::string, std::string> rules) : lexer (rules) {
}

int lexer_algo1::get_longest_match (int index, std::string &stream, std::pair<std::string, std::string> &rule) {
    std::string pattern = rule.second;
    int j = 0;
    int last_star_index = -1, last_matched_index = -1;
    while (1) {
        if (j >= pattern.size()) {
            last_matched_index = index - 1;
            j = pattern.size() - 1;
        }
        if (index >= stream.size()) break;
        if (stream[index] == pattern[j]) {
            index++;
            j++;
            continue;
        }
        if (pattern[j] == '*') {
            last_star_index = j;
            j++;
            index++;
        }
        else {
            if (last_star_index == -1) {
                std::cout << "index: " << index << std::endl;
                std::cout << "j: " << j << std::endl;
                std::cout << "last_star_index == -1" << std::endl;
                return -1;
            }
            int prev_index = get_previous_index_of_char(pattern, '*', stream[index], j - 1);
            while (1) {
                if (prev_index == -1) {
                    j = last_star_index;
                    break;
                }
                else {
                    std::string pattern_sub_str = pattern.substr(last_star_index + 1, prev_index - last_star_index - 1);
                    std::string stream_sub_str = stream.substr(index - pattern_sub_str.size(), pattern_sub_str.size());
                    if (pattern_sub_str == stream_sub_str) {
                        j = prev_index;
                        break;
                    }
                    else {
                        prev_index = get_previous_index_of_char(pattern, '*', stream[index], prev_index - 1);
                    }
                }
            }
        }
    }
    return last_matched_index;
}

std::vector<token*> lexer_algo1::get_tokens (std::string &char_stream) {
    int i = 0;
    while (i < char_stream.size()) {
        
    }
}