#include <Joystick.h>

// Joystick Tanımlaması: 
// - 4 Eksen aktif: X (Direksiyon), Accelerator (Gaz), Brake (Fren), Y (Debriyaj), Z (El Freni) 
// - 10 Buton aktif (0'dan 9'a kadar)
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_JOYSTICK,
  10, 0,                 // 10 Buton, 0 Hi-hat
  true, true, true,      // X ekseni (Direksiyon), Y ekseni (Debriyaj), Z ekseni (El Freni) aktif
  false, false, false,   // Rotasyonlar kapalı
  false, false,          // Rudder, Throttle kapalı
  true, true, false);    // Gaz ve Fren aktif

// --- PİN TANIMLAMALARI ---
// Analog Pinler (Potansiyometreler)
const int steeringPin = A0;
const int gasPin = A1;
const int brakePin = A2;
const int clutchPin = A3;
const int handbrakePin = A4; // El freni potansiyometresi

// Dijital Pinler (Vitesler, Switch'ler ve Anahtar)
const int vites1Pin = 2;
const int vites2Pin = 3;
const int vites3Pin = 4;
const int vites4Pin = 5;
const int vites5Pin = 6;
const int vites6Pin = 7;
const int geriVitesPin = 8;
const int pedalSwitch1Pin = 9;
const int pedalSwitch2Pin = 10;
const int toggleAnahtarPin = 11;

// Direksiyon Kalibrasyon Değerleri (Kendi ölçtüğün min ve max değerleri buraya yazmalısın)
const int steeringMin = 150; 
const int steeringMax = 870; 

void setup() {
  // Tüm dijital buton, switch ve anahtar pinlerini dahili pull-up direnci ile başlatıyoruz
  pinMode(vites1Pin, INPUT_PULLUP);
  pinMode(vites2Pin, INPUT_PULLUP);
  pinMode(vites3Pin, INPUT_PULLUP);
  pinMode(vites4Pin, INPUT_PULLUP);
  pinMode(vites5Pin, INPUT_PULLUP);
  pinMode(vites6Pin, INPUT_PULLUP);
  pinMode(geriVitesPin, INPUT_PULLUP);
  pinMode(pedalSwitch1Pin, INPUT_PULLUP);
  pinMode(pedalSwitch2Pin, INPUT_PULLUP);
  pinMode(toggleAnahtarPin, INPUT_PULLUP);

  Joystick.begin();
}

void loop() {
  // --- 1. DİREKSİYON VE PEDALLAR / EL FRENİ (Eksenler) ---
  
  // Direksiyon (900 Derece Çark)
  int rawSteering = analogRead(steeringPin);
  rawSteering = constrain(rawSteering, steeringMin, steeringMax);
  int steeringVal = map(rawSteering, steeringMin, steeringMax, 0, 1023);
  Joystick.setXAxis(steeringVal);

  // Gaz Pedalı
  int gasVal = analogRead(gasPin);
  Joystick.setAccelerator(map(gasVal, 0, 1023, 0, 1023));

  // Fren Pedalı
  int brakeVal = analogRead(brakePin);
  Joystick.setBrake(map(brakeVal, 0, 1023, 0, 1023));

  // Debriyaj Pedalı
  int clutchVal = analogRead(clutchPin);
  Joystick.setYAxis(map(clutchVal, 0, 1023, 0, 1023));

  // El Freni (A4 Potansiyometresi)
  int handbrakeVal = analogRead(handbrakePin);
  Joystick.setZAxis(map(handbrakeVal, 0, 1023, 0, 1023));

  // --- 2. TÜM BUTONLAR, SWITCH'LER VE ANAHTAR ---
  // INPUT_PULLUP kullanıldığı için basıldığında LOW (0), bırakıldığında HIGH (1) olur.
  // Baştaki '!' işareti ile durumu ters çeviriyoruz.

  Joystick.setButton(0, !digitalRead(vites1Pin));        // Buton 0: 1. Vites
  Joystick.setButton(1, !digitalRead(vites2Pin));        // Buton 1: 2. Vites
  Joystick.setButton(2, !digitalRead(vites3Pin));        // Buton 2: 3. Vites
  Joystick.setButton(3, !digitalRead(vites4Pin));        // Buton 3: 4. Vites
  Joystick.setButton(4, !digitalRead(vites5Pin));        // Buton 4: 5. Vites
  Joystick.setButton(5, !digitalRead(vites6Pin));        // Buton 5: 6. Vites
  Joystick.setButton(6, !digitalRead(geriVitesPin));     // Buton 6: Geri Vites
  Joystick.setButton(7, !digitalRead(pedalSwitch1Pin));  // Buton 7: Pedal Switch 1
  Joystick.setButton(8, !digitalRead(pedalSwitch2Pin));  // Buton 8: Pedal Switch 2
  Joystick.setButton(9, !digitalRead(toggleAnahtarPin)); // Buton 9: Ekstra Anahtar

  delay(5); // Kararlı çalışma için kısa gecikme
}