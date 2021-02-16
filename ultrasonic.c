#include <stdio.h>
#include <wiringPi.h>

int ultrasonic_R_trig = 24;
int ultrasonic_R_echo = 25;
int ultrasonic_L_trig = 26;
int ultrasonic_L_echo = 27;
int ultrasonic_F_trig = 28;
int ultrasonic_F_echo = 29;

float start_time_R;
float start_time_L;
float start_time_F;
float end_time_R;
float end_time_L;
float end_time_F;
float distance_R;
float distance_L;
float distance_F;

/*
void ULTRASONIC(){
	
	while(1){
		
		
		start_time_R = -1;
		start_time_L = -1;
		start_time_F = -1;
		end_time_R = -1;
		end_time_L = -1;
		end_time_F = -1;
		distance_R = -1;
		distance_L = -1;
		distance_F = -1;
		
		digitalWrite(ultrasonic_R_trig,LOW);
		digitalWrite(ultrasonic_L_trig,LOW);
		digitalWrite(ultrasonic_F_trig,LOW);
	
		digitalWrite(ultrasonic_R_trig,HIGH);
		delayMicroseconds(10);
		
		digitalWrite(ultrasonic_L_trig,HIGH);
		delayMicroseconds(10);
		
		digitalWrite(ultrasonic_F_trig,HIGH);
 		delayMicroseconds(10);

		digitalWrite(ultrasonic_R_trig,LOW);
		digitalWrite(ultrasonic_L_trig,LOW);
		digitalWrite(ultrasonic_F_trig,LOW);
		
		
		while(digitalRead(ultrasonic_R_echo) != 1);
	       	start_time_R = micros();
		while(digitalRead(ultrasonic_L_echo) != 1);
		start_time_L = micros();
		while(digitalRead(ultrasonic_F_echo) != 1);
		start_time_F = micros();

		printf("%f %f %f\n",start_time_R,start_time_L,start_time_F);

		while(digitalRead(ultrasonic_R_echo) != 0);
	       	end_time_R = micros();
		while(digitalRead(ultrasonic_L_echo) != 0);
		end_time_L = micros();
		while(digitalRead(ultrasonic_F_echo) != 0);
		end_time_F = micros();
		
		printf("%f %f %f\n",end_time_R,end_time_L,end_time_F);



		distance_R = (end_time_R - start_time_R)/58.;
		distance_L = (end_time_L - start_time_L)/58.;
		distance_F = (end_time_F - start_time_F)/58.;

		printf("distance R : %fcm\n", distance_R);
		printf("distance L : %fcm\n", distance_L);
		printf("distance F : %fcm\n", distance_F);

		delay(100);
	}
	return;
} */

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

	pinMode(ultrasonic_R_trig,OUTPUT);
	pinMode(ultrasonic_R_echo,INPUT);
	pinMode(ultrasonic_L_trig,OUTPUT);
	pinMode(ultrasonic_L_echo,INPUT);
	pinMode(ultrasonic_F_trig,OUTPUT);
	pinMode(ultrasonic_F_echo,INPUT);

	while(1){
		ULTRASONIC_R();
		ULTRASONIC_L();
		ULTRASONIC_F();
	}

	return 0;
}
