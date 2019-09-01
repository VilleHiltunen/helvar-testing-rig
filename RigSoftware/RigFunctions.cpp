#include "RigSoftware.h"
#include <Arduino.h>

/*
 * Function for handling type 5 commands, which is the group for core user functions that don't fit in the other categories.
 */
void sendControlCommand(unsigned long *timers, parseResult result, commandWordInfoStruct *commandWordInfo, ringBufferInfoStruct &ringBufferInfo, HardwareSerial &rSerial, homeInfoStruct &homeInfo, int *sensorTasklist) {
	String cmdWord = commandWordInfo[result.commandIndex].commandWord;
	if (cmdWord == "homexy") {
    // Command to home the XY plane. This function has conditionals in the xy
		// Note: The ringbuffer is flushed and no new commands will be accepted while homing.
		ringBufferInfo.commandCount = 0;
		ringBufferInfo.ringInputIndex = 0;
		ringBufferInfo.ringOutputIndex = 0;
		injectCommand(ringBufferInfo,"rfs(1,0)");
		injectCommand(ringBufferInfo,"rfs(2,0)");
		homeInfo.replyCount = 2;
		homeInfo.homeXFlag = 1;
		// After homing is done this allows xypos command
		homeInfo.homedFlag = 1;
	}
	else if (cmdWord == "homesen") {
    // Homes sensor head to 0.
		homeInfo.sensorHomeFlag = 1;
		sensorTasklist[SENSOR_STEPS] = -30000;
	}
	else if (cmdWord == "xypos") {
    // Xypos breaks down the position to separate X and Y move commands.
    // This function is not allowed until the device is homed.
    // BUG: If the steppers were unresponsive during "homexy" command, the machine will
    //      still consider itself homed.
		if (homeInfo.homedFlag) {
			String command1_1 = "mvp(1,";
			String command2_1 = "mvp(2,";
			String command2 = ")";
			String full;
			char tempHolder[CMD_BUFFER_LEN] = {0};
			full = command1_1 + (long)(((float)(result.args[0] + X_OFFSET)) * STEPS_TO_MM) + command2;
			full.toCharArray(tempHolder,CMD_BUFFER_LEN);
			rSerial.println("Sending the following PANdrive commands:");
			injectCommand(ringBufferInfo,tempHolder);
			rSerial.println(full);
			full = command2_1 + (long)(((float)(result.args[1] + Y_OFFSET)) * STEPS_TO_MM) + command2;
			full.toCharArray(tempHolder,CMD_BUFFER_LEN);
			rSerial.println(full);
			injectCommand(ringBufferInfo,tempHolder);
			rSerial.print("Moving to position (");
			rSerial.print(result.args[0]);
			rSerial.print(",");
			rSerial.print(result.args[1]);
			rSerial.println(").");
		}
		else {
			rSerial.println("Command refused. Please home the device before using the homexy command.");
		}
	}
	else if (cmdWord == "help") {
		rSerial.println("Input commands by typing command, followed by");
		rSerial.println("the arguments separated by commas.");
		rSerial.println("Example command: \"xypos(200,100)\"");
		rSerial.println("Printing commands with the related");
		rSerial.println("number of args and their constraints");
		rSerial.println("See documentation for full description.");
		for (int i = 0; i < COMMAND_LIST_SIZE; i++) {
			rSerial.print(commandWordInfo[i].commandWord);
			rSerial.print(" # of args: ");
			rSerial.println(commandWordInfo[i].numOfArgs);
			if (commandWordInfo[i].numOfArgs > 0) {
				for (int j = 0; j < commandWordInfo[i].numOfArgs; j++) {
					rSerial.print("Arg ");
					rSerial.print(j);
					rSerial.print(" constraints: [");
					rSerial.print(commandWordInfo[i].lowerConst[j]);
					rSerial.print(",");
					rSerial.print(commandWordInfo[i].upperConst[j]);
					rSerial.println("]");
				}
			}
			rSerial.println("----------------");
		}	
	}
}

