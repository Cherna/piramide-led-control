// bool is_seq_moment(Triangulito *target)
// {
//   if (target->seq_order == target->caras_order)
//   {
//     return true;
//   }
//   return false;
// }

bool is_fading(Triangulito *target)
{
  if (now >= target->fade_tick)
  {
    return false;
  }
  return true;
}

bool is_holding(Triangulito *target)
{
  if (now >= target->hold_tick)
  {
    return false;
  }
  return true;
}

void modos_exec()
{
  // switch(modo_secuencia) {
  //   case 1:
  //     modo_encendido(target);
  //       break;
  // }

  // // Resolver modos secuencia
  // for (int ca = 0; ca < CA; ca++)
  // {
  //     switch(current_modo_secuencia[ca]) {
  //       case MODO_SEQ_BASE:

  //         break;
  //     }
  // }
  
  // Resolver otros
  for (int ca = 0; ca < CA; ca++)
  {
    for (int tr = 0; tr < TR; tr++)
    {
      for (int ti = 0; ti < TI; ti++)
      {
        Triangulito *target = &piramide[ca][tr][ti];
        if((*target->modo) != NULL) {
          (*target->modo)(target);
        }
      }
    }
  }
}

void init_piramide()
{
  for (int ca = 0; ca < CA; ca++)
  {
    for (int tr = 0; tr < TR; tr++)
    {
      for (int ti = 0; ti < TI; ti++)
      {
        Serial.println("Iniciando piramide");
        Triangulito *target = &piramide[ca][tr][ti];
        target->target_value_hi = 0;
        target->target_value_mid = 0;
        target->target_value_lo = 0;
        target->current_value = 0;

        target->direction = UP;

        target->fade_tick = 0;
        target->fade_time = 0;
        target->hold_tick = 0;
        target->hold_time = 0;
        // target->seq_tick = 0;
        // target->seq_time = 0;

        target->nmodo = 0;
        target->modo = NULL;

        SoftPWMSet(target->pin_softpwm, 0);
      }
    }
  }
}
