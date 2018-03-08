# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

# Write up


## Explanations

PID - Controller:

### Setting the controller parameters:

#### Description

**P = proportional.**
The proportional parameter outputs a value that is proportional to the actual error. Using the P-parameter, the car's steering change will always be proportional to the car's distance from the center of the lane. That means the higher the p-value, the greater the steering angle. A too high P-value would will increase the tendency to overshoot and lead to an unstable driving behaviour.

**I = integral.** The I component helps offset the bias in the CTE that can be caused by steering drift. Small I-values will help to prevent the car from oszillating around the center line by taking into account the duration of the error. The bias can also be called steady-state error coming from e.g. mechanical effects.

**D = differential.** Sometimes the P component overshoots the center of the line. To mitigate the impact of oscillation we set the differential component as a kind of a damping factor for the proportional parameter. A well-chosen D-parameter helps to stabilize the car in the simulator. The differential term describes the slope of the error, the derivative between two time steps. By setting it accordingly, it helps to stabilize the driving behaviour of the car.

### How I set the parameters

#### Proportional parameter
I decided to manually tune the parameters because the twiddle algorithm did not work out as I wished. First I increased the proportional factor until the car in the simulator starts to oscillate around the center of the lane. I started with 0.01 and ended at 0.5.
#### Integral parameter
As described above the I-parameter compensates the bias in the CTE, e.g. due to mechanical issues. Since the car in the simulator does not have a certain mechanical bias, therefore I kept it at 0.0 at the beginning. Next I started to tune the differential parameter.
#### Differential parameter
I started to increase the differential parameter until the transient oscillation was sufficient fast. It was kind of a fine-tuning to not over-damp or under-damp the car control. After finding a suitable paramter that shows a good performance in the simulator I startet to increase the integral parameter by very small amounts.

The following animation perfectly describes the approach for manually tuning the PID parameters:
![](https://upload.wikimedia.org/wikipedia/commons/3/33/PID_Compensation_Animated.gif)

source: https://www.wikiwand.com/en/PID_controller

### Finally chosen paramters
At the end I came up with the following parameters:

- P-parameter: 0.13
- I-parameter: 0.0003
- D-parameter: 5


## Visualization of the PID-controller performance

I recorded two videos that show the PID-controller in action. One is with the initially set throttle value of 0.3 (well, in fact I increased it to 0.38) and another video with an additional implemented PID-controller for the throttle/braking. I significantly increased the throttle value here like it was told in the lesson to release the "inner Vin Diesel".

To be fair: The parameters for the second video (with more sophisticated throttle value could be further optimized to mitigate the under-damped oscillation.

**Please mute the sound, otherwise you will hear noise from TV ;-)**

#### With project throttle parameter of 0.3 - 0.4
[https://youtu.be/-IV9dNSFzaY](https://youtu.be/-IV9dNSFzaY "Video 1")

#### With throttle parameter "inner Vin Diesel"
[https://youtu.be/tkOfDjGxsOw](https://youtu.be/tkOfDjGxsOw)