/**
* @file     prob38.c
* @author   Stavros Vagionitis
* @date     26 Mar 2015
* @brief    [Problem 38 in Project Euler](https://projecteuler.net/problem=38)
*           Pandigital multiples
*           ====================
*           Take the number 192 and multiply it by each of 1, 2, and 3:
*
*           192 × 1 = 192
*           192 × 2 = 384
*           192 × 3 = 576
*
*           By concatenating each product we get the 1 to 9 pandigital, 192384576.
*           We will call 192384576 the concatenated product of 192 and (1,2,3)
*
*           The same can be achieved by starting with 9 and multiplying by 1, 2, 3, 4, and 5,
*           giving the pandigital, 918273645, which is the concatenated product of 9 and (1,2,3,4,5).
*
*           What is the largest 1 to 9 pandigital 9-digit number that can be formed as the concatenated
*           product of an integer with (1,2, ... , n) where n > 1?
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
 * \param   digits  The digits that the number should have
 * \return 1 if it's pandigital, 0 if not.
 */
uint8_t isPandigitalDigit(const uint64_t num, uint64_t digits)
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

    if (digits == cnt_digits)
        return 1;
    else
        return 0;
}

/**
 * \brief The solution using a naive way.
 *
 * \param   num  Max number to look for pandigital
 * \return  1 if everything is ok, 0 if not.
 */
uint8_t solution1(uint64_t num)
{

    for (uint64_t i = 1;i<num;i++)
    {
        uint64_t concatenated_prod = 0;
        uint64_t pow = 1;

        if (count_digits(i) == 9)
            break;

        for (uint64_t j = 1;j<i;j++)
        {
            uint64_t prod = i * j;
            uint64_t cnt_digits_prod = count_digits(prod);

            if (j > 1)
                pow = pow1(10, cnt_digits_prod);

            concatenated_prod *= pow;
            concatenated_prod += prod;

            if (count_digits(concatenated_prod) > 9)
                break;
            else if (count_digits(concatenated_prod) == 9)
            {
                if (isPandigitalDigit(concatenated_prod, 9))
                {
                    fprintf(stdout, "i: %ju j: %ju concatenated_prod: %ju\n", i, j, concatenated_prod);
                    break;
                }
            }
        }
#if 0
        // Concatenate in reverse the numbers
        for (uint64_t j = 1;j<5;j++)
        {
            uint64_t prod = i * j;
            uint64_t cnt_digits_prod = count_digits(prod);

            if (j > 1)
                pow *= pow1(10, cnt_digits_prod);

            concatenated_prod += prod * pow;

            fprintf(stdout, "i: %ju j: %ju prod: %ju concatenated_prod: %ju\n", i, j, prod, concatenated_prod);
        }
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
    fprintf(stdout, "%s <Max number to look for pandigital>\n", argv0);
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
