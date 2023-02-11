import socket
import json
from confidentials import *

HOST = Confidentials.HOST  # The server's hostname or IP address
PORT = Confidentials.PORT  # The port used by the server
m = {"method": "sendData", "timestamp": 1649265197,
     "temperature": 20, "humidity": 50, "relay": 1}
data = json.dumps(m)

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    s.sendall(bytes(data, encoding="utf-8"))
    data = s.recv(1024)
    s.close()
print(f"Received {data!r}")
