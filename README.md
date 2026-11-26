<div align="center">
  <p>Universidad Peruana de Ciencias Aplicadas</p>
  <p>Carrera de Ingeniería de Software</p>
  <p><strong>1ASI0572</strong></p>
  <p><strong>Desarrollo de Soluciones IOT</strong></p>
  <p>NRC</p>
  <p><strong>16518</strong></p>
  <h2>Laboratorio 4: Instalación heredada - Planta Costa Norte</h2>
  <p>Docente</p>
  <p><strong>Sanchez Portugal, Jimmy Enrique</strong></p>
  <p>Equipo</p>
  <p><strong>PrimeFuel</strong></p>
  <p>Grupo 2</p>
</div>


<h2 align="center">Integrantes</h2>
<div align="center">
  <table>
    <tr>
      <th><strong>N.º</strong></th>
      <th><strong>Código</strong></th>
      <th><strong>Apellidos y Nombres</strong></th>
      <th><strong>Nodo</strong></th>
      <th><strong>Rol</strong></th>
    </tr>
    <tr><td>1</td><td>u202317269</td><td>Bonifacio Jaramillo Samuel Jesus</td><td>N1 Pozas</td><td>Dueño de nodo</td></tr>
    <tr><td>2</td><td>u201822823</td><td>Castro Pariona Jefferson Ernesto</td><td>N1 Pozas</td><td>Dueño de nodo</td></tr>
    <tr><td>3</td><td>u20221a118</td><td>Katherine Maryory Mejia Aliaga</td><td>N2 Secadores</td><td>Dueño de nodo</td></tr>
    <tr><td>4</td><td>u202320684</td><td>Ponce Perales Alberto Alejandro</td><td>N3 Perímetro</td><td>Dueño de nodo</td></tr>
    <tr><td>5</td><td>u202321843</td><td>Delgado Carrasco Schneider Carlos Alberto</td><td>N4 Lavador</td><td>Dueño de nodo</td></tr>
    <tr><td>6</td><td>u202312700</td><td>Lopez Goitia Carlos Alberto</td><td>N4 Lavador</td><td>Dueño de nodo</td></tr>
    <tr><td>7</td><td>u202223286</td><td>Rodriguez Parco Joseph Pablo</td><td>N5 Gateway</td><td>Integrador</td></tr>
    <tr><td>8</td><td>u202116246</td><td>Guerrero Vasquez Jhon Danny</td><td>N5 Gateway</td><td>Dueño de nodo</td></tr>
  </table>
</div>


<div align="center">
  <p><strong>Período 202620</strong></p>
  <p><strong>Noviembre 2026</strong></p>
</div>


## Registro de Versiones

| Versión | Fecha    | Autores   | Descripción de modificación                                  |
| ------- | -------- | --------- | ------------------------------------------------------------ |
| v0.1    | 24/11/26 | PrimeFuel | Estructura inicial del README, roles y enlaces a las copias de Wokwi. |

## Enlaces del proyecto

**Repositorio del laboratorio:** https://github.com/16518-IoT-PrimeFuel/lab4-IoT

**Tablero de incidencias (Trello/Jira):** _<pegar URL>_

