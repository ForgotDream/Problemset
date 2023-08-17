{
ID: matrix61
PROB: kimbits
LANG: PASCAL
}
var count:array[0..31,0..31]of dword;
   len,l:integer;
   n:dword;

procedure InitCount;
var i,j,k:integer;
begin
for i:=0 to 31 do
  count[i,0]:=1;
for i:=0 to 31 do
  count[0,i]:=1;
for i:=1 to 31 do
for j:=1 to 31 do
  count[i,j]:=count[i-1,j]+count[i-1,j-1];
end;

function can(a:dword):boolean;
var st:string;
   i,s:integer;
begin
st:=binstr(a,31);
s:=0;
for i:=1 to length(st) do
  inc(s,ord(st[i]='1'));
if s<=l then can:=true
        else can:=false;
end;

function HowMany(a:dword):dword;
var st:string;
   ans:dword;
   i,s:integer;
begin 
ans:=0;
s:=l;
st:=binstr(a,31);
for i:=1 to length(st) do
  if st[i]='1' then
    begin
    inc(ans,count[length(st)-i,s]);
    dec(s); if s<0 then break;
    end;
HowMany:=ans;
end;

{====main====}
var big,small:dword;
   i:integer;
   ans:string;
begin
assign(input,'bits.in');
reset(input);
readln(len,l,n);
close(input);

InitCount;
big:=1;
for i:=1 to len do big:=big*2;
big:=big-1;
small:=0;

repeat
if HowMany((big+small)div 2)>=n
  then big:=(big+small)div 2
  else small:=(big+small)div 2;
until HowMany(big)-HowMany(small)<=1;

while not can(small) or (HowMany(small)<n-1) do inc(small);
ans:=binstr(small,31);
while (ans[1]='0') and (length(ans)>len) do delete(ans,1,1);

assign(output,'bits.out');
rewrite(output);
writeln(ans);
close(output);
end.
