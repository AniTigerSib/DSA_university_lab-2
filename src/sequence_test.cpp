#include "sequence_test.hpp"

int SequenceSortedTest(int *seq, int length) {
    int i = 0;
    for (i = 0; (i < length - 1) && (seq[i] <= seq[i + 1]); i++);
    return (i == length - 1) ? 1 : 0;
}