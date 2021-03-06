#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

int dcmotor_FR_1 = 1;
int dcmotor_FR_2 = 4;
int dcmotor_BR_1 = 5;
int dcmotor_BR_2 = 6;
int dcmotor_FL_1 = 7;
int dcmotor_FL_2 = 0;
int dcmotor_BL_1 = 2;
int dcmotor_BL_2 = 3;
int* speed_level;
char message;

void ROTATE_L(){
	
	while(1){
		softPwmWrite(dcmotor_FR_1,0);
		softPwmWrite(dcmotor_FR_2,200);
		softPwmWrite(dcmotor_BR_1,200);
		softPwmWrite(dcmotor_BR_2,0);
		softPwmWrite(dcmotor_FL_1,200);
		softPwmWrite(dcmotor_FL_2,0);
		softPwmWrite(dcmotor_BL_1,0);
		softPwmWrite(dcmotor_BL_2,200);
	}

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

	softPwmCreate(dcmotor_FR_1,0,200);
	softPwmCreate(dcmotor_FR_2,0,200);
	softPwmCreate(dcmotor_BR_1,0,200);
	softPwmCreate(dcmotor_BR_2,0,200);
	softPwmCreate(dcmotor_FL_1,0,200);
	softPwmCreate(dcmotor_FL_2,0,200);
	softPwmCreate(dcmotor_BL_1,0,200);
	softPwmCreate(dcmotor_BL_2,0,200);

	scanf("%c",&message);

	if(message == 'L'){
		ROTATE_L();
	}
	return 0;
}
