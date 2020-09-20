#include "bigbool.h"

#define RESET "\033[0m"
#define RED   "\033[31m"		/* Red */
#define GREEN "\033[32m"		/* Green */

#define LOG_ERR(msg) \
	printf(RED"%s:%d %s [ERR] %s\n"RESET,\
		__FILE__, __LINE__, __func__, msg);


int test_converting()
{
    int count = 0;

    bigbool* vec = BB_from_string("10110111");
    char* string = BB_to_str(vec);
    if (strcmp(string, "10110111"))
    {
        LOG_ERR("BB_from_string - does not work correctly");
        count++;
    }
    free(string);
    BB_free(vec);

    vec = BB_from_string("1011");
    string = BB_to_str(vec);
    if (strcmp(string, "1011"))
    {
        LOG_ERR("BB_from_string - does not work correctly");
        count++;
    }
    free(string);
    BB_free(vec);

    vec = BB_from_string("10101111010101110011111111011010101011101011010");
    string = BB_to_str(vec);
    if (strcmp(string, "10101111010101110011111111011010101011101011010"))
    {
        LOG_ERR("BB_from_string - does not work correctly");
        count++;
    }
    free(string);
    BB_free(vec);

    return count;
}

int test_logic_functions()
{
    int count = 0;

    bigbool* vec1 = BB_from_string("10101111010101110011111111011010101011101011010");
    bigbool* vec2 = BB_from_string("10111010001");
    bigbool* vec3 = BB_from_string("1011");
    bigbool* vec4 = BB_from_string("00001110110");
    bigbool* vec5 = BB_from_string("10110111");

    //inversion
    bigbool* inversion = BB_not(vec1);
    char* string = BB_to_str(inversion);
    if (strcmp(string, "01010000101010001100000000100101010100010100101"))
    {
        LOG_ERR("BB_not - does not work correctly");
        count++;
    }
    free(string);
    BB_free(inversion);

    inversion = BB_not(vec2);
    string = BB_to_str(inversion);
    if (strcmp(string, "01000101110"))
    {
        LOG_ERR("BB_not - does not work correctly");
        count++;
    }
    free(string);
    BB_free(inversion);

    inversion = BB_not(vec3);
    string = BB_to_str(inversion);
    if (strcmp(string, "0100"))
    {
        LOG_ERR("BB_not - does not work correctly");
        count++;
    }
    free(string);
    BB_free(inversion);

    inversion = BB_not(vec4);
    string = BB_to_str(inversion);
    if (strcmp(string, "11110001001"))
    {
        LOG_ERR("BB_not - does not work correctly");
        count++;
    }
    free(string);
    BB_free(inversion);

    inversion = BB_not(vec5);
    string = BB_to_str(inversion);
    if (strcmp(string, "01001000"))
    {
        LOG_ERR("BB_not - does not work correctly");
        count++;
    }
    free(string);
    BB_free(inversion);

    //xor
    bigbool* xor = BB_xor(vec1, vec2);
    string = BB_to_str(xor);
    if (strcmp(string, "10101111010101110011111111011010101001010001011"))
    {
        LOG_ERR("BB_xor - does not work correctly");
        count++;
    }
    free(string);
    BB_free(xor);

    xor = BB_xor(vec2, vec3);
    string = BB_to_str(xor);
    if (strcmp(string, "10111011010"))
    {
        LOG_ERR("BB_xor - does not work correctly");
        count++;
    }
    free(string);
    BB_free(xor);

    xor = BB_xor(vec2, vec4);
    string = BB_to_str(xor);
    if (strcmp(string, "10110100111"))
    {
        LOG_ERR("BB_xor - does not work correctly");
        count++;
    }
    free(string);
    BB_free(xor);

    xor = BB_xor(vec4, vec5);
    string = BB_to_str(xor);
    if (strcmp(string, "00011000001"))
    {
        LOG_ERR("BB_xor - does not work correctly");
        count++;
    }
    free(string);
    BB_free(xor);

    //disjunction
    bigbool* or = BB_or(vec1, vec2);
    string = BB_to_str(or);
    if (strcmp(string, "10101111010101110011111111011010101011111011011"))
    {
        LOG_ERR("BB_or - does not work correctly");
        count++;
    }
    free(string);
    BB_free(or);

    or = BB_or(vec2, vec3);
    string = BB_to_str(or);
    if (strcmp(string, "10111011011"))
    {
        LOG_ERR("BB_or - does not work correctly");
        count++;
    }
    free(string);
    BB_free(or);

    or = BB_or(vec2, vec4);
    string = BB_to_str(or);
    if (strcmp(string, "10111110111"))
    {
        LOG_ERR("BB_or - does not work correctly");
        count++;
    }
    free(string);
    BB_free(or);

    or = BB_or(vec4, vec5);
    string = BB_to_str(or);
    if (strcmp(string, "00011110111"))
    {
        LOG_ERR("BB_or - does not work correctly");
        count++;
    }
    free(string);
    BB_free(or);

    //conjuction
    bigbool* and = BB_and(vec1, vec2);
    string = BB_to_str(and);
    if (strcmp(string, "00000000000000000000000000000000000010101010000"))
    {
        LOG_ERR("BB_and - does not work correctly");
        count++;
    }
    free(string);
    BB_free(and);

    and = BB_and(vec2, vec3);
    string = BB_to_str(and);
    if (strcmp(string, "00000000001"))
    {
        LOG_ERR("BB_and - does not work correctly");
        count++;
    }
    free(string);
    BB_free(and);

    and = BB_and(vec2, vec4);
    string = BB_to_str(and);
    if (strcmp(string, "00001010000"))
    {
        LOG_ERR("BB_and - does not work correctly");
        count++;
    }
    free(string);
    BB_free(and);

    and = BB_and(vec4, vec5);
    string = BB_to_str(and);
    if (strcmp(string, "00000110110"))
    {
        LOG_ERR("BB_and - does not work correctly");
        count++;
    }
    free(string);
    BB_free(and);

    BB_free(vec1);
    BB_free(vec2);
    BB_free(vec3);
    BB_free(vec4);
    BB_free(vec5);

    return count;
}

