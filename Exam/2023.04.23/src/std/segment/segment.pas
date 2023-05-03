program segment ;
 type 
  point = record x , y : longint ; end ;
 function dist ( a , b : point ) : real ;
  begin
   exit ( sqrt ( sqr ( a.x - b.x ) + sqr ( a.y - b.y ) ) ) ;
  end ;
 function ip ( o , a , b : point ) : longint ; {µã»ý}  
  begin
   exit ( ( a.x - o.x ) * ( b.x - o.x ) + ( a.y - o.y  ) * ( b.y - o.y  ) ) ;
  end ;
 function op ( o , a , b : point ) : longint ; {²æ»ý} 
  begin
   exit ( ( a.x - o.x ) * ( b.y - o.y ) - ( b.x - o.x  ) * ( a.y - o.y  ) ) ;  
  end ;
 var
  a , b , c , d : point ;
  x ,  answer   : real ;
 procedure update ( x : real ) ;
  begin
   if x < answer then
    answer := x ;
  end ;
 begin
  assign(input,'segment.in');
  reset(input);
  assign(output,'segment.out');
  rewrite(output);
  readln ( a.x , a.y ) ;
  readln ( b.x , b.y ) ;
  readln ( c.x , c.y ) ;
  readln ( d.x , d.y ) ;
  if ( op ( a , b , c ) * op ( a , b , d ) < 0 ) and ( op ( c , d , a ) * op ( c , d , b ) < 0 ) then
   writeln ( 0.000 : 0 : 4 ) 
   else
    begin
     answer := 999999999 ;
     x := dist ( a , c ) ;
     update ( x ) ;
     x := dist ( a , d ) ;
     update ( x ) ;
     x := dist ( b , c ) ;
     update ( x ) ;
     x := dist ( b , d ) ;
     update ( x ) ;
     if ( ip ( c , d , a ) >= 0 ) and ( ip ( d , c , a ) >= 0 ) then
      begin
       x := abs ( op ( c , d , a ) / dist ( c , d ) ) ;
       update ( x ) ;
      end ;
     if ( ip ( c , d , b ) >= 0 ) and ( ip ( d , c , b ) >= 0 ) then
      begin
       x := abs ( op ( c , d , b ) / dist ( c , d ) ) ;
       update ( x ) ;
      end ;
     if ( ip ( a , b , c ) >= 0 ) and ( ip ( b , a , c ) >= 0 ) then
      begin
       x := abs ( op ( a , b , c ) / dist ( a , b ) ) ;
       update ( x ) ;
      end ;
     if ( ip ( a , b , d ) >= 0 ) and ( ip ( b , a , d ) >= 0 ) then
      begin
       x := abs ( op ( a , b , d ) / dist ( a , b ) ) ;
       update ( x ) ;
      end ;
     writeln ( answer : 0 : 4 ) ;
    end ;
  Close(input);
  Close(output);
 end . 