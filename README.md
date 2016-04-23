### OpenCL C++ Example - Encapsulated
This example encapsulates the C++ wrapper APIs of OpenCL into a class, `CLApp`. This class simplifies the coding with OpenCL.

#### Explanation 
##### class `CLApp`
This class encapsulates the OpenCL setup code, such as get the platforms and devices information, create command queue etc.

##### class `Algorithm`
This class encapsulates a specific algorithm. For example, if you would like to implement a `simple_add` function, you could put the control code such as creating buffer, launching the computation etc. in this class. In fact, in this project, it calls the class `CLApp` to do real OpenCL computing work.

#### How to use it
CMake(config + generate) `=>` Build `=>` CMake(config) again.

-- *Apr. 24, 2016* --

---
