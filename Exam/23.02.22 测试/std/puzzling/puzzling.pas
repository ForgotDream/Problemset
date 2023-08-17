Program Puzzling;
const
  inf='puzzling.in';
  ouf='puzzling.out';
type
  lx=record
    x,y:integer;
    dt:array[1..5,1..5] of word;
  end;

var
  a:array[1..5] of lx;
  c:array[1..9,1..9] of word;
  bc,n:integer;

Procedure Outp(t:integer);
var
  i,j:integer;
begin
  Assign(output,ouf);
  Rewrite(output);
  if t=-1 then Writeln('No solution possible')
         else
           If t=-2 then Writeln('1') else
           begin
             for i:=1 to bc do
               begin
                 for j:=1 to bc do Write(c[i,j]);
                 Writeln;
               end;
           end;
  Close(output);
end;

Procedure Init;
var
  i,j,k,mj:integer;
  ch:char;
begin
  Assign(input,inf);
  Reset(input);
  mj:=0;
  read(n);
  for i:=1 to n do
    begin
      readln(a[i].x,a[i].y);
      for j:=1 to a[i].x do
      begin
        for k:=1 to a[i].y do
          begin
            read(ch);
            if ch='1' then a[i].dt[j,k]:=1 else a[i].dt[j,k]:=0;
            if a[i].dt[j,k]=1 then mj:=mj+1;
          end;
        readln;
      end;
    end;
  bc:=trunc(sqrt(mj));
  if bc<>sqrt(mj) then begin Outp(-1); halt; end;
  if mj=1 then begin Outp(-2); halt; end;
  Close(input);
end;

Function CanPut(x,y,w:integer):boolean;
var
  i,j:integer;
begin
  if (a[w].x+x-1)>bc then begin CanPut:=false; exit; end;
  if (a[w].y+y-1)>bc then begin CanPut:=false; exit; end;
  for i:=x to (a[w].x+x-1) do
    for j:=y to (a[w].y+y-1) do
      begin
        if a[w].dt[i-x+1,j-y+1]=1 then
          if c[i,j]<>0 then begin CanPut:=false; exit; end;
      end;
  CanPut:=true;
end;

Procedure PutInMap(x,y,w:integer);
var
  i,j:integer;
begin
  for i:=x to (a[w].x+x-1) do
    for j:=y to (a[w].y+y-1) do
        if a[w].dt[i-x+1,j-y+1]=1 then c[i,j]:=w;
end;

Procedure dfs(b:integer);
var
  i,j:integer;
  temp:array[1..9,1..9] of word;
begin
  if b>n then
    begin Outp(b); halt; end;
  for i:=1 to bc do
    for j:=1 to bc do
        if CanPut(i,j,b) then
          begin
            temp:=c;
            PutInMap(i,j,b);
            dfs(b+1);
            c:=temp;
          end;
end;

begin
  Init;
  dfs(1);
  Outp(-1);
end.
