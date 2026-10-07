#include <iostream>
#include <stdexcept>

#ifndef MATRIX_H
#define MATRIX_H

class MatrixOutOfRange : public std::out_of_range {
 public:
  MatrixOutOfRange() : std::out_of_range("MatrixOutOfRange") {
  }
};

template <class T, size_t N, size_t M>
class Matrix {
 public:
  T matrix[N][M];
  size_t RowsNumber() const {
    return N;
  }

  size_t ColumnsNumber() const {
    return M;
  }

  const T& operator()(size_t n, size_t m) const {
    return matrix[n][m];
  }

  T& operator()(size_t n, size_t m) {
    return matrix[n][m];
  }

  T& At(size_t n, size_t m) {
    if (m >= M || n >= N) {
      throw MatrixOutOfRange();
    }
    return matrix[n][m];
  }

  const T& At(size_t n, size_t m) const {
    if (m >= M || n >= N) {
      throw MatrixOutOfRange();
    }
    return matrix[n][m];
  }


  Matrix<T, N, M>& operator+=(Matrix<T, N, M> mat) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        matrix[i][j] += mat(i, j);
      }
    }
    return *this;
  }

  Matrix<T, N, M>& operator-=(Matrix<T, N, M> mat) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        matrix[i][j] -= mat(i, j);
      }
    }
    return *this;
  }

  Matrix<T, N, M>& operator*=(Matrix<T, M, M> mat) {
    Matrix<T, N, M> temp_matrix;
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        for (size_t k = 0; k < M; ++k) {
          temp_matrix(i, j) += matrix[i][k] * mat(k, j);
        }
      }
    }
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        matrix[i][j] = temp_matrix(i, j);
      }
    }
    return *this;
  }

  Matrix<T, N, M>& operator*=(double x) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        matrix[i][j] *= x;
      }
    }
    return *this;
  }

  Matrix<T, N, M>& operator/=(double x) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        matrix[i][j] /= x;
      }
    }
    return *this;
  }
};

template <class T, size_t N, size_t M>
Matrix<T, M, N> GetTransposed(Matrix<T, N, M> mat) {
  Matrix<T, M, N> transposed;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      transposed(j, i) = mat(i, j);
    }
  }
  return transposed;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M> operator+(Matrix<T, N, M> first, Matrix<T, N, M> second) {
  Matrix<T, N, M> sum;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      sum(i, j) = first(i, j) + second(i, j);
    }
  }
  return sum;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M> operator-(Matrix<T, N, M> first, Matrix<T, N, M> second) {
  Matrix<T, N, M> dif;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      dif(i, j) = first(i, j) - second(i, j);
    }
  }
  return dif;
}

template <class T, size_t N, size_t M, size_t L>
Matrix<T, N, M> operator*(Matrix<T, N, L> first, Matrix<T, L, M> second) {
  Matrix<T, N, M> mult;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      for (size_t k = 0; k < L; ++k) {
        mult(i, j) += first(i, k) * second(k, j);
      }
    }
  }
  return mult;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M> operator*(Matrix<T, N, M> mat, double x) {
  Matrix<T, N, M> mult = mat;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      mult(i, j) *= x;
    }
  }
  return mult;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M> operator*(double x, Matrix<T, N, M> mat) {
  Matrix<T, N, M> mult = mat;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      mult(i, j) *= x;
    }
  }
  return mult; 
}

template <class T, size_t N, size_t M>
Matrix<T, N, M> operator/(Matrix<T, N, M> mat, double x) {
  Matrix<T, N, M> div = mat;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      div(i, j) /= x;
    }
  }
  return div;
}

template <class T, size_t N, size_t M>
bool operator==(Matrix<T, N, M> first, Matrix<T, N, M> second) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      if (first(i, j) != second(i, j)) {
        return first(i, j) == second(i, j);
      }
    }
  }
  return first(0, 0) == second(0, 0);
}

template <class T, size_t N, size_t M>
bool operator!=(Matrix<T, N, M> first, Matrix<T, N, M> second) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      if (first(i, j) != second(i, j)) {
        return first(i, j) != second(i, j);
      }
    }
  }
  return first(0, 0) != second(0, 0);
}

template <class T, size_t N, size_t M>
std::istream& operator>>(std::istream& min, Matrix<T, N, M>& mat) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      min >> mat.matrix[i][j];
    }
  }
  return min;
}

template <class T, size_t N, size_t M>
std::ostream& operator<<(std::ostream& mout, const Matrix<T, N, M>& mat) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      if (j < M - 1) {
        mout << mat(i, j) << " ";
      } else {
        mout << mat(i, j) << '\n';
      }
    }
  }
  return mout;
}

#endif /* MATRIX_H */