

void turnlight();
void hault();
void forward();
#define NUM_SENSORS 8

#define avgSpeed 255
int k1;
int m;
int k=0;
int sum = 0;
int posLeft = 10;
int posRight = 10;
int pwmA = 5;
int pwmB = 6;

int kp = 5;
float kd =0.01;
float ki =0.005;
int error = 0;
int lastError = 0;
int proportional = 0;
int derivative = 0;
int integral = 0;
int ir1 =4;
int ir2 =7;
int ir3 =8;
int ir4 =9;
int ir5 =10;
int ir6 =11;
int ir7 =12;
int ir8 =3;

unsigned int sensorValues[NUM_SENSORS];
void setup(){
Serial.begin(9600);
pinMode(ir1, INPUT);
pinMode(ir2, INPUT);
pinMode(ir3, INPUT);
pinMode(ir4, INPUT);
pinMode(ir5, INPUT);
pinMode(ir6, INPUT);
pinMode(ir7, INPUT);
pinMode(ir8, INPUT);
pinMode(pwmA, OUTPUT);
pinMode(pwmB, OUTPUT);
pinMode(13, OUTPUT);


analogWrite(pwmA, avgSpeed);
analogWrite(pwmB, avgSpeed);
}

void loop(){

m=digitalRead(ir7);
if(m==0){
  k=0;
}
else if(m==1){
  k=1;
}
 if(k!=k1){
  turnlight();
 }
else if(k==0){
sensorValues[0]=digitalRead(ir1);
sensorValues[1]=digitalRead(ir2);
sensorValues[2]=digitalRead(ir3);
sensorValues[3]=digitalRead(ir4);
sensorValues[4]=digitalRead(ir5);
sensorValues[5]=digitalRead(ir6);
sensorValues[6]=digitalRead(ir7);
sensorValues[7]=digitalRead(ir8);

  
}
  

else if(k==1){
  sensorValues[0]=digitalRead(ir1);
sensorValues[1]=digitalRead(ir2);
sensorValues[2]=digitalRead(ir3);
sensorValues[3]=digitalRead(ir4);
sensorValues[4]=digitalRead(ir5);
sensorValues[5]=digitalRead(ir6);
sensorValues[6]=digitalRead(ir7);
sensorValues[7]=digitalRead(ir8);
for (int i=0; i<NUM_SENSORS; i++){
sensorValues[i]=~sensorValues[i];
    }
  
}


if(sensorValues[0]==0 && sensorValues[3]==0 && sensorValues[4]==0 && sensorValues[7]==0 ){
 forward();
 delay(1000);
 
}
else if(sensorValues[0]==1 && sensorValues[3]==1 && sensorValues[4]==1 && sensorValues[7]==1 ){
 forward();
 delay(1000);
}

else if( sensorValues[0]==0 && sensorValues[6]==1 && sensorValues[3]==1 && sensorValues[4]==1 && sensorValues[1]==1 && sensorValues[7]==0 ){
 forward();
 delay(2500);
 hault();
 delay(4000);
}
sum = 0;
posLeft = 10;
posRight = 10;
for (int i=0; i<NUM_SENSORS/2; i++){
sum=sum+sensorValues[i];
if(sensorValues[i]==1){
posRight=i-3;
}
}
for (int i=NUM_SENSORS-1; i>=NUM_SENSORS/2; i--){
sum=sum+sensorValues[i];
if(sensorValues[i]==1){
posLeft=i-4;
}
}
if(sum>=3){
sum=2;
}
if(sum==0){
if(lastError<0){
error=-8;
}
else{
error=8;
}
}
else if((posLeft!=10)&&(posRight!=10)){
error=0;
}
else if(posLeft!=10){
error=posLeft*2+sum;
}
else if(posRight!=10){
error=posRight*2-sum;
}
proportional = error;
derivative = error-lastError;
integral += proportional;
if(integral > 255){
integral=255;
};
if(integral < -255){
integral=-255;
};
int turn = proportional*kp + derivative*kd + integral*ki;
if(turn>=255)
turn=255;
if(turn<=-255)
turn=-255;
int speedA=0;
int speedB=0;
if(turn>=0){
speedA=avgSpeed;
speedB=avgSpeed-turn;
}
else{
speedA=avgSpeed+turn;
speedB=avgSpeed;
}
//Serial.print("P=");
//Serial.print(proportional);
//Serial.print('\t');
//Serial.print("I=");
//Serial.print(integral);
//Serial.print('\t');
//Serial.print("D=");
//Serial.print(derivative);
//Serial.print('\t');
//Serial.print("Turn=");
//Serial.print(turn);
//Serial.print('\t');
//Serial.print("speedA=");
//Serial.print(speedA);
//Serial.print('\t');
//Serial.print("speedB=");
//Serial.print(speedB);
//Serial.print('\t');
analogWrite(pwmA, speedA);
analogWrite(pwmB, speedB);
lastError=error;
//Serial.println();

k1=k;
}



void hault(){
  analogWrite(pwmA, 0);
analogWrite(pwmB, 0);
}
void forward()
{
  analogWrite(pwmA, avgSpeed);
analogWrite(pwmB, avgSpeed);
}

void turnlight(){
   digitalWrite(13, HIGH);   
  delay(1000);              
  digitalWrite(13, LOW);    
  delay(1000);           
}

