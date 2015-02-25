/**
* @file     prob10.c
* @author   Stavros Vagionitis
* @date     25 Feb 2015
* @brief    [Problem 10 in Project Euler](https://projecteuler.net/problem=10)
*           Summation of primes
*           ===================
*           The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
*
*           Find the sum of all the primes below two million.
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
 * \brief The solution using a naive way.
 *
 * \param   num  Upper limit in order to calculate the sum of primes.
 * \return  1 if everything is ok, 0 if not.
 */
uint8_t solution1(uint64_t num)
{
    uint64_t sum = 0;
    for(uint64_t i = 0;i<num;i++)
    {
        if (isPrime(i))
            sum+=i;
    }

    fprintf(stdout, "The sum of all primes below %ju is %ju\n", num, sum);

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
    fprintf(stdout, "%s <Upper limit in order to calculate the sum of primes.>\n", argv0);
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
