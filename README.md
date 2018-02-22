# binary-search-trees
Non-Linear Data Structures  
Project 1  
Binary Tree  

# Prompt:
You are to implement the seven Dynamic Set Operators using a Binary Search Tree (BST).  
The nodes for your tree will contain a string (the “key”), an integer (a piece of “Satellite data,” to count
the number of times the string has been seen), and of course, left and right child pointers. You may
implement the parent pointer, if you think it will help you implement your solution, but it is not required.
Your program will consist of a loop within main, which will accept commands from the keyboard, and
execute them one-at-a-time.

The commands to be implemented are as follows:  
insert <string>  
delete <string>   
search <string>   
min   
max   
next <string>   
prev <string>   
list   
help   
exit   
  
# Details
Commands are case insensitive. If there is no min, max, next, or previous, the program outputs a blank line.  
List outputs an in order traversal of the list.  
Help outputs the list of commands.  
If the string to be deleted is not within the tree, the code will output <String> -1.  
