#!/usr/bin/env python3
"""Genera una orden firmada para upc/gc/pozas/cmd (simula al gateway en HiveMQ).

Uso:
  python3 firmar_orden.py VENT:MAX
  python3 firmar_orden.py UMBRAL:1500
  python3 firmar_orden.py VENT:MAX --viejo     # ts de hace 120 s (prueba de antiguedad)

Copia la linea que imprime y publicala en HiveMQ dentro de los 60 s siguientes.
"""
import hashlib
import hmac
import sys
import time

CLAVE = b"costa-norte-gc-6402"

if len(sys.argv) < 2:
    sys.exit(__doc__)

comando = sys.argv[1]
ts = int(time.time()) - (120 if "--viejo" in sys.argv else 0)
firma = hmac.new(CLAVE, f"pozas|{comando}|{ts}".encode(), hashlib.sha256).hexdigest()[:16]
print(f"{comando}|{ts}|{firma}")
