****






## 零、序言

本实验中我们实现了PASCAL编译器  
该编译器实现的功能包括：  
* 二元运算（支持强制类型转换）：+ - * /，赋值，比较
* 一元运算：取反not，异或等
* 逻辑语句（支持嵌套）：if-else， for， while do，repeat until   
* 函数定义，函数调用
* 支持的数据类型：枚举，常量，数组
* 自定义类型：typedef





#### 文件说明

* lexcial.l  lexcial.h mainlex.c									词法分析
* mainparser.c  parse.h parse.y parsetools.c       语法分析，语义分析
* symtb.c   symtb.h                                                    符号表
* pprint.c pprint.h printtoken.c                               打印AST

* geninter.c , geninter.h                                            生成中间代码
* test1~8.pascal                                                          测试代码                   



#### 分工

##### 孙路

* 词法分析
* 语法分析
* 语义分析

##### 刘宁

* AST可视化
* 生成中间代码
* 功能测试

****



****

## 一、词法分析

#### 1.1  TOKEN的数据结构
​	在介绍词法分析之前，我需要先介绍用于存储 Yacc 中 **TOKEN** 的数据结构

```c
typedef struct tokenstruct{
    int tokenNo;
    int tokenType;
    int dataType;
    struct tokenstruct* next;
    struct tokenstruct* firstOperand;
    struct symtbr* symType;
    struct symtbr* symEntry;
    union 
    {    
        int intVal;
        double floatVal;
        char charVal;
        char stringVal[16];
    }val;
} *TOKEN;
```

* tokenNo：对于每一种TOKEN我都进行了编号以存储TOKEN信息。例如，ID的编号为258，左括号LP的编号为263等等。在后续处理中通过tokenNo字段我可以得知这是什么TOKEN

* tokenType：根据TOKEN存储信息和功能的不同，我将TOKEN分为了几个类型

    | token 类型 | 编号 | 说明   |
    | ---------- | ---- | ------ |
    | OPERATOR   | 0    | 操作符 |
    | DELIMITER  | 1    | 分隔符 |
    | RESERVED   | 2    | 保留字 |
    | TOKEN_ID   | 3    | ID     |
    | TOKEN_STR  | 4    | 字符串 |
    | TOKEN_NUM  | 5    | 数字   |
    | TOKEN_CHAR | 6    | 字符   |

* dataType：记录TOKEN中存储的数据的类型，包括 INT, FLOAT, CHAR, BOOL 与 STRING。这个字段与之后的 val 字段结合，可以确定 TOKEN 中存储的数据。

* next：指向语法树结构中当前节点的下一个兄弟的指针

* firstOperand：指向语法树结构中当前节点的第一个儿子的指针

* symType：若该TOKEN对应一个 Symbol，则该字段指向对应于此 Symbol 的数据类型的Symbol（符号表中所有基础数据类型和自定义的数据类型都由一个专门的 Symbol 表示）

* symEntry：若该TOKEN对应一个 Symbol，该字段指向那个 Symbol

* val：若该 TOKEN 存储有数据，则存储在此处。数据最大为16个字符大小。
  ​	

#### 1.2 正则规则

 ​	因为 PASCAL 是大小写不敏感语言，因此我用诸如 ``` A   [Aa]``` 的规则来忽略大小写差异的匹配字母。 ​对于字符串，我只匹配开头的```\'``` ，之后的具体处理在匹配时完成



#### 1.3 匹配并创建TOKEN 

 	​	函数```int install_tokenVal(int type, int tokenNumber)``` 用于创建并初始化一个TOKEN，参数 type 代表 TOKEN 的类型，对应于 TOKEN 数据结构中的 tokenType ，tokenNumber 对应 TOKEN 数据结构中的 tokenNo 。

 ​	在匹配分隔符，操作符以及保留词类型的 TOKEN 时，通过调用上述函数创建对应的 TOKEN  ,以左括号（ LP ）为例：

 ```c
 "("			{ return install_tokenVal(DELIMITER,LP); }
 ```

 ​	左括号属于分隔符的一种，所以 tokenType 应当是 DELIMITER，同时左括号自身的 tokenNo 就是 LP 对应的编号。这样通过 tokenType 字段我可以得知该 TOKEN 属于分隔符， 当我关心这具体是一个什么分隔符的时候，我可以通过 tokenNo 字段得知它是一个 LP。

 ​	特别说明一点，在上述函数中，如果传入的是一个 RESERVED 类型的 TOKEN ，那么我除了初始化 tokenNo 字段和 tokenType 字段外，还会将该保留词以字符串形式存入 val 字段。

 ​	对于ID， 数字， 字符和字符串， 匹配到之后也需要新建并初始化一个TOKEN。思路仍旧是根据匹配到的内容初始化TOKEN中的字段，细节在此不做赘述。



