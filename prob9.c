/**
* @file     prob9.c
* @author   Stavros Vagionitis
* @date     25 Feb 2015
* @brief    [Problem 9 in Project Euler](https://projecteuler.net/problem=9)
*           Special Pythagorean triplet
*           ===========================
*           A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,
*           a^2 + b^2 = c^2
*
*           For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2.
*
*           There exists exactly one Pythagorean triplet for which a + b + c = 1000.
*           Find the product abc.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef struct pyth_tripl {
    uint64_t a;
    uint64_t b;
    uint64_t c;
}pyth_tripl_t;

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
 * \brief Find the Pythagorian triplets.
 *
 * \param   maxNum          [IN] The max number to calculate the triplets.
 * \param   pyth_tripl      [OUT] An array of type pyth_tripl_t of the triplets.
 * \param   sz_pyth_tripl   [OUT] The size of the triplets.
 * \return 1 if everything ok, 0 if not.
 */
uint8_t findPythTriplets(uint64_t maxNum, pyth_tripl_t **pyth_tripl, uint64_t *sz_pyth_tripl)
{
    *sz_pyth_tripl = 0;
    pyth_tripl_t *tmp = NULL;

    for(uint64_t a = 1;a<maxNum;a++)
    {
        uint64_t ap2 = pow1(a,2);
        for(uint64_t b = a+1;b<maxNum;b++)
        {
            uint64_t bp2 = pow1(b,2);
            for(uint64_t c = b+1;c<maxNum;c++)
            {
                if (ap2+bp2 == pow1(c,2))
                {
                    *sz_pyth_tripl += 1;

                    tmp = realloc(*pyth_tripl, *sz_pyth_tripl * sizeof(pyth_tripl_t));
                    if (tmp != NULL)
                        *pyth_tripl = tmp;
                    else
                    {
                        fprintf(stderr, "%s:%d Mem Alloc failed\n", __func__, __LINE__);

                        if (*pyth_tripl)
                            free(*pyth_tripl);

                        return 0;
                    }

                    (*pyth_tripl)[*sz_pyth_tripl - 1].a = a;
                    (*pyth_tripl)[*sz_pyth_tripl - 1].b = b;
                    (*pyth_tripl)[*sz_pyth_tripl - 1].c = c;
                }
            }
        }
    }

    return 1;
}


/**
 * \brief The solution using a naive way.
 *
 * \param   num  Max number to calculate triplets.
 * \return  1 if everything is ok, 0 if not.
 */
uint8_t solution1(uint64_t num)
{

    pyth_tripl_t *pyth_tripl = NULL;
    uint64_t sz_pyth_tripl = 0;

    findPythTriplets(num, &pyth_tripl, &sz_pyth_tripl);

    for (uint64_t i = 0;i<sz_pyth_tripl;i++)
    {
#if 0
        fprintf(stdout, "Triplets: %ju %ju %ju\n", pyth_tripl[i].a,pyth_tripl[i].b,pyth_tripl[i].c);
#endif

        if (pyth_tripl[i].a + pyth_tripl[i].b + pyth_tripl[i].c == 1000)
        {
            fprintf(stdout, "The product is %ju\n", pyth_tripl[i].a * pyth_tripl[i].b * pyth_tripl[i].c);
            break;
        }
    }

    if (pyth_tripl)
        free(pyth_tripl);

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
    fprintf(stdout, "%s <Max number to calculate triplets.>\n", argv0);
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
