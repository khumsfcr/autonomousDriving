#include <stdio.h>
#include <wiringPi.h>

int red = 21;
int green = 22;
int blue = 23;

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
	
}

void BLUE(){
	
		digitalWrite(red,HIGH);
		digitalWrite(green,HIGH);
		digitalWrite(blue,LOW);
	
	return;
}

int main(){
	
	if(wiringPiSetup() == -1){
		return 0;
	}

	pinMode(red,OUTPUT);
	pinMode(green,OUTPUT);
	pinMode(blue,OUTPUT);

	while(1){
		
		RED();
		delay(1000);
		GREEN();
		delay(1000);
		BLUE();
		delay(1000);
	}
	return 0;
}
