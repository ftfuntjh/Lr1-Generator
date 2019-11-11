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
            Item{"S_", ItemType::NoTerminal},
            Item{"S", ItemType::NoTerminal},
            Item{"C", ItemType::NoTerminal},
            Item{"c", ItemType::Terminal},
            Item{"d", ItemType::Terminal},
    };
    Item &S_ = itemList[0];
    Item &S = itemList[1];
    Item &C = itemList[2];
    Item &c = itemList[3];
    Item &d = itemList[4];
    vector<Production> productions{
            Production{S_, vector<Item>{S}},
            Production{S, vector<Item>{C, C}},
            Production{C, vector<Item>{c, C}},
            Production{C, vector<Item>{d}},
    };

    Context context{productions, productions[0]};
};

TEST_F(Goto, ShouldGenerateLr1Table) {
    try {
        context.first();
        context.follow();
        auto result = context.generalLr1();
        for (auto n : result) {
            cout << endl;
            cout << "--- start new state " << n.shiftItem().getName() << " ---" << endl;
            for (auto h : n.ruleList()) {
                h.printHandler();
            }
            cout << "--- end new state --- " << endl;
        }
        auto table = context.table(result);
        context.printTable(table);
    } catch (const exception &exp) {
        cout << "exception " << endl;
    }

}

TEST_F(Goto, ShouldReturnNextHandlerSet) {
    context.first();
    context.follow();
    Item eof{"$", ItemType::Terminal};
    set<Item> lookAt{eof};
    Handler handler{productions[0], 0, lookAt};
    vector<Handler> closure{};
    context.closureSet(handler, closure);
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

