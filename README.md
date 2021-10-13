# Flight Simulation for 3rd Person: Number 03

[Code inspired by this Udemy Course](https://www.udemy.com/course/graphics-with-modern-opengl/)

## Topic

The scene is derived from [scene #2](https://github.com/TallDave67/flight_sim_3p_02).

The code has been re-organized into appropriate sub-folders as the overall size of the project is growing.  The motion classes have also been re-organized and now the specific motion function for any object is set as a lambda function, so no need to have a derived class per object just to provide unique motion.

In the scene an x-wing fighter flies along a closed curve and makes smooth turns as it circles a rotating satellite above a spherical (mostly) moon. And now a transport ship joins him on a perpendicular axis in this game of circling the satellite.

Various lights accentuate the drama of the scene and the vastness of space is now filled with far away stars.

This scene repeats indefinitely.  So there is plenty of time to explore it by moving the camera using the following keys:

* W or Z: move camera forward (into screen)
* S move camera backwards (out of screen)
* A or Q: move camera left
* D: move camera right

* KEY_UP: angle camera up
* KEY_DOWN: angle camera down
* KEY_LEFT: angle camera left
* KEY_RIGHT: angle camera right

## Video Streaming

[FFMPEG Encoder](https://www.gyan.dev/ffmpeg/builds/)

[How to stream opengl framebuffer to ffmpeg](http://blog.mmacklin.com/2013/06/11/real-time-video-capture-with-ffmpeg/)