int test_BB_from_uint64()
{
    int count = 0;

    uint64_t num = 8192;
    bigbool* vec = BB_from_uint64(num);
    char* string = BB_to_str(vec);
    if (strcmp(string, "10000000000000"))
    {
        LOG_ERR("BB_from_uint64 - does not work correctly");
        count++;
    }
    free(string);
    BB_free(vec);

    uint64_t num1 = 0b101111011111001000100010110100101;
    vec = BB_from_uint64(num1);
    string = BB_to_str(vec);
    if (strcmp(string, "101111011111001000100010110100101"))
    {
        LOG_ERR("BB_from_uint64 - does not work correctly");
        count++;
    }
    free(string);
    BB_free(vec);

    uint64_t num2 = 0;
    vec = BB_from_uint64(num2);
    string = BB_to_str(vec);
    if (strcmp(string, "0"))
    {
        LOG_ERR("BB_from_uint64 - does not work correctly");
        count++;
    }
    free(string);
    BB_free(vec);

    return count;
}

int test_shifts()
{
    int count = 0;

    bigbool* vec = BB_from_string("10111010001");
    bigbool* shift = BB_left_shift(vec, 7);
    char* string = BB_to_str(shift);
    if (strcmp(string, "101110100010000000"))
    {
        LOG_ERR("BB_left_shift - does not work correctly");
        count++; 
    }
    free(string);
    BB_free(shift);
    BB_free(vec);

    vec = BB_from_string("10100110000111");
    shift = BB_right_shift(vec, 4);
    string = BB_to_str(shift);
    if (strcmp(string, "1010011000"))
    {
        LOG_ERR("BB_right_shift - does not work correctly");
        count++; 
    }
    free(string);
    BB_free(shift);
    BB_free(vec);

    //num < 0
    vec = BB_from_string("101011011111110101011");
    shift = BB_left_shift(vec, -3);
    string = BB_to_str(shift);
    if (strcmp(string, "101011011111110101"))
    {
        LOG_ERR("BB_left_shift - does not work correctly");
        count++; 
    }
    free(string);
    BB_free(shift);

    shift = BB_right_shift(vec, -3);
    string = BB_to_str(shift);
    if (strcmp(string, "101011011111110101011000"))
    {
        LOG_ERR("BB_right_shift - does not work correctly");
        count++; 
    }
    free(string);
    BB_free(shift);
    BB_free(vec);

    //num >= 0
    vec = BB_from_string("10111010001");
    shift = BB_right_shift(vec, 11);
    string = BB_to_str(shift);
    if (strcmp(string, "0"))
    {
        LOG_ERR("BB_right_shift - does not work correctly");
        count++; 
    }
    free(string);
    BB_free(shift);
    BB_free(vec);

    return count;
}

