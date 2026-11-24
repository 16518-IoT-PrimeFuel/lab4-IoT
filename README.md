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
| F1 - N1 Pozas     | Visible    |                           |         |            |                     |        |                       |
| F2 - N1 Pozas     | Silenciosa |                           |         |            |                     |        |                       |
| F3 - N1 Pozas     | Seguridad  |                           |         |            |                     |        |                       |
| F4 - N1 Pozas     | Cruzada    |                           |         |            |                     |        |                       |
| F1 - N2 Secadores | Visible    |                           |         |            |                     |        |                       |
| F2 - N2 Secadores | Silenciosa |                           |         |            |                     |        |                       |
| F3 - N2 Secadores | Seguridad  |                           |         |            |                     |        |                       |
| F4 - N2 Secadores | Cruzada    |                           |         |            |                     |        |                       |
| F1 - N3 Perímetro | Visible    |                           |         |            |                     |        |                       |
| F2 - N3 Perímetro | Silenciosa |                           |         |            |                     |        |                       |
| F3 - N3 Perímetro | Seguridad  |                           |         |            |                     |        |                       |
| F4 - N3 Perímetro | Cruzada    |                           |         |            |                     |        |                       |
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
| `bugfix/pozas-...` |      |         |        |

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
