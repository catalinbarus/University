function R = Algebraic(nume, d)
	% Functia care calculeaza vectorul PageRank folosind varianta algebrica de calcul.
	% Intrari: 
	%	-> nume: numele fisierului in care se scrie;
	%	-> d: probabilitatea ca un anumit utilizator sa continue navigarea la o pagina urmatoare.
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
  
  % Determin matricele K si M asa cum este explicat in enuntul temei
  K = zeros(n);
  for i=1:n
    K(i, i) = link(i);
  endfor
  
  % Ma folosesc de algoritmul Gram Schmidt pentru a determina inversele
  % lui M si K
  M = zeros(n);
  M = (GS(K) * A)';
  
  I=eye(n);
  reversi=GS(I - d * M);
  
  % Am folosit formula de la algoritmul Algebraic asa cum a fost
  % descrisa in enuntul temei
  R=reversi*(1 - d )/n*ONE; 
endfunction
  