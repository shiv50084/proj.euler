/**
* @file     prob7.c
* @author   Stavros Vagionitis
* @date     24 Feb 2015
* @brief    [Problem 7 in Project Euler](https://projecteuler.net/problem=7)
*           10001st prime
*           =============
*           By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.
*
*           What is the 10001st prime number?
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
 * \brief Find nth prime number
 *
 * \param   nth     The nth value.
 * \return the nth prime number.
 */
uint64_t findNthPrime(uint64_t nth)
{
    uint64_t i = 0;
    uint64_t count_prime = 0;

    while(1)
    {
        if (isPrime(i))
            count_prime++;

        if (count_prime == nth)
            break;
        else
            i++;
    }

    return i;
}

/**
 * \brief The solution using a naive way.
 *
 * \param   num  The nth value.
 * \return  1 if everything is ok, 0 if not.
 */
uint8_t solution1(uint64_t num)
{

    fprintf(stdout, "Find %ju-th prime: %ju\n", num, findNthPrime(num));

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
    fprintf(stdout, "%s <Nth value>\n", argv0);
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
