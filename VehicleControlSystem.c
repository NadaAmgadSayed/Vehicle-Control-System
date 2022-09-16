/****************************************************************************
 Name        : VehicleControlSystem.c
 Author      : Nada Amged
 Description : Implementing a Vehicle Control system
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define TURN_OFF_VEHICLE 0
#define TURN_ON_VEHICLE 1
#define QUIT_SYSTEM 2
//#define AC_OFF 0
//#define AC_ON 1

enum Sensorcoice{
	Turn_OFF , Traffic_Color , Room_Temp , Engine_Temp
};
enum EngineTempController{
	ENGINECONTROL_OFF, ENGINECONTROL_ON
};
enum AcState{
	AC_OFF , AC_ON
};

int 	command = TURN_ON_VEHICLE;
char trafficColor;
float vehicleSpeed = 40;
float roomTemp = 25;
float engineTemp = 90;
int state;
int engineControl;

void MainMenu(void);
void SensorSetMenu(void);
void SensorSetMenuChoice(char choice);
void VehicleContolSystem(void);
void setSpeed(char trafficColor);
void setRoomTemp(float Temp);
void setEngineTemp(float engTemp);
void speed30(void);
void displayStates(void);

int main(void) {

	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	puts("      Welcome to Your Vehicle Control System      \n");

	VehicleContolSystem();

	return 0;
}


/*
 * Description :
 * Function to view the main menu of the system.
 */
void MainMenu(void){
	puts("MAIN MENU:\n");
	puts("Please choose the required command:");
	puts("a. To Turn OFF the vehicle -> Press 'a'");
	puts("b. To Turn ON the vehicle -> Press 'b'");
	puts("c. To Quit the program -> press 'c'");
}


/*
 * Description :
 * Function to view the Sensor set menu when the user chooses to turn the vehicle engine on.
 */
void SensorSetMenu(void){
	printf("\n");
	puts("SENSORS SET MENU:\n");
	puts("a. To Turn off the engine -> Press 'a'");
	puts("b. To Set the traffic light color -> Press 'b'");
	puts("c. To Set the room temperature -> Press 'c' ");
	puts("d. To Set the engine temperature -> Press 'd'");
}


/*
 * Description :
 * Function to perform the choice chosen from the sensor set menu.
 */
void SensorSetMenuChoice(char choice){
	switch(choice){

	case('A'):
	case('a'):
	puts("Vehicle's engine turned off.");
	command = TURN_OFF_VEHICLE;
	displayStates();
	VehicleContolSystem(); /*if the vehicle's engine is turned off display the main menu*/
	break;

	case('B'):
	case('b'):
	puts("Choose traffic light state from G , O , R");
	scanf(" %c" , &trafficColor);
	setSpeed(trafficColor);  /*check the traffic color*/
	/***check for special cases***/
	if(vehicleSpeed == 30){
		speed30();  /*processing the function*/
	}
	displayStates();
	break;

	case('C'):
	case('c'):
	/***check for special cases***/
	if(vehicleSpeed == 30){    /*Special case whan speed is 30*/
		speed30();    /*processing the function*/
		displayStates();    /*displaying the states*/
		return;    /*returning from the function*/
	}

	/*** If the speed is not 30 ***/
	puts("Please enter the room temperature:");
	scanf(" %f" , &roomTemp); /*get the room temperature as a sensor reading*/
	setRoomTemp(roomTemp);  /*check the conditions in the called function*/

	displayStates();  /*display states*/
	break;

	case('D'):
	case('d'):
	/***check for special cases***/
	if(vehicleSpeed == 30){    /*Special case whan speed is 30*/
		speed30();  /*processing the function*/
		displayStates();  /*displaying the states*/
		return;   /*returning from the function*/
	}

	/*** If the speed is not 30 ***/
	puts("Please enter the engine temperature:");
	scanf(" %f" , &engineTemp); /*get the Engine temperature as a sensor reading*/
	setEngineTemp(engineTemp); /*check the conditions in the called function*/

	displayStates(); /*display states*/
	break;

	default:
		puts("Invalid choice!! Please choose one of the given choices:");  /*if the user entered an invalid command the systems keeps asking him to choose the correct command*/
		SensorSetMenu();   /*Display the menu once more*/
		scanf(" %c", &choice);  /*get the choice input from the user*/
		SensorSetMenuChoice(choice); /*go to the function once more to choose the command*/
	}
}


/*
 * Description :
 * Master Function of the system that performs the choice chosen from the main menu.
 */
