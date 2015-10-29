//*********************************************************
// main.cxx
//
// Author: Jeff Wen
// Email: mjeffwhen@gmail.com
//*********************************************************

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <string>
#include "hill-algorithm.h"

//*********************************************************
// Get matrix from "matrix.data"
// Otherwise ask for input
//*********************************************************
int matrixInit(std::array<std::array<int, matrSize>, matrSize> &matr)
{
  int i, j;
  std::ifstream matrDataFile("matrix.data");
  try {
    if (!matrDataFile.is_open()) throw 0;
    std::string sLine;
    for (i = 0; i < matrSize; i++) {
      if (!(std::getline(matrDataFile, sLine))) throw 1;
      std::stringstream ssLine(sLine);
      for (j = 0; j < matrSize; j++)
        if (!(ssLine >> matr[i][j])) throw 2;
    }
    matrDataFile.close();
  } catch (int e) {
    matrDataFile.close();
    std::ofstream matrDataOut("matrix.data");
    if (!matrDataOut.is_open()) return 1;
    std::cout << "Error: " << e << std::endl
              << "Now input the matrix: " << std::endl;;
    for (i = 0; i < matrSize; i++) {
      for (j = 0; j < matrSize; j++) {
        std::cout << "matrix[" << i << "]["
                  << j << "]: ";
        std::cin >> matr[i][j];
        matrDataOut << matr[i][j] << " ";
      }
      matrDataOut << std::endl;
    }
    matrDataOut.close();
  }
  return 0;
}

//*********************************************************
// Cipher a text
//*********************************************************
std::string cipher(Matrix k, std::string plainText) {
  std::string rtv;
  Matrix c, p;
  
  int elements = matrSize * matrSize;
  int blocks = plainText.length() / elements;
  while (plainText.length() % matrSize != 0) {
    plainText.push_back('a');
  }
  int rest = plainText.length() % elements;
  for (int i = 0; i < blocks; i++) {
    p.parseString(plainText.substr(i * elements, (i + 1) * elements));
    rtv += k.hillCipher(p).toString();
  }
  if (rest) {
    int end = plainText.length();
    std::string t;
    t = plainText.substr(end - rest, end);
    for (int i = 0; i < elements - rest; i++)
      t.push_back('a');
    p.parseString(t);
    c = k.hillCipher(p);
    rtv += c.toString().substr(0, rest);
  }
  return rtv;
}

//*********************************************************
// Decrypt a ciphered text
//*********************************************************
std::string decrypt(Matrix k, std::string cipheredText) {
  std::string rtv;
  Matrix c, p;
  
  int elements = matrSize * matrSize;
  int blocks = cipheredText.length() / elements;
  int rest = cipheredText.length() % elements;
  for (int i = 0; i < blocks; i++) {
    c.parseString(cipheredText.substr(i * elements, (i + 1) * elements));
    rtv += k.hillDecrypt(c).toString();
  }
  if (rest) {
    int end = cipheredText.length();
    std::string t;
    t = cipheredText.substr(end - rest, end);
    for (int i = 0; i < elements - rest; i++)
      t.push_back('a');
    c.parseString(t);
    p = k.hillDecrypt(c);
    rtv += p.toString().substr(0, rest);
  }
  return rtv;
}

int main()
{
  std::array<std::array<int, matrSize>, matrSize> matrix;
  if(matrixInit(matrix)) return 1;
  Matrix k(matrix);
  Matrix p, c;

  std::cout << "Ciphered text: " << cipher(k, "ohiamfuckinghandsomeyesiam") << std::endl;
  std::cout << "Plain text: " << decrypt(k, cipher(k, "ohiamfuckinghandsomeyesiam")) << std::endl;

  return 0;
}