#### 1.4 词法分析报错
​    用 lineCount 变量记录当前词法分析匹配到第几行。 当匹配到换行符或者整行注释时 lineCnt+1 。这样当匹配到非法字符时，可以打印出在第几行出现了词法分析错误。

****





## 二、语法分析

1. **TOKEN的声明**  

在 yacc 文件的第二部分需要声明会匹配到的各种 TOKEN ，这里我声明了在词法分析中会返回的 TOKEN 。这里的 TOKEN 名字必须与 lex 中匹配到相应 TOKEN 时返回的一样， 也必须与之后语法中出现的终结符名字一样。

   

2. **语法**

语法规则按照提供的 PASCAL_syntax.txt 规定。

   

3. **语法树结构**

本部分将阐述我们语法树的抽象结构，即面对不同代码段时将大概形成何种语法树结构。  
首先介绍语法树的数据结构,以下为token节点内的两个指针，一个为next，另一个为firstOperand，其中first指向其大儿子，firstOperand指向其兄弟。一般来说，next指向的部分解释了token的内容，firstoperand指向的部分是与token同级的，并行的操作码。
以下我们将称呼next和firstOperand为token的子节点
```
    struct tokenstruct* next;
    struct tokenstruct* firstOperand;
```
接下来我们将举例不同的代码生成的语法树结构
#### 3.1 assign，四则运算操作
assign，当出现形如a:=b的代码时，形成的是以:=为父节点，a为父节点operand，b为父节点firstOperand->next的结构
```
//表达式a:=b
:=
a   b
//表达式c:=a+b
:=
c   +
    a   b
```
#### 3.2 出现不同类型的赋值运算
当出现向浮点数赋值整形数的操作时，需要添加float操作符节点以进行类型转换
```
//int a;float b;b:=a
:=
b   OP_FLOAT
    a
```
#### 3.3 数组操作
出现数组时，其两个操作数分别为数组名与offset，需要注意的是，这里offset的值是偏移的字节量
```
//a:array[1..10] of integer;int b;....;b:=a[1];
:=
b   OP_AREF
    a       4
//int占据4个字节
```
#### 3.4 if操作
出现if语句时，其三个子节点分别为判断语句，正确部分的代码，else部分的代码
```
//if x<2 then y:=1 else y:=2 end;
OP_IF
<       :=      :=
x   2   y   1   y   2
```
#### 3.5 repeat/while/for语句
此类循环语句都是在if语句的基础上加上label进行跳转的，在此以repeat为例,如果until的条件满足，他将执行if为true的内容，即剩余的代码段，否则执行goto代码回到repeat开头
```
//repeat x:=x+1 until x<20
label   :=          if
1       x   +       <       progn   goto
            x   1   x   20          1
```

#### 3.6 function函数声明
当遇到函数声明时，它会先生成函数声明操作符FUNCTION，随后各个节点分别为函数作用域，函数名，形参类型，形参名字
```
//function fname(i : integer): integer;
OP_FUNCL
FUNCTION
2       fname   integer i
//2代表符号表的第2层，第0层为系统定义，第1层为整个程序
```

   

4. **语法分析报错**

​    与词法分析报错类似，通过 lineCount 变量确定在第几行出现了错误， 在 yyerror 函数进行打印。

****



## 三、语义分析

​    本段主要介绍如何结合语法分析，生成特定的语法树结构，并确保语法树上每一个节点 TOKEN 内各个字段的数据正确无误。

#### 3.1 符号表相关

##### 3.1.1 符号表数据结构

```c
typedef struct symtbr {
	struct symtbr *link;
	char   nameString[16];
	int    kind;                /* kind of symbol -- see defines. */
	int    basicType;             /* type code for basic data types       */
	struct symtbr *dataType;    /* pointer for more complex data types  */
	int    blockLevel;
	int    size;
	int    offset;
	union  {
		char  stringConst[16];
		int   intNum;			// also store boolean value
		double realNum;
		char charConst;
	} constval;
	int    lowBound;
	int    highBound;
} SYMBOLREC, *SYMBOL;
```

* link：指向 Symbol 列表的下一个 Symbol
* nameString：Symbol 的名字
* kind： 说明符号的种类

    | Symbol类型   | 编号 | 说明     |
    | ------------ | ---- | -------- |
    | SYM_ARGM     | 0    | 参数     |
    | SYM_BASIC    | 1    | 基础类型 |
    | SYM_CONST    | 2    | 常量     |
    | SYM_VAR      | 3    | 变量     |
    | SYM_SUBRANGE | 4    | 子范围   |
    | SYM_FUNCTION | 5    | 函数     |
    | SYM_ARRAY    | 6    | 数组     |
    | SYM_RECORD   | 7    | 记录     |
    | SYM_TYPE     | 8    | 类型     |
    | SYM_POINTER  | 9    | 指针     |
    | SYM_ARGLIST  | 10   | 参数列表 |
    
