void modo_pleno(Triangulito *target)
{
  if (target->current_value != target->target_value_hi)
  {
    Serial.println("Resolviendo modo encendido");
    Serial.println(modo_modos_time);
    SoftPWMSet(target->pin_softpwm, target->target_value_hi);
    target->current_value = target->target_value_hi;
  }
}

void modo_latido(Triangulito *target)
{
  int target_value;
  if (!is_fading(target) && !is_holding(target))
  {
    //Serial.println("Resolviendo modo latido");
    if (target->direction == UP)
      target_value = target->target_value_hi;
    else
      target_value = target->target_value_lo;
    SoftPWMSet(target->pin_softpwm, target_value);
    target->fade_tick = now + target->fade_time;
    target->hold_tick = target->fade_tick + target->hold_time;
    target->direction = !target->direction;
    target->current_value = target_value;
  }
}



// void modo_seq_dos(Triangulito *target)
// {
//   int target_value;
//   if (is_seq_moment(target) && !is_fading(target) && !is_holding(target))
//   {
//     if (target->direction == UP)
//       target_value = target->target_value_hi;
//     else
//       target_value = target->target_value_lo;

//     SoftPWMSet(target->pin_softpwm, target_value);

//     target->fade_tick = now + target->fade_time;
//     target->hold_tick = target->fade_tick + target->hold_time;
//     target->seq_tick  = target->hold_tick + target->seq_time;
//     target->direction = !target->direction;
//     target->current_value = target_value;

//     target->caras_order = target->caras_order + 1;
//     if(target->caras_order == target->caras_order_max)
//       target->caras_order = 0;
//   }
// }

// void modo_seq_tres(Triangulito *target)
// {
//   int target_value;
//   if (is_seq_moment(target) && !is_fading(target) && !is_holding(target))
//   {
//     if ((target->direction == UP && target->current_value == target->target_value_lo) ||
//         (target->direction == DOWN && target->current_value == target->target_value_hi))
//       target_value = target->target_value_mid;
//     else if (target->direction == UP)
//     {
//       target_value = target->target_value_hi;
//       target->direction = DOWN;
//     }
//     else
//     {
//       target_value = target->target_value_lo;
//       target->direction = UP;
//     }

//     SoftPWMSet(target->pin_softpwm, target_value);

//     target->fade_tick = now + target->fade_time;
//     target->hold_tick = target->fade_tick + target->hold_time;
//     target->seq_tick  = target->hold_tick + target->seq_time;
//     target->current_value = target_value;
//   }
// }
