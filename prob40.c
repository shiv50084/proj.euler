/**
* @file     prob40.c
* @author   Stavros Vagionitis
* @date     22 Mar 2015
* @brief    [Problem 40 in Project Euler](https://projecteuler.net/problem=40)
*           Champernowne's constant
*           =======================
*           An irrational decimal fraction is created by concatenating the positive integers:
*
*           0.12345678910*1*112131415161718192021...
*
*           It can be seen that the 12th digit of the fractional part is 1.
*
*           If dn represents the nth digit of the fractional part, find the value of the following expression.
*
*           d1 × d10 × d100 × d1000 × d10000 × d100000 × d1000000
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
 * \brief Generate the Champernowne's constant
 *        See http://en.wikipedia.org/wiki/Champernowne_constant
 *        for more info
 *
 * \param   sz              The size of the constant
 * \param   champernowne    The array of the digits of the constant
 * \return  1 if everything is ok, 0 if not
 */
uint8_t genChampernowneConstant(uint64_t sz, uint8_t **champernowne)
{
    *champernowne = calloc(sz, sizeof(uint8_t));
    if (*champernowne == NULL)
    {
        fprintf(stderr, "%s:%d Mem Alloc failed\n", __func__, __LINE__);
        return 0;
    }

    // The index in the constant's array.
    uint64_t j = 0;
    for (uint64_t i = 1;i<=UINT64_MAX;i++)
    {
        uint64_t n = i;
        uint64_t sz_i = count_digits(i);
        uint8_t sz_full = 0;

        while(n)
        {
            uint64_t sz_n = count_digits(n);
            uint8_t d = n % 10;

            if (j>sz-1)
            {
                sz_full = 1;
                break;
            }

            // The digits are gathered from right
            // to left, so need to reverse in the
            // array.
            (*champernowne)[j+(sz_n-1)] = d;

            n/=10;
        }
        j+=sz_i;

        if (sz_full)
            break;
    }

    return 1;
}

/**
 * \brief The solution using a naive way.
 *
 * \param   num  The size of the constant.
 * \return  1 if everything is ok, 0 if not.
 */
uint8_t solution1(uint64_t num)
{
    uint8_t *cc = NULL;

    genChampernowneConstant(num, &cc);

#if 0
    for (uint64_t i = 0;i<num;i++)
        fprintf(stdout, "%u", cc[i]);
    fprintf(stdout, "\n");
#endif

    fprintf(stdout, "d1:%u × d10:%u × d100:%u × d1000:%u × d10000:%u × d100000:%u × d1000000:%u = %ju\n", cc[0], cc[9], cc[99],
                                                                                                        cc[999], cc[9999], cc[99999], cc[999999],
                                                                                                        cc[0] * cc[9] * cc[99] * cc[999] * cc[9999] * cc[99999] * cc[999999]);
    if (cc)
        free(cc);

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
    fprintf(stdout, "%s <The size of the constant>\n", argv0);
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
