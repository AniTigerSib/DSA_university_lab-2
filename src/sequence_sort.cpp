#include "sequence_sort.hpp"

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
        while (IsBigger(data[j-1], key)) {
            data[j] = data[j-1];
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
            while (j >= h && data[j - h] > key) {
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

int g_msd_sort_num = 0;
// 0 - MSD_2
// 1 - MSD_4
// 2 - MSD_8

int* AH = NULL; // For MSD_2/4/8

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