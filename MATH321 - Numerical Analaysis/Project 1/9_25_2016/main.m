format longEngG

% Sparks going up. My function only worked for the sparks going up
[A1, A2]= FindCrit(x(754), x(1021), x, y);
[C1, C2]= FindCrit(x(1552), x(1752), x, y);
[F1, F2]= FindCrit(x(3500), x(3820), x, y);

% Sparks going down (through eyeballing)
B1=1276; 
B2=1526;
D1=2153;
D2=2341;
E1=2379;
E2=2546;

% The intervals we should integrate over along with the points 
plot(x, y);
hold on;
scatter(x(A1), y(A1));
scatter(x(968), y(968));

scatter(x(B1), y(B1));
scatter(x(B2), y(B2));
scatter(x(C1), y(C1));
scatter(x(C2), y(C2));
scatter(x(D1), y(D1));
scatter(x(D2), y(D2));
scatter(x(E1), y(E1));
scatter(x(E2), y(E2));
scatter(x(F1), y(F1));
scatter(x(F2), y(F2));

A_simp=Simpson(y, A1, A2);
B_simp=Simpson(y, B1, B2);
C_simp=Simpson(y, C1, C2);
D_simp=Simpson(y, D1, D2);
E_simp=Simpson(y, E1, E2);
F_simp=Simpson(y, F1, F2);