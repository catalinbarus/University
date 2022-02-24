function y = Apartenenta(x, val1, val2)
	% Functia care primeste ca parametrii x, val1, val2 si care calculeaza valoarea functiei membru in punctul x.
	% Stim ca 0 <= x <= 1 
  
  % a si b au fost calculate folosind proprietatea de continuitate a unei
  % functii pe ramuri
  a = 1 / (val2 - val1);
  b = val1/(val1 - val2);
  
  % y-ul se determina in functie de ramura pe care se afla x
  if(x >= 0 && x < val1)
    y = 0;
  endif
  if (x >= val1 && x <= val2)
    y = a*x + b;
	endif
  if (x > val2 && x <= 1)
    y = 1;
  endif
endfunction