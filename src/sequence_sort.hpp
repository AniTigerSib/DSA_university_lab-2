#ifndef SEQUENCE_SORT_HPP
#define SEQUENCE_SORT_HPP

#include <sys/types.h>
#include <cstdlib>

// #define digit(A,R) ((uchar*)&A)[R]

int IsBigger(int a, int b);
void Swap(int& a, int& b);
void InsertionSortWithKey(int* data, int size);
void ShellSort(int* data, int size);
void MSD(int *data, int size);
void MSRadix(int* data, int low, int high, uint Mask);
int MSDPatrition(int* data, int low, int high, uint Mask);
void MSDG(int *A, int Size);
void MSRadix_8(int *A, int low, int high, int R);
void MSRadix_4(int* A, int low, int high, int R);
void MSRadix_2(int* A, int low, int high, int R);

#endif