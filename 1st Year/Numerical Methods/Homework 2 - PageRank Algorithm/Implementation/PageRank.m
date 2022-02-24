function [R1 R2] = PageRank(nume, d, eps)
	% Calculeaza indicii PageRank pentru cele 3 cerinte
	% Scrie fisierul de iesire nume.out 
  
  % Deschid fisierul pentru a citi graful
  FILE = fopen(nume, 'r');
  
  % Citesc pe rand cate un element din fisierul deschis
  
  n=fscanf(FILE, '%f', 1);

  for i=1:n
    l = fscanf(FILE, '%f', 1);
    size = fscanf(FILE, '%f', 1);
    for j = 1:size
      c = fscanf(FILE, '%f', 1);
    endfor
  endfor
  
  val1 = fscanf(FILE, '%f', 1);
  val2 = fscanf(FILE, '%f', 1);
  
  fclose(FILE);
  
  nume_o = strcat(nume, '.out');
  FILE_O = fopen(nume_o, 'w');
  fprintf(FILE_O, '%i \n', n);
  
  R1 = Iterative(nume, d, eps);
  fprintf(FILE_O, '%.6f \n', R1);
  fprintf(FILE_O, '\n');
  
  R2 = Algebraic(nume, d);
  fprintf(FILE_O, '%.6f \n', R2);
  fprintf(FILE_O, '\n');
  
  [PR1, idx] = sort(R2, 'descend');
  
  rank=1;
  while(rank <= n)
    y = Apartenenta(PR1(rank), val1, val2);
    fprintf(FILE_O, '%i %i %.6f\n', rank, idx(rank), y);
    rank=rank+1;
  endwhile
  
  fclose(FILE_O);
  
endfunction 