#define MOTOR_LEFT 3
#define MOTOR_RIGHT 11
#define IR_LEFT A6
#define IR_RIGHT A2
#define IR_MID A3
#define LED_RED 7
#define LED_BLUE 5
#define LED_GREEN 6
// Change motor speed
int speedL = 170;
int speedR = 120;
int count = 0;

void setup() {
  pinMode(MOTOR_LEFT, OUTPUT);
  pinMode(MOTOR_RIGHT, OUTPUT);
  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);
  pinMode(IR_MID, INPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  Serial.begin(9600);
}

 bool firstLine = false;
 bool passedFirstLine = false;

 int startTime = 0;
 //int currentTime = 0;
  
void loop() {
  // Detect light
  int ir_left = analogRead(IR_LEFT);
  ir_left = map(ir_left, 120, 434, 0, 255);
  int ir_right = analogRead(IR_RIGHT);
  ir_right = map(ir_right, 100, 158, 0, 255);
  int ir_mid = analogRead(IR_MID);
  ir_mid = map(ir_mid, 120, 146, 0, 255); 

  Serial.print("left: ");
  Serial.print(ir_left);
  Serial.print(" mid: ");
  Serial.print(ir_mid);
  Serial.print(" right: ");
  Serial.println(ir_right);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, LOW);

if (ir_right < 100 && ir_left < 100 && !firstLine)
{//end case
  firstLine = true;
}

if ( (ir_right >= 20 || ir_left >= 20) && firstLine )
{
  passedFirstLine = true;
  startTime = millis();
}

if (ir_right < 100 && ir_left < 100  && passedFirstLine){ //end case
  {
    if( millis() - startTime > 1000 )
    {
      firstLine = false;
      passedFirstLine = false;
    }
    else
    {
    analogWrite(MOTOR_LEFT, LOW);
    analogWrite(MOTOR_RIGHT, LOW);
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_BLUE, HIGH);
    while (passedFirstLine) {}
    }
  }
  
  speedL = 166;
  speedR = 110;
  digitalWrite(LED_GREEN, HIGH);
}

else if (ir_mid < 20 ){
  speedL = 170;
  speedR = 115;
  digitalWrite(LED_GREEN, HIGH);
}

else if ( ir_left < 195){ //left turn
  speedL = 50;
  speedR = 130;
  digitalWrite(LED_BLUE, HIGH);
}

else if ( ir_right < 184){ //right turn
  speedL = 175;
  speedR = 30;
  digitalWrite(LED_RED, HIGH);
}

else { //middle
  speedL = 170;
  speedR = 115;
  digitalWrite(LED_GREEN, HIGH);
}

  // Set the motor 
  analogWrite(MOTOR_LEFT, speedL);
  analogWrite(MOTOR_RIGHT, speedR);
}

