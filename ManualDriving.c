#include <stdio.h>
#include <stdlib.h>
#include <wirignPi.h>
#include <softPwm.h>

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

	softPwmCreate(dcmotor_FR_1,0,200);
	softPwmCreate(dcmotor_FR_2,0,200);
	softPwmCreate(dcmotor_BR_1,0,200);
	softPwmCreate(dcmotor_BR_2,0,200);
	softPwmCreate(dcmotor_FL_1,0,200);
	softPwmCreate(dcmotor_FL_2,0,200);
	softPwmCreate(dcmotor_BL_1,0,200);
	softPwmCreate(dcmotor_BL_2,0,200);

	speed_level = (int*)malloc(sizeof(int)*2);
	speed_level[0] = 0;
	
	while(1){

		scanf("%c",&message)

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
			UP();
		}

		else if(message == 'D'){
			DOWN();
		}
	}
	return 0;
}
			
