import socket
import json

HOST = "192.168.178.29"  # The server's hostname or IP address
PORT = 65435  # The port used by the server
m = {"method": "receiveData"}
data = json.dumps(m)

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    #s.sendall(json.loads('{"timestamp":1649265197, "temperature": 20, "humidity": 50}'))
    s.sendall(bytes(data,encoding="utf-8"))
    data = s.recv(1024)
    s.close()
print(f"Received {data!r}")