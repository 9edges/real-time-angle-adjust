#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MyI2C.h"
#include "MPU6050.h"
#include "Sqrt.h"
#include "stdlib.h"
#include "math.h"
#include "PWM.h"
#include "Servo.h"

#define G 9.8
#define PI 3.14159


uint16_t ID;
int16_t  AX,AY,AZ,GX,GY,GZ;     //GX,GY此处没有用
double ax,ay,az,gz;				//ax,ay,az,gz分别对应转为double格式后的MPU6050的数据

long double Pitch , Raw , Yaw;
long double P0,Y0;      		//上一组Pitch和Yaw
long double P,Y1;				//新的Pitch和Yaw

const long double a=90; 		//设定目标角度


int main(void){	
	OLED_Init();
	MPU6050_Init();
	Servo_Init();
	Servo_SetAngle(a);
	
	OLED_ShowString(1,1,"ID:");
	ID = MPU6050_GetID();
	OLED_ShowHexNum(1,4,ID,2);
	
	P = a ;
	
	while (1){		
		MPU6050_GetData(&AX,&AY,&AZ,&GX,&GY,&GZ);
		ax=(double)AX*16/32768*G;
		ay=(double)AY*16/32768*G;
		az=(double)AZ*16/32768*G;
		ax=(ax*100.0+0.5)/100;
		ay=(ay*100.0+0.5)/100;
		az=(az*100.0+0.5)/100;
		
		//当前的Pitch
		Pitch = (atan(-ax/Sqrt(az*az+ay*ay)))/(PI/180.0);
		
		//舵机需要的角度
		P = a  + Pitch;
		
		Servo_SetAngle(P);
		
		OLED_ShowSignedNum(2,1,Pitch,5);
		OLED_ShowSignedNum(3,1,P,5);
		
		Delay_ms(20);
	}
}
