#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void slowFans()
{
    // variables to use
    char address[20], user[20], password[20], option[10], fan[10];

    // Message to user to set the ip of the server
    printf("Enter Server Address: \n");
    scanf("%s", address);

    // Message to user to set the ip of the server
    printf("Enter Server User: \n");
    scanf("%s", user);   

    // Get Password of the server
    printf("Enter Server Password: \n");
    scanf("%s", password);
    
    // print options
    printf("Select Fan Speed to Set\n");
    printf("1. Fans to 20 percent\n");
    printf("2. Fans to 30 percent\n");
    printf("3. Fans to 50 percent\n");
    printf("4. Fans to 80 percent\n");
    printf("5. Fans to 100 percent\n");
    printf("6. Exit Program\n");
   
    // get option to set fan speed
    scanf("%s", option);   

    // convert option to int
    long int option_int = strtol(option, NULL, 10);
    if (option_int == 0 && *option != '0'){
        printf("Invalid option selected. Exiting...\n");
        return;
    }
        // capture fan speed to set
        switch (option_int)
        {
        case 1:
            strcpy(fan, "0x14");
            printf("Setting fan speed to 20 percent\n");
            break;
        case 2:
            strcpy(fan, "0x1e");
            printf("Setting fan speed to 30 percent\n");
            break;
        case 3:
            strcpy(fan, "0x32");
           printf("Setting fan speed to 50 percent\n");
            break;
        case 4:
            strcpy(fan, "0x50");
            printf("Setting fan speed to 80 percent\n");
            break;
        case 5:
            strcpy(fan, "0x64");
            printf("Setting fan speed to 100 percent\n");
            break;
        case 6:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid option selected. Exiting...\n");
            break;
        }
        
        
        // exec fan command complete
        //char* command = "ipmitool";
        pid_t pid1 = fork();
        if (pid1 == 0) 
        {
        char* args1[] = {"ipmitool", "-I", "lanplus", "-H", address, "-U", user, "-P", password, "raw", "0x30", "0x30", "0x01", "0x00", NULL};  
        printf("\n");
        execvp("ipmitool", args1);
        perror("execvp");            
        }
        else if (pid1 < 0)
        {
        perror("fork");
        exit(EXIT_FAILURE);
        }
        
        pid_t pid2 = fork();
        if (pid2 == 0) {
        char* args2[] = {"ipmitool", "-I", "lanplus", "-H", address, "-U", user, "-P", password, "raw", "0x30", "0x30", "0x02", "0xff", fan, NULL};
        execvp("ipmitool", args2);
        perror("execvp");
        } else if (pid2 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
        }
        //Fan Speed set Message
        printf("Fan Speed Set successfully!\n");
        // end program
        printf("Program finished correctly!\n");
    }

    int main(void)
    {
        slowFans();
        return 0;
    }
