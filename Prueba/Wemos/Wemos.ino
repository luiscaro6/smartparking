int nivelluz = 0;

void setup(){ 
  Serial.begin(9600);
  pinMode(8, OUTPUT); 
}
void loop(){
  nivelluz = analogRead(A1);
  Serial.println(nivelluz);
  if (nivelluz > 700){
      digitalWrite(8, LOW);
    } else {
      digitalWrite(8, HIGH);   
    }  
}
