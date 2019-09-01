#ifndef RIGSOFTWARE_H
#define RIGSOFTWARE_H
#include <Arduino.h>
#include <Servo.h>
/*
 * User input command buffer length
 */
#define CMD_BUFFER_LEN 							32
/*
 * User input command buffer length
 */
#define CMD_RING_BUFFER_LEN 				20

/*
 * Minimum length of a command in characters
 */
#define CMD_MIN_LEN									3
/*
 * Pandrive stepper message length
 */
#define STEPPER_LEN 								9

/*
 * Error codes
 */
#define E_BUFFER_FULL 	 						111
#define E_CHECKSUM_OFF							222
#define E_COMMAND_MALFORMED					333
#define E_CONSTRAINT								444
#define E_NOTFOUND									404

/*
 * Stepper rs-485 D/R pin
 */
#define DR_PIN											3
/*
 * Heat control pin
 */
#define HEATING_PIN									13
/*
 * Maximum command arguments
 */
#define MAX_ARGS										5
/*
 * Number of motor info fields
 */
#define MI_FIELDS										5
#define MI_BYTE_LEN									8
/*
 * The number of user commands recognized by the software
 */
#define COMMAND_LIST_SIZE						24
/*
 * Timer and timing definitions
 */
#define LOOP_TIMER									0
#define SENSOR_STEP_TIMER						1
#define REPLY_TIMER									2
#define HOME_TIMER									3
#define MICRO_LOOP_TIMER						4
#define LIMIT_SWITCH_TIMER					5
#define HEATING_TIMER								6
#define OLD_MICRO_TIMER							7

#define TIMER_LEN										8

#define SENSOR_STEP_DELAY						1
#define REPLY_DELAY									250
#define HOME_DELAY									2000
#define DR_LINE_DELAY_U							0
#define SERVO_DEFAULT_DELAY_U				20000
#define SERVO_UPPER_DELAY_U					30000
#define SERVO_LOWER_DELAY_U					3000
#define LIMIT_SWITCH_DELAY					1000
#define HEATING_DELAY								60000
#define SERVO_DEFAULT_HOLD_DELAY		3000						
/*
 * Sensor tasklist definitions
 */
#define SENSOR_STEPS								0
#define SENSOR_POS									1
#define SENSOR_MAX									2
#define SENSOR_MIN									3
#define SENSOR_HOME									4
#define SENSOR_TASKLIST_LEN					5

/*
 * Sensor steps to angle conversion
 */
#define STEPS_TO_ANGLE							0.45F
/*
 * XY steps to millimeter conversion
 */
#define STEPS_TO_MM									-700.0F
/*
 * Sensor home correction
 */
#define SENSOR_HOME_CORR            4
/*
 * Max number of servos and slots to put them in
 */
#define SERVO_AMOUNT								10
#define SERVO_SLOTS									32

/*
 * Servo max and min angles
 */
#define MAX_ANGLE										110
#define MIN_ANGLE										70

/*
 * XY plane stepper max and min positions.
 */
#define X_OFFSET										0
#define Y_OFFSET										50

/*
 * Arduino mega pin offset for the 32 pin slot.
 */
#define SERVO_PIN_OFFSET						21
/*
 * Sensor stepper pin definitions
 */
#define SENSOR_ENABLE								6
#define SENSOR_DIR									4
#define SENSOR_STEP									5
#define SENSOR_LSWITCH							8
#define SENSOR_RSWITCH							7

#define X_RSWITCH										9
#define X_LSWITCH										10
#define Y_RSWITCH										11
#define Y_LSWITCH										12

#define HEATING_DEFAULT_PERCENT			25
/*
 * Struct for holding getCommand information.
 * 
 * @param cmdBuffer			Pointer to the buffer to store incoming data
 * @param dataIndex			Holds the data index where to start in the buffer
 * @param newCmd				Flag whether a command has been completed and should be parsed.
 * @param errorNmbr			Holds the error code for the command listener
 */
typedef struct 
{
	char *cmdBuffer;
	int dataIndex;
	int newCmd;
	int errorNmbr;
} commandInfo;
/*
 * This struct holds information related to homing the XY plane
 */
typedef struct 
{
	int replyCount;
	int homeXFlag;
	int homeYFlag;
	int sensorHomeFlag;
	int homedFlag;
} homeInfoStruct;
/*
 * This is the ring buffer for holding commands before they are executed.
 */
