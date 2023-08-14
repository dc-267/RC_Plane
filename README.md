# RC-Plane

A simple PID controller is implemented.

Attitude feedback is taken from MPU 9250 sensor.

Input is taken from the RF transmitter which gives 1000 to 2000 analog values. To capture those values **pinchange** interrupt is used.
