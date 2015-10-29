//*********************************************************
//
// hill-algorithm.cxx - the implement of hill algorithm
//
// Author: Jeff Wen
//*********************************************************

#include <iostream>
#include <stdexcept>
#include "hill-algorithm.h"

//*********************************************************
// Constructor of Matrix class
//*********************************************************
Matrix::Matrix(std::array<std::array<int, matrSize>, matrSize> m) {
  for (int i = 0; i < matrSize; i++) {
    for (int j = 0; j < matrSize; j++)
      matrix[i][j] = m[i][j];
  }
}

//*********************************************************
// Copy constructor of Matrix class
//*********************************************************
Matrix::Matrix(const Matrix &m)
{
  for (int i = 0; i < matrSize; i++) {
    for (int j = 0; j < matrSize; j++)
      matrix[i][j] = m[i][j];
  }
}

//*********************************************************
// Print the matrix
//*********************************************************
void Matrix::print(void)
{
  for (auto low:matrix) {
    for (auto n:low)
      std::cout << n << "\t";
    std::cout << std::endl;
  }
}
std::string Matrix::toString(void) {
  std::string str;
  for (auto low:matrix) 
    for (auto n:low)
      str.push_back(char(n + int('a')));
  return str;
}

//*********************************************************
// Parse string to set matrix values
// String must be low cased and 'a' is treated as 0
// Return 0 if succeed.
//*********************************************************
int Matrix::parseString(std::string str) {
  if (int(str.length()) != matrSize * matrSize) return -1;
  for (int i = 0; i < matrSize; i++) {
    for (int j = 0; j < matrSize; j++) {
      if (str[i * matrSize + j] >= 'a' && str[i * matrSize + j] <= 'z')
        matrix[i][j] = int(str[i * matrSize + j] - 'a');
      else
        return 1;
    }
  }
  return 0;
}

//*********************************************************
// Overload the "+" operator 
//*********************************************************
Matrix Matrix::operator+(const Matrix& b)
{
  Matrix rtv;
  for (int i = 0; i < matrSize; i++) {
    for (int j = 0; j < matrSize; j++)
      rtv[i][j] += matrix[i][j];
  }
  return rtv;
}

//*********************************************************
// this * b
//*********************************************************
Matrix Matrix::leftMulti(Matrix b) {
  Matrix rtv;
  for (int i = 0; i < matrSize; i++) {
    for (int j = 0; j < matrSize; j++) {
      rtv[i][j] = 0;
      for (int ct = 0; ct < matrSize; ct++) {
        rtv[i][j] += matrix[i][ct] * b[ct][j];
      }
      rtv[i][j] = (rtv[i][j] % 26 + 26) % 26;
      //std::cout << std::endl; //debug
    }
  }
  return rtv;
}

//*********************************************************
// Overload the "[]" operator 
//*********************************************************
const std::array<int, matrSize> 
Matrix::operator[](const unsigned index) const {
  if (index < matrSize)
    return matrix[index];
  throw std::out_of_range("Out of bound");
}

std::array<int, matrSize>& 
Matrix::operator[](const unsigned index) {
  if (index < matrSize)
    return matrix[index];
  throw std::out_of_range("Out of bound");
}

//*********************************************************
// Calc cofactor matrix
//*********************************************************

// Temporary function to get sub-matrix
// m and r should be located before invoking
void cutMatrix(int **m, int **r, int order, int row, int column) {
  int row_offset, col_offset;
  for (int i = 0; i < order - 1; i++) {
    for (int j = 0; j < order - 1; j++) {
      if (i >= row)
        row_offset = 1;
      else 
        row_offset = 0;
      if (j >= column)
        col_offset = 1;
      else 
        col_offset = 0;
      r[i][j] = m[i + row_offset][j + col_offset];
      //std::cout << r[i][j] << " ";//debug
    }
    //std::cout << std::endl; //debug
  }
}

