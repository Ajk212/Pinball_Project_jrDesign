//Code for pinball machine goes here

//Just testing Git Addition

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool call_act1(int cd){
    //Code to action 1 goes here
    //Prompts user to press left button
    //Include timer
    //Include incorrect action check
    //returns true if either triggered
    //false if done correctly
}
bool call_act2(int cd){
    //Code to action 2 goes here
    //Prompts user to press right button
    
    /*NEEDS
    Timer
    action check
    returns
    */
}
bool call_act3(int cd){
    //Code to action 3 goes here
    //Prompts user to pull marble launcher
    
    /*NEEDS
    Timer
    action check
    returns
    */
}
bool call_act4(int cd){
    //Code to action 4 goes here
    //Prompts user to insert coin
    
    /*NEEDS
    Timer
    action check
    returns
    */
}
void updateScore(int score){
    //Code which updates scoreboard displays and LEDs goes here
    //If score reaches incriment of 10 (ie 10,20,30 etc) light additional LED around board
}

int main() {
    
    
    bool lost, gameStart = false;
    int score = 0;
    int actionNum, countdown; //Need to determine how countdown will operate
    
    while(true){
            
        
        //Pre-Play loop - Waits for user to start game
        while(gameStart == false){
            //Continues to check if start button pressed
            if(1){
                gameStart == true;
            }
            //Maybe include idle sequence, ie flash LEDs in a line?
        }
        
        //Play loop
        while(gameStart == true){
        
            actionNum = rand() % 4 + 1;
            printf("Rolled", actionNum);
            
            if(actionNum == 1){
                lost = call_act1(countdown);
            }
            else if(actionNum == 2){
                lost = call_act2(countdown);
            }
            else if(actionNum == 3){
                lost = call_act3(countdown);
            }
            else if(actionNum == 4){
                lost = call_act4(countdown);
            }
            
            if(lost == true){
                //loss sequence, displays final score and resets game
                gameStart == false;
            }
            
            //reduce countdown
            
            //incriment score
            score++;
            updateScore(score);
        }
    }
    
    
    //Should never reach here
    return 0;
}
