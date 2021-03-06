/**
* @file     prob44.c
* @author   Stavros Vagionitis
* @date     31 Mar 2015
* @brief    [Problem 44 in Project Euler](https://projecteuler.net/problem=44)
*           Pentagon numbers
*           ================
*           Pentagonal numbers are generated by the formula, Pn=n(3n−1)/2.
*           The first ten pentagonal numbers are:
*
*           1, 5, 12, 22, 35, 51, 70, 92, 117, 145, ...
*
*           It can be seen that P4 + P7 = 22 + 70 = 92 = P8. However, their difference,
*           70 − 22 = 48, is not pentagonal.
*
*           Find the pair of pentagonal numbers, Pj and Pk, for which their sum and difference are pentagonal
*           and D = |Pk − Pj| is minimised; what is the value of D?
*
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

/**
 * \brief Get the abs value of a number.
 *        See https://graphics.stanford.edu/~seander/bithacks.html#IntegerAbs
 *        for more info.
 *
 * \param   num     The number to get absolute value.
 * \return  the absolute value.
 */
inline uint64_t abs1(int64_t num)
{
    uint64_t res = 0;
    int64_t const mask = num >> sizeof(int64_t) * 8 - 1;

    res = (num ^ mask) - mask;

    return res;
}

/**
 * \brief Generate a pentagonal number using the formula
 *        pn = n(3n-1)/2
 *
 * \param   num  Number to generate the pentagonal
 * \return  the pentagonal number.
 */
inline uint64_t generatePentagonal(uint64_t num)
{
    return (num*(3*num-1))/2;
}

/**
 * \brief Check if a number is pentagonal
 *
 * \param   num  Number to check
 * \return  1 if it's pentagonal, 0 otherwise.
 */
uint8_t isPentagonal(uint64_t num)
{
    for (uint64_t i = 1;i*i<=num;i++)
    {
        if ((2*num) == (i*(3*i-1)))
            return 1;
    }

    return 0;
}

/**
 * \brief The solution using a naive way.
 *
 * \param   num  Number to do something.
 * \return  1 if everything is ok, 0 if not.
 */
uint8_t solution1(uint64_t num)
{

    for (uint64_t i = 1;i<num;i++)
    {
        // Generate the first pentagonal
        uint64_t pj = generatePentagonal(i);

        for (uint64_t j = i+1;j<num;j++)
        {
            // Generate the second pentagonal
            uint64_t pk = generatePentagonal(j);

            uint64_t sum = pj + pk;

            // Check if the sum is pentagonal
            if (isPentagonal(sum))
            {
                uint64_t d = abs1(pk - pj);

                // Check if the difference is pentagonal
                if (isPentagonal(d))
                {
                    fprintf(stdout, "pj: %ju pk: %ju sum: %ju d: %ju\n", pj, pk, sum, d);
                }
            }
        }
    }

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
