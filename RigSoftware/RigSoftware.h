/*
 * Written by Ville Hiltunen (2019) villejhiltunen@gmail.com under MIT license.
 */

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
#define COMMAND_LIST_SIZE						23
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
// Tweak the DR_LINE_DELAY_U to control how long we wait after setting the D/R line before actually sending
// a command to the stepper motors. In earlier prototypes the D/R line reacted too slowly and the 
// first bits of the message would get cut
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
 * XY plane stepper max and min positions
 */
#define X_OFFSET										0
#define Y_OFFSET										50

/*
 * Arduino mega pin offset for the 32 pin slot
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
 * @param newCmd				Flag whether a command has been completed and should be parsed
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
 * 
 * @param replyCount      Counts downwards each time a reply is read and ignores the reply. Used for homing XY-plane
 * @param homeXFlag       Flag for x-axis homing state
 * @param homeYFlag       Flag for y-axis homing state
 * @param sensorHomeFlag  Flag for whether homing is in progress
 * @param homedFlag       Flag whether the XY-plane is homed. Disallows xypos unless set
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
 * This is the ring buffer for holding commands before they are executed
 * 
 * @param ringInputIndex    The index where the next command should be inserted
 * @param ringOutputIndex   The index where the next command should be read
 * @param commandCount      How many unread commands the ring buffer holds
 * @param cmdRingBuffer     Pointer to the ring buffer. This is an array of arrays
 */
typedef struct
{
  int ringInputIndex;
  int ringOutputIndex;
  int commandCount; //TODO: Handle ring buffer overflow when commandCount > CMD_RING_BUFFER_LEN
  char cmdRingBuffer[CMD_RING_BUFFER_LEN][CMD_BUFFER_LEN];
} ringBufferInfoStruct;
/*
 * This struct stores the proper datafields for sending a PANdrive stepper command
 * Note that not all fields are relevant with all commands. See PD42 firmware manual for more info
 * 
 * @param moduleAddress    Address of the motor. The motors are set to 1 and 2 but can be redefined using SAP
 * @param command          The command instruction number for the motor
 * @param commandType      The subtype of the command
 * @param motorBank        The memory bank the command targets
 * @param motorValue       Value field of the command
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
 * Union for accessing the motorInfoStruct via direct byte array access
 * 
 * @param bytes            byte access to the union
 * @param motorInfo        the motorInfo, as defined above
 */
typedef union {
	byte bytes[MI_BYTE_LEN];
	motorInfoStruct motorInfo;
} motorInfoUnion;

/*
 * This behemoth contains the full command format definition accepted by the command functions
 * 
 * Read the detailed usage description in the main file
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
 * Struct to store information parsed out of a command
 */
typedef struct 
{
	int commandIndex;
	int errorStatus;
	long args[MAX_ARGS];
} parseResult;

/*
 * Struct to store all servo related things.
 * 
 * @param servos      An array of our Arduino defined servo objects
 * @param pos         The angular position of each servo
 * @param states      The direction of each servo
 * @param slots       The field of 32 possible positions for a servo to be attached in
 *                    -1 means it is empty, 0-9 means it is occupied with the servo from servos with the same index.
 * @param timers      When the servo last moved an angle
 * @param holdTimers  When the servo last went into holding
 * @param delays      How long to wait between each angle
 * @param holdDelays  How long to hold at the ends of the motion
 * @param modeFlags   The hold mode of a servo. 0 means constant sway, 1 means stop at min and max angles for hold duration.
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
 * 
 * @param heatingPercent    What percentage of the full power we are currently heating with
 * @param heatingActual     The percentage in an integer number from 0-255 for PWM output
 * @param heatingFlag       Whether we are still in initial heating mode.
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
void sendMotorCommand(unsigned long *timers, parseResult &result, commandWordInfoStruct *commandWordInfo);
void sendServoCommand(unsigned long *timers, parseResult &result, commandWordInfoStruct *commandWordInfo, servoInfoStruct &servoInfo, HardwareSerial &rSerial);
void sendSensorCommand(unsigned long *timers, parseResult &result, commandWordInfoStruct *commandWordInfo, int *sensorTasklist, HardwareSerial &rSerial);
void sendHeatingCommand(unsigned long *timers, parseResult &result, commandWordInfoStruct *commandWordInfo, heatingInfoStruct &heatingInfo, HardwareSerial &rSerial);
void sendControlCommand(unsigned long *timers, parseResult result, commandWordInfoStruct *commandWordInfo, ringBufferInfoStruct &ringBufferInfo, HardwareSerial &rSerial, homeInfoStruct &homeInfo, int *sensorTasklist);
parseResult parseCommandString(String cmdString, int nbrOfArgs, int stringLen, int cmdWordLen);
void displayReply(commandInfo replyInfo, HardwareSerial &rSerial);
void sensorLoop(int *tasklist, unsigned long *timers, homeInfoStruct &homeInfo, HardwareSerial &rSerial);
void servoLoop(servoInfoStruct &servoInfo, unsigned long *timers);
void injectCommand(ringBufferInfoStruct &ringBufferInfo, char *command);
String grabRingBufferCommand(ringBufferInfoStruct &ri);
void homeLoop(ringBufferInfoStruct &ringBufferInfo, unsigned long *timers, homeInfoStruct &homeInfo);
void heatingLoop(heatingInfoStruct &heatingInfo, unsigned long *timers, HardwareSerial &rSerial);

#endif
