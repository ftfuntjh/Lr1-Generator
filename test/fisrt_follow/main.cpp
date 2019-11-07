#include <gmock/gmock.h>
#include "../../src/Context.h"

using namespace std;
using namespace testing;
const static Item Eof{"$", ItemType::Terminal};

class Grammar : public ::testing::Test {
public:
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
    Item &E = items[0];
    Item &E_ = items[1];
    Item &T = items[2];
    Item &T_ = items[3];
    Item &F = items[4];
    Item &empty = items[5];
    Item &plus = items[6];
    Item &star = items[7];
    Item &left = items[8];
    Item &right = items[9];
    Item &i = items[10];

};

TEST_F(Grammar, GivenGrammarShouldHaveExpectedFirstSet) {
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
    Context context{grammar, grammar.front()};
    context.first();
    context.follow();
    auto E_FIRST = set<Item>{i, left};
    auto E__FIRST = set<Item>{plus, empty};
    EXPECT_THAT(context.firstAt(E)->second, E_FIRST);
    EXPECT_THAT(context.firstAt(E_)->second, E__FIRST);
}


TEST_F(Grammar, GivenGrammarShouldHaveExpectedFollowSet) {
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
    Context context{grammar, grammar.front()};
    context.first();
    context.follow();
    auto E_FOLLOW = set<Item>{Eof, right};
    auto F_FOLLOW = set<Item>{Eof, right, star, plus};
    EXPECT_THAT(context.followAt(E)->second, E_FOLLOW);
    EXPECT_THAT(context.followAt(F)->second, F_FOLLOW);
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
