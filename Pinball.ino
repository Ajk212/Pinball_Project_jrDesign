
int pushL = 8;
int pushR = 7;
int MP3 = 6;
int buttonL = 9;
int buttonR = 10;
int irCoin = 11;
int irLauncher = 12;
unsigned long startTime, timePassed;


void setup() {
  // put your setup code here, to run once:
  // Needed Pin outputs - 10x LED (?), 2x Hex display, 2x Push Solenoids, MP3 PLayer
  // Needed Pin inputs - 2x Flipper Buttons, 2x IR sensor, 

  pinMode(pushL, OUTPUT); //Solenoid #1
  pinMode(pushR, OUTPUT); //Solenoid #2
  pinMode(MP3, OUTPUT); //MP3 Player

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
    if(digitalRead(irLauncher) == HIGH){
      gameStart = true;
    }
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Maybe include idle sequence?
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
      gameStart = false;
    }

    score++;
    updateScore(score);

    if(countDown > 1000){
      countDown -= 250;
    }

  }


}


bool call_act1(int cd){
  
  //Tell user to press left button through MP3

  //sets countdown timer 
  startTime = millis();
  timePassed = 0;
  //if action is complete within time limit, return false
  //if incorrect action or timer runout, return true

  while(timePassed < cd) {

    timePassed = millis() - startTime;

    if(digitalRead(buttonL) ==HIGH){
      return false;
    }

    if(digitalRead(buttonR) == HIGH || digitalRead(irLauncher) == HIGH || digitalRead(irCoin) == HIGH){
      return true;
    }

  }
  //If not completed in alloted time, sets loss to true
  return true;
}

bool call_act2(int cd){
  
  //Tell user to press right button through MP3

  //sets countdown timer 
  startTime = millis();
  timePassed = 0;
  //if action is complete within time limit, return false
  //if incorrect action or timer runout, return true

  while(timePassed < cd) {

    timePassed = millis() - startTime;

    if(digitalRead(buttonR) == HIGH){
      return false;
    }

    if(digitalRead(buttonL) == HIGH || digitalRead(irLauncher) == HIGH || digitalRead(irCoin) == HIGH){
      return true;
    }

  }
  //If not completed in alloted time, sets loss to true
  return true;
}

bool call_act3(int cd){
  
  //Tell user to pull ball launcher through MP3

  //sets countdown timer 
  startTime = millis();
  timePassed = 0;
  //if action is complete within time limit, return false
  //if incorrect action or timer runout, return true

  while(timePassed < cd) {

    timePassed = millis() - startTime;

    if(digitalRead(irLauncher) == HIGH){
      return false;
    }

    if(digitalRead(buttonR) == HIGH || digitalRead(buttonL) == HIGH || digitalRead(irCoin) == HIGH){
      return true;
    }

  }
  //If not completed in alloted time, sets loss to true
  return true;
}

bool call_act4(int cd){
  
  //Tell user to insert coin through MP3
  //Figure code out and place here

  //sets countdown timer 
  startTime = millis();
  timePassed = 0;

  //if action is complete within time limit, return false
  //if incorrect action or timer runout, return true

  while(timePassed < cd) {

    timePassed = millis() - startTime;

    if(digitalRead(irCoin) == HIGH){
      return false;
    }

    if(digitalRead(buttonR) == HIGH || digitalRead(irLauncher) == HIGH || digitalRead(buttonL) == HIGH){
      return true;
    }

  }
  //If not completed in alloted time, sets loss to true
  return true;
}

void updateScore(int score){
  //Sends current score to hex displays and updates LED board
}
