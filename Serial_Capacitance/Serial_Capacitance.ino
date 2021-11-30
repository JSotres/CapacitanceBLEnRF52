const int OUT_PIN = A1;
const int IN_PIN = A0;

//Capacitance between IN_PIN and Ground
//Stray capacitance is always present. Extra capacitance can be added to
//allow higher capacitance to be measured.
const float IN_STRAY_CAP_TO_GND = 9.3; //provide here the stray capacitance, look in the repo README how to calculate it
const float IN_EXTRA_CAP_TO_GND = 0.0;
const float IN_CAP_TO_GND  = IN_STRAY_CAP_TO_GND + IN_EXTRA_CAP_TO_GND;
const int MAX_ADC_VALUE = 1023;

const int n_averages = 200;

float capacitance_sum;
float capacitance_average;
int counter;





void setup() {
  pinMode(OUT_PIN, OUTPUT);
  //digitalWrite(OUT_PIN, LOW);  //This is the default state for outputs
  pinMode(IN_PIN, OUTPUT);
  //digitalWrite(IN_PIN, LOW);

  counter = 1;
  
  Serial.begin(115200);
  
}
 
void loop() {

  //Capacitor under test between OUT_PIN and IN_PIN
  //Rising high edge on OUT_PIN
  pinMode(IN_PIN, INPUT);
  digitalWrite(OUT_PIN, HIGH);
  int val = analogRead(IN_PIN);
 
  //Clear everything for next measurement
  digitalWrite(OUT_PIN, LOW);
  pinMode(IN_PIN, OUTPUT);
 
  //Calculate and print result
 
  //float capacitance = (float)val * IN_CAP_TO_GND / (float)(MAX_ADC_VALUE - val);
  float capacitance = 4.7 * (1023.0-val)/(val*1.0); // Para calibrar la cpacidad de entrada a Arduino usando un condensado de 4.7 pF
  //float capacitance = 2.1;

  capacitance_sum = capacitance_sum + capacitance;

  //Serial.println(capacitance);

  if (counter<n_averages){
    
    counter = counter + 1;
  }
  else {
    capacitance_average = capacitance_sum/n_averages;
    capacitance_sum = 0;
    counter = 1;
    //Serial.println();
    Serial.println(capacitance_average);
    //Serial.println();
  }
  
  
  delay(500);
  //yield();
  

}
