import socket
import threading
from concurrent.futures import ThreadPoolExecutor
import time

HOST = '127.0.0.1'
PORT = 8080

# Helper: Send HTTP request
def send_http_request(method="GET", path="/trial.html", body="", headers=None, keep_alive=False):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((HOST, PORT))

    if headers is None:
        headers = {}

    headers.setdefault("Host", f"{HOST}:{PORT}")
    headers.setdefault("Connection", "keep-alive" if keep_alive else "close")

    if method in ["PUT", "POST"]:
        headers.setdefault("Content-Length", str(len(body)))

    header_str = "".join(f"{k}: {v}\r\n" for k, v in headers.items())
    request = f"{method} {path} HTTP/1.1\r\n{header_str}\r\n{body}"
    
    s.sendall(request.encode())

    # Read response
    response = b""
    try:
        while True:
            chunk = s.recv(4096)
            if not chunk:
                break
            response += chunk
    except Exception as e:
        print(f"[ERROR] Socket error: {e}")

    s.close()
    return response.decode(errors='ignore')


# Test cases
def test_basic_requests():
    print("[TEST] GET /trial.html")
    print(send_http_request("GET", "/trial.html"))

    print("[TEST] HEAD /trial.html")
    print(send_http_request("HEAD", "/trial.html"))

    print("[TEST] PUT /upload.txt")
    print(send_http_request("PUT", "/upload.txt", body="Sample file content."))

    print("[TEST] GET /upload.txt")
    print(send_http_request("GET", "/upload.txt"))

    print("[TEST] DELETE /upload.txt")
    print(send_http_request("DELETE", "/upload.txt"))

    print("[TEST] OPTIONS *")
    print(send_http_request("OPTIONS", "*"))

    print("[TEST] Invalid Path Traversal")
    print(send_http_request("GET", "/../../etc/passwd"))


def test_concurrent_requests(n=20):
    def worker(i):
        resp = send_http_request("GET", "/trial.html")
        print(f"[{i}] Length: {len(resp)} Status: {resp.splitlines()[0]}")

    with ThreadPoolExecutor(max_workers=10) as pool:
        pool.map(worker, range(n))


def test_keep_alive():
    s = socket.socket()
    s.connect((HOST, PORT))
    request = (
        "GET /trial.html HTTP/1.1\r\n"
        f"Host: {HOST}:{PORT}\r\n"
        "Connection: keep-alive\r\n\r\n"
    )
    s.sendall(request.encode())
    print(s.recv(4096).decode())

    request = (
        "GET /trial.html HTTP/1.1\r\n"
        f"Host: {HOST}:{PORT}\r\n"
        "Connection: close\r\n\r\n"
    )
    s.sendall(request.encode())
    print(s.recv(4096).decode())
    s.close()


if __name__ == "__main__":
    print("---- BASIC TESTS ----")
    test_basic_requests()
    print("---- CONCURRENCY TEST ----")
    test_concurrent_requests(n=50)
    print("---- KEEP-ALIVE TEST ----")
    test_keep_alive()

