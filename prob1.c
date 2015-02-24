/**
* @file     prob1.c
* @author   Stavros Vagionitis
* @date     12 Feb 2015
* @brief    [Problem 1 in Project Euler](https://projecteuler.net/problem=1)
*           Multiples of 3 and 5
*           ====================
*           If we list all the natural numbers below 10 that are multiples of 3 or 5,
*           we get 3, 5, 6 and 9. The sum of these multiples is 23. Find the sum of all
*           the multiples of 3 or 5 below 1000.
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
 * \brief The solution using a naive way.
 *
 * \param   maxNum  The max number to iterate.
 * \return  1 if everything is ok, 0 if not.
 */
uint8_t solution1(uint64_t maxNum)
{
    uint64_t sum = 0;
    for (uint64_t i = 0;i < maxNum;i++)
        if (isMultiple(i, 3) || isMultiple(i, 5))
            sum += i;

    fprintf(stdout, "Sum: %u\n", sum);

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
    fprintf(stdout, "%s <Max number to calculate.>\n", argv0);
    return -1;
}


int main(int argc, char *argv[])
{
    if (argc != 2)
        return usage(argv[0]);

    uint64_t maxNum = strtoull(argv[1], NULL, 10);

    solution1(maxNum);

    return 0;
}
