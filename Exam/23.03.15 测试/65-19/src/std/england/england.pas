var
a:array[0..100005]of longint;
f:array[0..100005,0..55]of longint;
n,i,j,max:longint;

procedure init;
        begin
        readln(n);
        for i:=1 to n do read(a[i]);

        fillchar(f,sizeof(f),0);
        end;

procedure main;
        begin
        for i:=1 to a[1] do f[1,i]:=i;
        max:=a[i];

        for i:=2 to n do
        for j:=1 to a[i] do
                begin
                if f[i,j]<f[i-1,j]+j then
                   f[i,j]:=f[i-1,j]+j;
                if f[i,j]>max then max:=f[i,j];
                end;
        end;

procedure print;
        begin
        writeln(max);
        end;

begin
assign(input,'england.in'); reset(input);
assign(output,'england.out'); rewrite(output);
init;
main;
print;
close(input); close(output);
end.
