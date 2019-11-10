#include <gmock/gmock.h>
#include "../../src/Context.h"

using namespace std;
using namespace testing;

class Lua : public Test {
public:
    Item empty{"000", ItemType::Terminal};
    Item start{"start", ItemType::NoTerminal};
    Item chunk{"#chunk", ItemType::NoTerminal};
    Item reptstat{"#reptstat", ItemType::NoTerminal};
    Item optbreak{"#optbreak", ItemType::NoTerminal};
    Item reptlaststat{"#reptlaststat", ItemType::NoTerminal};
    Item block{"#block", ItemType::NoTerminal};
    Item stat{"#stat", ItemType::NoTerminal};
    Item reptelseifexp{"#reptelseifexp", ItemType::NoTerminal};
    Item optelseblock{"#optelseblock", ItemType::NoTerminal};
    Item optexp{"#optexp", ItemType::NoTerminal};
    Item opteqexplist1{"#opteqexplist1", ItemType::NoTerminal};
    Item optexplist1{"#optexplist1", ItemType::NoTerminal};
    Item laststat{"#laststat", ItemType::NoTerminal};
    Item funcname{"#funcname", ItemType::NoTerminal};
    Item reptdotname{"#reptdotname", ItemType::NoTerminal};
    Item reptcommaname{"#reptcommaname", ItemType::NoTerminal};
    Item optsemicolonname{"#optsemicolonname", ItemType::NoTerminal};
    Item varlist1{"#varlist1", ItemType::NoTerminal};
    Item reptcommavar{"#reptcommavar", ItemType::NoTerminal};
    Item var{"#var", ItemType::NoTerminal};
    Item namelist{"#namelist", ItemType::NoTerminal};
    Item explist1{"#explist1", ItemType::NoTerminal};
    Item reptexpcomma{"#reptexpcomma", ItemType::NoTerminal};
    Item exp{"#exp", ItemType::NoTerminal};
    Item prefixexp{"#prefixexp", ItemType::NoTerminal};
    Item functioncall{"#functioncall", ItemType::NoTerminal};
    Item args{"#args", ItemType::NoTerminal};
    Item function_{"#function", ItemType::NoTerminal};
    Item optparlist1{"#optparlist1", ItemType::NoTerminal};
    Item funcbody{"#funcbody", ItemType::NoTerminal};
    Item optcommadotdotdot{"#optcommadotdotdot", ItemType::NoTerminal};
    Item parlist1{"#parlist1", ItemType::NoTerminal};
    Item optfieldlist{"#optfieldlist", ItemType::NoTerminal};
    Item tableconstructor{"#tableconstructor", ItemType::NoTerminal};
    Item reptfieldsepfield{"#reptfieldsepfield", ItemType::NoTerminal};
    Item optfieldsep{"#optfieldsep", ItemType::NoTerminal};
    Item fieldlist{"#fieldlist", ItemType::NoTerminal};
    Item field{"#field", ItemType::NoTerminal};
    Item fieldsep{"#fieldsep", ItemType::NoTerminal};
    Item binop{"#binop", ItemType::NoTerminal};
    Item unop{"#unop", ItemType::NoTerminal};

