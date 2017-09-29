#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/uaccess.h>
#include <linux/slab.h>


/*declare global variable*/
char* my_string;
int my_accumulator;

EXPORT_SYMBOL(my_string);/*gets varibale from kernel to userspace */
EXPORT_SYMBOL(my_accumulator);


/*sets kernel variables to integers taken in as paramters for the syscall*/
asmlinkage long sys_my_set_state(char *the_string, int accumulator)
{
    int length_of_string;
   
    if(accumulator < 0)//accumulator value must be non-negative
    {
        return -EINVAL;
    }
      
    else if(my_string != NULL)
    {
        kfree(my_string); //frees memory assigned to my_string
    }

    length_of_string = 1 + strlen_user(the_string);
    my_string = (char *) kmalloc(sizeof(length_of_string), GFP_KERNEL);//allocates memory to my-string
    my_accumulator = accumulator;//sets kernel variable value to the parameter

    if(copy_from_user(my_string, the_string, length_of_string))//my_string = the_string;
        return -EFAULT;
   
   
    return 0;
   

}


/*Store copy of the kernel variable my_accumulator into user provided my_value and add it tp the parameter inc_value */
asmlinkage long sys_my_get_and_sum(int *my_value, int inc_value)
{   
       
    if(inc_value < 0)//inc_value must be non-negative
        return -EINVAL;
   
    if(inc_value + my_accumulator > INT_MAX)//the sum of inc_value and my_accumulator should not be great than INT_MAX
    {
        return -EOVERFLOW;
    }
   
    my_accumulator = my_accumulator + inc_value;//update my_accumulator to the sum of my_accumulator and inc_value
   
    if (copy_to_user(my_value, &my_accumulator, sizeof(int)))//copies a block of data from the kernel to userspace
            return -EFAULT;
   
       return 0;   
}


/*Store copy of the kernel variable my_string into user provided buffer buf of size bsize*/
asmlinkage long sys_my_get_string(char *buf, int bsize)
{
    int copylen, slen;
    slen = strlen(my_string);//slen takes length of kernel variable my_string
   
       if (my_string == NULL)//if my_string is empty return ENODATA
    {
        return -ENODATA;
    }
    copylen = min((int)slen, (int)(bsize-1));//take least value of lengths between bsize-1 and kernel variable my string
    if(copy_to_user(buf, my_string, copylen))//copies a block of data from the kernel to userspace
        return -EFAULT;
   
    return 0;
}
