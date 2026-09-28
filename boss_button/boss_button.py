import serial
import webbrowser
import os
import time

# Ensure GUI apps know which screen to open on in Linux / VMs
os.environ["DISPLAY"] = ":0"

SERIAL_PORT = '/dev/ttyACM0'  # Change to /dev/ttyUSB0 if needed
BAUD_RATE = 9600
TARGET_URL = 'https://www.youtube.com/'

print(f"Connecting to {SERIAL_PORT}...")

try:
    sp = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=0.5)
    print("SUCCESS! Connected.")
    print("Press your AVR button now (Press Ctrl+C to stop)...\n")
except Exception as e:
    print(f"Error opening port: {e}")
    print("Tip: Check if port is /dev/ttyUSB0 instead of /dev/ttyACM0")
    exit(1)

while True:
    try:
        # Check if any bytes have arrived from the AVR
        if sp.in_waiting > 0:
            raw_bytes = sp.read(sp.in_waiting)
            print(f"[RECEIVED DATA]: {raw_bytes}")
            
            print("--> TRIGGER MATCHED! Opening browser...")
            webbrowser.open(TARGET_URL)
            
            # Flush remaining buffer & pause 2 seconds to avoid opening 20 tabs
            sp.reset_input_buffer()
            time.sleep(2)

    except KeyboardInterrupt:
        print("\nStopping listener.")
        break
    except Exception as e:
        print(f"Loop error: {e}")
        time.sleep(1)