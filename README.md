# Introduction

This C script its a simple way to use IPMITOOL to control the fan speeds of a server. IPMITOOL is a command-line interface for managing IPMI-compliant devices, including servers, workstations, and blade systems.

## Prerequisites

- A server/workstation with IPMI support.
- IPMITOOL installed on your system.(aviable for all systems)
- Same network as the server.
- Credentials of IPMI user with power user privileges.

## Breakdown

### Get User Input

First verify that the ipmi utility is on the correct path, after this, prompts the user for the server's IP address, Username and password.
After the necessary info comes the menu with the selection of the fan speed to set.

### Construct Commands

Builds the IPMITOOL commands using the provided input.

### Execute Commands

Forks child processes to execute each IPMITOOL command asynchronously.
Waits for each child process to finish.

### Error Handling

Use error handling such as perror, to display a message on the output of any of the commands or system calls to be executed.

### Explanation of IPMITOOL Commands

ipmitool I lanplus: Selects the LAN+ interface for IPMI communication.
-H address: Specifies the server's IP address.
-U user: Sets the username for IPMI authentication.
-P password: Sets the password for IPMI authentication.
raw: Specifies the raw command to execute.

### Usage

- Make sure you have installed ipmitool
- Compile the C code using your favorite compiler (i pref Clang).
- Run the compiled executable.
- Enter the server's ip address, user, and password.
- Chose your fan speed to set.
- The script will execute the IPMITOOL commands to set the fan speed.

### Additional Notes

- IPMITOOL is an open source tool, maintained by IBM and used to manage Dell, HP and other branded servers/workstations.
ß- Refer to the IPMITOOL documentation for more details on available commands and options.
- This script provides a basic example. You may need to customize it further based on your specific requirements and server configuration.