/*
 * Function to loop through computer -> Arduino serial connection
 * 
 * The function appends serial input to a buffer until a newline
 * character is met, which causes the newCmd flag to be set and
 * the buffer index to reset. See getCommandInfo in RigSoftware.h.
 */
commandInfo getCommand(commandInfo info, HardwareSerial &rSerial)
{
  char currentByte = 0;
	while(rSerial.available() > 0)
  {
  	if (info.dataIndex > CMD_BUFFER_LEN - 2) {
  		info.errorNmbr = E_BUFFER_FULL;
  		return info;
  	}
  	currentByte = rSerial.read();
  	if (currentByte == '\n') {
  		info.newCmd = 1;
  		info.cmdBuffer[info.dataIndex] = '\0';
  		return info;
  	}
    info.cmdBuffer[info.dataIndex] = currentByte;
    info.dataIndex++;
  }
  return info;
}

/*
 * Function to loop through stepper driver -> Arduino serial
 * 
 * The function appends serial input to a buffer until a newline
 * character is met, which causes the newCmd flag to be set and
 * the buffer index to reset. See getCommandInfo in RigSoftware.h.
 */
commandInfo getReply(commandInfo info, HardwareSerial &rSerial)
{
  char currentByte = 0;
	while(rSerial.available() > 0)
  {
  	if (info.dataIndex > CMD_BUFFER_LEN - 2) {
  		info.errorNmbr = E_BUFFER_FULL;
  		return info;
  	}
  	currentByte = rSerial.read();
    info.cmdBuffer[info.dataIndex] = currentByte;
    info.dataIndex++;
    if (info.dataIndex == STEPPER_LEN) {
    	info.newCmd = 1;
    	//info.dataIndex = 0;
    	int checksum = 0;
    	for (int i = 0; i < STEPPER_LEN - 1; i++) {
    		checksum += info.cmdBuffer[i];
    		//Serial.println(info.cmdBuffer[i],DEC);
    	}
    	/*
    	Serial.println("CheckSums");
    	Serial.println(checksum,DEC);
    	Serial.println(info.cmdBuffer[STEPPERLEN - 1],DEC);
    	Serial.println(info.cmdBuffer[STEPPERLEN],DEC);
    	*/
    	if (checksum != info.cmdBuffer[STEPPER_LEN - 1]) {
    		info.errorNmbr = E_CHECKSUM_OFF;
        rSerial.println("Checksum was off");
    	}
    }
  }
  return info;
}

/*
 * Function to parse a reply from a Pandrive stepper motor
 */
int parseMotorReply(char *outBuffer, char *inBuffer)
{
  for (int i = 0; i < STEPPER_LEN; i++) {
    outBuffer[i] = inBuffer[i];
  } 
  if(inBuffer[STEPPER_LEN] != '\r') {
    return 1;
  }
  return 0;
}

/*
 * Function to format and send a command to a Pandrive stepper motor
 */
