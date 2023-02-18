# echo-server.py

import socket
import json
import time
import mysql.connector
import datetime
from tabulate import tabulate

from colors import *
from confidentials import *

HOST = Confidentials.HOST  # Standard loopback interface address (localhost)
# Port to listen on (non-privileged ports are > 1023)
PORT = Confidentials.PORT

# Establishing Database Connection
connection = mysql.connector.connect(host=HOST,
                                     database=Confidentials.DATABASE_NAME,
                                     user=Confidentials.DATABASE_USERNAME,
                                     password=Confidentials.DATABASE_PW)
cursor = connection.cursor()


def insertIntoTable(timestamp, temperature=0, humidity=0, relay=0, tablename=""):

    if tablename == 'sampleData':
        sql = f"""INSERT INTO {tablename}(timestamp, temperature, humidity, relay) 
                             VALUES 
                             (%s,%s,%s,%s)"""

        """ convert seconds into unix timestamp"""
        value = datetime.datetime.fromtimestamp(timestamp)
        data = [[value, temperature, humidity, relay]]
        print(f"{Color_Off}", tabulate(data, headers=[
              "timestamp", "temperature", "humidity", "relay"]), "\n")

        val = (value, temperature, humidity, relay)

        cursor.execute(sql, val)
        connection.commit()
        print(f"{BGreen} -> Record inserted successfully into", tablename)
    elif tablename == 'relayData':
        sql = f"""INSERT INTO {tablename}(timestamp, relay)
                                VALUES
                                (%s,%s)"""
        value = datetime.datetime.fromtimestamp(timestamp)
        data = [[value, relay]]

        val = (value, relay)

        cursor.execute(sql, val)
        connection.commit()
        print(f"{BGreen} -> Record inserted", tablename)


def retrieveLastData(tablename, columns):
    sql_columns = ','.join(columns)
    sql = f"""SELECT {sql_columns} FROM {tablename} ORDER BY timestamp DESC LIMIT 1"""
    cursor.execute(sql)
    myresult = cursor.fetchall()
    return myresult


def retrieveData(tablename, fromDate, toDate, columns):
    print(f"{BYellow} -> reading table", tablename)
    sql_columns = ','.join(columns)
    sql = f"""SELECT {sql_columns} FROM {tablename} WHERE timestamp >= '{fromDate}' AND timestamp <= '{toDate}'"""
    cursor.execute(sql)
    myresult = cursor.fetchall()
    return myresult

# TODO: create generic Converter


def convertLatestDataIntoObjectStructure(data):
    data_set = {"timestamp": [], "relay": []}
    for i in data:
        data_set['timestamp'].append(i[0])
        data_set['relay'].append(i[1])
    print(f"{BGreen} -> finished converting data parsing")
    return json.dumps(data_set)


def convertCurrentTemperatureIntoObjectStructure(data):
    data_set = {"timestamp": [], "temperature": []}
    for i in data:
        data_set['timestamp'].append(i[0])
        data_set['temperature'].append(i[1])
    print(f"{BGreen} -> finished converting data parsing")
    return json.dumps(data_set)


def convertReceivedDataIntoObjectStructure(data):
    data_set = {"timestamp": [], "humidity": [],
                "temperature": [], "relay": []}
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
            s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            s.bind((HOST, PORT))
            s.listen()
            conn, addr = s.accept()
            with conn:
                #print(f"Connected by {addr} \n")
                dataReceived = False
                while not dataReceived:
                    data = conn.recv(1024)
                    if data != b'':
                        print(f"data", data)
                        request = json.loads(data.decode("utf-8"))
                        if request['method'] == 'getLatestData':
                            try:
                                retrievedData = retrieveLastData(
                                    "sampleData", ["timestamp", "humidity", "temperature", "relay"])
                                object = convertReceivedDataIntoObjectStructure(
                                    retrievedData)
                            except:
                                print(error)
                            finally:
                                conn.sendall(object.encode())
                                dataReceived = True
                        elif request['method'] == 'queryHistoricData':
                            try:
                                if request['params']:
                                    retrievedData = retrieveData("sampleData", request['params']["fromDate"], request['params']["toDate"], [
                                                                 "timestamp", "humidity", "temperature", "relay"])
                                    object = convertReceivedDataIntoObjectStructure(
                                        retrievedData)
                            finally:
                                conn.sendall(object.encode())
                                dataReceived = True
                        elif request['method'] == 'sendGeneralData':
                            try:
                                insertIntoTable(
                                    request['timestamp'], request['temperature'], request['humidity'], request['relay'], "sampleData")
                            except:
                                print(error)
                            finally:
                                s.close()
                                conn.close()
                                dataReceived = True
                        elif request['method'] == 'sendRelayData':
                            try:
                                insertIntoTable(
                                    request['timestamp'], 0, 0, request['relay'], "relayData")
                            except:
                                print(error)
                            finally:
                                s.close()
                                conn.close()
                                dataReceived = True


try:
    while True:
        waitingfordata()
        time.sleep(10)
except mysql.connector.Error as error:
    print(f"{BRed}", "Error ", error)
