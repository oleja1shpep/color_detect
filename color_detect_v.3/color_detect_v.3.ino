#define S0 10
#define S1 9
#define S2 6
#define S3 7
#define sensorOut 8
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;
int lan = 1;

#include <LiquidCrystal.h>
LiquidCrystal lcd(11, 12, 5, 4, 3, 2);


// для хранения данных о красном, зеленом и синем цветах:
int redColor = 0;
int greenColor = 0;
int blueColor = 0;
#define BUTTON_PIN A1
boolean buttonWasUp = true;  // была ли кнопка отпущена?

void setup() {


  // выставляем контакты S0, S1, S2 и S3 в режим OUTPUT:
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  
  lcd.begin(16, 2);



  // выставляем контакт sensorOut в режим INPUT:
  pinMode(sensorOut, INPUT);

  // задаем масштабирование частоты на 20%:
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  // запускаем последовательную коммуникацию:
  Serial.begin(9600);
}

void loop() {


  // настраиваем датчик таким образом, чтобы считывать данные
  // с фотодиодов с красным фильтром:
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);

  // считываем выходную частоту:
  redFrequency = pulseIn(sensorOut, LOW);
  // подгоняем считанное значение к диапазону 0-255;
  // вместо «XX» нужно поставить собственные значения; например, так:
  // redColor = map(redFrequency, 70, 120, 255,0):
  redColor = map(redFrequency, 90, 500, 255, 0);

  // печатаем значение для красного цвета:
  Serial.print("R = ");
  Serial.print(redFrequency);
  delay(100);




  // настраиваем датчик таким образом, чтобы считывать данные
  // с фотодиодов с зеленым фильтром:
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);

  // считываем выходную частоту:
  greenFrequency = pulseIn(sensorOut, LOW);

  
  // подгоняем считанное значение к диапазону 0-255;

  greenColor = map(greenFrequency, 100, 730, 255, 0);

  Serial.print(" G = ");
  Serial.print(greenFrequency);
  delay(100);




  // настраиваем датчик таким образом, чтобы считывать данные
  // с фотодиодов с синим фильтром:
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);

  // считываем выходную частоту:
  blueFrequency = pulseIn(sensorOut, LOW);
  // подгоняем считанное значение к диапазону 0-255;
  blueColor = map(blueFrequency, 60, 500, 255, 0);

  Serial.print(" B = ");
  Serial.print(blueFrequency);
  delay(100);
  Serial.println();




  if (greenFrequency > 800 and blueFrequency > 500 and redFrequency > 700){
    if (lan == 0) { //делаем проверку на язык
      lcd.setCursor(4, 0);
      lcd.print("English");
      lcd.setCursor(5, 1);
      lcd.print("BLACK");
    }
 
    if (lan == 1) {
      lcd.setCursor(4, 0);
      lcd.print("\x50ycc\xBA\xB8\xB9"); //на русском
      lcd.setCursor(4, 1);
      lcd.print("\xAB\xB5p\xBD\xC3\xB9");
    }
    delay(1000);
    lcd.clear();
  }

  else if (greenFrequency < 160 and blueFrequency < 160 and redFrequency < 160){
    if (lan == 0) { //делаем проверку на язык
      lcd.setCursor(4, 0);
      lcd.print("English");
      lcd.setCursor(5, 1);
      lcd.print("WHITE");
    }
 
    if (lan == 1) {
      lcd.setCursor(4, 0);
      lcd.print("\x50ycc\xBA\xB8\xB9"); //на русском
      lcd.setCursor(5, 1);
      lcd.print("\xA0\x65\xBB\xC3\xB9");
    }
    delay(1000);
    lcd.clear();
    
  }

  else{

  

  // смотрим, какой цвет определился и печатаем
  // соответствующее сообщение в мониторе порта:
  if (redColor > greenColor && redColor > blueColor) {
    if (lan == 0) { //делаем проверку на язык
      lcd.setCursor(4, 0);
      lcd.print("English");
      lcd.setCursor(6, 1);
      lcd.print("RED");
    }
 
    if (lan == 1) {
      lcd.setCursor(4, 0);
      lcd.print("\x50ycc\xBA\xB8\xB9"); //на русском
      lcd.setCursor(4, 1);
      lcd.print("Kpac\xBD\xC3\xB9");
    }
    delay(1000);
    lcd.clear();
  }

  
  if (greenColor > redColor && greenColor > blueColor) {
    if (lan == 0) {
      lcd.setCursor(4, 0);
      lcd.print("English");
      lcd.setCursor(5, 1);
      lcd.print("GREEN");
    }
    if (lan == 1) {
      lcd.setCursor(4, 0);
      lcd.print("\x50ycc\xBA\xB8\xB9");
      lcd.setCursor(4, 1);
      lcd.print("3e\xBB\xB5\xBD\xC3\xB9");
    }
    delay(1000);
    lcd.clear();
  }

  
  if (blueColor > redColor && blueColor > greenColor) {
    if (lan == 0) {
      lcd.setCursor(4, 0);
      lcd.print("English");
      lcd.setCursor(5, 1);
      lcd.print("BLUE");
    }
    if (lan == 1) {
      lcd.setCursor(4, 0);
      lcd.print("\x50ycc\xBA\xB8\xB9");
      lcd.setCursor(5, 1);
      lcd.print("C\xB8\xBD\xB8\xB9");
    }
    delay(1000);
    lcd.clear();
  }


  
     boolean buttonIsUp = digitalRead(BUTTON_PIN);
   if (buttonWasUp && !buttonIsUp) {
    delay(5);
     buttonIsUp = digitalRead(BUTTON_PIN);
    if (!buttonIsUp) { 
      lan = !lan;
      }
   }
  }
}
