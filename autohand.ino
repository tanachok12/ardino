

const int pir = 3;
const int Pump =  2;

int pirState = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Micro Project Thailand ~^.^~ ");
  pinMode(Pump, OUTPUT); //เพื่อให้ปั้มout put ต่อออกขา2 DG
  pinMode(pir, INPUT); //ประกาศpirเป็นตัวอ่าน sensor 
}

void loop() {
  pirState = digitalRead(pir);

  Serial.print("pirState : ");
  Serial.println(pirState);

  if (pirState == LOW) {  // ตัวทที่ใช้มันsensor สลับกันกับความจริง จริงๆต้องHIGH 
    digitalWrite(Pump, HIGH); 
  }

  else if (pirState == HIGH) {
    digitalWrite(Pump, LOW);
  //เพิ่มdelay ได้ ตามความต้องการเพื่อให้ปั้มทำงาน 
  //เเต่ที่ตัวsensor มีตัวปรับdaleyอยู่
  }

}
