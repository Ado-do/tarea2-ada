#!/bin/bash

./scripts/medir_memoria.sh
./scripts/medir_tiempo.sh
python ./scripts/graficar_memoria.py
python ./scripts/graficar_tiempo.py
