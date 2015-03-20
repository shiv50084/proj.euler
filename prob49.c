/**
* @file     prob49.c
* @author   Stavros Vagionitis
* @date     20 Mar 2015
* @brief    [Problem 49 in Project Euler](https://projecteuler.net/problem=49)
*           Prime permutations
*           ==================
*           The arithmetic sequence, 1487, 4817, 8147, in which each of the terms increases by 3330,
*           is unusual in two ways: (i) each of the three terms are prime, and, (ii) each of the 4-digit
*           numbers are permutations of one another.
*
*           There are no arithmetic sequences made up of three 1-, 2-, or 3-digit primes, exhibiting this property,
*           but there is one other 4-digit increasing sequence.
*
*           What 12-digit number do you form by concatenating the three terms in this sequence?
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
 * \brief Check if the number is prime
 *
 * \param   num     The number to check if prime
 * \return 1 if it's prime, 0 if not.
 */
uint8_t isPrime(uint64_t num)
{
    if (num < 2)
        return 0;
    else if (num == 2)
        return 1;
    else if (num == 3)
        return 1;
    else if (num == 5)
        return 1;
    else if (num == 7)
        return 1;
    else
    {
        if (isMultiple(num, 2))
            return 0;
        else if (isMultiple(num, 3))
            return 0;
        else if (isMultiple(num, 5))
            return 0;
        else if (isMultiple(num, 7))
            return 0;
        else
        {
            for (uint64_t i = 11;i*i <= num;i+=2)
            {
                if (isMultiple(num, i))
                    return 0;
            }
        }
    }

    return 1;
}

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
 * \brief Swap the digits from two positions
 *        It's a naive approach because this implementation iterates
 *        the number twice
 *              *   once to find the digits
 *              *   second to reconstruct the number with the digits
 *                  swapped
 *
 *        There must be a more efficient way to do that.
 *
 *        TODO Find a more efficient way to swap the digits.
 *
 * \param   num         The number to swap the digits
 * \param   out_num     The number with the digits swapped
 * \param   dpos1       The first position to swap
 * \param   dpos2       The second position to swap
 * \return 1 if everything was ok, 0 if not
 */
uint8_t swap_digits(const uint64_t num, uint64_t *out_num, uint64_t dpos1, uint64_t dpos2)
{
    uint64_t cd = count_digits(num);
    uint64_t n = num;
    // Digits to be swapped.
    uint64_t d1 = 0, d2 = 0;

    // If the position of the digits
    // to swap are larger than the total
    // number of digits then return false.
    // Return false if the positions are zeros
    if (dpos1 > cd-1 || dpos2 > cd-1)
        return 0;

    // Get the digits of the specified
    // positions.
    uint64_t pos = cd-1;
    while(n)
    {
        uint64_t d = n % 10;

        if (dpos1 == pos)
            d1 = d;
        if (dpos2 == pos)
            d2 = d;

        n /= 10;
        pos -= 1;
    }

    // Reconstruct the number with the
    // digits swapped.
    *out_num = 0;
    uint64_t dec = 1;
    n = num;
    pos = cd-1;
    while(n)
    {
        uint64_t d = n % 10;

        if (dpos1 == pos)
            d = d2;
        if (dpos2 == pos)
            d = d1;

        *out_num += (d*dec);

        n /= 10;
        pos -= 1;
        dec *= 10;
    }

    return 1;
}

/**
 * \brief Find all permutations
 *        The algorithm used here can be found in
 *        http://www.quickperm.org/pseudo2.php
 *
 *
 * \param   num     The number to permute
 * \param   perm    An array of permutation of number num
 * \param   perm_sz The size of the array.
 */
uint8_t perm(const uint64_t num, uint64_t **perm, uint64_t *perm_sz)
{
    *perm = NULL;
    *perm_sz = 0;
    uint64_t *tmp = NULL;

    uint64_t n = num;
    uint64_t cd = count_digits(num);
    uint64_t *p = calloc(cd, sizeof(uint64_t));
    if (p == NULL)
    {
        fprintf(stderr, "%s:%d Mem Alloc failed\n", __func__, __LINE__);
        return 0;
    }

    for (uint64_t i = 0;i<cd;i++)
        p[i] = i;


    uint64_t i = 1;
    uint64_t j = 0;
    uint64_t c = 0;

    while(i<cd)
    {
        if (p[i]>0)
        {
            p[i]--;
            j = 0;

            if (i%2 != 0)
                j = p[i];

            swap_digits(n, &n, j, i);

            *perm_sz += 1;
            tmp = realloc(*perm, *perm_sz * sizeof(uint64_t));
            if (tmp != NULL)
            {
                *perm = tmp;
            }
            else
            {
                fprintf(stderr, "%s:%d Mem Alloc failed\n", __func__, __LINE__);

                if (*perm)
                    free(*perm);

                return 0;
            }
            (*perm)[*perm_sz - 1] = n;

            c++;
            i = 1;
        }
        else
        {
            p[i] = i;
            i++;
        }
    }

    if (p)
        free(p);

    return 1;
}

uint8_t isPermutationOf(const uint64_t num1, const uint64_t num2)
{
    uint64_t cd1 = count_digits(num1);
    uint64_t cd2 = count_digits(num2);
    // Counter for all the digits
    uint64_t count_digits[10]={0};

    if (cd1 != cd2)
        return 0;

    uint64_t n1 = num1;
    uint64_t n2 = num2;

    while(n1 && n2)
    {

        // A digit from num1
        uint64_t d1 = n1 % 10;
        if (count_digits[d1])
            count_digits[d1]--;
        else
            count_digits[d1]++;

        // A digit from num2
        uint64_t d2 = n2 % 10;
        if (count_digits[d2])
            count_digits[d2]--;
        else
            count_digits[d2]++;

        n1/=10;
        n2/=10;
    }

    uint64_t sum = 0;
    for (uint64_t i = 0;i<10;i++)
        sum += count_digits[i];

    if (!sum)
        return 1;
    else
        return 0;
}


/**
 * \brief The solution using a naive way.
 *
 * \param   num  Number to do something.
 * \return  1 if everything is ok, 0 if not.
 */
uint8_t solution1(uint64_t num)
{

    for (uint64_t i = 999;i<10000;i++)
        if (isPrime(i))
        {
            fprintf(stdout, "Prime: %ju - ", i);
            uint64_t j = i+3330;
            if (isPrime(j) && isPermutationOf(j, i))
            {
                fprintf(stdout, "%ju - ", j);
                uint64_t k = i+6660;
                if (isPrime(k) && isPermutationOf(k, i))
                {
                    fprintf(stdout, "%ju - ", k);
                }
            }
            fprintf(stdout, "\n");

#if 0
            // Get the permutations of the prime and
            // check which are primes.
            fprintf(stdout, "Prime: %ju - ", i);
            uint64_t *prm = NULL;
            uint64_t sz_prm = 0;

            // Find all the permutations of the prime
            perm(i, &prm, &sz_prm);

            uint64_t prime_count = 0;
            // From the permutations check how many are primes
            for(uint64_t j = 0;j<sz_prm;j++)
            {
                if (isPrime(prm[j]))
                {
                    fprintf(stdout, "%ju ", prm[j]);
                    prime_count++;
                }
            }
            fprintf(stdout, "\n");

            if (prm)
                free(prm);
#endif
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
