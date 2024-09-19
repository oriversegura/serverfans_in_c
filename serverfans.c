#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Enumeration options
enum FanSpeed {
  FAN_SPEED_20 = 1,
  FAN_SPEED_30 = 2,
  FAN_SPEED_50 = 3,
  FAN_SPEED_80 = 4,
  FAN_SPEED_100 = 5

};

int main(void) {
  // check IPMI is installed all systems path
  char *path[] = {"/usr/bin/ipmitool", "/usr/local/bin/ipmitool", "C:\\ipmitool"};
  int i;
  for (i = 0; i < 3; i++) {
    if (access(path[i], X_OK) == 0) {
        printf("Ipmitool is installed on the system!\n");
    } else {
        if (i > 2 && access(path[i], X_OK) != 0) {
        printf("Ipmitool is not installed on the system!\n");
        }
    }
  }

  // variables to use
  char address[20], fan[10], user[20];
  char *password;

  // Message to user to set the ip of the server
  printf("Enter Server Address: \n");
  scanf("%s", address);

  // Message to user to set the ip of the server
  printf("Enter Server User: \n");
  scanf("%s", user);

  // Get Password of the server
  password = getpass("Enter Server Password: \n");
  if (setenv("PASSWORD_IPMI", password, 1) != 0) {
    perror("Error in set enviroment variable \n");
    return 1;
  }

  // Get and use password from enviroment variable
  char *password_env = getenv("PASSWORD_IPMI");

  // Declare variable for chose option
  int option;

  // print options
  printf("Select Fan Speed to Set\n");
  printf("1. Fans to 20 percent\n");
  printf("2. Fans to 30 percent\n");
  printf("3. Fans to 50 percent\n");
  printf("4. Fans to 80 percent\n");
  printf("5. Fans to 100 percent\n");
  printf("6. Exit Program\n");

  // get option to set fan speed
  scanf("%d", &option);

  // capture fan speed to set in RAW
  switch (option) {
  case FAN_SPEED_20:
    strcpy(fan, "0x14");
    printf("Setting fan speed to 20 percent\n");
    break;
  case FAN_SPEED_30:
    strcpy(fan, "0x1e");
    printf("Setting fan speed to 30 percent\n");
    break;
  case FAN_SPEED_50:
    strcpy(fan, "0x32");
    printf("Setting fan speed to 50 percent\n");
    break;
  case FAN_SPEED_80:
    strcpy(fan, "0x50");
    printf("Setting fan speed to 80 percent\n");
    break;
  case FAN_SPEED_100:
    strcpy(fan, "0x64");
    printf("Setting fan speed to 100 percent\n");
    break;
  case 6:
    printf("Exiting...\n");
    exit(1);
    break;
  default:
    printf("Invalid option selected. Exiting...\n");
    break;
  }

  // exec fan set command complete
  // Process 1
  pid_t pid1 = fork();
  if (pid1 == 0) {
    char *args1[] = {"ipmitool", "-I",   "lanplus", "-H",         address,
                     "-U",       user,   "-P",      password_env, "raw",
                     "0x30",     "0x30", "0x01",    "0x00",       NULL};
    printf("\n");
    execvp("ipmitool", args1);
    perror("execvp");
  } else if (pid1 < 0) {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  // Process 2
  pid_t pid2 = fork();
  if (pid2 == 0) {
    char *args2[] = {"ipmitool", "-I",   "lanplus",    "-H",  address, "-U",
                     user,       "-P",   password_env, "raw", "0x30",  "0x30",
                     "0x02",     "0xff", fan,          NULL};
    execvp("ipmitool", args2);
    perror("execvp");
  } else if (pid2 < 0) {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  // Delete Enviroment Variable before program end
  unsetenv("PASSWORD_IPMI");

  // Fan Speed its correct set Message
  printf("Fan Speed set successfully!\n");
}
