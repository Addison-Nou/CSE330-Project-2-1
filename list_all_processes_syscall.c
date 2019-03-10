#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <linux/init.h>
#include <stdio.h>

asmlinkage long sys_list_all_processes(int user_uid, int* userspace_PID_array_user, int* userspace_PRIO_array_user, char* userspace_CLS_array_user, char* userspace_CMD_array_user)
{

   //char* u = argv[1];
   struct task_struct* p;
   int number_of_processes = 0;
   //char* y = get_user(y, *u);

   for_each_process(p)
   {

      // If p->cred->uid.val == User's UID, then increment number_of_processes;
      if(p->cred->uid.val == user_uid)
          number_of_processes++;
   }

   // Create 4 arrays of values, where array[i]
   // in each array contains the i'th process' attribute

   int* PID_array_ptr = malloc( number_of_processes * sizeOf(int));
   int* PRIO_array_ptr = malloc( number_of_processes * sizeOf(int));
   char* CLS_array_ptr = malloc( number_of_processes * sizeOf(char) * 10); // ONLY WORKS IF CLS NAMES ARE SHORTER THAN 10 CHARACTERS
   char* CMD_array_ptr = malloc( number_of_processes * sizeOf(char) * 40); // ONLY WORKS IF EXECUTABLE NAMES ARE SHORTER THAN 40 CHARACTERS


   int array_counter = 0;
   
   for_each_process(p)
   {
      // Compare owner UID. If equivalent to UID, get PID, PRIO, CLS, and CMD.
      if(p->cred->uid.val == user_uid)
      {
         PID_array_ptr[array_counter] = p->pid;  //provides process id
         PRIO_array_ptr[array_counter] = p->prio;   //provides priority of the process
         CLS_array_ptr[array_counter * 10] = p->policy;   //provides policy (class) of the process
         CMD_array_ptr[array_counter * 40] = p->comm;  //provides command of the process
         
         array_counter++;
      }
   }

    // unsigned long copy_to_user(void *to, const void *from, int n);
    
    // copies n bytes from the kernel space memory
    // starting at address from to the user space memory starting at address to.
    // returns number of bytes that could not be copied. On success, this will be zero.

    // put_user(x, addr) the addresses of each array and the counter

    // PID
    if (copy_to_user(userspace_PID_array_user, PID_array_ptr, number_of_processes * sizeOf(int)))
    {
        std::cout << "PID ain't fucked, coach" << std::endl;
    }
    
    if (put_user(PID_array_ptr, userspace_PID_array_user))
    {
        std::cout << "PID's not fucked 2, electric boogaloo" << std::endl;
    }
    
    //////////////////////////////////////////

    // PRIO
    if (copy_to_user(userspace_PRIO_array_user, PRIO_array_ptr, number_of_processes * sizeOf(int)))
    {
        std::cout << "PRIO ain't fucked, coach" << std::endl;
    }
    
    if (put_user(PRIO_array_ptr, userspace_PRIO_array_user))
    {
        std::cout << "PRIO's not fucked 2, electric boogaloo" << std::endl;
    }

    //////////////////////////////////////////

    // CLS
    if (copy_to_user(userspace_CLS_array_user, CLS_array_ptr, number_of_processes * sizeOf(char) * 10))
    {
        std::cout << "CLS ain't fucked, coach" << std::endl;
    }
    
    if (put_user(CLS_array_ptr, userspace_CLS_array_user))
    {
        std::cout << "CLS's not fucked 2, electric boogaloo" << std::endl;
    }

    //////////////////////////////////////////

    // CMD
    if (copy_to_user(userspace_CMD_array_user, CMD_array_ptr, number_of_processes * sizeOf(char) * 40))
    {
        std::cout << "CMD ain't fucked, coach" << std::endl;
    }
    
    if (put_user(CMD_array_ptr, userspace_CMD_array_user))
    {
        std::cout << "CMD's not fucked 2, electric boogaloo" << std::endl;
    }


   return 0;
   
}