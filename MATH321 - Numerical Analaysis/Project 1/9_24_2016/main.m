format longEngG

% First spark
A_left = FindInflex(3.660999900000000e+14, 3.6670001e+14, x, y);
A_right= FindInflex(3.675000200000000e+14, 3.681200000000000e+14, x, y);

B_left = FindInflex(3.755200000000000e+14,3.764599900000000e+14, x, y);
B_right= FindInflex(3.780000000000000e+14, 3.792200100000000e+14, x, y);

C_left = FindInflex(3.813000200000000e+14, 3.815999900000000e+14, x, y);
C_right= FindInflex(3.828000000000000e+14, 3.833599900000000e+14, x, y);

F_left = FindInflex(4.210000100000000e+14, 4.221400200000000e+14, x, y);
F_right= FindInflex(4.235000200000000e+14,4.245000000000000e+14, x, y);


% The intervals we should integrate over along with the points 
plot(x,y);
hold on; 
scatter(x(A_left), y(A_left), 'k');
scatter(x(A_right), y(A_right), 'k');

scatter(x(B_left), y(B_left), 'k');
scatter(x(B_right), y(B_right), 'k');

scatter(x(C_left), y(C_left), 'k');
scatter(x(C_right), y(C_right), 'k');

scatter(x(F_left), y(F_left), 'k');
scatter(x(F_right), y(F_right), 'k');
