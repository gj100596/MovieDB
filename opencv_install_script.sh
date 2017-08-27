# Removing  older versions of OpenCV
sudo apt-get remove libopencv
sudo apt-get remove opencv

#First, build tools
sudo apt-get install build-essential

#Then the required packages:
sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev

#Downloading OpenCV source files
#download sources into “/opt/” folder
cd /opt
sudo git clone https://github.com/Itseez/opencv.git
sudo git clone https://github.com/Itseez/opencv_contrib.git

#Pre-Build Configuration
cd /opt/opencv
mkdir release
cd release
cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D OPENCV_EXTRA_MODULES_PATH=/opt/opencv_contrib/modules /opt/opencv/

#Make and install
cd /opt/opencv/release
sudo make
sudo make install

#your installation should be done by now! To check, following command should print "3.1.0"	
pkg-config --modversion opencv

