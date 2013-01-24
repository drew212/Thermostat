int TEMP_PIN= A0;
int AC = 8;
int HEAT = 9;

int TEMP = 71;
int RANGE = 1;
int MINUTE = 60000;

void setup()
{
	pinMode(AC, OUTPUT);
	pinMode(HEAT, OUTPUT);
}

void loop()
{
	int AC_state = digitalRead(AC);
	int HEAT_state = digitalRead(HEAT);

	float tempf = get_temperature();

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

	sleep(1 * MINUTE);
  
}



void sleep(int sleepTime)
{
	delay(sleepTime);
}

float get_temperature()
{
	float tempc = 0;
	for(int i = 0; i < 8; i++)
	{
		tempc += analogRead(TEMP_PIN);
		delay(1000);
	}

	tempc /= 8;
	tempc = ( 5.0 * tempc * 100.0) / 1024.0;

	float tempf = (tempc * 9 / 5) + 32;
	return tempf;
}