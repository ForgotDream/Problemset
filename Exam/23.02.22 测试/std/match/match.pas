program lx;
var
  inf,outf:text;
  table:array[1..499,1..499] of longint;
  data:array[1..499] of longint;
  n,m,t:longint;

procedure init;
var
  temp,i,x:longint;
begin
  readln(inf,n,m,t);
  fillchar (table,sizeof(table),0);
  for i:=1 to n do
  begin
    readln(inf,temp);
    table[i,m]:=temp;
    table[i,temp]:=m;
    if (temp=m) then x:=i;  
  end;
  temp:=1;i:=x;
  repeat
    data[temp]:=table[i,m];
    inc(i);inc(temp);
    if (i>n) then i:=1;
  until (i=x);
end;

function get_temp(x:longint):longint;
var
  i:longint;
begin
  for i:=1 to n do
  if (table[i,m]=x) then begin
			   get_temp:=i;
			   break;
			 end;
end;

procedure main;
var
  i,j,temp:longint;
begin
  for i:=1 to n do
  if (i<>m) then
  begin
    temp:=get_temp(i);
    for j:=1 to n do
    begin
      table[temp,i]:=data[j];
      inc(temp);
      if (temp>n) then temp:=1;
    end;
  end;
end;

procedure print;
var
  i:longint;
begin
    write (outf,table[t,1]);
    for i:=2 to n do write(outf,' ',table[t,i]);
end;

begin
  assign(inf,'match.in');
  assign(outf,'match.out');
  reset(inf);
  rewrite(outf);
  init;
  main;
  print;
  close(inf);
  close(outf);
end.