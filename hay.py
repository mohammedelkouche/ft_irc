import os
import sys
# TMP='''PASS 1234\r\nNICK nick{0}\r\nUSER user{0} 0 * abc \r\n'''


# for clinet in range(int(sys.argv[1])):
#     cmd = TMP.format(clinet)
#     filename = "files/infile{0}".format(clinet)
#     with open(filename, "w") as fp:
#         fp.write(cmd)
#     os.system("nc 127.0.0.1 8888 < '" + filename + "'")


# -------------------------------

#-------------------------------
# TMP='''PASS h\r\nNICK nick{0}\r\nUSER user{0} 0 * abc\r\nJOIN #channel{0}\r\nPART #channel{0}\r\n'''
# # TMP='''PASS h\r\nNICK nick{0}\r\nUSER user{0} 0 * abc\r\nJOIN #channel{0}\r\nPART #channel{0}\r\n'''

# for clinet in range(int(sys.argv[1])):
#     cmd = TMP.format(clinet)
#     filename = "files/infile{0}".format(clinet)
#     with open(filename, "w") as fp:
#         fp.write(cmd)
#     os.system("nc -c 127.0.0.1 8080 < '" + filename + "'")

#-------*************-----------

import socket
import sys
import threading

# Server address and port
server_address = 'localhost'
server_port = 8080

# Initial lines to send
initial_lines = [
    'pass h\r\n',
    # 'nick ouss\r\n',
    'nick aygaoua\r\n',
    'user r r r r\r\n',
    'join #cc\r\n',
    # 'privmsg bot start\r\n'
    # 'privmsg :bot Nwetat\r\n'
    # 'join #cc key,popo\r\n',
    # 'mode #cc +k key\r\n'
]

def receive_from_server(sock):
    while True:
        try:
            data = sock.recv(4096)
            if data:
                sys.stdout.write(data.decode('utf-8'))
                sys.stdout.flush()
            else:
                print('Connection closed by server.')
                break
        except Exception as e:
            print(f'Error receiving data: {e}')
            break

def send_to_server(sock):
    while True:
        try:
            line = input()
            if line:
                line += '\r\n'  # Ensure the line ends with \r\n
                sock.sendall(line.encode('utf-8'))
        except KeyboardInterrupt:
            print("\nDisconnected.")
            break
        except Exception as e:
            print(f'Error sending data: {e}')
            break

def main():
    try:
        # Create a socket object
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
            # Connect to the server
            sock.connect((server_address, server_port))
            print(f'Connected to {server_address}:{server_port}')
            
            # Send initial lines
            for line in initial_lines:
                sock.sendall(line.encode('utf-8'))
            
            # Start threads for sending and receiving
            receive_thread = threading.Thread(target=receive_from_server, args=(sock,))
            send_thread = threading.Thread(target=send_to_server, args=(sock,))
            
            receive_thread.start()
            send_thread.start()
            
            send_thread.join()  # Wait for the send_thread to finish
            sock.close()        # Close the socket when done
            receive_thread.join()  # Ensure receive_thread finishes before exiting

    except Exception as e:
        print(f'An error occurred: {e}')

if __name__ == '__main__':
    main()
