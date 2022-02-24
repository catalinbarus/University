function R = Iterative(nume, d, eps)
	% Functia care calculeaza matricea R folosind algoritmul iterativ.
	% Intrari:
	%	-> nume: numele fisierului din care se citeste;
	%	-> d: coeficentul d, adica probabilitatea ca un anumit navigator sa continue navigarea (0.85 in cele mai multe cazuri)
	%	-> eps: eruarea care apare in algoritm.
	% Iesiri:
	%	-> R: vectorul de PageRank-uri acordat pentru fiecare pagina. 
  
  % Deschid fisierul pentru a citi graful
  FILE = fopen(nume, 'r');
  
  % Citesc pe rand cate un element din fisierul deschis
  
  n=fscanf(FILE, '%f', 1);
  % Matricea de adicenta
  A=zeros(n); 
  ONE=ones(n, 1);
  
  % Citesc sirul de vecini pentru fiecare nod (link-urile la care pot sa
  % ajung de pe site-ul i) si verific simultan sa nu iau in considerare 
  % link-urile care ma redirecteaza la aceeasi pagina facand diagonala
  % principala a matricei de adiacenta 0.
  for i=1:n
    l = fscanf(FILE, '%f', 1);
    size = fscanf(FILE, '%f', 1);
    for j = 1:size
      c = fscanf(FILE, '%f', 1);
      A(l, c) = 1;
      if(l == c)
        A(l, c) = 0;
      endif
    endfor
  endfor
  
  fclose(FILE);
   
  % Determin exact cate link-uri detine un site i
  link = zeros(1, n);
  for i=1:n
    for j=1:n
      link(i)=link(i) + A(i, j);
    endfor
  endfor
  
  
  K = zeros(n);
  for i=1:n
    K(i, i) = link(i);
  endfor
  
  M = zeros(n);
  M = (inv(K) * A)';
  
  R_0 = zeros(n, 1);
  for i=1:n
    R_0(i, 1) = 1/n;
  endfor
  
  % Am aflat prima iteratie in afara buclei de while ca sa pot folosi 
  % norm in conditia lui while
  R = d*M*R_0+((1-d)/n)*ONE;
  while (norm(R - R_0) >= eps)
    R_0 = R;
    R = d*M*R_0 + ((1-d )/n)*ONE;
  endwhile
  
  R = R_0; 
endfunction