# 2nd assignment for ADA

Author: Søren Riisom Pedersen  
Contact: soepe13@student.sdu.dk  

Github project: git@github.com:PoSRP/ada-portfolio2.git  

## ADA Portfolio 2 Description

### 1 Knight Problem
Jakob and Jens are playing chess and they want to figure out what is the minimum number of moves it takes for a knight at a given position to reach another position.  
The legal moves of a knight can be seen in figure 1. Your method should work for arbitrary sizes of chess boards.  
To solve this problem, you must implement your own classes, Tree and Node. You should also provide a public method that allows your instructor to test your work. Just as shown below:  
```
int minimum_steps(int board_height,  
                  int board_width,  
                  int knight_start_x_position,  
                  int knight_start_y_position,  
                  int knight_end_x_position,  
                  int knight_end_y_position)
```
  An example could be for the knight in figure 1, then the input would be:  
    `minimum_steps(8, 8, 4, 4, 3, 2);`  
  You do not have to write your own driver.  
  Just make sure that your code complies with the previously mentioned interface.  

### 2 Formalia
You  should  only  hand  in  ONE  file  in  the  form  of  .zip.  
The  name  of  the  file should be your SDU username (e.g.  jeive17).  
In the .zip-file, you include all the relevant source (.cpp, .h, .hpp, .java). So only the programming languages C++and Java is acceptable and use only the standard libraries. So your program should be able to compile using a standard compiler. The portfolio should be completed and handed in individually.  
