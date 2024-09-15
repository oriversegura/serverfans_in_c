### Introduction

This C script demonstrates how to use IPMITOOL to control the fan speeds of a server. IPMITOOL is a command-line interface for managing IPMI-compliant devices, including servers, workstations, and blade systems.

#### Prerequisites

- A server with IPMI support.
- IPMITOOL installed on your system.
- Same network as the server.
- Credentials of IPMI user with power user privileges.

### Breakdown:

# Get User Input:

Prompts the user for the server's IP address, Username and password.
Select the fan speed to set.

# Construct Commands:

Builds the IPMITOOL commands using the provided input.

# Execute Commands:

Forks child processes to execute each IPMITOOL command asynchronously.
Waits for each child process to finish.

# Error Handling:

Uses perror to print error messages if execvp or fork fail.

# Explanation of IPMITOOL Commands

ipmitool I lanplus: Selects the LAN+ interface for IPMI communication.
-H address: Specifies the server's IP address.
-U root: Sets the username for IPMI authentication (adjust as needed).
-P password: Sets the password for IPMI authentication.
raw 0x30 0x30: Specifies the raw command to execute.
0x01: Sets the command's target.
0x00: Sets the command's data.
0x02: Sets the command's data.
0xff fan: Sets the fan speed.

# Usage

- Compile the C code.
- Run the compiled executable.
- Enter the server's IP address, desired fan speed, and password.
- The script will execute the IPMITOOL commands to set the fan speed.
- Customization
- Adjust the IPMITOOL commands and fan speed values to match your specific server configuration.
- Add error handling for invalid input or unexpected responses from the server.
- Consider using a configuration file to store server details and fan speed options.

#Additional Notes

- Ensure that IPMITOOL is installed and configured correctly on your system.
- Refer to the IPMITOOL documentation for more details on available commands and options.
- This script provides a basic example. You may need to customize it further based on your specific requirements and server configuration.
