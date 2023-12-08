// Setear las variables necesarias para que la cara pueda ejecutar su modo
// Esta es la papa. Después la función para manejar cada modo simplemente
// tendría que ejecutar acciones básicas y genéricas para resolver los fades
void set_modo_cara(int cara, MODOS nmodo)
{
  unsigned long fade_time;
  unsigned long hold_time;
  unsigned long seq_time;
  unsigned long hold_sync_tick = 0; // Este es para syncear los triangulitos por la mierda de softpwm
  int target_value_hi;
  int target_value_mid;
  int target_value_lo;
  int seq_order;
  void (*modo)(Triangulito *);

  Serial.println("Entrando a set modo_cara");
  Serial.println(modo_modos_time);
  switch (nmodo)
  {
  case CARA_ON:
    modo = modo_pleno;
    Serial.println("Seteando valores para CARA_ON");
    Serial.println(modo_modos_time);
    target_value_hi = luz100;
    target_value_lo = 0;
    fade_time = 2 * SEG;
    hold_time = 1 * SEG;
    for (int tr = 0; tr < TR; tr++)
    {
      for (int ti = 0; ti < TI; ti++)
      {
        piramide[cara][tr][ti].direction = UP;
      }
    }
    break;
  case CARA_OFF:
    modo = modo_pleno;
    Serial.println("Seteando valores para CARA_OFF");
    Serial.println(modo_modos_time);
    target_value_hi = 0;
    target_value_lo = 0;
    fade_time = 4 * SEG;
    hold_time = 1 * SEG;
    for (int tr = 0; tr < TR; tr++)
    {
      for (int ti = 0; ti < TI; ti++)
      {
        piramide[cara][tr][ti].direction = DOWN;
      }
    }
    break;
  case CARA_RANDOM:
    modo = modo_latido;
    Serial.println("Seteando valores para CARA_RANDOM");
    for (int tr = 0; tr < TR; tr++)
    {
      for (int ti = 0; ti < TI; ti++)
      {
        piramide[cara][tr][ti].target_value_hi = luz100;
        piramide[cara][tr][ti].target_value_lo = 0;
        piramide[cara][tr][ti].modo = modo;
        piramide[cara][tr][ti].nmodo = nmodo;
        piramide[cara][tr][ti].fade_time = round(random(1 * SEG, 4 * SEG));
        piramide[cara][tr][ti].hold_time = round(random(5 * SEG, 8 * SEG));
        Serial.println(piramide[cara][tr][ti].pin_softpwm);
        Serial.println(piramide[cara][tr][ti].fade_time);
        SoftPWMSetFadeTime(piramide[cara][tr][ti].pin_softpwm,
                           piramide[cara][tr][ti].fade_time,
                           piramide[cara][tr][ti].fade_time);
      }
    }
    return;
    break;
  
  case CARA_RANDOM_RAPIDO:
    modo = modo_latido;
    Serial.println("Seteando valores para CARA_RANDOM");
    for (int tr = 0; tr < TR; tr++)
    {
      for (int ti = 0; ti < TI; ti++)
      {
        piramide[cara][tr][ti].target_value_hi = luz100;
        piramide[cara][tr][ti].target_value_lo = 0;
        piramide[cara][tr][ti].modo = modo;
        piramide[cara][tr][ti].nmodo = nmodo;
        piramide[cara][tr][ti].fade_time = round(random(0.1 * SEG, 1 * SEG));
        piramide[cara][tr][ti].hold_time = round(random(0.1 * SEG, 1 * SEG));
        Serial.println(piramide[cara][tr][ti].pin_softpwm);
        Serial.println(piramide[cara][tr][ti].fade_time);
        SoftPWMSetFadeTime(piramide[cara][tr][ti].pin_softpwm,
                           piramide[cara][tr][ti].fade_time,
                           piramide[cara][tr][ti].fade_time);
      }
    }
    return;
    break;

  case CARA_RANDOM_SUPER_RAPIDO:
    modo = modo_latido;
    Serial.println("Seteando valores para CARA_RANDOM");
    for (int tr = 0; tr < TR; tr++)
    {
      for (int ti = 0; ti < TI; ti++)
      {
        piramide[cara][tr][ti].target_value_hi = luz100;
        piramide[cara][tr][ti].target_value_lo = 0;
        piramide[cara][tr][ti].modo = modo;
        piramide[cara][tr][ti].nmodo = nmodo;
        piramide[cara][tr][ti].fade_time = 0;//round(random(0.1 * SEG, 1 * SEG));
        piramide[cara][tr][ti].hold_time = round(random(0.05 * SEG, 0.1 * SEG));
        SoftPWMSetFadeTime(piramide[cara][tr][ti].pin_softpwm,
                           piramide[cara][tr][ti].fade_time,
                           piramide[cara][tr][ti].fade_time);
      }
    }
    return;
    break;
  
  case CARA_LATIDO:
    modo = modo_latido;
    Serial.println("Seteando valores para CARA_LATIDO");
    Serial.println(modo_modos_time);
    target_value_hi = luz100;
    target_value_lo = 0;
    fade_time = 1 * SEG;
    hold_time = 0.1 * SEG;
    for (int tr = 0; tr < TR; tr++)
    {
      for (int ti = 0; ti < TI; ti++)
      {
        piramide[cara][tr][ti].direction = UP;
        SoftPWMSetFadeTime(piramide[cara][tr][ti].pin_softpwm, 0, 0);
        SoftPWMSet(piramide[cara][tr][ti].pin_softpwm, 0);
      }
    }
    break;

  case CARA_STROBO1:
    modo = modo_latido;
    Serial.println("Seteando valores para CARA_LATIDO");
    Serial.println(modo_modos_time);
    target_value_hi = luz100;
    target_value_lo = 0;
    fade_time = 0;
    hold_time = 150;
    for (int tr = 0; tr < TR; tr++)
    {
      for (int ti = 0; ti < TI; ti++)
      {
        piramide[cara][tr][ti].direction = UP;
        SoftPWMSetFadeTime(piramide[cara][tr][ti].pin_softpwm, 0, 0);
        SoftPWMSet(piramide[cara][tr][ti].pin_softpwm, 0);
      }
    }
    break;
  
  case CARA_STROBO2:
    modo = modo_latido;
    target_value_hi = luz100;
    target_value_lo = 0;
    fade_time = 0;
    hold_time = 90;
    for (int tr = 0; tr < TR; tr++)
    {
      for (int ti = 0; ti < TI; ti++)
      {
        piramide[cara][tr][ti].direction = UP;
        SoftPWMSetFadeTime(piramide[cara][tr][ti].pin_softpwm, 0, 0);
        SoftPWMSet(piramide[cara][tr][ti].pin_softpwm, 0);
      }
    }
    break;
  
  case CARA_STROBO3:
    modo = modo_latido;
    target_value_hi = luz100;
    target_value_lo = 0;
    fade_time = 0;
    hold_time = 50;
    for (int tr = 0; tr < TR; tr++)
    {
      for (int ti = 0; ti < TI; ti++)
      {
        piramide[cara][tr][ti].direction = UP;
        SoftPWMSetFadeTime(piramide[cara][tr][ti].pin_softpwm, 0, 0);
        SoftPWMSet(piramide[cara][tr][ti].pin_softpwm, 0);
      }
    }
    break;
  
  case CARA_3D1:
    modo = modo_pleno;
    target_value_lo = 0;
    fade_time = 4 * SEG;
    hold_time = 1 * SEG;

    piramide[cara][0][0].target_value_hi = luz5;
    piramide[cara][0][1].target_value_hi = luz50;
    piramide[cara][0][2].target_value_hi = 0;
    piramide[cara][0][3].target_value_hi = 0;

    piramide[cara][1][0].target_value_hi = luz5;
    piramide[cara][1][1].target_value_hi = luz50;
    piramide[cara][1][2].target_value_hi = luz33;
    piramide[cara][1][3].target_value_hi = luz33;

    piramide[cara][2][0].target_value_hi = luz100;
    piramide[cara][2][1].target_value_hi = luz5;
    piramide[cara][2][2].target_value_hi = 0;
    piramide[cara][2][3].target_value_hi = 0;

    piramide[cara][3][0].target_value_hi = luz5;
    piramide[cara][3][1].target_value_hi = luz50;
    piramide[cara][3][2].target_value_hi = luz33;
    piramide[cara][3][3].target_value_hi = luz33;

    for (int tr = 0; tr < TR; tr++)
    {
      for (int ti = 0; ti < TI; ti++)
      {
        piramide[cara][tr][ti].fade_time = fade_time;
        piramide[cara][tr][ti].hold_time = hold_time;
        piramide[cara][tr][ti].target_value_lo = 0;
        piramide[cara][tr][ti].modo = modo;
        piramide[cara][tr][ti].nmodo = nmodo;
        SoftPWMSetFadeTime(piramide[cara][tr][ti].pin_softpwm, fade_time, fade_time);
      }
    }
    return;
    break;
  case CARA_3D2:
    modo = modo_pleno;
    target_value_lo = 0;
    fade_time = 4 * SEG;
    hold_time = 1 * SEG;

    piramide[cara][0][0].target_value_hi = luz5;
    piramide[cara][0][1].target_value_hi = 0;
    piramide[cara][0][2].target_value_hi = luz50;
    piramide[cara][0][3].target_value_hi = luz50;

    piramide[cara][1][0].target_value_hi = luz100;
    piramide[cara][1][1].target_value_hi = 0;
    piramide[cara][1][2].target_value_hi = luz5;
    piramide[cara][1][3].target_value_hi = luz5;

    piramide[cara][2][0].target_value_hi = luz5;
    piramide[cara][2][1].target_value_hi = luz100;
    piramide[cara][2][2].target_value_hi = 0;
    piramide[cara][2][3].target_value_hi = 0;

    piramide[cara][3][0].target_value_hi = luz100;
    piramide[cara][3][1].target_value_hi = 0;
    piramide[cara][3][2].target_value_hi = luz5;
    piramide[cara][3][3].target_value_hi = luz5;

    for (int tr = 0; tr < TR; tr++)
    {
      for (int ti = 0; ti < TI; ti++)
      {
        piramide[cara][tr][ti].fade_time = fade_time;
        piramide[cara][tr][ti].hold_time = hold_time;
        piramide[cara][tr][ti].target_value_lo = 0;
        piramide[cara][tr][ti].modo = modo;
        piramide[cara][tr][ti].nmodo = nmodo;
        SoftPWMSetFadeTime(piramide[cara][tr][ti].pin_softpwm, fade_time, fade_time);
      }
    }
    return;
    break;

  case CARA_3D3:
    modo = modo_pleno;
    target_value_lo = 0;
    fade_time = 4 * SEG;
    hold_time = 1 * SEG;

    piramide[cara][0][0].target_value_hi = luz50;
    piramide[cara][0][1].target_value_hi = luz5;
    piramide[cara][0][2].target_value_hi = luz33;
    piramide[cara][0][3].target_value_hi = luz25;

    piramide[cara][1][0].target_value_hi = luz50;
    piramide[cara][1][1].target_value_hi = luz5;
    piramide[cara][1][2].target_value_hi = luz50;
    piramide[cara][1][3].target_value_hi = luz33;

    piramide[cara][2][0].target_value_hi = luz5;
    piramide[cara][2][1].target_value_hi = luz33;
    piramide[cara][2][2].target_value_hi = luz33;
    piramide[cara][2][3].target_value_hi = luz50;

    piramide[cara][3][0].target_value_hi = luz100;
    piramide[cara][3][1].target_value_hi = luz5;
    piramide[cara][3][2].target_value_hi = luz50;
    piramide[cara][3][3].target_value_hi = luz33;

    for (int tr = 0; tr < TR; tr++)
    {
      for (int ti = 0; ti < TI; ti++)
      {
        piramide[cara][tr][ti].fade_time = fade_time;
        piramide[cara][tr][ti].hold_time = hold_time;
        piramide[cara][tr][ti].target_value_lo = 0;
        piramide[cara][tr][ti].modo = modo;
        piramide[cara][tr][ti].nmodo = nmodo;
        SoftPWMSetFadeTime(piramide[cara][tr][ti].pin_softpwm, fade_time, fade_time);
      }
    }
    return;
    break;

  case CARA_3D4:
    modo = modo_pleno;
    target_value_lo = 0;
    fade_time = 4 * SEG;
    hold_time = 1 * SEG;

    piramide[cara][0][0].target_value_hi = luz50;
    piramide[cara][0][1].target_value_hi = 0;
    piramide[cara][0][2].target_value_hi = luz5;
    piramide[cara][0][3].target_value_hi = luz5;

    piramide[cara][1][0].target_value_hi = luz50;
    piramide[cara][1][1].target_value_hi = luz100;
    piramide[cara][1][2].target_value_hi = luz50;
    piramide[cara][1][3].target_value_hi = luz50;

    piramide[cara][2][0].target_value_hi = luz33;
    piramide[cara][2][1].target_value_hi = luz100;
    piramide[cara][2][2].target_value_hi = luz5;
    piramide[cara][2][3].target_value_hi = luz5;

    piramide[cara][3][0].target_value_hi = luz33;
    piramide[cara][3][1].target_value_hi = 0;
    piramide[cara][3][2].target_value_hi = 0;
    piramide[cara][3][3].target_value_hi = 0;

    for (int tr = 0; tr < TR; tr++)
    {
      for (int ti = 0; ti < TI; ti++)
      {
        piramide[cara][tr][ti].fade_time = fade_time;
        piramide[cara][tr][ti].hold_time = hold_time;
        piramide[cara][tr][ti].target_value_lo = 0;
        piramide[cara][tr][ti].modo = modo;
        piramide[cara][tr][ti].nmodo = nmodo;
        SoftPWMSetFadeTime(piramide[cara][tr][ti].pin_softpwm, fade_time, fade_time);
      }
    }
    return;
    break;


  case CARA_PLENOS1:
    modo = modo_pleno;
    target_value_lo = 0;
    fade_time = 4 * SEG;
    hold_time = 1 * SEG;

    piramide[cara][0][0].target_value_hi = 0;
    piramide[cara][0][1].target_value_hi = 0;
    piramide[cara][0][2].target_value_hi = 0;
    piramide[cara][0][3].target_value_hi = 0;

    piramide[cara][1][0].target_value_hi = luz5;
    piramide[cara][1][1].target_value_hi = luz5;
    piramide[cara][1][2].target_value_hi = luz5;
    piramide[cara][1][3].target_value_hi = luz5;

    piramide[cara][2][0].target_value_hi = luz100;
    piramide[cara][2][1].target_value_hi = luz100;
    piramide[cara][2][2].target_value_hi = luz100;
    piramide[cara][2][3].target_value_hi = luz100;

    piramide[cara][3][0].target_value_hi = luz33;
    piramide[cara][3][1].target_value_hi = luz33;
    piramide[cara][3][2].target_value_hi = luz33;
    piramide[cara][3][3].target_value_hi = luz33;

    for (int tr = 0; tr < TR; tr++)
    {
      for (int ti = 0; ti < TI; ti++)
      {
        piramide[cara][tr][ti].fade_time = fade_time;
        piramide[cara][tr][ti].hold_time = hold_time;
        piramide[cara][tr][ti].target_value_lo = 0;
        piramide[cara][tr][ti].modo = modo;
        piramide[cara][tr][ti].nmodo = nmodo;
        SoftPWMSetFadeTime(piramide[cara][tr][ti].pin_softpwm, fade_time, fade_time);
      }
    }
    return;
    break;

  case CARA_PLENOS2:
    modo = modo_pleno;
    target_value_lo = 0;
    fade_time = 4 * SEG;
    hold_time = 1 * SEG;

    piramide[cara][0][0].target_value_hi = luz66;
    piramide[cara][0][1].target_value_hi = luz66;
    piramide[cara][0][2].target_value_hi = luz66;
    piramide[cara][0][3].target_value_hi = luz66;

    piramide[cara][1][0].target_value_hi = 0;
    piramide[cara][1][1].target_value_hi = 0;
    piramide[cara][1][2].target_value_hi = 0;
    piramide[cara][1][3].target_value_hi = 0;

    piramide[cara][2][0].target_value_hi = luz33;
    piramide[cara][2][1].target_value_hi = luz33;
    piramide[cara][2][2].target_value_hi = luz33;
    piramide[cara][2][3].target_value_hi = luz33;

    piramide[cara][3][0].target_value_hi = luz5;
    piramide[cara][3][1].target_value_hi = luz5;
    piramide[cara][3][2].target_value_hi = luz5;
    piramide[cara][3][3].target_value_hi = luz5;

    for (int tr = 0; tr < TR; tr++)
    {
      for (int ti = 0; ti < TI; ti++)
      {
        piramide[cara][tr][ti].fade_time = fade_time;
        piramide[cara][tr][ti].hold_time = hold_time;
        piramide[cara][tr][ti].target_value_lo = 0;
        piramide[cara][tr][ti].modo = modo;
        piramide[cara][tr][ti].nmodo = nmodo;
        SoftPWMSetFadeTime(piramide[cara][tr][ti].pin_softpwm, fade_time, fade_time);
      }
    }
    return;
    break;

  case CARA_SOLO0:
    modo = modo_pleno;
    target_value_lo = 0;
    fade_time = 0.5 * SEG;
    hold_time = 1 * SEG;

    piramide[cara][0][0].target_value_hi = luz100;
    piramide[cara][0][1].target_value_hi = luz100;
    piramide[cara][0][2].target_value_hi = luz100;
    piramide[cara][0][3].target_value_hi = luz100;

    piramide[cara][1][0].target_value_hi = 0;
    piramide[cara][1][1].target_value_hi = 0;
    piramide[cara][1][2].target_value_hi = 0;
    piramide[cara][1][3].target_value_hi = 0;

    piramide[cara][2][0].target_value_hi = 0;
    piramide[cara][2][1].target_value_hi = 0;
    piramide[cara][2][2].target_value_hi = 0;
    piramide[cara][2][3].target_value_hi = 0;

    piramide[cara][3][0].target_value_hi = 0;
    piramide[cara][3][1].target_value_hi = 0;
    piramide[cara][3][2].target_value_hi = 0;
    piramide[cara][3][3].target_value_hi = 0;

    for (int tr = 0; tr < TR; tr++)
    {
      for (int ti = 0; ti < TI; ti++)
      {
        piramide[cara][tr][ti].fade_time = fade_time;
        piramide[cara][tr][ti].hold_time = hold_time;
        piramide[cara][tr][ti].target_value_lo = 0;
        piramide[cara][tr][ti].modo = modo;
        piramide[cara][tr][ti].nmodo = nmodo;
        SoftPWMSetFadeTime(piramide[cara][tr][ti].pin_softpwm, fade_time, fade_time);
      }
    }
    return;
    break;

  case CARA_SOLO1:
    modo = modo_pleno;
    target_value_lo = 0;
    fade_time = 0.5 * SEG;
    hold_time = 1 * SEG;

    piramide[cara][0][0].target_value_hi = 0;
    piramide[cara][0][1].target_value_hi = 0;
    piramide[cara][0][2].target_value_hi = 0;
    piramide[cara][0][3].target_value_hi = 0;

    piramide[cara][1][0].target_value_hi = luz100;
    piramide[cara][1][1].target_value_hi = luz100;
    piramide[cara][1][2].target_value_hi = luz100;
    piramide[cara][1][3].target_value_hi = luz100;

    piramide[cara][2][0].target_value_hi = 0;
    piramide[cara][2][1].target_value_hi = 0;
    piramide[cara][2][2].target_value_hi = 0;
    piramide[cara][2][3].target_value_hi = 0;

    piramide[cara][3][0].target_value_hi = 0;
    piramide[cara][3][1].target_value_hi = 0;
    piramide[cara][3][2].target_value_hi = 0;
    piramide[cara][3][3].target_value_hi = 0;

    for (int tr = 0; tr < TR; tr++)
    {
      for (int ti = 0; ti < TI; ti++)
      {
        piramide[cara][tr][ti].fade_time = fade_time;
        piramide[cara][tr][ti].hold_time = hold_time;
        piramide[cara][tr][ti].target_value_lo = 0;
        piramide[cara][tr][ti].modo = modo;
        piramide[cara][tr][ti].nmodo = nmodo;
        SoftPWMSetFadeTime(piramide[cara][tr][ti].pin_softpwm, fade_time, fade_time);
      }
    }
    return;
    break;

  case CARA_SOLO2:
    modo = modo_pleno;
    target_value_lo = 0;
    fade_time = 0.5 * SEG;
    hold_time = 1 * SEG;

    piramide[cara][0][0].target_value_hi = 0;
    piramide[cara][0][1].target_value_hi = 0;
    piramide[cara][0][2].target_value_hi = 0;
    piramide[cara][0][3].target_value_hi = 0;

    piramide[cara][1][0].target_value_hi = 0;
    piramide[cara][1][1].target_value_hi = 0;
    piramide[cara][1][2].target_value_hi = 0;
    piramide[cara][1][3].target_value_hi = 0;

    piramide[cara][2][0].target_value_hi = luz100;
    piramide[cara][2][1].target_value_hi = luz100;
    piramide[cara][2][2].target_value_hi = luz100;
    piramide[cara][2][3].target_value_hi = luz100;

    piramide[cara][3][0].target_value_hi = 0;
    piramide[cara][3][1].target_value_hi = 0;
    piramide[cara][3][2].target_value_hi = 0;
    piramide[cara][3][3].target_value_hi = 0;

    for (int tr = 0; tr < TR; tr++)
    {
      for (int ti = 0; ti < TI; ti++)
      {
        piramide[cara][tr][ti].fade_time = fade_time;
        piramide[cara][tr][ti].hold_time = hold_time;
        piramide[cara][tr][ti].target_value_lo = 0;
        piramide[cara][tr][ti].modo = modo;
        piramide[cara][tr][ti].nmodo = nmodo;
        SoftPWMSetFadeTime(piramide[cara][tr][ti].pin_softpwm, fade_time, fade_time);
      }
    }
    return;
    break;
  
  case CARA_SOLO3:
    modo = modo_pleno;
    target_value_lo = 0;
    fade_time = 0.5 * SEG;
    hold_time = 1 * SEG;

    piramide[cara][0][0].target_value_hi = 0;
    piramide[cara][0][1].target_value_hi = 0;
    piramide[cara][0][2].target_value_hi = 0;
    piramide[cara][0][3].target_value_hi = 0;

    piramide[cara][1][0].target_value_hi = 0;
    piramide[cara][1][1].target_value_hi = 0;
    piramide[cara][1][2].target_value_hi = 0;
    piramide[cara][1][3].target_value_hi = 0;

    piramide[cara][2][0].target_value_hi = 0;
    piramide[cara][2][1].target_value_hi = 0;
    piramide[cara][2][2].target_value_hi = 0;
    piramide[cara][2][3].target_value_hi = 0;

    piramide[cara][3][0].target_value_hi = luz100;
    piramide[cara][3][1].target_value_hi = luz100;
    piramide[cara][3][2].target_value_hi = luz100;
    piramide[cara][3][3].target_value_hi = luz100;

    for (int tr = 0; tr < TR; tr++)
    {
      for (int ti = 0; ti < TI; ti++)
      {
        piramide[cara][tr][ti].fade_time = fade_time;
        piramide[cara][tr][ti].hold_time = hold_time;
        piramide[cara][tr][ti].target_value_lo = 0;
        piramide[cara][tr][ti].modo = modo;
        piramide[cara][tr][ti].nmodo = nmodo;
        SoftPWMSetFadeTime(piramide[cara][tr][ti].pin_softpwm, fade_time, fade_time);
      }
    }
    return;
    break;

  case CARA_IZQUIERDA:
    modo = modo_pleno;
    target_value_lo = 0;
    fade_time = 4 * SEG;
    hold_time = 1 * SEG;

    piramide[cara][0][0].target_value_hi = luz100;
    piramide[cara][0][1].target_value_hi = 0;
    piramide[cara][0][2].target_value_hi = luz100;
    piramide[cara][0][3].target_value_hi = 0;

    piramide[cara][1][0].target_value_hi = luz100;
    piramide[cara][1][1].target_value_hi = luz100;
    piramide[cara][1][2].target_value_hi = luz100;
    piramide[cara][1][3].target_value_hi = luz100;

    piramide[cara][2][0].target_value_hi = 0;
    piramide[cara][2][1].target_value_hi = luz100;
    piramide[cara][2][2].target_value_hi = 0;
    piramide[cara][2][3].target_value_hi = luz100;

    piramide[cara][3][0].target_value_hi = 0;
    piramide[cara][3][1].target_value_hi = 0;
    piramide[cara][3][2].target_value_hi = 0;
    piramide[cara][3][3].target_value_hi = 0;

    for (int tr = 0; tr < TR; tr++)
    {
      for (int ti = 0; ti < TI; ti++)
      {
        piramide[cara][tr][ti].fade_time = fade_time;
        piramide[cara][tr][ti].hold_time = hold_time;
        piramide[cara][tr][ti].target_value_lo = 0;
        piramide[cara][tr][ti].modo = modo;
        piramide[cara][tr][ti].nmodo = nmodo;
        SoftPWMSetFadeTime(piramide[cara][tr][ti].pin_softpwm, fade_time, fade_time);
      }
    }
    return;
    break;

  case CARA_DERECHA:
    modo = modo_pleno;
    target_value_lo = 0;
    fade_time = 4 * SEG;
    hold_time = 1 * SEG;

    piramide[cara][0][0].target_value_hi = 0;
    piramide[cara][0][1].target_value_hi = luz100;
    piramide[cara][0][2].target_value_hi = 0;
    piramide[cara][0][3].target_value_hi = luz100;

    piramide[cara][1][0].target_value_hi = 0;
    piramide[cara][1][1].target_value_hi = 0;
    piramide[cara][1][2].target_value_hi = 0;
    piramide[cara][1][3].target_value_hi = 0;

    piramide[cara][2][0].target_value_hi = luz100;
    piramide[cara][2][1].target_value_hi = 0;
    piramide[cara][2][2].target_value_hi = luz100;
    piramide[cara][2][3].target_value_hi = 0;

    piramide[cara][3][0].target_value_hi = luz100;
    piramide[cara][3][1].target_value_hi = luz100;
    piramide[cara][3][2].target_value_hi = luz100;
    piramide[cara][3][3].target_value_hi = luz100;

    for (int tr = 0; tr < TR; tr++)
    {
      for (int ti = 0; ti < TI; ti++)
      {
        piramide[cara][tr][ti].fade_time = fade_time;
        piramide[cara][tr][ti].hold_time = hold_time;
        piramide[cara][tr][ti].target_value_lo = 0;
        piramide[cara][tr][ti].modo = modo;
        piramide[cara][tr][ti].nmodo = nmodo;
        SoftPWMSetFadeTime(piramide[cara][tr][ti].pin_softpwm, fade_time, fade_time);
      }
    }
    return;
    break;

  // case CARA_LATIDO_MITADES:
  //   target_value_hi = luz100;
  //   target_value_lo = 0;
  //   fade_time = 1 * SEG;
  //   hold_time = 0.1 * SEG;
  //   seq_time = 0;

  //   //LADO DERECHO
  //   piramide[cara][0][1].seq_time = seq_time;
  //   piramide[cara][0][3].seq_time = seq_time;
  //   piramide[cara][2][2].seq_time = seq_time;
  //   piramide[cara][2][0].seq_time = seq_time;
  //   piramide[cara][3][0].seq_time = seq_time;
  //   piramide[cara][3][1].seq_time = seq_time;
  //   piramide[cara][3][2].seq_time = seq_time;
  //   piramide[cara][3][3].seq_time = seq_time;

  //   piramide[cara][0][1].seq_tick = now + seq_time;
  //   piramide[cara][0][3].seq_tick = now + seq_time;
  //   piramide[cara][2][2].seq_tick = now + seq_time;
  //   piramide[cara][2][0].seq_tick = now + seq_time;
  //   piramide[cara][3][0].seq_tick = now + seq_time;
  //   piramide[cara][3][1].seq_tick = now + seq_time;
  //   piramide[cara][3][2].seq_tick = now + seq_time;
  //   piramide[cara][3][3].seq_tick = now + seq_time;

  //   seq_time += seq_time + hold_time;

  //   //LADO IZQUIERDO
  //   piramide[cara][0][0].seq_time = seq_time;
  //   piramide[cara][0][2].seq_time = seq_time;
  //   piramide[cara][2][3].seq_time = seq_time;
  //   piramide[cara][2][1].seq_time = seq_time;
  //   piramide[cara][1][1].seq_time = seq_time;
  //   piramide[cara][1][0].seq_time = seq_time;
  //   piramide[cara][1][3].seq_time = seq_time;
  //   piramide[cara][1][2].seq_time = seq_time;

  //   piramide[cara][0][0].seq_tick = now + seq_time;
  //   piramide[cara][0][2].seq_tick = now + seq_time;
  //   piramide[cara][2][3].seq_tick = now + seq_time;
  //   piramide[cara][2][1].seq_tick = now + seq_time;
  //   piramide[cara][1][1].seq_tick = now + seq_time;
  //   piramide[cara][1][0].seq_tick = now + seq_time;
  //   piramide[cara][1][3].seq_tick = now + seq_time;
  //   piramide[cara][1][2].seq_tick = now + seq_time;
  //   break;

  // case CARA_SEQ_BASE:
  //   target_value_hi = luz100;
  //   target_value_lo = 0;
  //   fade_time = 1 * SEG;
  //   hold_time = 1 * SEG;
  //   for (int tr = 0; tr < TR; tr++)
  //   {
  //     for (int ti = 0; ti < TI; ti++)
  //     {
  //       //piramide[cara][tr][ti]->direction = UP;
  //       //piramide[cara][tr][ti].seq_time = seq_time;
  //       //piramide[cara][tr][ti].seq_tick = now + seq_time;
  //       piramide[cara][tr][ti].caras_order = 0;
  //       piramide[cara][tr][ti].caras_order_max = 16;        
  //       piramide[cara][tr][ti].seq_order = seq_order;
  //       seq_order++;
  //     }
  //   }
  //   break;
  }

  // Acá se pueden hacer configuraciones por cara
  // Seteamos los valores si en el switch anteriormente no se hizo
  for (int tr = 0; tr < TR; tr++)
  {
    for (int ti = 0; ti < TI; ti++)
    {
      Serial.println("Seteando valores y fades y poniendo en sync");
      Serial.println(modo_modos_time);
      // if(piramide[cara][tr][ti].hold_tick > hold_sync_tick)
      //   hold_sync_tick = piramide[cara][tr][ti].hold_tick;
      // if(piramide[cara][tr][ti].seq_tick > hold_sync_tick);
      //   hold_sync_tick = piramide[cara][tr][ti].seq_tick;
      piramide[cara][tr][ti].hold_tick = hold_sync_tick;
      piramide[cara][tr][ti].modo = modo;
      piramide[cara][tr][ti].nmodo = nmodo;
      piramide[cara][tr][ti].fade_time = fade_time;
      piramide[cara][tr][ti].hold_time = hold_time;
      piramide[cara][tr][ti].target_value_hi = target_value_hi;
      piramide[cara][tr][ti].target_value_lo = target_value_mid;
      piramide[cara][tr][ti].target_value_lo = target_value_lo;
      Serial.println(piramide[cara][tr][ti].pin_softpwm);
      SoftPWMSetFadeTime(piramide[cara][tr][ti].pin_softpwm, fade_time, fade_time);
      Serial.println("Termine de setear valores");
      Serial.println(modo_modos_time);
    }
  }
}

