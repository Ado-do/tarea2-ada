#!/bin/bash

# Compilar todo
echo "--- Compilando todo: ---"
make all || {
    echo "Error: Compilation failed."
    exit 1
}
echo "Compilación completada."

# Generacion de texto
echo "--- Generando textos de prueba ---"
texts=()
texts+=("experimento")
texts+=("problema edit distance")
texts+=("Este es un ejemplo de una frase para el analisis experimental de algoritmos.Se define como el numero minimo de operaciones de insercion, eliminacion o sustitucion de un solo caracter necesarias para cambiar una secuencia por la otra")
texts+=("Los algoritmos son procedimientos definidos que transforman una entrada en una salida esperada. En el ámbito de la informática, existen muchos tipos de algoritmos aplicados a tareas como ordenamiento, búsqueda, optimización y criptografía. La eficiencia de un algoritmo puede evaluarse a través de su complejidad temporal y espacial. Esta eficiencia es crucial en aplicaciones donde el tiempo de ejecución y el consumo de recursos son limitantes. Por ejemplo, en sistemas embebidos, bases de datos, redes y aplicaciones móviles. Es fundamental conocer múltiples enfoques algorítmicos para seleccionar la mejor estrategia según el problema. Los algoritmos de ordenamiento como quicksort, mergesort y heapsort se utilizan extensamente en bibliotecas estándar. También existen estructuras de datos especializadas que facilitan ciertas operaciones como pilas, colas, árboles binarios, tablas hash, y grafos. La programación dinámica, la recursión y la técnica divide y vencerás son paradigmas clásicos que ayudan a resolver problemas complejos de manera eficiente. Además, la inteligencia artificial y el aprendizaje automático han impulsado el desarrollo de nuevos algoritmos capaces de aprender de los datos. El diseño algorítmico es una habilidad clave para cualquier profesional del software, y su estudio continuo garantiza soluciones óptimas ante los desafíos computacionales modernos. Los algoritmos son procedimientos definidos que transforman una entrada en una salida esperada. En el ámbito de la informática, existen muchos tipos de algoritmos aplicados a tareas como ordenamiento, búsqueda, optimización y criptografía. La eficiencia de un algoritmo puede evaluarse a través de su complejidad temporal y espacial. Esta eficiencia es crucial en aplicaciones donde el tiempo de ejecución y el consumo de recursos son limitantes. Por ejemplo, en sistemas")

echo "Textos de prueba generados:"
for text in "${texts[@]}"; do
    echo "- \"$text\" (Longitud: ${#text})"
done

# Archivo CSV de salida
output="build/resultados_memoria.csv"
echo "Algoritmo,Texto1,Longitud1,Texto2,Longitud2,Longitud_Producto,Memoria(KB)" > "$output"
echo "Preparando archivo de resultados: $output"

# Medir memoria
medir_memoria() {
    local prog_path=$1
    local t1=$2
    local t2=$3
    local len1=${#t1}
    local len2=${#t2}
    local len_prod=$((len1 * len2))

    echo "Ejecutando $(basename "$prog_path") con longitudes ${len1} y ${len2} (midiendo memoria)..."

    if [[ -x "$prog_path" ]]; then
        memoria_kb=$({ /usr/bin/time -f "%M" "$prog_path" <<< "$t1"$'\n'"$t2" 1>/dev/null; } 2>&1)
        echo "$(basename "$prog_path"),\"$t1\",$len1,\"$t2\",$len2,$len_prod,$memoria_kb" >> "$output"
    else
        echo "Error: No se puede ejecutar $prog_path."
    fi
}

# Recorrer algoritmos y aplicar logica de medicion
archivos=("build/editDistanceMemo" "build/editDistanceDP" "build/editDistanceDPOptimized" "build/editDistanceRecursive")

echo "--- Iniciando mediciones de memoria ---"
num_texts=${#texts[@]}

for archivo in "${archivos[@]}"; do
    if [[ "$(basename "$archivo")" == "editDistanceRecursive" ]]; then
        echo "--- Mediciones especiales para $archivo ---"
        t1=${texts[0]}
        t2=${texts[1]}
        medir_memoria "$archivo" "$t1" "$t2"
        medir_memoria "$archivo" "$t2" "$t1"
    else
        echo "--- Iniciando mediciones para $archivo ---"
        for i in $(seq 0 $((num_texts - 1))); do
            for j in $(seq 0 $((num_texts - 1))); do
                if [ "$i" -ne "$j" ]; then
                    t1=${texts[$i]}
                    t2=${texts[$j]}
                    medir_memoria "$archivo" "$t1" "$t2"
                fi
            done
        done
    fi
done

echo "--- Mediciones de memoria finalizadas. Resultados guardados en $output ---"
