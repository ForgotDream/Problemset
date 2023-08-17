program compare;
const
  inf='compare.in';
  ouf='compare.out';
  infinite=maxlongint*maxlongint;
var
  n,m,time:longint;
  a:array[1..1000,1..1000]of extended;
  ans:extended;
  s:ansistring;
procedure int;
var
  i,j,k:longint;
begin
  read(n,m,time);
  for i:=1 to n do
    for j:=1 to n do
      if i<>j
        then a[i,j]:=-1;
  for i:=1 to m do
    begin
      read(j,k);
      read(a[j,k]);
      a[k,j]:=a[j,k];
    end;
  readln;
end;
function calc(s:ansistring):extended;
var
  i,j,k,t:longint;
  long:extended;
begin
  k:=length(s);
  for i:=1 to k do
    if not(s[i] in ['0'..'9',' '])
      then exit(infinite);
  while s[1]=' ' do delete(s,1,1);
  i:=0;
  while s[1]<>' ' do
    begin
      i:=i*10+ord(s[1])-ord('0');
      if i>n then exit(infinite);
      delete(s,1,1);
    end;
  long:=0;
  if i<>1 then exit(infinite);
  while length(s)>0 do
    begin
      while (length(s)>0) and (s[1]=' ') do delete(s,1,1);
      j:=0;
      if length(s)=0
        then
          if i=n
            then exit(long)
            else exit(infinite);
      while (length(s)>0) and (s[1]<>' ') do
        begin
          j:=j*10+ord(s[1])-ord('0');
          if j>n then exit(infinite);
          delete(s,1,1);
        end;
      if a[i,j]<0
        then exit(infinite)
        else long:=long+a[i,j];
      i:=j;
    end;
  if j=n
    then exit(long)
    else exit(infinite);
end;
procedure main;
var
  i:longint;
  tmp:extended;
begin
  ans:=infinite;
  for i:=1 to time do
    begin
      readln(s);
      tmp:=calc(s);
      if tmp<ans then ans:=tmp;
    end;
  if ans=infinite
    then writeln('Wrong')
    else writeln(ans:0:4);
end;
begin
  assign(input,inf);
  assign(output,ouf);
  reset(input);
  rewrite(output);
  int;
  main;
  close(input);
  close(output);
end.
