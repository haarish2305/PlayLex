#include <iostream>
#include <fstream>
#include "includes/lexer.h"
#include "includes/parser.h"
using namespace std;

grammer* parse_grammer_file(string file_name) {
    fstream file(file_name, ios::in);
    if (!file.is_open()) {
        cout << file_name << " cannot be opened for reading" << endl;
        return NULL;
    }
    grammer *my_grammer = new grammer();
    string buffer;
    while(getline(file, buffer)) {
        if (buffer.find("start_symbol") != string::npos) {
            int equal_index = buffer.find('=');
            my_grammer->start_symbol = buffer.substr(equal_index + 1, buffer.size() - 1 - equal_index)[0];
        }
        else if (buffer.find("terminals") != string::npos) {
            int equal_index = buffer.find('=');
            string terminal = "";
            for (int i = equal_index + 1; i < buffer.size(); i++) {
                if (buffer[i] != ',') {
                    terminal += buffer[i];
                }
                else {
                    my_grammer->terminals.insert(terminal[0]);
                    terminal = "";
                }
            }
            my_grammer->terminals.insert(terminal[0]);
        }
        else if (buffer.find("prods") != string::npos) {
            while(getline(file, buffer)) {
                int equal_index = buffer.find('=');
                string first = buffer.substr(0, equal_index);
                string second = buffer.substr(equal_index + 1, buffer.size() - 1 - equal_index);
                production *prod = new production();
                prod->left_side = first[0];
                for (char ch: second) prod->right_side.push_back(ch);
                my_grammer->prods.push_back(prod);
            }
        }
    }
    return my_grammer;
}

void print_grammer(grammer *my_grammer) {
    cout << "start_symbol: " << my_grammer->start_symbol << endl;
    cout << "terminals: ";
    for (char ch: my_grammer->terminals) cout << ch;
    cout << endl;
    cout << "prods: " << endl;
    for (production *prod: my_grammer->prods) {
        cout << prod->left_side << " -> ";
        for (char ch: prod->right_side) cout << ch;
        cout << endl;
    }
}

void test_parser (string file_name) {
    // grammer *my_grammer = new grammer();
    // my_grammer->start_symbol = 'S';
    // my_grammer->terminals = { 'a', 'b', 'c', 'd' };

    // production *prod1 = new production();
    // production *prod2 = new production();
    // production *prod3 = new production();
    // production *prod4 = new production();
    // production *prod5 = new production();

    // prod1->left_side = 'S';
    // prod1->right_side = { 'A', 'B', 'b' };

    // prod2->left_side = 'A';
    // prod2->right_side = { 'c' };

    // prod3->left_side = 'A';
    // prod3->right_side = { 'e' };

    // prod4->left_side = 'B';
    // prod4->right_side = { 'd' };

    // prod5->left_side = 'B';
    // prod5->right_side = { 'e' };

    // my_grammer->prods = { prod1, prod2, prod3, prod4, prod5 };

    grammer *my_grammer = parse_grammer_file(file_name);
    
    print_grammer(my_grammer);

    ll1_parser my_ll1_parser(my_grammer);

    for (production *prod: my_grammer->prods) {
        my_ll1_parser.compute_first(prod->left_side);
    }

    unordered_set<char> done;

    for (production *prod: my_grammer->prods) {
        if (done.find(prod->left_side) != done.end()) continue;
        done.insert(prod->left_side);
        cout << "First of " << prod->left_side << ": ";
        for (char ch: my_ll1_parser.first[prod->left_side]) {
            cout << ch << " ";
        }
        cout << endl;
    }
}

int main (int num_args, char **args) {
    if (num_args <= 1) {
        cout << "Enter file name with path" << endl;
        return 0;
    }
    test_parser(args[2]);
    // string stream, pattern;
    // cin >> pattern;
    // unordered_map<string, string> rules;
    // lexer_algo1 lex(rules);
    // pair<string,string> p = { "", pattern };
    // while (1) {
    //     cin >> stream;
    //     cout << lex.get_longest_match(0, stream, p) << endl;
    // }
}