* basicType：该符号的基础类型，例如 TYPE_INT, TYPE_CHAR
* dataType：指向一个代表该符号的类型的符号
* blocklevel：该符号所在的作用域
* size：该符号的大小
* offset：该符号在作用域数组中的偏移
* constval：对于 SYM_CONST 类型的符号，存储常量
* highBound\lowBound：对于 SYM_SUBRANGE 类型的符号，存储上下界

```c
int    contblock[MAXBLOCKS];  
int    blockoffs[MAXBLOCKS] = {0};  		
SYMBOL symtab[MAXBLOCKS][HASH_SIZE];    
```

* contblock[]：记录当前 Symbol 的上一层作用域是第几层

* blockoffs[]：记录每一层作用域的符号表当前存储到的位置
* symtab[] []：符号表， 每一层代表一个作用域



##### 3.1.2 符号表相关函数

1. 函数 `SYMBOL makesym(char name[])`

   ​	创建一个 Symbol ，Symbol 的名称初始化为传入的字符串

   

2. 函数``SYMBOL insertsymat(char name[], int level)``

   ​	用哈希函数计算 name 的哈希值作为该符号的插入位置，如果哈希值所在位置已经有符号，则向后顺延。知道所在作用域的符号表已满，报错。之后将符号插入 level 层作用域符号表的对应位置。

   

3. 函数 ``SYMBOL searchlev(char name[], int level)``

   ​	在指定 level 的 HASH(name) 处寻找与 name 同名的符号，若找不到则向后顺延一个位置，直到再次循环回 HASH(name) 处，这说明该符号不存在与该层符号表。

   

4. 哈希函数

   ​	符号表需要一个哈希函数计算符号在符号表中的位置。我这里使用了一个非常简单的哈希函数：哈希值为首字母在字母表中的位置。

   ```c
   int hashfun(char name[]) {
   	if (name[0] == '_') return 26;
   	return tolower(name[0])-'a';
   }
   ```

   

5. 函数 ```void initsyms()```

   ​	需要在主函数中调用该函数初始化符号表， 该函数在符号表中插入了一些事先定义的符号， 包括基础数据类型和系统函数。





#### 3.2 构建语法树
​	构建语法树的基本过程是，根据匹配到的某些语法规则，构建语法树的节点，将相关的节点按照事先定义好的结构连接起来。

##### 3.2.1 需要构建新 TOKEN \ 更改已有 TOKEN 的情况

1. 函数 ``TOKEN linkBrothers(TOKEN origin, TOKEN newSon)``

  ​	在很多地方需要将一个 TOKEN 连接到另一个 TOKEN 的最后。例如参数列表的声明：

  ```c
  para_decl_list	: para_decl_list SEMI para_type_list
  													{ $$ = linkBrothers($1, $3); }
  ```

  ​	该函数首先不断地取 next 直到 origin 的最后一个兄弟， 之后将最后一个兄弟的 next 指向 newSon。

   

2. 函数```genTokenProgram(TOKEN programHead, TOKEN routine)```

  ​	整个语法树的根是一个 tokenNo 为 OP_PROGRAM 的 TOKEN 。仅当语法分析规约到整个程序的这条规则时才会调用该函数生成程序 TOKEN 
  ```c
  program	: program_head routine DOT	   { parseresult = genTokenProgram($1, $2); }
  ```

  该函数初始化一个新的 TOKEN ， tokenNo 初始化为 OP_PROGRAM， tokenType 为 OPERATOR。 程序 TOKEN 的第一个子节点（以下称为大儿子）初始化为 program head，即程序名。 程序名所指向的兄弟节点（以下称为兄弟）初始化为程序对应的 routine ,即代码段。

  

3. 函数```TOKEN genTokenFuncDecl(TOKEN head, TOKEN body)```

   ​	当语法分析规约到函数定义或者过程定义时，需要在语法树上生成一个代表该函数定义的子树：

   ```c
   function_decl	: function_head SEMI sub_routine SEMI
   													{ $$ = genTokenFuncDecl($1, $3); }
   procedure_decl	: procedure_head SEMI sub_routine SEMI
   													{ $$ = genTokenFuncDecl($1, $3); }
   ```

   ​	该函数生成一个 tokenNo 为 OP_FUNDCL 的 TOKEN ，大儿子指向 head ，即函数头，第二个儿子是函数体代码段。

   ​	同时需要将符号表的指针指向下一层符号表的起始位置。

   

