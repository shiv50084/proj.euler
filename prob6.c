/**
* @file     prob6.c
* @author   Stavros Vagionitis
* @date     24 Feb 2015
* @brief    [Problem 6 in Project Euler](https://projecteuler.net/problem=6)
*           Sum square difference
*           =====================
*           The sum of the squares of the first ten natural numbers is,
*
*           1^2 + 2^2 + ... + 10^2 = 385
*           The square of the sum of the first ten natural numbers is,
*
*           (1 + 2 + ... + 10)^2 = 55^2 = 3025
*           Hence the difference between the sum of the squares of the
*           first ten natural numbers and the square of the sum is 3025 − 385 = 2640.
*
*           Find the difference between the sum of the squares of the
*           first one hundred natural numbers and the square of the sum.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

/**
 * \brief Compute the exponential power for uint64_t
 *
 * \param   base    The base to be expanded.
 * \param   exp     The exponential.
 * \return  the computed power exponential.
 */
uint64_t pow1(uint64_t base, uint64_t exp)
{
    uint64_t t = 1;

    if (exp == 0)
        return 1;
    else
    {
        for(uint64_t i = 0;i<exp;i++)
            t*=base;
    }

    return t;
}

/**
 * \brief Compute the sum of the squares of the first maxNum
 *        natural numbers
 *
 * \param   maxNum  The max number of natural numbers to compute
 *                  the sum of squares.
 * \return  the sum of squares.
 */
uint64_t sumSquares(uint64_t maxNum)
{
    uint64_t sum = 0;

    for(uint64_t i = 1;i<=maxNum;i++)
        sum+=pow1(i,2);

    return sum;
}

/**
 * \brief Compute the square of the sum of the first maxNum
 *        natural numbers
 *
 * \param   maxNum  The max number of natural numbers to compute
 *                  the square of the sum.
 * \return  the square of the sum.
 */
uint64_t squareSum(uint64_t maxNum)
{
    uint64_t sum = 0;

    for(uint64_t i = 1;i<=maxNum;i++)
        sum+=i;

    return pow1(sum,2);
}

/**
 * \brief The solution using a naive way.
 *
 * \param   num  Number of natural numbers.
 * \return  1 if everything is ok, 0 if not.
 */
uint8_t solution1(uint64_t num)
{

    fprintf(stdout, "Difference between the square of the sum and sum of squares of the first %ju natural numbers: %ju\n", num, squareSum(num) - sumSquares(num));

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
    fprintf(stdout, "%s <Number of natural numbers.>\n", argv0);
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
