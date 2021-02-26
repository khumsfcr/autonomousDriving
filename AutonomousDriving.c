#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <math.h>

int dcmotor_FR_1 = 1;
int dcmotor_FR_2 = 4;
int dcmotor_BR_1 = 5;
int dcmotor_BR_2 = 6;
int dcmotor_FL_1 = 7;
int dcmotor_FL_2 = 0;
int dcmotor_BL_1 = 2;
int dcmotor_BL_2 = 3;

int red = 21;
int green = 22;
int blue = 23;

int ultrasonic_R_trig = 24;
int ultrasonic_R_echo = 25;
int ultrasonic_L_trig = 26;
int ultrasonic_L_echo = 27;
int ultrasonic_F_trig = 28;
int ultrasonic_F_echo = 29;

float start_time_R, start_time_L, start_time_F, end_time_R, end_time_L, end_time_F, distance_R, distance_L, distance_F;

int* speed_level;
char message;

void FORWARD(int* speed_level){
	
		softPwmWrite(dcmotor_FR_1,0);
		softPwmWrite(dcmotor_FR_2,50*speed_level[0]);
		softPwmWrite(dcmotor_BR_1,50*speed_level[0]);
		softPwmWrite(dcmotor_BR_2,0);
		softPwmWrite(dcmotor_FL_1,0);
		softPwmWrite(dcmotor_FL_2,50*speed_level[0]);
		softPwmWrite(dcmotor_BL_1,50*speed_level[0]);
		softPwmWrite(dcmotor_BL_2,0);

	return;
}

void BACKWARD(int* speed_level){
	
		softPwmWrite(dcmotor_FR_1,50*speed_level[0]);
		softPwmWrite(dcmotor_FR_2,0);
		softPwmWrite(dcmotor_BR_1,0);
		softPwmWrite(dcmotor_BR_2,50*speed_level[0]);
		softPwmWrite(dcmotor_FL_1,50*speed_level[0]);
		softPwmWrite(dcmotor_FL_2,0);
		softPwmWrite(dcmotor_BL_1,0);
		softPwmWrite(dcmotor_BL_2,50*speed_level[0]);
	
	return;
}

void ROTATE_R(){

		softPwmWrite(dcmotor_FR_1,200);
		softPwmWrite(dcmotor_FR_2,0);
		softPwmWrite(dcmotor_BR_1,0);
		softPwmWrite(dcmotor_BR_2,200);
		softPwmWrite(dcmotor_FL_1,0);
		softPwmWrite(dcmotor_FL_2,200);
		softPwmWrite(dcmotor_BL_1,200);
		softPwmWrite(dcmotor_BL_2,0);

	return;
}

void ROTATE_L(){

		softPwmWrite(dcmotor_FR_1,0);
		softPwmWrite(dcmotor_FR_2,200);
		softPwmWrite(dcmotor_BR_1,200);
		softPwmWrite(dcmotor_BR_2,0);
		softPwmWrite(dcmotor_FL_1,200);
		softPwmWrite(dcmotor_FL_2,0);
		softPwmWrite(dcmotor_BL_1,0);
		softPwmWrite(dcmotor_BL_2,200);

	return;
}

void STOP(){
	
		softPwmWrite(dcmotor_FR_1,0);
		softPwmWrite(dcmotor_FR_2,0);
		softPwmWrite(dcmotor_BR_1,0);
		softPwmWrite(dcmotor_BR_2,0);
		softPwmWrite(dcmotor_FL_1,0);
		softPwmWrite(dcmotor_FL_2,0);
		softPwmWrite(dcmotor_BL_1,0);
		softPwmWrite(dcmotor_BL_2,0);
	
	return;
}

void RED(){
	
		digitalWrite(red,LOW);
		digitalWrite(green,HIGH);
		digitalWrite(blue,HIGH);
	
	return;
}

void GREEN(){
	
		digitalWrite(red,HIGH);
		digitalWrite(green,LOW);
		digitalWrite(blue,HIGH);
	
	return;	
}

void BLUE(){
	
		digitalWrite(red,HIGH);
		digitalWrite(green,HIGH);
		digitalWrite(blue,LOW);
	
	return;
}

void ULTRASONIC_R(){
	

	digitalWrite(ultrasonic_R_trig,0);
	digitalWrite(ultrasonic_R_trig,1);
	delayMicroseconds(10);
	digitalWrite(ultrasonic_R_trig,0);

	while(digitalRead(ultrasonic_R_echo) != 1);
	start_time_R = micros();

	while(digitalRead(ultrasonic_R_echo) != 0);
	end_time_R = micros();

	distance_R = (end_time_R - start_time_R)/58.;

	printf("Distance R : %fcm\n",distance_R);
        
	delay(100);
	
	return;
}

