This directory contains code to programmatically determine unique combinations
of columns in a table.  Take this table for example:

| A | B | C |
|---|---|---|
| 0 | 1 | 2 |
| 1 | 2 | 0 |
| 2 | 1 | 0 |

What columns or set of columns could be used at the primary key?  The answer:

1. `A`
2. `A`, `B`
3. `A`, `C`
4. `A`, `B`, `C`
5. `B`, `C`

Since column `A` is unique, it follows that `A` could theoretically be used as
a primary key, as well as `A` combined with any one or more other columns.
However, we prefer using `A` by itself, since minimizing the number of columns
used in a primary key reduces its complexity.

-------------------------------------------------------------------------------

Now, take this table for example:

| A | B | C |
|---|---|---|
| 1 | 1 | 2 |
| 1 | 2 | 0 |
| 2 | 1 | 0 |

The primary key could be any pair of columns, since each pair is unique:

1. `A`, `B`
2. `A`, `C`
3. `B`, `C`

-------------------------------------------------------------------------------

Here is another example:

| A | B | C |
|---|---|---|
| 1 | 1 | 2 |
| 2 | 2 | 0 |
| 2 | 1 | 0 |

This time, only two pairs of columns are unique:

1. `A`, `B`
2. `B`, `C`
