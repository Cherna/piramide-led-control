void set_pines_softpwm()
{
  // PRIMER CARA, LADO DERECHO
  piramide[0][0][1].pin_softpwm = 38;
  piramide[0][0][3].pin_softpwm = 39;
  piramide[0][2][2].pin_softpwm = 40;
  piramide[0][2][0].pin_softpwm = 41;
  piramide[0][3][0].pin_softpwm = 42;
  piramide[0][3][1].pin_softpwm = 43;
  piramide[0][3][2].pin_softpwm = 44;
  piramide[0][3][3].pin_softpwm = 45;
  
  // PRIMER CARA, LADO IZQUIERDO
  piramide[0][0][0].pin_softpwm = 22;
  piramide[0][0][2].pin_softpwm = 23;
  piramide[0][2][3].pin_softpwm = 28;
  piramide[0][2][1].pin_softpwm = 29;
  piramide[0][1][1].pin_softpwm = 26;
  piramide[0][1][0].pin_softpwm = 27;
  piramide[0][1][3].pin_softpwm = 24;
  piramide[0][1][2].pin_softpwm = 25;

  // SEGUNDA CARA, LADO DERECHO
  piramide[1][0][1].pin_softpwm = 46;
  piramide[1][0][3].pin_softpwm = 47;
  piramide[1][2][2].pin_softpwm = 48;
  piramide[1][2][0].pin_softpwm = 49;
  piramide[1][3][0].pin_softpwm = 50;
  piramide[1][3][1].pin_softpwm = 51;
  piramide[1][3][2].pin_softpwm = 52;
  piramide[1][3][3].pin_softpwm = 53;

  // SEGUNDA CARA, LADO IZQUIERDO
  piramide[1][0][0].pin_softpwm = 30;
  piramide[1][0][2].pin_softpwm = 31;
  piramide[1][2][3].pin_softpwm = 32;
  piramide[1][2][1].pin_softpwm = 33;
  piramide[1][1][1].pin_softpwm = 34;
  piramide[1][1][0].pin_softpwm = 35;
  piramide[1][1][3].pin_softpwm = 36;
  piramide[1][1][2].pin_softpwm = 37;

}
