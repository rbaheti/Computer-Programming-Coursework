Assignment 4

Question:  
The purpose of this assignment is to use threads to solve a problem.   1. Implement a robot that executes the given commands. Each command requires the robot to move one of its 4 arms in a certain way.  
2. Read the commands from the given XML file.  
3. Each command is encoded in 2 bytes. The bits in the 2 bytes should be interpreted as described below:   Byte1   0 1 = left   1 2 = right   2 4 = up   3 8 = down   4 16 = clockwise   5 32 = counterclockwise   6 64 = fast   7 128 = slow   Byte2   0 - 255 Degrees of rotation   4. Use a thread to execute the commands.  