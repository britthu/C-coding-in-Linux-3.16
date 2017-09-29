#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/unistd.h>
#include <linux/moduleparam.h>

/*global variable*/
int pid_var= 1;

module_param(pid_var, int, S_IRUGO|S_IWUSR);/*allows global to be set as a changeable paramter*/
MODULE_PARM_DESC(pid_var, "this is an int variable");
void convert_and_print_flags(unsigned int flags);/*converts and prints information about process flags*/

/* This function is called when the module is loaded. */
int init(void)
{   
	/*declare pointer to struct task_struct and struct list_head*/	
	struct task_struct *task;
	struct task_struct *child;
	struct list_head *front;
  
    printk(KERN_INFO "Loading Module\n");
    for_each_process(task)/*iterates through the list of task structs/processes*/
    {
        if(pid_var == task->pid) /*if process id matches then extract information */
        {              
                printk("current pid: %d \n", task->pid);
                printk("current name: %s \n", task->comm); /*to print any process name use comm*/
                printk("current gid: %i \n", task->cred->gid.val);
                printk("current uid: %i \n", task->cred->uid.val);
	
		/*print parent process info*/
                printk("parent pid: %d \n", task->parent->pid);
                printk("parent name: %s \n", task->parent->comm);
		
		/*call convert flags function*/
		convert_and_print_flags(task->flags);
          
          
           
           

            list_for_each(front,&task->children)/*iterates through list of current process' children, taking task->children as the head of the list and using front to traverse*/

            {	/*prints children processes' information*/ 
                child = list_entry(front, struct task_struct, sibling);/*returns pointer an dpoints to siblning within struct list_head*/
                printk("child pid: %d \n", child->pid);
                printk("child name: %s \n", child->comm);
              
            }
        }
      
    }

    return 0;
}

void convert_and_print_flags(unsigned int flags) {
  if((flags & PF_EXITING) != 0) printk(KERN_INFO "Flag state: getting shut down \n");
  if((flags & PF_EXITPIDONE) != 0) printk(KERN_INFO "Flag state: pi exit done on shut down");
  if((flags & PF_VCPU) != 0) printk(KERN_INFO "Flag state: I'm a virtual CPU\n");
  if((flags & PF_WQ_WORKER ) != 0) printk(KERN_INFO "Flag state: I'm a workqueue worker\n");
  if((flags & PF_FORKNOEXEC) != 0) printk(KERN_INFO "Flag state: forked but didn't exec\n");
  if((flags & PF_MCE_PROCESS) != 0) printk(KERN_INFO "Flag state: process policy on mce errors\n");
  if((flags & PF_SUPERPRIV) != 0) printk(KERN_INFO "Flag state: used super-user privileges\n");
  if((flags & PF_DUMPCORE) != 0) printk(KERN_INFO "Flag state: dumped core\n");
  if((flags & PF_SIGNALED) != 0) printk(KERN_INFO "Flag state: killed by a signal\n");
  if((flags & PF_MEMALLOC) != 0) printk(KERN_INFO "Flag state: Allocating memory\n");
  if((flags & PF_NPROC_EXCEEDED) != 0) printk(KERN_INFO "Flag state: set_user noticed that RLIMIT_NPROC was exceeded\n");
  if((flags & PF_USED_MATH) != 0) printk(KERN_INFO "Flag state: if unset the fpu must be initialized before use\n");
  if((flags & PF_USED_ASYNC) != 0) printk(KERN_INFO "Flag state: used async_schedule*(), used by module init\n");
  if((flags & PF_NOFREEZE) != 0) printk(KERN_INFO "Flag state: this thread should not be frozen\n");
  if((flags & PF_FROZEN) != 0) printk(KERN_INFO "Flag state: frozen for system suspend\n");
  if((flags & PF_FSTRANS) != 0) printk(KERN_INFO "Flag state: inside a filesystem transaction\n");
  if((flags & PF_KSWAPD) != 0) printk(KERN_INFO "Flag state: I am kswapd\n");
  if((flags & PF_MEMALLOC_NOIO) != 0) printk(KERN_INFO "Flag state: Allocating memory without IO involved\n");
  if((flags & PF_LESS_THROTTLE) != 0) printk(KERN_INFO "Flag state: Throttle me less: I clean memory\n");
  if((flags & PF_KTHREAD) != 0) printk(KERN_INFO "Flag state: I am a kernel thread\n");
  if((flags & PF_RANDOMIZE) != 0) printk(KERN_INFO "Flag state: randomize virtual address space\n");
  if((flags & PF_SWAPWRITE) != 0) printk(KERN_INFO "Flag state: Allowed to write to swap\n");
  if((flags & PF_SPREAD_PAGE) != 0) printk(KERN_INFO "Flag state: Spread page cache over cpuset\n");
  if((flags & PF_SPREAD_SLAB) != 0) printk(KERN_INFO "Flag state: Spread some slab caches over cpuset\n");
  if((flags & PF_NO_SETAFFINITY) != 0) printk(KERN_INFO "Flag state: Userland is not allowed to meddle with cpus_allowed\n");
  if((flags & PF_MCE_EARLY) != 0) printk(KERN_INFO "Flag state: Early kill for mce process policy\n");
  if((flags & PF_MUTEX_TESTER) != 0) printk(KERN_INFO "Flag state: Thread belongs to the rt mutex tester\n");
  if((flags & PF_FREEZER_SKIP) != 0) printk(KERN_INFO "Flag state: Freezer should not count it as freezable\n");
  if((flags & PF_SUSPEND_TASK) != 0) printk(KERN_INFO "Flag state: This thread called freeze_processes and should not be frozen\n");
  return;
}
/* This function is called when the module is removed. */
void exit(void)
{
    printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init(init);
module_exit(exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("PID_INFO Module");
MODULE_AUTHOR("SGG");
