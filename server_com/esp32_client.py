import socket

# ESP32 AP IP and port
ESP32_IP = '192.168.4.1'  # Default for ESP32 in AP mode
ESP32_PORT = 5000          # Must match WiFiServer port on ESP32

# List of test commands to send
commands = ["forward", "left", "stop", "back", "right"]

def send_command(command):
    try:
        # Create a TCP socket
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((ESP32_IP, ESP32_PORT))
            s.sendall((command + "\n").encode())  # Send command with newline
            # Receive response from ESP32
            response = s.recv(1024).decode().strip()
            print(f"ESP32 response: {response}")
    except ConnectionRefusedError:
        print("Failed to connect. Is the ESP32 AP active and running the server?")
    except Exception as e:
        print("Error:", e)

if __name__ == "__main__":
    for cmd in commands:
        print(f"Sending command: {cmd}")
        send_command(cmd)
