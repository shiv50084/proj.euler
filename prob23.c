/**
* @file     prob23.c
* @author   Stavros Vagionitis
* @date     xx Mar 2015
* @brief    [Problem 23 in Project Euler](https://projecteuler.net/problem=23)
*           Non-abundant sums
*           =================
*           A perfect number is a number for which the sum of its proper divisors
*           is exactly equal to the number. For example, the sum of the proper divisors
*           of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.
*
*           A number n is called deficient if the sum of its proper divisors is less than n and
*           it is called abundant if this sum exceeds n.
*
*           As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number that
*           can be written as the sum of two abundant numbers is 24. By mathematical analysis, it can
*           be shown that all integers greater than 28123 can be written as the sum of two abundant numbers.
*           However, this upper limit cannot be reduced any further by analysis even though it is known that
*           the greatest number that cannot be expressed as the sum of two abundant numbers is less than this limit.
*
*           Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.
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
 * \brief Find the divisors of a number. For example
 *
 *        28: 1,2,4,7,14
 *
 *        See more info of several implementations in
 *        http://www.mathblog.dk/uva-294-divisors/
 *
 * \param   num         [IN] The number to find the divisors.
 * \param   divisors    [OUT] The divisors.
 * \param   sz_divisors [OUT] The total number of divisors.
 * \return  1 if everything is ok, 0 if not.
 */
uint8_t findDivisors(uint64_t num, uint64_t **divisors, uint64_t *sz_divisors)
{
    uint64_t *tmp = NULL;
    *sz_divisors = 0;

    for (uint64_t i = 1;i*i<=num;i++)
    {
        if (isMultiple(num, i))
        {
            if (i == 1 || num == i*i)
                *sz_divisors += 1;
            else
                *sz_divisors += 2;

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
            if (i > 1 && num != i*i)
                (*divisors)[*sz_divisors - 2] = num/i;

        }
    }

#if 0
    // For debugging
    fprintf(stdout, "%ju: ", num);
    for (uint64_t i = 0;i<*sz_divisors;i++)
        fprintf(stdout, "%ju ", (*divisors)[i]);
    fprintf(stdout, "\n");
#endif

    return 1;
}

/**
 * \brief Add the elements of an array
 *
 * \param   arr     The array of which the elements will
 *                  be added.
 * \param   sz      The size of the array.
 * \return  the sum of the elements of the array.
 */
uint64_t sum_array(uint64_t arr[], uint64_t sz)
{
    uint64_t sum = 0;

    for(uint64_t i = 0;i<sz;i++)
        sum += arr[i];

    return sum;
}

/**
 * \brief Check if a number is perfect
 *        A perfect number is a number for which the sum of
 *        its proper divisors is exactly equal to the number.
 *        See http://en.wikipedia.org/wiki/Perfect_number for
 *        more info
 *
 * \param   num     The number to check
 * \return  1 if it's perfect, 0 otherwise.
 */
uint8_t isPerfect(uint64_t num)
{
    uint64_t *div = NULL;
    uint64_t div_sz = 0;

    findDivisors(num, &div, &div_sz);

    // Calculate the sum of the divisors
    uint64_t sum_div = sum_array(div, div_sz);

    // Free and initialize the divisors array
    if (div)
        free(div);

    if (sum_div == num)
        return 1;
    else
        return 0;
}

/**
 * \brief Check if a number is deficient
 *        A deficient number is a number for which the sum of
 *        its proper divisors is less than the number.
 *        See http://en.wikipedia.org/wiki/Deficient_number for
 *        more info
 *
 * \param   num     The number to check
 * \return  1 if it's deficient, 0 otherwise.
 */
uint8_t isDeficient(uint64_t num)
{
    uint64_t *div = NULL;
    uint64_t div_sz = 0;

    findDivisors(num, &div, &div_sz);

    // Calculate the sum of the divisors
    uint64_t sum_div = sum_array(div, div_sz);

    // Free and initialize the divisors array
    if (div)
        free(div);

    if (sum_div < num)
        return 1;
    else
        return 0;
}

/**
 * \brief Check if a number is abundant
 *        An abuntant number is a number for which the sum of
 *        its proper divisors is greater than the number.
 *        See http://en.wikipedia.org/wiki/Abundant_number for
 *        more info
 *
 * \param   num     The number to check
 * \return  1 if it's abuntant, 0 otherwise.
 */
uint8_t isAbundant(uint64_t num)
{
    uint64_t *div = NULL;
    uint64_t div_sz = 0;

    findDivisors(num, &div, &div_sz);

    // Calculate the sum of the divisors
    uint64_t sum_div = sum_array(div, div_sz);

    // Free and initialize the divisors array
    if (div)
        free(div);

    if (sum_div > num)
        return 1;
    else
        return 0;
}

/**
 * \brief The solution using a naive way.
 *        TODO Find an efficient way to calculate
 *             quickly the sum
 *
 * \param   num  Number to do something.
 * \return  1 if everything is ok, 0 if not.
 */
uint8_t solution1(uint64_t num)
{
    uint64_t c = 0;
    uint64_t sum = 0;
    for (uint64_t a = 1;a<=num;a++)
    {
        uint8_t isSumAbundant = 0;
        for (uint64_t i = 1;i<=a;i++)
        {
            if (isAbundant(i))
            {
                for (uint64_t j = i;j<=a;j++)
                {
                    if (isAbundant(j))
                    {
                        if (a == i+j)
                        {
#if 1
                            fprintf(stdout, "%ju. %ju + %ju = %ju\n", c, i, j, a);
#endif
                            c++;
                            isSumAbundant = 1;
                            break;
                        }
                        else
                        {
                            isSumAbundant = 0;
                        }
                    }
                }
            }

            if (isSumAbundant)
                break;
        }

        if (!isSumAbundant)
        {
#if 0
            fprintf(stdout, "%ju\n", a);
#endif
            isSumAbundant = 0;
            sum += a;
        }
    }

    fprintf(stdout, "Sum of all the positive integers which cannot be written as the sum of two abundant numbers is %ju.\n", sum);

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
