/*
 * Written by Ville Hiltunen (2019) villejhiltunen@gmail.com under MIT license.
 */

#include "RigSoftware.h"
#include <Servo.h>

/*
 * Command definitions here. 
 * Type 1 corresponds to PANdrive stepper functions, 
 * Type 2 is servo related functions
 * Type 3 is for sensor movement
 * Type 4 is heating related functions
 * Type 5 is the type for the main composite functionalities that issue commands themselves and other miscallaneous control commands.
 * 
 * If you wish to add your own ones, add it here, go to the function that handles it and add a handler.
 * Also increment the COMMAND_LIST_SIZE by one. PANdrive stepper functions have a universal handler, provided a prefilled MI
 * and arg field is provided.
 * 
 * CMD is the command word recognized by the parser.
 * 
 * Len is the number of letters in the command word.
 * 
 * Args is the number of arguments the command has
 * 
 * Arg_Field is strictly for PANdrive stepper functions and guides which argument fills which datafield in the 9 byte command.
 *    arg_Field should be the size of the number of arguments for the command. Argument 0 uses the index of arg_field[0] and so forth.
 *    Index 0 is the machine address, Index 1 is the command type, Index 2 is the type specification, Index 3 is the motor bank and Index 4 is the 4-byte value.
 *    Check sendMotorCommand function for more details.
 *    
 * Lower and higher constraints limit the allowed user input between them. There should be as many constraints as there are arguments.
 * 
 * Prefilled MI is a motorInfo struct that has the correct command number associated with the command according to PANdrive manual. Not used for non PD-stepper functions.
 */
commandWordInfoStruct commandWordInfo[COMMAND_LIST_SIZE] = {
//Type	Cmd					Len	Args	arg_Field			Lower constraints			Higher constraints		Prefilled MI
	//{1,		"ror",			3,	2,		{0,4,},				{1,-2047,},						{2,2047,},						{0,1,},},
	{1,		"mst",			3,	1,		{0,},					{1,},									{2,},									{0,3,},},
	{1,		"mvp",			3,	2,		{0,4,},				{1,-2147483648,},			{2,2147483647,},			{0,4,},},
	{1,		"gap",			3,	2,		{0,2,},				{1,},									{2,255,},							{0,6,},},
	{1,		"ggp",			3,	3,		{0,2,3,},			{1,},									{2,255,3,},						{0,10,},},
	{1,		"sgp",			3,	4,		{0,2,3,4},		{1,0,0,-2147483647},	{2,255,3,2147483647},	{0,9,},},
	{1,		"sap",			3,	3,		{0,2,4,},			{1,0,-2147483648,},		{2,255,2147483647,},	{0,5,},},
	{1,		"rfs",			3,	2,		{0,2,},				{1,},									{2,255,3,},						{0,13,},},
	{1,		"stap",			4,	2,		{0,2,},				{1,},									{2,255,},							{0,7,},},
	{2,		"srva",			4,	1,		{0},					{1,},									{32,},},
	{2,		"srvr",			4,	1,		{0},					{-1,},								{32,},},
	{2,		"srvs",			4,	2,		{0,2,},				{-1,1,},							{32,100,},},
	{2,		"srvl",			4,	0,		},
	{2,		"srvm",			4,	2,		{0,},					{-1,0,},							{32,1,},},
	{2,		"srvh",			4,	2,		{0,},					{-1,5,},							{32,30000,},},
	{3,		"sen",			3,	1,		{0},					{-125,},							{125,},},
	{4,		"heatc",		5,	1,		{0},					{0},									{100},},
	{4,		"heatl",		5,	0,		},
	{4,		"heati",		5,	0,		},
	{5,		"xypos",		5,	2,		{0},					{0,0,},								{1000,500,},/*{-2147483648,-2147483648,},		{2147483647,2147483647,},*/},
	{5,		"homexy",		6,	0,		},
	{5,		"homesen",	7,	0,		},
	{5,		"help",			4,	0,		},
	{1,		"exp",			3,	5,		{0,1,2,3,4},	{0,0,0,0,-2147483647},{255,255,255,255,2147483647},					{0,},},
};

//Buffers, flags and struct inits.
char cmdBuffer[CMD_BUFFER_LEN];
char replyBuffer[CMD_BUFFER_LEN];
commandInfo cmdInfo;
commandInfo replyInfo;
int sensorTasklist[SENSOR_TASKLIST_LEN];
unsigned long timers[TIMER_LEN];
int replyFlag;
int servoModeFlag;
ringBufferInfoStruct ringBufferInfo;
servoInfoStruct servoInfo;
heatingInfoStruct heatingInfo;
homeInfoStruct homeInfo;