    Item brk{";", ItemType::Terminal};
    Item eq{"=", ItemType::Terminal};
    Item do_{"do", ItemType::Terminal};
    Item end_{"end", ItemType::Terminal};
    Item while_{"while", ItemType::Terminal};
    Item repeat{"repeat", ItemType::Terminal};
    Item until{"until", ItemType::Terminal};
    Item if_{"if", ItemType::Terminal};
    Item then_{"then", ItemType::Terminal};
    Item for_{"for", ItemType::Terminal};
    Item name{"name", ItemType::Terminal};
    Item comma{",", ItemType::Terminal};
    Item in_{"in", ItemType::Terminal};
    Item local{"local", ItemType::Terminal};
    Item elseif_{"elseif", ItemType::Terminal};
    Item else_{"else", ItemType::Terminal};
    Item return_{"return", ItemType::Terminal};
    Item break_{"break", ItemType::Terminal};
    Item dot{".", ItemType::Terminal};
    Item semicolon{":", ItemType::Terminal};
    Item r_seq_bracket{"]", ItemType::Terminal};
    Item l_seq_bracket{"[", ItemType::Terminal};
    Item nil{"nil", ItemType::Terminal};
    Item false_{"false", ItemType::Terminal};
    Item true_{"true", ItemType::Terminal};
    Item number_{"number", ItemType::Terminal};
    Item string_{"string", ItemType::Terminal};
    Item dotdotdot{"...", ItemType::Terminal};
    Item l_bracket{"(", ItemType::Terminal};
    Item r_bracket{")", ItemType::Terminal};
    Item l_ang_bracket{"{", ItemType::Terminal};
    Item r_ang_bracket{"}", ItemType::Terminal};
    Item plus{"+", ItemType::Terminal};
    Item minus{"-", ItemType::Terminal};
    Item mul{"*", ItemType::Terminal};
    Item divi{"/", ItemType::Terminal};
    Item caret{"^", ItemType::Terminal};
    Item percent{"%", ItemType::Terminal};
    Item dotdot{"..", ItemType::Terminal};
    Item lt{"<", ItemType::Terminal};
    Item lte{"<=", ItemType::Terminal};
    Item gt{">", ItemType::Terminal};
    Item gte{">=", ItemType::Terminal};
    Item ieq{"==", ItemType::Terminal};
    Item neq{"~=", ItemType::Terminal};
    Item and_{"and", ItemType::Terminal};
    Item or_{"or", ItemType::Terminal};
    Item pound{"#", ItemType::Terminal};
    Item not_{"not", ItemType::Terminal};
    Item func{"function", ItemType::Terminal};

