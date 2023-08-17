var
s,n,x,y,z,tot,i:longint;

begin
assign(input,'china.in'); reset(input);
assign(output,'china.out'); rewrite(output);
readln(s,n);
for i:=1 to n do
        begin
        readln(x,y,z);
        tot:=tot+(y-x+1)*z;
        s:=s-(y-x+1);
        end;
writeln(tot+s);
close(input); close(output);
end.
