function [centroids] = clustering_pc(points, NC)
  
  [N, D]=size(points);
  
  c=1;
  add=NC;
  for i=1:NC
    for j=1:N
      if(i == NC && add<=j)
        cluster(c)=add;
        c=c+1;
        add=add+NC;
      else
      if(mod(j, NC) == i)
        cluster(c)=j;
        c=c+1;
      endif 
     endif
    endfor
    sum=0;
    for l=1:D
      for k=1:length(cluster)
        sum=sum+points(cluster(k), l);
      endfor
      centroids_init(i, l)=sum/length(cluster);
      sum=0;
    endfor
    c=1;
  endfor
  
  centroids_new=zeros(length(centroids_init), D);
  mindist=90000;
  dist=0;
  [R, C]=size(centroids_init);
  A=zeros(R, R*C);
  left=1;
  right=C;
  
  while(1)
  for i=1:N
    for j=1:R
      for k=1:C
        dist=dist+(centroids_init(j, k)-points(i, k))^2;
      endfor
      dist=sqrt(dist);
      if(dist < mindist)
        mindist=dist;
        idx=j;
      endif
      dist=0;
    endfor
    mindist=90000;
    for l=1:C
      A(i, l+(idx-1)*C)=points(i, l);
    endfor
  endfor
  
  sum=0;
  zerocount=0;
  [rowA, colA]=size(A);
  for x=1:NC
    w=1;
    for y=left+(x-1)*C:right+(x-1)*C
      for z=1:rowA
        sum=sum+A(z, y);
        if(A(z, y) == 0)
          zerocount=zerocount+1;
        endif
      endfor
      if(sum != 0)
      centroids_new(x, w)=sum/(rowA-zerocount);
      endif
      w=w+1;
      sum=0;
      zerocount=0;
    endfor
  endfor
  A=zeros(R, R*C);
  if(isequal(centroids_init, centroids_new) == 1)
    break;
  else
  centroids_init=centroids_new;
  endif
endwhile
centroids=centroids_new;
endfunction
