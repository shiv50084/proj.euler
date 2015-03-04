#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

typedef struct bnum
{
    uint64_t sz_num;
    uint8_t *num;
}bnum_t;


bnum_t max_sz_bnum(const bnum_t bn1, const bnum_t bn2)
{
    if (bn1.sz_num >= bn2.sz_num)
        return bn1;
    else
        return bn2;
}

bnum_t min_sz_bnum(const bnum_t bn1, const bnum_t bn2)
{
    if (bn1.sz_num <= bn2.sz_num)
        return bn1;
    else
        return bn2;
}

uint64_t count_digits(uint64_t n)
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

uint8_t reverse_bnum(bnum_t *bn)
{
    if (bn == NULL)
    {
        fprintf(stderr, "%s:%d Input value is NULL\n", __func__, __LINE__);
        return 0;
    }

    for (uint64_t i = 0;i<bn->sz_num / 2;i++)
    {
        bn->num[i] ^= bn->num[bn->sz_num - 1 - i];
        bn->num[bn->sz_num - 1 - i] ^= bn->num[i];
        bn->num[i] ^= bn->num[bn->sz_num - 1 - i];
    }

    return 1;
}

uint8_t convert_num_to_bnum(const uint64_t n, bnum_t *bn)
{
    bn->sz_num = count_digits(n);

    bn->num = malloc(bn->sz_num * sizeof(uint8_t));
    if (bn->num == NULL)
    {
        fprintf(stderr, "%s:%d Mem Alloc failed\n", __func__, __LINE__);
        return 0;
    }

    uint64_t num = n;
    for (uint64_t i = bn->sz_num - 1;i != (uint64_t)(-1);i--)
    {
        bn->num[i] = (uint8_t)(num % 10);
        num/=10;
    }

#if 0
    // Debugging...
    for (uint64_t i = 0;i<bn->sz_num;i++)
    {
        if (i == 0)
            fprintf(stdout, "%s:%d %u", __func__, __LINE__, bn->num[i]);
        else if (i == bn->sz_num - 1)
            fprintf(stdout, "%u\n", bn->num[i]);
        else
            fprintf(stdout, "%u", bn->num[i]);
    }
#endif

    return 1;
}

uint8_t convert_string_to_bnum(const uint8_t str[], bnum_t *bn)
{
    bn->sz_num = strlen(str);

    bn->num = malloc(bn->sz_num * sizeof(uint8_t));
    if (bn->num == NULL)
    {
        fprintf(stderr, "%s:%d Mem Alloc failed\n", __func__, __LINE__);
        return 0;
    }

    for (uint64_t i = 0;i<bn->sz_num;i++)
        bn->num[i] = str[i] - 48;

#if 0
    // Debugging...
    for (uint64_t i = 0;i<bn->sz_num;i++)
    {
        if (i == 0)
            fprintf(stdout, "%s:%d %u", __func__, __LINE__, bn->num[i]);
        else if (i == bn->sz_num - 1)
            fprintf(stdout, "%u\n", bn->num[i]);
        else
            fprintf(stdout, "%u", bn->num[i]);
    }
#endif

    return 1;
}