    vector<Production> productionList{
            Production{start, vector<Item>{chunk}},
            Production{chunk, vector<Item>{reptstat, reptlaststat}},
            Production{reptstat, vector<Item>{empty}},
            Production{reptstat, vector<Item>{reptstat, stat, optbreak}},
            Production{optbreak, vector<Item>{empty}},
            Production{optbreak, vector<Item>{brk}},
            Production{reptlaststat, vector<Item>{empty}},
            Production{reptlaststat, vector<Item>{laststat, optbreak}},
            Production{block, vector<Item>{chunk}},
            Production{stat, vector<Item>{varlist1, eq, explist1}},
            Production{stat, vector<Item>{functioncall}},
            Production{stat, vector<Item>{do_, block, end_}},
            Production{stat, vector<Item>{while_, exp, do_, block, end_}},
            Production{stat, vector<Item>{repeat, block, until, exp}},
            Production{stat, vector<Item>{if_, exp, then_, block, reptelseifexp, optelseblock, end_}},
            Production{stat, vector<Item>{for_, name, eq, exp, comma, exp, optexp, do_, block, end_}},
            Production{stat, vector<Item>{for_, namelist, in_, explist1, do_, block, end_}},
            Production{stat, vector<Item>{function_, funcname, funcbody}},
            Production{stat, vector<Item>{local, function_, name, funcbody}},
            Production{stat, vector<Item>{local, namelist, opteqexplist1}},
            Production{reptelseifexp, vector<Item>{empty}},
            Production{reptelseifexp, vector<Item>{reptelseifexp, elseif_, exp, then_, block}},
            Production{optelseblock, vector<Item>{empty}},
            Production{optelseblock, vector<Item>{else_, block}},
            Production{optexp, vector<Item>{empty}},
            Production{optexp, vector<Item>{brk, exp}},
            Production{opteqexplist1, vector<Item>{empty}},
            Production{opteqexplist1, vector<Item>{eq, explist1}},
            Production{optexplist1, vector<Item>{empty}},
            Production{optexplist1, vector<Item>{explist1}},
            Production{laststat, vector<Item>{return_, optexplist1}},
            Production{laststat, vector<Item>{break_}},
            Production{funcname, vector<Item>{name, reptdotname, optsemicolonname}},
            Production{reptdotname, vector<Item>{empty}},
            Production{reptdotname, vector<Item>{reptdotname, dot, name}},
            Production{reptcommaname, vector<Item>{empty}},
            Production{reptcommaname, vector<Item>{reptcommaname, comma, name}},
            Production{optsemicolonname, vector<Item>{empty}},
            Production{optsemicolonname, vector<Item>{semicolon, name}},
            Production{varlist1, vector<Item>{var, reptcommavar}},
            Production{reptcommavar, vector<Item>{empty}},
            Production{reptcommavar, vector<Item>{reptcommavar, var}},
            Production{var, vector<Item>{name}},
            Production{var, vector<Item>{prefixexp, l_seq_bracket, exp, r_seq_bracket}},
            Production{var, vector<Item>{prefixexp, dot, name}},
            Production{namelist, vector<Item>{name, reptcommaname}},
            Production{explist1, vector<Item>{reptexpcomma, exp}},
            Production{reptexpcomma, vector<Item>{empty}},
            Production{reptexpcomma, vector<Item>{reptexpcomma, exp, comma}},
            Production{exp, vector<Item>{nil}},
            Production{exp, vector<Item>{false_}},
            Production{exp, vector<Item>{true_}},
            Production{exp, vector<Item>{number_}},
            Production{exp, vector<Item>{string_}},
            Production{exp, vector<Item>{dotdotdot}},
            Production{exp, vector<Item>{function_}},
            Production{exp, vector<Item>{prefixexp}},
            Production{exp, vector<Item>{tableconstructor}},
            Production{exp, vector<Item>{exp, binop, exp}},
            Production{exp, vector<Item>{unop, exp}},
            Production{prefixexp, vector<Item>{var}},
            Production{prefixexp, vector<Item>{functioncall}},
            Production{prefixexp, vector<Item>{l_bracket, exp, r_bracket}},
            Production{functioncall, vector<Item>{prefixexp, args}},
            Production{functioncall, vector<Item>{prefixexp, semicolon, name, args}},
            Production{args, vector<Item>{l_bracket, optexplist1, r_bracket}},
            Production{args, vector<Item>{tableconstructor, string_}},
            Production{function_, vector<Item>{func, funcbody}},
            Production{optparlist1, vector<Item>{empty}},
            Production{optparlist1, vector<Item>{parlist1}},
            Production{funcbody, vector<Item>{l_bracket, parlist1, r_bracket, block, end_}},
            Production{optcommadotdotdot, vector<Item>{empty}},
            Production{optcommadotdotdot, vector<Item>{comma, dotdotdot}},
            Production{parlist1, vector<Item>{namelist, optcommadotdotdot}},
            Production{parlist1, vector<Item>{dotdotdot}},
            Production{optfieldlist, vector<Item>{empty}},
            Production{optfieldlist, vector<Item>{fieldlist}},
            Production{tableconstructor, vector<Item>{l_ang_bracket, optfieldlist, r_ang_bracket}},
            Production{reptfieldsepfield, vector<Item>{empty}},
            Production{reptfieldsepfield, vector<Item>{reptfieldsepfield, fieldsep, field}},
            Production{optfieldsep, vector<Item>{empty}},
            Production{optfieldsep, vector<Item>{fieldsep}},
            Production{fieldlist, vector<Item>{field, reptfieldsepfield, optfieldsep}},
            Production{field, vector<Item>{l_seq_bracket, exp, r_seq_bracket, eq, exp}},
            Production{field, vector<Item>{name, eq, exp}},
            Production{field, vector<Item>{exp}},
            Production{fieldsep, vector<Item>{comma}},
            Production{fieldsep, vector<Item>{brk}},
            Production{binop,
                       vector<Item>{plus, minus, mul, divi, caret, percent, dotdot, lt, lte, gt, gte, ieq, neq, and_,
                                    or_}},
            Production{unop, vector<Item>{minus, not_, pound}},

    };

    Context context{productionList, productionList[0]};
};

TEST_F(Lua, ShouldGenerateLr1Table) {
    context.first();
    context.follow();
    auto result = context.generalLr1();
    auto table = context.table(result);
    context.printTable(table);

}

int main(int argc, char *argv[]) {
    InitGoogleTest();
    return RUN_ALL_TESTS();
}
