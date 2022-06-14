void setup(){ 
  pinMode(13,OUTPUT);
  Serial.begin(9600);
}
void loop(){ 
        char dato= Serial.read();//Guardamos en la variable dato el valor leido
        switch(dato){ //Comprobamos el dato
         case 'r':  //Si recibimos una 'r' ...
          for(int i=0; i<20; i++){
               digitalWrite(13,HIGH);
               delay(80);
               digitalWrite(13,LOW);
               delay(80);
          }
          break;
         case 'l':    //si recibimos una 'l' ...
         for(int i=0; i<10; i++){
               digitalWrite(13,HIGH);
               delay(1000);
               digitalWrite(13,LOW);
               delay(1000);
          }
          break;
          default:
           digitalWrite(13,LOW);
           break;
        }
}
