#include "bigbool.h"

int errno = ERR_OK;

size_t len_vector(bigbool* vec)
{
    if (vec == NULL)
    {
        errno = ERR_ARG;
        return -1;
    }

    size_t len = (vec->last_byte * 8) + vec->last_bit;
    return len;
}

int BB_check(char* str)
{
    size_t len = strlen(str);
    if (len == 0)
    {
        return ERR_ARG;
    }

    for (size_t i = 0; i < len; i++)
    {
        if (str[i] != '1' && str[i] != '0')
        {
            return ERR_WRT;
        }
    }
    return ERR_OK;
}

char* BB_string_input()
{
    char symbol;
    char* string = (char *)malloc(1 * sizeof(char));
    if(string == NULL)
    {
        errno = ERR_MEM;
        return NULL;
    }
    int i = 0;
    while((symbol = fgetc(stdin)) != '\n')
    {
        string[i] = symbol;
        string = (char *)realloc(string, i * sizeof(char) + 2);
        if(string == NULL)
        {
            errno = ERR_MEM;
            return NULL;
        }
        i++;
    }
    return string;
}

bigbool* empty_bool(size_t len)
{
    bigbool* vec = (bigbool *)calloc(1, sizeof(bigbool));
    if (vec == NULL)
    {
        errno = ERR_MEM;
        return NULL;
    }

    vec->last_byte = len / 8;
    vec->last_bit = len % 8;

    vec->parts = (uint8_t *)calloc(vec->last_byte + (vec->last_bit > 0), sizeof(uint8_t));
    if (vec->parts == NULL)
    {
        errno = ERR_MEM;
        return NULL;
    }

    return vec;
}

bigbool* BB_from_string(char* str)
{
    int corrent = BB_check(str);
    if (corrent)
    {
        return NULL;
    }

    size_t len = strlen(str);
    if (len == 0)
    {
        errno = ERR_ARG;
        return NULL;
    }     
    
    bigbool* vec = empty_bool(len);
    if (vec == NULL)
    {
        errno = ERR_MEM;
        return NULL;
    }

    size_t ind = 0;
    for (size_t i = 0; i < vec->last_byte; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            ind = len - 1 - (i * 8 + j);
            vec->parts[i] = vec->parts[i] | ((str[ind] - '0') << j);
        }
    }
    for (size_t i = 0; i < vec->last_bit; i++)
    {
        ind = len - 1 - (vec->last_byte * 8 + i);
        vec->parts[vec->last_byte] = vec->parts[vec->last_byte] | ((str[ind] - '0') << i);
    }  

    return vec;
}

char* BB_to_str(bigbool* vec)
{
    if (vec == NULL)
    {
        errno = ERR_ARG;
        return NULL;
    }

    size_t len = len_vector(vec);

    char* str = (char*)calloc((len + 1), sizeof(char));
    if (str == NULL)
    {
        errno = ERR_MEM;
        return NULL;
    }

    size_t index = 0;
    for (size_t i = 0; i < vec->last_byte; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            index = len - ((i * 8) + j) - 1;
	        str[index] = ((vec->parts[i] >> j) & 1) + '0';
        }
    }
    for (size_t i = 0; i < vec->last_bit; i++)
    {
        index = len - ((vec->last_byte * 8) + i) - 1;
	    str[index] = ((vec->parts[vec->last_byte] >> i) & 1) + '0';
    }

    return str;
}

bigbool* BB_from_uint64(uint64_t num)
{
    int len = 0;
    for (len = 63; len > 0; len--)
    {
        if (((num >> len) & 1) == 1)
        {
            break;
        } 
    }
    len++;

    bigbool* vec = empty_bool(len);
    if (vec == NULL)
    {
        errno = ERR_MEM;
        return NULL;
    }
 
    int ind = 0;
    for (size_t i = 0; i < vec->last_byte; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            vec->parts[i] = vec->parts[i] | (((num >> ind) & 1) << j);
            ind++;
        }
    }

    for (size_t i = 0; i < vec->last_bit; i++)
    {        
        vec->parts[vec->last_byte] = vec->parts[vec->last_byte] | (((num >> ind) & 1) << i);
        ind++;
    }

    return vec;
}

