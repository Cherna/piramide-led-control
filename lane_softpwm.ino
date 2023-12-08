// flariut

#include <SoftPWM.h>

#define ON true
#define OFF false

#define UP true
#define DOWN false

#define CA 2 // Caras
#define TR 4 // Triangulos
#define TI 4 // Triangulitos

#define NMODOSMODOS 41 // Número de modos modos
//#define NMODOS 3      // Número de modos

// Tiempos
#define SEG 1000
#define MIN 60000

// Luz
const int L100 = 255;
const int L75  = round(L100 * 0.75);
const int L66  = round(L100 * 0.66);
const int L50  = round(L100 * 0.50);
const int L33  = round(L100 * 0.33);
const int L25  = round(L100 * 0.25);
const int L10  = round(L100 * 0.10);
const int L5   = round(L100 * 0.05);

int luz100 = L100;
int luz75  = L75;
int luz66  = L66;
int luz50  = L50;
int luz33  = L33;
int luz25  = L25;
int luz10  = L10;
int luz5   = L5;

// tiempos y modos
unsigned long modo_modos_start = 0;
unsigned long modo_modos_time = 0;
unsigned long now = 0;
int current_modo_modos = 0;
int rand_modo_modos = 0;

int current_modo_secuencia[2] = {0, 0};

bool in_modo_modos = false;

typedef enum MODOS
{
  CARA_ON = 1,
  CARA_OFF,
  CARA_RANDOM,
  // CARA_SEQ_BASE,
  // CARA_SEQ_TRES,
  CARA_LATIDO,
  //CARA_LATIDO_MITADES,
  CARA_RANDOM_RAPIDO,
  CARA_RANDOM_SUPER_RAPIDO,
  CARA_STROBO1,
  CARA_STROBO2,
  CARA_STROBO3,
  CARA_3D1,
  CARA_3D2,
  CARA_3D3,
  CARA_3D4,
  CARA_PLENOS1,
  CARA_PLENOS2,
  CARA_SOLO0,
  CARA_SOLO1,
  CARA_SOLO2,
  CARA_SOLO3,
  CARA_IZQUIERDA,
  CARA_DERECHA
} MODOS;

typedef struct Triangulito
{
  // Pin
  int pin_softpwm;

  // Valores
  int target_value_hi;
  int target_value_mid;
  int target_value_lo;
  int current_value;

  // Switches
  bool direction; // UP = fade para arriba, DOWN = fade para abajo

  // Tiempos
  unsigned long fade_tick;
  unsigned long fade_time;
  unsigned long hold_tick;
  unsigned long hold_time;

  // unsigned long seq_time;
  // unsigned long seq_tick;

  // Modos
  MODOS nmodo; // numero de modo
  void (*modo)(Triangulito *); // puntero a funcion de modo que resuelve el triangulito

} Triangulito;

Triangulito piramide[CA][TR][TI];

void setup()
{
  //Serial.begin(9600);
  randomSeed(analogRead(0));
  SoftPWMBegin();
  set_pines_softpwm();

  init_piramide();
}

void loop()
{
  //Serial.println(now - modo_modos_start);
  now = millis();
  if (!in_modo_modos) // Seteo del modo de modos
  {
    while (current_modo_modos == rand_modo_modos)
    {
      //rand_modo_modos = (rand_modo_modos + 1) % (NMODOSMODOS + 1);//
      rand_modo_modos = (int)random(1, NMODOSMODOS + 1);
    }
    //Serial.println(rand_modo_modos);
    current_modo_modos = rand_modo_modos;
    modo_modos_time = round(random(20 * SEG, 40 * SEG));

    // Randoms
    if (current_modo_modos == 1)
      modo_modos_time = 1 * MIN;

    // Mitades/Verticales
    if (current_modo_modos == 7 || current_modo_modos == 8)
      modo_modos_time = 5 * SEG;

    // Strobos
    if (current_modo_modos == 4 || current_modo_modos == 5 || current_modo_modos == 6 || current_modo_modos == 36)
      modo_modos_time = 4 * SEG;

    if (current_modo_modos == 41)
      modo_modos_time = 6 * SEG;


    Serial.println("Acabo de setear modo_modos_time");
    Serial.println(modo_modos_time);
    //Serial.println("Tiempo del modo: " + modo_modos_time);
    set_modo_modos();
    in_modo_modos = true;
    modo_modos_start = now;
  }
  // Momento de setear un modo de modos
  else if (now - modo_modos_start > modo_modos_time)
  {
    Serial.println("Reseteando modo de modos");
    Serial.println(modo_modos_time);
    in_modo_modos = false;
  }
  // Resolver los modos
  else
  {
    // Serial.println("En modos exec");
    //Serial.println(modo_modos_time);
    modos_exec();
  }
}
