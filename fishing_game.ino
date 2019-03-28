#include <Arduino.h>
#include <TM1637Display.h>
#include <Stepper.h>

#define START_BUTTON 2 //게임 시작 버튼
#define FISHING_BUTTON 3 //낚시줄 동작 버튼

#define WATER_PUMP 4 //수중 펌프 모터

#define STEPS 2048 //한바퀴 = 2048, 반바퀴 = 1024
#define STEPPER_IN4 11 //stepper motor IN4
#define STEPPER_IN3 10 //stepper motor IN3
#define STEPPER_IN2 9  //stepper motor IN2
#define STEPPER_IN1 8  //stepper motor IN1

#define RPM 2 //회전 되어야 될 횟수

boolean start_check = false; //게임 시작 상태 여부
boolean fishing_check = false; //낚시 움직임 상태 여부
int i = 0; //회전 횟수
boolean check_rotation = true; //낚시줄 시계방향, 반시계방향 체크
Stepper stepper(STEPS, STEPPER_IN4, STEPPER_IN2, STEPPER_IN3, STEPPER_IN1); //(IN4, IN2, IN3, IN1)

void setup() {
  pinMode(START_BUTTON, INPUT);
  pinMode(FISHING_BUTTON, INPUT);
  stepper.setSpeed(12); //스탭모터 스피드 설정

  Serial.begin(9600);
}

void loop() {
  // 게임 실행 버튼을 입력받았을 경우
  if(digitalRead(START_BUTTON) == LOW) {
    start_check = true;
    Serial.println("start on!!!!");
  }
  
  //낚시줄 동작은 무조건 게임 실행 버튼을 눌르고만 가능
  if (start_check) { 
    if(digitalRead(FISHING_BUTTON)== LOW){
      Serial.println("펌프 돌아가는중");

      if(digitalRead(FISHING_BUTTON) == HIGH && !fishing_check){
        Serial.println("fishing");
        fishing_check = true;
      
        stepperRotation();
      }
    }  
  }
}

void stepperRotation() {
  for(int i = 0; i < RPM; i++)
    stepper.step(-STEPS);

  for(int i = 0; i < RPM; i++)
    stepper.step(STEPS);

   fishing_check = false;
   start_check = false;
}