void setup() {
	Serial.begin(38400);
	Serial1.begin(38400);
	while (!Serial) {
		;
	}
  pinMode(DR_PIN, OUTPUT);
  pinMode(SENSOR_ENABLE, OUTPUT);
  pinMode(HEATING_PIN, OUTPUT);
  pinMode(SENSOR_DIR, OUTPUT);
  pinMode(SENSOR_STEP, OUTPUT);
  pinMode(SENSOR_LSWITCH, INPUT_PULLUP);
  pinMode(SENSOR_RSWITCH, INPUT_PULLUP);
  // Sadly there was no time to add the xy limit switches. RIP
  //pinMode(X_RSWITCH, OUTPUT);
  //pinMode(X_LSWITCH, OUTPUT);
  digitalWrite(SENSOR_ENABLE, HIGH);
  digitalWrite(SENSOR_DIR, LOW);
  digitalWrite(SENSOR_STEP, LOW);
	digitalWrite(DR_PIN,LOW);
  // Setting default values
	sensorTasklist[SENSOR_MAX] = 300;
	sensorTasklist[SENSOR_MIN] = -300;
	heatingInfo.heatingActual = map(HEATING_DEFAULT_PERCENT,0,100,0,200);
	heatingInfo.heatingPercent = HEATING_DEFAULT_PERCENT;
	cmdInfo.cmdBuffer = cmdBuffer;
	replyInfo.cmdBuffer = replyBuffer;
  // We initialize each servo position with -1, which means no servo.
  // Also, we attach and detach each servo position to prevent floating servo signals at startup.
	for (int i = 0; i < SERVO_SLOTS; i++) {
    servoInfo.servos[0].attach(i+1+SERVO_PIN_OFFSET);
		servoInfo.slots[i] = -1;
    delay(20);
    servoInfo.servos[0].detach();
	}
	for (int i = 0; i < SERVO_AMOUNT; i++) {
		servoInfo.states[i] = 1;
		servoInfo.delays[i] = SERVO_DEFAULT_DELAY_U;
		servoInfo.holdDelays[i] = SERVO_DEFAULT_HOLD_DELAY;
	}
	// Actual initialization of the machine. We set the proper speed for the machine, set the heating to max for 60 seconds
  // And we home the steppers
  injectCommand(ringBufferInfo, "heati");
  injectCommand(ringBufferInfo, "sap(1,4,400)");
  injectCommand(ringBufferInfo, "sap(2,4,200)");
  /*
  injectCommand(ringBufferInfo, "sap(1,194,2000)");
  injectCommand(ringBufferInfo, "sap(2,194,2000)");
  */
  /*
  injectCommand(ringBufferInfo, "sap(1,140,7)");
  injectCommand(ringBufferInfo, "sap(2,140,7)");
  */
  /*
  injectCommand(ringBufferInfo, "sap(1,140,7)");
  injectCommand(ringBufferInfo, "sap(2,140,7)");
  */
  //injectCommand(ringBufferInfo, "homexy");
	timers[LOOP_TIMER] = millis();
}

