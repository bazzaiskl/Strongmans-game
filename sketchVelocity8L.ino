//sketch for the strongmans game
#include<Wire.h>

//-----globals-----//
//--behvaiour knobs--//
  //change these value to change the difficulty of the game(how are you have to hit)
int hitSense = 500; //minimium value to register a hit, this removed noise causeing it to trigger
float topScore = 32768; //this is the value a max score minus the scale, max of sensor (0.5*2^16)(32768)
float easy = 6000; //sets the topScore to this when on easy mode
float hard = 13500; //sets the topScore to this when on hard mode
float scale = 3001;//a constant that adds to the hit score

//--pins--//
int L1 =2;
int L2 = 3;
int L3 = 4;
int L4 = 5;
int L5 = 6;
int L6 = 7;
int L7 = 8;
int L8 = 9;
int LTotal = 8; //total number of lights
int difficultySwitch = 10;
int resetSwitch = 12;


//other
const int MPU6050_addr = 0x68; //address for the IMU sensor
int16_t VelX, VelY, VelZ, Vel;

//initilzation variables 
bool initComplete = 0;
int16_t initVel = 0;

//recording 
int16_t recordArray[100];
int rPos = 0;

//---functions---//
//sensor
void getData() {
  //gets the data from the MPU6050
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x43);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_addr, 14, true);
  VelX = Wire.read() << 8 | Wire.read();
  VelY = Wire.read() << 8 | Wire.read();
  VelZ = Wire.read() << 8 | Wire.read();
  Vel = VelZ; //only measures Z axis rotation, this changes on how you mount it
}

void getInit() {
  //gets the base velocity when the sensor is stationary
  //takes 3 reading and forms an average
  Serial.println("initilzing sensor");
  int16_t  initArray[3];
  int readings = 3;
  for (int i = 0; i < readings; i++) {
    getData();
    initArray[i] = abs(Vel);
    delay(100);
  }
  int sum = 0;
  for (int j = 0; j < readings; j++) {
    sum = sum + initArray[j];
  }
  initVel = sum / readings;
  Serial.print("initilzing complete init score is: ");
  Serial.println(initVel);
  return;
}

int score(int16_t VelMax) {
  
  //determines score of hit currently linear progression, may be better to use logetihmic(how our minds work) or parabolic(how gravity works)
  if (VelMax >= topScore + scale) {
    return 8;
  }
  if (VelMax >= (topScore * (7/8.0) + scale)) {
    //Serial.println((topScore * (4/5.0)+scale ));
    return 7;
  }
  if (VelMax >= (topScore * (6/ 8.0) + scale)) {
    return 6;
  }
  if (VelMax >= (topScore * (5 / 8.0) + scale)) {
    return 5;
  }
  if (VelMax >= (topScore * (4 / 8.0) + scale)) {
    return 4;
  }
  if (VelMax >= (topScore * (3 / 8.0) + scale)) {
    return 3;
  }
  if (VelMax >= (topScore * (2 / 8.0) + scale)) {
    return 2;
  }
  if (VelMax >= (topScore * (1 / 8.0) + scale)) {
    return 1;
  }
  return 0;
}

int measure() {
  //waits in this loop for a hit, 
  int16_t VelMax = 0;;
  bool hit = false;
  
  while (true) {
    reset();
    getDifficulty();
    getData();
    //if its been hit, it measures the hit and many times as it can. then takes the max score from them
    if (Vel > initVel * hitSense) {
      Serial.print("HIT score: ");
      Serial.println(Vel);
      hit = true;

      if (Vel > VelMax) {
        Serial.print("NEW TOP score: ");
        Serial.println(Vel);
        VelMax = Vel;
      }
    }
    if (hit == true) {
      //checks to ensure that the sensor has stopped moving before recording final score
      Serial.println("attempt stop");
      if (Vel < initVel * hitSense) {
        Serial.print("HIT complete max score: ");
        Serial.println(VelMax);
        
        int s = score(VelMax);
        delay(1000);
        return s;
      }
    }
  }
}

