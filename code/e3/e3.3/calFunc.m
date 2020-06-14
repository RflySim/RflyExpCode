function Y = calFunc(x, p)
%Function description:
%  magnetometer error model, Y(i) = norm(Km*(x(:,i) - bm))
%Input:
%  x: magnetometer data, dimension 3*m
%  p: model parameter, dimension 6*1
%Output:
%  Y: calibrated magnetometer value.

    kx = p(1);
    ky = p(2);
    kz = p(3);
    bx = p(4);
    by = p(5);
    bz = p(6);

    Km = [kx 0 0;0 ky 0;0 0 kz];
    bm = [bx by bz]';
    m = length(x);
    Y = zeros(1, m);
    for i = 1 : m  
        Y(i) = norm(Km*(x(1:3, i) + bm));
    end
end