void sendMotorCommand(unsigned long *timers, parseResult &result, commandWordInfoStruct *commandWordInfo) {
	//We wait for the D/R line to properly activate before sending data.
	digitalWrite(DR_PIN,HIGH);
	//delayMicroseconds(DR_LINE_DELAY_U);
	//Use the motorInfo struct that is prefilled with the correct instruction type for the stepper driver.
	motorInfoUnion mi = commandWordInfo[result.commandIndex].mi;
	for (int i = 0; i < commandWordInfo[result.commandIndex].numOfArgs; i++) {
		//Place the user inputted data into the motorInfo struct. Note that since the value
		//is a long, so it is handled separately. The rest are bytes accessesd by union.
		if (commandWordInfo[result.commandIndex].argFields[i] == 4) {
			mi.motorInfo.motorValue = result.args[i];
		}
		else {
			mi.bytes[commandWordInfo[result.commandIndex].argFields[i]] = (byte)result.args[i];
		}
	}
	unsigned char i, Checksum;
	unsigned char Command[9];
	Command[0] = mi.motorInfo.moduleAddress;				      //Module address
	Command[1] = mi.motorInfo.command;				            //Command
	Command[2] = mi.motorInfo.commandType;				        //Type
	Command[3] = mi.motorInfo.motorBank;				          //Motor/Bank
	Command[4] = (mi.motorInfo.motorValue >> 24);				  //Value(Byte 3)
	Command[5] = (mi.motorInfo.motorValue >> 16) & 0xff;	//Value(Byte 2)
	Command[6] = (mi.motorInfo.motorValue >> 8) & 0xff;		//Value(Byte 1)
	Command[7] = mi.motorInfo.motorValue & 0xff;		      //Value(Byte 0)
	Checksum = Command[0];
	for(i=1; i<8; i++) {
		Checksum+=Command[i];
	}
	Command[8] = Checksum;
	//Serial1.write(Command,9);
	for(int i = 0; i<9;i++)
	{
		Serial1.write(Command[i]);
	}
	// This is hardcoded to use serial1. Needs to be changed in case other serial is designated for stepper communication.
	while(!(UCSR1A & (1 << TXC1)));
	digitalWrite(DR_PIN,LOW);
	timers[REPLY_TIMER] = millis();
}

/*
 * This function parses the contents between the ( and ) after a command. It counts the commas and returns every argument in
 * between them. The amount of arguments needs to match the command in the command list, lest it is banished to the shadow realm.
 */
parseResult parseCommandString(String cmdString, int nbrOfArgs, int stringLen, int cmdWordLen) {
	parseResult result = {0};
	if ((stringLen >= cmdWordLen) && (nbrOfArgs > 0)) {
		int startIndex = cmdString.indexOf('(');
		int endIndex = cmdString.indexOf(')');
		/*
		Serial.print("first pass");
		Serial.print('\t');
		Serial.print(currentIndex);
		Serial.print('\t');
		Serial.println(endIndex);
		Serial.print("first pass");
		Serial.print('\t');
		Serial.print(cmdString.lastIndexOf(')'));
		Serial.print('\t');
		Serial.println(cmdString.lastIndexOf('('));
		*/
		// Check that we have braces in our command and that there is only one set.
		if (	endIndex > startIndex
				&& nbrOfArgs <= MAX_ARGS
				&& endIndex > 0 
				&& startIndex > 0
				&& endIndex == (cmdString.lastIndexOf(')'))
				&& startIndex == (cmdString.lastIndexOf('('))) {
			int pivotIndex = 0;
			int precheckIndex = 0;
			int separatorCount = 0;		
			// Loop through the content between braces and count the commas
			while ((pivotIndex = cmdString.substring(startIndex,endIndex).indexOf(',',precheckIndex)) > 0) {	
				separatorCount += 1;
				precheckIndex = pivotIndex + 1;
			}
			// We must have exactly one less delimiter than total arguments
			if (separatorCount == nbrOfArgs - 1) {								
				int currentIndex = startIndex + 1;
				String argString;
				// Loop through the command, reading the values separated by commas
				for (int i = 0; i < nbrOfArgs; i++) {
					pivotIndex = cmdString.indexOf(',',currentIndex);					
					if (pivotIndex < 0 && i == nbrOfArgs - 1) {
						// Check if we are dealing with the last argument
							argString = cmdString.substring(currentIndex,endIndex);
					}
					else if (pivotIndex > 0 && pivotIndex > currentIndex) {
							//Otherwise we are dealing with a normal argument.
							argString = cmdString.substring(currentIndex,pivotIndex);
					}					
					else {
						// Something went wrong. Raise error flag and return.
						result.errorStatus = E_COMMAND_MALFORMED;
						return result;
					}
					for (int j = 0; j < argString.length(); j++) {
						// Iterate over the argument canditate. If it has non digits reject it and raise error.
						if (j == 0 && (isDigit(argString[j]) || argString[j] == '-')) {
							;
						}
						else if (isDigit(argString[j])) {
							;
						}
						else {
							result.errorStatus = E_COMMAND_MALFORMED;
							return result;
						}
					}
					long argVal = argString.toInt();
					result.args[i] = argVal;
					currentIndex = pivotIndex + 1;
					
				}
			}
			else {
				result.errorStatus = E_COMMAND_MALFORMED;
			}
		}
		else {
			result.errorStatus = E_COMMAND_MALFORMED;
		}
	}
	return result;
}

