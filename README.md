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

| N.º y nodo        | Tipo       | Paso del marco (12 pasos) | Síntoma | Causa raíz | Corrección (commit) | Prueba | Responsable / Revisor |
| ----------------- | ---------- | ------------------------- | ------- | ---------- | ------------------- | ------ | --------------------- |
| F1 - N1 Pozas | Visible | Paso 8: sensores y actuadores | Con el DS18B20 a 22 °C la consola y HiveMQ muestran `"temp":71.6`. | `sensor.getTempFByIndex(0)` devuelve grados Fahrenheit; R1 define el umbral en 35 °C. | `getTempCByIndex(0)`. Commit `64a9c7f` (rama `bugfix/pozas-temp-celsius`). | Con 22 °C: antes `71.6`, después `22.0` en consola y HiveMQ. Evidencias: `evidencia/n1-pozas/f1-antes.png`, `f1-despues.png`. | Jefferson Castro / Samuel Bonifacio |
| F2 - N1 Pozas | Silenciosa | Paso 10: procesamiento por nodo | Con 40 °C y gas bajo el umbral las pozas no ventilan. Sin broker el nodo deja de leer sensores y de accionar el relé (incumple R2). | El `else` de la condición de gas sobrescribe la de temperatura, y `conectar()` bloquea el `loop()` con `while` sin salida. Además publicaba sin validar la hora NTP. | `ventilar = gas>umbral \|\| temp>35 \|\| ventMax`, reconexión sin bloqueo cada 5 s y no se publica sin broker ni hora válida. Commit `10e8807` (rama `bugfix/pozas-accion-local`). | 40 °C con gas bajo el umbral: antes `OFF`, después `ON`. Broker inválido: antes la consola queda congelada (57 s sin lecturas), después lee y ventila cada 2 s y muestra `Sin broker u hora valida: no se publica`. Evidencias: `f2-antes-temp.png`, `f2-despues-temp.png`, `f2-antes-broker.png`, `f2-despues-broker.png`. | Jefferson Castro / Samuel Bonifacio |
| F3 - N1 Pozas | Seguridad | Paso 4: capa de intercambio | Cualquiera que publique `UMBRAL:9000` en `upc/gc/pozas/cmd` cambia el umbral y apaga la ventilación (R10). | `alRecibir()` acepta `UMBRAL:` y `VENT:` sin firma, antigüedad ni rango. | Formato `<comando>\|<ts>\|<firma>` con HMAC de `pozas\|comando\|ts`, menos de 60 s y umbral entre 500 y 5000; rechazos publicados en `upc/gc/pozas/alerta`. Herramienta `nodos/n1-pozas/firmar_orden.py`. Commit `864a28c` (rama `bugfix/pozas-orden-firmada`). | Antes: `UMBRAL:9000` sin firma se acepta. Después: `UMBRAL:99999` da `Orden rechazada: formato`, una orden firmada vencida da `Orden rechazada: firma invalida o vencida` y `UMBRAL:5000` firmado se acepta. Evidencias: `f3-ataque-antes.png`, `f3-ataque-despues.png`, `f3-vencida-despues.png`, `f3-firmada-despues.png`. | Jefferson Castro / Samuel Bonifacio |
| F4 - N1 Pozas | Cruzada | Paso 4: capa de intercambio (contrato de interfaz) | HiveMQ recibe datos de pozas, pero el gateway no puede usar el valor (el síntoma aparece en N5). | N1 publica `"valor":"8859.6ppm"` (texto con unidad) y firma esa cadena; el contrato exige `valor` numérico y firma sobre `id\|ts\|valor`. | `"valor":<número>` y firma sobre `pozas\|ts\|<número>`. Commit `3abbf5f` (rama `bugfix/pozas-valor-numerico`). | HiveMQ: antes `"valor":"8859.6ppm"`, después `"valor":8859.6`; la firma publicada `e245434e7f030ec9` coincide con HMAC(`pozas\|1795653319\|8859.6`). Pendiente confirmar en el gateway (N5). Evidencias: `f4-antes.png`, `f4-despues.png`. | Jefferson Castro (síntoma en N5) / Samuel Bonifacio |
| F1 - N2 Secadores | Visible    |                           |         |            |                     |        |                       |
| F2 - N2 Secadores | Silenciosa |                           |         |            |                     |        |                       |
| F3 - N2 Secadores | Seguridad  |                           |         |            |                     |        |                       |
| F4 - N2 Secadores | Cruzada    |                           |         |            |                     |        |                       |
| F1 - N3 Perímetro | Visible    | Paso 8: sensores y actuadores | El viento se calcula mal: con el potenciómetro en [posición] la consola muestra `viento=[valor antes]` en vez de [valor esperado], y el LED de riesgo no responde bien al rango 90°–180°. | `PIN_VIENTO=25` es un pin ADC2 (no usable con WiFi encendido) y `map(…, 0, 1023, 0, 360)` ignora que el ADC del ESP32 es de 12 bits (0–4095). | Pin 34 (ADC1) y `map(…, 0, 4095, 0, 359)`; cable `viento:SIG` a `esp:34`. Commit `[hash]`. | Con el gas alto y el potenciómetro en 0 %, 25 %, 50 %, 75 % y 100 % la consola muestra [0, ~90, ~180, ~269, 359]; el LED enciende solo con viento entre 90° y 180°. | Alberto Ponce / Katherine Mejia |
| F2 - N3 Perímetro | Silenciosa | Paso 10: procesamiento por nodo | Si el broker o el WiFi no están disponibles, el nodo se queda atrapado en `conectar()` y deja de leer el gas y de accionar el LED. Si no hay hora NTP, publica con `ts` cercano a 1970 y el gateway lo rechaza sin avisar. | `conectar()` bloquea el `loop()` con un `while` sin salida y no se valida la hora antes de publicar. | Reconexión sin bloqueo cada 5 s, el LED sigue funcionando y no se publica sin hora válida. Commit `[hash]`. | Con un broker inválido temporal: antes el LED nunca responde; después el LED responde y la consola imprime `Sin broker u hora valida: no se publica`. | Alberto Ponce / Katherine Mejia |
| F3 - N3 Perímetro | Seguridad  | Paso 4: capa de intercambio | Cualquiera que publique `OFFSET:-10000` en `upc/gc/perimetro/cmd` cambia la calibración y el gas se lee como 0, así que el nodo queda ciego (R10). | El callback acepta `OFFSET:` sin comprobar firma, antigüedad ni rango. | La orden debe ser `OFFSET:<valor>:<ts>:<firma>`, firmada, de menos de 60 s y con valor absoluto de hasta 500. Commit `[hash]`. | Desde HiveMQ se publica `OFFSET:-10000`: antes la consola muestra `Nueva calibracion: -10000.00`; después muestra `Orden rechazada: formato`. | Alberto Ponce / Katherine Mejia |
| F4 - N3 Perímetro | Cruzada    | Paso 4: capa de intercambio (contrato de tópicos) | Los datos de N3 salen a `upc/gc/perimetro/datos` pero el gateway nunca imprime `OK perimetro`. | El gateway se suscribe a `upc/gc/+/dato` (sin "s"), distinto del contrato `datos`. | En N5: `mqtt.subscribe("upc/gc/+/datos")`. Commit `[hash]` en la rama del gateway. | Antes: HiveMQ muestra los datos y el gateway no responde. Después: el gateway imprime `OK perimetro: [valor] ppm` cada 2 s. | Alberto Ponce (síntoma) / corrige N5 (Joseph) |
| F1 - N4 Lavador   | Visible    |                           |         |            |                     |        |                       |
| F2 - N4 Lavador   | Silenciosa |                           |         |            |                     |        |                       |
| F3 - N4 Lavador   | Seguridad  |                           |         |            |                     |        |                       |
| F4 - N4 Lavador   | Cruzada    |                           |         |            |                     |        |                       |
| F1 - N5 Gateway   | Visible    |                           |         |            |                     |        |                       |
| F2 - N5 Gateway   | Silenciosa |                           |         |            |                     |        |                       |
| F3 - N5 Gateway   | Seguridad  |                           |         |            |                     |        |                       |
| F4 - N5 Gateway   | Cruzada    |                           |         |            |                     |        |                       |

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

| Rama               | PR   | Revisor | Estado |
| ------------------ | ---- | ------- | ------ |
| `bugfix/pozas-temp-celsius` |      | Samuel Bonifacio | Pendiente |
| `bugfix/pozas-accion-local` |      | Samuel Bonifacio | Pendiente |
| `bugfix/pozas-orden-firmada` |      | Samuel Bonifacio | Pendiente |
| `bugfix/pozas-valor-numerico` |      | Samuel Bonifacio | Pendiente |
| `bugfix/perimetro-viento-adc` |      |         |        |
| `bugfix/perimetro-reconexion-y-hora` |      |         |        |
| `bugfix/perimetro-orden-firmada` |      |         |        |

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
