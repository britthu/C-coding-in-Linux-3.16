#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/mm_types.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/atomic.h>



char *mod_name = "pid_vminfo";

module_param(mod_name, charp, S_IRUGO);
MODULE_PARM_DESC(mod_name, "This is a string variable for module name.");

   


/* This function is called when the module is loaded. */
static int pid_vminfo_show(struct seq_file *m, void *v)/*prints to file m using esq_printf*/
{	
	
       printk(KERN_INFO "Loading Module\n");

     struct vm_area_struct *virtual_memory;
     virtual_memory = current->mm->mmap;/*points to type struct mmap/vm_area_struct*/

	
	/*print information about memory*/
    seq_printf(m, "\n\n");
    seq_printf(m, "The access flags: %u \n", current->mm->def_flags);

    /*seq_printf(m, "The address space users: %d \n", atomic_read(current->mm->mm_users));
    seq_printf(m, "The primary usage counter: %d \n", atomic_read(current->mm->mm_count));*/

    seq_printf(m, "The number of memory areas: %d \n", current->mm->map_count);
	seq_printf(m, "The start adress of code: %lu \n", current->mm->start_code);
    seq_printf(m, "The final address of code: %lu \n", current->mm->end_code);
    seq_printf(m, "The start address of data: %lu \n", current->mm->start_data);
    seq_printf(m, "The final address of data: %lu \n", current->mm->end_code);
    seq_printf(m, "The start address of heap: %lu \n", current->mm->start_brk);
    seq_printf(m, "The final address of head: %lu \n", current->mm->brk);
    seq_printf(m, "The start address of stack: %lu \n", current->mm->start_stack);
    seq_printf(m, "The start of arguments: %lu \n", current->mm->arg_start);
    seq_printf(m, "The end of arguments: %lu \n", current->mm->arg_end);
    seq_printf(m, "The start of environment: %lu \n", current->mm->env_start);
    seq_printf(m, "The end of environment: %lu \n", current->mm->env_end);
    seq_printf(m, "The pages allocated: %lu \n", current->mm->rss);
    seq_printf(m, "The total number of pages: %lu \n\n\n", current->mm->total_vm);



    seq_printf(m, "Virtual Memory Area Struct Structure:\n");
	/*prints information for each vm_area_struct in the current process*/
    while(virtual_memory != NULL)
    {
      
        seq_printf(m, "The virtual machine start: %lu \n", current->mm->mmap->vm_start);
        seq_printf(m, "The virtual machine end: %lu \n", virtual_memory->vm_end);
        seq_printf(m, "The virtual machine access permissions: %#x \n", virtual_memory->vm_page_prot);
      seq_printf(m, "The virtual machine flags: %#x \n", virtual_memory->vm_flags);


        virtual_memory = virtual_memory ->vm_next;/*take you to the next vm_area_struct; so *(current->mm->mmap) = current->mm->mmap->vm_next;*/
        seq_printf(m, "\n\n");
    }
  

       return 0;
}

static int pid_vminfo_open(struct inode *inode, struct file *file)
{
     return single_open(file, pid_vminfo_show, NULL);
}

 static const struct file_operations pid_vminfo_fops = {
     .owner = THIS_MODULE,
     .open = pid_vminfo_open,
     .read = seq_read,
     .llseek = seq_lseek,
     .release = single_release,
 };

 static int __init pid_vminfo_init(void)
 {
     proc_create("pid_vminfo", 0, NULL, &pid_vminfo_fops);
     return 0;
 }

/* This function is called when the module is removed. */
 static void __exit pid_vminfo_exit(void)
 {
     remove_proc_entry("pid_vminfo", NULL);
     printk(KERN_INFO "Removing module.\n");
}


/* Macros for registering module entry and exit points. */
module_init( pid_vminfo_init );
module_exit( pid_vminfo_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("PID_VMINFO Module");
MODULE_AUTHOR("SGG");
