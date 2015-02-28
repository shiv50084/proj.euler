/**
* @file     prob15.c
* @author   Stavros Vagionitis
* @date     xx Feb 2015
* @brief    [Problem 15 in Project Euler](https://projecteuler.net/problem=15)
*           Lattice paths
*           =============
*           Starting in the top left corner of a 2×2 grid, and only being able to move to the right and down, there are exactly 6 routes to the bottom right corner.
*
*
*            >> >>       >> __       >> __
*           |  |  v     |  v  |     |  v  |
*           |__|__v     |__v>>v     |__v__|
*           |  |  v     |  |  v     |  v  |
*           |__|__v     |__|__v     |__v>>>
*
*            __ __       __ __       __ __
*           v  |  |     v  |  |     v  |  |
*           v>>>>>>     v>>>__|     v__|__|
*           |  |  v     |  v  |     v  |  |
*           |__|__v     |__v>>>     v>>>>>>
*
*
*           How many such routes are there through a 20×20 grid?
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
 * \brief Calculate the central binomial coefficient of a number
 *
 *        (2n)
 *        |  | = (2*n)! / (n!)^2
 *        ( n)
 *
 *        More info http://en.wikipedia.org/wiki/Central_binomial_coefficient
 *
 * \param   num     The number to calculate the central binomial coefficient
 * \return  the central binomial coefficient. If there is a integer overflow
 *          calculating the factorials, then return UINT64_MAX.
 */
uint64_t central_binomial_coefficient(uint64_t num)
{
    uint64_t fact_n = factorial(num);

    if (fact_n == UINT64_MAX)
        return UINT64_MAX;

    uint64_t fact_2n = factorial(2*num);

    if (fact_2n == UINT64_MAX)
        return UINT64_MAX;

    return fact_2n / (fact_n * fact_n);
}

/**
 * \brief The solution using a naive way.
 *
 * \param   num  Number to do something.
 * \return  1 if everything is ok, 0 if not.
 */
uint8_t solution1(uint64_t num)
{

    for (uint64_t i = 0;i<num;i++)
    {
        fprintf(stdout, "%ju! = %ju\n", i, factorial(i));
    }

    fprintf(stdout, "Central binomial coefficient of %ju is %ju\n", num, central_binomial_coefficient(num));


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
