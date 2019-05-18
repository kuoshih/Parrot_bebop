# Parrot_bebop

![alt text](https://github.com/kuoshih/Parrot_bebop/blob/master/pictures/bebop.jpg)  

## Abstract
This code is for final projects of MA5041 Modern Artificial Intelligence and MA5039 Perception and Estimation in Robotics.
It is a sample code for Parrot Bebop2.
Before using this code, you should install bebop_autonomy for the Bebop2 driver.
https://bebop-autonomy.readthedocs.io/en/latest/index.html 
This code activates a node "Bebop_CODE". 
This node subscribes two topics -- bebop/odom and bebop/image_raw.
This node publishes one topics -- bebop/cmd_vel. 
You can access data from two Callback functions in src/listener.cpp.
The timer callback will send velocity commends to bebop.


## About us
Developer:   
* Kuo-Shih Tseng   
Contact: kuoshih@math.ncu.edu.tw   
Date: 2019/05/17  
License: Apache 2.0  


## Install bebop_autonomy
Create and initialize the workspace    
$ mkdir -p ~/bebop_ws/src && cd ~/bebop_ws    
$ catkin init    
$ git clone https://github.com/AutonomyLab/bebop_autonomy.git src/bebop_autonomy    
Update rosdep database and install dependencies (including parrot_arsdk)    
$ rosdep update    
$ rosdep install --from-paths src -i # Build the workspace    
$ catkin build   

## Download and compile the code
$ cd catkin_ws/src     
$ git clone https://github.com/kuoshih/Parrot_bebop      
$ cd ..     
$ catkin_make     


## Run the code   
Connect your WiFi to Bebop2 (Turn on Bebop's power)   
run the Bebop2 driver  
$roslaunch bebop_driver bebop_node.launch     
run the node for receiving and sending data  
$rosrun bebop listener     

The bebop will take off, moving foward, backward and land.   

## rviz
$rviz     
Press "Add" button in rviz, then select "image"  
Set topic as "bebop/image_raw."
You can see the real-time image from bebop  
![alt text](https://github.com/kuoshih/hypharos_minibot/blob/master/document/??)  
## Edit code  
You can edit src/listener.cpp for your project.
