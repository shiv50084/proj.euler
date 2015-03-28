/**
* @file     prob37.c
* @author   Stavros Vagionitis
* @date     28 Mar 2015
* @brief    [Problem 37 in Project Euler](https://projecteuler.net/problem=37)
*           Truncatable primes
*           ==================
*           The number 3797 has an interesting property. Being prime itself, it is possible
*           to continuously remove digits from left to right, and remain prime at each stage:
*           3797, 797, 97, and 7. Similarly we can work from right to left: 3797, 379, 37, and 3.
*
*           Find the sum of the only eleven primes that are both truncatable from left to right and right to left.
*
*           NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.
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
    else if (exp == 1)
        return base;
    else if (exp == 2)
        return base * base;
    else
    {
        for(uint64_t i = 0;i<exp;i++)
            t*=base;
    }

    return t;
}

/**
 * \brief Check if a number is truncatable prime
 *        See http://en.wikipedia.org/wiki/Truncatable_prime
 *        for more info
 *
 * \param   num    The number to check
 * \return  1 if truncatable prime, 0 otherwise.
 */
uint8_t isTruncatablePrime(const uint64_t num)
{
    uint64_t cd = count_digits(num);
    uint64_t n_left2right = num;
    uint64_t n_right2left = num;
    uint64_t counter = 0;


    if (isPrime(num))
    {
        // One digit primes are not
        // truncatable
        if (cd == 1)
            return 0;

        uint64_t dec = pow1(10, cd-1);
        while(n_right2left || n_left2right)
        {
#if 0
            fprintf(stdout, "n_right2left = %ju n_left2right = %ju\n", n_right2left, n_left2right);
#endif
            n_right2left /= 10;

            if (isPrime(n_right2left))
                counter++;

            // Get the most left digit
            uint64_t d = n_left2right / dec;
            n_left2right -= d*dec;
            dec /=10;

            if (isPrime(n_left2right))
                counter++;
        }
    }
    else
        return 0;


    if (counter == 2 * cd - 2)
        return 1;
    else
        return 0;
}

/**
 * \brief The solution using a naive way.
 *
 * \param   num  Max number to check
 * \return  1 if everything is ok, 0 if not.
 */
uint8_t solution1(uint64_t num)
{
    uint64_t sum = 0;
    uint64_t c = 0;

    for (uint64_t i = 1;i<num;i++)
        if (isTruncatablePrime(i))
        {
            fprintf(stdout, "%ju. Truncatable prime: %ju\n", c, i);
            sum += i;
            c++;
        }

    fprintf(stdout, "The sum of %ju truncatable primes is %ju\n", c, sum);

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
    fprintf(stdout, "%s <Max number to check.>\n", argv0);
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
