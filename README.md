# **Moto-Unit-Control-Arduino Nano**
## Una especie de **PLC** para controlar las luces de una moto.

Usando libreria [ButtonKing 1.0.2](https://github.com/TanPitch/ButtonKing/releases/tag/1.0.2)

<img src="https://github.com/Fzf-z/Central-Moto/blob/master/Documentos/IMG_20200412_204718-01.jpeg" width="400">

Cuenta con:
- 6 entradas Logicas Pull UP
- 6 salidas PWM (con Mosfet IRF9540) para 4A (sin disipador)
  > Circuito para salida PWM extraido de [Link](https://forum.arduino.cc/index.php?topic=451897.0)
- Regulador de voltaje



## Futuras Implementaciones

- Encendidio automatico de Luces despues arrancar el motor.
- Entradas aisladas con optoacopladores.
- Salidas con relé para manejar focos alogenos y que no requieran PWM.
- Soporte para Binary Encoding con 74LS148 [Link](https://github.com/bxparks/AceButton/blob/develop/docs/binary_encoding/README.md)
