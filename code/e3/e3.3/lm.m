function p = lm(func, p, x, y_dat, dp, p_min, p_max)
%Function description:
%Refer to: Methods for Non-Linear Least Squares Problems. lecture note. pp. 24-30.
%Input:
%  func: functfion name y_hat = func(x, p)
%  p: initial value of the parameter to be estimated
%  x: original value
%  y_dat: func(x, p)'s expected value, m-dimensional vector
%  dp: related to the Jocobian matrix. 
%  p_min: the minimum value of the parameter to be estimated, default is -10*abs(p)
%  p_max: the maximum value of the parameter to be estimated, default is 10*abs(p)
%Output:
%  p: estimated parameter

   p = p(:); y_dat = y_dat(:);  % convert to column vector
   Npar = length(p); 			% number of parameters to be estimated

   if length(x) ~= length(y_dat)
       disp('lm.m err: The length of x must be equal to the length of y_dat!');
   end

    %parameter
    MaxIter = 200000*Npar;	% the maximum number of iterations
	epsilon_1     = 1e-6;	% gradient convergence tolerance of cost function
	epsilon_2     = 1e-6;	% convergence tolerance of the parameters to be fitted
	epsilon_4     = 1e-6;	% parameters in the LM algorithm, determining the transformation step size of the parameters
	lambda_0      = 1e-5;	% lambda initial parameter

	Fx_hst = [];
    %If no parameters are specified, then the default parameters are used.
	if nargin < 5, dp = 0.001; end
	if nargin < 6, p_min   = -100*abs(p); end
	if nargin < 7, p_max   =  100*abs(p); end

     p_min=p_min(:); p_max=p_max(:);

	if length(dp) == 1
        dp = dp*ones(Npar,1);
    end
 
	stop = 0;       

	[alpha, beta, delta_y] = lm_matx(func, x, p, y_dat, dp);
    Fx_old = delta_y' * delta_y;
    Fx_hst(1) =  Fx_old;
    if ( max(abs(beta)) < epsilon_1 )
        fprintf(' *** The initial estimated parameters is close to optimal and the Fx derivative tends to zero. ***\n')
        fprintf(' *** epsilon_1 = %e\n', epsilon_1);
        fprintf('***Fx = %e\n', Fx_old);
        stop = 1;
    end
 
    % lambda initial value
	lambda  = lambda_0 * max(diag(alpha));	% Nielsen method
	nu = 2;
    
    iteration = 0;
    while ( ~stop && iteration <= MaxIter )	

        iteration = iteration + 1;
        % update mode of the parameter change step size
        delta_p = ( alpha + lambda*diag(diag(alpha)) ) \ beta;	

        p_try = p + delta_p;  % update parameter
        p_try = min(max(p_min,p_try), p_max);  % parameter clipping

        delta_y = y_dat - (feval(func, x, p_try))';  % residual
        Fx = delta_y' * delta_y;
        Fx_hst(iteration+1) = Fx;
        rho = (Fx_old - Fx) / ( delta_p' * (lambda * delta_p + beta) ); % Nielsen

        if ( rho > epsilon_4 )
            % The approximation is good, the lamda is reduced, and the step
            % size is close to the step size of the Gauss-Newton method.
            p = p_try(:);
    
            [alpha, beta, delta_y] = lm_matx(func, x, p, y_dat, dp);
            Fx = delta_y' * delta_y;
            Fx_old = Fx;
    
            lambda = lambda*max( 1/3, 1-(2*rho-1)^3 ); nu = 2;
        else
            % poor approximation, using small steps
            lambda = lambda * nu;   nu = 2*nu;  % Nielsen
        end
        % determine if iteration can be ended
        if ( max(abs(delta_p./p)) < epsilon_2  &&  iteration > 2 ) 
            fprintf(' **** The parameters to be estimated tend to be stable during the iteration **** \n')
            fprintf(' **** epsilon_2 = %e\n', epsilon_2);
            fprintf('***The number of iterations is %e\n', iteration);
            figure
            plot(1:iteration+1, Fx_hst(1:iteration+1))
            title('Fx changes with the number of iterations')
            xlabel('Number of iterations')
            ylabel('Fx')
            stop = 1;
        end
        if ( max(abs(beta)) < epsilon_1  &&  iteration > 2 ) 
            fprintf(' **** The first derivative of Fx tends to zero  **** \n')
            fprintf(' **** epsilon_1 = %e\n', epsilon_1);
            fprintf('***Number of iterations£º%e\n',iteration);
            figure
            plot(1:iteration+1,Fx_hst(1:iteration+1))
            title('Fx changes with the number of iterations')
            xlabel('Number of iterations')
            ylabel('Fx')
            stop = 1;
        end
        if ( iteration == MaxIter )
            disp(' !! Reach the maximum number of iterations %e£¬not yet fitted successfully !!',MaxIter)
            stop = 1;
        end
    end
        
function dydp = lm_dydp(func, x ,p, y, dp)
%Function description:
%  calculate the first derivative of func to p, the Jocobian matrix
%Input:
%  func : y_hat = func(x,p)
%  x: m-dimensional vector
%  p: n-dimensional vector
%  y = func(t,p),m-dimensional vector
%  dp: The magnitude of the disturbance when deriving the number. Derivation method:
%      dp(j)>0 f'(x)=(f(x,p+dp*p)-f(x,p-dp*p))/(2*dp*p)
%      dp(j)<0 f'(x)=(f(x,p+dp*p)-f(x,p))/(dp*p)
%      default: 0.001;
%Output:
%  dydp = Jacobian Matrix dydp(i,j)=dy(i)/dp(j)	i=1:m; j=1:n 

	m=length(y);
	n=length(p);

	if nargin < 5
        dp = 0.001*ones(1, n);
	end

	ps = p; dydp = zeros(m, n); del = zeros(n, 1);

	for j = 1:n
        del(j) = dp(j) * p(j);
        p(j) = ps(j) + del(j);

        if del(j) ~= 0
            y1 = feval(func, x, p);
            if (dp(j) < 0)
                dydp(:, j) = (y1 - y)./del(j);
            else
                p(j) = ps(j) - del(j);
                dydp(:, j) = (y1 - feval(func, x, p)) ./ (2 .* del(j));
            end
        end
        p(j) = ps(j);
	end

function [alpha, beta, delta_y] = lm_matx(func, x, p, y_dat, dp)
%Function description:
%  Calculate key data in the lm algorithm: alpha, beta.
%Input:
%  func: y_hat = func(x,p)
%  x: m-dimensional vector
%  p: n-dimensional vector
%  y_dat£ºfunc(x,p)'s desired value,m-dimensional vector
%  dp: The magnitude of the disturbance when deriving the number. Derivation method:
%      dp(j)>0 f'(x)=(f(x,p+dp*p)-f(x,p-dp*p))/(2*dp*p)
%      dp(j)<0 f'(x)=(f(x,p+dp*p)-f(x,p))/(dp*p)
%      default:0.001;
%Output:
%  alpha: J'J
%  beta: J'delta_y
%  delta_y: residual.

	Npar = length(p);
	if nargin < 5
        dp = 0.001;
    end
 
	alpha = zeros(Npar);
	beta  = zeros(Npar,1);
  
	y_hat = feval(func,x,p);
	delta_y = y_dat - y_hat';

    dydp = lm_dydp(func, x, p, y_hat, dp);
	alpha = dydp'*  dydp;  % J'J  
	beta  = dydp'* delta_y;  % J'delta_y

