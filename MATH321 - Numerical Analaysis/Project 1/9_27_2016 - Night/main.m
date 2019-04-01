format longEngG

% Sparks going up or down
[A1, A2]= FindCrit(x(754), x(1021), x, y, 1);
[C1, C2]= FindCrit(x(1552), x(1752), x, y, 1);
[F1, F2]= FindCrit(x(3500), x(3820), x, y, 1);

% Sparks going down (through eyeballing)
[B1, B2]= FindCrit(x(1250), x(1550), x, y, 0);
[D1, E2]= FindCrit(x(2100), x(2550), x, y, 0);
[D2] = FindLow(x(D1), x(E2), x, y);
 E1=2379; 

% The intervals we should integrate over along with the points 
plot(x, y);
hold on;
scatter(x(A1), y(A1));
scatter(x(A2), y(A2));
scatter(x(C1), y(C1));
scatter(x(C2), y(C2));
scatter(x(F1), y(F1));
scatter(x(F2), y(F2));

scatter(x(B1), y(B1));
scatter(x(B2), y(B2));

scatter(x(D1), y(D1));
scatter(x(D2), y(D2));
scatter(x(E1), y(E1));
scatter(x(E2), y(E2));

% Apply Simpsons over intervals
A_simp=Simpson(x, y, A1, A2);
B_simp=Simpson(x, y, B1, B2);
C_simp=Simpson(x, y, C1, C2);
F_simp=Simpson(x, y, F1, F2);

D_simp=2*Simpson(x, y, D1, D2);
E_simp=2*Simpson(x, y, E1, E2);

% Apply Trapezoid over intervals; we have to double dip one differently
A_T=Trap(x, y, A1, A2);
B_T=Trap(x, y, B1, B2);
C_T=Trap(x, y, C1, C2);
F_T=Trap(x, y, F1, F2)

% We use the point D1 and E2 to find the function of the line that goes
% between these two points, then we just integrate over the line 
f = @(z) ((y(E2)-y(D1))/(x(E2)-x(D1))*(z-x(D1))+y(D1));
D_T= 2*integral(f, x(D1), x(D2));
E_T= 2*integral(f, x(E1), x(E2));

plot(x,y);
hold on;
plot(x, f(x)); 
    
% Get the differene
A_area=abs(A_simp-A_T);
B_area=abs(B_simp-B_T);
C_area=abs(C_simp-C_T);
D_area=abs(D_simp-D_T);
E_area=abs(E_simp-E_T);
F_area=abs(F_simp-F_T);  



