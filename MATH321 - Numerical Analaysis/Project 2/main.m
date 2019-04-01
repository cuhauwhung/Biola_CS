%Constants
Cd = 0.3926485; CL = 0.255819;
phi_s = 236.0038*pi/180; phi_m = 146;
theta = 3.9; spin = 2388;
g = 32.2; K = 0.005152949;
X0=-2.43;Y0=50; Z0=6.46; Vx=9.46; Vy=-143.17; Vz=-9.15; Ax = -23.08; 
Ay = 34.2; Az = -26.09;

%PART ONE 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
syms t

Xx = @(t) x0 + t*Vx0 + 0.5*Ax*t.^2;
Xy = @(t) y0 + t*Vy0 + 0.5*Ay*t.^2;
Xz = @(t) z0 + t*Vz0 + 0.5*Az*t.^2;

% To find the tmax for part 1 
eqn = Xy(t) == 1.417;
tmax = solve(eqn, t);
tmax = tmax(2);

time = 0:1/10000:tmax;
  
Table = double([time.' Xx(time).' Xy(time).' Xz(time).']);

%PART TWO 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Declarations
V = @(x, y, z) sqrt(x.^2 + y.^2 + z.^2);
f = @(t, x)[x(4);  x(5);  x(6);
    -K*Cd*V(x(4), x(5), x(6))*x(4) - K*CL*V(x(4), x(5), x(6))*x(5)*sin(phi_s); 
    -K*Cd*V(x(4), x(5), x(6))*x(5) - K*CL*V(x(4), x(5), x(6))*(x(4)*sin(phi_s - x(6)*cos(phi_s))); 
    -K*Cd*V(x(4), x(5), x(6))*x(6) + K*CL*V(x(4), x(5), x(6))*x(5)*cos(phi_s) - g];
alpha = [x0; y0; z0; Vx0; Vy0; Vz0];
beta = [-2.43; 50; 6.46; 9.46; -143.17; -9.15]; 

% Run the RK and the RK Output 
[RK_Output, RK_tmax]=RK4(f, 0, 1/10000, beta);
disp(RK_tmax); 

% Run the ODE45 and the Output
[t, ODE45_Output] = ode45(f, [0 RK_tmax], beta);

% OUTPUT FROM ABOVE ARE IDENTICAL
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


% PLOT BOTH IN SAME GRAPH
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
PT1 = plot3(Xx(time), Xy(time), Xz(time));
hold on
grid on
RKX = RK_Output(:, 2);
RKY = RK_Output(:, 3);
RKZ = RK_Output(:, 4);
PT2 = plot3(RKX, RKY, RKZ);
set(PT1, 'LineWidth', 1);
set(PT2, 'LineWidth', 1);
hold off
legend('Part 1', 'Part 2')

% MAX VELOCITY
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

H =1/10000;
VF_PT2 = vpa(V(RK_Output(3850, 5), RK_Output(3850, 6), RK_Output(3850, 7)));
Vfx = (Table(3829, 2) - Table(3828, 2))/H;
Vfy = (Table(3829, 3) - Table(3828, 3))/H;
Vfz = (Table(3829, 4) - Table(3828, 4))/H;
VF_PT1 = vpa(V(Vfx, Vfy, Vfz));
    

% MAX TIME
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

TM_PT1 = vpa(tmax);
TM_PT2 = RK_tmax;
