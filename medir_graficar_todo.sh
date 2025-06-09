#!/bin/bash

bash ./scripts/medir_memoria.sh
bash ./scripts/medir_tiempo.sh
python ./scripts/graficar_memoria.py
python ./scripts/graficar_tiempo.py
