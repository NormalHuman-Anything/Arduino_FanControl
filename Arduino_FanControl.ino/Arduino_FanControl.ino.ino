const byte OC1A_PIN = 9;
const byte OC1B_PIN = 10;
const word PWM_FREQ_HZ = 25000; //Adjust this value to adjust the frequency
const word TCNT1_TOP = 16000000/(2*PWM_FREQ_HZ);
int potpin = A7;
int pot = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(OC1A_PIN, OUTPUT);

   // PWM settings
  // Clear Timer1 control and count registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  // Set Timer1 configuration
  // COM1A(1:0) = 0b10   (Output A clear rising/set falling)
  // COM1B(1:0) = 0b00   (Output B normal operation)
  // WGM(13:10) = 0b1010 (Phase correct PWM)
  // ICNC1      = 0b0    (Input capture noise canceler disabled)
  // ICES1      = 0b0    (Input capture edge select disabled)
  // CS(12:10)  = 0b001  (Input clock select = clock/1)
  
  TCCR1A |= (1 << COM1A1) | (1 << WGM11);
  TCCR1B |= (1 << WGM13) | (1 << CS10);
  ICR1 = TCNT1_TOP;

}

void loop() {
  // put your main code here, to run repeatedly:
  setPwmDuty();
}


void setPwmDuty() {
  pot = analogRead(A7);
  pot = map(pot, 0, 1023, 0, 100);
  OCR1A = (word) (pot*TCNT1_TOP)/100;
}
