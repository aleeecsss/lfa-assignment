// skibidi.h
#ifndef SKIBIDI_H
#define SKIBIDI_H

bool is_non_terminal(char c) {
    if (c >= 'A' && c <= 'Z') {
        return true;
    }
    return false;
}

/**
 * ok, deci mi-a fost o lene infecta sa optimizez backtracking-ul, asa ca m-am pus
 * sa ma gandesc la o implementare mai eficienta
 * 
 * datorita structurii amuzante a problemei (hahah simbol mare face boom 💥 explozie 
 * INSANE in mai multe caractere), m-am gandit sa o iau invers. oare ce se intampla
 * daca pornim de la target_string si ne ducem inapoi, in caracterul de unde a inceput
 * BIG BANG-UL 🤩??!
 * 
 * hmmm are structura de dinamica mixta... adica daca consideram numai caracterele
 * dintr-o secventa continua, problema inversa nu se extinde altundeva, ramane acolo 
 * cuminte 🫠. (!)
 * 
 * 🗣️🔥🔥💯 PAC! avem din start un dp[i][j]. dar din pacate nu avem suficiente 
 * informatii...
 * 
 * 🤓☝️ acshually mai putem baga un parametru de symbol care indica in dinamica
 * urmatoarea definitie: dp[i][j][symbol] = putem transforma secventa [i..j] din
 * target_string in simbolul sigma 🗿 non-terminal "symbol"?
 * 
 * okay, avem asta, now what?
 * 
 * acum trebuie sa ma folosesc de cooking 🔥🔥🔥🔥, ca sa pot determina starile
 * dinamicii. am deja recipe-urile inverse (adica dintr-un string pot ajunge la un
 * anumit simbol "symbol"). 
 * 
 * OH SHIT! recipe-urile pot fi INSANE de imbarligate, ce fac acum ?!?!
 * 
 * exemplu: S <- "(S)(E)xfgr(B)sda(C)asfa(S)asda(A)"
 * 
 * interesant... putem fixa pentru dp[i][j][symbol] un recipe specific simbolului
 * "symbol", si putem baga o alta dinamica sa vedem daca chiar e posibil sa dam
 * reverse-engineer secventei [i..j] in simbolul "symbol", cu ajutorul acelui recipe.
 * 
 * acum vine the ultimate final boss: dp_𝓯𝓻𝓮𝓪𝓴𝔂
 * 
 * mama bro sunt cooked frfr 🔥 it looks exponential... pana la urma, trebuie sa
 * dam match la recipe cu secventa [i..j], fara sa stim absolut deloc lungimile pe
 * care le vor ocupa simbolurile sigma...
 * 
 * wait, cred ca m-am prins. putem considera fiecare alocare posibila (un caracter
 * pentru un caracter non-sigma si un numar variabil de caractere pentru un caracter
 * sigma). sI fUNCTIONEAZA BROOOO !! pentru ca problema are structura de dinamica
 * mixta (see (!)) si caracterele asociate unui caracter sigma reprezinta o secventa
 * continua. LESS GOO WE'RE COOKING
 * 
 * bun, hai sa vedem de ce avem nevoie. pac, din start avem dp_𝓯𝓻𝓮𝓪𝓴𝔂[i][j] (logic,
 * avem nevoie de restrictiile subproblemei noastre, doar umblam cu secventa [i..j],
 * nu cu [2-9] [2-10] etccc)
 * 
 * okay, avem nevoie de o referinta pentru recipe book-ul nostru, boss, inca 2 parametri,
 * te rog. 
 * 
 * PAC dp_𝓯𝓻𝓮𝓪𝓴𝔂[i][j][symbol][recipe_idx].
 * 
 * okay, iar acum, pentru a vedea indicele la care ne aflam in recipe-ul nostru (pentru
 * a face matching-ul dintre recipe si secventa noastra [i..j]), mai avem nevoie de inca
 * un parametru c care reprezinta indicele la care ne aflam in recipe-ul nostru.
 * 
 * dp_𝓯𝓻𝓮𝓪𝓴𝔂[i][j][c][symbol][recipe_idx]
 * 
 * ok, pare suficient, hai sa vedem acum care ar fi recurenta de baza + definitiile.
 * 
 * dp[i][j][symbol] = true / false (putem transforma secventa [i..j] in simbolul "symbol",
 * facand transformari inverse?)
 * 
 * dp_𝓯𝓻𝓮𝓪𝓴𝔂[i][j][c][symbol][recipe_idx] = true / false (putem transforma successfully
 * secventa [i..j] in simbolul "symbol", stiind ca vom folosi recipe-ul cu indicele
 * "recipe_idx" din lista recipe-urilor pentru "symbol", stiind ca am facut progres si 
 * mai trebuie sa consideram prefixul [0..c] din recipe si sa-l cuplam cumva cu secventa
 * [i..j] ramasa?)
 * 
 * bun, recurentele:
 * 
 * dp[i][j][symbol] = max {dp_𝓯𝓻𝓮𝓪𝓴𝔂[i][j][recipes[symbol][recipe_idx].size() - 1][symbol][recipe_idx],
 *                          pentru fiecare recipe_idx}
 *
 * daca caracterul curent din recipe (recipes[symbol][c]) este sigma: 
 * dp_𝓯𝓻𝓮𝓪𝓴𝔂[i][j][c][symbol][recipe_idx] = max {dp_𝓯𝓻𝓮𝓪𝓴𝔂[k + 1][j][c - 1][symbol][recipe_idx] &
 *                                                  dp[i][k][recipes[symbol][c]],
 *                                                  pentru fiecare i <= k <= j (alocam numarul variabil
 *                                                  de caractere pentru simbolul sigma)}
 * 
 * daca caracterul curent din recipe (recipes[symbol][c]) NU este sigma:
 * dp_𝓯𝓻𝓮𝓪𝓴𝔂[i][j][c][symbol][recipe_idx] = dp_𝓯𝓻𝓮𝓪𝓴𝔂[i + 1][j][c - 1][symbol][recipe_idx], daca
 *                                                  recipes[symbol][c] == target_string[i] (cuplare 1-to-1);
 *                                           false, altfel.
 * 
 * damnn, pretty solid dp. OH ShIT am uitat de ciclari in dinamica.
 * 
 * ce fac cand avem ceva de genul:
 * 
 * A -> "B"
 * B -> "C"
 * C -> "A"
 * 
 * ca subset in recipe book?
 * 
 * se rezolva bro, baga si tu un in_progress[][][] acolo sa nu reintri in aceeasi stare din
 * greseala. LESS GOO!!
 * 
 * bla bla memoizare pentru implementare mai usoara bla bla
 * 
 * |target_string| = n
 * 
 * Complexitate: O(n^3 * 🗿 * 🔥MAXLEN * 🔥MAXCOUNT).
 * 
 * partea de reconstruire e destul de straight-forward. salvam o partitie valida pentru
 * fiecare dp si dp_𝓯𝓻𝓮𝓪𝓴𝔂 si dupa mergem recursiv in copiii lui.
 * 
 * edge-cases si base-cases bla bla bla cancer implementarea
 */