/*
 * The command preparser. Some checking to see that the command word and the constraints match.
 */
parseResult evaluateCommand(String incString, commandWordInfoStruct* commandWordInfo, HardwareSerial &rSerial) {
	incString.trim();
	incString.toLowerCase();
	parseResult result;
	for (int i = 0; i < COMMAND_LIST_SIZE; i++) {
		if (incString.substring(0,commandWordInfo[i].commandWordLen) == commandWordInfo[i].commandWord) {
			rSerial.print("Command word detected: ");
			rSerial.println(commandWordInfo[i].commandWord);
			result = parseCommandString(incString, commandWordInfo[i].numOfArgs, incString.length(),commandWordInfo[i].commandWordLen);
			if (result.errorStatus) {
				return result;
			}
			result.commandIndex = i;
			for (int j = 0; j < commandWordInfo[i].numOfArgs; j++) {
				if (commandWordInfo[i].lowerConst[j] > result.args[j] || commandWordInfo[i].upperConst[j] < result.args[j]) {
					result.errorStatus = E_CONSTRAINT;
					rSerial.print("Value given for argument: ");
					rSerial.print(j,DEC);
					rSerial.println(" was off.");
					rSerial.println("Constraints:");
					rSerial.print("Lower: ");
					rSerial.println(commandWordInfo[i].lowerConst[j]);
					rSerial.print("Upper: ");
					rSerial.println(commandWordInfo[i].upperConst[j]);
					rSerial.print("Input was: ");
					rSerial.println(result.args[j]);
					return result;
				}
			}
			return result;
		}
	}
	result.errorStatus = E_NOTFOUND;
  rSerial.println("Command not found.");
	return result;
}

/*
 * This function handles all the servo (aka model movement) funtions.
 */
