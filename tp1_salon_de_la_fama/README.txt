Como aclaración general, lamentablemente no llegué a terminar el tp, o sea que está incompleto.
Siguiendo el orden provisto por el pdf, lo más lejos que llegué fue la implementación de la función salon_leer_archivo pero sin éxito de completarla.
Entiendo que no es suficiente para aprobar pero me parecia que era prudente al menos entregar lo que llegué a hacer.

Del archivo util.c hice cada una de las funciones dentro de cada una de las declaraciones provistas sin funciones ni modularizaciones adicionales.
A falta de pruebas, las únicas funciones que no estoy seguro de que cumplan su trabajo son vtrfree y fclosen.
En cuanto a fgets_alloc utilicé el ejemplo dado en uno de los videos cortos de la cátedra en el que se implementaba una función muy parecida.
Agregué la biblioteca de string.h para hacer uso del strlen en split.

En salon.c empecé incluyendo el archivo util.h para poder usar las funciones implementadas.
De este archivo solo a llegué a empezar la funcion salon_leer_archivo pero quedó incompleta.

1.Heap y stack: ¿Para qué y cómo se utiliza cada uno?
El Stack se usa para almacenar variables locales, mientras que el Heap es un espacio de memoria dinámica que se usa para almacenar objetos.

2.Malloc/Realloc/Free: ¿Cómo y para qué se utilizan?
Tanto malloc y realloc se utilizan para reservar memoria dinámica en el heap, mientras que free se utiliza para liberar memoria.
Malloc particularmente se usa para reservar o asignar un número específico de bytes a un objeto que queremos guardar en el heap.
Realloc sirve para aumentar o disminuir el tamaño de memoria que un objeto tiene reservada.
Free, como dice su nombre, libera el bloque de memoria asignado a un objeto de nuevo al sistema.