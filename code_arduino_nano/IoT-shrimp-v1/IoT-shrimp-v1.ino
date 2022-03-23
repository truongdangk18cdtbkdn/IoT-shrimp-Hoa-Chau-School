#define quatNuoc   2
#define bomNuoc    3
#define bomXiPhong 4
#define mayChoAn   5
#define bompH      6
#define van        7

char  dieuKhien[1]={};
bool sttQuatNuoc = 0;
bool sttBomNuoc = 0;
bool sttBomXiPhong = 0;
bool sttMayChoAn = 0;
bool sttBompH = 0;
bool sttVan = 0;
long doDuc = 0;
int   pH    = 0;
bool do1 = 0;
bool do2 = 0;
bool do3 = 0;
bool dopH = 0;
unsigned long batDauDo = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(13, LOW);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0)
    Serial.readBytes(dieuKhien, Serial.available());
  // Read
  if(dieuKhien[0] == '2') sttQuatNuoc = 1;
  else if(dieuKhien[0] == 'b') sttQuatNuoc = 0;
  else if(dieuKhien[0] == '3') sttBomNuoc = 1;
  else if(dieuKhien[0] == 'c') sttBomNuoc = 0;
  else if(dieuKhien[0] == '4') sttBomXiPhong = 1;
  else if(dieuKhien[0] == 'd') sttBomXiPhong = 0;
  else if(dieuKhien[0] == '5') sttMayChoAn = 1;
  else if(dieuKhien[0] == 'e') sttMayChoAn = 0;
  else if(dieuKhien[0] == '6') sttBompH = 1;
  else if(dieuKhien[0] == 'f') sttBompH = 0;
    // Control
    if(sttQuatNuoc) digitalWrite(quatNuoc, HIGH);
    else digitalWrite(quatNuoc, LOW);
    if(sttBomNuoc) digitalWrite(bomNuoc, HIGH);
    else digitalWrite(bomNuoc, LOW);
    if(sttBomXiPhong) digitalWrite(bomXiPhong, HIGH);
    else digitalWrite(bomXiPhong, LOW);
    if(sttMayChoAn) digitalWrite(mayChoAn, HIGH);
    else digitalWrite(mayChoAn, LOW);
    if(sttBompH == 1 || dopH == 1)
    {
      dopH = 1;
      if(batDauDo == 0) 
      {
        batDauDo = millis();       
        digitalWrite(13, HIGH);
        digitalWrite(bompH, HIGH);
      }
      else if(((millis()-batDauDo) >21000) && ((millis()-batDauDo) <27000)) // Sau22s, tắt bơm, bắt đầu đo
      {
        digitalWrite(bompH, LOW);
        doDuc = analogRead(A0);
        doDuc = doDuc * 1000 / 1023;
//        Serial.write(doDuc);
      }
      else if((millis()-batDauDo) >27000 && (millis()-batDauDo) <51000) // Sau 15s, bật van xả nước
      {
        digitalWrite(van, HIGH);
      }
      else if((millis()-batDauDo) >=51000)        // Sau 25s, tắt van xả nước
      {
        digitalWrite(van, LOW);
        batDauDo = 0;
        dopH = 0;
      }
    }
    else
    {     
      digitalWrite(13, LOW);
      digitalWrite(bompH, LOW);
      digitalWrite(van, LOW);
    } 
  
}
