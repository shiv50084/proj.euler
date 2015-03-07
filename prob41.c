/**
* @file     prob41.c
* @author   Stavros Vagionitis
* @date     07 Mar 2015
* @brief    [Problem 41 in Project Euler](https://projecteuler.net/problem=41)
*           Pandigital prime
*           ================
*           We shall say that an n-digit number is pandigital if it makes use of all
*           the digits 1 to n exactly once. For example, 2143 is a 4-digit pandigital
*           and is also prime.
*
*           What is the largest n-digit pandigital prime that exists?
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
 * \brief Checks if a number is pandigital.
 *        An n-digit number is pandigital if it makes
 *        use of all the digits 1 to n exactly once.
 *        For example, the following numbers are pandigital
 *
 *        12 is a 2-digit
 *        312 is a 3-digit
 *        4312 is a 4-digit
 *        54123 is a 5-digit
 *
 * \param   num     The number to check.
 * \return 1 if it's pandigital, 0 if not.
 */
uint8_t isPandigital(const uint64_t num)
{
    uint64_t n = num;

    // An array that holds the count of digits
    uint64_t count[10] = {0};

    uint64_t cnt_digits = count_digits(num);

    while(n)
    {
        uint64_t d = n % 10;

        // If the digit is 0
        // then it's not a pandigital.
        // It should >= 1
        if (d == 0)
            return 0;

        // If the digit is larger than
        // the number of digits of the
        // number, then it's not pandigital.
        if (d > cnt_digits)
            return 0;

        count[d] += 1;

        if (count[d] > 1)
            return 0;

        n/=10;
    }

    return 1;
}

/**
 * \brief The solution using a naive way.
 *
 * \param   num  Upper limit to check for pandigital primes.
 * \return  1 if everything is ok, 0 if not.
 */
uint8_t solution1(uint64_t num)
{

    for (uint64_t i = 0;i<num;i++)
    {
        if (isPandigital(i) && isPrime(i))
            fprintf(stdout, "%ju is a pandigital prime.\n", i);
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
    fprintf(stdout, "%s <Upper limit to check for pandigital primes.>\n", argv0);
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