**Broker:** `broker.hivemq.com` (1883 nodos, WebSocket 8884) · **Cliente web:** [hivemq.com/demos/websocket-client](https://www.hivemq.com/demos/websocket-client/) · **Suscripción del grupo:** `upc/gc/#`

### Copias de Wokwi (corregidas)

| Nodo         | Responsable(s)     | Original (docente)                            | Copia corregida |
| ------------ | ------------------ | --------------------------------------------- | --------------- |
| N1 Pozas     | 1 y 2              | https://wokwi.com/projects/481589840859419649 | _<pendiente>_   |
| N2 Secadores | 3                  | https://wokwi.com/projects/481589918908098561 | https://wokwi.com/projects/481600352780962817  |
| N3 Perímetro | 4                  | https://wokwi.com/projects/481589993437759489 | _<pendiente>_   |
| N4 Lavador   | 5 y 6              | https://wokwi.com/projects/481590066854881281 | _<pendiente>_   |
| N5 Gateway   | 7 (integrador) y 8 | https://wokwi.com/projects/481590141067867137 | _<pendiente>_   |

## Contenido

- [1. Contexto y encargo](#1-contexto-y-encargo)
- [2. Roles y organización](#2-roles-y-organización)
- [3. Procedimiento por falla](#3-procedimiento-por-falla)
- [4. Bitácora de fallas](#4-bitácora-de-fallas)
- [5. Medición antes y después del lazo cerrado](#5-medición-antes-y-después-del-lazo-cerrado)
- [6. Pruebas de integración, regresión y ataque](#6-pruebas-de-integración-regresión-y-ataque)
- [7. Ramas y pull requests](#7-ramas-y-pull-requests)
- [8. Evidencia del tablero](#8-evidencia-del-tablero)
- [9. Exposición](#9-exposición)
- [10. Anexo: evidencias](#10-anexo-evidencias)

## 1. Contexto y encargo

Pesquera Costa Norte S.A.C. (empresa ficticia) procesa hasta 1 200 t diarias de anchoveta en Chimbote, a 800 m de una zona residencial. Un proveedor instaló un sistema IoT de 5 nodos (3 de detección, 1 de tratamiento de gases y 1 gateway) y se retiró. Como equipo de mantenimiento, debemos **auditar la instalación, encontrar cada falla, explicar su causa raíz, corregirla y demostrar que el sistema integrado vuelve a funcionar**. Cada nodo contiene 4 fallas (visible, silenciosa, de seguridad y cruzada); una falla no está resuelta hasta que se demuestra con una prueba.

## 2. Roles y organización

| Rol           | Responsabilidad                                              | Quién                    |
| ------------- | ------------------------------------------------------------ | ------------------------ |
| Dueño de nodo | Encuentra, corrige y prueba las fallas de su nodo; lleva su bitácora | Ver tabla de integrantes |
| Revisor       | Aprueba el PR de un compañero asignado; nadie aprueba su propio cambio | Ver rotación             |
| Integrador    | Dueño del gateway; dirige reuniones de pie, mantiene el tablero y coordina la prueba de integración | Integrante 7             |
| Grupo         | Resuelve las fallas cruzadas y ejecuta la prueba de regresión final | Todos                    |

**Rotación de revisión:** el integrante 1 revisa al 2, el 2 al 3, …, el 7 al 8 y el 8 revisa al integrador (7).

**Reuniones de pie** (3 min, minutos 60 y 120 de la sesión 1): ¿qué falla resolví?, ¿qué me bloquea?, ¿a quién necesito?

**Nodos en pareja:** solo un integrante ejecuta la simulación (mismo client ID = expulsión del broker); el otro revisa código y prepara pruebas.

## 3. Procedimiento por falla

1. **Observar** el síntoma frente a la especificación.
2. **Registrar** la incidencia en el tablero (responsable y estado).
3. **Diagnosticar** la causa raíz (línea de código, conexión del circuito o acuerdo del contrato).
4. **Corregir** en una rama `bugfix/<nodo>-<descripcion>`.
5. **Probar** que el síntoma desaparece y que nada más se rompió.
6. **Integrar** con PR aprobado por el revisor y commit `fix(<nodo>): <descripcion>`.


## 4. Bitácora de fallas

Una fila por falla (4 por nodo, 20 en total).

| N.º y nodo | Tipo | Paso del marco (12 pasos) | Síntoma | Causa raíz | Corrección (commit) | Prueba | Responsable / Revisor |
| --- | --- | --- | --- | --- | --- | --- | --- |
| F1 - N1 Pozas | Visible | Paso 8: sensores y actuadores | Con el DS18B20 a 22 °C la consola y HiveMQ muestran `"temp":71.6`. | `sensor.getTempFByIndex(0)` devuelve grados Fahrenheit; R1 define el umbral en 35 °C. | `getTempCByIndex(0)`. Commit `64a9c7f` (rama `bugfix/pozas-temp-celsius`). | Con 22 °C: antes `71.6`, después `22.0` en consola y HiveMQ. Evidencias: `evidencia/n1-pozas/f1-antes.png`, `f1-despues.png`. | Jefferson Castro / Samuel Bonifacio |
| F2 - N1 Pozas | Silenciosa | Paso 10: procesamiento por nodo | Con 40 °C y gas bajo el umbral las pozas no ventilan. Sin broker el nodo deja de leer sensores y de accionar el relé (incumple R2). | El `else` de la condición de gas sobrescribe la de temperatura, y `conectar()` bloquea el `loop()` con `while` sin salida. Además publicaba sin validar la hora NTP. | `ventilar = gas>umbral \|\| temp>35 \|\| ventMax`, reconexión sin bloqueo cada 5 s y no se publica sin broker ni hora válida. Commit `10e8807` (rama `bugfix/pozas-accion-local`). | 40 °C con gas bajo el umbral: antes `OFF`, después `ON`. Broker inválido: antes la consola queda congelada (57 s sin lecturas), después lee y ventila cada 2 s y muestra `Sin broker u hora valida: no se publica`. Evidencias: `f2-antes-temp.png`, `f2-despues-temp.png`, `f2-antes-broker.png`, `f2-despues-broker.png`. | Jefferson Castro / Samuel Bonifacio |
| F3 - N1 Pozas | Seguridad | Paso 4: capa de intercambio | Cualquiera que publique `UMBRAL:9000` en `upc/gc/pozas/cmd` cambia el umbral y apaga la ventilación (R10). | `alRecibir()` acepta `UMBRAL:` y `VENT:` sin firma, antigüedad ni rango. | Formato `<comando>\|<ts>\|<firma>` con HMAC de `pozas\|comando\|ts`, menos de 60 s y umbral entre 500 y 5000; rechazos publicados en `upc/gc/pozas/alerta`. Herramienta `nodos/n1-pozas/firmar_orden.py`. Commit `864a28c` (rama `bugfix/pozas-orden-firmada`). | Antes: `UMBRAL:9000` sin firma se acepta. Después: `UMBRAL:99999` da `Orden rechazada: formato`, una orden firmada vencida da `Orden rechazada: firma invalida o vencida` y `UMBRAL:5000` firmado se acepta. Evidencias: `f3-ataque-antes.png`, `f3-ataque-despues.png`, `f3-vencida-despues.png`, `f3-firmada-despues.png`. | Jefferson Castro / Samuel Bonifacio |
| F4 - N1 Pozas | Cruzada | Paso 4: capa de intercambio (contrato de interfaz) | HiveMQ recibe datos de pozas, pero el gateway no puede usar el valor (el síntoma aparece en N5). | N1 publica `"valor":"8859.6ppm"` (texto con unidad) y firma esa cadena; el contrato exige `valor` numérico y firma sobre `id\|ts\|valor`. | `"valor":<número>` y firma sobre `pozas\|ts\|<número>`. Commit `3abbf5f` (rama `bugfix/pozas-valor-numerico`). | HiveMQ: antes `"valor":"8859.6ppm"`, después `"valor":8859.6`; la firma publicada `e245434e7f030ec9` coincide con HMAC(`pozas\|1795653319\|8859.6`). Pendiente confirmar en el gateway (N5). Evidencias: `f4-antes.png`, `f4-despues.png`. | Jefferson Castro (síntoma en N5) / Samuel Bonifacio |
| F1 - N2 Secadores | Visible | Paso 10: procesamiento por nodo | Por revisión de código, sin reproducir: el nodo intenta publicar unas 10 veces por segundo; R8 exige cada 2 s. | `PERIODO = 100` ms en `sketch.ino`. | Pendiente (sin commit). Propuesta: `PERIODO = 2000`. | Pendiente: medir el intervalo entre mensajes en la consola y en HiveMQ. Evidencia inicial: `antes-01-circuito.png`. | Katherine Mejia / Jefferson Castro |
| F2 - N2 Secadores | Silenciosa | Paso 4: capa de intercambio | Por revisión de código, sin reproducir: la consola imprimiría el mensaje, pero HiveMQ no lo recibiría. | El mensaje (unos 245 bytes) más el tópico y la cabecera supera el búfer por defecto de `PubSubClient` (256 bytes): no se llama a `setBufferSize()` ni se comprueba el resultado de `publish()`. | Pendiente (sin commit). Propuesta: `mqtt.setBufferSize(512)`, quitar los campos que no pide el contrato y comprobar `publish()`. | Pendiente: verificar en HiveMQ que llegan los datos. | Katherine Mejia / Jefferson Castro |
| F3 - N2 Secadores | Seguridad | Paso 4: capa de intercambio | Por revisión de código: los datos salen con `"firma":""` y exponen equipo, zona y responsable en un broker público. | No se calcula el HMAC y el mensaje incluye campos fuera del contrato (R9). | Pendiente (sin commit). Propuesta: firmar `secadores\|ts\|valor` con HMAC-SHA256, publicar solo con hora NTP válida y retirar esos campos. | Pendiente: comparar la firma publicada y probar que el gateway rechaza un dato sin firma. | Katherine Mejia / Jefferson Castro |
| F4 - N2 Secadores | Cruzada | Paso 4: capa de intercambio (contrato de interfaz) | Por revisión de código, sin reproducir: si N2 y N3 corren a la vez, el broker desconectaría a uno cada vez que el otro se conecta. | N2 y N3 usan el mismo client ID, `gc-sensor`; el contrato exige uno único por nodo. | Pendiente (sin commit). Propuesta: ID propio, por ejemplo `gc-secadores-` más un sufijo único (N3 debe hacer lo mismo). | Pendiente: ejecutar N2 y N3 juntos y verificar que ninguno se reconecta en bucle. | Katherine Mejia / Jefferson Castro |
| F1 - N3 Perímetro | Visible | Paso 8: sensores y actuadores | El viento se calcula mal: con el potenciómetro en [posición] la consola muestra `viento=[valor antes]` en vez de [valor esperado], y el LED de riesgo no responde bien al rango 90°–180°. | `PIN_VIENTO=25` es un pin ADC2 (no usable con WiFi encendido) y `map(…, 0, 1023, 0, 360)` ignora que el ADC del ESP32 es de 12 bits (0–4095). | Pin 34 (ADC1) y `map(…, 0, 4095, 0, 359)`; cable `viento:SIG` a `esp:34`. Commit `[hash]`. | Con el gas alto y el potenciómetro en 0 %, 25 %, 50 %, 75 % y 100 % la consola muestra [0, ~90, ~180, ~269, 359]; el LED enciende solo con viento entre 90° y 180°. | Alberto Ponce / Katherine Mejia |
| F2 - N3 Perímetro | Silenciosa | Paso 10: procesamiento por nodo | Si el broker o el WiFi no están disponibles, el nodo se queda atrapado en `conectar()` y deja de leer el gas y de accionar el LED. Si no hay hora NTP, publica con `ts` cercano a 1970 y el gateway lo rechaza sin avisar. | `conectar()` bloquea el `loop()` con un `while` sin salida y no se valida la hora antes de publicar. | Reconexión sin bloqueo cada 5 s, el LED sigue funcionando y no se publica sin hora válida. Commit `[hash]`. | Con un broker inválido temporal: antes el LED nunca responde; después el LED responde y la consola imprime `Sin broker u hora valida: no se publica`. | Alberto Ponce / Katherine Mejia |
| F3 - N3 Perímetro | Seguridad | Paso 4: capa de intercambio | Cualquiera que publique `OFFSET:-10000` en `upc/gc/perimetro/cmd` cambia la calibración y el gas se lee como 0, así que el nodo queda ciego (R10). | El callback acepta `OFFSET:` sin comprobar firma, antigüedad ni rango. | La orden debe ser `OFFSET:<valor>:<ts>:<firma>`, firmada, de menos de 60 s y con valor absoluto de hasta 500. Commit `[hash]`. | Desde HiveMQ se publica `OFFSET:-10000`: antes la consola muestra `Nueva calibracion: -10000.00`; después muestra `Orden rechazada: formato`. | Alberto Ponce / Katherine Mejia |
| F4 - N3 Perímetro | Cruzada | Paso 4: capa de intercambio (contrato de tópicos) | Los datos de N3 salen a `upc/gc/perimetro/datos` pero el gateway nunca imprime `OK perimetro`. | El gateway se suscribe a `upc/gc/+/dato` (sin "s"), distinto del contrato `datos`. | En N5: `mqtt.subscribe("upc/gc/+/datos")`. Commit `[hash]` en la rama del gateway. | Antes: HiveMQ muestra los datos y el gateway no responde. Después: el gateway imprime `OK perimetro: [valor] ppm` cada 2 s. | Alberto Ponce (síntoma) / corrige N5 (Joseph) |
| F1 - N4 Lavador | Visible | Paso 8: sensores y actuadores | El lavador recibe la orden ON mediante MQTT y el motor gira, pero el relé no responde correctamente a las órdenes de control. | En `sketch.ino`, `PIN_RELE=27`, mientras que en `diagram.json` la entrada `rele:IN` está conectada a `esp:26`. | Se modificó `PIN_RELE` de 27 a 26 para establecer la correspondencia entre el código y el circuito. Commit `b230c4d`. [PR #1](https://github.com/16518-IoT-PrimeFuel/lab4-IoT/pull/1). | Se enviaron órdenes ON y OFF desde HiveMQ al tópico `upc/gc/lavador/cmd`. Después de la corrección, el indicador del relé responde a ambas órdenes. Evidencias: `f1-antes.png`, `f1-causa-raiz.png`, `f1-despues-off.png` y `f1-despues.png`. | Schneider Delgado |
| F2 - N4 Lavador | Silenciosa | Paso 10: procesamiento por nodo | El lavador permanece apagado después de 60 segundos sin recibir mensajes del gateway, incumpliendo la regla R6. | El `loop()` reinicia constantemente `ultimoContacto` mientras MQTT está conectado. Además, `conectar()` contiene bucles de espera indefinida que impiden evaluar el modo seguro durante una desconexión. | Se actualiza `ultimoContacto` al recibir mensajes reconocidos, se eliminan los bucles de espera indefinida y se implementan reintentos de conexión cada 5 s. Commit `70c141b`. [PR #2](https://github.com/16518-IoT-PrimeFuel/lab4-IoT/pull/2). | Antes: el lavador permanece apagado tras la ausencia de mensajes del gateway. Después: el relé y el motor se activan automáticamente y la consola muestra `[F2] Activando modo seguro tras 60 segundos`. Evidencias: `f2-antes.png`, `f2-inicio-prueba.png` y `f2-despues.png`. Pendiente la prueba de desconexión completa del broker. | Schneider Delgado |
| F3 - N4 Lavador | Seguridad | Paso 4: capa de intercambio | El lavador acepta ordenes `ON`, `OFF` e `INT:` en texto plano en `upc/gc/lavador/cmd` sin ninguna validacion, y ejecuta un `OFF` aunque la concentracion de gas este sobre el umbral de 2000 ppm (R7, R10). | El `alRecibir()` no verificaba firma ni antiguedad en los comandos recibidos, y `apagar()` no revisaba la variable `concentracion` antes de bajar el rele. | Las ordenes ahora requieren el formato `<comando>|<ts>|<firma>`, validado con HMAC-SHA256 (misma clave del grupo) y antiguedad menor a 60 s; un `OFF` se ignora si `concentracion >= CONC_ALTA`. Tambien se agrego `msg.trim()` para evitar fallos de parseo por espacios o saltos de linea en el payload. Commit `71c3411`. | Desde HiveMQ: un `ON` en texto plano fue aceptado en el codigo original y rechazado con `{"alerta":"orden rechazada: formato"}` en el corregido. Con la concentracion simulada en 2500 ppm, un `OFF` correctamente firmado fue ignorado con `{"alerta":"orden OFF ignorada: concentracion alta"}`. Evidencias: `f3-ataque-antes.png`, `f3-ataque-despues.png`, `f3-conc-alta-despues.png`. | Carlos Lopez / Schneider Delgado |
| F4 - N4 Lavador | Cruzada | Paso 4: capa de intercambio (contrato de topicos) | En el escenario integrado, con gas alto en 2 o mas nodos y viento entre 90 y 180 grados, el gateway nunca envia `ON` a `upc/gc/lavador/cmd`, por lo que el lazo cerrado del lavador no llega a probarse. | El gateway (N5) se suscribe a `upc/gc/+/dato` en vez de `upc/gc/+/datos`, el mismo desacuerdo de contrato ya identificado en F4 de N3 Perimetro, asi que nunca recibe los niveles de gas de ningun nodo de deteccion. | Corresponde a N5: cambiar a `mqtt.subscribe("upc/gc/+/datos")`. Pendiente de que Joseph aplique y confirme el fix en su rama del gateway. | Pendiente, bloqueada hasta integrar el fix de N5. Una vez aplicado, se forzara el escenario de gas alto y viento 90-180 grados y se medira el tiempo de deteccion a confirmacion para la seccion 5. | Carlos Lopez (sintoma) / corrige N5 (Joseph) |
| F1 - N5 Gateway | Visible | | | | | | |
| F2 - N5 Gateway | Silenciosa | | | | | | |
| F3 - N5 Gateway | Seguridad | | | | | | |
| F4 - N5 Gateway | Cruzada | | | | | | |

## 5. Medición antes y después del lazo cerrado

Tiempo desde la detección hasta la confirmación del lavador (R5: máximo 10 s).

| Momento                     | Detección (ts) | Confirmación (ts) | Tiempo (s) | Cumple R5 |
| --------------------------- | -------------- | ----------------- | ---------- | --------- |
| Antes de las correcciones   |                |                   |            |           |
| Después de las correcciones |                |                   |            |           |

## 6. Pruebas de integración, regresión y ataque

| Prueba                                  | Escenario                                      | Resultado esperado                                | Resultado | Evidencia |
| --------------------------------------- | ---------------------------------------------- | ------------------------------------------------- | --------- | --------- |
| Integración                             | Pico de gas + viento 90°–180°                  | Gateway enciende lavador; lavador confirma ≤ 10 s |           |           |
| Apagado (R4/R7)                         | Concentración < 80 % del umbral                | Lavador se apaga solo entonces                    |           |           |
| Falla del lavador (R5)                  | Lavador sin confirmar                          | Alerta «falla del lavador» y ventilación máxima   |           |           |
| Modo seguro (R6)                        | Lavador sin mensajes 60 s                      | Lavador se enciende                               |           |           |
| Ataque: sin firma / firma inválida (R9) | Publicar en `upc/gc/<nodo>/datos` desde HiveMQ | Gateway rechaza                                   |           |           |
| Ataque: mensaje antiguo > 60 s (R9)     | Reenviar un dato viejo                         | Gateway rechaza                                   |           |           |
| Ataque: orden falsa (R10)               | Publicar en `upc/gc/<nodo>/cmd`                | Nodo ignora                                       | N1 pozas: cumple. Orden sin firma y orden firmada vencida rechazadas; orden firmada vigente aceptada. Resto de nodos: pendiente | `evidencia/n1-pozas/f3-ataque-despues.png`, `f3-vencida-despues.png`, `f3-firmada-despues.png` |
| Regresión final                         | Todos los escenarios anteriores                | Sin regresiones                                   |           |           |


## 7. Ramas y pull requests

| Rama | PR | Commits | Falla / contenido | Autor (GitHub) | Revisor (rotación) | Estado |
| ---- | -- | ------- | ----------------- | -------------- | ------------------ | ------ |
| `bugfix/n1-pozas` | — | — | Sin commits propios (ya contenida en `main`) | JeffersonCastroPariona | — | Sin cambios frente a `main` |
| `bugfix/pozas-temp-celsius` | [#9](https://github.com/16518-IoT-PrimeFuel/lab4-IoT/pull/9) | `64a9c7f`, `b2db61f` | N1 F1: temperatura en grados Celsius, con evidencias | JeffersonCastroPariona | samuelbonifacio015 | Mergeado, sin revisiones |
| `bugfix/pozas-accion-local` | [#7](https://github.com/16518-IoT-PrimeFuel/lab4-IoT/pull/7) | `10e8807`, `a3c1231` | N1 F2: ventilación por gas o temperatura sin depender del broker, con evidencias (incluye F1) | JeffersonCastroPariona | samuelbonifacio015 | Mergeado, sin revisiones |
| `bugfix/pozas-orden-firmada` | [#4](https://github.com/16518-IoT-PrimeFuel/lab4-IoT/pull/4) | `864a28c`, `8167c24` | N1 F3: valida firma HMAC y antigüedad de las órdenes, con evidencias (incluye F1 y F2) | JeffersonCastroPariona | samuelbonifacio015 | Mergeado, sin revisiones |
| `bugfix/pozas-valor-numerico` | [#5](https://github.com/16518-IoT-PrimeFuel/lab4-IoT/pull/5) | `3abbf5f`, `2f909d4` | N1 F4: publica el valor numérico según el contrato, con evidencias (incluye F1 a F3) | JeffersonCastroPariona | samuelbonifacio015 | Mergeado, sin revisiones |
| `docs/n1-pozas-bitacora` | [#8](https://github.com/16518-IoT-PrimeFuel/lab4-IoT/pull/8) | `4faf55e` | Bitácora F1 a F4 de N1 | JeffersonCastroPariona | samuelbonifacio015 | Abierto, sin revisiones; en conflicto con `main` |
| `bugfix/n4-lavador-pin-rele` | [#1](https://github.com/16518-IoT-PrimeFuel/lab4-IoT/pull/1) | `bf07c5c`, `b230c4d` | N4: archivos base y F1 (pin del relé) | schneiderdc | aponceperales | Mergeado, sin revisiones |
| `bugfix/n4-lavador-modo-seguro` | [#2](https://github.com/16518-IoT-PrimeFuel/lab4-IoT/pull/2) | `97e9948` | N4 F2: modo seguro (incluye F1) | schneiderdc | aponceperales | Mergeado, sin revisiones |
| `bugfix/n4-lavador-ordenes-firmadas` | — | `71c3411`, `c8f9fc2` | N4 F3: órdenes firmadas y bloqueo de apagado con concentración alta, con evidencias | CarlosAlb101 | schneiderdc | Publicada, sin PR; en conflicto con `main` |
| `docs/n4-lavador-bitacora` | [#3](https://github.com/16518-IoT-PrimeFuel/lab4-IoT/pull/3) | `e98d23f`, `4a1bb38` | Bitácora F1 a F4 de N4 | schneiderdc, CarlosAlb101 | aponceperales | Mergeado, sin revisiones |
| `bugfix/n2-secadores` | — | — | N2: archivos base, evidencia inicial y registro de fallas | KathMJ | JeffersonCastroPariona | Sin publicar en GitHub |

## 8. Evidencias

### N1 Pozas

#### N1 F1: temperatura en Celsius

**Antes: 22 °C se publica como 71.6** (`f1-antes.png`)

<img src="evidencia/n1-pozas/f1-antes.png" alt="N1 Antes: 22 °C se publica como 71.6" width="800">

**Después: se publica 22.0** (`f1-despues.png`)

<img src="evidencia/n1-pozas/f1-despues.png" alt="N1 Después: se publica 22.0" width="800">

#### N1 F2: acción local sin broker

**Antes: 40 °C y ventilación apagada** (`f2-antes-temp.png`)

<img src="evidencia/n1-pozas/f2-antes-temp.png" alt="N1 Antes: 40 °C y ventilación apagada" width="800">

**Después: 40 °C y ventilación encendida** (`f2-despues-temp.png`)

<img src="evidencia/n1-pozas/f2-despues-temp.png" alt="N1 Después: 40 °C y ventilación encendida" width="800">

**Antes: broker inválido, sin lecturas** (`f2-antes-broker.png`)

<img src="evidencia/n1-pozas/f2-antes-broker.png" alt="N1 Antes: broker inválido, sin lecturas" width="800">

**Después: broker inválido, sigue ventilando** (`f2-despues-broker.png`)

<img src="evidencia/n1-pozas/f2-despues-broker.png" alt="N1 Después: broker inválido, sigue ventilando" width="800">

#### N1 F3: órdenes firmadas

**Antes: se acepta una orden sin firma** (`f3-ataque-antes.png`)

<img src="evidencia/n1-pozas/f3-ataque-antes.png" alt="N1 Antes: se acepta una orden sin firma" width="800">

**Después: orden sin firma rechazada** (`f3-ataque-despues.png`)

<img src="evidencia/n1-pozas/f3-ataque-despues.png" alt="N1 Después: orden sin firma rechazada" width="800">

**Después: orden vencida rechazada** (`f3-vencida-despues.png`)

<img src="evidencia/n1-pozas/f3-vencida-despues.png" alt="N1 Después: orden vencida rechazada" width="800">

**Después: orden firmada aceptada** (`f3-firmada-despues.png`)

<img src="evidencia/n1-pozas/f3-firmada-despues.png" alt="N1 Después: orden firmada aceptada" width="800">

#### N1 F4: valor numérico

**Antes: valor como texto con unidad** (`f4-antes.png`)

<img src="evidencia/n1-pozas/f4-antes.png" alt="N1 Antes: valor como texto con unidad" width="800">

**Después: valor numérico** (`f4-despues.png`)

<img src="evidencia/n1-pozas/f4-despues.png" alt="N1 Después: valor numérico" width="800">

### N2 Secadores

#### N2 estado inicial (antes de corregir)

**Código y circuito heredados** (`antes-01-circuito.png`)

<img src="evidencia/n2-secadores/antes-01-circuito.png" alt="N2 Código y circuito heredados" width="800">

**Arranque de la simulación** (`antes-02-arranque.png`)

<img src="evidencia/n2-secadores/antes-02-arranque.png" alt="N2 Arranque de la simulación" width="800">

**Conexiones en diagram.json** (`antes-03-diagrama.png`)

<img src="evidencia/n2-secadores/antes-03-diagrama.png" alt="N2 Conexiones en diagram.json" width="800">

**A los 40 s: sin mensajes en la consola tras el arranque** (`antes-04-sin-salida.png`)

<img src="evidencia/n2-secadores/antes-04-sin-salida.png" alt="N2 A los 40 s: sin mensajes en la consola tras el arranque" width="800">

### N4 Lavador

#### N4 F1: pin del relé

**Antes de la corrección** (`f1-antes.png`)

<img src="evidencia/n4-lavador/f1-antes.png" alt="N4 Antes de la corrección" width="800">

**Causa raíz** (`f1-causa-raiz.png`)

<img src="evidencia/n4-lavador/f1-causa-raiz.png" alt="N4 Causa raíz" width="800">

**Después de la corrección** (`f1-despues.png`)

<img src="evidencia/n4-lavador/f1-despues.png" alt="N4 Después de la corrección" width="800">

**Después: orden OFF** (`f1-despues-off.png`)

<img src="evidencia/n4-lavador/f1-despues-off.png" alt="N4 Después: orden OFF" width="800">

#### N4 F2: modo seguro

**Antes de la corrección** (`f2-antes.png`)

<img src="evidencia/n4-lavador/f2-antes.png" alt="N4 Antes de la corrección" width="800">

**Inicio de la prueba** (`f2-inicio-prueba.png`)

<img src="evidencia/n4-lavador/f2-inicio-prueba.png" alt="N4 Inicio de la prueba" width="800">

**Después: modo seguro activado** (`f2-despues.png`)

<img src="evidencia/n4-lavador/f2-despues.png" alt="N4 Después: modo seguro activado" width="800">

#### N4 F3: órdenes firmadas (rama `bugfix/n4-lavador-ordenes-firmadas`, sin integrar)

**Antes: ataque** (`f3-ataque-antes.png`)

<img src="https://raw.githubusercontent.com/16518-IoT-PrimeFuel/lab4-IoT/c8f9fc206b8299435042fa516d2148585f0026b0/evidencia/n4-lavador/f3-ataque-antes.png" alt="N4 Antes: ataque" width="800">

**Después: ataque rechazado** (`f3-ataque-despues.png`)

<img src="https://raw.githubusercontent.com/16518-IoT-PrimeFuel/lab4-IoT/c8f9fc206b8299435042fa516d2148585f0026b0/evidencia/n4-lavador/f3-ataque-despues.png" alt="N4 Después: ataque rechazado" width="800">

**Después: OFF ignorado con concentración alta** (`f3-conc-alta-despues.png`)

<img src="https://raw.githubusercontent.com/16518-IoT-PrimeFuel/lab4-IoT/c8f9fc206b8299435042fa516d2148585f0026b0/evidencia/n4-lavador/f3-conc-alta-despues.png" alt="N4 Después: OFF ignorado con concentración alta" width="800">

### N3 Perímetro y N5 Gateway

_Sin imágenes de evidencia en el repositorio._
