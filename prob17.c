/**
* @file     prob17.c
* @author   Stavros Vagionitis
* @date     xx Mar 2015
* @brief    [Problem 17 in Project Euler](https://projecteuler.net/problem=17)
*           Number letter counts
*           ====================
*           If the numbers 1 to 5 are written out in words: one, two, three, four, five,
*           then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.
*
*           If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, 
*           how many letters would be used?
*
*           NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and forty-two) contains 23 letters and
*           115 (one hundred and fifteen) contains 20 letters. The use of "and" when writing out numbers is in compliance with British usage.
*
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Lookup table of the words of numbers.
// Another lookup table would be with only
// the sizes
const char *number_words_lu_tbl[] = {
    "zero",     "one",      "two",          "three",    "four",     //  0,  1,  2,   3,    4
    "five",     "six",      "seven",        "eight",    "nine",     //  5,  6,  7,   8,    9
    "ten",      "eleven",   "twelve",       "thirteen", "fourteen", // 10, 11, 12,  13,   14
    "fifteen",  "sixteen",  "seventeen",    "eighteen", "nineteen", // 15, 16, 17,  18,   19
    "twenty",   "thirty",   "forty",        "fifty",    "sixty",    // 20, 30, 40,  50,   60
    "seventy",  "eighty",   "ninety",       "hundred",  "thousand"  // 70, 80, 90, 100, 1000
};

#define NUMBER_WORDS_LUTBL_SZ (sizeof (number_words_lu_tbl) / sizeof (const char *))

/**
 * \brief Check if a number is multiple of another number.
 *
 * \param   num     The number to check if it's multiple
 * \param   mult    The multiple to be checked.
 * \return  1 if it's multiple, 0 if not.
 */
uint8_t isMultiple(uint64_t num, uint64_t mult)
{
    if (num % mult == 0)
        return 1;
    else
        return 0;
}

