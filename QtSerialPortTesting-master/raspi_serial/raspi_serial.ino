const int pin =  9;
char a;
int b;
void setup() {
  Serial.begin(9600);
  pinMode(pin, OUTPUT);
  
  analogWrite(pin,255);
}

void loop() {
   
  if (Serial.available()){
    char a = Serial.read();
    int b = Serial.parseInt();
    writeLed(a,b);  
  }
  delay(1);        // delay in between reads for stability
  //Serial.println(a);
}

void writeLed(char a, int b){
  if (a=='r'){
    analogWrite(pin, 255-b);
    Serial.print(a);
    Serial.print(b);
    return;
  }
  return;
}



