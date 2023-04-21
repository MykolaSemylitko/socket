
import socket
import time

def main():
    sock = socket.socket(socket.AddressFamily.AF_INET, socket.SOCK_STREAM)
    # sock.bind(('127.0.0.1', 55555))
    server_addr = ('127.0.0.1', 40405)
    sock.connect(server_addr)

    while True:
        try:
            msg = input("message:")
            sock.send(msg.encode())
        except:
            print('end')
            break
        
        # time.sleep(1)
    print('done')

if __name__ == "__main__":
    main()
