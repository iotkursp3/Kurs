void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); //Podešava brzinu komunikacije sa terminalom
}

void loop() {
  // put your main code here, to run repeatedly:
  int broj = 39;
  float decimalni_broj = 1.56;
  String text = "Hello World!;
    
  //Serial.print(broj); //Ispisuje vrijednosti u istoj liniji
  //Serial.println(broj); //Ispisuje vrijednosti u novoj liniji
  
  Serial.println(broj);
  Serial.println(decimalni_broj);
  Serial.println(text);
}
