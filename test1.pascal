//测试for，while，repeat循环
program test1;
var i,s:integer;
begin
	s:=0;
	for i:=1 to 10 do
		s:=s+i;
	while i<0 do begin
		s:=s-i;
		i:=i-1;
	end;
	repeat 
		i:=i+1;
	until i<20;
end
.