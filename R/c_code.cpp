#include <RcppArmadillo.h>
#include <boost/integer/common_factor.hpp> 
#include <boost/math/distributions/students_t.hpp>
#include <boost/math/distributions.hpp>
using namespace Rcpp;

// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::depends(BH)]]
// [[Rcpp::export]]  
Rcpp::List lm_cpp(const arma::mat& X, const arma::colvec& y) {
  int n = X.n_rows, k = X.n_cols;
  Function pt_R("pt");
  arma::colvec coef = arma::solve(X, y);     // fit model y ~ X
  arma::colvec res  = y - X*coef;            // residual error
  int df = n - k;                            // residual degrees of freedom
  double s2 = arma::dot(res, res) / df; // std.errors of coefficients
  arma::colvec std_err = arma::sqrt(s2 * arma::diagvec(arma::pinv(arma::trans(X)*X)));
  arma::colvec t_value = coef/std_err;
  std::student_t_distribution<double> dist(df);
  NumericVector p_values = pt_R(abs(t_value), df, _["lower.tail"] = 0);

  return Rcpp::List::create(Rcpp::Named("coefficients") = coef,
                            Rcpp::Named("stderr")       = std_err,
                            Rcpp::Named("t.value")       = t_value,
                            Rcpp::Named("df.residual")  = df,
                            Rcpp::Named("p.values")  = 2 * p_values);
}

// [[Rcpp::depends(BH)]]
// [[Rcpp::export]] 
 int computeGCD(int a, int b) {
  return boost::integer::gcd(a, b);
}

 