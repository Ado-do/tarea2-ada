import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

def graficar_tiempo():
    """
    Genera una gráfica de barras a partir de los resultados de tiempo
    y la guarda como un archivo de imagen.
    """
    try:
        # Cargar los datos desde el archivo CSV
        df = pd.read_csv("resultados_tiempo.csv")
    except FileNotFoundError:
        print("Error: El archivo 'resultados_tiempo.csv' no fue encontrado.")
        print("Asegúrate de ejecutar primero el script 'medir_tiempo.sh'.")
        return

    # Asegurarse de que los datos son numéricos para poder graficar
    df['Tiempo(s)'] = pd.to_numeric(df['Tiempo(s)'], errors='coerce')
    df = df.dropna(subset=['Tiempo(s)'])

    # Crear una etiqueta más descriptiva para el eje X para identificar cada prueba
    df['Etiqueta_Prueba'] = df.apply(
        lambda row: f"L{row['Longitud1']} vs L{row['Longitud2']}", axis=1
    )

    # Ordenar los datos por el producto de las longitudes para una mejor visualización
    # Y también por la longitud de los textos para que L3 vs L36 sea diferente de L36 vs L3
    df['Longitud_Producto_Orden'] = df['Longitud1'] * df['Longitud2']
    df = df.sort_values(by=['Longitud_Producto_Orden', 'Longitud1', 'Longitud2'])

    # Definir el orden deseado para los algoritmos
    # Queremos que 'editDistanceRecursive' sea el último
    # Asegúrate de que todos los nombres de tus algoritmos estén aquí
    algorithm_order = [
        'editDistanceMemo',
        'editDistanceDP',
        'editDistanceDPOptimized',
        'editDistanceRecursive'
    ]

    plt.style.use('seaborn-v0_8-whitegrid')
    plt.figure(figsize=(16, 9))

    # Crear el gráfico de barras con Seaborn
    ax = sns.barplot(
        data=df,
        x='Etiqueta_Prueba',
        y='Tiempo(s)',
        hue='Algoritmo',
        palette='viridis',
        hue_order=algorithm_order # <--- AQUI SE ESPECIFICA EL ORDEN
    )

    # --- Usar escala logarítmica para el eje Y ---
    # Esencial para poder visualizar las enormes diferencias de rendimiento.
    ax.set_yscale("log")

    # Añadir títulos y etiquetas para mayor claridad
    ax.set_title('Comparación de Tiempo de Ejecución de Algoritmos ', fontsize=20, pad=20)
    ax.set_xlabel('Comparación de Textos (Longitud1 vs Longitud2)', fontsize=14, labelpad=15)
    ax.set_ylabel('Tiempo de Ejecución en Segundos (Escala Logarítmica)', fontsize=14, labelpad=15)

    # Mejorar la legibilidad
    plt.xticks(rotation=45, ha='right')
    plt.legend(title='Algoritmo', fontsize=12)
    plt.tight_layout()

    # Guardar la gráfica en un archivo
    nombre_archivo = "grafico_tiempo.png"
    plt.savefig(nombre_archivo)
    print(f"Gráfica de tiempo guardada como '{nombre_archivo}'")
    # plt.show() # Descomentar si deseas ver la gráfica al ejecutar el script

if __name__ == '__main__':
    graficar_tiempo()
