#include "Common.h"
#include "Context.h"

using std::vector;

int main(int argc, char *argv[], char *env[]) {
    vector<Item> items{
            Item{"E", ItemType::NoTerminal},
            Item{"E_", ItemType::NoTerminal},
            Item{"T", ItemType::NoTerminal},
            Item{"T_", ItemType::NoTerminal},
            Item{"F", ItemType::NoTerminal},
            Item{"^", ItemType::Terminal},
            Item{"(", ItemType::Terminal},
            Item{")", ItemType::Terminal},
            Item{"i", ItemType::Terminal},
            Item{"+", ItemType::Terminal},
            Item{"*", ItemType::Terminal},
    };
    auto &E = items[0];
    auto &E_ = items[1];
    auto &T = items[2];
    auto &T_ = items[3];
    auto &F = items[4];
    auto &empty = items[5];
    auto &left_brace = items[6];
    auto &right_brace = items[7];
    auto &i = items[8];
    auto &star = items[10];
    auto &plus = items[9];
    vector<Production> grammar{
            Production{E, vector<Item>{T, E_}},
            Production{E_, vector<Item>{plus, T, E_}},
            Production{E_, vector<Item>{empty}},
            Production{T, vector<Item>{F, T_}},
            Production{T_, vector<Item>{star, F, T_}},
            Production{T_, vector<Item>{empty}},
            Production{F, vector<Item>{left_brace, E, right_brace}},
            Production{F, vector<Item>{i}}
    };
    Context context{grammar};
    context.first();
    context.printFirst();
    return 0;
}
