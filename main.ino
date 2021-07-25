#include <Arduino.h>

#define greenLight 8
#define yellowLight 9
#define redLight 10

#define buttonInput 3
#define buttonOutput 7


int level;
bool button_value = 0;
int time;
int highScore = 1;

void startLevel(){
    level++;
    time -= 50;
    digitalWrite(buttonOutput, LOW);
    digitalWrite(yellowLight, LOW);

    for (int i = 0; i < 5; i++){
        digitalWrite(greenLight, HIGH);
        delay(200);
        digitalWrite(greenLight, LOW);
        delay(200);
    }

    listen();
}


void listen () {
    bool yellow_light_mode = false;

    randomSeed(millis());

    unsigned long long randomInterval = millis() + random(200, 4000);

    digitalWrite(buttonOutput, HIGH);

    while (true){
        if (millis() > randomInterval){
            break;
        }
        if (digitalRead(buttonInput) == 1){
            return reset();
        }
    }

    while (true){
        button_value = digitalRead(buttonInput);

        if ((button_value == 1 && yellow_light_mode == true)){
            return startLevel();
        }
        else if (button_value == 1 && yellow_light_mode == false){
            return reset();
        }
        if (millis() < randomInterval + time){
            digitalWrite(yellowLight, HIGH);
            yellow_light_mode = true;
        }
        else {
            digitalWrite(yellowLight, LOW);
            yellow_light_mode = false;
            return reset();
        }
    }
}

void reset(){
    Serial.print("Your Reaction time was approximedialy: ");
    Serial.print(time + 50);
    Serial.println("ms");

    if (highScore < level){
        highScore = level;
        Serial.println("Good job in beating your high score");
    }

    time = 600;
    level = 0;

    for (int i = 0; i < 10; i++){
        digitalWrite(redLight, HIGH);
        delay(200);
        digitalWrite(redLight, LOW);
        delay(200);
    }

    delay(1000);
    startLevel();
}



void setup(){
    Serial.begin(9600);

    pinMode(buttonInput, INPUT);
    pinMode(buttonOutput, OUTPUT);
    pinMode(greenLight, OUTPUT);
    pinMode(yellowLight, OUTPUT);
    pinMode(redLight, OUTPUT);

    time = 600;
    level = 0;

    startLevel();
}






void loop () {

}