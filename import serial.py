import serial
import matplotlib.pyplot as plt
import numpy as np

ser = serial.Serial('COM7', 115200)

data = []
labels = []

plt.ion()

def detect_material(freq):
    if freq > 17:
        return "metal"
    elif freq > 12:
        return "pierre"
    elif freq > 8:
        return "bois"
    else:
        return "terre"

while True:
    line = ser.readline().decode(errors='ignore').strip()

    if line:
        try:
            name, val = line.split(",")
            val = float(val)

            data.append(val)
            labels.append(name)

            data = data[-100:]
            labels = labels[-100:]

            if len(data) > 50:
                # FFT
                fft = np.abs(np.fft.rfft(data))
                freqs = np.fft.rfftfreq(len(data), d=0.01)

                dominant_freq = freqs[np.argmax(fft)]

                predicted = detect_material(dominant_freq)
                real = labels[-1]

                plt.clf()

                # Signal
                plt.subplot(2,1,1)
                plt.plot(data)
                plt.title(f"Signal | Réel: {real} | Détecté: {predicted}")

                # FFT
                plt.subplot(2,1,2)
                plt.plot(freqs, fft)
                plt.title(f"Fréquence dominante: {dominant_freq:.2f} Hz")

                plt.pause(0.01)

        except:
            pass