int lightUp(int score){
//takes a score from 1 to 8 (8 being the highest and turns leds on in a certain pattern
  if (score == 1) {
    digitalWrite(L1,HIGH);
    return 0;
  }

  if (score == 2) {
    digitalWrite(L1,HIGH);
    delay(2000);
    digitalWrite(L2, HIGH);
    return 0;
  }

  if (score == 3) {
    digitalWrite(L1,HIGH);
    delay(2000);
    digitalWrite(L2, HIGH);
    delay(2000);
    digitalWrite(L3, HIGH);
    return 0;    
  }

  if (score == 4) {
    digitalWrite(L1,HIGH);
    delay(2000);
    digitalWrite(L2, HIGH);
    delay(2000);
    digitalWrite(L3, HIGH);
    delay(2000);
    digitalWrite(L4, HIGH);
    return 0;    
  }

   if (score == 5) {
    digitalWrite(L1,HIGH);
    delay(2000);
    digitalWrite(L2, HIGH);
    delay(2000);
    digitalWrite(L3, HIGH);
    delay(2000);
    digitalWrite(L4, HIGH);
    delay(2000);
    digitalWrite(L5, HIGH);
    return 0;      
  }

  if (score == 6) {
    digitalWrite(L1,HIGH);
    delay(2000);
    digitalWrite(L2, HIGH);
    delay(2000);
    digitalWrite(L3, HIGH);
    delay(2000);
    digitalWrite(L4, HIGH);
    delay(2000);
    digitalWrite(L5, HIGH);
    delay(2000);
    digitalWrite(L6, HIGH);
    return 0;      
  }

  if (score == 7) {
    digitalWrite(L1,HIGH);
    delay(2000);
    digitalWrite(L2, HIGH);
    delay(2000);
    digitalWrite(L3, HIGH);
    delay(2000);
    digitalWrite(L4, HIGH);
    delay(2000);
    digitalWrite(L5, HIGH);
    delay(2000);
    digitalWrite(L6, HIGH);
    delay(2000);
    digitalWrite(L7, HIGH);
    return 0;      
  }

  if (score == 8) {
    digitalWrite(L1,HIGH);
    delay(2000);
    digitalWrite(L2, HIGH);
    delay(2000);
    digitalWrite(L3, HIGH);
    delay(2000);
    digitalWrite(L4, HIGH);
    delay(2000);
    digitalWrite(L5, HIGH);
    delay(2000);
    digitalWrite(L6, HIGH);
    delay(2000);
    digitalWrite(L7, HIGH);
    delay(3000);
    digitalWrite(L8, HIGH); //here L8 is a bell we would like to auto shut off
    delay(5000);
    digitalWrite(L8, LOW);
    return 0;      
  }
 return -1;  
}

int getDifficulty(){
  //sets the topScore global dependent on difficulty
  int  bPress = digitalRead(difficultySwitch);
  //Serial.println(bPress);
  if (bPress == HIGH){
    topScore = easy;
    return 1;
  }
  if (bPress == LOW){
    topScore = hard;
    return 0;
  }  
  return -1;
}

int reset(){
  //resets the game by turning all ligths off
  int bPress = digitalRead(resetSwitch);
  if(bPress == LOW){
    digitalWrite(L1, LOW);
    digitalWrite(L2, LOW);
    digitalWrite(L3, LOW);
    digitalWrite(L4, LOW);
    digitalWrite(L5, LOW);
    digitalWrite(L6, LOW);
    digitalWrite(L7, LOW);
    digitalWrite(L8, LOW);
    Serial.print("difficulty is ");
    Serial.println(topScore);
    delay(100);
    Serial.println("reset sucessful");
    return 0;
  }
  return 1;
}

void setup() {
  // put your setup code here, to run once:
  //lights setup
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
  pinMode(L4, OUTPUT);
  pinMode(L5, OUTPUT);
  pinMode(L6, OUTPUT);
  pinMode(L7, OUTPUT);
  pinMode(L8, OUTPUT);

  //turn all off to begin
  
  digitalWrite(L1, LOW);
  digitalWrite(L2, LOW);
  digitalWrite(L3, LOW);
  digitalWrite(L4, LOW);
  digitalWrite(L5, LOW);
  digitalWrite(L6, LOW);
  digitalWrite(L7, LOW);
  digitalWrite(L8, LOW);
  
  pinMode(difficultySwitch, INPUT_PULLUP);
  pinMode(resetSwitch, INPUT_PULLUP);

//sensor setup
  Wire.begin();
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x6B);
  Wire.write(0);

  Wire.endTransmission(true);
  //set the sensitvity to 2000deg/sec
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x1B);
  Wire.write(0x18);
  Wire.endTransmission(true);

  Serial.begin(9600);

  Serial.println("sanity begin");
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x1B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_addr,1,true);
  Serial.println(Wire.read());
  Serial.println("sanity end");

  getInit();
  reset();
  Serial.println("setup Complete");
}

void loop() {
  // put your main code here, to run repeatedly:
  //call measure() to get score, measure is where the code waits for hit
  int difficulty = getDifficulty();
  int points = measure();
  Serial.print("you scored: ");
  Serial.print(points);
  Serial.print(" on difficulty ");
  Serial.println(topScore);
  Serial.println();
  Serial.println();
  Serial.println();
  lightUp(points);
  points =0;
  
  //redundent but too scared to remove
  reset();
}