// Setear el modo de modos de la piramide
// Esta funcion simplemente es hardcodear que distribucion de modos
// tiene que tener el modo de modos en las caras
void set_modo_modos()
{
  switch (current_modo_modos)
  {
  case 1: // dos caras on, dos caras random
    set_modo_cara(0, CARA_RANDOM);
    set_modo_cara(1, CARA_RANDOM);
    break;
  case 2:
    set_modo_cara(0, CARA_ON);
    set_modo_cara(1, CARA_OFF);
    break;
  case 3:
    set_modo_cara(0, CARA_LATIDO);
    set_modo_cara(1, CARA_LATIDO);
    break;
  case 4:
    set_modo_cara(0, CARA_STROBO1);
    set_modo_cara(1, CARA_STROBO1);
    break;
  case 5:
    set_modo_cara(0, CARA_STROBO2);
    set_modo_cara(1, CARA_STROBO2);
    break;
  case 6:
    set_modo_cara(0, CARA_STROBO3);
    set_modo_cara(1, CARA_STROBO3);
    break;
  case 7:
    set_modo_cara(0, CARA_IZQUIERDA);
    set_modo_cara(1, CARA_IZQUIERDA);
    break;
  case 8:
    set_modo_cara(0, CARA_DERECHA);
    set_modo_cara(1, CARA_DERECHA);
    break;
  case 9:
    set_modo_cara(0, CARA_3D1);
    set_modo_cara(1, CARA_3D1);
    break;
  case 10:
    set_modo_cara(0, CARA_3D2);
    set_modo_cara(1, CARA_3D2);
    break;
  case 11:
    set_modo_cara(0, CARA_3D3);
    set_modo_cara(1, CARA_3D3);
    break;
  case 12:
    set_modo_cara(0, CARA_3D4);
    set_modo_cara(1, CARA_3D4);
    break;
  case 13: // dos caras on, dos caras random
    set_modo_cara(0, CARA_RANDOM_RAPIDO);
    set_modo_cara(1, CARA_RANDOM_RAPIDO);
    break;
  case 14: // dos caras on, dos caras random
    set_modo_cara(0, CARA_RANDOM_SUPER_RAPIDO);
    set_modo_cara(1, CARA_RANDOM_SUPER_RAPIDO);
    break;
  case 15:
    set_modo_cara(0, CARA_3D1);
    set_modo_cara(1, CARA_3D2);
    break;
  case 16:
    set_modo_cara(0, CARA_3D1);
    set_modo_cara(1, CARA_3D3);
    break;
  case 17:
    set_modo_cara(0, CARA_3D1);
    set_modo_cara(1, CARA_3D4);
    break;
  case 18:
    set_modo_cara(0, CARA_3D2);
    set_modo_cara(1, CARA_3D1);
    break;
  case 19:
    set_modo_cara(0, CARA_3D2);
    set_modo_cara(1, CARA_3D3);
    break;
  case 20:
    set_modo_cara(0, CARA_3D2);
    set_modo_cara(1, CARA_3D4);
    break;
  case 21:
    set_modo_cara(0, CARA_3D3);
    set_modo_cara(1, CARA_3D1);
    break;
  case 22:
    set_modo_cara(0, CARA_3D3);
    set_modo_cara(1, CARA_3D2);
    break;
  case 23:
    set_modo_cara(0, CARA_3D3);
    set_modo_cara(1, CARA_3D4);
    break;
  case 24:
    set_modo_cara(0, CARA_3D4);
    set_modo_cara(1, CARA_3D1);
    break;
  case 25:
    set_modo_cara(0, CARA_3D4);
    set_modo_cara(1, CARA_3D2);
    break;
  case 26:
    set_modo_cara(0, CARA_3D4);
    set_modo_cara(1, CARA_3D3);
    break;
  case 27:
    set_modo_cara(0, CARA_3D4);
    set_modo_cara(1, CARA_3D4);
    break;
  case 28:
    set_modo_cara(0, CARA_OFF);
    set_modo_cara(1, CARA_ON);
    break;
  case 29: // dos caras on, dos caras random
    set_modo_cara(0, CARA_RANDOM_RAPIDO);
    set_modo_cara(1, CARA_RANDOM);
    break;
  case 30: // dos caras on, dos caras random
    set_modo_cara(0, CARA_RANDOM);
    set_modo_cara(1, CARA_RANDOM_RAPIDO);
    break;
  case 31: // dos caras on, dos caras random
    set_modo_cara(0, CARA_PLENOS1);
    set_modo_cara(1, CARA_PLENOS2);
    break;
  case 32: // dos caras on, dos caras random
    set_modo_cara(0, CARA_PLENOS2);
    set_modo_cara(1, CARA_PLENOS1);
    break;
  case 33: // dos caras on, dos caras random
    set_modo_cara(0, CARA_PLENOS1);
    set_modo_cara(1, CARA_PLENOS1);
    break;
  case 34: // dos caras on, dos caras random
    set_modo_cara(0, CARA_PLENOS2);
    set_modo_cara(1, CARA_PLENOS2);
    break;
  case 35: // dos caras on, dos caras random
    set_modo_cara(0, CARA_SOLO0);
    set_modo_cara(1, CARA_SOLO0);
    break;
  case 36:
    set_modo_cara(0, CARA_STROBO1);
    set_modo_cara(1, CARA_STROBO2);
    break;
  case 37: // dos caras on, dos caras random
    set_modo_cara(0, CARA_RANDOM);
    set_modo_cara(1, CARA_RANDOM);
    break;
  case 38: // dos caras on, dos caras random
    set_modo_cara(0, CARA_RANDOM_RAPIDO);
    set_modo_cara(1, CARA_RANDOM_RAPIDO);
    break;
  case 39: // dos caras on, dos caras random
    set_modo_cara(0, CARA_RANDOM_SUPER_RAPIDO);
    set_modo_cara(1, CARA_RANDOM_SUPER_RAPIDO);
    break;
  case 40:
    set_modo_cara(0, CARA_LATIDO);
    set_modo_cara(1, CARA_LATIDO);
    break;
  case 41:
    set_modo_cara(0, CARA_OFF);
    set_modo_cara(1, CARA_OFF);
    break;
  // case 3:
  //   set_modo_cara(0, modo_encendido, CARA_ON);
  //   set_modo_cara(1, modo_seq_tres, CARA_SEQ_TRES);
  //   break;
  }
}
