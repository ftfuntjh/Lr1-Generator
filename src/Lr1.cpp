#include "Common.h"
#include "Context.h"
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

int main(int argc, char *argv[], char *env[]) {
    vector<Item> items{
            Item{"E", ItemType::NoTerminal},
            Item{"E_", ItemType::NoTerminal},
            Item{"T", ItemType::NoTerminal},
            Item{"T_", ItemType::NoTerminal},
            Item{"F", ItemType::NoTerminal},
            Item{"^", ItemType::Terminal},
            Item{"+", ItemType::Terminal},
            Item{"*", ItemType::Terminal},
            Item{"(", ItemType::Terminal},
            Item{")", ItemType::Terminal},
            Item{"i", ItemType::Terminal},
    };
    auto &E = items[0];
    auto &E_ = items[1];
    auto &T = items[2];
    auto &T_ = items[3];
    auto &F = items[4];
    auto &empty = items[5];
    auto &plus = items[6];
    auto &star = items[7];
    auto &left = items[8];
    auto &right = items[9];
    auto &i = items[10];
    vector<Production> grammar{
            Production{E, vector<Item>{T, E_}},
            Production{E_, vector<Item>{plus, T, E_}},
            Production{E_, vector<Item>{empty}},
            Production{T, vector<Item>{F, T_}},
            Production{T_, vector<Item>{star, F, T_}},
            Production{T_, vector<Item>{empty}},
            Production{F, vector<Item>{left, E, right}},
            Production{F, vector<Item>{i}},
    };
    Context context{grammar, grammar[0]};
    cout << "--- the grammar is ---" << endl;
    context.printGrammar();
    context.first();
    cout << "--- the first set is ---" << endl;
    context.printFirst();
    context.follow();
    cout << "--- the follow set is ---" << endl;
    context.printFollow();
    return 0;
}
