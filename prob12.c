/**
* @file     prob12.c
* @author   Stavros Vagionitis
* @date     27 Feb 2015
* @brief    [Problem 12 in Project Euler](https://projecteuler.net/problem=12)
*           Highly divisible triangular number
*           ==================================
*           The sequence of triangle numbers is generated by adding the natural numbers.
*           So the 7th triangle number would be 1 + 2 + 3 + 4 + 5 + 6 + 7 = 28. The first ten terms would be:
*
*           1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...
*
*           Let us list the factors of the first seven triangle numbers:
*
*           1: 1
*           3: 1,3
*           6: 1,2,3,6
*           10: 1,2,5,10
*           15: 1,3,5,15
*           21: 1,3,7,21
*           28: 1,2,4,7,14,28
*
*           We can see that 28 is the first triangle number to have over five divisors.
*
*           What is the value of the first triangle number to have over five hundred divisors?
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

#if 0
/**
 * \brief Find the n-th triangle number using the naive way.
 *
 * \param   nth    The nth number to calulate the triangle.
 * \return  the nth triangle number.
 */
uint64_t findNthTriangle(uint64_t nth)
{
    uint64_t sum = 0;

    for (uint64_t i = 1;i<=nth;i++)
        sum+=i;

    return sum;
}
#endif

/**
 * \brief Find the n-th triangle number using the formula
 *
 *        f(n) = n*(n+1)/2
 *
 *        http://en.wikipedia.org/wiki/Triangular_number
 *
 * \param   nth    The nth number to calulate the triangle.
 * \return  the nth triangle number.
 */
uint64_t findNthTriangle(uint64_t nth)
{
    return (nth * (nth + 1)) / 2;
}

/**
 * \brief Find the divisors of a number. For example
 *
 *        28: 1,2,4,7,14,28
 *
 * \param   num         [IN] The number to find the divisors.
 * \param   divisors    [OUT] The divisors.
 * \param   sz_divisors [OUT] The total number of divisors.
 * \return  1 if everything is ok, 0 if not
 */
uint8_t findDivisors(uint64_t num, uint64_t **divisors, uint64_t *sz_divisors)
{
    uint64_t *tmp = NULL;
    *sz_divisors = 0;

    for (uint64_t i = 1;i<=num;i++)
    {
        if (isMultiple(num, i))
        {
            *sz_divisors += 1;

            tmp = realloc(*divisors, *sz_divisors * sizeof(uint64_t));
            if (tmp != NULL)
                *divisors = tmp;
            else
            {
                fprintf(stderr, "%s:%d Mem Alloc failed\n", __func__, __LINE__);

                if (*divisors)
                    free(*divisors);

                return 0;
            }

            (*divisors)[*sz_divisors - 1] = i;

        }
    }

    return 1;
}

/**
 * \brief The solution using a naive way.
 *
 * \param   num  The upper limit to calculate the triangle numbers.
 * \return  1 if everything is ok, 0 if not.
 */
uint8_t solution1(uint64_t num)
{

    for (uint64_t i = 1;i<=num;i++)
    {
        // Get the triangle number
        uint64_t triangle = findNthTriangle(i);

        uint64_t *triangle_divisors = NULL;
        uint64_t sz_triangle_divisors = 0;

        // Find the divisors of the triangle
        findDivisors(triangle, &triangle_divisors, &sz_triangle_divisors);

        if (sz_triangle_divisors > 500)
        {
            fprintf(stdout, "Triangle number %ju has over 500 divisors.\n", triangle);
            break;
        }
#if 0
        fprintf(stdout, "%ju: ", triangle);
        for (uint64_t j = 0;j<sz_triangle_divisors;j++)
        {
            if (j != sz_triangle_divisors - 1)
                fprintf(stdout, "%ju ", triangle_divisors[j]);
            else
                fprintf(stdout, "%ju\n", triangle_divisors[j]);
        }
#endif

        if (triangle_divisors)
            free(triangle_divisors);
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
    fprintf(stdout, "%s <Upper limit for the triangle numbers.>\n", argv0);
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