bigbool* BB_not(bigbool* vec)
{
    if (vec == NULL)
    {
        errno = ERR_ARG;
        return NULL;
    }

    bigbool* vec1 = empty_bool(len_vector(vec));
    if (vec1 == NULL)
    {
        errno = ERR_MEM;
        return NULL;
    }

    vec1->last_bit = vec->last_bit;
    vec1->last_byte = vec->last_byte;

    for (int i = 0; i <= (vec->last_byte + (vec->last_bit > 0) - 1); i++)
    {
        vec1->parts[i] = ~(vec->parts[i]);
    }

    return vec1;
}

bigbool* BB_xor(bigbool* vec1, bigbool* vec2)
{
    if((vec1 == NULL) || (vec2 == NULL))
    {
        errno = ERR_ARG;
        return NULL;
    }

    if((len_vector(vec2)) > (len_vector(vec1)))
    {
        return BB_xor(vec2, vec1);
    }

    bigbool* vec = empty_bool(len_vector(vec1));
    if (vec == NULL)
    {
        errno = ERR_MEM;
        return NULL;
    }

    vec->last_byte = vec1->last_byte;
    vec->last_bit = vec1->last_bit;

    for (int i = 0; i <= (vec2->last_byte + (vec2->last_bit > 0) - 1); i++)
    {
        vec->parts[i] = vec1->parts[i] ^ vec2->parts[i];
    }

    for (int i =(vec2->last_byte - (vec2->last_bit == 0) + 1); i <= (vec1->last_byte + (vec1->last_bit > 0) - 1); i++)
    {
        vec->parts[i] = vec1->parts[i];
    }

    return vec;
}

bigbool* BB_or(bigbool* vec1, bigbool* vec2)
{
    if((vec1 == NULL) || (vec2 == NULL))
    {
        errno = ERR_ARG;
        return NULL;
    }

    if((len_vector(vec2)) > (len_vector(vec1)))
    {
        return BB_or(vec2, vec1);
    }

    bigbool* vec = empty_bool(len_vector(vec1));
    if (vec == NULL)
    {
        errno = ERR_MEM;
        return NULL;
    }

    vec->last_byte = vec1->last_byte;
    vec->last_bit = vec1->last_bit;

    for (int i = 0; i <= (vec2->last_byte + (vec2->last_bit > 0) - 1); i++)
    {
        vec->parts[i] = vec1->parts[i] | vec2->parts[i];
    }

    for (int i = (vec2->last_byte - (vec2->last_bit == 0) + 1); i <= (vec1->last_byte + (vec1->last_bit > 0) - 1); i++)
    {
        vec->parts[i] = vec1->parts[i];
    }

    return vec;
}

bigbool* BB_and(bigbool* vec1, bigbool* vec2)
{
    if((vec1 == NULL) || (vec2 == NULL))
    {
        errno = ERR_ARG;
        return NULL;
    }

    if((len_vector(vec2)) > (len_vector(vec1)))
    {
        return BB_and(vec2, vec1);
    }

    bigbool* vec = empty_bool(len_vector(vec1));
    if (vec == NULL)
    {
        errno = ERR_MEM;
        return NULL;
    }

    vec->last_byte = vec1->last_byte;
    vec->last_bit = vec1->last_bit;

    for (int i = 0; i <= (vec2->last_byte + (vec2->last_bit > 0) - 1); i++)
    {
        vec->parts[i] = vec1->parts[i] & vec2->parts[i];
    }

    for (int i = (vec2->last_byte - (vec2->last_bit == 0) + 1); i <= (vec1->last_byte + (vec1->last_bit > 0) - 1); i++)
    {
        vec->parts[i] = 0;
    }

    return vec;
}

