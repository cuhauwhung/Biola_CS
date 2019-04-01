function [Output, RK_tmax] = RK4(f, a, h, alpha)

%Constants
Cd = 0.3926485; CL = 0.255819;
phi_s = 236.0038*pi/180; phi_m = 146;
theta = 3.9; spin = 2388;
g = 32.2; K = 0.005152949;
X0=-2.43;Y0=50; Z0=6.46; Vx=9.46; Vy=-143.17; Vz=-9.15; Ax = -23.08; 
Ay = 34.2; Az = -26.09;

% Conditions/Variables 
V = @(x, y, z) sqrt(x.^2 + y.^2 + z.^2);
f = @(t, x)[x(4);  x(5);  x(6);
    -K*Cd*V(x(4), x(5), x(6))*x(4) - K*CL*V(x(4), x(5), x(6))*x(5)*sin(phi_s); 
    -K*Cd*V(x(4), x(5), x(6))*x(5) - K*CL*V(x(4), x(5), x(6))*(x(4)*sin(phi_s - x(6)*cos(phi_s))); 
    -K*Cd*V(x(4), x(5), x(6))*x(6) + K*CL*V(x(4), x(5), x(6))*x(5)*cos(phi_s) - g];

m = size(alpha,1);
if m == 1
   alpha = alpha';
end

%h = (b-a)/N;        %the step size
t(1) = a;
w(:,1) = alpha;     %initial conditions

for i = 1:300000
   k1 = h*f(t(i), w(:,i));
   k2 = h*f(t(i)+h/2, w(:,i)+0.5*k1);
   k3 = h*f(t(i)+h/2, w(:,i)+0.5*k2); 
   k4 = h*f(t(i)+h, w(:,i)+k3);
   w(:,i+1) = w(:,i) + (k1 + 2*k2 + 2*k3 + k4)/6;
   t(i+1) = a + i*h;
    
   if (w(2,i)<1.417)
       RK_tmax=t(i);
       break;
   end
   
end


Output = [t' w'];
