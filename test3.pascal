//测试常量
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