// Calculate determinante of a matrix
int calcDet(int **m, int order) {
  if (order <= 2) {
    return m[0][0] * m[1][1] - m[1][0] * m[0][1];
  }
  order--;
  int sum = 0;
  bool flag = true;
  int **nm = new int*[order];
  for (int i = 0; i < order; i++)
    nm[i] = new int[order];
  for (int i = 0; i < order + 1; i++) {
    //std::cout << "*********************" << std::endl;//debug
    cutMatrix(m, nm, order + 1, 0, i);
    if (flag)
      sum += m[0][i] * calcDet(nm, order);
    else 
      sum -= m[0][i] * calcDet(nm, order);
    flag = !flag;
    //std::cout << "*********************" << std::endl;//debug
  }
  for (int i = 0; i < order; i++)
    delete[] nm[i];
  delete[] nm;
  return sum;
}

// Cofactor matrix
Matrix Matrix::cofactor(void) {
  // Init arrays
  Matrix result;
  int **m = new int*[matrSize];
  for (int i = 0; i < matrSize; i++)
    m[i] = new int[matrSize];
  for (int i = 0; i < matrSize; i++)
    for (int j = 0; j < matrSize; j++)
      m[i][j] = matrix[i][j];

  int **fdet = new int*[matrSize - 1];
  for (int i = 0; i < matrSize - 1; i++)
    fdet[i] = new int[matrSize - 1];

  for (int i = 0; i < matrSize; i++) {
    for (int j = 0; j < matrSize; j++) {
      int flag = 1;
      for (int ct = 0; ct < i + j; ct++)
        flag = flag * (-1);
      cutMatrix(m, fdet, matrSize, i, j);
      result[i][j] = flag * calcDet(fdet, matrSize - 1);
    }
  }

  // Delete arrays
  for (int i = 0; i < matrSize - 1; i++) {
    delete[] m[i];
    delete[] fdet[i];
  }
  delete[] m[matrSize - 1];
  delete[] fdet;
  delete[] m;

  //std::cout << "debug" << std::endl;//debug
  return result;
}

//*********************************************************
//*********************************************************
int Matrix::det() {
  int **m = new int*[matrSize];
  for (int i = 0; i < matrSize; i++)
    m[i] = new int[matrSize];
  for (int i = 0; i < matrSize; i++)
    for (int j = 0; j < matrSize; j++)
      m[i][j] = matrix[i][j];
  return calcDet(m, matrSize);
}

//*********************************************************
// Transpose matrix
//*********************************************************
Matrix Matrix::transpose(void)
{
  std::array<std::array<int, matrSize>, matrSize> m;
  for (int i = 0; i < matrSize; i++) {
    for (int j = 0; j < matrSize; j++) {
      m[i][j] = matrix[j][i];
    }
  }
  return Matrix(m);
}

//*********************************************************
// Inverse matrix in specific mod 
//*********************************************************

// Calculate a number's inverse in specific mod
int calcModInverse(int num, int mod) {
  num = num % mod;
  if (num < 0) num += mod;
  
  int rtv = 0;
  do {
    rtv++;
  } while ((num * rtv % mod) != 1 && rtv < mod);
  if (rtv == mod)
    return -1;
  else
    return rtv;
}

//*********************************************************
// Inverse a matrix in a specific mod
// Will throw a integer if the operation cannot be done
//*********************************************************
Matrix Matrix::inverse(int mod) {
  Matrix c = this->cofactor();
  Matrix rtv;
  int det = this->det();
  //std::cout << "Det: " << det << std::endl; //debug
  int reversedDet = calcModInverse(det, mod);
  //std::cout << "Reversed det: " << reversedDet << std::endl; //debug
  if (reversedDet == -1) throw 0;

  for (int i = 0; i < matrSize; i++) {
    for (int j = 0; j < matrSize; j++) {
      rtv[i][j] = c[i][j] * reversedDet;
      rtv[i][j] = (rtv[i][j] % mod + mod) % mod;
    }
  }
  return rtv.transpose();
}

//*********************************************************
// Hill cipher
//*********************************************************
Matrix Matrix::hillCipher(Matrix plainText) {
  return plainText.leftMulti(this->transpose());
  //return this->leftMulti(plainText.transpose()).transpose();
}

//*********************************************************
// Hill decryption
//*********************************************************
Matrix Matrix::hillDecrypt(Matrix c) {
  return c.leftMulti(this->transpose().inverse(26));
  //return this->inverse(26).leftMulti(c.transpose()).transpose();
}

