import serial
import time

# serielle Verbindung herstellen
port = serial.Serial('COM3', 9600)  

time.sleep(2)  # warten bis diese hergestellt ist

# aktuelle Uhrzeit holen
current_time = time.strftime('%H:%M')

# Uhrzeit an den Arduino senden
port.write((current_time + '\n').encode('utf-8'))
port.close()



