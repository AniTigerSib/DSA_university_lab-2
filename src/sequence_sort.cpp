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

void MSD(int *data, int size) {
    int i = 0;
    uint Mask = 0;
    for (i = 0; i < size; i++) {
        Mask |= (uint) data[i];
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
// За количество сравнений принять количество смен (свапов),
// так как мы по сути сраниваем элементы, которые меняем местами
// только за счет битовой операции. Мы однозначно значем, что
// елемент слева больше элемента справа и свапаем.
// Объяснить в отчете
int MSDPatrition(int* data, int low, int high, uint Mask) {
    int i = low - 1;
    int j = high + 1;
    while (true) {
        while((!(Mask & (uint)data[++i])) && i < high);
        while(((Mask & (uint)data[--j])) && j > low);
        if (i >= j) break;
        Swap(data[i], data[j]);
    }
    return (i == j && i == high) ? ++i : i;
}