void VehicleContolSystem(void){

	char sensorchoice;
	char menuChoice;
	do{  /*do the following for the first time with no condition checked*/
		MainMenu(); /*display the main menu*/
		scanf(" %c", &menuChoice); /*input the menu choice from the user*/
		if((menuChoice == 'A') ||(menuChoice == 'a') ){
			command = TURN_OFF_VEHICLE;

			printf("\n");
			puts("Vehicle's engine turned off."); /*display the state*/
			puts("\n==============================================");

		}
	}while((menuChoice == 'A') ||(menuChoice == 'a'));  /*repeat the do while loop if the vehicle's engine is off*/

	switch(menuChoice){

	case('A'):
	case('a'):
	command = TURN_OFF_VEHICLE;
	printf("\n");
	puts("Vehicle's engine turned off.");
	puts("\n==============================================");

	break;

	case('B'):
	case('b'):
	command = TURN_ON_VEHICLE;
	printf("\n");
	puts("\n==============================================");
	puts("Vehicle's engine turned on.");  /*print the state*/
	while((command == TURN_ON_VEHICLE)){  /*When the vehicle's engine is turned on keep displaying the menu*/
		SensorSetMenu();   /*Display the menu*/
		scanf(" %c", &sensorchoice); /*get the choice input*/
		SensorSetMenuChoice(sensorchoice);  /*call the function to check the choice*/
	}
	break;

	case('C'):
	case('c'):
	printf("\n");
	puts("Quitting the System..."); /*print the state*/
	return; /*return from the fuction to quit the system*/
	break; /*Optional it will always return from the function*/
	default:
		puts("Invalid command!! Please choose one of the given commands:");  /*if the user entered an invalid command the systems keeps asking him to choose the correct command*/
		VehicleContolSystem(); /*go to the function once more to choose the command*/

	}

}

/*
 * Description :
 * Function to set the speed of the car according to the traffic light.
 */
void setSpeed(char trafficColor){
	if((trafficColor == 'G') || (trafficColor == 'g')){
		vehicleSpeed = 100;  /*Speed is 100 km/hr if color is green*/
	}
	else if((trafficColor == 'O') || (trafficColor == 'o')){
		vehicleSpeed = 30;  /*Speed is 30 km/hr if color is orange*/
	}
	else if((trafficColor == 'R') || (trafficColor == 'r')){
		vehicleSpeed = 0;  /*Speed is 0 km/hr if color is red*/
	}
	else{
		puts("Invalid traffic Color!!!");   /*if the user entered an invalid Traffic color the systems keeps asking him to choose the correct color*/
		puts("Choose traffic light state from G , O , R");  /*Display the choices again*/
		scanf(" %c" , &trafficColor); /*input the choice from the user*/
		setSpeed(trafficColor); /*go to the function once more to choose the color*/
	}
}

void setRoomTemp(float Temp){

	if ((Temp < 10) || (Temp >30)){ /*if the room Temp id <10 or >30*/
		roomTemp = 20;
		state = AC_ON;
	}

	else{ /*otherwise*/
		state = AC_OFF;
	}
}

void setEngineTemp(float engTemp){

	if ((engTemp < 100) || (engTemp >150)){  /*if the engine Temp is >150 or <100*/
		engineTemp = 125;
		engineControl = ENGINECONTROL_ON;
	}

	else{  /*otherwise*/
		engineControl = ENGINECONTROL_OFF;
	}
}

void speed30(void){
	/**** Special Case when the Vehicle Speed is 30 km/hr ****/
	float currentTemp;
	float currentEngineTemp;

	printf("Please enter the current room temperature: \n");
	scanf("%f",&currentTemp );  /*Getting the current room temperature*/
	state = AC_ON;  /*setting the Ac state ON*/
	roomTemp = (currentTemp * (1.25))+1;

	printf("Please enter the current Engine temperature: \n");
	scanf("%f",&currentEngineTemp );  /*Getting the current Engine temperature*/
	engineControl = ENGINECONTROL_ON;  /*setting the Engine controller state ON*/
	engineTemp = (currentEngineTemp * (1.25))+1;

}

void displayStates(void){

	/*****DISPLAY THE ENGINE STATE*****/
	puts("\n==============================================");
	if(command == TURN_OFF_VEHICLE){
		puts("Vehicle's engine turned OFF.");
	}

	else if(command == TURN_ON_VEHICLE){
		puts("Vehicle's engine turned ON.");
	}

	/*****DISPLAY THE AC STATE*****/
	if( (state == AC_OFF)){
		printf("AC state is OFF. \n");
	}
	else if((state == AC_ON)){
		printf("AC state is ON. \n");
	}

	/*****DISPLAY THE VEHICLE SPEED*****/
	printf("The speed of the vehicle is: %f km/hr \n" ,vehicleSpeed );

	/*****DISPLAY THE ROOM TEMPERATURE*****/
	printf("The room temperature is: %f C\n", roomTemp);

	/*****DISPLAY THE ENGINE TEMPERATURE CONTROL STATE*****/
	if(engineControl == ENGINECONTROL_OFF){
		printf("The engine controller state is OFF. \n");
	}
	else if(engineControl == ENGINECONTROL_ON){
		printf("The engine controller state is ON. \n");
	}

	/*****DISPLAY THE ENGINE TEMPERATURE*****/
	printf("The engine temperature is: %f C\n", engineTemp);
	puts("\n==============================================");

}
