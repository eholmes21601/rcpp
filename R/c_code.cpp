#include <RcppArmadillo.h>
using namespace Rcpp;


//

// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::export]]
arma::mat M1 (NumericMatrix x,NumericVector y) {
  arma::mat x_ = as<arma::mat>(x);
  arma::vec y_ = as<arma::vec>(y);
  arma::mat z = inv(x_) + y_*y_.t();
  return(arma::diagvec(z)) ;
}


// You can include R code blocks in C++ files processed with sourceCpp
// (useful for testing and development). The R code will be automatically 
// run after the compilation.
//

/*** R
M1(matrix(c(1,3,2,4),2,2), c(2,3))
*/
