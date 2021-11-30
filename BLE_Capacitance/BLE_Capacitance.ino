#include <bluefruit.h>
#include <avr/dtostrf.h>

int hum = 2;

const int OUT_PIN = A1;
const int IN_PIN = A0;

//Capacitance between IN_PIN and Ground
//Stray capacitance is always present. Extra capacitance can be added to
//allow higher capacitance to be measured.
const float IN_STRAY_CAP_TO_GND = 9.3; //provide here the stray capacitance, look in the repo README how to calculate it
const float IN_EXTRA_CAP_TO_GND = 0.0;
const float IN_CAP_TO_GND  = IN_STRAY_CAP_TO_GND + IN_EXTRA_CAP_TO_GND;
const int MAX_ADC_VALUE = 1023;

// OTA DFU service
BLEDfu bledfu;
 
// Uart over BLE service
BLEUart bleuart;

// Function prototypes for packetparser.cpp
uint8_t readPacket (BLEUart *ble_uart, uint16_t timeout);
float   parsefloat (uint8_t *buffer);
void    printHex   (const uint8_t * data, const uint32_t numBytes);

// Packet buffer
extern uint8_t packetbuffer[];

/* Set the delay between fresh samples */
uint16_t BNO055_SAMPLERATE_DELAY_MS = 100;


void setup() {
  pinMode(OUT_PIN, OUTPUT);
  //digitalWrite(OUT_PIN, LOW);  //This is the default state for outputs
  pinMode(IN_PIN, OUTPUT);
  //digitalWrite(IN_PIN, LOW);
  
  Serial.begin(115200);
  Bluefruit.begin();
  Bluefruit.setTxPower(4);    // Check bluefruit.h for supported values
  Bluefruit.setName("Bluefruit52");
 
  // To be consistent OTA DFU should be added first if it exists
  bledfu.begin();
 
  // Configure and start the BLE Uart service
  bleuart.begin();
 
  // Set up and start advertising
  startAdv();
 
//  Serial.println(F("Please use Adafruit Bluefruit LE app to connect in Controller mode"));
//  Serial.println(F("Then activate/use the sensors, color picker, game controller, etc!"));
//  Serial.println();  
//  Serial.print("Initializing SD card...");



}
 
void startAdv(void)
{
  // Advertising packet
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  
  // Include the BLE UART (AKA 'NUS') 128-bit UUID
  Bluefruit.Advertising.addService(bleuart);
 
  // Secondary Scan Response packet (optional)
  // Since there is no room for 'Name' in Advertising packet
  Bluefruit.ScanResponse.addName();
 
  /* Start Advertising
   * - Enable auto advertising if disconnected
   * - Interval:  fast mode = 20 ms, slow mode = 152.5 ms
   * - Timeout for fast mode is 30 seconds
   * - Start(timeout) with timeout = 0 will advertise forever (until connected)
   * 
   * For recommended advertising interval
   * https://developer.apple.com/library/content/qa/qa1931/_index.html   
   */
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
  Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds  
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
 
  float capacitance = (float)val * IN_CAP_TO_GND / (float)(MAX_ADC_VALUE - val);
  //float capacitance = 4.7 * (1023.0-val)/(val*1.0); // Para calibrar la cpacidad de entrada a Arduino usando un condensado de 4.7 pF
  //float capacitance = 2.1;
  
  delay(1000);
  yield();
  
  // int count1 = Serial.readBytes(hum, sizeof(hum));
  //hum = 2

  //char cap[10];
  //dtostrf(capacitance,0,2,cap);
  //bleuart.write(cap, sizeof(cap));
      bleuart.print(String(capacitance));
       //bleuart.print(capacitance);
       //bleuart.write(capacitance, sizeof(capacitance));
//     // int count2 = Serial.readBytes(temp, sizeof(temp));
//      bleuart.write(temp, sizeof(temp));


  delay(BNO055_SAMPLERATE_DELAY_MS);

}
