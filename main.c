#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <math.h>
#include "/home/pi/autonomousDriving/linux_kbhit.h"

int dcmotor_FR_1 = 1; //gpio pin number of Dcmotor
int dcmotor_FR_2 = 4;
int dcmotor_BR_1 = 5;
int dcmotor_BR_2 = 6;
int dcmotor_FL_1 = 7;
int dcmotor_FL_2 = 0;
int dcmotor_BL_1 = 2;
int dcmotor_BL_2 = 3;

int red = 21; //gpio pin number of LED
int green = 22;
int blue = 23;

int ultrasonic_R_trig = 24; //gpio pin number of Ultrasonic sensor
int ultrasonic_R_echo = 25;
int ultrasonic_L_trig = 26;
int ultrasonic_L_echo = 27;
int ultrasonic_F_trig = 28;
int ultrasonic_F_echo = 29;

float start_time_R, start_time_L, start_time_F, end_time_R, end_time_L, end_time_F, distance_R, distance_L, distance_F;

int* speed_level; //Velocity level of rc czr (0 : STOP, 4 : Maximum Velocity)
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

void UP(){
	
		speed_level[0] = speed_level[0] + 1;

	return;
}

void DOWN(){

		speed_level[0] = speed_level[0] - 1;
	
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
	speed_level[0] = 2;
	
	while(1){
		
		message = linux_kbhit();
		printf("message = %c\n",message);
		
		if(message == 'F'){
			FORWARD(speed_level);
			GREEN();
		}

		else if(message == 'B'){
			BACKWARD(speed_level);
			GREEN();
		}

		else if(message == 'R'){
			ROTATE_R();
			BLUE();
		}

		else if(message == 'L'){
			ROTATE_L();
			BLUE();
		}

		else if(message == 'S'){
			STOP();
			RED();
		}
		
		else if(message == 'U'){
			STOP();
			UP();
		}

		else if(message == 'D'){
			STOP();
			DOWN();
		}	
		
		else if(message == 'A'){
			while(1){	
				FORWARD(speed_level);
				GREEN();
		
				ULTRASONIC_R();
				ULTRASONIC_L();
				ULTRASONIC_F();

				if(distance_L < 15){
					STOP();
					RED();
					delay(1000);
			
					ULTRASONIC_L();
					ULTRASONIC_F();
			
					float p = distance_F + 12.5; //Height of rc car = 25
					float q = distance_L + 11.2; //Length of rc car = 22.4
					float cos_alpha = p / sqrt(pow(p,2)+pow(q,2));
			
					while(fabs(distance_L -(q * cos_alpha - 11.2)) > 0.5){
						ROTATE_R();
						BLUE();
						ULTRASONIC_L();
					}
					STOP();
					RED();
					delay(1000);
			
					ROTATE_R();
					BLUE();
					delay(500);
			
					FORWARD(speed_level);
					GREEN();
					delay(500);
		
					ROTATE_L();
					BLUE();
					delay(500);
				}
		
				if(distance_R < 15){
			
					STOP();
					RED();
					delay(1000);
			
					ULTRASONIC_R();
					ULTRASONIC_F();
			
					float p = distance_F + 12.5;
					float q = distance_R + 11.2;
					float cos_alpha = p / sqrt(pow(p,2)+pow(q,2));
			
					while(fabs(distance_R - (q * cos_alpha - 11.2)) > 0.5){
						ROTATE_L();
						BLUE();
						ULTRASONIC_R();
					}

					STOP();
					RED();
					delay(1000);
			
					ROTATE_L();
					BLUE();
					delay(500);
			
					FORWARD(speed_level);
					GREEN();
					delay(500);
			
					ROTATE_R();
					BLUE();
					delay(500);
				}
		
				if(distance_F < 20 && distance_L < distance_R){
			
					STOP();
					RED();
					delay(1000);
			
					while(fabs(distance_F - distance_L - 1.3) > 2){
				 
						ROTATE_R();
						BLUE();
						ULTRASONIC_L();
					}
				}
				
				if(distance_F < 20 && distance_L > distance_R){
			
					STOP();
					RED();
					delay(1000);
			
					while(fabs(distance_F - distance_R - 1.3) > 2){
				
						ROTATE_L();
						BLUE();
						ULTRASONIC_R();
					}
				}
			}
		}	
		printf("speed_level = %d\n",speed_level[0]);
	}
	return 0;
} //Khumsfcr
