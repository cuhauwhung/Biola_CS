function [Simpson_output] = Simpson(x, y, a, b)

deltX=((x(b)-x(a))/(b-a));
disp(deltX);

Simpson_output=y(a)+y(b); 
odd=true;

for z=(a+1):1:(b-1) 
    if odd==true; 
        Simpson_output=Simpson_output+(4*y(z)); 
        odd=false;
    else
        Simpson_output=Simpson_output+(2*y(z));
        odd=true;
    end 
    
end 

Simpson_output=(deltX/3)*Simpson_output; 

end
