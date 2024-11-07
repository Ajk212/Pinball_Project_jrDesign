#include <DFMiniMp3.h>


int MP3Tx = 1;
int MP3Rx = 2;
int hexRESET = 3;
int hexCLK = 4;
int LED1 = 5;
int LED2 = 6;
int LED3 = 7;
int buttonL = 8;
int buttonR = 9;
int pushL = 11;
int pushR = 12;
int irCoin = 25;
int irLauncher = 24;
unsigned long startTime, timePassed;



class Mp3Notify{
public:
    // required type
    typedef void TargetType;

    // required method even though it doesn't do anything
    static void SetTarget(TargetType*)
    {
    }

    static void PrintlnSourceAction(DfMp3_PlaySources source, const char* action)
    {
        if (source & DfMp3_PlaySources_Sd)
        {
            Serial.print("SD Card, ");
        }
        if (source & DfMp3_PlaySources_Usb)
        {
            Serial.print("USB Disk, ");
        }
        if (source & DfMp3_PlaySources_Flash)
        {
            Serial.print("Flash, ");
        }
        Serial.println(action);
    }

    // required method
    static void OnError(uint16_t errorCode)
    {
        // see DfMp3_Error for code meaning
        Serial.println();
        Serial.print("Com Error ");
        Serial.println(errorCode);
    }

    // required method
    static void OnPlayFinished([[maybe_unused]] DfMp3_PlaySources source, uint16_t track)
    {
        Serial.print("Play finished for #");
        Serial.println(track);
    }

    // required method
    static void OnPlaySourceOnline(DfMp3_PlaySources source)
    {
        PrintlnSourceAction(source, "online");
    }

    // required method
    static void OnPlaySourceInserted(DfMp3_PlaySources source)
    {
        PrintlnSourceAction(source, "inserted");
    }

    // required method
    static void OnPlaySourceRemoved(DfMp3_PlaySources source)
    {
        PrintlnSourceAction(source, "removed");
    }
};


SoftwareSerial secondarySerial(2, 1); // RX, TX
typedef DFMiniMp3<SoftwareSerial, Mp3Notify> DfMp3;

DfMp3 dfmp3(secondarySerial);


void setup() {
  // Needed Pin outputs - 1x MP3, 2xHex, 2xPaddle, 
  // Needed Pin inputs - 2x Side Buttons, 2x IR sensor, 1x MP3

  dfmp3.begin(2,1); //Ini mp3
  dfmp3.setVolume(20);
  dfmp3.playFolderTrack(1,1); //Plays game music | Main music is a track, all other commands are "Advertisments" Which only pause the track

  pinMode(MP3Tx, INPUT); //mp3 output

  pinMode(MP3Rx, OUTPUT);//mp3 input
  pinMode(hexRESET, OUTPUT);//hex reset
  pinMode(hexCLK, OUTPUT); //hex clock
  pinMode(LED1, OUTPUT); //hex clock
  pinMode(LED2, OUTPUT); //hex clock
  pinMode(LED3, OUTPUT); //hex clock
  pinMode(pushL, OUTPUT); //Left paddle
  pinMode(pushR, OUTPUT); //right paddle

  pinMode(buttonL, INPUT); //Button L #1
  pinMode(buttonR, INPUT); //Button R #2
  pinMode(irCoin, INPUT); //IR Sensor #1
  pinMode(irLauncher, INPUT); //IR Sensor #2

  randomSeed(analogRead(0));

}

void loop() {
  // put your main code here, to run repeatedly:

  bool lost = false;
  bool gameStart = false;
  int score = 0;
  int actionNum;
  int countDown = 5000; //Countdown is in MILLISECONDS

  while(gameStart == false){
    if(digitalRead(irCoin) == HIGH){
      gameStart = true;
    }
    if(digitalRead(buttonL) == HIGH){
      Lpaddle();
    }
    if(digitalRead(buttonR) == HIGH ){
      Rpaddle();
    }
  }

  while(gameStart == true){

    actionNum = random(1,5);

    if(actionNum == 1){
      lost = call_act1(countDown);
    }
    if(actionNum == 2){
      lost = call_act2(countDown);
    }
    if(actionNum == 3){
      lost = call_act3(countDown);
    }
    if(actionNum == 4){
      lost = call_act4(countDown);
    }

    if(lost == true){
      //Display endgame items
      lostSeq();
      gameStart = false;
      break;
    }

    score++;
    //Play win ding?

    if(score == 99){
      winSeq();
    }

    updateScore();

    if(countDown > 1000){
      countDown -= 250;
    }

  }


}


