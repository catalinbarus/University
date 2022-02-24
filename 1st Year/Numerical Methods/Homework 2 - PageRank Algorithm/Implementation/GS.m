% Algortimul Gram schmidt este folosit pentru functia Algebraic
% si l-am implementat folsindu-ma de algoritmul deja existent pe 
% pagina de curs, la care am adu mici modificari
function B = GS(A)
  
  n = size(A); 
  Q = A;
	R = zeros(n);
  
	for k = 1 : n
     R(k, k) = norm(Q(:, k ));
	   Q(:, k ) = Q(:, k) / R(k, k);
	   for j = k + 1 : n
		  R(k, j) = Q(:, k)' * Q(:, j);
		  Q(:, j) = Q(:, j) - Q(:, k) * R(k, j);
	   endfor
	endfor
  
  B = zeros(n);
  I = eye(n);
  
  % Rezolv sistemul descris in enuntul temei "T · x i = e i"
  % folosindu-ma de algortimul SST pentru a determina inversa
  % matricei A
  for i = 1 : n
    x = SST(R, Q' * I(:, i));
    B(:, i) = x;
  endfor
endfunction