bigbool* BB_left_shift(bigbool* vec, int num)
{
    if(vec == NULL)
    {
        errno = ERR_ARG;
        return NULL;
    }

    if (num < 0)
    {
        num = num * (-1);
        return BB_right_shift(vec, num);
    }

    size_t new_len = len_vector(vec) + num;
    bigbool* res = empty_bool(new_len);
    if (res == NULL)
    {
        errno = ERR_MEM;
        return NULL;
    }

    res->last_byte = new_len / 8;
    res->last_bit = new_len % 8;

    size_t byte = num / 8;
    size_t bit = num % 8;

    uint8_t first_parts = 0;
    uint8_t last_parts = 0;

    for (int i = 0; i <= vec->last_byte - (vec->last_bit == 0); i++)
    {
        last_parts = vec->parts[i] >> (8 - bit);
        res->parts[i + byte] = first_parts | (vec->parts[i] << (bit));
        first_parts = last_parts;
    }
   
    if (vec->last_bit + bit > 7)
    {
        res->parts[byte + vec->last_byte + 1 - (res->last_bit == 0)] |= last_parts;
    }

    for(int i = 0; i < byte; i++)
    {
        res->parts[i] = 0; 
    }

    return res;
}

bigbool* BB_right_shift(bigbool* vec, int num)
{
    if(vec == NULL)
    {
        errno = ERR_ARG;
        return NULL;
    }

    if (num < 0)
    {
        num = num * (-1);
        return BB_left_shift(vec, num);
    }

    if (num >= len_vector(vec))
    {
        return empty_bool(1);
    }

    size_t new_len = len_vector(vec) - num;

    bigbool* res = empty_bool(new_len);
    if (res == NULL)
    {
        errno = ERR_MEM;
        return NULL;
    }

    res->last_byte = new_len / 8;
    res->last_bit = new_len % 8;
   
    size_t byte = num / 8;
    size_t bit = num % 8;

    res->parts[0] = vec->parts[byte] >> (bit);
    uint8_t first_parts = 0;
    for (int i = byte + 1; i <= vec->last_byte - (vec->last_bit == 0); i++)
    {

        first_parts = vec->parts[i] << (8 - bit);
        res->parts[i - byte] = vec->parts[i] >> (bit);
        res->parts[i - byte - 1] |= first_parts;
    }

    return res;
}

bigbool* BB_left_circle_shift(bigbool* vec, int num)
{
    if(vec == NULL)
    {
        errno = ERR_ARG;
        return NULL;
    }

    if (num < 0)
    {
        num = num * (-1);
        return BB_right_circle_shift(vec, num);
    }

    bigbool* vec1 = BB_left_shift(vec, num);
    if(vec1 == NULL)
    {
        return NULL;
    }

    bigbool* vec2 = BB_right_shift(vec, len_vector(vec) - num);
    if(vec2 == NULL)
    {
        return NULL;
    }

    bigbool* res = BB_or(vec1, vec2);
    if(res == NULL)
    {
        return NULL;
    }

    res->last_byte = vec->last_byte;
    res->last_bit = vec->last_bit;

    BB_free(vec2);
    BB_free(vec1);

    return res;
}

bigbool* BB_right_circle_shift(bigbool* vec, int num)
{
    if(vec == NULL)
    {
        errno = ERR_ARG;
        return NULL;
    }

    if (num < 0)
    {
        num = num * (-1);
        return BB_left_circle_shift(vec, num);
    }

    bigbool* vec1 = BB_right_shift(vec, num);
    if(vec1 == NULL)
    {
        return NULL;
    }

    bigbool* vec2 = BB_left_shift(vec, len_vector(vec) - num);
    if(vec2 == NULL)
    {
        return NULL;
    }

    bigbool* res = BB_or(vec1, vec2);
    if(res == NULL)
    {
        return NULL;
    }

    res->last_byte = vec->last_byte;
    res->last_bit = vec->last_bit;

    BB_free(vec2);
    BB_free(vec1);

    return res;
}

void BB_free(bigbool* vec)
{
    if (vec == NULL || vec->parts == NULL)
    {
        errno = ERR_ARG;
        return;
    }   

    free(vec->parts);
    free(vec);
}