4. 函数 ```TOKEN genTokenProgn(TOKEN token, TOKEN stmtToken)```

   ​	progn 指一个代码段，即在 BEING 和 END 之间的一段代码。因此只有在语法分析规约到 BEGIN END 时调用该函数

   ```C
   compound_stmt	: BEGIN_T stmt_list END				{ $$ = genTokenProgn($1, $2); }
   ```

   ​	该函数与构建程序 TOKEN 类似，只不过代码段并没有名字，因此大儿子变成了 stmtToken，即之后的一系列语句。

   

5. 函数 ```TOKEN genTokenUnaryOp(TOKEN op, TOKEN lhs)```

   ​	当语法分析规约到一元操做符时，调用该函数生成一个对应操作符的 TOKEN

   ```c
   				| NOT factor						{ $$ = genTokenUnaryOp($1, $2); }
   				| MINUS factor						{ $$ = genTokenUnaryOp($1, $2); }
   ```

   ​	因为 op 一定是一个在词法分析时创建过的 TOKEN， 这里只需要将它的大儿子指向操作数 lhs 即可。

   

6. 函数 ```TOKEN genTokenBinOperator(TOKEN op, TOKEN left, TOKEN right)```

   ​	因为语法树里面所有的二元操作符树结构都一样，因此当规约到所有的二元操作符时都可以调用该函数。例如最普通的加减乘除二则运算

   ```c
   expression		: expression GE expr	{ $$ = genTokenBinOperator($2, $1, $3); }
   				| expression GT expr	{ $$ = genTokenBinOperator($2, $1, $3); }
   				| expression LE expr	{ $$ = genTokenBinOperator($2, $1, $3); }
   				| expression LT expr	{ $$ = genTokenBinOperator($2, $1, $3); }
   				| expression EQ expr	{ $$ = genTokenBinOperator($2, $1, $3); }
   				| expression NE expr	{ $$ = genTokenBinOperator($2, $1, $3); }
   				| expr					{ $$ = $1; }
   				;
   ```

   ​	当然，更为普遍的二元操作也调用该函数，例如赋值操作

   ```c
   assign_stmt	: ID ASSIGN expression	{ $$ = genTokenBinOperator($2, findId($1), $3); }
   ```

   ​	因为这里的 op 一定是一个现有的 TOKEN ，所以我们不需要新建一个 TOKEN， 只需要对 op 进行更改。二元运算涉及到两个操作数类型是否匹配的问题。若两个操作数类型不匹配时，调用 ```TOKEN binTypeCoerce(TOKEN op, TOKEN lhs, TOKEN rhs)``` 插入一个类型转换的 TOKEN 以进行强制类型转换。之后将 op 的大儿子指向第一个操作数， 大儿子的兄弟指向第二个操作数。op 代表整个二元操作，他的 dataType 为 操作数计算结果的 dataType。

   

7. 函数 ```TOKEN genTokenFuncall(TOKEN token, TOKEN funToken, TOKEN parasToken)```

   ​	当语法分析规约到函数调用或者过程调用时， 需要产生一个 TOKEN 代表函数\过程的调用。以带参数的函数调用为例

   ```c
    ID LP args_list RP				{ $$ = genTokenFuncall($2, $1, $3); }
   ```

   ​	该函数需要先在符号表中搜索 ID 对应的符号，之后可以获得 ID 代表的函数的返回值类型作为新建的 TOKEN out 的dataType 。out 的大儿子为函数名 ID， 二儿子为参数列表 args_list。

   

8. 函数 ```TOKEN genTokenIF(TOKEN token, TOKEN expToken, TOKEN thenToken, TOKEN elseToken)```

   ​	当语法分析遇到 IF 语句时需要插入一个子树代表 IF 语句

   ```c
   if_stmt			: IF expression THEN stmt else_clause		
   												{ $$ = genTokenIF($1, $2, $4, $5); }
   ```

   ​	函数新建一个 tokenNo 为 OP_IF 的 TOKEN, tokenType 初始化为 OPERATOR， 该 TOKEN 的三个儿子依次为 expression, stmt 和 else_clause。

   

9. 函数 ```TOKEN genTokenRepeat(TOKEN stmtToken, TOKEN exprToken)```

   ​	当语法分析规约到 REPEAT...UNTIL 语句时调用该函数在语法树中插入子树

   ```c
   repeat_stmt		: REPEAT stmt_list UNTIL expression	{ $$ = genTokenRepeat($2, $4); }
   ```

   ​	对于 REPEAT 语句，并没有定义新的语法树， 而是藉由 IF TOKEN 和 goto TOKEN 组合出 IF 语句的逻辑。

   ```c
       TOKEN labelToken = makeLabel(); //this label shoule be at end of expr
       TOKEN gotoToken = makeGoto(labelToken->firstOperand->val.intVal);
       TOKEN temp = talloc();
       TOKEN notDoToken = makeOp(OP_PROGN);
       TOKEN doToken = genOperatorToken(OP_PROGN);
       TOKEN repeatToken = genTokenProgn(temp,stmtToken);   
       TOKEN ifToken = genOperatorToken(OP_IF);
       ifToken = genTokenIF(ifToken,exprToken,notDoToken,NULL);
       labelToken->next = stmtToken;;
       notDoToken->link = gotoToken;
       goToLastBrother(stmtToken)->next = ifToken;
   
       return repeatToken;
   ```

   ​	IF 语句的条件是 UNTIL 部分的判断语句， IF 语句判断成功执行的语句为 notDoToken， 失败不执行语句。 notDoToken 是一个新建的 progn 类型 TOKEN， 代表 UNTIL 之后的语句。

    

