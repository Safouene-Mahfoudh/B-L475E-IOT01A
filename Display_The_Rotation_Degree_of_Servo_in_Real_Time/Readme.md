> Author   
> [Safouene Mahfoudh](https://github.com/Safouene-Mahfoudh)


### B-L475E-IOT01A : Degree Rotation of Servo Motor in real time.  

In this example I used the values of the proximity sensor of B-L475E-IOT01A , So You need to write a program like this [one](https://github.com/Safouene-Mahfoudh/B-L475E-IOT01A/tree/main/Moving_The_Servo_Motor_Using_Your_Hand) to make this interface work.  

This is the interface how is looking :  

![Interface](https://github.com/Safouene-Mahfoudh/B-L475E-IOT01A/blob/main/Display_The_Rotation_Degree_of_Servo_in_Real_Time/interface.png).  

Remember that Servos can go from 0 to 180 degrees depending on the width of the pulse.So you need to keep the pulse (+5v) high for a particular amount of time. Few are listed bellow:

* 1 milliseconds and corresponds to 0 degrees.    
* 1.5 milliseconds and corresponds to 90 degrees.    
* 2 milliseconds and corresponds to 180 degrees.  

* The frequency of the pulse must be **50 Hz** or the period between two pulses must be **20ms**.  

To know more about how to give a Pulse Width you can visit this [link](https://github.com/Safouene-Mahfoudh/B-L475E-IOT01A/blob/main/Moving_The_Servo_Motor_Using_Your_Hand/Readme.md) or this [link](https://github.com/Safouene-Mahfoudh/B-L475E-IOT01A/blob/main/Moving_Servo_With_Accelerometer/Readme.md)
To know more about PWM and how to calculate a PWM signal period you can visit this [link](https://github.com/Safouene-Mahfoudh/STM32F429I/blob/main/Confguration_Of%20_PWM_With_Values_30_50_100/Readme.md).  

As mentionned above on the interface , you can see **Pulse Width** wich is represent the pulse width sent in real time to our interface.So when the Pulse Width is changed the Servo turn in a specific direction and we can see the rotation of the Servo in real time.  


