#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include "list_all_processes_userspace.h"


int main(char* argv[]){
   
   int* userspace_PID_array_ptr;
   int* userspace_PRIO_array_ptr;
   char* userspace_CLS_array_ptr;
   char* userspace_CMD_array_ptr;
   
   char* u = argv[1];

   int user_uid = getpwnam(u)->pw_uid;

   long int ret_status = syscall(398, user_uid, *userspace_PID_array_ptr, *userspace_PRIO_array_ptr, *userspace_CLS_array_ptr, *userspace_CMD_array_ptr);

   if (ret_status == 0)
   {
      printf("System call worked, fam.");
   }
   else
   {
      printf("FAILURE. YOU SUCK");
   }
   return 0;
}

