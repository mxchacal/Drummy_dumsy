
// rotary encoder demo by 'jurs' for Arduino Forum
struct rotary_t {byte pinA; byte pinB; int count;};

rotary_t encoder[]={ // define 2 pins for each rotary encoder
  {2,3},  // encoder[0].pinA, encoder[0].pinB
  {4,5},  // encoder[1].pinA, encoder[1].pinB
  {6,7},  // encoder[2].pinA, encoder[2].pinB
  {8,9},  // encoder[3].pinA, encoder[3].pinB
};
#define NUMENCODERS (sizeof(encoder)/sizeof(encoder[0]))

volatile byte state_ISR[NUMENCODERS];
volatile int8_t count_ISR[NUMENCODERS];


void beginEncoders()
{ // active internal pullup resistors on each encoder pin and start timer2
  for (int i=0; i<NUMENCODERS; i++)
  {
    pinMode(encoder[i].pinA, INPUT_PULLUP);
    pinMode(encoder[i].pinB, INPUT_PULLUP);
    readEncoder(i); // Initialize start condition
  }
  startTimer2();
}

boolean updateEncoders()
{ // read all the 'volatile' ISR variables and copy them into normal variables
  boolean changeState=false;
  for (int i=0; i<NUMENCODERS; i++)
  {
    if (count_ISR[i]!=0)
    {
      changeState=true;
      noInterrupts();
      encoder[i].count+= count_ISR[i];
      count_ISR[i]=0;
      interrupts();
    }
  }
  return changeState;
}

void printEncoders()
{ // print current count of each encoder to Serial
  for (int i=0; i<NUMENCODERS; i++)
  {
    Serial.print(encoder[i].count);
    Serial.print('\t');
  }
  Serial.println();
}

int8_t readEncoder(byte i)
{ // this function is called within timer interrupt to read one encoder!
  int8_t result=0;
  byte state=state_ISR[i];
  state= state<<2 | (byte)digitalRead(encoder[i].pinA)<<1 | (byte)digitalRead(encoder[i].pinB);
  state= state & 0xF;   // keep only the lower 4 bits
  /* // next two lines would be code to read 'quarter steps'
  if (state==0b0001 || state==0b0111 || state==0b1110 || state==0b1000) result= -1;
  else if (state==0b0010 || state==0b1011 || state==0b1101 || state==0b0100) result= 1;
  */
  // next two lines is code to read 'full steps'
  if (state==0b0001) result= -1;
  else if (state==0b0010) result= 1;
  state_ISR[i]= state;
  return result;
}


void startTimer2()  // start TIMER2 interrupts
{
  noInterrupts();
  // Timer 2 CTC mode
  TCCR2B = (1<<WGM22) | (1<<CS22)  | (1<<CS20);
  TCCR2A = (1<<WGM21);
  OCR2A = 124;   // 249==500,  124==1000 interrupts per second
                 // 63 ==2000,  31==4000
                 // 15 ==8000,   7==16000
  TIMSK2 = (1<<OCIE2A); // enable Timer 2 interrupts
  interrupts();
}

void stopTimer2() // stop TIMER2 interrupts
{
  noInterrupts();
  TIMSK2 = 0;
  interrupts();
}


ISR(TIMER2_COMPA_vect)  // handling of TIMER2 interrupts
{
  for (int i=0; i<NUMENCODERS; i++)
  {
    count_ISR[i]+= readEncoder(i);
  }
}


#define BAUDRATE 115200L // serial baud rate

void setup() {
  Serial.begin(BAUDRATE);
  Serial.println();
  Serial.println("Good night and good luck!"); // print some Test-Message at beginning
  beginEncoders();
}

void loop() {
  if (updateEncoders()) printEncoders();
}