10. 函数 ```TOKEN genTokenWhile(TOKEN exprToken, TOKEN stmtToken)```

      当语法分析规约到 WHILE DO 语句时，调用该函数在语法树中插入一个代表 WHILE DO 的子树

    ```c
    while_stmt		: WHILE expression DO stmt			{ $$ = genTokenWhile($2, $4); }
    ```

    ​	与 REPAET 语句相同， 这里仍然藉由 IF 和 goto 实现 WHILE DO

    ```c
        TOKEN labelToken = makeLabel(); //this label shoule be at begin of stmt
        TOKEN gotoToken = makeGoto(labelToken->firstOperand->val.intVal);
        TOKEN whileToken = genTokenProgn(talloc(),labelToken);
        TOKEN doToken = genOperatorToken(OP_PROGN);
        TOKEN ifToken = genOperatorToken(OP_IF);
        ifToken = genTokenIF(ifToken,exprToken,doToken,NULL);
        labelToken->next = ifToken;
        doToken->firstOperand = stmtToken;
        goToLastBrother(stmtToken)->next = gotoToken;
    
        return whileToken;
    ```

    

11. 函数 ```TOKEN genTokenFor(TOKEN assignToken, TOKEN dirToken, TOKEN experToken, TOKEN stmtToken)```

    ​	当语法分析规约到 for 语句时调用该函数在语法树中插入代表 for 语句的子树

    ​	与 REPEAT 语句类似，这里仍旧以 IF 语句和 goto 实现 for 语句

    ```c
        if(DEBUG){
            printf("start genTokenFor\n");
        }	
    	int sign = 1;
    	if (strcmp("to", dirToken->val.stringVal) == 0) sign = 1;
    	else if (strcmp("downto", dirToken->val.stringVal) == 0) sign = -1;
    	
    	TOKEN for_asg_progn_tok = genTokenProgn(talloc(), assignToken);
    	TOKEN label_tok = makeLabel();
    	
    	TOKEN stop_op_tok = genOperatorToken(OP_LE);
    	TOKEN do_progn_tok = genTokenProgn(talloc(), stmtToken);
    	TOKEN ifop_tok = genTokenIF(genOperatorToken(OP_IF), stop_op_tok, do_progn_tok, NULL);
    	
    	TOKEN loop_stop_tok = TokenCopyConstruct(assignToken->firstOperand); // the counter var, eg "i" in trivb.pas
    	TOKEN stmt_incr_tok = makeLoopIncr(assignToken->firstOperand, sign);
    	TOKEN goto_tok;
    	
    	if (!for_asg_progn_tok || !label_tok || !ifop_tok || !stop_op_tok ||
    	!do_progn_tok || !loop_stop_tok || !stmt_incr_tok) {
    		printf(" Failed to alloc TOKEN(s), makeFor().\n");
    		return NULL;
    	}
    	
    	goto_tok = makeGoto(label_tok->firstOperand->val.intVal);  // TODO: not null-checked
    	
    	if (sign == -1) {
    		stop_op_tok->tokenNo = OP_GE;   // "downto"
    	}
    	
    	/* Link all the tokens together. */
    	assignToken->next = label_tok;
    	label_tok->next = ifop_tok;
    	stop_op_tok->firstOperand = loop_stop_tok;
    	loop_stop_tok->next = experToken;
    	
    	/* Handle elimination of nested progns */
    	if (do_progn_tok->tokenNo != OP_PROGN) {
    		do_progn_tok->firstOperand = stmtToken;
    		stmtToken->next = stmt_incr_tok;
    	}
    	else {   // do_progn_tok == statement
    		goToLastBrother(do_progn_tok->firstOperand)->next = stmt_incr_tok;
    	}
    	stmt_incr_tok->next = goto_tok;
        if(DEBUG){
            printf("end genTokenFor\n");
        }		
    	return for_asg_progn_tok;
    ```

    ​	IF 语句的判断条件为操作符 TOKEN stop_op_token， 其值为GE 或 LE， 这取决于 dirToken 的内容是 to 还是 downto， stop_op_token 的大儿子是 assignToken 的大儿子，即循环变量；二儿子是 exprToken 即循环终止值。 IF 语句判断成功执行的语句即 stmtToken。 构建一个新的 TOKEN stmt_incr_tok 代表对循环变量的自增\减，插入在循环体的最后，即 stmt_incr_tok 插入在 stmtToken 最后一个兄弟的后面。

    

