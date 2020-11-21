> Author   
> [Safouene Mahfoudh](https://github.com/Safouene-Mahfoudh)


### B-L475E-IOT01A : Moving Servo with your hand.  

### How to control servo motor using STM32B-L475E-IOT01A Proximity sensor 

First of all we will start to explain how servos work. Servos can go from 0 to 180 degrees depending on the width of the pulse. Basically you need to keep the pulse (+5v) high for a particular amount of time. Few are listed bellow:

* 1 milliseconds and corresponds to 0 degrees.    
* 1.5 milliseconds and corresponds to 90 degrees.    
* 2 milliseconds and corresponds to 180 degrees.    

* The period between two pulses must be **20ms** or we can say the frequency of the pulse must be **50 Hz**.  


 Then we need to configurate our timer using STM32CubeMX. We will use TIM4 of the STM32B-L475E-IOT01A. I didn't check where TIM4 is connected (on wich bus APB1 or AB2) so i set the clock such that my TIM4 gets only 8 MHz on APB1 and APB2. My setup is bellow:  
 ![Timer](https://github.com/Safouene-Mahfoudh/B-L475E-IOT01A/blob/main/Moving_Servo_With_Accelerometer/Servo/Timer.png).  
 ![Clock](https://github.com/Safouene-Mahfoudh/B-L475E-IOT01A/blob/main/Moving_Servo_With_Accelerometer/Servo/Clock.png).

  



 As I mentioned above that the frequency must be 50 Hz, we need to divide the clock using prescalar and the ARR registers. Let’s calculate : ( 8MHz/50 Hz) = 160000 KHz. So now to get a  50 Hz of frequency, We need to divide this 160000 KHz between Prescalar and ARR. So we write 160-1 (**TIM_Period = timer_tick_frequency / PWM_frequency - 1**) in prescalar Register and 1000 in ARR.  
 To know more about PWM and how to calculate a PWM signal period you can visit this [link](https://github.com/Safouene-Mahfoudh/STM32F429I/blob/main/Confguration_Of%20_PWM_With_Values_30_50_100/Readme.md).

 For example,we want to give a pulse width of 1 ms, (1x1000/20) = 50%, we write **htim4.Instance->CCR3 = 50**. For 2 ms, It will be 100%, and for 1.5 ms, It will be 75%.  
 The reason why we choosed 1000 because it will act as 1000% Pulse Width and if we want to change the Pulse Width to any other value, all we have to do is write x% to CCR3 register.  


 Finnaly you can generate your code.  

### Important.  
You must add vl53l0x folder wich is containing all the required files (.c and .h) in your project target.  
* If you are using Keil µVISION, follow this [steps](https://www.keil.com/support/docs/1740.htm) to add all the necessary files.  
* If you are using IAR Embedded Workbench, follow this [steps](https://www.silabs.com/community/mcu/32-bit/knowledge-base.entry.html/2014/06/25/create_a_new_project-Geye#:~:text=Right%20click%20the%20source%20group,c%20file%20and%20press%20open.&text=6.1%3A%20It%20is%20time%20to,the%20CMSIS%20and%20emlib%20groups.) to add all the necessary files.  



 As we know the Servo move from 0° to 180° , we must convert the Proximity's value in sush a way when we move the hand up or down vertically, the angle of the servo change also, and to do this conversion we can use the map function which we quite often use in different embedded systems applications. The map function is commonly used as a built-in Arduino C function and it’s very handy in a wide range of applications. Mathematically, the mapping function is to find the corresponding value from a certain domain to another domain.    



  ```C

int16_t map(int16_t IN, int16_t INmin, int16_t INmax, int16_t OUTmin, int16_t OUTmax)
{
    return ((((IN - INmin)*(OUTmax - OUTmin))/(INmax -INmin)) + OUTmin);
}
```


The Commande to start the PWM on CCR3 is :
**HAL_TIM_PWM_Start( &htim4, TIM_CHANNEL_3 );**

During the execution of the main program, it is sometimes necessary to modify the Duty Cycle, So two instructions from the 
**__HAL** library will be needed to vary duty_cycle :
**__HAL_TIM_GET_AUTORELOAD(&htim4);**
**__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, duty_cycle);**