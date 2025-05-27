/**
0-cfg.in
S
S -> "aSb" | ""

1-cfg.in
E
E -> "E+T" | "T"
T -> "T*F" | "F"
F -> "(E)" | "a"

2-cfg.in
S
S -> "S" | "X" | "aSX" | "XSa" | ""
X -> "S" | "b" | "ab" | ""
*/

/**
 * Task #1:
 * Caracterele mari sunt non-terminale.
 * Orice alt caracter este terminal.
 * Simbolul de start reprezinta prima linie din *-cfg.in
 * 
 * Productie:
 * <caracter non-terminal> -> "<string_1>" | "<string_2>" | ... "<string_n>"
 * 
 * <caracter non-terminal> poate fi 'A', 'B' ... 'Z'.
 * <string_1>, <string_2> ... <string_n> pot fi orice string format din caractere
 * terminale / nonterminale.
 */

#include <bits/stdc++.h>
#include "skibidi.h"

std::ifstream fin("cfg.in");
std::mt19937 rng(420);

int main() {
    fin >> start_symbol;

    char symbol;

    while (fin >> S) { // Parsare simpla
        if (S.size() == 1 && is_non_terminal(S[0])) {
            symbol = S[0];
            continue;
        }

        if (S.size() == 2 && S[0] == '-' && S[1] == '>') {
            continue;
        }

        if (S.size() >= 2 && *S.begin() == '"' && *S.rbegin() == '"') {
            std::string T;

            for (int i = 1; i < (int)(S.size() - 1); ++i) {
                T.push_back(S[i]);
            }

            recipes[symbol - 'A'].push_back(T);
        }
    }

    // DEBUG!
    //
    // for (int i = 0; i < SIGMA; ++i) {
    //     std::cout << char(i + 'A') << ":\n";

    //     for (int j = 0; j < recipes[i].size(); ++j) {
    //         std::cout << recipes[i][j] << "\n";
    //     }

    //     std::cout << "\n";
    // }

    std::cout << "Task #2:\n";

    for (int tst = 0; tst < 10; ++ tst) {
        int num_it = rng() % 6;

        for (int i = 0; i < num_it; ++i) {
            std::cout << "a";
        }

        for (int i = 0; i < num_it; ++i) {
            std::cout << "b";
        }

        std::cout << "\n";
    }

    std::cout << "\n";

    std::cout << "Task #3 + #4:\n";

    target_string = "aaabbb";

    std::cout << "Target String: " << target_string << "\n";

    init_dp();

    if (DP(0, target_string.size() - 1, start_symbol - 'A') == 1) {
        std::cout << "wait, we're cooking 🗣️🔥🔥💯\n";

        👷(0, target_string.size() - 1, start_symbol - 'A');
    } else {
        std::cout << "hell naw, this string is beta frfr 🗣️🔥🔥💯\n";
    }

    return 0;
}
