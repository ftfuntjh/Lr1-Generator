# Calculate First/Follow Set of given grammar

## Notice
The project is in development. 

## TODO list
- parse user input BNF grammer
- check grammar ambiguity
- generate SLR table for given grammar
- generate LR(1) table for given grammer
- generate LALR table for given grammer
- a simple implement of yacc

## Usage
### Install
```
git clone https://github.com/ftfuntjh/First-Follow.git
cd First-Follow
mkdir build && cd build
cmake .. && cmake -- build .
./build/lr1
```
### Add User Grammar
first you need to define `Item` and `Production`,`Context`class.  
support you have a grammar language like this:
```
S' -> S
S  -> CC
C  -> cC
C  -> d
```
as you can see, the language has four production with five terminal/no terminal token.  
in this implement, you need do as following code:
```

    vector<Item> itemList{
            Item{"S_", ItemType::NoTerminal},
            Item{"S", ItemType::NoTerminal},
            Item{"C", ItemType::NoTerminal},
            Item{"c", ItemType::Terminal},
            Item{"d", ItemType::Terminal},
    }; // the tokens in the language
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
    // the productions in language
    
    Context context{productions, productions[0]};
    // the context for given language
    // Context{vector<Production>,Production startProduciton};
```
after that you could calculate the first/follow set and the lr(1) state table of given language
```
    context.first(); // calculate the first set
    context.follow(); // calculate the follow set
    context.generalLr1(); // generate the lr(1) state table(the Actions And Goto Tables in developments.)

    context.printFirst(); // print the first set 
    context.printFollow(); // print the follow set
```
**see the [test code](https://github.com/ftfuntjh/First-Follow/tree/master/test) for details**
### Example First/Follow Set
The example grammar is
```
E -> TE_
E_ -> +TE_
E_ -> ^
T -> FT_
T_ -> *FT_
T_ -> ^
F -> (E)
F -> i
```
**the '^' means 'ε'**  
**the '$' means 'eof'**
### the result is
```
--- the first set is ---
E -> {'(' ,'i'}
E_ -> {'+' ,'^'}
F -> {'(' ,'i'}
T -> {'(' ,'i'}
T_ -> {'*' ,'^'}
--- the follow set is ---
E -> {'$' ,')'}
E_ -> {'$' ,')'}
F -> {'$' ,')' ,'*' ,'+'}
T -> {'$' ,')' ,'+'}
T_ -> {'$' ,')' ,'+'}
```

### Example Lr1 Actions Goto Table
```
                   action|      goto
     state    c    d    $|    S    C
         0  s1   s3      |    4    2
         1  s1   s3      |         5
         2  s6   s7      |         8
         3  r0   r0      |          
         4            a0 |          
         5  r1   r1      |          
         6  s6   s7      |         9
         7            r2 |          
         8            r2 |          
         9            r6 |          
```