uint8_t convert_number_to_word(uint64_t num, char **num_word, size_t *len_num_word)
{
    *num_word = NULL;
    *len_num_word = 0;
    size_t sz_num_word = 0;

    if (num < 21)
    {
        sz_num_word= strlen(number_words_lu_tbl[num])+1;

        *num_word = calloc(sz_num_word, sizeof(char));
        if (*num_word == NULL)
        {
            fprintf(stderr, "%s:%d Mem Alloc failed\n", __func__, __LINE__);
            return 0;
        }

        snprintf(*num_word, sz_num_word, "%s", number_words_lu_tbl[num]);
    }
    else if (num > 20 && num < 100)
    {
        uint64_t first_digit = num / 10;
        uint64_t last_digit = num % 10;

        if (last_digit == 0)
        {
            sz_num_word = strlen(number_words_lu_tbl[18 + first_digit]) + 1;

            *num_word = calloc(sz_num_word, sizeof(char));
            if (*num_word == NULL)
            {
                fprintf(stderr, "%s:%d Mem Alloc failed\n", __func__, __LINE__);
                return 0;
            }

            snprintf(*num_word, sz_num_word, "%s", number_words_lu_tbl[18 + first_digit]);
        }
        else
        {
            sz_num_word = strlen(number_words_lu_tbl[18 + first_digit]) + \
                          strlen(number_words_lu_tbl[last_digit])+1;

            *num_word = calloc(sz_num_word, sizeof(char));
            if (*num_word == NULL)
            {
                fprintf(stderr, "%s:%d Mem Alloc failed\n", __func__, __LINE__);
                return 0;
            }

            snprintf(*num_word, sz_num_word, "%s%s", number_words_lu_tbl[18 + first_digit], number_words_lu_tbl[last_digit]);
        }
    }
    else if (num > 99 && num < 1000)
    {
        uint64_t last_two_digits = num % 100;
        uint64_t first_digit = num / 100;

        // if 100, 200, 300, ...
        if (last_two_digits == 0)
        {
            sz_num_word = strlen(number_words_lu_tbl[first_digit]) + \
                          strlen(number_words_lu_tbl[28])+1;

            *num_word = calloc(sz_num_word, sizeof(char));
            if (*num_word == NULL)
            {
                fprintf(stderr, "%s:%d Mem Alloc failed\n", __func__, __LINE__);
                return 0;
            }

            snprintf(*num_word, sz_num_word, "%s%s",number_words_lu_tbl[first_digit], number_words_lu_tbl[28]);
        }
        else
        {
            sz_num_word = strlen(number_words_lu_tbl[first_digit]) + \
                          strlen(number_words_lu_tbl[28]) + strlen("and");
        }

        if (last_two_digits < 21 && last_two_digits != 0)
        {
            sz_num_word += strlen(number_words_lu_tbl[last_two_digits])+1;

            *num_word = calloc(sz_num_word, sizeof(char));
            if (*num_word == NULL)
            {
                fprintf(stderr, "%s:%d Mem Alloc failed\n", __func__, __LINE__);
                return 0;
            }

            snprintf(*num_word, sz_num_word, "%s%sand%s",number_words_lu_tbl[first_digit], number_words_lu_tbl[28], number_words_lu_tbl[last_two_digits]);
        }
        else if (last_two_digits > 20)
        {
            uint64_t first_digit1 = last_two_digits / 10;
            uint64_t last_digit = last_two_digits % 10;

            if (last_digit == 0)
            {
                sz_num_word += strlen(number_words_lu_tbl[18 + first_digit1]) + 1;

                *num_word = calloc(sz_num_word, sizeof(char));
                if (*num_word == NULL)
                {
                    fprintf(stderr, "%s:%d Mem Alloc failed\n", __func__, __LINE__);
                    return 0;
                }

                snprintf(*num_word, sz_num_word, "%s%sand%s",number_words_lu_tbl[first_digit], number_words_lu_tbl[28],
                                                             number_words_lu_tbl[18 + first_digit1]);
            }
            else
            {
                sz_num_word += strlen(number_words_lu_tbl[18 + first_digit1]) + \
                               strlen(number_words_lu_tbl[last_digit])+1;

                *num_word = calloc(sz_num_word, sizeof(char));
                if (*num_word == NULL)
                {
                    fprintf(stderr, "%s:%d Mem Alloc failed\n", __func__, __LINE__);
                    return 0;
                }

                snprintf(*num_word, sz_num_word, "%s%sand%s%s",number_words_lu_tbl[first_digit], number_words_lu_tbl[28],
                                                               number_words_lu_tbl[18 + first_digit1], number_words_lu_tbl[last_digit]);
            }
        }
    }
    else
    {
        uint64_t first_digit = num / 1000;
        uint64_t last_three_digits = num % 1000;

        // if 1000, 2000, 3000, ...
        if (last_three_digits == 0)
        {
            sz_num_word = strlen(number_words_lu_tbl[first_digit]) + \
                          strlen(number_words_lu_tbl[29])+1;

            *num_word = calloc(sz_num_word, sizeof(char));
            if (*num_word == NULL)
            {
                fprintf(stderr, "%s:%d Mem Alloc failed\n", __func__, __LINE__);
                return 0;
            }

            snprintf(*num_word, sz_num_word, "%s%s",number_words_lu_tbl[first_digit], number_words_lu_tbl[29]);
        }

    }

    *len_num_word = strlen(*num_word);

    return 1;
}

/**
 * \brief The solution using a naive way.
 *
 * \param   num  Number to do something.
 * \return  1 if everything is ok, 0 if not.
 */
uint8_t solution1(uint64_t num)
{
    uint64_t sum_len = 0;
    size_t len = 0;
    char *nw = NULL;

    for (uint64_t i = 1;i<=num;i++)
    {
        len = 0;
        nw = NULL;

        convert_number_to_word(i, &nw, &len);
        sum_len += len;

#if 0
        fprintf(stdout, "%ju - %s(%d)\n", i, nw, len);
#endif

        if (nw)
            free(nw);
    }

    fprintf(stdout, "Number of letters from 1 to %ju is %ju\n", num, sum_len);

    return 1;
}

/**
 * \brief Usage of this program.
 *
 * \param   argv0   The first argument string which is the current executable.
 * \return  -1.
 */
int usage(char *argv0)
{
    fprintf(stdout, "%s <Number to do something.>\n", argv0);
    return -1;
}


int main(int argc, char *argv[])
{
    if (argc != 2)
        return usage(argv[0]);

    uint64_t num = strtoull(argv[1], NULL, 10);

    solution1(num);

    return 0;
}
