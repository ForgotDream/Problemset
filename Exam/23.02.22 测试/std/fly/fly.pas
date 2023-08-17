program ural1119;
const maxn=1000;
var
   f:array[0..maxn] of longint;
   a:array[0..maxn,1..2] of longint;
   i,j,k,m,n,temp:longint;
   fil:text;
procedure init;
begin
     assign(fil,'fly.in');
     reset(fil);
     readln(fil,n,m);
     readln(fil,k);
     for i:=1 to k do
         readln(fil,a[i,1],a[i,2]);
     close(fil);
     for i:=1 to k-1 do
         for j:=1 to k-i do
             if (a[j,1]>a[j+1,1]) or (a[j,2]>a[j+1,2]) then
                begin
                     temp:=a[j,1];
                     a[j,1]:=a[j+1,1];
                     a[j+1,1]:=temp;
                     temp:=a[j,2];
                     a[j,2]:=a[j+1,2];
                     a[j+1,2]:=temp;
                end;
end;
procedure main;
begin
     for i:=1 to k do
         begin
              temp:=0;
              for j:=0 to i do
                  begin
                       if (a[j,1]<a[i,1]) and (a[j,2]<a[i,2]) and (f[j]+1>temp)
                          then temp:=f[j]+1;
                  end;
              f[i]:=temp;
         end;
     temp:=0;
     for i:=1 to k do 
         if f[i]>temp
            then temp:=f[i];  	
end;
begin
     init;
     main;
     assign(fil,'fly.out');
     rewrite(fil);
     writeln(fil,(m+n-2*temp+sqrt(2)*temp)*100:0:0);
     close(fil);
end.