const int NMAX = 35, 🗿 = 26, 🔥MAXLEN = 25, 🔥MAXCOUNT = 5;

char start_symbol;
std::string S, saved_str, target_string;
std::vector<std::string> recipes[🗿];
std::vector<std::string> generated_strings;

int dp[NMAX][NMAX][🗿];
int dp_𝓯𝓻𝓮𝓪𝓴𝔂[NMAX][NMAX][🔥MAXLEN][🗿][🔥MAXCOUNT];

std::bitset<🗿> marked[NMAX][NMAX];
std::bitset<🔥MAXCOUNT> marked_𝓯𝓻𝓮𝓪𝓴𝔂[NMAX][NMAX][🔥MAXLEN][🗿];

std::bitset<🗿> in_progress[NMAX][NMAX];

struct Derivation {
    int recipe_idx;
    std::vector<std::pair<int, int>> partitions;
};

Derivation derivation[NMAX][NMAX][🗿];
Derivation derivation_𝓯𝓻𝓮𝓪𝓴𝔂[NMAX][NMAX][🔥MAXLEN][🗿][🔥MAXCOUNT];

int DP(int i, int j, int symbol);

void init_dp() {
    for (int i = 0; i < NMAX; ++i) {
        for (int j = 0; j < NMAX; ++j) {
            for (int k = 0; k < 🗿; ++k) {
                marked[i][j][k] = false;
                dp[i][j][k] = 0;
                in_progress[i][j][k] = false;
                derivation[i][j][k].recipe_idx = -1;
                derivation[i][j][k].partitions.clear();
            }
        }
    }

    for (int i = 0; i < NMAX; ++i) {
        for (int j = 0; j < NMAX; ++j) {
            for (int k = 0; k < 🔥MAXLEN; ++k) {
                for (int l = 0; l < 🗿; ++l) {
                    for (int p = 0; p < 🔥MAXCOUNT; ++p) {
                        marked_𝓯𝓻𝓮𝓪𝓴𝔂[i][j][k][l][p] = false;
                        dp_𝓯𝓻𝓮𝓪𝓴𝔂[i][j][k][l][p] = 0;
                        derivation_𝓯𝓻𝓮𝓪𝓴𝔂[i][j][k][l][p].recipe_idx = -1;
                        derivation_𝓯𝓻𝓮𝓪𝓴𝔂[i][j][k][l][p].partitions.clear();
                    }
                }
            }
        }
    }
}

