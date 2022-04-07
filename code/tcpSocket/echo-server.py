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

def insertIntoTable(timestamp, temperature, humidity, tablename):
    print(f"{BYellow} -> Trying to insert following data into table",tablename, "\n")
    sql = f"""INSERT INTO {tablename}(timestamp, temperature, humidity) 
                             VALUES 
                             (%s,%s,%s)"""

    """ convert seconds into unix timestamp"""
    value = datetime.datetime.fromtimestamp(timestamp)
    data = [[value, temperature, humidity]]
    print(f"{Color_Off}",tabulate(data, headers=["timestamp", "temperature", "humidity"]), "\n")

    val = (value, temperature, humidity)

    cursor.execute(sql, val)
    connection.commit()
    print(f"{BGreen} -> Record inserted successfully into ", tablename)
    cursor.close()

def retrieveData(tablename):
    print(f"{Color_Off}-> reading table ", tablename)
    sql = f"""SELECT * FROM {tablename}"""
    cursor.execute(sql)
    myresult = cursor.fetchall()
    print(myresult)
    """for x in myresult:
        print(x)
    cursor.close()"""

def waitingfordata():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        print("Searching for Connections")
        s.bind((HOST, PORT))
        s.listen()
        conn, addr = s.accept()
        with conn:
            print(f"Connected by {addr} \n")

            while True:
                data = conn.recv(1024)
                some = json.loads(data.decode("utf-8"))
                try:
                    insertIntoTable(some['timestamp'], some['temperature'], some['humidity'], "sampleData")
                except:
                    e = sys.exc_info()[0]
                    print(e)
                finally:
                    retrieveData("sampleData")
                    s.close()
                #conn.sendall(data)
                #conn.sendmsg("Test")
                #s.sendall('Test, Test')

try:
    waitingfordata()

except mysql.connector.Error as error:
    print(f"{BRed}","Some Error ".format(error))

finally:
    if connection.is_connected():
        connection.close()
        print(f"{BRed}","MySQL connection is closed")


"""Unused by now"""
