function [point1, point2] = FindCrit (a, b, x, y, up)

in_a=0; in_b=0;
yIndex=0;yMax=0; yMin=y(1);  
minDiff=1; 

% Index the points 
for i=1:size(x)
    if a==x(i) 
        in_a=i;
    end 
    
    if b==x(i)
        in_b=i;
    end 
end 

% for the sparks going up
if (up==1)
    for i=in_a:1:in_b
        if i<in_b
            diff=abs(y(i+1)-y(i));
        end     

        if diff<minDiff;
            minDiff=diff; 
            point1=i;
        end 

        if y(i)>yMax 
            yMax=y(i);
            yIndex=i;
        end 
    end 
    
point2=((yIndex-point1)+yIndex);

else 
    for i=in_b:-1:in_a
        
        if i>in_a
            diff=abs(y(i+1)-y(i));
        end     

        if diff<minDiff;
            minDiff=diff; 
            point2=i;
        end 

        if y(i)<yMin 
            yMin=y(i);
            yIndex=i;
        end 
    end 
    
point1=yIndex-(point2-yIndex);

end

end 
 

 