int DP_FREAKY(int i, int j, int c, int symbol, int recipe_idx) {
    if (c < 0) {
        return (i > j) ? 1 : 0;
    }

    if (i > j) {
        return 0;
    }
    
    if (marked_𝓯𝓻𝓮𝓪𝓴𝔂[i][j][c][symbol][recipe_idx] == true) {
        return dp_𝓯𝓻𝓮𝓪𝓴𝔂[i][j][c][symbol][recipe_idx];
    }
    
    marked_𝓯𝓻𝓮𝓪𝓴𝔂[i][j][c][symbol][recipe_idx] = true;
    
    std::string& recipe = recipes[symbol][recipe_idx];
    
    std::vector<std::string> symbols;
    std::string current;
    
    for (int idx = 0; idx <= c; ++idx) {
        if (is_non_terminal(recipe[idx])) {
            if (!current.empty()) {
                symbols.push_back(current);
                current.clear();
            }
            symbols.push_back(std::string(1, recipe[idx]));
        } else {
            current += recipe[idx];
        }
    }

    if (!current.empty()) {
        symbols.push_back(current);
    }
    
    if (symbols.empty()) {
        dp_𝓯𝓻𝓮𝓪𝓴𝔂[i][j][c][symbol][recipe_idx] = (i > j) ? 1 : 0;
        return dp_𝓯𝓻𝓮𝓪𝓴𝔂[i][j][c][symbol][recipe_idx];
    }

    std::vector<std::pair<int, int>> best_partition;
    
    std::function<bool(int, int, std::vector<std::pair<int, int>>&)> try_match = 
        [&](int sym_idx, int pos, std::vector<std::pair<int, int>>& current_partition) -> bool {
        
        if (sym_idx == symbols.size()) {
            if (pos == j + 1) {
                best_partition = current_partition;
                return true;
            }

            return false;
        }
        
        if (pos > j) {
            return false;
        }
        
        const std::string& sym = symbols[sym_idx];
        
        if (sym.size() == 1 && is_non_terminal(sym[0])) {
            for (int end_pos = pos; end_pos <= j; ++end_pos) {
                if (DP(pos, end_pos, sym[0] - 'A')) {
                    current_partition.push_back({pos, end_pos});

                    if (try_match(sym_idx + 1, end_pos + 1, current_partition)) {
                        return true;
                    }
                    
                    current_partition.pop_back();
                }
            }
        } else {
            if (pos + sym.size() <= j + 1) {
                bool matches = true;
                for (int k = 0; k < sym.size(); ++k) {
                    if (target_string[pos + k] != sym[k]) {
                        matches = false;
                        break;
                    }
                }
                if (matches) {
                    current_partition.push_back({pos, pos + sym.size() - 1});
                    if (try_match(sym_idx + 1, pos + sym.size(), current_partition)) {
                        return true;
                    }
                    current_partition.pop_back();
                }
            }
        }
        
        return false;
    };
    
    std::vector<std::pair<int, int>> current_partition;
    bool result = try_match(0, i, current_partition);
    
    if (result) {
        derivation_𝓯𝓻𝓮𝓪𝓴𝔂[i][j][c][symbol][recipe_idx].partitions = best_partition;
    }
    
    dp_𝓯𝓻𝓮𝓪𝓴𝔂[i][j][c][symbol][recipe_idx] = result ? 1 : 0;
    return dp_𝓯𝓻𝓮𝓪𝓴𝔂[i][j][c][symbol][recipe_idx];
}