void sendServoCommand(unsigned long *timers, parseResult &result, commandWordInfoStruct *commandWordInfo, servoInfoStruct &servoInfo, HardwareSerial &rSerial) {
	String cmdWord = commandWordInfo[result.commandIndex].commandWord;
	if (cmdWord == "srva") {
    // Command for adding a servo. Target a slot from 1-32.
			if (servoInfo.slots[result.args[0]-1] != -1) {
				rSerial.println("Servo slot already taken. Please detach it.");
			}
      else {
      	int freeServoIndex = -1;
        for (int i = 0; i < SERVO_AMOUNT; i++) {
        	if (!servoInfo.servos[i].attached()) {
        		freeServoIndex = i;
        		break;
        	}
        }
        if (freeServoIndex == -1) {
        	rSerial.println("No free servos available, please detach one.");
        }
        servoInfo.servos[freeServoIndex].attach(result.args[0]+SERVO_PIN_OFFSET);
        servoInfo.slots[result.args[0]-1] = freeServoIndex;
        rSerial.println("Servo succesfully attached");
        rSerial.print("Slot    ");
        rSerial.println(result.args[0]);
        rSerial.print("srvl symbol    ");
        rSerial.println(freeServoIndex);
		  }
	}
	else if (cmdWord == "srvr") {
  // Remove a servo from slot, or purge everything with -1
		if (result.args[0] == -1) {
			rSerial.println("All servo slots purged.");
			for (int i = 0; i < SERVO_SLOTS; i++) {
				servoInfo.slots[i] = -1;
			}
			for (int i = 0; i < SERVO_AMOUNT; i++) {
				servoInfo.servos[i].detach();
			}
		}
		else {
			if (servoInfo.slots[result.args[0]-1] == -1) {
				rSerial.println("Servo slot already open.");
			}
	    else {
	    	rSerial.println("Servo succesfully removed");
	      rSerial.print("Slot    ");
	      rSerial.println(result.args[0]);
	    	int freeServoIndex = servoInfo.slots[result.args[0]-1];
	    	rSerial.print("srvl symbol    ");
	      rSerial.println(freeServoIndex);
	    	servoInfo.slots[result.args[0]-1] = -1;
	      servoInfo.servos[freeServoIndex].detach();
		  }
		}
	}
 // Set the speed of a servo in a slot, or all of them with -1
	else if (cmdWord == "srvs") {
		if (result.args[0] == -1) {
			rSerial.print("All servo speeds set to speed: ");
			rSerial.println(result.args[1]);
			unsigned long delayActual = map(result.args[1],1,100,SERVO_UPPER_DELAY_U,SERVO_LOWER_DELAY_U);
			rSerial.print("Which corresponds to ");
			rSerial.print(delayActual);
			rSerial.println(" microsecond delay between each degree of motion.");
			for (int i = 0; i < SERVO_AMOUNT; i++) {
				servoInfo.delays[i] = delayActual;
			}
		}
		else {
			if (servoInfo.slots[result.args[0]-1] == -1) {
				rSerial.println("Servo slot has no servo.");
			}
	    else {
	    	rSerial.println("Servo speed succesfully adjusted");
	      rSerial.print("Slot    ");
	      rSerial.println(result.args[0]);
	    	int servoIndex = servoInfo.slots[result.args[0]-1];
	    	rSerial.print("srvl symbol    ");
	      rSerial.println(servoIndex);
	    	rSerial.print("speed    ");
	      rSerial.println(result.args[1]);
	      unsigned long delayActual = map(result.args[1],1,100,SERVO_UPPER_DELAY_U,SERVO_LOWER_DELAY_U);
	      rSerial.print("Which corresponds to ");
				rSerial.print(delayActual);
				rSerial.println(" microsecond delay between each degree of motion.");
	    	servoInfo.delays[servoIndex] = delayActual;
		  }
		}
	}
	else if (cmdWord == "srvl") {
  // list all servo related stats. Simple and no arguments.
		rSerial.println("###############");
		for (int i = 3; i >= 0; i--) {
			for (int j = 0; j < 8; j++) {
				if (servoInfo.slots[i*8+j] != -1) {
					rSerial.print(servoInfo.slots[i*8+j]);
				}
				else {
					rSerial.print("-");
				}
				rSerial.print(" ");
			}
			rSerial.println("");
		}
		rSerial.println("###############");
		rSerial.println("1 2 3 4 5 6 7 8");
		rSerial.println(" ");
		rSerial.println("Servo delays:");
		for (int i = 0; i < SERVO_AMOUNT; i++) {
			rSerial.print("Servo ");
			rSerial.print(i);
			if (servoInfo.servos[i].attached()) {
				rSerial.print(" in slot: ");
				for (int j = 0; j < SERVO_SLOTS; j++) {
					if (servoInfo.slots[j] == i) {
						rSerial.print(j+1);
						break;
					}
				}
			}
			else {
				rSerial.print("            ");
			}
			rSerial.print(" Speed: ");
			unsigned long percentDelay = map(servoInfo.delays[i],SERVO_UPPER_DELAY_U,SERVO_LOWER_DELAY_U,1,100);
			rSerial.print(percentDelay);
			rSerial.print("%, ");
      rSerial.print("Delay in hold mode: ");
      rSerial.print(servoInfo.holdDelays[i]);
      rSerial.println("milliseconds.");
		}
	}
	else if (cmdWord == "srvm") {
  // Change the mode of a servo from continuous sway to hold and swipe. Target all with -1.
		if (result.args[0] == -1) {
			rSerial.print("All servo modes assigned to mode: ");
			rSerial.println(result.args[1]);
			for (int i = 0; i < SERVO_AMOUNT; i++) {
				servoInfo.modeFlags[i] = result.args[1];
			}
		}
		else {
			if (servoInfo.slots[result.args[0]-1] == -1) {
				rSerial.println("Servo slot has no servo.");
			}
	    else {
	    	rSerial.println("Servo mode succesfully adjusted");
	      rSerial.print("Slot    ");
	      rSerial.println(result.args[0]);
	    	int servoIndex = servoInfo.slots[result.args[0]-1];
	    	rSerial.print("srvl symbol    ");
	      rSerial.println(servoIndex);
	    	rSerial.print("mode    ");
	      rSerial.println(result.args[1]);
	    	servoInfo.modeFlags[servoIndex] = result.args[1];
		  }
		}
	}
 // Set the hold delay for a servo, or all of them with -1.
	else if (cmdWord == "srvh") {
		if (result.args[0] == -1) {
			rSerial.print("All servo hold delays set to: ");
			rSerial.print(result.args[1]);
			rSerial.println("milliseconds.");
			for (int i = 0; i < SERVO_AMOUNT; i++) {
				servoInfo.holdDelays[i] = result.args[1];
			}
		}
		else {
			if (servoInfo.slots[result.args[0]-1] == -1) {
				rSerial.println("Servo slot has no servo.");
			}
	    else {
	    	rSerial.println("Servo hold delay succesfully adjusted");
	      rSerial.print("Slot    ");
	      rSerial.println(result.args[0]);
	    	int servoIndex = servoInfo.slots[result.args[0]-1];
	    	rSerial.print("srvl symbol    ");
	      rSerial.println(servoIndex);
	    	rSerial.print("delay    ");
	      rSerial.print(result.args[1]);
	      rSerial.println("milliseconds.");
	    	servoInfo.holdDelays[servoIndex] = result.args[1];
		  }
		}
	}
	else {
		rSerial.println("Unrecognized servo command.");
	}
}
// Sensor commands operate via a tasklist that contains the number of steps to take and in what direction. Steps are taken every other loop.
// All values are relative to the home position.
void sendSensorCommand(unsigned long *timers, parseResult &result, commandWordInfoStruct *commandWordInfo, int *sensorTasklist, HardwareSerial &rSerial) {
	int currentPos = sensorTasklist[SENSOR_POS];
	int targetPos = sensorTasklist[SENSOR_HOME] + (int)((float)result.args[0] * (1/STEPS_TO_ANGLE));
	int stepsToTake = targetPos - currentPos;
	sensorTasklist[SENSOR_STEPS] = stepsToTake;
}
// Heating commands drive a transistor-pmos array to control 12V PWM to the models. Full 255 is not allowed due to current concerns.
void sendHeatingCommand(unsigned long *timers, heatingInfoStruct &heatingInfo, parseResult &result, commandWordInfoStruct *commandWordInfo, HardwareSerial &rSerial) {
	String cmdWord = commandWordInfo[result.commandIndex].commandWord;
	if (cmdWord == "heatc") {
		int heatActual = map(result.args[0],0,100,0,200);
		analogWrite(HEATING_PIN,heatActual);
		heatingInfo.heatingActual = heatActual;
		heatingInfo.heatingPercent = result.args[0];
		rSerial.print("Heating set to: ");
		rSerial.println(result.args[0]);
	}
	else if (cmdWord == "heatl") {
		rSerial.println("Heating strength:");
		rSerial.print(heatingInfo.heatingPercent);
		rSerial.println("%");
	}
	else if (cmdWord == "heati") {
		rSerial.println("Initializing full burn for:");
		rSerial.print(HEATING_DELAY/1000);
		rSerial.println(" seconds");
		analogWrite(HEATING_PIN,200);
		heatingInfo.heatingFlag = 1;
		timers[HEATING_TIMER] = millis();
	}
}
// Function to display message from the PD steppers, or trash is some slipped through.
void displayReply(commandInfo replyInfo, HardwareSerial &rSerial) {
	rSerial.print(replyInfo.cmdBuffer[0],DEC);
  rSerial.print('\t');
  rSerial.println("Reply address");
  rSerial.print(replyInfo.cmdBuffer[1],DEC);
  rSerial.print('\t');
  rSerial.println("Module address");
  rSerial.print(replyInfo.cmdBuffer[2],DEC);
  rSerial.print('\t');
  rSerial.println("Status");
  rSerial.print(replyInfo.cmdBuffer[3],DEC);
  rSerial.print('\t');
  rSerial.println("Command number");
  rSerial.print(replyInfo.cmdBuffer[4],DEC);
  rSerial.print('\t');
  rSerial.println("Val4");
  rSerial.print(replyInfo.cmdBuffer[5],HEX);
  rSerial.print('\t');
  rSerial.println("Val3");
  rSerial.print(replyInfo.cmdBuffer[6],HEX);
  rSerial.print('\t');
  rSerial.println("Val2");
  rSerial.print(replyInfo.cmdBuffer[7],HEX);
  rSerial.print('\t');
  rSerial.println("Val1");
  rSerial.print(replyInfo.cmdBuffer[8],HEX);
  rSerial.print('\t');
  rSerial.println("Checksum");
}
// The main loop to go through the tasklist.
void sensorLoop(int *tasklist, unsigned long *timers, homeInfoStruct &homeInfo, HardwareSerial &rSerial) {
	if (tasklist[SENSOR_STEPS] != 0 && timers[SENSOR_STEP_TIMER] + SENSOR_STEP_DELAY < timers[LOOP_TIMER]) {
     // If we have steps we take them and adjust for direction. The output pins drive a SilentStepStick motor controller.
    digitalWrite(SENSOR_ENABLE,LOW);
    if (tasklist[SENSOR_STEPS] > 0) {
	    digitalWrite(SENSOR_DIR, HIGH);
	    if (!digitalRead(SENSOR_STEP)) {
	    	tasklist[SENSOR_STEPS] -= 1;
	    	tasklist[SENSOR_POS] += 1;
	    }
    }
    else {
    	digitalWrite(SENSOR_DIR, LOW);
    	if (!digitalRead(SENSOR_STEP)) {
    		tasklist[SENSOR_STEPS] += 1;
    		tasklist[SENSOR_POS] -= 1;
    	}
    }
    digitalWrite(SENSOR_STEP, !digitalRead(SENSOR_STEP));
    timers[SENSOR_STEP_TIMER] = millis();
    if ((!digitalRead(SENSOR_LSWITCH)) && timers[LIMIT_SWITCH_TIMER] + LIMIT_SWITCH_DELAY < timers[LOOP_TIMER]) {
      // Check if we have hit a limit switch. If homing this is a good thing, if not, we return to home and complain to user.
    	if (homeInfo.sensorHomeFlag) {
    		tasklist[SENSOR_MIN] = 0;
    		tasklist[SENSOR_POS] = 0;
    		tasklist[SENSOR_STEPS] = 30000;
    		rSerial.println("LSWITCH HIT");

    	}
    	else {
    		rSerial.println("Left switch hit, returning to last home");
    		rSerial.println("Send homesen to recalibrate sensor header.");
    		tasklist[SENSOR_STEPS] = tasklist[SENSOR_HOME]-tasklist[SENSOR_POS];
    	}
    	timers[LIMIT_SWITCH_TIMER] = millis();
    }
    if ((!digitalRead(SENSOR_RSWITCH)) && timers[LIMIT_SWITCH_TIMER] + LIMIT_SWITCH_DELAY < timers[LOOP_TIMER]) {
    	if (homeInfo.sensorHomeFlag) {
    		tasklist[SENSOR_MAX] = tasklist[SENSOR_POS] - SENSOR_HOME_CORR;
    		tasklist[SENSOR_HOME] = tasklist[SENSOR_MAX]/2;
    		rSerial.println("RSWITCH HIT");
        rSerial.println("Setting home to midway point.");
    		tasklist[SENSOR_STEPS] = -tasklist[SENSOR_HOME];
    		homeInfo.sensorHomeFlag = 0;
    	}
    	else {
	    	rSerial.println("Right switch hit, returning to last home");
	    	rSerial.println("Send homesen to recalibrate sensor header.");
	    	tasklist[SENSOR_STEPS] = tasklist[SENSOR_HOME]-tasklist[SENSOR_POS];
    	}
    	timers[LIMIT_SWITCH_TIMER] = millis();
    }
  }
}

