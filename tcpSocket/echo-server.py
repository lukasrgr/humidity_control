# echo-server.py

import socket
import json
import sys

import mysql.connector
import datetime
from tabulate import tabulate

from colors import *

HOST = "192.168.178.29"  # Standard loopback interface address (localhost)
PORT = 65435  # Port to listen on (non-privileged ports are > 1023)

connection = mysql.connector.connect(host='192.168.178.107',
                                     database='humidity',
                                     user='test1',
                                     password='test1')
cursor = connection.cursor()


def insertIntoTable(timestamp, temperature, humidity, relay, tablename):
    print(f"{BYellow} -> Trying to insert following data into table", tablename, "\n")
    sql = f"""INSERT INTO {tablename}(timestamp, temperature, humidity, relay) 
                             VALUES 
                             (%s,%s,%s,%s)"""

    """ convert seconds into unix timestamp"""
    value = datetime.datetime.fromtimestamp(timestamp)
    data = [[value, temperature, humidity, relay]]
    print(f"{Color_Off}", tabulate(data, headers=["timestamp", "temperature", "humidity", "relay"]), "\n")

    val = (value, temperature, humidity, relay)

    cursor.execute(sql, val)
    connection.commit()
    print(f"{BGreen} -> Record inserted successfully into", tablename)


def retrieveData(tablename):
    print(f"{BYellow} -> reading table", tablename)
    sql = f"""SELECT timestamp, humidity, temperature, relay FROM {tablename}"""
    cursor.execute(sql)
    myresult = cursor.fetchall()
    return myresult


def convertReceivedDataIntoObjectStructure(data):
    data_set = {"timestamp": [], "humidity": [],"temperature": [],"relay": []}
    for i in data:
        data_set['timestamp'].append(i[0])
        data_set['humidity'].append(i[1])
        data_set['temperature'].append(i[2])
        data_set['relay'].append(i[3])
    print(f"{BGreen} -> finished converting data parsing")
    return json.dumps(data_set)


def waitingfordata():
    print("Searching for Connections")
    while True:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.bind((HOST, PORT))
            s.listen()
            conn, addr = s.accept()
            with conn:
                print(f"Connected by {addr} \n")
                dataReceived = False
                while not dataReceived:
                    data = conn.recv(1024)
                    if data != b'':
                        some = json.loads(data.decode("utf-8"))
                        print(f"test", some)
                        if some['method'] == 'receiveData':
                            try:
                                retrievedData = retrieveData("sampleData")
                                object = convertReceivedDataIntoObjectStructure(retrievedData)
                                print(f"object ", object)
                            except:
                                print(error)
                            finally:
                                #s.send(bytes(object,encoding="utf-8"))
                                #s.sendto()
                                dataReceived = True
                        elif some['method'] == 'sendData':
                            try:
                                insertIntoTable(some['timestamp'], some['temperature'], some['humidity'], some['relay'],
                                                "sampleData")
                            except:
                                print(error)
                            finally:
                                s.close()
                            dataReceived = True


try:
    while True:
        waitingfordata()
except mysql.connector.Error as error:
    print(f"{BRed}", "Some Error ", error)

finally:
    """if connection.is_connected():
        connection.close()
        print(f"{BRed}","MySQL connection is closed")"""

"""Unused by now"""
