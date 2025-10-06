import matplotlib.pyplot as plt
import numpy as np

# Tamanhos dos arrays
tamanhos = [100, 1000, 10000]

# Tempos em nanosegundos para cada pivô e cenário
tempos = {
    "First Pivot": {
        "Quase ordenado": [31521, 181826, 394483],
        "Ordenado": [17762, 940927, 36716711],  # 36ms = 36000000ns + 316711ns
        "Aleatório": [59521, 231725, 1112529]   # 1ms = 1000000ns + 112529ns
    },
    "Last Pivot": {
        "Quase ordenado": [20007, 234615, 552681],
        "Ordenado": [15833, 1488154, 3671558],  # 36ms = 36000000ns + 671558ns
        "Aleatório": [75631, 469012, 1142430]   # 1ms = 1000000ns + 142430ns
    },
    "Random Pivot": {
        "Quase ordenado": [18721, 204590, 811269],
        "Ordenado": [6065, 67613, 695938],
        "Aleatório": [14191, 191607, 1687454]   # 1ms = 1000000ns + 687454ns
    },
    "Median Pivot": {
        "Quase ordenado": [25076, 297388, 569184],
        "Ordenado": [2980, 28790, 353080],
        "Aleatório": [9234, 146032, 1411957]    # 1ms = 1000000ns + 411957ns
    }
}

cenarios = ["Quase ordenado", "Ordenado", "Aleatório"]
cores = ["r", "g", "b"]  # cores diferentes para cada cenário

plt.figure(figsize=(12, 6))
for idx, (pivo, dados) in enumerate(tempos.items()):
    for c, cenario in enumerate(cenarios):
        plt.plot(tamanhos, dados[cenario], marker='o', color=cores[c],
                 linestyle='--', label=f"{pivo} - {cenario}" if idx == 0 else "")

plt.xscale('log')
plt.yscale('log')
plt.xlabel("Tamanho do Array")
plt.ylabel("Tempo (ns)")
plt.title("Desempenho dos Algoritmos Quicksort com Diferentes Estratégias de Pivô")
plt.legend()
plt.grid(True, which="both", ls="--", lw=0.5)
plt.show()
