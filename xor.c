#include "bigbool.h"

#define RESET "\033[0m"
#define RED   "\033[31m"		/* Red */
#define GREEN "\033[32m"		/* Green */

#define LOG_ERR(msg) \
	printf(RED"%s:%d %s [ERR] %s\n"RESET,\
		__FILE__, __LINE__, __func__, msg);

int test_xor()			//vec1 ^ vec2 = (~vec1 & vec2) | (vec1 & ~vec2)
{
    int count = 0;

    srand (time (NULL));

    bigbool* vec1 = BB_from_uint64 (rand());
    bigbool* vec2 = BB_from_uint64 (rand());

    equil_size(vec1, vec2);

	//xor = vec1 ^ vec2
    bigbool* vec_xor = BB_xor (vec1, vec2);
    char* str_vec_xor = BB_to_str(vec_xor);

	//~vec1
    bigbool* not_vec1 = BB_not(vec1);
	//~vec2
    bigbool* not_vec2 = BB_not(vec2);
	//~vec1 & vec2
    bigbool* first_part = BB_and (not_vec1, vec2);
	//vec1 & ~vec2
    bigbool* second_part = BB_and (vec1, not_vec2);
	//(~vec1 & vec2) | (vec1 & ~vec2) = vec1 ^ vec2
    bigbool* res_xor = BB_or (first_part, second_part);
    char* str_res = BB_to_str(res_xor);

    if (strcmp(str_vec_xor, str_res))
    {
        LOG_ERR("xor - does not work correctly");
        printf("%s != %s\n", str_vec_xor, str_res);
        count++; 
    }
    
    BB_free(vec1);
    BB_free(vec2);
    BB_free(vec_xor);
    free(str_vec_xor);
    BB_free(not_vec1);
    BB_free(not_vec2);
    BB_free(first_part);
    BB_free(second_part);
    BB_free(res_xor);
    free(str_res);

	return count;
}

int main()
{
    int count = 0;
    
    int value = 10000;
    while(value)
    {    
        count += test_xor();
        value--;
    }

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