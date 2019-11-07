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
cd first-Follow
mkdir build && cd build
cmake .. && cmake -- build .
./build/lr1
```

### Example

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



