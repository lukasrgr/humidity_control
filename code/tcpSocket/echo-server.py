# echo-server.py

import socket
import json
import mysql.connector
import datetime

HOST = "192.168.178.29"  # Standard loopback interface address (localhost)
PORT = 65432  # Port to listen on (non-privileged ports are > 1023)

connection = mysql.connector.connect(host='192.168.178.107',
                                         database='humidity',
                                         user='test1',
                                         password='test1')

def insertIntoTable(timestamp, temperature, humidity, tablename):
    print("Trying to insert into Table",tablename)
    sql = f"""INSERT INTO {tablename}(timestamp, temperature, humidity) 
                             VALUES 
                             (%s,%s,%s)"""

    """ convert seconds into unix timestamp"""
    value = datetime.datetime.fromtimestamp(timestamp)
    print(value.strftime('%Y-%m-%d %H:%M:%S'))

    val = (value, temperature, humidity)

    cursor = connection.cursor()
    cursor.execute(sql, val)
    connection.commit()
    print(cursor.rowcount, "Record inserted successfully into ", tablename)
    cursor.close()

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
                print(f'Retrieved: {data}')
                print("test",some['timestamp'], some['temperature'], some['humidity'])
                try:
                    parsedjson = json.loads(data.decode("utf-8"))
                    insertIntoTable(some['timestamp'], some['temperature'], some['humidity'], "sampleData")
                except:
                    #e = sys.exc_info()[0]
                    print()
                finally:
                    s.close()
                #conn.sendall(json.dumps(data, indent=2).encode('utf-8'))


try:
    waitingfordata()

except mysql.connector.Error as error:
    print(f"Failed to insert record into table ".format(error))

finally:
    if connection.is_connected():
        connection.close()
        print("MySQL connection is closed")