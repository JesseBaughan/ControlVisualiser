# **Control Visualisation Tool**  
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
