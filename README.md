# Calculate First/Follow Set of given grammar

## Notice
The project is in development.

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
E→TE’，

E’→+TE’，

E’→ε，

T→FT’，

T’→*FT’，

T’→ε，

F→(E)|i
```
**the '^' means 'ε'**
the result is
```
E -> {'(' ,'i'}
E_ -> {'+' ,'^'}
F -> {'(' ,'i'}
T -> {'(' ,'i'}
T_ -> {'*' ,'^'}
```



