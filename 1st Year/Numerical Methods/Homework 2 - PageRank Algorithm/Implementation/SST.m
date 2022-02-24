% Algortimul a fost implementat folosind explicatiile din laboratorul 2
% incarcat pe pagina de curs
function x = SST(A, b)
  
  [n n] = size(A); 
  for i=n : -1 : 1
    s=0;
    for j=(i + 1) : n
      s = s + A(i, j) * x(j);
    endfor
    x(i) = (b(i) - s) / A(i, i);
  endfor
endfunction
