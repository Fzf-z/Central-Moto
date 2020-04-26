# **PLC-Moto-Arduino Nano**
## Una especie de **PLC** para controlar las luces de una moto.

<img src="https://github.com/Fzf-z/Central-Moto/blob/master/Documentos/IMG_20200412_204718-01.jpeg" width="400">

Cuenta con:
- 6 entradas Logicas Pull UP
- 6 salidas PWM (con Mosfet IRF9540) para 4A (sin disipador)
- Regulador de voltaje

>Circuito para salida PWM extraido de [Link](https://forum.arduino.cc/index.php?topic=451897.0)
>
>

## Futuras Implementaciones

- Entradas aisladas con optoacopladores.
- Salidas con relé para manejar focos alogenos y que no requieran PWM.
- Soporte para Binary Encoding con 74LS148 [LINK](https://github.com/bxparks/AceButton/blob/develop/docs/binary_encoding/README.md)
- Encendidio automatico de Luces despues arrancar el motor.