typedef struct
{
  int ringInputIndex;
  int ringOutputIndex;
  int commandCount;
  char cmdRingBuffer[CMD_RING_BUFFER_LEN][CMD_BUFFER_LEN];
} ringBufferInfoStruct;
/*
 * This struct stores the proper datafields for sending a PANdrive stepper command
 */
typedef struct
{
	char moduleAddress;				//Module address
	char command;							//Command
	char commandType;					//Type
	char motorBank;						//Motor/bank
	long motorValue;
} motorInfoStruct;


/*
 * Union for accessing the motorInfoStruct via direct byte array access.
 */
typedef union {
	byte bytes[MI_BYTE_LEN];
	motorInfoStruct motorInfo;
} motorInfoUnion;

/*
 * This behemoth contains the full command format definition accepted by the command functions.
 */
typedef struct {
	int commandType;
	const char* commandWord;
	int commandWordLen;
	int numOfArgs;
	int argFields[MI_FIELDS];
	long lowerConst[MI_FIELDS];
	long upperConst[MI_FIELDS];
	motorInfoUnion mi;
} commandWordInfoStruct;

/*
 * Struct to store information parsed out of a command.
 */
typedef struct 
{
	int commandIndex;
	int errorStatus;
	long args[MAX_ARGS];
} parseResult;

/*
 * Struct to store all servo related things.
 */
typedef struct
{
	Servo servos[SERVO_AMOUNT];
	int pos[SERVO_AMOUNT];
	int states[SERVO_AMOUNT];
	int slots[SERVO_SLOTS];
	unsigned long timers[SERVO_AMOUNT];
	unsigned long holdTimers[SERVO_AMOUNT];
	unsigned long delays[SERVO_AMOUNT];
	unsigned long holdDelays[SERVO_AMOUNT];
	int modeFlags[SERVO_AMOUNT];
} servoInfoStruct;

/*
 * Struct to store heating related things.
 */
typedef struct
{
	int heatingPercent;
	int heatingActual;
	int heatingFlag;
} heatingInfoStruct;

/*
 * The function declarations. There were more to be made than I initially expected. The inputs are quite bloated too, maybe I should have left Serials as a global thing.
 */
parseResult evaluateCommand(String incString, commandWordInfoStruct* commandWordInfo, HardwareSerial &rSerial);
commandInfo getCommand(commandInfo info, HardwareSerial &rSerial);
commandInfo getReply(commandInfo info, HardwareSerial &rSerial);
int parseMotorReply(char *outBuffer, char *inBuffer);
void sendMotorCommand(unsigned long *timers, parseResult &result, commandWordInfoStruct *commandWordInfo);
void sendServoCommand(unsigned long *timers, parseResult &result, commandWordInfoStruct *commandWordInfo, servoInfoStruct &servoInfo, HardwareSerial &rSerial);
void sendSensorCommand(unsigned long *timers, parseResult &result, commandWordInfoStruct *commandWordInfo, int *sensorTasklist, HardwareSerial &rSerial);
void sendHeatingCommand(unsigned long *timers, heatingInfoStruct &heatingInfo, parseResult &result, commandWordInfoStruct *commandWordInfo, HardwareSerial &rSerial);
void sendControlCommand(unsigned long *timers, parseResult result, commandWordInfoStruct *commandWordInfo, ringBufferInfoStruct &ringBufferInfo, HardwareSerial &rSerial, homeInfoStruct &homeInfo, int *sensorTasklist);
parseResult parseCommandString(String cmdString, int nbrOfArgs, int stringLen);
//int parseAndSendUserCommand(String incCommand, HardwareSerial &rSerial, int *tasklist, unsigned long *timers, servoInfoStruct &servoInfo, heatingStruct &heatingInfo);
void displayReply(commandInfo replyInfo, HardwareSerial &rSerial);
void sensorLoop(int *tasklist, unsigned long *timers, homeInfoStruct &homeInfo, HardwareSerial &rSerial);
void servoLoop(servoInfoStruct &servoInfo, unsigned long *timers);
void injectCommand(ringBufferInfoStruct &ringBufferInfo, char *command);
String grabRingBufferCommand(ringBufferInfoStruct &ri);
void homeLoop(ringBufferInfoStruct &ringBufferInfo, unsigned long *timers, homeInfoStruct &homeInfo);
void heatingLoop(heatingInfoStruct &heatingInfo, unsigned long *timers, HardwareSerial &rSerial);

#endif
