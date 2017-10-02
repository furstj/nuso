// g++ cblas1.cpp -lcblas -lblas

#include <iostream>
#include <cblas.h>

using namespace std;

class Matrix {
public:

  Matrix(size_t rows, size_t cols):
    rows_(rows),
    cols_(cols)
  { data_ = new double[rows*cols]; }

  ~Matrix() { delete[] data_; }

  size_t rows() const { return rows_; }
  size_t cols() const { return cols_; }
  size_t lda() const { return cols_; }
  double* data() { return data_; }

  double* operator[](int row) { return data_ + row*cols_; }

private:
  size_t rows_;
  size_t cols_;
  double* data_;
};

int main() {
  int n = 10;

  double* x = new double[n];
  double* y = new double[n];
  double alpha = 1.0;
  double beta = 1.0;

  Matrix A(n, n);
  
  for (size_t i=0; i<n; i++) {
    for (size_t j=0; j<n; j++) 
      A[i][j] = 1.0;
    A[i][i] = n+0.5;
    x[i] = 2.0;
    y[i] = 3.0;
  }
    
  // y = alpha * A * x + beta * y
  cblas_dgemv(CblasRowMajor, CblasNoTrans, 
	      A.rows(), A.cols(), alpha, A.data(), A.lda(),
	      x, 1, 
	      beta, y, 1);

  for (size_t i=0; i<A.rows(); i++) 
    cout << "y[i] = " << y[i] << endl;
 
  delete[] y;
  delete[] x;

  return 0;
}
