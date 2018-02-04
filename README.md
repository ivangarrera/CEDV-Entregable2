# Ejercicio II - Manejo básico de C++ en UE4

### El ejercicio consistirá en una ampliación/modificación del proyecto manejado en las sesiones de Clases y Herencia.

A continuación se establecen los **requisitos mínimos** para el ejercicio a resolver:

* Creación de una nueva jerarquía, en C++, de 3 tipos **diferentes** de enemigos.
* Cada tipo de enemigo ha de tener un **comportamiento diferente**, tanto entre sí como con respecto a los proporcionados en el ejemplo de Herencia.
* **Limitar el número máximo de enemigos** que pueden aparecer en el mapa después de su eliminación. Por ejemplo, si este valor se establece a 25, entonces solo podrá haber 25 acciones de spawn de enemigos de forma general.
* Creación de una clase, denominada AchievementManager, responsable de **notificar eventos**, de manera gráfica, cuando se cumpla alguna de las siguientes condiciones:
    * Conseguir una racha de eliminación de n enemigos de un tipo. n ha de ser parametrizable.
    * Conseguir acabar con todos los enemigos sin fallar ningún disparo.
    * Conseguir acabar con todos los enemigos sin recibir daño.
