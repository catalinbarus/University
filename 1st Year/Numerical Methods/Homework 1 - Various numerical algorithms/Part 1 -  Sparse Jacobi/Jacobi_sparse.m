function [x] = Jacobi_sparse(G_values, G_colind, G_rowptr, c, tol)
  
x0=zeros(length(c), 1);
x=csr_multiplication(G_values, G_colind, G_rowptr, x0)+c;
  while(norm(x - x0) > tol)
        x0=x;
        x=csr_multiplication(G_values, G_colind, G_rowptr, x0)+c;
  endwhile
endfunction