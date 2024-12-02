#include "DFRobotDFPlayerMini.h"
#include <SoftwareSerial.h>


int hexRESET = 3;
int hexCLK = 4;
int LED1 = 5;
int LED2 = 6;
//int Launcher = 7;
int buttonL = 8;
int buttonR = 9;
int pushL = 12;
int pushR = 11;
int irCoin = 2;
unsigned long startTime, timePassed;
int voltsC, voltsL; //coin and launcher voltages
int actionNum;

#define irCoin A2

SoftwareSerial mySoftwareSerial(10, 13); // Create a software serial connection on pins 10 (RX) and 11 (TX)
DFRobotDFPlayerMini myDFPlayer;          // Create a DFPlayerMini object

void setup() {
  // Needed Pin outputs - 1x MP3, 2xHex, 2xPaddle, 
  // Needed Pin inputs - 2x Side Buttons, 2x IR sensor, 1x MP3

  //MP3 Setup
  mySoftwareSerial.begin(9600);     // Start software serial communication at 9600 baud rate
  Serial.begin(115200);             // Start serial communication at 115200 baud rate

  if (!myDFPlayer.begin(mySoftwareSerial)) { // Initialize the DFPlayer Mini module
    Serial.println(F("Not initialized:"));
    Serial.println(F("1. Check the DFPlayer Mini connections"));
    Serial.println(F("2. Insert an SD card"));
    while (true);                  // If initialization fails, print error messages and halt the program
  }

  Serial.println();
  Serial.println(F("DFPlayer Mini module initialized!")); // Print initialization success message
  myDFPlayer.setTimeOut(500);       // Set the timeout value for serial communication
  myDFPlayer.volume(30);            // Set the volume level (0 to 30)
  myDFPlayer.EQ(0);                 // Set the equalizer setting (0: Normal, 1: Pop, 2: Rock, 3: Jazz, 4: Classic, 5: Bass)

  pinMode(hexRESET, OUTPUT);//hex reset
  pinMode(hexCLK, OUTPUT); //hex clock
  pinMode(LED1, OUTPUT); 
  pinMode(LED2, OUTPUT); 



  pinMode(pushL, OUTPUT); //Left paddle
  pinMode(pushR, OUTPUT); //right paddle

 // pinMode(Launcher, INPUT);
  pinMode(buttonL, INPUT); //Button L #1
  pinMode(buttonR, INPUT); //Button R #2


  randomSeed(analogRead(0));

}

void loop() {
  delay(5000);
  digitalWrite(hexRESET,LOW);
  bool lost = false;
  bool gameStart = false;
  int score = 0;
  int countDown = 10000; //Countdown is in MILLISECONDS
  myDFPlayer.play(9);


  while(gameStart == false){
    if(digitalRead(buttonL) == HIGH){
      gameStart = true;
      
    }
  }

  while(gameStart == true){
    delay(1000);
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
      lostSeq(score);
      gameStart = false;
      break;
    }

    score++;
    myDFPlayer.play(7);
    delay(1000);

    if(score == 99){
      winSeq(score);
      gameStart = false;
      break;
    }

    updateScore();

    if(countDown > 1000){
      countDown -= 250;
    }

  }


}


bool call_act1(int cd){
  
  //Tell user to press left button through MP3
  myDFPlayer.play(3); //play left button sound
  //sets countdown timer 
  startTime = millis();
  timePassed = 0;

  //if action is complete within time limit, return false
  //if incorrect action or timer runout, return true
  while(timePassed < cd) {

    timePassed = millis() - startTime;

    if(digitalRead(buttonL) == HIGH){
      //LPaddle();
      return false;
    }

    if(digitalRead(buttonR) == HIGH){
      //RPaddle();
      return true;
    }

  //  if(digitalRead(Launcher) == HIGH){
 //     return true;
//    }

    voltsC = analogRead(irCoin);
    delay(15);
    if (voltsC > 605){
      return true;
    }

  }
  //If not completed in alloted time, sets loss to true
  return true;
}

