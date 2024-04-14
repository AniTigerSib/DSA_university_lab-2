#include <cstdlib>
#include <iostream>

#include "sequence_gen.hpp"
#include "sequence_sort.hpp"
#include "sequence_test.hpp"

#define TEST_CASES_NUM 10
#define GENERATE_FUNC_NUM 4
#define INSERTION_MIN_SEQ_SIZE 1e4
#define INSERTION_SORT_SEQ_CASE_STEP 5e3
// #define MIN_SEQ_SIZE 5e5
// #define SORT_SEQ_CASE_STEP 5e5

int g_size_of_sequence = 0;
int g_seq_step = 0;
int g_func_to_test_num = 0;
// 0 - InsertionSortWithKey
// 1 - ShellSort
// 2 - MSD_1
// 3 - MSD_2
// 4 - MSD_4
// 5 - MSD_8
// 6 - qsort
int g_msd_sort_num = 0;

long long g_compare_count = 0;
int* AH = NULL; // For MSD_2/4/8

int main(int argc, char** argv) {
    const TestFunction functions_to_test[4] = {InsertionSortWithKey, ShellSort, MSD, MSDG};
    if (argc != 4) {
        std::cout << "Not correct amount of command line params\n";
        return 0;
    }
    g_size_of_sequence = atoi(argv[1]);
    g_seq_step = atoi(argv[2]);
    g_func_to_test_num = atoi(argv[3]);
    if (g_func_to_test_num > 2) {
        g_msd_sort_num = g_func_to_test_num - 3;
        g_func_to_test_num = 3;
    }
    

    // int* sequence = (int*)calloc(g_size_of_sequence, sizeof(int));
    // GenerateSawtoothSequence(sequence, g_size_of_sequence, MINIMAL_SEQUENCE_VAL, MAXIMAL_SEQUENCE_VAL);
    // GenerateSortedSquence(sequence, g_size_of_sequence, false);

    // std::cout << TestFunctionsForCorrectSorting(functions_to_test, 3);
#ifdef TIME_TEST
    TimesPrint(functions_to_test[g_func_to_test_num]);
#endif
#ifdef COMPARE_COUNT_TEST
    ComparesPrint(functions_to_test[g_func_to_test_num]);
#endif

    // MSDG(sequence, g_size_of_sequence);
    // qsort(sequence, g_size_of_sequence, sizeof(int), Compare);
    // std::cout << SequenceSortedTest(sequence, g_size_of_sequence) << std::endl;

    return 0;
}

int TestFunctionsForCorrectSorting(const TestFunction* func_to_test, const int func_count) {
    int f_result = 1;
    for (int i = 0; i < func_count; i++) {
        int* sequence = (int*)calloc(g_size_of_sequence, sizeof(int));
        GenerateSawtoothSequence(sequence, g_size_of_sequence, MINIMAL_SEQUENCE_VAL, MAXIMAL_SEQUENCE_VAL);
        func_to_test[i](sequence, g_size_of_sequence);
        f_result &= SequenceSortedTest(sequence, g_size_of_sequence);
        free(sequence);
    }
    return f_result;
}

void TimesPrint(TestFunction func_to_test) {
    for (int i = 0; i < TEST_CASES_NUM; i++) {
        std::cout << g_size_of_sequence;
        for (int j = 0; j < GENERATE_FUNC_NUM; j++) {
            int* sequence = (int*)calloc(g_size_of_sequence, sizeof(int));
            GenerateSequenceWithType(sequence, g_size_of_sequence, j, MINIMAL_SEQUENCE_VAL,
                                     MAXIMAL_SEQUENCE_VAL);
            std::cout << "\t" << TimeOfSortingTest(func_to_test, sequence, g_size_of_sequence);
            std::cout.flush();
            free(sequence);
        }
        std::cout << std::endl;
        g_size_of_sequence += g_seq_step;
    }
}

void ComparesPrint(TestFunction func_to_test) {
    for (int i = 0; i < TEST_CASES_NUM; i++) {
        std::cout << g_size_of_sequence;
        for (int j = 0; j < GENERATE_FUNC_NUM; j++) {
            int* sequence = (int*)calloc(g_size_of_sequence, sizeof(int));
            GenerateSequenceWithType(sequence, g_size_of_sequence, j, MINIMAL_SEQUENCE_VAL,
                                     MAXIMAL_SEQUENCE_VAL);
            std::cout << "\t" << CompareCountTest(func_to_test, sequence, g_size_of_sequence);
            std::cout.flush();
            free(sequence);
        }
        std::cout << std::endl;
        g_size_of_sequence += g_seq_step;
    }
}

float TimeOfSortingTest(TestFunction func_to_test, int* seq, int length) {
    auto start = std::chrono::steady_clock::now();
#ifdef QUICK_STD_TEST
    qsort(seq, length, sizeof(int), Compare);
#else
    func_to_test(seq, length);
#endif
    auto elapsed =
        std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start);
    return elapsed.count() / 1e3;
}

long CompareCountTest(TestFunction func_to_test, int* seq, int length) {
    g_compare_count = 0;
#ifdef QUICK_STD_TEST
    qsort(seq, length, sizeof(int), Compare);
#else
    func_to_test(seq, length);
#endif
    return g_compare_count;
}

int IsBigger(int a, int b) {  // Прикрутить счетчик сравнений
    g_compare_count++;
    return a > b ? 1 : 0;
}

int Compare(const void* a, const void* b) {
    return IsBigger(*(int*)a, *(int*)b);
}

void Swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void InsertionSortWithKey(int* data, int size) {
    int key = data[0];

    for (int i = size - 1; i > 0; i--) {
        if (IsBigger(data[i - 1], data[i])) {
            Swap(data[i], data[i - 1]);
        }
    }
    for (int i = 2; i < size; i++) {
        key = data[i];
        int j = i;
        while (IsBigger(data[j - 1], key)) {
            data[j] = data[j - 1];
            j--;
        }
        data[j] = key;
    }
}

void ShellSort(int* data, int size) {
    int h = 0;
    for (h = 1; h <= size / 9; h = 3 * h + 1);
    for (; h > 0; h /= 3) {
        for (int i = h; i < size; i++) {
            int key = data[i];
            int j = i;
            while (j >= h && IsBigger(data[j - h], key)) {
                data[j] = data[j - h];
                j -= h;
            }
            data[j] = key;
        }
    }
}

// MSD_1
void MSD(int* data, int size) {
    int i = 0;
    uint Mask = 0;
    for (i = 0; i < size; i++) {
        Mask |= (uint)data[i];
    }
    for (i = 31; i >= 1; i--) {
        if (Mask & (1 << i)) {
            break;
        }
    }
    MSRadix(data, 0, size - 1, 1 << i);
}

void MSRadix(int* data, int low, int high, uint Mask) {
    if (Mask > 0 && low < high) {
        int i = MSDPatrition(data, low, high, Mask);
        MSRadix(data, low, i - 1, Mask >> 1);
        MSRadix(data, i, high, Mask >> 1);
    }
}

int MSDPatrition(int* data, int low, int high, uint Mask) {
    int i = low - 1;
    int j = high + 1;
    while (true) {
        while ((!(Mask & (uint)data[++i])) && i < high);
        while (((Mask & (uint)data[--j])) && j > low);
        if (i >= j) break;
        Swap(data[i], data[j]);
    }
    return (i == j && i == high) ? ++i : i;
}

// За количество сравнений принять количество смен (свапов),
// так как мы по сути сраниваем элементы, которые меняем местами
// только за счет битовой операции. Мы однозначно значем, что
// елемент слева больше элемента справа и свапаем.
// Объяснить в отчете


void MSDG(int* data, int size) {
    AH = (int*)malloc(sizeof(int) * size);
    switch(g_msd_sort_num) {
    case 0:
        MSRadix_2(data, 0, size - 1, 15);
        break;
    case 1:
        MSRadix_4(data, 0, size - 1, 7);
        break;
    case 2:
        MSRadix_8(data, 0, size - 1, 3);
        break;
    default:
        break;
    }
    free(AH);
}

#define digit(A,R) (((int)A >> (R*8)) & 0xFF)
// MSD_8
void MSRadix_8(int* A, int low, int high, int R) {
    int i, Cnt[257] = {0};
    if (R < 0) return;
    if (high - low <= 10) {
        InsertionSortWithKey(A + low, high - low + 1);
        return;
    }
    for (i = low; i <= high; i++) Cnt[digit(A[i], R) + 1]++;
    for (i = 1; i < 257; i++) Cnt[i] += Cnt[i - 1];
    for (i = low; i <= high; i++) AH[Cnt[digit(A[i], R)]++] = A[i];
    for (i = low; i <= high; i++) A[i] = AH[i - low];
    MSRadix_8(A, low, low + Cnt[0] - 1, R - 1);
    for (i = 0; i < 256; i++)
        MSRadix_8(A, low + Cnt[i], low + Cnt[i + 1] - 1, R - 1);
}

#undef digit
#define digit(A,R) (((int)A >> (R*4)) & 0xF)
// MSD_4
void MSRadix_4(int* A, int low, int high, int R) {
    int i, Cnt[17] = {0};
    if (R < 0) return;
    if (high - low <= 10) {
        InsertionSortWithKey(A + low, high - low + 1);
        return;
    }
    for (i = low; i <= high; i++) Cnt[digit(A[i], R) + 1]++;
    for (i = 1; i < 17; i++) Cnt[i] += Cnt[i - 1];
    for (i = low; i <= high; i++) AH[Cnt[digit(A[i], R)]++] = A[i];
    for (i = low; i <= high; i++) A[i] = AH[i - low];
    MSRadix_4(A, low, low + Cnt[0] - 1, R - 1);
    for (i = 0; i < 16; i++)
        MSRadix_4(A, low + Cnt[i], low + Cnt[i + 1] - 1, R - 1);
}

#undef digit
#define digit(A,R) (((int)A >> (R*2)) & 0x3)
// MSD_2
void MSRadix_2(int* A, int low, int high, int R) {
    int i, Cnt[5] = {0};
    if (R < 0) return;
    if (high - low <= 10) {
        InsertionSortWithKey(A + low, high - low + 1);
        return;
    }
    for (i = low; i <= high; i++) Cnt[digit(A[i], R) + 1]++;
    for (i = 1; i < 5; i++) Cnt[i] += Cnt[i - 1];
    for (i = low; i <= high; i++) AH[Cnt[digit(A[i], R)]++] = A[i];
    for (i = low; i <= high; i++) A[i] = AH[i - low];
    MSRadix_2(A, low, low + Cnt[0] - 1, R - 1);
    for (i = 0; i < 4; i++)
        MSRadix_2(A, low + Cnt[i], low + Cnt[i + 1] - 1, R - 1);
}

// По 17, 17, 16 для 4 двоичных разрядов
// 5, 5, 4 для 2 двоичных разрядов