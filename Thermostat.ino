#include <LiquidCrystal.h>


// Connections:
// rs (LCD pin 4) to Arduino pin 12
// rw (LCD pin 5) to Arduino pin 11
// enable (LCD pin 6) to Arduino pin 10
// LCD pin 15 to Arduino pin 13
// LCD pins d4, d5, d6, d7 to Arduino pins 6, 5, 4, 3
LiquidCrystal lcd(12, 11, 10, 6, 5, 4, 3);

int TEMP_PIN= A0;
int AC = 8;
int HEAT = 9;

float TEMP = 70.0;
float RANGE = 1.5;
int MINUTE = 60000;

void setup()
{
	Serial.begin(9600);
	pinMode(AC, OUTPUT);
	pinMode(HEAT, OUTPUT);
	lcd.begin(16,2);              // columns, rows.  use 16,2 for a 16x2 LCD, etc.
	lcd.clear();                  // start with a blank screen
	lcd.setCursor(0,0);           // set cursor to column 0, row 0 (the first row)
}

void loop()
{
	int AC_state = digitalRead(AC);
	int HEAT_state = digitalRead(HEAT);

	float tempf = get_temperature();
	lcd.setCursor(0,0);
	lcd.print("Curr Temp: ");
	lcd.print(tempf);
	Serial.print(tempf);
	Serial.println(" degrees F");

	if(AC_state == HIGH)
	{
		// Check if temp is inside temperature range and turn off AC 
		if(tempf <= TEMP)
			digitalWrite(AC, LOW);
	}
	else if(HEAT_state == HIGH)
	{
		// Check if temp is inside temperature range and turn off HEAT
		if(tempf >= TEMP)
			digitalWrite(HEAT, LOW);
	}
	else
	{
		// Check temp is within ranges
		if(TEMP + RANGE >= tempf)
		{
			digitalWrite(AC, HIGH);
		}
		else if(TEMP - RANGE <= tempf)
		{
			digitalWrite(HEAT, HIGH);
		}
	}

	//sleep(1 * MINUTE);

}



void sleep(int sleepTime)
{
	delay(sleepTime);
}

float get_temperature()
{
	float tempc = 0;
	for(int i = 0; i < 100; i++)
	{
		tempc += analogRead(TEMP_PIN);
		sleep(10);
	}

	tempc /= 100;
	tempc =  (5.0 * tempc * 100.0) / 1024.0;

	float tempf = (tempc * 9 / 5) + 32;
	return tempf;
}