bool call_act2(int cd){
  
  //Tell user to press right button through MP3
  myDFPlayer.play(4); //play right button sound
  //sets countdown timer 
  startTime = millis();
  timePassed = 0;

  //if action is complete within time limit, return false
  //if incorrect action or timer runout, return true
  while(timePassed < cd) {

    timePassed = millis() - startTime;

    if(digitalRead(buttonL) == HIGH){
      //LPaddle();
      return true;
    }

    if(digitalRead(buttonR) == HIGH){
      //RPaddle();
      return false;
    }

 //   if(digitalRead(Launcher) == HIGH){
 //     return true;
 //   }

    voltsC = analogRead(irCoin);
    delay(15);
    if (voltsC > 605){
      return true;
    }

  }
  //If not completed in alloted time, sets loss to true
  return true;
}

bool call_act3(int cd){
  
  //Tell user to pull ball launcher through MP3
  myDFPlayer.play(2);
  //sets countdown timer 
  startTime = millis();
  timePassed = 0;

  //if action is complete within time limit, return false
  //if incorrect action or timer runout, return true
  while(timePassed < cd) {

    timePassed = millis() - startTime;

    if(digitalRead(buttonL) == HIGH){
      //LPaddle();
      return true;
    }

    if(digitalRead(buttonR) == HIGH){
      //RPaddle();
      return true;
    }

  //  if(digitalRead(Launcher) == HIGH){
 //     return false;
 //   }

    voltsC = analogRead(irCoin);
    delay(15);
    if (voltsC > 605){
      return true;
    }

  }
  //If not completed in alloted time, sets loss to true
  return true;
}

bool call_act4(int cd){
  
  //Tell user to insert coin through MP3
  myDFPlayer.play(1);

  //sets countdown timer 
  startTime = millis();
  timePassed = 0;

  //if action is complete within time limit, return false
  //if incorrect action or timer runout, return true
  while(timePassed < cd) {

    timePassed = millis() - startTime;

    if(digitalRead(buttonL) == HIGH){
      //LPaddle();
      return true;
    }

    if(digitalRead(buttonR) == HIGH){
      //RPaddle();
      return true;
    }

    voltsC = analogRead(irCoin);
    delay(15);
    if (voltsC > 605){
      return false;
    }

//    if(digitalRead(Launcher) == HIGH){
//      return true;
//    }

  }
  //If not completed in alloted time, sets loss to true
  return true;
}

void updateScore(){
  //Sends clock signal to hex displays
    digitalWrite(hexCLK, HIGH);
    delay(100); 
    digitalWrite(hexCLK, LOW);
}

void resetScore(){
    //Sends reset signal to hex displays
    digitalWrite(hexRESET, HIGH);
    delay(100); 
    digitalWrite(hexRESET, LOW);
}

void LPaddle(){
    //sends signal to left paddle to flip
    digitalWrite(pushL, HIGH);
    delay(200); 
    digitalWrite(pushL, LOW);
}

void RPaddle(){
    //sends signal to right paddle to flip
    digitalWrite(pushR, HIGH);
    delay(200); 
    digitalWrite(pushR, LOW);
}

void winSeq(int score){
  //Flashes score and LEDs
  digitalWrite(hexRESET, HIGH);
  delay(100);
  digitalWrite(hexRESET, LOW);
  
  for(int i = 0; i < score; i++){
    updateScore();
  }

  //Plays victory music
  myDFPlayer.play(8);


  return;

}

void lostSeq(int score){
  //Gives final look at score
  digitalWrite(hexRESET, HIGH);
  delay(100);
  digitalWrite(hexRESET, LOW);
  
  for(int i = 0; i < score; i++){
    updateScore();
  }

  //Loser trumpet
  myDFPlayer.play(6);
  delay(2000);
  //Plays Play again?
  myDFPlayer.play(5);
  delay(2000);

  return;

}
