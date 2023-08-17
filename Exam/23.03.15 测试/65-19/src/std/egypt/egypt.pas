const
z=99999999;

type

lype=record
        aa:longint;
        bb:longint;
        cc:longint;
        pp:longint;
        end;

var
a,f,s:array[0..100,0..100,0..100]of longint;
    l:array[0..100,0..100,0..100,0..10]of lype;
i,j,k,n,m,a1,b1,c1,a2,b2,c2,p,t:longint;

procedure init;
        begin
        readln(n,m);
        for i:=n downto 1 do
        for j:=1 to i do
        for k:=1 to i do
        read(a[i,j,k]);

        for i:=1 to m do
                begin
                readln(a1,b1,c1,a2,b2,c2,p);
                a1:=n+1-a1; a2:=n+1-a2;
                inc(s[a2,b2,c2]);
                l[a2,b2,c2,s[a2,b2,c2]].aa:=a1;
                l[a2,b2,c2,s[a2,b2,c2]].bb:=b1;
                l[a2,b2,c2,s[a2,b2,c2]].cc:=c1;
                l[a2,b2,c2,s[a2,b2,c2]].pp:=p;
                end;

        for i:=2 to n do
        for j:=0 to i+1 do
        for k:=0 to i+1 do
        f[i,j,k]:=z;
        end;

function min(x,y:longint):longint;
        begin
        if x<y then min:=x
               else min:=y;
        end;

procedure sos(i,j,k:longint);
        begin
        if f[i,j-1,k]<z then
        if f[i,j-1,k]>f[i,j,k]+a[i,j-1,k] then
                begin
                f[i,j-1,k]:=f[i,j,k]+a[i,j-1,k];
                sos(i,j-1,k);
                end;

        if f[i,j+1,k]<z then
        if f[i,j+1,k]>f[i,j,k]+a[i,j+1,k] then
                begin
                f[i,j+1,k]:=f[i,j,k]+a[i,j+1,k];
                sos(i,j+1,k);
                end;

        if f[i,j,k-1]<z then
        if f[i,j,k-1]>f[i,j,k]+a[i,j,k-1] then
                begin
                f[i,j,k-1]:=f[i,j,k]+a[i,j,k-1];
                sos(i,j,k-1);
                end;

        if f[i,j,k+1]<z then
        if f[i,j,k+1]>f[i,j,k]+a[i,j,k+1] then
                begin
                f[i,j,k+1]:=f[i,j,k]+a[i,j,k+1];
                sos(i,j,k+1);
                end;
        end;

procedure main;
        begin
        f[n,1,1]:=a[n,1,1];
        for j:=1 to n do
        for k:=1 to n do
        f[n,j,k]:=min(f[n,j,k],min(f[n,j-1,k],f[n,j,k-1])+a[n,j,k]);
        sos(n,j,k);

        for i:=n-1 downto 1 do
                begin
                for j:=1 to i do
                for k:=1 to i do
                        begin
                        a1:=min(f[i+1,j,k],f[i+1,j,k+1]);
                        a2:=min(f[i+1,j+1,k],f[i+1,j+1,k+1]);
                        f[i,j,k]:=min(a1,a2)+a[i,j,k];

                        for t:=1 to s[i,j,k] do
                                begin
                                a1:=l[i,j,k,t].aa;
                                b1:=l[i,j,k,t].bb;
                                c1:=l[i,j,k,t].cc;
                                p:=l[i,j,k,t].pp;
                                if f[a1,b1,c1]+p+a[i,j,k]<f[i,j,k] then
                                   f[i,j,k]:=f[a1,b1,c1]+p+a[i,j,k];
                                end;
                        end;

                for j:=1 to i do
                for k:=1 to i do
                sos(i,j,k);
                end;
        end;

procedure print;
        begin
        writeln(f[1,1,1]);
        end;

begin
assign(input,'egypt.in'); reset(input);
assign(output,'egypt.out'); rewrite(output);
init;
main;
print;
close(input); close(output);
end.
