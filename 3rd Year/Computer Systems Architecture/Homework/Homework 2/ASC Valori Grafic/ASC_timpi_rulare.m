
x_neopt = [400, 500, 600, 700, 800, 900, 1000, 1100, 1200];
y_neopt = [1.160794, 2.280208, 4.201136, 6.250985, 10.290288, 13.154470, 17.736488, 23.799044, 32.714115];

x_blas = [400, 500, 600, 700, 800, 900, 1000, 1100, 1200];
y_blas = [0.095167, 0.076895, 0.126840, 0.193361, 0.279967, 0.390163, 0.546965, 0.717561, 0.916927];

x_opt_m = [400, 500, 600, 700, 800, 900, 1000, 1100, 1200];
y_opt_m = [0.359455, 0.712957, 1.212313, 1.870186, 4.503133, 4.332955, 5.191469, 9.755822, 12.072292];

figure
plot(x_neopt, y_neopt)
hold on 
plot(x_blas, y_blas)
hold on
plot(x_opt_m, y_opt_m)
hold off
title('Diferentele de timp intre cele 3 implementari')
xlabel('Matrix size (N)')
ylabel('Time (s)')
legend('Neopt', 'Blas', 'Opt M')