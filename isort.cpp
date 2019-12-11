#ifndef ISORT_CPP
#define ISORT_CPP

template <class T>
void insertionSort(std::vector<T> &a)
{
    int j;
    for (int p = 1; p < a.size(); ++p) {
        T tmp = a[p];
        for (j = p; j > 0 && tmp < a[j - 1]; --j)
            a[j] = a[j - 1];
        a[j] = tmp;
    }
}

#endif
