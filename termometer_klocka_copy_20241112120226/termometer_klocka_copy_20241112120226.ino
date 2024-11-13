#include <U8glib.h>
#include <RTClib.h>
#include <Wire.h>
#include <Servo.h>
RTC_DS3231 rtc;
char t[32];
bool vilken = true;
bool timme = true;

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);
Servo myservo;
//libs and some variabels the libs ned

void setup() {
  Serial.begin(9600);
  Wire.begin();
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));
  myservo.attach(2);
  //starts some proceses
}

void loop() {
  int read = digitalRead(8);
  Serial.println(read);

  if (read == 1 && timme == true) {
    vilken = !vilken;
    timme = !timme;
  }
  if (read == 0 && timme == false) {
    timme = !timme;
  }
  //code for button pres that shifts betwen two code varients

  if (vilken==true){
    text(0,33 , time());
    myservo.write(vo());
  }
  //code varient to display time on monitor, temp on servo
  if (vilken==false){
    text(0,33 , String(temp()) + " celcius");
    DateTime now = rtc.now();
    int cord= map(now.second(),0, 60, 0,180);
    if (cord==180){
      cord=0;
    }
    myservo.write(cord);
    delay(1000);
  }
  //code varient to display temp on monitor, time on servo
}

int temp() {
  int Vo;
  float R1 = 10000; // value of R1 on board
  float logR2, R2, T;
  float c1 = 0.001129148, c2 = 0.000234125, c3 = 0.0000000876741;
  Vo = analogRead(A1);
  R2 = R1 * (1023.0 / (float)Vo - 1.0); //calculate resistance on thermistor
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2)); // temperature in Kelvin
  T = T - 273.15; //convert Kelvin to Celcius
  return T;
}
//function to get the temperatur in celcius

int vo(){
  return(map(temp(), 0, 25, 0,180));
}
//function to convert temperature to servo position

String time(){
  DateTime now = rtc.now();
  String tid= String("klockan ") + String(now.hour())  + ":"+ String(now.minute())  + ":"+ String(now.second());
  return(tid);
}
//function to get the curent time "klocka h:m:s"

void text(int x, int y, String ord) {
  u8g.firstPage();
  do {
     u8g.setFont(u8g_font_unifont);
     u8g.drawStr(x, y, ord.c_str());
     //what word sholud be displayed and where
     for(int i=0; i<128; i++){
      for(int j=0; j<17; j+=1){
        u8g.drawPixel(i, j);
      }
     }
     for(int i=0; i<128; i++){
      for(int j=40; j<64; j+=1){
        u8g.drawPixel(i, j);
      }
     }
     //boxes in the text displayed
  } while (u8g.nextPage());
}
//display loop
