# RTIOW
My own implementation of [Peter Shirley's Ray Tracing In One Weekend + Ray Tracing the Next Week](https://github.com/RayTracing/raytracing.github.io).

The project was very interesting as it required the application of both my Mathematics / Physics background as well as my Computing Science background.

At the time of working on this project, there was also a strange issue with the lighting that occured in my final render. Although I double-checked with the original example source code and verified that my code was consistent, eventually I tracked the issue down to an integer overflow due to very bright areas surpassing the maximum value of an unsigned 8-bit integer (255). You can see the before/after difference in applying this fix below:

![](https://dsgn.nadon.io/3d/RTIOW_pre-patched.png)

![](https://dsgn.nadon.io/3d/RTIOW.png)