// Function to sway servos back and forth. Microseconds are used for swaying, milliseconds for holding.
void servoLoop(servoInfoStruct &servoInfo, unsigned long *timers) {
	for (int i = 0; i < SERVO_AMOUNT; i++) {
		if (servoInfo.servos[i].attached() && servoInfo.timers[i] + servoInfo.delays[i] < timers[MICRO_LOOP_TIMER] && servoInfo.holdTimers[i] + servoInfo.holdDelays[i] < timers[LOOP_TIMER]) {
			if (servoInfo.pos[i] >= MAX_ANGLE) {
				servoInfo.states[i] = -1;
				servoInfo.pos[i] = MAX_ANGLE;
				if (servoInfo.modeFlags[i]) {
					servoInfo.holdTimers[i] = millis();
				}
			}
			else if (servoInfo.pos[i] <= MIN_ANGLE){
				servoInfo.states[i] = 1;
				servoInfo.pos[i] = MIN_ANGLE;
				if (servoInfo.modeFlags[i]) {
					servoInfo.holdTimers[i] = millis();
				}
			}
			servoInfo.pos[i] += servoInfo.states[i];
			servoInfo.servos[i].write(servoInfo.pos[i]);
			servoInfo.timers[i] = micros();
		}	
	}
}
// This function inserts commands to the ringbuffer. This is used all around to peacefully add commands to execute regardless of where it's called.
void injectCommand(ringBufferInfoStruct &ri, char *command) {
	strcpy(ri.cmdRingBuffer[ri.ringInputIndex],command);
	ri.ringInputIndex += 1;
	if (ri.ringInputIndex >= CMD_RING_BUFFER_LEN) {
		ri.ringInputIndex = 0;
	}
	ri.commandCount += 1;
}
// Grab a command from the ring buffer.
String grabRingBufferCommand(ringBufferInfoStruct &ri) {
	String incCommand = String(ri.cmdRingBuffer[ri.ringOutputIndex]);
	ri.ringOutputIndex += 1;
	if (ri.ringOutputIndex >= CMD_RING_BUFFER_LEN) {
		ri.ringOutputIndex = 0;
	}
	ri.commandCount -= 1;
	return incCommand;
}
// This function asks if the PD steppers have reached the left limit switch yet. The spam repeats until something is found.
void homeLoop(ringBufferInfoStruct &ringBufferInfo, unsigned long *timers, homeInfoStruct &homeInfo) {	
	if (timers[HOME_TIMER] + HOME_DELAY < timers[LOOP_TIMER]) {
		if (homeInfo.homeXFlag) {
			injectCommand(ringBufferInfo,"rfs(1,2)");
		}
		if (homeInfo.homeYFlag) {
			injectCommand(ringBufferInfo,"rfs(2,2)");
		}
		timers[HOME_TIMER] = millis();
	}
}
// Function to check if the timed heater burn command should be finished.
void heatingLoop(heatingInfoStruct &heatingInfo, unsigned long *timers, HardwareSerial &rSerial) {
	if (timers[HEATING_TIMER] + HEATING_DELAY < timers[LOOP_TIMER]) {
		heatingInfo.heatingFlag = 0;
		analogWrite(HEATING_PIN,heatingInfo.heatingPercent);
		rSerial.println("Full burn is off");
	}
}
	
