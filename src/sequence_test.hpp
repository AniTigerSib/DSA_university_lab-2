#ifndef SEQUENCE_TEST_HPP
#define SEQUENCE_TEST_HPP

#include <chrono>

typedef void (*TestFunction)(int *seq, int length);

int SequenceSortedTest(int *seq, int length);
float TimeOfSortingTest(TestFunction func_to_test, int *seq, int length);
long CompareCountTest(TestFunction func_to_test, int *seq, int length);
int TestFunctionsForCorrectSorting(const TestFunction *func_to_test, const int func_count);
void TimesPrint(TestFunction func_to_test);
void ComparesPrint(TestFunction func_to_test);

#endif