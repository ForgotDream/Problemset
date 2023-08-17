const
z=0.0000001;

var
a,b,x,y:array[0..1000]of longint;
      t:array[0..1000]of real;
i,j,n,m:longint;
    max:real;

procedure init;
        begin
        readln(a[0],b[0],n,m);
        for i:=1 to n do readln(a[i],b[i]);
        for i:=1 to m do readln(x[i],y[i]);
        for i:=1 to n do t[i]:=99999999;
        max:=99999999;
        end;

function mi(x,y:longint):longint;
        begin
        if x<y then mi:=x else mi:=y;
        end;

function ma(x,y:longint):longint;
        begin
        if x>y then ma:=x else ma:=y;
        end;

function can(s,t:longint):boolean;
 var   i:longint;
     p,c:real;
        begin
        can:=true;
        for i:=1 to m do
             if a[s]=a[t] then begin
                               if (y[i]>mi(b[s],b[t]))and
                                  (y[i]<ma(b[s],b[t]))and
                                  (x[i]=a[s]) then exit(false);
                               end
        else if b[s]=b[t] then begin
                               if (x[i]>mi(a[s],a[t]))and
                                  (x[i]<ma(a[s],a[t]))and
                                  (y[i]=b[s]) then exit(false);
                               end
        else begin
             p:=(b[t]-b[s])/(a[t]-a[s]);
             c:=b[s]-p*a[s];
             if (x[i]>mi(a[s],a[t]))and(x[i]<ma(a[s],a[t]))and
                (y[i]>mi(b[s],b[t]))and(y[i]<ma(b[s],b[t]))and
                (abs(p*x[i]+c-y[i])<z) then exit(false);
             end;
        end;

function dist(s,t:longint):real;
        begin
        dist:=sqrt(sqr(a[s]-a[t])+sqr(b[s]-b[t]));
        end;

procedure dfs(i:longint; min:real);
 var j:longint;
        begin
        if min>t[i] then exit
                    else t[i]:=min;

        if min+dist(0,i)*2<max then max:=min+dist(0,i)*2;
        for j:=1 to n do
        if can(i,j) then
        if min+dist(0,i)*2>min+dist(i,j)+dist(0,j)*2 then
        dfs(j,min+dist(i,j));
        end;

procedure print;
        begin
        writeln(max:0:0);
        end;

begin
assign(input,'brazil.in'); reset(input);
assign(output,'brazil.out'); rewrite(output);
init;
dfs(1,0);
print;
close(input); close(output);
end.