12. 函数 ```TOKEN arrayRef(TOKEN arr, TOKEN tok, TOKEN subs, TOKEN tokb)```

    ​	当语法分析规约到数组索引时需要调用该函数返回一个代表索引结果的 TOKEN 

    ​	数组索引首先需要做的是在符号表中找到 TOKEN arr 的名字所代表的 Symbol ，若该数组只有一维， 那么subs 没有兄弟。 subs 所存储的数字减去 arr 对应 Symbol 的 lowbound ，再乘上该数组每个元素的 size 就是所索引元素在数组中的偏移量 offset。

    ​	

##### 3.2.2 需要构建Symbol并插入符号表的情况

1. 函数 ``` void genSymConst(TOKEN IDtoken, TOKEN constToken)```

   ​	在语法分析规约到声明常量时需要向符号表中插入新建的符号

   ```c
   const_expr_list	: const_expr_list ID EQ const_value SEMI
   													{ genSymConst($2, $4); }
   				| ID EQ const_value SEMI			{ genSymConst($1, $3); }
   ```

   ​	在符号表中新建名为 IDtoken 的 sym，kind 为 SYM_CONST 。根据 constToken 的 dataType 设置 sym 的 basicType， constval 和 size 等字段。 

   

2. 函数 ```void genSymType(TOKEN typeName, TOKEN typeToken)```

   ​	在语法分析规约到声明自定义类型时需要向符号表插入新建的符号

   ````c
   type_definition	: ID EQ type_decl SEMI				{ genSymType($1, $3); }
   ````

   ​	该函数需要先在函数表中查找 typeName 对应的Symbol， 若找到同名 Symbol 则返回语义分析错误重定义。

   ​	新建并向符号表中插入 typeName 为名的Symbol。 用 typeToken 的 symType 指向的符号的信息去初始化新建 Symbol 的字段。

   

3. 函数 ```TOKEN genSymEnum(TOKEN IDs)```

   ​	在语法分析规约到声明枚举类型时需要向符号表插入新建的符号。

   ​	函数遍历 IDs 和它的所有兄弟， 并递增地为每一个兄弟构建一个 CONST_INT 的 Symbol。

   

4. 函数 `TOKEN genSymArray(TOKEN bounds, TOKEN typetok)`

   ​	在语法分析规约到声明数组时需要产生一个数组类型的 TOKEN 

   ​	该函数并没有向符号表中插入新的 Symbol ， 但是它根据 typetok 的 symtype 和 bounds 新建并初始化一个 Symbol， 之后将返回的 TOKEN 的 Symtype 指向该 Symbol。 后续的规约中会用到这个 Symbol。

   ​	

5. 函数 `void genSymVars(TOKEN IDs, TOKEN typeToken)`

   ​	在语法分析规约到声明变量时需要向符号表中插入新建的符号

   ```c
   var_decl		: id_list COLON type_decl SEMI		{ genSymVars($1, $3); }
   ```

   ​	函数遍历 id_list IDs 的每一个兄弟， 对每一个兄弟新建一个 Symbol, 并根据 typeToken 初始化 Symbol。

   

6. 函数 `TOKEN genSymFunc(TOKEN head)`

   ​	在语法分析规约到声明函数\过程时需要新建符号并插入符号表

   ```c
   function_head	: FUNCTION ID parameters COLON simple_type_decl
   		{ $$ = genSymFunc(linkBrothers($1, linkBrothers($2, linkBrothers($5, $3)))); } // FUNCTION, ID, type, para
   				;
   procedure_decl	: procedure_head SEMI sub_routine SEMI
   													{ $$ = genTokenFuncDecl($1, $3); }
   ```

   ​	以函数声明为例， 将 FUNCTION关键词，函数名，返回类型和参数列表连接起来后作为参数传给 genSymFunc(TOKEN head)

   ​	函数为参数列表的每一个 TOKEN 创建临时的 Symbol 并通过 dataType 字段将它们连接起来。 之后调用insertfnx()， 将函数名， 返回值类型的 Symbol 和刚刚创建的 Symbol 列表传入， 以在符号表插入该函数。

****

