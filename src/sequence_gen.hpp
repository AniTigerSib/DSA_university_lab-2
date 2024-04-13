#ifndef SEQUENCE_GEN_HPP
#define SEQUENCE_GEN_HPP

#include <random>
#include <algorithm>

void GenerateSawtoothSequence(int *data, size_t size, int min_value, int max_value);
void GenerateSortedSquence(int *sequence, int lenght, bool ascending);
void GenerateRandomSequence(int *data, size_t size, int min_value, int max_value);
void GenerateSequenceWithType(int *sequence, int size, int type, int min_value, int max_value);

#endif