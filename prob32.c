/**
* @file     prob32.c
* @author   Stavros Vagionitis
* @date     08 Mar 2015
* @brief    [Problem 32 in Project Euler](https://projecteuler.net/problem=32)
*           Pandigital products
*           ===================
*           We shall say that an n-digit number is pandigital if it makes use of all
*           the digits 1 to n exactly once; for example, the 5-digit number, 15234, is 1 through 5 pandigital.
*
*           The product 7254 is unusual, as the identity, 39 × 186 = 7254, containing multiplicand, multiplier,
*           and product is 1 through 9 pandigital.
*
*           Find the sum of all products whose multiplicand/multiplier/product identity can be written as a 1 through 9 pandigital.
*           HINT: Some products can be obtained in more than one way so be sure to only include it once in your sum.
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
 * \brief Concatenate three uint64 numbers into one uint64
 *        An example is the following
 *        If the numbers are 12, 345, 6789, then
 *        the concatenated number is 123456789
 *
 * \param   multiplicand    The one number to concatenate
 * \param   multiplier      The second number to concatenate
 * \param   product         The third number to concatenate
 * \return  the concatenated number.
 */
uint64_t concat_numbers(uint64_t multiplicand, uint64_t multiplier, uint64_t product)
{

    uint64_t multiplicand_digits = count_digits(multiplicand);
    uint64_t multiplier_digits = count_digits(multiplier);
    uint64_t product_digits = count_digits(product);


    return product + \
           multiplier * pow1(10, product_digits) + \
           multiplicand * pow1(10, multiplier_digits) * pow1(10, product_digits);
}

/**
 * \brief The solution using a naive way.
 *
 * \param   num  Upper limit for calculating the sum of products.
 * \return  1 if everything is ok, 0 if not.
 */
uint8_t solution1(uint64_t num)
{
    uint64_t sum_prod = 0;

    for (uint64_t i = 1;i<num;i++)
    {
        for (uint64_t j = i;j<num;j++)
        {
            uint64_t product = i * j;
            uint64_t concat_prod = concat_numbers(i, j, product);

            if (count_digits(concat_prod) == 9)
            {
                if (isPandigital(concat_prod))
                {
                    sum_prod += product;
                    fprintf(stdout, "Product: %ju x %ju = %ju (%ju) is pandigital\n", i, j, product, concat_prod);
                }
            }
        }
    }

    fprintf(stdout, "The sum of products whose multiplicand/multiplier/product identity can be written as a 1 through 9 pandigital is %ju.\n", sum_prod);

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
    fprintf(stdout, "%s Upper limit for calculating the sum of products.>\n", argv0);
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
