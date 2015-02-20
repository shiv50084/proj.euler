/**
* @file     prob3.c
* @author   Stavros Vagionitis
* @date     20 Feb 2015
* @brief    [Problem 3 in Project Euler](https://projecteuler.net/problem=3)
*           Largest prime factor
*           ====================
*           The prime factors of 13195 are 5, 7, 13 and 29.
*           What is the largest prime factor of the number 600851475143 ?
*/

#include <stdlib.h>
#include <stdio.h>

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

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
 * \brief Check if the number is prime
 *
 * \param   num     The number to check if prime
 * \return 1 if it's prime, 0 if not.
 */
uint8_t isPrime(uint64_t num)
{
    for (uint64_t i = 2;i < num;i++)
    {
        if (isMultiple(num, i))
            return 0;
    }

    return 1;
}


/**
 * \brief Find the prime factors of a number
 *        (using a modified algorithm from
 *        http://www.geeksforgeeks.org/print-all-prime-factors-of-a-given-number/)
 *
 * \param   num             [IN] The number to find the prime factors.
 * \param   prim_fact       [OUT] The prime factors found.
 * \param   sz_prim_fact    [OUT] The size of the prime factors.
 * \return 1 if everything ok, 0 if not.
 */
uint8_t findPrimeFactors(const uint64_t num, uint64_t **prim_fact, uint64_t *sz_prim_fact)
{
    uint64_t n = num;
    uint64_t *tmp = NULL;

    *sz_prim_fact = 0;


    // Even numbers
    if (isMultiple(n,2))
    {
        while(isMultiple(n, 2))
        {
            *sz_prim_fact += 1;

            tmp = realloc(*prim_fact, *sz_prim_fact * sizeof(uint64_t));
            if (tmp != NULL)
                *prim_fact = tmp;
            else
            {
                fprintf(stderr, "%s:%d Mem Alloc failed\n", __func__, __LINE__);

                if (*prim_fact)
                    free(*prim_fact);

                return 0;
            }

            (*prim_fact)[*sz_prim_fact - 1] = 2;

            n/=2;
        }
    }
    // Odd numbers
    else
    {
        for(uint64_t i = 3;i*i<=n;i+=2)
        {
            while(isMultiple(n, i))
            {
                *sz_prim_fact += 1;

                tmp = realloc(*prim_fact, *sz_prim_fact * sizeof(uint64_t));
                if (tmp != NULL)
                    *prim_fact = tmp;
                else
                {
                    fprintf(stderr, "%s:%d Mem Alloc failed\n", __func__, __LINE__);

                    if (*prim_fact)
                        free(*prim_fact);

                    return 0;
                }

                (*prim_fact)[*sz_prim_fact - 1] = i;

                n/=i;
            }
        }
    }

    // If the remaining number n is prime,
    // then add it to the prime factors
    if (n>2)
    {
        *sz_prim_fact += 1;

        tmp = realloc(*prim_fact, *sz_prim_fact * sizeof(uint64_t));
        if (tmp != NULL)
            *prim_fact = tmp;
        else
        {
            fprintf(stderr, "%s:%d Mem Alloc failed\n", __func__, __LINE__);

            if (*prim_fact)
                free(*prim_fact);

            return 0;
        }

        (*prim_fact)[*sz_prim_fact - 1] = n;
    }

    return 1;
}


/**
 * \brief The solution using a naive way.
 *
 * \param   num     The number to check for largest prime factor
 * \return  1 if everything is ok, 0 if not.
 */
uint8_t solution1(uint64_t num)
{

    uint64_t *prm_fct = NULL;
    uint64_t sz_prm_fct = 0;
    uint64_t max_prm_fct = 0;

    findPrimeFactors(num, &prm_fct, &sz_prm_fct);

    for(uint64_t i = 0;i<sz_prm_fct;i++)
        max_prm_fct = max(prm_fct[i], 0);

    fprintf(stdout, "Max prime factor: %u\n", max_prm_fct);

    if (prm_fct)
        free(prm_fct);
}

/**
 * \brief Usage of this program.
 *
 * \param   argv0   The first argument string which is the current executable.
 * \return  -1.
 */
int usage(char *argv0)
{
    fprintf(stdout, "%s <Number to check for largest prime factor.>\n", argv0);
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
