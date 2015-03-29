/**
* @file     prob30.c
* @author   Stavros Vagionitis
* @date     29 Mar 2015
* @brief    [Problem 30 in Project Euler](https://projecteuler.net/problem=30)
*           Digit fifth powers
*           ==================
*           Surprisingly there are only three numbers that can be written as the
*           sum of fourth powers of their digits:
*
*           1634 = 1^4 + 6^4 + 3^4 + 4^4
*           8208 = 8^4 + 2^4 + 0^4 + 8^4
*           9474 = 9^4 + 4^4 + 7^4 + 4^4
*
*           As 1 = 1^4 is not a sum it is not included.
*
*           The sum of these numbers is 1634 + 8208 + 9474 = 19316.
*
*           Find the sum of all the numbers that can be written as the sum of fifth powers of their digits.
*
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

/**
 * \brief Count the digits of a number
 *
 * \param   n     The number to count the digits
 * \return the number of digits.
 */
uint64_t count_digits(const uint64_t n)
{
    uint64_t counter = 0;
    uint64_t num = n;

    while(num)
    {
        num/=10;
        counter++;
    }

    return counter;
}

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
    else if (exp == 1)
        return base;
    else if (exp == 2)
        return base * base;
    else
    {
        for(uint64_t i = 0;i<exp;i++)
            t*=base;
    }

    return t;
}

/**
 * \brief Checks if the sum of digits in power exp
 *        equals with the number
 *
 * \param   num     The number to checks
 * \param   exp     The exponential of the digits.
 * \return  1 if it's true, 0 otherwise.
 */
uint8_t isSumOfDigitPowers(const uint64_t num, uint64_t exp)
{
    uint64_t n = num;
    uint64_t cd = count_digits(n);
    uint64_t sum = 0;

    if (cd == 1 || n == 0)
        return 0;

    while(n)
    {
        uint64_t d = n % 10;

        sum += pow1(d, exp);

        n/=10;
    }

    if (sum == num)
        return 1;
    else
        return 0;
}

/**
 * \brief The solution using a naive way.
 *
 * \param   num  Max number to check.
 * \return  1 if everything is ok, 0 if not.
 */
uint8_t solution1(uint64_t num)
{
    uint64_t sum = 0;
    for (uint64_t i = 0;i<num;i++)
    {
        if (isSumOfDigitPowers(i, 5))
        {
            fprintf(stdout, "Number %ju equals with the sum of %juth power of it's digits.\n", i, 5);
            sum += i;
        }
    }

    fprintf(stdout, "The sum of the numbers is %ju\n", sum);

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
    fprintf(stdout, "%s <Max number to check.>\n", argv0);
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
