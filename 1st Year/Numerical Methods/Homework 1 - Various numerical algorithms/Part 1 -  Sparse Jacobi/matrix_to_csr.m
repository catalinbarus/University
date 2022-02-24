function [values, colind, rowptr] = matrix_to_csr(A)
  
  n=length(A);
  m=length(A);
  c=1;
  ok=0;
  k=1;
  for i=1:n
    for j=1:m
      if(A(i, j) != 0)
       values(c)=A(i, j);
       colind(c)=j;
       c=c+1;
       if(ok == 0)
        aux=c-1;
        ok=1;
       endif
      endif
    endfor
    if(ok == 1)
    rowptr(k)=aux;
    k=k+1;
    ok=0;
    endif 
  endfor
  c=length(rowptr);
  rowptr(c+1)=length(values)+1;
endfunction