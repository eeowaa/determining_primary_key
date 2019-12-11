#include <stdlib.h>
#include <string.h>

void isort(std::vector<T> &a)
{
    int j;
    for (int p = 1; p < a.size(); ++p) {
        T tmp = a[p];
        for (j = p; j > 0 && tmp < a[j - 1]; --j)
            a[j] = a[j - 1];
        a[j] = tmp;
    }
}

void isort(void *base, size_t nmemb, size_t size,
           int (*compar)(const void *, const void *))
{
    int j, p;
    char *tmp; /* memory safety? */

    for (p = 1; p < nmemb; ++p) {
        memcpy(tmp, base + p, size);
        for (j = p; j > 0 && (*compar)(tmp, base[j - 1]) < 0; --j)
            memcpy(base + j, base + j - 1, size);
        memcpy(base + j, tmp, size);
    }
}

/* qsort sorts an array (beginning at `base') of `nmemb' objects.  `size'
 * describes the size of each element of the array.
 *
 * You must supply a pointer to a comparison function, using the argument shown
 * as `compar'.  (This permits sorting objects of unknown properties.)  Define
 * the comparison function to accept two arguments, each a pointer to an
 * element of the array starting at `base'.  The result of `(*compar)' must be
 * negative if the first argument is less than the second, zero if the two
 * arguments match, and positive if the first argument is greater than the
 * second (where "less than" and "greater than" refer to whatever arbitrary
 * ordering is appropriate).
 *
 * The array is sorted in place; this is, when qsort returns, the array
 * elements beginning at `base' have been reordered.
 */
void qsort(void *base, size_t nmemb, size_t size,
           int (*compar)(const void *, const void *))
{
    size_t i, j, m, ms;
    char *qi, *qj, *qp, *q1, *q2, buf[BUFSIZ];

    while (nmemb > 1) {
        i = 0, j = nmemb - 1;
        qp = qj = (qi = (char *)base) + size * j;

        while (i < j) {
            /* parition about pivot */
            while (i < j && (*compar)(qi, qp) <= 0)
                ++i, qi += size;
            while (i < j && (*compar)(qp, qj) <= 0)
                --j, qj -= size;
            if (i < j) {
                /* swap elements i and j */
                q1 = qi, q2 = qj;
                /* swap as many as possible */
                for (ms = size; ms > 0; ms -= m, q1 += m, q2 -= m) {
                    m = ms < sizeof(buf) ? ms : sizeof(buf);
                    memcpy(buf, q1, m);
                    memcpy(q1, q2, m);
                    memcpy(q2, buf, m);
                }
                ++i, qi += size;
            }
            if (qi != qp) {
                /* swap elements i and pivot */
                q1 = qi, q2 = qp;
                /* swap as many as possible */
                for (ms = size; ms > 0; ms -=m , q1 += m, q2 -= m) {
                    m = ms < sizeof(buf) ? ms : sizeof(buf);
                    memcpy(buf, q1, m);
                    memcpy(q1, q2, m);
                    memcpy(q2, buf, m);
                }
            }
            j = nmemb - i - 1, qi += size;
            if (j < i) {
                /* recurse on smaller partition */
                if (j > 1)
                    qsort(qi, j, size, compar);
                nmemb = i;
            } else {
                /* lower partition is smaller */
                if (i > 1)
                    qsort(base, i, size, compar);
                nmemb = j, base = qi;
            }
        }
    }
}
