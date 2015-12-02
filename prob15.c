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
 * \param   from    The upper limit to calculate the factorial
 * \param   to      The lower limit to calculate the factorial
 * \return  the factorial. If there is a integer overflow,
 *          then returns the UINT64_MAX value and stops the
 *          computation of factorial.
 *
 * How to use:
 *      If you want to calculate the 7! then use it like factorial(7, 1)
 *      If you want to calculate the factorial from 7 to 3, then use it like factorial(7, 2)
 */
uint64_t factorial(uint64_t from, uint64_t to)
{
    uint64_t fact = 1;

    if (to == 0 || to > from)
    {
        fprintf(stderr,"Lower limit is 0 or more than the upper.\n");
        return UINT64_MAX;
    }

    if (from == 0)
        return 1;
    else if (from == 1)
        return 1;
    else
    {
        // To check for integer overflow.
        uint64_t prev_fact = 1;

        // Don't need to multiple with 1.
        for (uint64_t i = from;i>to;i--)
        {
            fact *= i;

            // Check for integer overflow.
            // If there is overflow, then return the max value.
            if (prev_fact > fact)
            {
                fprintf(stderr,"UINT64 overflow for (%ju,%ju)! when multiplying %ju.\n", from, to, i);
                return UINT64_MAX;
            }

            prev_fact = fact;
        }
    }

    return fact;
}

#if 0
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
    uint64_t fact_n = factorial(num, 1);

    if (fact_n == UINT64_MAX)
        return UINT64_MAX;

    uint64_t fact_2n = factorial(2*num, 1);

    if (fact_2n == UINT64_MAX)
        return UINT64_MAX;

    return fact_2n / (fact_n * fact_n);
}
#endif

#if 1
/**
 * \brief Calculate the central binomial coefficient of a number with a more
 *        smarter way
 *
 *        The normal calculation is the following
 *        (2n)
 *        |  | = (2*n)! / (n!)^2 = (2*n)! / n! * n! = n! * (n+1) * (n+2) ... * (2*n) / n! * n! =
 *        ( n)
 *             = (n+1) * (n+2) ... * (2*n) / n!
 *
 *        More info http://en.wikipedia.org/wiki/Central_binomial_coefficient
 *
 *
 * \param   num     The number to calculate the central binomial coefficient
 * \return  the central binomial coefficient. If there is a integer overflow
 *          calculating the factorials, then return UINT64_MAX.
 */
uint64_t central_binomial_coefficient(uint64_t num)
{
    uint64_t fact_n = factorial(num, 1);

    if (fact_n == UINT64_MAX)
        return UINT64_MAX;

    uint64_t fact_2n = factorial(2*num, num);

    if (fact_2n == UINT64_MAX)
        return UINT64_MAX;

    return fact_2n / fact_n;
}
#endif

#if 1
/**
 * \brief The solution using a naive way.
 *
 * \param   num  Number to do something.
 * \return  1 if everything is ok, 0 if not.
 */
uint8_t solution1(uint64_t num)
{

    fprintf(stdout, "Central binomial coefficient of %ju is %ju\n", num, central_binomial_coefficient(num));


    return 1;
}
#endif


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
