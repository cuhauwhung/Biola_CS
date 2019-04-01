%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUALITY CONTROL OF LCG
CheckN=100;
Check = LCG(CheckN);
lengthCheck=length(unique(Check));     % Shows that there is no duplicate and all unique 

x2 = 1:2:CheckN; y2 = 2:2:CheckN;
plot(Check(x2),Check(y2),'o')          %Plot points in 2D

x3 = 1:3:CheckN-1; y3 = 2:3:CheckN; z3 = 3:3:CheckN-1;
plot3(Check(x3), Check(y3), Check(z3), 'o'); %Plot points in 3D

%Plot has no linear lines. No pattern - good generator 

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%SCENARIO 1: N LINES, N SERVERS, 
%WITH PRE-DETERMINED NUMBER OF PEOPLE (P) IN EACH LINE

n = 20; %Number of Lines/Servers
p = 40; %Number of People in each line
avg_time = 3; %Average Time per Customer
range = 2; %Room for Error
A = avg_time + (LCG(n*p)-0.5)*range; %Get all random values

%Distribute Random Values to Each Line
T1 = [];
t1 = [];
for i = 1:(n*p);
    t1 = [t1 A(i)];
    if (mod(i, n) == 0)
        T1 = [T1 t1'];
        t1 = [];
    end
end
T1 = T1';

%Find Max Value
s1 = sum(T1);
m1 = max(s1); %TOTAL TIME ELAPSED

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Adding weights to different servers (some servers might be more experienced than others)  
% Weights vary formr 0.5 - 1.5 
for i=1:n
    weight= 0.5+(1)*rand(1,1)
    disp(weight);
    T1(:, i) = T1(:,i)*weight;
end 

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Using central limit theorem to get normal distributed values 
ANorm=[];
for i=1:(n*p)
    Temp=[];
    for j=1:12
    r = randi([1 n*p], 1);
    Temp = [Temp A(r)];
    end 
    ANorm=[ANorm sum(Temp)/12];
end 

hist(ANorm)
A=ANorm;
% Run everything again using this new A
% Can apply to scenario 1 and 2


n = 20; %Number of Lines/Servers
p = 40; %Number of People in each line
avg_time = 3; %Average Time per Customer
range = 2; %Room for Error

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Updating N and seeing how the time decreases with set P (total number of
%customers) 
output=[];
number=[];
% n=number of servers
for n=1:20
    p = 40; %Number of People total
    avg_time = 3; %Average Time per Customer
    range = 2; %Room for Error
    A = avg_time + (LCG(p)-0.5)*range; %Get all random values

    %Distribute Random Values to Each Line
    T1 = [];
    t1 = [];
    for i = 1:(p);
        t1 = [t1 A(i)];
        if (mod(i, n) == 0)
            T1 = [T1 t1'];
            t1 = [];
        end
    end
    T1 = T1';

    %Find Max Value
    s1 = sum(T1);
    m1 = max(s1); %TOTAL TIME ELAPSED
    output=[output m1];
    number=[number n];
end





%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%SCENARIO 2: 1 LINE, N SERVERS, N*P PEOPLE
%FIRST IN, FIRST OUT
    
T2 = zeros(n,1);
%Put first n people to the servers
for i = 1:n
    T2(i) = A(i);
end

%find the minimum time for next server for
%subsequent customers
for i = (n+1):(n*p)
    %find index of minimum time
    [~, min_index] = min(T2);

    %Add next value to the min value (because it finishes first)
    T2(min_index) = T2(min_index) + A(i);
end

m2 = max(T2);



%SCENARIO 3: Same as SCENARIO 2, but CUSTOMERS HAVE DIFFERENT ARRIVAL
%TIMES

%Assume customers come to the servers in the first 15 minutes, but at
%random times.
%At time t, customer will find go to the server with the shortest queue
%Uses Greedy Algorithm -- DOES NOT GIVE OPTIMAL SOLUTION

AT = LCG(n*p*2);
AT = AT((n*p+1):(n*p*2))*15;
AT = sort(AT); %Arrival times for Customers in array A

T3 = zeros(n,1);
%Put first n people to the servers, added with their duration
for i = 1:n
    T3(i) = AT(i)+A(i);
end

for i = (n+1):(n*p)
    %Find a free server (not currently serving a customer)
    foundfreeserver = false;
    for j = 1:n
        if (T3(j) < AT(i)) %if the arrival time is greater than server's finish time
            T3(i) = AT(i) + A(i); %add his arrival time + duration
            foundfreeserver = true;
            break;
        end
    end
    
    %Go to next customer if this customer finds a free server:
    if foundfreeserver == true
        continue
    end
    
    %ALL SERVERS ARE BUSY HANDLING CUSTOMERS:
    %Choose line with earliest finish time
    [~, earliest_index] = min(T3);
    T3(earliest_index) = T3(earliest_index) + A(i);
end

m3 = max(T3);
