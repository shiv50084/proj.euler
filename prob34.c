/**
* @file     prob34.c
* @author   Stavros Vagionitis
* @date     07 Mar 2015
* @brief    [Problem 34 in Project Euler](https://projecteuler.net/problem=34)
*           Digit factorials
*           ====================
*           145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.
*
*           Find the sum of all numbers which are equal to the sum of the factorial of their digits.
*
*           Note: as 1! = 1 and 2! = 2 are not sums they are not included.
*
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

/**
 * \brief Calculate the factorial of a number
 *
 *        n! = n*n-1*...*3*2*1
 *        5! = 5*4*3*2*1
 *
 *        The value 20! is the largest factorial that
 *        can be stored in a 64-bit number.
 *
 *        More info here http://en.wikipedia.org/wiki/Factorial
 *
 * \param   num     The number to calculate the factorial
 * \return  the factorial. If there is a integer overflow,
 *          then returns the UINT64_MAX value and stops the
 *          computation of factorial.
 */
uint64_t factorial(uint64_t num)
{
    uint64_t fact = 1;

    if (num == 0)
        return 1;
    else if (num == 1)
        return 1;
    else
    {
        // To check for integer overflow.
        uint64_t prev_fact = 1;

        // Don't need to multiple with 1.
        for (uint64_t i = num;i>1;i--)
        {
            fact *= i;

            // Check for integer overflow.
            // If there is overflow, then return the max value.
            if (prev_fact > fact)
            {
                fprintf(stderr,"UINT64 overflow for %ju! when multiplying %ju.\n", num, i);
                return UINT64_MAX;
            }

            prev_fact = fact;
        }
    }

    return fact;
}

/**
 * \brief Check if a number is a curious number
 *        Curious number is the one the he is equal
 *        with the sum of the factorials of each digits.
 *
 *        E.g 145 is curious because
 *
 *         1! + 4! + 5! = 1 + 24 + 120 = 145
 *
 *        Note: 1! = 1 and 2! = 2 are not sums, so
 *        they are not included.
 *
 * \param   num     The number to check if it's curious
 * \return  1 if it's curious, 0 if not.
 */
uint8_t isCuriousNumber(const uint64_t num)
{
    uint64_t n = num;
    uint64_t sum_fact_dig = 0;

    // 1! = 1 and 2! = 2 are not sums,
    // so they are not included.
    if (num == 0 || num == 1 || num == 2)
        return 0;

    while(n)
    {
        uint64_t dig = n % 10;

        sum_fact_dig += factorial(dig);

        n/=10;
    }

    // If the sum is equal to the number
    // then it's a curious number
    if (num == sum_fact_dig)
        return 1;
    else
        return 0;

}

/**
 * \brief The solution using a naive way.
 *
 * \param   num  Upper limit to calculate the sum of curious.
 * \return  1 if everything is ok, 0 if not.
 */
uint8_t solution1(uint64_t num)
{

    uint64_t sum_curious = 0;

    for (uint64_t i = 0;i<num;i++)
    {
        if (isCuriousNumber(i))
        {
            fprintf(stdout, "Curious number: %ju\n", i);
            sum_curious += i;
        }
    }

    fprintf(stdout, "The sum of the curious numbers, with upper limit %ju, is %ju\n", num, sum_curious);

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
    fprintf(stdout, "%s <Upper limit to calculate the sum of curious.>\n", argv0);
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
