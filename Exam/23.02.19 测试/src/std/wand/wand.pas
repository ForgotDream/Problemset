const
   MaxN=1000;

var
   f:array[0..MaxN,0..MaxN]of int64;
   L,M:array[0..MaxN]of longint;
   n,lo,hi:longint;

procedure update(var a:int64;b:int64);
begin
   if b>a then a:=b;
end;

procedure readp;
var
   i:longint;
begin
   readln(n,lo,hi);
   for i:=1 to n do read(L[i]);
   for i:=1 to n do read(M[i]);
   for i:=1 to n do L[i]:=L[i]+L[i-1];
   for i:=1 to n do M[i]:=M[i]+M[i-1];
end;

procedure solve;
var
   i,j:longint;
begin
   for i:=1 to n do
   for j:=i to n do
   begin
      update(f[i,j],f[i-1,j]);
      if i<j then update(f[i,j],f[i,j-1]);
      if (L[j]-L[i-1]>=lo) and (L[j]-L[i-1]<=hi) then
         update(f[i,j],f[i-1,j-1]+M[j]-M[i-1]);
   end;
end;

procedure writep;
begin
   writeln(f[n,n]);
end;

{====main====}
begin
   assign(input,'wand.in');
   reset(input);
   assign(output,'wand.out');
   rewrite(output);
   readp;
   solve;
   writep;
   close(input);
   close(output);
end.
