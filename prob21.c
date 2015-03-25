/**
* @file     prob21.c
* @author   Stavros Vagionitis
* @date     20 Mar 2015
* @brief    [Problem 21 in Project Euler](https://projecteuler.net/problem=21)
*           Amicable numbers
*           ================
*           Let d(n) be defined as the sum of proper divisors of n (numbers less than
*           n which divide evenly into n). If d(a) = b and d(b) = a, where a ≠ b, then a and b
*           are an amicable pair and each of a and b are called amicable numbers.
*
*           For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110;
*           therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.
*
*           Evaluate the sum of all the amicable numbers under 10000.
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
 * \param   num         [IN] The number to find the divisors.
 * \param   divisors    [OUT] The divisors.
 * \param   sz_divisors [OUT] The total number of divisors.
 * \return  1 if everything is ok, 0 if not.
 */
uint8_t findDivisors(uint64_t num, uint64_t **divisors, uint64_t *sz_divisors)
{
    uint64_t *tmp = NULL;
    *sz_divisors = 0;

    for (uint64_t i = 1;i<=num/2;i++)
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
 * \brief Check if a number is amicable.
 *        See http://en.wikipedia.org/wiki/Amicable_numbers for more info.
 *
 * \param   arr     The array of which the elements will
 *                  be added.
 * \param   sz      The size of the array.
 * \return  the sum of the elements of the array.
 */
uint8_t isAmicable(uint64_t num)
{
    uint64_t *div = NULL;
    uint64_t div_sz = 0;

    findDivisors(num, &div, &div_sz);

    // Calculate the sum of the divisors
    uint64_t sum_div = sum_array(div, div_sz);

    // Free and initialize the divisors array
    if (div)
        free(div);

    div = NULL;
    div_sz = 0;

    // Find the divisors of the sum of divisors.
    findDivisors(sum_div, &div, &div_sz);

    // Calculate the sum
    uint64_t sum_sum_div = sum_array(div, div_sz);

    if (div)
        free(div);

    if (num != sum_div && sum_sum_div == num)
    {
#if 0
        fprintf(stdout, "d(%ju)=%ju and d(%ju)=%ju\n", num, sum_div, sum_div, sum_sum_div);
#endif
        return 1;
    }
    else
        return 0;

}

/**
 * \brief The solution using a naive way.
 *
 * \param   num  The upper limit to calculate the
 *               sum of amicables.
 * \return  1 if everything is ok, 0 if not.
 */
uint8_t solution1(uint64_t num)
{
    uint64_t sum_amicable = 0;

    for (uint64_t i = 0;i<num;i++)
        if (isAmicable(i))
            sum_amicable += i;

    fprintf(stdout, "Sum of amicables under %ju is %ju\n", num, sum_amicable);

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
    fprintf(stdout, "%s <The upper limit to calculate the sum of amicables.>\n", argv0);
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
