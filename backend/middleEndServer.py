import asyncio
import json
import socket
from colors import *

import websockets

def getData(jsonObject):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect(("192.168.178.107", 65435))
        jsonObject = json.dumps(jsonObject)
        s.sendall(bytes(jsonObject,encoding="utf-8"))
        data = s.recv(1024)
        s.close()
    return data


async def handler(websocket):
    while True:
        try:
            message = await websocket.recv()

        except websockets.ConnectionClosedOK:
            break

        jsonObject = json.loads(message)
        if jsonObject:
            print(f"{Yellow}", "Fetching Data", jsonObject)
            response = getData(jsonObject)
            print(f"{Green}", "Fetching Successfull")
            await websocket.send(response.decode("utf-8"))

def sendResponse(response):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect(("localhost", 8001))
        jsonObject = json.dumps(response)
        s.sendall(bytes(jsonObject,encoding="utf-8"))
        #data = s.recv(1024)
        s.close()


async def main():
    async with websockets.serve(handler, "", 8001):
        await asyncio.Future()  # run forever


if __name__ == "__main__":
    asyncio.run(main())