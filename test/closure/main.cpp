#include <gmock/gmock.h>
#include "../../src/Context.h"

using namespace std;
using namespace testing;

class Closure : public Test {
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

TEST_F(Closure, ClouseShouldInitTheStartItemSet) {
    set<Item> s_Set{Item{"$", ItemType::Terminal}};
    set<Item> cc_Set{c, d};
    set<Item> c_Set{c};
    set<Item> d_Set{d};
    Handler startHandler(productions.front(), 0, s_Set);
    context.first();
    context.follow();
    cout << "--- first --- " << endl;
    context.printFirst();
    cout << "--- end ---" << endl;
    context.printFollow();
    vector<Handler> result{};
    context.closureSet(startHandler, result);
    cout << "--- handler ---" << endl;
    for (auto h : result) {
        h.printHandler();
    }

    vector<Handler> expected{
            Handler{productions[0], 0, s_Set},
            Handler{productions[1], 0, s_Set},
            Handler{productions[2], 0, cc_Set},
            Handler{productions[3], 0, cc_Set},
    };
    EXPECT_THAT(result, expected);
}

int main(int argc, char *argv[]) {
    InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
