/**
* @file     prob4.c
* @author   Stavros Vagionitis
* @date     24 Feb 2015
* @brief    [Problem 4 in Project Euler](https://projecteuler.net/problem=4)
*           Largest palindrome product
*           ==========================
*           A palindromic number reads the same both ways. The largest palindrome
*           made from the product of two 2-digit numbers is 9009 = 91 × 99.
*
*           Find the largest palindrome made from the product of two 3-digit numbers.
*
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

/**
 * \brief Check if the number is palindrome.
 *
 * \param   num     The number to check if it's palindrome.
 * \return  1 if it's palindrome, 0 if not.
 */
uint8_t isPalindrome(const uint64_t num)
{
    uint64_t n = num;
    uint64_t count_digits = 0;
    uint8_t *numb = NULL;
    uint8_t *tmp = NULL;

    // Save digits of the number in
    // an array.
    while(n)
    {
        count_digits++;

        tmp = realloc(numb, count_digits * sizeof(uint8_t));
        if (tmp != NULL)
            numb = tmp;
        else
        {
            fprintf(stderr, "%s:%d Mem Alloc failed\n", __func__, __LINE__);

            if (numb)
                free(numb);

            return 0;
        }

        numb[count_digits-1] = n%10;

        n/=10;
    }

    for(uint64_t i = 0;i<=count_digits/2;i++)
        if (numb[i] != numb[count_digits - 1 - i])
            return 0;

    if(numb)
        free(numb);

    return 1;
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
    else
    {
        for(uint64_t i = 0;i<exp;i++)
            t*=base;
    }

    return t;
}

/**
 * \brief The solution using a naive way.
 *
 * \param   num  The number of digits
 * \return  1 if everything is ok, 0 if not.
 */
uint8_t solution1(uint64_t num)
{
    uint64_t maxPalindrome = 0;

    for(uint64_t i = pow1(10,num)-1;i>=pow1(10,num-1);i--)
        for(uint64_t j = pow1(10,num)-1;j>=pow1(10,num-1);j--)
        {
            if(isPalindrome(i*j))
                maxPalindrome = max(i*j, maxPalindrome);
        }

    fprintf(stdout, "Max palindrome is %ju\n", maxPalindrome);
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
    fprintf(stdout, "%s <Number of digits.>\n", argv0);
    return -1;
}


int main(int argc, char *argv[])
{
    if (argc != 2)
        return usage(argv[0]);

    // Number of digits
    uint64_t num = strtoull(argv[1], NULL, 10);

    solution1(num);

    return 0;
}
