# **Control Visualisation Tool**
## Overview
The goal of this project is to provide an easy GUI based tool for creating nice visualisations of control approaches.
For example, a user may be working with an L1 controller but doesn't yet have a deep understanding of how the controller
works for various system states. Using this tool, the user is able to input various system states and simluate how the 
controller would respond.

## Current state
I am still in the process of building the underlying engine that is based heavily off of Cherrno's Hazel engine. One 
all the requried functionality of the engine is added I will begin to build the necessary abstractions for creating the 2D 
control visualisations.

## Install dependencies  
### Linux:   
sudo apt-get update  
#### GLFW3
sudo apt-get install libglfw3  
sudo apt-get install libglfw3-dev  
#### GLEW
sudo apt install libglew-dev  
## Building project
cd build  
cmake ..  
make all  
./ControlVisualiser  

**Single step build process**  
cmake --build . --target ControlVisualiser  
<br/>
Replace the target name with ControlVisualiser_tst to build unit tests  
cmake --build . --target ControlVisualiser_tst
<br/>
## Running unit tests  
./test/ControlVisualiser_tst  