## 四、语法树可视化
本工程提供语法树的可视化操作，可以将语法树打印出来。考虑到我们生成的语法树的结构是左儿子右兄弟结构，而且语句条与条之间是兄弟排列（横向排列）的，所以如果按照树的形象结构打印出来的话，在函数内语句很多的情况下，语法树在横向上会很长且无法在一行完整打印。  
鉴于这些问题，我们按行紧凑打印每个节点的信息。为了区分本行的节点是上面一行哪个节点的儿子，我们需要在第一个儿子前标注上自己是哪个父亲的儿子。具体打印效果如一下例子所示
#### 以下为一段简短的pascal代码
```
program testx;
var
	x: integer;
    y: integer;
begin
    x:=21+3;
    y:=5;
end
.
```
#### 它打印出来的结果如图所示
```
--------------print AST------------------
program 
[col0 program]testx progn 
[col1 progn]:= := 
[col0 :=]x + [col1 :=]y 5 
[col1 +]21 3 
```
第0行为程序标示符号 program ，第1行的testx表示程序名叫做testx，随后的progn连接着程序的代码段，这两个节点属于program的儿子；第2行两个赋值符号表示两个赋值语句，且都属于程序代码段；第3行的第一个 x，+ 符号都属于上面一行第0列的赋值操作符的儿子，随后的y和5都属于第1列赋值操作符的儿子；第4行的21与3都属于第3行 + 操作符的儿子。
#### 其等同于以下语法树的形象表示
|||||||
|-|-|-|-|-|-|
|program||||||
|testx|progn|||||
||:=|||:=||
||x|+||y|5|
|||21|3|||


## 五、中间代码生成 
本部分我们将生成三地址码，由于我们不再生成目标代码，所以我们生成的中间代码将以文本的形式输出。  
生成中间代码的过程可以理解为遍历语法树的过程，在遍历过程中我们将针对节点中存储的不同信息进行对应的处理。这一过程发生在以下函数中
```
void genc(TOKEN tok,char *ret);
//tok为当前遍历所处在的节点，ret为从当前节点向父节点以字符串形式返回自己的信息，信息具体如何处理交由父亲操作
```
当我们遍历到一个节点时它属于如下几种类型之一：  
1.operator  
2.num/str/char/identifier  
3.reserved
我们将分别讨论上述情况如何处理生成中间代码  
#### 5.1节点为operator
当节点是操作符时，我们需要根据操作符的含义来处理子节点们返回的信息，并将其转化为中间代码输出到文件中。  

5.1.1.操作符是加减乘除，赋值，以及判断大于等运算符时  
我们需要将子节点返回回来的数据结合运算符组成一个三地址码。此时我们往往需要一个临时寄存器存储计算的结果，并将该式子输出到文件中；最后，我们将临时寄存器返回父亲节点，以便递归调用。
```
//以减号处理为例
case OP_MINUS:
	genc(tok->firstOperand,lop);
    //当减号只有单个操作数时，说明这表示一个负数
	if(tok->firstOperand->next==NULL){
		fprintf(INTCODE,"t%d =0 - %s\n",rnum,lop);//组成一个三段码
		sprintf(ret,"t%d",rnum);//返回临时寄存器
		rnum++;
		return;
	}
    //当减号有两个操作数时，表示这进行了减法操作
	genc(tok->firstOperand->next,rop);
	fprintf(INTCODE,"t%d =%s - %s\n",rnum,lop,rop);//组成一个三顿码
	sprintf(ret,"t%d",rnum);//返回临时寄存器
	rnum++;
	return;
	break;
```

5.1.2.操作符是类型强制转换类  
类型强制转换类包括fix，与float两种token，这两种操作符进行整型与浮点数之间的转换，其语法树结构是将转换后的数字挂在其大儿子处，所以只需要直接返回其子节点即可
```
case OP_FLOAT:
    genc(tok->firstOperand,lop);
    sprintf(ret,"%s",lop);
    return;
```

5.1.3.操作符是数组
当操作符是数组时，其儿子为数组名，次儿子为偏移量，我们只需要将偏移的目标地址存储到目标寄存器中，随后将目标寄存器代表地址加上*返回（即取内容返回）
```
case OP_AREF:
    genc(tok->firstOperand,lop);
    genc(tok->firstOperand->next,rop);//
    fprintf(INTCODE,"t%d =&%s + %s\n",rnum,lop,rop);
    sprintf(ret,"*t%d",rnum++);
    break;
```

5.1.4.操作符是if
当操作符是if时，其三个儿子分别为判断语句，判断语句为true时执行的代码段，判断语句为false执行的代码。结合书上的内容，我们将其翻译为if_false_goto的形式，首先我们需要自己生成一个label，并在false代码段前加上这个label；同时在true代码段后加上默认跳转到结尾的默认标签处
```
case OP_IF://if语句
    genc(tok->firstOperand,lop);//判断条件
    lfalse=lnum++;
    fprintf(INTCODE,"if_false %s goto L%d\n",lop,lfalse);
    genc(tok->firstOperand->next,rop);//true代码段

    //如果有else代码段
    if(tok->firstOperand->next->next!=NULL){
        ldefault=lnum++;
        fprintf(INTCODE,"goto L%d\n",ldefault);
    }	

    fprintf(INTCODE,"LABEL L%d\n",lfalse);//false标签

    if(tok-firstOperand->next->next!=NULL){
        genc(tok->firstOperand->next->next,top);			
        fprintf(INTCODE,"LABEL L%d\n",ldefault);
    }
    break;
```

