function [Output] = FindInflex (a, b, xVals, yVals)

in_a=0;
in_b=0;
Output=0;
maxDistance=10;

% Index the points 
for i=1:size(xVals)
  
    if a==xVals(i)
        in_a=i;
    end  
     
    if b==xVals(i)
        in_b=i;
    end 
    
end 

for i=in_a:1:in_b
    
    if i<in_b
        distance=abs(yVals(i+1)-yVals(i));
    end     
    
    if distance<maxDistance
        maxDistance=distance; 
        Output=i;
    end 
    
end 
 
end 

