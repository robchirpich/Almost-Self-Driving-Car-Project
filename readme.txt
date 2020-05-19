The purpose of this final project was to combine our knowledge from the material we learned in lecture and in lab over the semester into an (almost) self-driving car as a prototype.

For this project, there was no camera attached to the RC car, but it would have been possible to attach a camera to the RC car and connect it to the Raspberry Pi 4 via a USB port and open the camera device instead of the input video file that we used to process real-time video.


*** [hardware set-up] The first part of this project was to connect all the pieces together as follows:

First, the LIDAR sensor was connected to the Raspberry Pi 4.

Second, the servo motor was connected to the HiFive1 board.

Third, serial connections were opened between the Raspberry Pi 4 and the HiFive1 board.


*** [comm.c] The second part of this project was to program the servo motor, LIDAR sensor, and the HiFive1 board to work together as follows:

First, the Raspberry Pi 4 had to perform a DNN inference every 50ms from an image that was read from the input video file which would be used to get a steering angle for the RC car. This steering angle was then sent to the HiFive1 board.

Second, the HiFive1 board read the steering angle and controlled the servo motor based on the steering angle it was given.

* (angle <= 30 degrees && angle >= -30 degrees) means ALL LED's are turned ON to produce a white color, indicating CENTER
* (angle > 30 degrees) means GREEN_LED turns ON, indicating RIGHT
* (angle < -30 degrees) means BLUE_LED turns ON, indicating LEFT

While the HiFive1 board is reading the steering angle and controlling the servo motor, the HiFive1 board is also reading distance values from the connected LIDAR sensor.

* (distance < 50 centimeters) means RED_LED turns ON, indicating that there was an object detected within 50 centimeters of the RC car and the servo motor is going to STOP


*** [dnn.py] The third part of this project was to program the Raspberry Pi 4 board to display the current video frame and the DNN's output steering angle onto the current video frame in real-time. We were allowed to use any UI library we wanted to make this happen.

* I did this using the included "cv2" library and the functions: putText(), imshow(), and waitKey().