int test_circle_shift()
{
    int count = 0;

    bigbool* vec = BB_from_string("10101111010101110011111111011010101011101011010");
    bigbool* circ_shifts = BB_left_circle_shift(vec, 14);
    char* string = BB_to_str(circ_shifts);
    if(strcmp(string, "11001111111101101010101110101101010101111010101"))
    {
        LOG_ERR("BB_left_circle_shift - does not work correctly");
        count++; 
    }
    free(string);
    BB_free(circ_shifts);

    circ_shifts = BB_right_circle_shift(vec, 14);
    string = BB_to_str(circ_shifts);
    if(strcmp(string, "01011101011010101011110101011100111111110110101"))
    {
        LOG_ERR("BB_right_circle_shift - does not work correctly");
        count++; 
    }
    free(string);
    BB_free(circ_shifts);
    BB_free(vec);

    //num < 0
    vec = BB_from_string("10101111010101110011111111011000");
    circ_shifts = BB_left_circle_shift(vec, -12);
    string = BB_to_str(circ_shifts);
    if(strcmp(string, "11111101100010101111010101110011"))
    {
        LOG_ERR("BB_left_circle_shift - does not work correctly");
        count++; 
    }
    free(string);
    BB_free(circ_shifts);

    circ_shifts = BB_right_circle_shift(vec, -5);
    string = BB_to_str(circ_shifts);
    if(strcmp(string, "11101010111001111111101100010101"))
    {
        LOG_ERR("BB_right_circle_shift - does not work correctly");
        count++; 
    }
    free(string);
    BB_free(circ_shifts);
    BB_free(vec);

    //num == byte
    vec = BB_from_string("101011110101011100111111110100001001100000000100");
    circ_shifts = BB_left_circle_shift(vec, 16);
    string = BB_to_str(circ_shifts);
    if(strcmp(string, "001111111101000010011000000001001010111101010111"))
    {
        LOG_ERR("BB_left_circle_shift - does not work correctly");
        count++; 
    }
    free(string);
    BB_free(circ_shifts);

    circ_shifts = BB_right_circle_shift(vec, 16);
    string = BB_to_str(circ_shifts);
    if(strcmp(string, "100110000000010010101111010101110011111111010000"))
    {
        LOG_ERR("BB_right_circle_shift - does not work correctly");
        count++; 
    }
    free(string);
    BB_free(circ_shifts);
    BB_free(vec);

    return count;
}

int test_public_functions()
{
    int count = 0;

    bigbool* vec = BB_from_string("101100101101010101010111111101001100101111111111");
    size_t len = len_vector(vec);
    if (len != 48)
    {
        LOG_ERR("len_vector - does not work correctly");
        count++; 
    }

    bigbool* empbool = empty_bool(len);
    char* string = BB_to_str(empbool);
    if (strcmp(string, "000000000000000000000000000000000000000000000000"))
    {
        LOG_ERR("empty_bool - does not work correctly");
        count++; 
    }
    free(string);
    BB_free(empbool);
    BB_free(vec);

    return count;
}


int main()
{
    int count = 0;

    count += test_converting();
    count += test_logic_functions();
    count += test_BB_from_uint64();
    count += test_shifts();
    count += test_circle_shift();
    count += test_public_functions();
    if (count > 0)
	{
		puts ("");
		printf ("Number of failed tests: %d\n", count);
		return 0;
	}
    else
    {
        puts (GREEN"[OK] All is ok!"RESET);
    }
    
    return 0;
}