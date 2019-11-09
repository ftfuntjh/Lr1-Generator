//
// Created by ftfunjth on 2019/11/8.
//

#include <gmock/gmock.h>
#include "../../src/Context.h"
#include <cstdio>

using namespace std;
using namespace testing;

class Goto : public Test {
public:
    vector<Item> itemList{
            Item{"S", ItemType::NoTerminal},
            Item{"List", ItemType::NoTerminal},
            Item{"Pair", ItemType::NoTerminal},
            Item{"(", ItemType::Terminal},
            Item{")", ItemType::Terminal},
    };
    Item &S = itemList[0];
    Item &List = itemList[1];
    Item &Pair = itemList[2];
    Item &left = itemList[3];
    Item &right = itemList[4];
    vector<Production> productions{
            Production{S, vector<Item>{List}},
            Production{List, vector<Item>{List, Pair}},
            Production{List, vector<Item>{Pair}},
            Production{Pair, vector<Item>{left, Pair, right}},
            Production{Pair, vector<Item>{left, right}},
    };

    Context context{productions, productions[0]};
};

TEST_F(Goto, ShouldGenerateLr1Table) {
    context.first();
    context.follow();
    auto result = context.generalLr1();
    auto table = context.table(result);
    context.printTable(table);
}

TEST_F(Goto, ShouldReturnNextHandlerSet) {
    context.first();
    context.follow();
    Item eof{"$", ItemType::Terminal};
    set<Item> lookAt{eof};
    Handler handler{productions[0], 0, lookAt};
    auto closure = context.closureSet(handler);
    HandlerSet startHandlerSet{Item{"", ItemType::Terminal}, closure};
    auto gotoNext = context.Goto(startHandlerSet);
    for (auto n : gotoNext) {
        cout << endl;
        cout << "--- start new state " << n.shiftItem().getName() << " ---" << endl;
        for (auto h : n.ruleList()) {
            h.printHandler();
        }
        cout << "--- end new state --- " << endl;
    }
}

int main(int argc, char *argv[]) {
    InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