uint8_t bnum_add(const bnum_t bn1, const bnum_t bn2, bnum_t *bn)
{
    uint8_t *tmp = NULL;
    bn->num = NULL;
    bn->sz_num = 0;

    uint64_t max_sz_num = max(bn1.sz_num, bn2.sz_num);
    uint64_t min_sz_num = min(bn1.sz_num, bn2.sz_num);

    bnum_t max_num = max_sz_bnum(bn1, bn2);
    bnum_t min_num = min_sz_bnum(bn1, bn2);

    // Initially, the digits of the sum are
    // equally with the digits of the largest
    // number regarding the digits. It's possible
    // to be larger because of the carry in the last
    // digit.
    bn->sz_num = max_sz_num;
    bn->num = malloc(bn->sz_num * sizeof(uint8_t));
    if (bn->num == NULL)
    {
        fprintf(stderr, "%s:%d Mem Alloc failed\n", __func__, __LINE__);
        return 0;
    }

    uint64_t carry = 0;
    uint64_t i = 0, j = 0;
    // i index for max num and j index for min num.
    for (i = max_sz_num - 1, j = min_sz_num - 1;j != (uint64_t)(-1);i--, j--)
    {
        // Calculate the sum of the two digits of the numbers, including
        // carry if exists.
        uint64_t tmp_sum = max_num.num[i] + min_num.num[j] + carry;

        // If the addition produce 2-digit
        // then put a vavlue to the carry.
        if (tmp_sum > 9)
        {
            //Set the digit for the sum and the carry.
            bn->num[max_sz_num - 1 - i] = tmp_sum % 10;
            carry = tmp_sum / 10;

            // If the two numbers have equal size,
            // then, the k for loop is not needed.
            // If there is a carry at the last addition,
            // then add one more digit
            if (j == 0 && i == 0)
            {
                bn->sz_num += 1;

                tmp = realloc(bn->num,bn->sz_num  * sizeof(uint8_t));
                if (tmp != NULL)
                    bn->num = tmp;
                else
                {
                    fprintf(stderr, "%s:%d Mem Alloc failed\n", __func__, __LINE__);

                    if (bn->num)
                        free(bn->num);

                    return 0;
                }

                bn->num[bn->sz_num - 1] = carry;
            }
        }
        else
        {
            //Set the digit the sum and the carry.
            bn->num[max_sz_num - 1 - i] = tmp_sum;
            carry = 0;
        }

    }

    for (uint64_t k = i;k != (uint64_t)(-1);k--)
    {
        uint64_t tmp_sum = max_num.num[k] + carry;

        if (tmp_sum > 9)
        {
            // Set the digit for the sum and the carry.
            bn->num[max_sz_num - 1 - k] = tmp_sum % 10;
            carry = tmp_sum / 10;

            // If there is a carry at the last addition,
            // then add one more digit for the carry.
            if (k == 0)
            {
                bn->sz_num += 1;

                tmp = realloc(bn->num,bn->sz_num  * sizeof(uint8_t));
                if (tmp != NULL)
                    bn->num = tmp;
                else
                {
                    fprintf(stderr, "%s:%d Mem Alloc failed\n", __func__, __LINE__);

                    if (bn->num)
                        free(bn->num);

                    return 0;
                }

                bn->num[bn->sz_num - 1] = carry;
            }
        }
        else
        {
            // Set the digit for the sum and the carry.
            bn->num[max_sz_num - 1 - k] = tmp_sum;
            carry = 0;
        }
    }

    reverse_bnum(bn);

    return 1;
}

