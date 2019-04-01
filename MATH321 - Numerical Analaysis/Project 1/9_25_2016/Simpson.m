function [Simpson_output] = Simpson(y, a, b)

h=2*10^10;
Simpson_output=y(a)+y(b); 

even=false;

for z=(a+1):1:(b-1) 
    if even==false; 
        Simpson_output=Simpson_output+4*y(z); 
        even=true;
    else
        Simpson_output=Simpson_output+2*y(z);
    end 
    
end 

Simpson_output=(h/3)*Simpson_output; 

end

