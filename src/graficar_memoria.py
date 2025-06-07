import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

def graficar_memoria():
    """
    Genera una gráfica de barras a partir de los resultados de memoria
    y la guarda como un archivo de imagen.
    """
    try:
        # Cargar los datos desde el archivo CSV
        df = pd.read_csv("resultados_memoria.csv")
    except FileNotFoundError:
        print("Error: El archivo 'resultados_memoria.csv' no fue encontrado.")
        print("Asegúrate de ejecutar primero el script 'medir_memoria.sh'.")
        return

    # Asegurarse de que los datos son numéricos para poder graficar
    df['Memoria(KB)'] = pd.to_numeric(df['Memoria(KB)'], errors='coerce')
    df = df.dropna(subset=['Memoria(KB)'])
    
    # Crear una etiqueta más descriptiva para el eje X para identificar cada prueba
    df['Etiqueta_Prueba'] = df.apply(
        lambda row: f"L{row['Longitud1']} vs L{row['Longitud2']}", axis=1
    )

    # Ordenar los datos por el producto de las longitudes para una mejor visualización
    df = df.sort_values(by='Longitud_Producto')

    plt.style.use('seaborn-v0_8-whitegrid')
    plt.figure(figsize=(16, 9))

    # Crear el gráfico de barras con Seaborn
    ax = sns.barplot(
        data=df,
        x='Etiqueta_Prueba',
        y='Memoria(KB)',
        hue='Algoritmo',
        palette='plasma'
    )

    # Añadir títulos y etiquetas para mayor claridad
    ax.set_title('Comparación de Uso de Memoria de Algoritmos ', fontsize=20, pad=20)
    ax.set_xlabel('Comparación de Textos (Longitud1 vs Longitud2)', fontsize=14, labelpad=15)
    ax.set_ylabel('Uso Máximo de Memoria (en Kilobytes)', fontsize=14, labelpad=15)

    # Mejorar la legibilidad
    plt.xticks(rotation=45, ha='right')
    plt.legend(title='Algoritmo', fontsize=12, bbox_to_anchor=(1.0, 1.05), loc='upper left')
    plt.tight_layout()

    # Guardar la gráfica en un archivo
    nombre_archivo = "grafico_memoria.png"
    plt.savefig(nombre_archivo)
    print(f"Gráfica de memoria guardada como '{nombre_archivo}'")
    # plt.show() # Descomentar si deseas ver la gráfica al ejecutar el script


if __name__ == '__main__':
    graficar_memoria()
