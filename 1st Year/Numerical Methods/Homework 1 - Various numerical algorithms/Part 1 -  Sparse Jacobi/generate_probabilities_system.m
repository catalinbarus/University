function [A, b] = generate_probabilities_system(rows)
  
  s=0;
  for i=1:rows
    s=s+i;
  endfor
  b=zeros(s, 1);
  A=zeros(s, s);
  n=length(b);
  for i=0:rows-1
    b(n-i)=1;
  endfor
  k=s;
  p=rows;
  for i=rows:-1:3
    A(k-i, k-i)=5;
    A(k-i-(p-1)+1, k-i-(p-1)+1)=5;
    k=k-i;
    p=p-1;
  endfor
  A(1, 1)=4;
  A(2, 2)=5;
  A(3, 3)=5;
  A(s, s)=4;
  A(s-rows+1, s-rows+1)=4;
  for i=s-rows+2:s-1
    for j=s-rows+2:s-1
      if(i == j)
        A(i, j)=5;
      endif
    endfor
  endfor
  for i=1:n
    if(A(i, i) == 0)
      A(i, i)=6;
    endif
  endfor
  A(2, 1)=-1;
  A(3, 1)=-1;
  A(s-1, s)=-1
  A(s-rows, s)=-1;
  A(s-rows+2, s-rows+1)=-1;
  A(s-rows+1-(rows-1), s-rows+1)=-1;
  for i=s-rows+2:s-1
    A(i+1, i)=-1;
    A(i-1, i)=-1;
    A(i-rows, i)=-1;
    A(i-(rows-1), i)=-1;
  endfor
  
  right=s;
  left=s-rows+1;
  for i=rows:-1:4
    right=right-i;
    left=left-(i-1);
    A(left+1, left)=-1;
    A(left+(i-1), left)=-1;
    A(left+i, left)=-1;
    A(left-(i-2), left)=-1;
    A(right-1, right)=-1;
    A(right+i, right)=-1;
    A(right+(i-1), right)=-1;
    A(right-(i-1), right)=-1;
    for j=left+1:right-1
      A(j+1, j)=-1;
      A(j-1, j)=-1;
      A(j+i, j)=-1;
      A(j+(i-1), j)=-1;
      A(j-(i-2), j)=-1;
      A(j-(i-1), j)=-1;
    endfor
  endfor
  A(1, 2)=-1;
  A(3, 2)=-1;
  A(4, 2)=-1;
  A(5, 2)=-1;
  A(1, 3)=-1;
  A(2, 3)=-1;
  A(5, 3)=-1;
  A(6, 3)=-1;
endfunction