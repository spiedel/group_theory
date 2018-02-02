%5 point finite difference method 

N = 8;
M = 10;
A = zeros(N*M);
dx = 0.1;
dy = 0.01;


for i = 1:N*M %initialises matrix diagonal as the middle coefficient
    A(i,i) = -2*(1/dx^2 + 1/dy^2);
end

for i = 1:N-1
    for j = 1:M
           A(i+(j-1)*N, i+(j-1)*N+1) = 1/dx^2;
           A(i+(j-1)*N+1, i+(j-1)*N) = 1/dx^2;
    end
end

for i = 1:N
    for j = 1:M-1
        A(i+(j-1)*N, i+j*N) = 1/dy^2;
        A(i+j*N, i+(j-1)*N) = 1/dy^2;
    end
end

       