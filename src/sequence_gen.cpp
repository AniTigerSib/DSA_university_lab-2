#include "sequence_gen.hpp"

void GenerateSawtoothSequence(int *data, size_t size, int min_value, int max_value) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min_value, max_value);

    data[0] = dist(gen);
    data[size - 1] = dist(gen);

    bool increasing = true;
    for (int i = 1; i < (int) size - 1; i++) {
        if (increasing) {
            data[i] = dist(gen);
            while (data[i] <= data[i - 1]) {
                data[i] = dist(gen);
            }
        } else {
            data[i] = dist(gen);
            while (data[i] >= data[i - 1]) {
                data[i] = dist(gen);
            }
        }
        increasing = !increasing;
    }
}

void GenerateSortedSquence(int *sequence, int lenght, bool ascending = true) {
    if (ascending) {
        for (int i = 0; i < lenght; i++) {
            sequence[i] = i;
        }
    } else {
        for (int i = 0; i < lenght; i++) {
            sequence[i] = lenght - i - 1;
        }
    }
}

void GenerateRandomSequence(int *data, size_t size, int min_value, int max_value) {
    // Генератор случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());

    // Распределение
    using Dist = std::uniform_int_distribution<int>;

    Dist dist(min_value, max_value);

    // Генерация случайных чисел
    for (size_t i = 0; i < size; ++i) {
        data[i] = dist(gen);
    }

    // Перемешивание
    std::shuffle(data, data + size, gen);
}

void GenerateSequenceWithType(int *sequence, int size, int type, int min_value, int max_value) {
    switch (type) {
    case 0:
        GenerateSortedSquence(sequence, size, true);
        break;
    case 1:
        GenerateRandomSequence(sequence, size, min_value, max_value);
        break;
    case 2:
        GenerateSortedSquence(sequence, size, false);
        break;
    case 3:
        GenerateSawtoothSequence(sequence, size, min_value, max_value);
        break;
    default:
        break;
    }
}