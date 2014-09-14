// Light Sensor LSS05
// Connect LSS05 O1-05 to Arduino digital pins
// I use 0-4 on Leonardo

// Initate state of LSS05 outputs
int LSS[] = {
  0, 0, 0, 0, 0};

// Start & End pin for LSS05 O1-O5 on Arduino
int LSSStartPin = 0;
int LSSEndPin = 4;

// State to control robot (not sure good idea)
// 0 - Ready
// 1 - Move
// 2 - Pick up ball
// 3 - Drop ball
// 4 - Something is wrong
// 5 - END
int STATE = 0; 

void setup() {
  Serial.begin(9600);
}

void loop() {    
  axReadLSS(); 
  axMoveForward() ;    
  axPickupBall();
  // Extra simulation
}

// Get the value of LSS05 and assign them to global
void axReadLSS() {  
  for(int i = LSSStartPin; i <= LSSEndPin; i ++) {
    pinMode(i, INPUT);
    LSS[i] = digitalRead(i);
  }
}

// Move forward autonomously
void axMoveForward() {
  //   0,1,1,1,0 : move forward
  if(LSS[0] == 0 && LSS[1] == 1 && LSS[2] == 1 && LSS[3] == 1 && LSS[4] == 0) {
    bothWheelsOn();
  } 
  else {
    Serial.println("Stop moving");
  }
}

// Pickup the ball 
void axPickupBall(){
  pinMode(6, OUTPUT); // Indicates robot is picking up ball
  pinMode(7, OUTPUT); // Indicates robot has done picking up ball and ready to go
  STATE = 2;

  //  1,1,1,1,1 : stop to pick ball
  if(LSS[0] == 1 && LSS[1] == 1 && LSS[2] == 1 && LSS[3] == 1 && LSS[4] == 1) {
    Serial.println("Stop to pick ball");
    digitalWrite(6, HIGH);
    Serial.println("Picking up ball");
    delay(2000);
    digitalWrite(6, LOW);
    Serial.println("Ball has been picked");
    delay(2000);
    digitalWrite(7, HIGH);
    bothWheelsOn();
  }
}

// Simulate both wheels turn on
void bothWheelsOn() {
  Serial.println("Move forward");
  STATE = 1;
}