5.1.5.操作符是LABEL和GOTO
当操作符是标签时，说明这是程序给出的标签，那么输出此标签即可，为了区别于if的标签，此标签我们加上SYS_的前缀
当操作符是goto时，其子节点存的是label的编号，那么输出其label编号即可

5.1.6.操作符是函数调用
当操作符函数调用时，其子节点分别为函数名和实参，此时分别输出子节点的信息，再使用临时寄存器存储函数的返回值，返回临时寄存器

#### 5.2 节点为str/char/identifier/num
使用字符串的形式和sprintf函数返回节点存放的数据
```
else if(tok->tokenType==TOKEN_ID){		
    sprintf(ret,"%s",tok->stringval);
    return;
}
```
#### 5.3 节点为保留字
当节点为函数声明时，其子节点分别为函数名，函数参数等等，我们需要按顺序输出其子节点，为了区别这是函数声明，我们在前后加上下划线
```
if(strcmp(tok->stringval,"function")==0){
    fprintf(INTCODE,"_FUNCTION");
    sub=tok->firstOperand->next;
    while(sub){
        genc(sub,lop);
        fprintf(INTCODE,"_%s",lop);
        sub=sub->next;
    }
    fprintf(INTCODE,"_\n");
}
```
#### 5.4 其他处理细节
处理临时寄存器和if生成的label编号时，我们使用了两个数组rnum和lnum记录使用过的寄存器编号，这部分其实还有可以优化的余地，即考虑到实际的硬件设置，我们应该限制寄存器的个数，同时考虑到寄存器使用时间段，在临时寄存器使用完毕后释放掉它。

****
## 六、测试案例
#### 6.1测试数组
```
源代码
program test5;
var 
    student:array[1..10] of integer;

begin
    student[1] := 1;
    student[3] := 3;
end
.

AST：

--------------print AST------------------
program 
[col0 program]test5 progn 
[col1 progn]:= := 
[col0 :=]aref 1 [col1 :=]aref 3 
[col0 aref]student 0 [col2 aref]student 8



中间代码：
__MAIN__
t0 =&student + 0
*t0 = 1
t1 =&student + 8
*t1 = 3
```

#### 6.2测试const，函数定义，函数调用
```
源代码
program test3;
const cst = 1919;
type int=integer;
var
	i : int;
    j : int;
function go(a : int): int;
var
	b : integer;
	c : integer;
begin
    b := 0;
    while a<10 do
    begin
        a := a+cst;
        c := a*3;
        b := b+c;
    end
    ;
end
;

begin
    for j := 0 to 10 do
    begin 
	    i := go(10);
	    writeln(i);
    end
    ;
end
.

AST：
program 
[col0 program]test3 fundcl progn 
[col1 fundcl]function progn [col2 progn]progn 
[col0 function]2  go  int  a [col1 progn]:= progn [col2 progn]:= label if 
[col4 :=]b 0 [col5 progn]label if [col6 :=]j 0 [col7 label]2 [col8 if]<= progn 
[col2 label]1 [col3 if]< progn [col7 <=]j 10 [col8 progn]progn := goto 
[col1 <]a 10 [col2 progn]progn goto [col5 progn]:= funcall [col6 :=]j + [col7 goto]2 
[col2 progn]:= := := [col3 goto]1 [col4 :=]i funcall [col5 funcall]writeln i [col7 +]j 1 
[col0 :=]a + [col1 :=]c * [col2 :=]b + [col5 funcall]go 10 
[col1 +]a 1919 [col3 *]a 3 [col5 +]b c


中间代码
_FUNCTION_go_int_a_
b = 0
LABEL SYS_L1
t0=a<10
if_false t0 goto L0
t1 =a + 1919
a = t1
t2 =a * 3
c = t2
t3 =b + c
b = t3
goto SYS_L1
LABEL L0
__MAIN__
j = 0
LABEL SYS_L2
t4=j<=10
if_false t4 goto L1
t5=go 10
i = t5
t6=writeln i
t7 =j + 1
j = t7
goto SYS_L2
LABEL L1


```
#### 6.3测试x未定义
```
源代码
program test7;
var
	i : integer;
    f : real;
    r : real;

begin
	x := i+f;
	writeln(r);

end
.

报错：

semantic Error at line 8: var "x" not defined


```
#### 6.4测试x重定义报错
```
源代码
program test8;
var
	i : integer;
    f : real;
    r : real;
    i : real;

begin
	x := i+f;
	writeln(r);

end
.


报错：

semantic Error at line 6: redefinition of var "i"

```