bool call_act1(int cd){
  
  //Tell user to press left button through MP3
  dfmp3.playAdvertisment(X); //Unknown file numbers, fill when deciced
  //sets countdown timer 
  startTime = millis();
  timePassed = 0;

  //if action is complete within time limit, return false
  //if incorrect action or timer runout, return true
  while(timePassed < cd) {

    timePassed = millis() - startTime;

    if(digitalRead(buttonL) == HIGH){
      LPaddle();
      return false;
    }

    if(digitalRead(buttonR) == HIGH){
      RPaddle();
      return true;
    }

    if(analogRead(irLauncher) == HIGH || analogRead(irCoin) == HIGH){ //Check if correct useage of analog input
      return true;
    }
  }
  //If not completed in alloted time, sets loss to true
  return true;
}

bool call_act2(int cd){
  
  //Tell user to press right button through MP3
  dfmp3.playAdvertisment(X+1); //Unknown file numbers, fill when deciced
  //sets countdown timer 
  startTime = millis();
  timePassed = 0;

  //if action is complete within time limit, return false
  //if incorrect action or timer runout, return true
  while(timePassed < cd) {

    timePassed = millis() - startTime;

    if(digitalRead(buttonR) == HIGH){
      RPaddle();
      return false;
    }

    if(digitalRead(buttonL) == HIGH){
      LPaddle();
      return true;
    }

    if(analogRead(irLauncher) == HIGH || analogRead(irCoin) == HIGH){
      return true;
    }

  }
  //If not completed in alloted time, sets loss to true
  return true;
}

bool call_act3(int cd){
  
  //Tell user to pull ball launcher through MP3
  dfmp3.playAdvertisment(X+2); //Unknown file numbers, fill when deciced
  //sets countdown timer 
  startTime = millis();
  timePassed = 0;

  //if action is complete within time limit, return false
  //if incorrect action or timer runout, return true
  while(timePassed < cd) {

    timePassed = millis() - startTime;

    if(analogRead(irLauncher) == HIGH){
      return false;
    }

    if(digitalRead(buttonL) == HIGH){
      LPaddle();
      return true;
    }

    if(digitalRead(buttonR) == HIGH){
      RPaddle();
      return true;
    }

    if(analogRead(irCoin) == HIGH){
      return true;
    }

  }
  //If not completed in alloted time, sets loss to true
  return true;
}

bool call_act4(int cd){
  
  //Tell user to insert coin through MP3
  dfmp3.playAdvertisment(X+3); //Unknown file numbers, fill when deciced

  //sets countdown timer 
  startTime = millis();
  timePassed = 0;

  //if action is complete within time limit, return false
  //if incorrect action or timer runout, return true
  while(timePassed < cd) {

    timePassed = millis() - startTime;

    if(analogRead(irCoin) == HIGH){
      return false;
    }

    if(digitalRead(buttonL) == HIGH){
      LPaddle();
      return true;
    }

    if(digitalRead(buttonR) == HIGH){
      RPaddle();
      return true;
    }

    if(analogRead(irLauncher) == HIGH){
      return true;
    }

  }
  //If not completed in alloted time, sets loss to true
  return true;
}

void updateScore(){
  //Sends clock signal to hex displays
    digitalWrite(hexCLK, HIGH);
    delay(1); 
    digitalWrite(hexCLK, LOW);
}

void resetScore(){
    //Sends reset signal to hex displays
    digitalWrite(hexRESET, HIGH);
    delay(1); 
    digitalWrite(hexRESET, LOW);
}

void LPaddle(){
    //sends signal to left paddle to flip
    digitalWrite(pushL, HIGH);
    delay(1); 
    digitalWrite(pushL, LOW);
}

void RPaddle(){
    //sends signal to right paddle to flip
    digitalWrite(pushR, HIGH);
    delay(1); 
    digitalWrite(pushR, LOW);
}

void winSeq(){
  //Flashes score and LEDs

  //Plays victory music

  //"Good Job!" Audio?


}

void lostSeq(){
  //Gives final look at score

  //Plays loser music

  //Returns to pre game loop

  //"Try again?"" audio?
}
