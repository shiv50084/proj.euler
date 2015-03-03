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

    uint64_t carry = 0;
    uint64_t i = 0, j = 0;
    // i index for max num and j index for min num.
    for (i = max_sz_num - 1, j = min_sz_num - 1;j != (uint64_t)(-1);i--, j--)
    {
        uint64_t tmp_sum = max_num.num[i] + min_num.num[j] + carry;


        // Allocate memory for each digit of the sum
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

        // If the addition produce 2-digit
        // then put a vavlue to the carry.
        if (tmp_sum > 9)
        {
            bn->num[bn->sz_num - 1] = tmp_sum % 10;

            // Calculate carry.
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
            bn->num[bn->sz_num - 1] = tmp_sum;

            carry = 0;
        }

    }

    for (uint64_t k = i;k != (uint64_t)(-1);k--)
    {
        uint64_t tmp_sum = max_num.num[k] + carry;

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

        if (tmp_sum > 9)
        {
            bn->num[bn->sz_num - 1] = tmp_sum % 10;

            // Calculate carry.
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
            bn->num[bn->sz_num - 1] = tmp_sum;

            carry = 0;
        }
    }

    // Reverse digits of the big number
    for (uint64_t m = 0;m<bn->sz_num / 2;m++)
    {
        bn->num[m] ^= bn->num[bn->sz_num - 1 - m];
        bn->num[bn->sz_num - 1 - m] ^= bn->num[m];
        bn->num[m] ^= bn->num[bn->sz_num - 1 - m];
    }

    return 1;
}

int main(int argc, char *arv[])
{
    bnum_t b;
    convert_num_to_bnum(123455, &b);

    for (uint64_t i = 0;i<b.sz_num;i++)
        fprintf(stdout, "%u", b.num[i]);

    fprintf(stdout, "\n");

    if (b.num)
        free(b.num);



    bnum_t c;
    convert_string_to_bnum("543211", &c);

    for (uint64_t i = 0;i<c.sz_num;i++)
        fprintf(stdout, "%u", c.num[i]);

    fprintf(stdout, "\n");

    if (c.num)
        free(c.num);





    bnum_t b1, b2, add;

    convert_num_to_bnum(999, &b1);
    convert_num_to_bnum(999, &b2);

    fprintf(stdout, "Adding...\n");
    bnum_add(b1, b2, &add);

    for (uint64_t i = 0;i<add.sz_num;i++)
        fprintf(stdout, "%u", add.num[i]);

    fprintf(stdout, "\n");


}
