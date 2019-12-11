#ifndef QSORT_CPP
#define QSORT_CPP
#include "isort.cpp"

/**
 * Quicksort algorithm (driver).
 */
template <class T>
void quicksort(std::vector<T> &a)
{
    quicksort(a, 0, a.size() - 1);
}

/**
 * Return median of left, center, and right.
 * Order these and hide the pivot.
 */
template <class T>
const T &median3(std::vector<T> &a, int left, int right)
{
    int center = (left + right) / 2;
    if (a[center] < a[left])
        swap(a[left], a[center]);
    if (a[right] < a[left])
        swap(a[left], a[right]);
    if (a[right] < a[center])
        swap(a[center], a[right]);

    // Place pivot at position (right - 1)
    swap(a[center], a[right - 1]);
    return a[right - 1];
}

/**
 * Internal quicksort method that makes recursive calls.  Uses median-of-three
 * partitioning and a cutoff of 10.  `a' is an array of T objects.  `left' is
 * the left-most index of the subarray.  `right' is the right-most index of the
 * subarray.
 */
template <class T>
void quicksort(std::vector<T> &a, int left, int right)
{
    // If the vector contains 10 or fewer elements
    if (left + 10 <= right) {

        // Pivot on the median element
        T pivot = median3(a, left, right);

        // Begin partitioning
        int i = left, j = right - 1;
        for (;;) {
            while (a[++i] < pivot)
                ;
            while (a[--j] > pivot)
                ;
            if (i < j)
                swap(a[i], a[j]);
            else
                break;
        }
        // Restore point
        swap(a[i], a[right - 1]);

        quicksort(a, left, i - 1);  // Sort small elements
        quicksort(a, i + 1, right); // Sort large elements
    } else {
        // Do an insertion sort on the subarray
        insertionSort(a, left, right);
    }
}
#endif
