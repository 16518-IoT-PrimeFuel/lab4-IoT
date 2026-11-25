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
  <p>Grupo</p>
  <p><strong>G3 (prefijo <code>gc</code>)</strong></p>
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

**Repositorio del laboratorio:** _<pegar URL del repo de GitHub del grupo>_

**Tablero de incidencias (Trello/Jira):** _<pegar URL>_

**Broker:** `broker.hivemq.com` (1883 nodos, WebSocket 8884) · **Cliente web:** [hivemq.com/demos/websocket-client](https://www.hivemq.com/demos/websocket-client/) · **Suscripción del grupo:** `upc/gc/#`

### Copias de Wokwi (corregidas)

| Nodo         | Responsable(s)     | Original (docente)                            | Copia corregida |
| ------------ | ------------------ | --------------------------------------------- | --------------- |
| N1 Pozas     | 1 y 2              | https://wokwi.com/projects/481589840859419649 | _<pendiente>_   |
| N2 Secadores | 3                  | https://wokwi.com/projects/481589918908098561 | _<pendiente>_   |
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
| F1 - N1 Pozas | Visible | | | | | | |
| F2 - N1 Pozas | Silenciosa | | | | | | |
| F3 - N1 Pozas | Seguridad | | | | | | |
| F4 - N1 Pozas | Cruzada | | | | | | |
| F1 - N2 Secadores | Visible | | | | | | |
| F2 - N2 Secadores | Silenciosa | | | | | | |
| F3 - N2 Secadores | Seguridad | | | | | | |
| F4 - N2 Secadores | Cruzada | | | | | | |
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

> El tipo de cada falla es una hipótesis inicial; se confirma al diagnosticar.


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
| Ataque: orden falsa (R10)               | Publicar en `upc/gc/<nodo>/cmd`                | Nodo ignora                                       |           |           |
| Regresión final                         | Todos los escenarios anteriores                | Sin regresiones                                   |           |           |


## 7. Ramas y pull requests

| Rama | PR | Revisor | Estado |
| --- | --- | --- | --- |
| `bugfix/pozas-...` | | | |
| `bugfix/perimetro-viento-adc` | | | |
| `bugfix/perimetro-reconexion-y-hora` | | | |
| `bugfix/perimetro-orden-firmada` | | | |
| `bugfix/n4-lavador-pin-rele` | [PR #1](https://github.com/16518-IoT-PrimeFuel/lab4-IoT/pull/1) | Alberto Ponce | Abierto - Pendiente de aprobación |
| `bugfix/n4-lavador-modo-seguro` | [PR #2](https://github.com/16518-IoT-PrimeFuel/lab4-IoT/pull/2) | Alberto Ponce | Abierto - Pendiente de aprobación |

## 8. Evidencia del tablero

- Cierre de la sesión 1: _<captura>_
- Cierre de la sesión 2: _<captura>_

## 9. Exposición

| Bloque       | Quién           | Contenido                                                    | Tiempo           |
| ------------ | --------------- | ------------------------------------------------------------ | ---------------- |
| Apertura     | Integrador      | Estado inicial y resumen de fallas encontradas               | 1,5 min          |
| Fallas       | Cada integrante | La falla más difícil de su nodo: síntoma, causa raíz y prueba | 25 s por persona |
| Demostración | Integrador      | Pico de emisión con viento hacia la comunidad, lavador confirmado y un ataque rechazado | 2,5 min          |
| Preguntas    | Docente         | A cualquier integrante                                       | 2 min            |
