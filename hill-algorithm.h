//*********************************************************
// hill-algorithm.h
//
// Class and prototypes 
//
// Author: Jeff Wen
// Email: mjeffwhen@gmail.com
//*********************************************************

#ifndef HILL_ALGORITHM_H
#define HILL_ALGORITHM_H

#include <array>

const int matrSize = 4;

#ifdef DEBUG
# define DEBUG_PRINT(m) std::cout << (m)
#else
# define DEBUG_COUT(m)
#endif


class Matrix
{
  public:
  Matrix(){}
  Matrix(std::array<std::array<int, matrSize>, matrSize>);
  Matrix(const Matrix&);

  // Overload operator "[]"
  const std::array<int, matrSize> operator[](const unsigned) const;
  std::array<int, matrSize>& operator[](const unsigned);
  // Overload operator "+"
  Matrix operator+(const Matrix& b);
  // Left multi b
  Matrix leftMulti(Matrix b);
  // Print the matrix
  void print(void);

  // Convert to string, read in row
  std::string toString(void);
  // Parse string
  int parseString(std::string);
  // Calc cofactor matrix
  Matrix cofactor(void);
  // Calc transpose matrix
  Matrix transpose(void);
  // Inverse the matrix
  Matrix inverse(int);
  // Calculate the determinant
  int det();

  // Cipher
  Matrix hillCipher(Matrix);
  // Decryption
  Matrix hillDecrypt(Matrix);

  protected:
  std::array<std::array<int, matrSize>, matrSize> matrix;
};

#endif
