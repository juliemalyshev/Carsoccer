# Assignment 2: Car Soccer
Julie Malyshev
malys005

I did all of my collision checking in the update simulation. For the different wall sides and ground, I used the normal
of each plane to calculate the reflection off of that surface. I wanted to note that I used the epsilon trick to make sure 
that the ball was readjusted in a way that would not cause it to enter the if statement again, but sometimes the ball
sticks to the ceiling regardless of this change. I know for a fact that the velocity is reversing and I can not think 
of anything else that would cause it to do that. I would appreciate any feedback on what I was doing wrong about this
isse. For the most part the ball is bouncing normally and friction is applied if the vector is large each time it bounces.
I did update the speed but I did not implement the turning of the car. 
