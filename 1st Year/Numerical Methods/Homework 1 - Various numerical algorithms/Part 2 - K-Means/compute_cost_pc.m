function [cost] = compute_cost_pc(points, centroids)
  
  [N, D]=size(points);
  [R, C]=size(centroids);
  
  mindist=90000;
  dist=0;
  sum=0;
  
  for i=1:N
      for j=1:R
        for k=1:C
          dist=dist+(centroids(j, k)-points(i, k))^2;
        endfor
        dist=sqrt(dist);
        if(dist < mindist)
          mindist=dist;
        endif
        dist=0;
      endfor
      sum=sum+mindist;
      mindist=90000;
  endfor
  cost=sum;
endfunction