void ULTRASONIC_L(){
	
	digitalWrite(ultrasonic_L_trig,0);
	digitalWrite(ultrasonic_L_trig,1);
	delayMicroseconds(10);
	digitalWrite(ultrasonic_L_trig,0);

	while(digitalRead(ultrasonic_L_echo) != 1);
	start_time_L = micros();

	while(digitalRead(ultrasonic_L_echo) != 0);
	end_time_L = micros();

	distance_L = (end_time_L - start_time_L)/58.;

	printf("Distance L : %fcm\n",distance_L);
        
	delay(100);
	
	return;
}

void ULTRASONIC_F(){
	
	digitalWrite(ultrasonic_F_trig,0);
	digitalWrite(ultrasonic_F_trig,1);
	delayMicroseconds(10);
	digitalWrite(ultrasonic_F_trig,0);

	while(digitalRead(ultrasonic_F_echo) != 1);
	start_time_F = micros();

	while(digitalRead(ultrasonic_F_echo) != 0);
	end_time_F = micros();

	distance_F = (end_time_F - start_time_F)/58.;

	printf("Distance F : %fcm\n",distance_F);
        
	delay(100);
	
	return;
}

int main(){
	
	if(wiringPiSetup() == -1){
		return 0;
	}
	
	pinMode(dcmotor_FR_1,OUTPUT);
	pinMode(dcmotor_FR_2,OUTPUT);
	pinMode(dcmotor_BR_1,OUTPUT);
	pinMode(dcmotor_BR_2,OUTPUT);
	pinMode(dcmotor_FL_1,OUTPUT);
	pinMode(dcmotor_FL_2,OUTPUT);
	pinMode(dcmotor_BL_1,OUTPUT);
	pinMode(dcmotor_BL_2,OUTPUT);
	pinMode(red,OUTPUT);
	pinMode(green,OUTPUT);
	pinMode(blue,OUTPUT);
	pinMode(ultrasonic_R_trig,OUTPUT);
	pinMode(ultrasonic_R_echo,INPUT);
	pinMode(ultrasonic_L_trig,OUTPUT);
	pinMode(ultrasonic_L_echo,INPUT);
	pinMode(ultrasonic_F_trig,OUTPUT);
	pinMode(ultrasonic_F_echo,INPUT);

	softPwmCreate(dcmotor_FR_1,0,200);
	softPwmCreate(dcmotor_FR_2,0,200);
	softPwmCreate(dcmotor_BR_1,0,200);
	softPwmCreate(dcmotor_BR_2,0,200);
	softPwmCreate(dcmotor_FL_1,0,200);
	softPwmCreate(dcmotor_FL_2,0,200);
	softPwmCreate(dcmotor_BL_1,0,200);
	softPwmCreate(dcmotor_BL_2,0,200);

	speed_level = (int*)malloc(sizeof(int)*2);
	speed_level[0] = 4;
	
	while(1){
		
		FORWARD(speed_level);
		GREEN();
		
		ULTRASONIC_R();
		ULTRASONIC_L();
		ULTRASONIC_F();

	/*	float distance_R2 = distance_R;
		float distance_L2 = distance_L;
	        
		FORWARD(speed_level);
		GREEN();
		
		ULTRASONIC_R();
		ULTRASONIC_L();
		ULTRASONIC_R(); */

		if(distance_L < 5){
			STOP();
			RED();
			delay(1000);
			
			ULTRASONIC_L();
			ULTRASONIC_F();
			
			float p = distance_F + 12.5;
			float q = distance_L + 11;
			float cos_alpha = p / sqrt(pow(p,2)+pow(q,2));
			
			while(distance_L != q * cos_alpha - 11){
				ROTATE_R();
				BLUE();
				ULTRASONIC_L();
			}
		}
		
		if(distance_R < 5){
			
			STOP();
			RED();
			delay(1000);
			
			ULTRASONIC_L();
			ULTRASONIC_F();
			
			float p = distance_F + 12.5;
			float q = distance_L + 11;
			float cos_alpha = p / sqrt(pow(p,2)+pow(q,2));
			
			while(distance_R != q * cos_alpha - 11){
				ROTATE_L();
				BLUE();
				ULTRASONIC_R();
			}
		}

		/*if(fabs(distance_R - distance_R2) > 1){
			
			STOP();
			RED(); */
		
		if(distance_F < 5 && distance_L < distance_R){
			
			STOP();
			RED();
			delay(1000);
			
			while(distance_L != distance_F){
				
				ROTATE_R();
				BLUE();
				ULTRASONIC_L();
			}
		}
				
		if(distance_F < 5 && distance_L > distance_R){
			
			STOP();
			RED();
			delay(1000);
			
			while(distance_R != distance_F){
				
				ROTATE_L();
				BLUE();
				ULTRASONIC_R();
			}
		}
	}
	return 0;
}
