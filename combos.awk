#!/usr/bin/awk -f

# Before the program starts
BEGIN {
    # Define output control variables
    endianness = "big"
    printmask = "yes"
    placeholder = "-"
    FS = "\t"
    OFS = " "
}

# On the first input record (typically a line)
NR == 1 {

    # Determine how many fields there should be in each subsequent record
    num_elements = NF

    # Calculate the number of field combinations
    num_combinations = 2 ^ num_elements - 1
}

# If a record has the correct number of fields
NF == num_elements {

    # Print the current record verbatim
    print "# " $0

    # For each combination of fields in the current record
    for (c = 1; c <= num_combinations; ++c) {

        # Print the decimal index of the combination
        printf c ":"

        # Create a mask to apply to fields by converting the combination index
        # to binary and storing each bit in a separate array element
        for (e = num_elements; e > 0; --e) {
            element_mask[e] = rshift(c, e - 1) % 2

            # Print the mask (each bit of binary combination index) if desired
            if (printmask)
                printf element_mask[e]
        }
        if (printmask)
            printf ":"

        # For each field in the record
        for (e = num_elements; e > 0; --e) {

            # If the bit corresponding to field position within the binary
            # combination index is equal to 1
            if (element_mask[e]) {

                # Print the field, assuming field order increases right-to-left
                printf $(num_elements - e + 1)

            # Otherwise (the bit in the combination index is equal to 0)
            } else {

                # Print a "blank" placeholder
                printf placeholder
            }
        }

        # End the combination with a newline
        printf "\n"
    }

    # Separate each record with a blank line
    printf "\n"
}

# If the record has the wrong number of fields
NF != num_elements {

    # Write a warning and ignore the record
    printf "skipping line %d: wrong number of fields\n", NR > "/dev/stderr"
}
