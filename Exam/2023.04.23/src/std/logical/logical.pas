{
Problem: Stupid Family III - Logical
Algorithm: Tree-DP
Time:
}
const
  inf='logical.in';
  ouf='logical.out';
  maxn=131071; maxt=maxn;

type
  YZNode=record
    x,y,z,a:longint;
  end;

var
  Yz:array[1..maxn] of YZNode;
  Dp:array[1..maxn,0..1] of longint;
  n,m,root:longint;

Procedure AssignFile;
begin
  assign(input,inf);
  reset(input);
  assign(output,ouf);
  rewrite(output);
end;

Procedure CloseFile;
begin
  Close(input);
  Close(output);
end;

Procedure Init;
var
  i,x,y:longint;
begin
  read(n,m);
  for i:=1 to n do begin
    read(Yz[i].x,Yz[i].y,Yz[i].z,Yz[i].a);
    If Yz[i].z=0 then root:=i;
  end;

  for i:=1 to m do
    begin
      read(x,y);
      Dp[x,y]:=0; Dp[x,(y+1) mod 2]:=1;
    end;
end;

Function min(a,b:longint):longint; begin if a<b then exit(a) else exit(b); end;
Function max(a,b:longint):longint; begin if a>b then exit(a) else exit(b); end;

Procedure Dfs(v:longint);
var
  lson,rson:longint;
begin
  If Yz[v].x<>0 then
    begin
      Dfs(Yz[v].x);
      Dfs(Yz[v].y);
    end
  else exit;
  lson:=Yz[v].x;
  rson:=Yz[v].y;
  case Yz[v].a of
    1:
      begin
        Dp[v,0]:=min(min(Dp[lson,0]+Dp[rson,0],Dp[rson,0]+Dp[lson,1]),Dp[lson,0]+Dp[rson,1]);
        Dp[v,1]:=Dp[lson,1]+Dp[rson,1];
      end;
    2:
      begin
        Dp[v,0]:=Dp[lson,0]+Dp[rson,0];
        Dp[v,1]:=min(min(Dp[lson,1]+Dp[rson,1],Dp[lson,1]+Dp[rson,0]),Dp[lson,0]+Dp[rson,1]);
      end;
    3:
      begin
        Dp[v,0]:=min(Dp[lson,0]+Dp[rson,0],Dp[lson,1]+Dp[rson,1]);
        Dp[v,1]:=min(Dp[lson,0]+Dp[rson,1],Dp[lson,1]+Dp[rson,0]);
      end;
  end;
end;

Procedure Main;
begin
  Dfs(root);
end;

Procedure Outp;
begin
  Writeln(max(Dp[root,0],Dp[root,1]));
end;

begin
  AssignFile;

  Init;
  Main;
  Outp;

  CloseFile;
end.