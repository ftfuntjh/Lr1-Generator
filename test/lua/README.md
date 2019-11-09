### The Lua BNF Description
        chunk ::=  reptstat reptlaststat
        
        reptstat ::= ε | reptstat stat optbreak
        
        optbreak ::= ε | `;´
        
        reptlaststat ::=  ε | lastatat optbreak
        
        block ::= chunk

        stat ::=  varlist1 `=´ explist1  |
                 functioncall  |
                 do block end  |
                 while exp do block end  |
                 repeat block until exp  |
                 if exp then block reptelseifexp optelseblock end  |
                 for Name `=´ exp `,´ exp optexp do block end  |
                 for namelist in explist1 do block end  |
                 function funcname funcbody  |
                 local function Name funcbody  |
                 local namelist opteqexplist1
                 
        reptelseifexp ::= ε | reptelseifexp elseif exp then block
        
        optelseblock  ::= ε | else block
        
        optexp        ::= ε | `,` exp
        
        opteqexplist1   ::= ε | = explist1
        
        optexplist1     ::= ε | explist1

        laststat ::= return optexplists1  |  break

        funcname ::= Name reptdotname optsemicolonmae

        reptdotname ::= ε | reptdotname . Name

        reptcommaname ::= ε | reptcommaname , Name
        
        optsemicolonname ::= ε | : Name
        
        varlist1 ::= var reptcommavar
        
        reptcommavar ::= ε | reptcommavar , var

        var ::=  Name  |  prefixexp `[´ exp `]´  |  prefixexp `.´ Name

        namelist ::= Name reptcommaname

        explist1 ::= reptexpcomma  exp
        
        reptexpcomma = ε | reptexpcomma exp `,`

        exp ::=  nil  |  false  |  true  |  Number  |  String  |  `...´  |
                 function  |  prefixexp  |  tableconstructor  |  exp binop exp  |  unop exp

        prefixexp ::= var  |  functioncall  |  `(´ exp `)´

        functioncall ::=  prefixexp args  |  prefixexp `:´ Name args

        args ::=  `(´ optexplist1 `)´  |  tableconstructor  |  String

        function ::= function funcbody

        optparlist1 ::= ε | parlist1
        
        funcbody ::= `(´ parlist1 `)´ block end

        optcommadotdotdot ::= ε | `,´ `...´
        
        parlist1 ::= namelist optcommadotdotdot  |  `...´

        optfieldlist ::= ε | fieldlist
    
        tableconstructor ::= `{´ optfieldlist  `}´

        reptfieldsepfield ::= ε | reptfieldsepfield  fieldsep field
        
        optfieldsep ::= ε | fieldsep
        
        fieldlist ::= field reptfieldsepfield  optfieldsep 

        field ::= `[´ exp `]´ `=´ exp  |  Name `=´ exp  |  exp

        fieldsep ::= `,´  |  `;´

        binop ::= `+´  |  `-´  |  `*´  |  `/´  |  `^´  |  `%´  |  `..´  |
                 `<´  |  `<=´  |  `>´  |  `>=´  |  `==´  |  `~=´  |
                 and  |  or

        unop ::= `-´  |  not  |  `#´