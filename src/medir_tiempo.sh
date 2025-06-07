#!/bin/bash

# Define the C++ source files for Edit Distance implementations
archivos=("editDistanceMemo.cpp" "editDistanceDP.cpp" "editDistanceDPOptimized.cpp" "editDistanceRecursive.cpp")

# --- Compilation ---
echo "--- Compilando los programas ---"
for archivo in "${archivos[@]}"; do
    exe="${archivo%.cpp}" # Get executable name without .cpp extension
    echo "Compilando $archivo..."
    g++ -O2 -o "$exe" "$archivo" || { echo "Fallo al compilar $archivo"; exit 1; }
done
echo "Compilación completada."

# --- Text Generation ---
echo "--- Generando textos de prueba ---"
texts=()
texts+=("experimento")
texts+=("problema edit distance")
texts+=("Este es un ejemplo de una frase para el analisis experimental de algoritmos.Se define como el numero minimo de operaciones de insercion, eliminacion o sustitucion de un solo caracter necesarias para cambiar una secuencia por la otra")
texts+=("La distancia de edicion, tambien conocida como distancia de Levenshtein, es una metrica para medir la diferencia entre dos secuencias de caracteres. Se define como el numero minimo de operaciones de insercion, eliminacion o sustitucion de un solo caracter necesarias para cambiar una secuencia por la otra.Se define como el numero minimo de operaciones de insercion, eliminacion o sustitucion de un solo caracter necesarias para cambiar una secuencia por la otraSe define como el numero minimo de operaciones de insercion, eliminacion o sustitucion de un solo caracter necesarias para cambiar una secuencia por la otraSe define como el numero minimo de operaciones de insercion, eliminacion o sustitucion de un solo caracter necesarias para cambiar una secuencia por la otraSe define como el numero minimo de operaciones de insercion, eliminacion o sustitucion de un solo caracter necesarias para cambiar una secuencia por la otraLa distancia de edicion, tambien conocida como distancia de Levenshtein, es una metrica para medir la diferencia entre dos secuencias de caracteres. Se define como el numero minimo de operaciones de insercion, eliminacion o sustitucion de un solo caracter necesarias para cambiar una secuencia por la otra.Se define como el numero minimo de operaciones de insercion, eliminacion o sustitucion de un solo caracter necesarias para cambiar una secuencia por la otraSe define como el numero minimo de operaciones de insercion, eliminacion o sustitucion de un solo caracter necesarias para cambiar una secuencia por la otraSe define como el numero minimo de operaciones de insercion, eliminacion o sustitucion de un solo caracter necesarias para cambiar una secuencia por la otraSe define como el numero minimo de operaciones de insercion, eliminacion o sustitucion de un solo caracter necesarias para cambiar una secuencia por la otra")

echo "Textos de prueba generados:"
for text in "${texts[@]}"; do
    echo "- \"$text\" (Longitud: ${#text})"
done

# --- CSV Output Setup ---
output="resultados_tiempo.csv"
echo "Algoritmo,Texto1,Longitud1,Texto2,Longitud2,Longitud_Producto,Tiempo(s)" > "$output"
echo "Preparando archivo de resultados: $output"

# --- Measurement Function for Time (High Precision) ---
medir_tiempo() {
    local prog_path=$1
    local t1=$2
    local t2=$3
    local len1=${#t1}
    local len2=${#t2}
    local len_prod=$((len1 * len2))

    echo "Ejecutando ${prog_path##*/} con longitudes ${len1} y ${len2} (midiendo tiempo con alta precisión)..."

    if [[ -x "$prog_path" ]]; then
        # **NUEVO MÉTODO DE MEDICIÓN**
        # 1. Capturar el tiempo de inicio con nanosegundos.
        start=$(date +%s.%N)

        # 2. Ejecutar el programa. Su salida se envía a /dev/null para no interferir.
        "$prog_path" <<< "$t1"$'\n'"$t2" > /dev/null

        # 3. Capturar el tiempo de finalización.
        end=$(date +%s.%N)

        # 4. Usar 'bc' (basic calculator) para calcular la diferencia con alta precisión.
        tiempo_s=$(echo "$end - $start" | bc)

        # Escribir el resultado en el CSV, asegurando que los textos estén entrecomillados.
        echo "${prog_path##*/},\"$t1\",$len1,\"$t2\",$len2,$len_prod,$tiempo_s" >> "$output"
    else
        echo "Error: No se puede ejecutar $prog_path."
    fi
}

# --- Loop through algorithms and apply measurement logic ---
echo "--- Iniciando mediciones de tiempo ---"
num_texts=${#texts[@]}

for archivo in "${archivos[@]}"; do
    exe_path="./${archivo%.cpp}"
    
    if [[ "$archivo" == "editDistanceRecursive.cpp" ]]; then
        echo "--- Mediciones especiales para $archivo (es muy lento) ---"
        t1=${texts[0]}
        t2=${texts[1]}
        medir_tiempo "$exe_path" "$t1" "$t2"
        medir_tiempo "$exe_path" "$t2" "$t1"
    else
        echo "--- Iniciando mediciones para $archivo ---"
        for i in $(seq 0 $((num_texts - 1))); do
            for j in $(seq 0 $((num_texts - 1))); do
                if [ $i -ne $j ]; then
                    t1=${texts[$i]}
                    t2=${texts[$j]}
                    medir_tiempo "$exe_path" "$t1" "$t2"
                fi
            done
        done
    fi
done

echo "--- Mediciones de tiempo finalizadas. Resultados guardados en $output ---"