void loop() {
	// Check if serial line has data for us. It will be stored in the cmdInfo struct.
	if (!cmdInfo.newCmd && !(homeInfo.homeXFlag || homeInfo.homeYFlag)) {
		cmdInfo = getCommand(cmdInfo, Serial);
		if (replyInfo.errorNmbr) {
			// The command or the buffer had some error. Print complaint.
	  	Serial.print("Command buffer error -	");
	  	Serial.println(cmdInfo.errorNmbr);
	  	cmdInfo.errorNmbr = 0;
	  	cmdInfo.newCmd = 0;
	  	cmdInfo.dataIndex = 0;
	  }
	}
  // Check if the flag for a new command has been raised. (data contained a newline)
	if (cmdInfo.newCmd && !(homeInfo.homeXFlag || homeInfo.homeYFlag)) {
		// We have a new command. Copy it to our command ring buffer.
		injectCommand(ringBufferInfo,cmdInfo.cmdBuffer);
		cmdInfo.newCmd = 0;
		cmdInfo.dataIndex = 0;
	}
	// Process a command from the ringbuffer if there are any and we are not waiting.
	// Wait is issued when a command is sent to the XY-plan motors to reduce communication
	// errors.
	if (!replyFlag && ringBufferInfo.commandCount > 0) {
		String incCommand = grabRingBufferCommand(ringBufferInfo);
		parseResult result = evaluateCommand(incCommand, commandWordInfo, Serial);
		if (result.errorStatus) {
			Serial.print("Parsing error, code: ");
			Serial.println(result.errorStatus);
      if (result.errorStatus == E_COMMAND_MALFORMED) {
        Serial.println("Command malformed");
      }
			//Serial.println("Send command errl to list codes.");
		}
		else {
			switch (commandWordInfo[result.commandIndex].commandType) {
				case 1:
					sendMotorCommand(timers, result, commandWordInfo);			
					break;			
				case 2:
					sendServoCommand(timers, result, commandWordInfo, servoInfo, Serial);
					break;			
				case 3:
					sendSensorCommand(timers, result, commandWordInfo, sensorTasklist, Serial);
					break;		
				case 4:
					sendHeatingCommand(timers, result, commandWordInfo, heatingInfo, Serial);
					break;
				case 5:
					sendControlCommand(timers, result, commandWordInfo, ringBufferInfo, Serial, homeInfo, sensorTasklist);
					break;	
				default:
					Serial.print("Unknown command type.");
			}		
			replyFlag = 1;
		}
	}

	// Here we process the wait timer. Once the timer is ready (or the processed command
	// set no timer, we display whatever reply we got back to user and allow further
	// command processing.
  if (timers[REPLY_TIMER] + REPLY_DELAY < timers[LOOP_TIMER]) {
	  replyInfo = getReply(replyInfo, Serial1);
	  if (replyInfo.errorNmbr) {
	  	Serial.println("Reply buffer error, attempting to clear buffer."); 	
	  	replyInfo.dataIndex = 0;
	  	delay(20);
	  	while (Serial1.available() > 0) {
	  		char trashCan = Serial1.read();
	  	}
	  	Serial.print("Buffer error code:  ");
	  	Serial.println(replyInfo.errorNmbr);
	  	replyInfo.errorNmbr = 0;
	  	Serial.println("Displaying mangled reply: ");
	  	replyInfo.newCmd = 1;  	
	  }
	  if (replyInfo.newCmd) { 
	  	if (homeInfo.homeXFlag && homeInfo.replyCount > 0) {
        // If we are ignoring repliess, do so and subtract from the reply count.
	  		homeInfo.replyCount -= 1;
	  	}
	  	if (homeInfo.homeXFlag && homeInfo.replyCount == 0) {
	  		if (((long*)(replyInfo.cmdBuffer))[1] == 0 && replyInfo.cmdBuffer[3] == 13 && replyInfo.cmdBuffer[1] == 1) {
          // If we are not ignoring replies and were are homing, we will ask if x-axis is homed until it is
          // Then we do the same for y-axis
	  			homeInfo.homeXFlag = 0;
	  			homeInfo.homeYFlag = 1;
	  		}
	  	}
	  	else if (homeInfo.homeYFlag) {
	  		if (((long*)(replyInfo.cmdBuffer))[1] == 0 && replyInfo.cmdBuffer[3] == 13 && replyInfo.cmdBuffer[1] == 2) {
          // If we are here, y-axis homing is done as well now
	  			homeInfo.homeYFlag = 0;
          // At the end of the homing sequence, we put the sensor over the corner of the board.
          injectCommand(ringBufferInfo, "xypos(0,0)");
	  		}
	  	}
	    displayReply(replyInfo,Serial);
	    replyInfo.dataIndex = 0;
	    replyInfo.newCmd = 0;
	  }
  	replyFlag = 0;
  }
	// Sensor loop executes steps if a command added steps to be taken into the tasklist.
	sensorLoop(sensorTasklist, timers, homeInfo, Serial);
	// Servo loop rocks the servos back and forth, if any are attached.
  servoLoop(servoInfo,timers);
  // Loop to check if timed heating should be still active
  if (heatingInfo.heatingFlag) {
  	heatingLoop(heatingInfo,timers,Serial);
  }
  // Home loop in case we are homing
  if (homeInfo.homeXFlag || homeInfo.homeYFlag) {
  	homeLoop(ringBufferInfo, timers, homeInfo);
  }
  // Timer advancement.
  timers[LOOP_TIMER] = millis();
  timers[MICRO_LOOP_TIMER] = micros();
  // Arduino microsecond timer rolls over every 70 minutes or so.
  // When this happens, we must reset servo timers or they might get stuck.
  if (timers[MICRO_LOOP_TIMER] < timers[OLD_MICRO_TIMER]) {
  	for (int i = 0; i < SERVO_AMOUNT; i++) {
  		servoInfo.timers[i] = 0;
  	}
  }
}
