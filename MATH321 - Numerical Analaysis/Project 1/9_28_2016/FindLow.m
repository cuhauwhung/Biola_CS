function [yIndex] = FindLow (a, b, x, y)

in_a=0; in_b=0;
yIndex=0; yMin=y(1);  


% Index the points 
for i=1:size(x)
    if a==x(i) 
        in_a=i;
    end 

    if b==x(i)
        in_b=i;
    end 
end 

    
        for i=in_a:1:in_b

            if y(i)<yMin 
                yMin=y(i);
                yIndex=i;
            end 
        end
       

end 
 

 
