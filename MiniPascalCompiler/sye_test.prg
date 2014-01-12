PROGRAM SYNTAX ;
 VAR I,J : INTEGER ;
     A : ARRAY [1..10] OF CHAR;
 PROCEDURE P ;
  VAR J : INTEGER ;
    BEGIN
      READ(J);
      I := I * I-I * I DIV I ;
      IF((J=I) OR NOT (J<>I)) THEN A[I]:=' ' ELSE A[ ]:='''' ;
      IF ((J=I) OR NOT (J<>I))THEN A[I]:=' ' ELSE A[ ]:='''' ;
      WRITE(A[I]) ;
      I := I + 1
    END
 BEGIN
    I:= 1 ; J := 10000 ; A := (A+B)*(C+D);
    WHILE (I>0) AND (I<11) OR (I>=1) AND (I<=10) DO I := I+1;
    WRITE (J)
 END.