int DP(int i, int j, int symbol) {
    if (i > j) {
        for (int k = 0; k < recipes[symbol].size(); ++k) {
            if (recipes[symbol][k].empty()) {
                derivation[i][j][symbol].recipe_idx = k;
                return 1;
            }
        }

        return 0;
    }

    if (in_progress[i][j][symbol]) {
        return 0;
    }

    if (marked[i][j][symbol] == true) {
        return dp[i][j][symbol];
    }

    marked[i][j][symbol] = true;
    in_progress[i][j][symbol] = true;

    for (int k = 0; k < recipes[symbol].size(); ++k) {
        std::string sequence = recipes[symbol][k];
        
        bool is_pure_terminal = true;

        for (char c : sequence) {
            if (is_non_terminal(c)) {
                is_pure_terminal = false;
                break;
            }
        }
        
        if (is_pure_terminal && target_string.substr(i, j - i + 1) == sequence) {
            dp[i][j][symbol] = 1;
            derivation[i][j][symbol].recipe_idx = k;
            in_progress[i][j][symbol] = false;
            return 1;
        }
    }

    for (int k = 0; k < recipes[symbol].size(); ++k) {
        if (recipes[symbol][k].empty() && i <= j) {
            continue;
        }
        
        if (!recipes[symbol][k].empty()) {
            int result = DP_FREAKY(i, j, recipes[symbol][k].size() - 1, symbol, k);
            if (result == 1) {
                dp[i][j][symbol] = 1;
                derivation[i][j][symbol].recipe_idx = k;
                derivation[i][j][symbol].partitions = 
                derivation_𝓯𝓻𝓮𝓪𝓴𝔂[i][j][recipes[symbol][k].size() - 1][symbol][k].partitions;
                break;
            }
        }
    }

    in_progress[i][j][symbol] = false;
    return dp[i][j][symbol];
}

void 👷(int i, int j, int symbol, std::string indent = "") {
    if (derivation[i][j][symbol].recipe_idx == -1) {
        std::cout << indent << "No derivation found\n";
        return;
    }
    
    int recipe_idx = derivation[i][j][symbol].recipe_idx;
    std::string& recipe = recipes[symbol][recipe_idx];
    
    std::cout << indent << (char)(symbol + 'A') << " -> " << recipe;
    
    if (i > j) {
        std::cout << " (empty string)\n";
        return;
    }
    
    std::cout << " [" << target_string.substr(i, j - i + 1) << "]\n";

    bool is_pure_terminal = true;

    for (char c : recipe) {
        if (is_non_terminal(c)) {
            is_pure_terminal = false;
            break;
        }
    }
    
    if (is_pure_terminal) {
        return;
    }

    std::vector<std::string> symbols;
    std::string current;
    
    for (char c : recipe) {
        if (is_non_terminal(c)) {
            if (!current.empty()) {
                symbols.push_back(current);
                current.clear();
            }

            symbols.push_back(std::string(1, c));
        } else {
            current += c;
        }
    }

    if (!current.empty()) {
        symbols.push_back(current);
    }

    int partition_idx = 0;

    for (const auto& sym : symbols) {
        if (sym.size() == 1 && is_non_terminal(sym[0])) {
            if (partition_idx < derivation[i][j][symbol].partitions.size()) {
                auto& part = derivation[i][j][symbol].partitions[partition_idx];
                👷(part.first, part.second, sym[0] - 'A', indent + "  ");
                partition_idx++;
            }
        } else {
            partition_idx++;
        }
    }
}

#endif