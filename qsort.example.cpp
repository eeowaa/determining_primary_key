/* Duplicates can be found any time elements are compared... */
quicksort([5, 3, 6, 2, 3]);
quicksort([5, 3, 6, 2, 3], 0, 4); // pretend there are > 10 elements
int pivot = median3([5, 3, 6, 2, 3], 0, 4) {
    int center = 2;
    if (6 < 5)
        swap(6, 5); /* 6, 3, 5, 2, 3 */
    if (3 < 6)
        swap(6, 3); /* 3, 3, 5, 2, 6 */
    if (6 < 5)
        swap(5, 6); /* N/A */

    swap(5, 2);     /* 3, 3, 2, 5, 6 */
    return 5;
}
pivot = 5;
int i = 0, j = 4 - 1; /* 3 */
    