uint8_t bnum_mult(const bnum_t bn1, const bnum_t bn2, bnum_t *bn)
{
    uint8_t *tmp = NULL;
    bn->num = NULL;
    bn->sz_num = 0;

    uint64_t max_sz_num = max(bn1.sz_num, bn2.sz_num);
    uint64_t min_sz_num = min(bn1.sz_num, bn2.sz_num);

    bnum_t max_num = max_sz_bnum(bn1, bn2);
    bnum_t min_num = min_sz_bnum(bn1, bn2);

    // Allocate bnum to add after multiply
    // Usually we multiply like the following
    //      9999    max_num
    //    x   99    min_num
    //   -------
    //     89991
    //   +89991
    //   -------
    //    989901
    //
    // In the above example we have 2 bnums which is the
    // same as the size of the small number.
    bnum_t *bnum_mult_add = malloc(min_sz_num * sizeof(bnum_t));
    if (bnum_mult_add == NULL)
    {
        fprintf(stderr, "%s:%d Mem Alloc failed\n", __func__, __LINE__);
        return 0;
    }

    // Looping through the digits of min number
    for (uint64_t j = min_sz_num - 1;j != (uint64_t)(-1);j--)
    {
        uint64_t carry = 0;

        // The size of the number which produced when multiplying
        // the digits of the min number with the max number. The size
        // most of the times will be max_sz_num, but if there is a carry
        // at the last digit, then there will be max_sz_num+1.
        bnum_mult_add[j].sz_num = max_sz_num;
        bnum_mult_add[j].num = malloc(bnum_mult_add[j].sz_num * sizeof(uint8_t));
        if (bnum_mult_add[j].num == NULL)
        {
            fprintf(stderr, "%s:%d Mem Alloc failed\n", __func__, __LINE__);
            return 0;
        }

        // Looping through the digits of the max number
        for (uint64_t i = max_sz_num - 1;i != (uint64_t)(-1);i--)
        {
            uint64_t tmp_mult = (min_num.num[j] * max_num.num[i]) + carry;

            if (tmp_mult > 9)
            {
                bnum_mult_add[j].num[max_sz_num - 1 - i] = tmp_mult % 10;
                carry = tmp_mult / 10;

                // There is a carry at the last digit, the size of
                // max_sz_num is becoming max_sz_num+1;
                if (i == 0)
                {
                    bnum_mult_add[j].sz_num += 1;

                    tmp = realloc(bnum_mult_add[j].num,bnum_mult_add[j].sz_num  * sizeof(uint8_t));
                    if (tmp != NULL)
                        bnum_mult_add[j].num = tmp;
                    else
                    {
                        fprintf(stderr, "%s:%d Mem Alloc failed\n", __func__, __LINE__);

                        if (bnum_mult_add[j].num)
                            free(bnum_mult_add[j].num);

                        return 0;
                    }

                    bnum_mult_add[j].num[bnum_mult_add[j].sz_num - 1] = carry;
                }
            }
            else
            {
                bnum_mult_add[j].num[max_sz_num - 1 - i] = tmp_mult;
                carry = 0;
            }
        }

        // Reverse digits of the big number
        reverse_bnum(&bnum_mult_add[j]);

#if 1
        for (uint64_t k = 0;k<bnum_mult_add[j].sz_num;k++)
            fprintf(stdout, "%ju", bnum_mult_add[j].num[k]);
        fprintf(stdout, "\n");
#endif


    }
}

int main(int argc, char *arv[])
{
    // Convert number to bnum
    bnum_t b;
    convert_num_to_bnum(123455, &b);

    for (uint64_t i = 0;i<b.sz_num;i++)
        fprintf(stdout, "%u", b.num[i]);

    fprintf(stdout, "\n");

    if (b.num)
        free(b.num);


    // Convert string to bnum
    bnum_t c;
    convert_string_to_bnum("543211", &c);

    for (uint64_t i = 0;i<c.sz_num;i++)
        fprintf(stdout, "%u", c.num[i]);

    fprintf(stdout, "\n");

    if (c.num)
        free(c.num);


    // Addition
    bnum_t b1, b2, add;

    convert_num_to_bnum(999999999, &b1);
    convert_num_to_bnum(99999, &b2);

    bnum_add(b1, b2, &add);

    for (uint64_t i = 0;i<add.sz_num;i++)
        fprintf(stdout, "%u", add.num[i]);

    fprintf(stdout, "\n");

    if (b1.num)
        free(b1.num);
    if (b2.num)
        free(b2.num);
    if (add.num)
        free(add.num);


    // Multiplication
    bnum_t b3, b4, mult;

    convert_num_to_bnum(9999, &b3);
    convert_num_to_bnum(99, &b4);

    bnum_mult(b3, b4, &mult);

    for (uint64_t i = 0;i<mult.sz_num;i++)
        fprintf(stdout, "%u", mult.num[i]);

    fprintf(stdout, "\n");

    if (b3.num)
        free(b3.num);
    if (b4.num)
        free(b4.num);
    if (mult.num)
        free(mult.num);

}
