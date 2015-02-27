/**
* @file     prob14.c
* @author   Stavros Vagionitis
* @date     xx Feb 2015
* @brief    [Problem 14 in Project Euler](https://projecteuler.net/problem=14)
*           Longest Collatz sequence
*           ========================
*           The following iterative sequence is defined for the set of positive integers:
*
*           n → n/2 (n is even)
*           n → 3n + 1 (n is odd)
*
*           Using the rule above and starting with 13, we generate the following sequence:
*
*           13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1
*
*           It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms.
*           Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.
*
*           Which starting number, under one million, produces the longest chain?
*
*           NOTE: Once the chain starts the terms are allowed to go above one million.
*
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


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

/**
 * \brief Find the Collatz sequence. See http://en.wikipedia.org/wiki/Collatz_conjecture
 *        for more info.
 *
 * \param   numStart        The starting number to produce the squence
 * \param   collatz_seq     The Collatz sequence.
 * \param   sz_collatz_seq  The size of the Collatz sequence.
 * \return  1 if it's ok, 0 if not.
 */
uint8_t findCollatzSequence(const uint64_t numStart, uint64_t **collatz_seq, uint64_t *sz_collatz_seq)
{
    uint64_t num = numStart;
    uint64_t *tmp = NULL;


    if (num == 0 || num == 1)
    {
        fprintf(stderr, "%s:%d Number is 0 or 1.\n", __func__, __LINE__);
        return 0;
    }

    // Add the initial value.
    *sz_collatz_seq = 1;
    tmp = realloc(*collatz_seq, *sz_collatz_seq * sizeof(uint64_t));
    if (tmp != NULL)
        *collatz_seq = tmp;
    else
    {
        fprintf(stderr, "%s:%d Mem Alloc failed\n", __func__, __LINE__);

        if (*collatz_seq)
            free(*collatz_seq);

        return 0;
    }
    (*collatz_seq)[*sz_collatz_seq - 1] = num;


    while(num != 1)
    {
        if (isMultiple(num,2))
            num/=2;
        else
            num = 3*num + 1;

        *sz_collatz_seq += 1;

        tmp = realloc(*collatz_seq, *sz_collatz_seq * sizeof(uint64_t));
        if (tmp != NULL)
            *collatz_seq = tmp;
        else
        {
            fprintf(stderr, "%s:%d Mem Alloc failed\n", __func__, __LINE__);

            if (*collatz_seq)
                free(*collatz_seq);

            return 0;
        }

        (*collatz_seq)[*sz_collatz_seq - 1] = num;

    }

    return 1;
}

/**
 * \brief The solution using a naive way.
 *
 * \param   num  Upper limit to find the longest sequence.
 * \return  1 if everything is ok, 0 if not.
 */
uint8_t solution1(uint64_t num)
{
    uint64_t *collatz_sq = NULL;
    uint64_t sz_collatz_sq = 0;

    uint64_t max_collatz_chain = 0;
    uint64_t max_collatz_chain_num = 0;

    for (uint64_t i = 2;i<num;i++)
    {
        collatz_sq = NULL;

        findCollatzSequence(i, &collatz_sq, &sz_collatz_sq);

        if (sz_collatz_sq > max_collatz_chain)
        {
            max_collatz_chain = sz_collatz_sq;
            max_collatz_chain_num = i;
        }

#if 0
        for (uint64_t j = 0;j<sz_collatz_sq;j++)
        {
            if (j == 0)
                fprintf(stdout, "\n%ju ->", collatz_sq[j]);
            else if (j == sz_collatz_sq - 1)
                fprintf(stdout, " %ju\n", collatz_sq[j]);
            else
                fprintf(stdout, " %ju ->", collatz_sq[j]);
        }
#endif

        if (collatz_sq)
            free(collatz_sq);
    }

    fprintf(stdout, "Number %ju produce longest chain: %ju under %ju\n", max_collatz_chain_num, max_collatz_chain, num);

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
    fprintf(stdout, "%s <Upper limit to find the longest sequence.>\n", argv0);
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
