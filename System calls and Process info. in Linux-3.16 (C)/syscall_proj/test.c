#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>

int main()
{
    int a;
    char* b;
/*parameters for sys_my_set_stste*/
    a = 2;
    b = "test string";
   
	/*paramter for sys_my_get_and_sum*/
    int *test_value = (int *) malloc(sizeof(int));
   
	/*paramters for sys_my_get_string*/
    char *test_char = (char *) malloc(sizeof(char)*13);
    int length_of_b = strlen(b);
   
/*call syscalls and print current state of each kernel varibale after each syscall*/
    long int test_case_1 = syscall(354, b, a);
    printf("If sys_my_set_state was successful then 0 is returned: %ld \n", test_case_1);
   
   
    long int test_case_2 = syscall(355, test_value, 4);
    printf("If sys_my_get_and_sum was successful then 0 is returned: %ld \n", test_case_2);
    printf("Changed value of my_accumulator is: %ld \n\n", test_value);

   
    long int test_case_3 = syscall(356, test_char, length_of_b);
    printf("If sys_my_get_string was successful then 0 is returned: %ld \n", test_case_3);
    printf("Changed value of my_string is: %s \n\n", test_char);

    return 0;    
}
