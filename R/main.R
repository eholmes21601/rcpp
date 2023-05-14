pacman::p_load(tidyverse, Rcpp, RcppArmadillo)
sourceCpp('R//c_code.cpp')

cppFunction(depends = "RcppArmadillo",
            ' 
  arma::vec GLS_cpp( arma::mat X, arma::mat V, arma::vec y ) {
    arma::mat V_inv = inv(V); 
    arma::vec res   = inv(X.t() * V_inv * X) * X.t() * V_inv * y;
    return res;
  }
'
)

data(trees, package="datasets")
fastLm(cbind(1, log(trees$Girth)), log(trees$Volume))

y.pred <- as.vector(lm(log(Volume) ~ log(Girth), data = trees)$fitted.values)
res <- log(trees$Volume) - y.pred
res %*% res
