pacman::p_load(tidyverse, Rcpp, RcppArmadillo, BH)
sourceCpp('R//c_code.cpp')

#in Rcpp
data(trees, package="datasets")
out <- lm_cpp(cbind(1, log(trees$Girth)), log(trees$Volume))
2 * pt(abs(out$t.value), out$df.residual, lower.tail = FALSE)
## in R
fit1 <- summary(lm(log(Volume) ~ log(Girth), data = trees));fit1


y.pred <- as.vector(lm(log(Volume) ~ log(Girth), data = trees)$fitted.values)
res <- log(trees$Volume) - y.pred
res %*% res
