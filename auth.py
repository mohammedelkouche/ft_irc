import socket
import sys
import threading

# Server address and port
server_address = 'localhost'
server_port = 8080

# Initial lines to send
initial_lines = [
    'pass x\r\n',
    'nick sama\r\n',
    'user r r r r\r\n',
    'join #c,#p\r\n',
    # 'mode #c +k key\r\n'
    # 'mode #r +k key\r\n'
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
                line += '\r\n'
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
            
            send_thread.join()
            sock.close()
            receive_thread.join()

    except Exception as e:
        print(f'An error occurred: {e}')

if __name__ == '__main__':
    main()