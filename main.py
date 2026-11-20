from pathlib import Path
import socketserver
from urllib.parse import parse_qs, urlparse
import json, os, subprocess, threading
from http.server import ThreadingHTTPServer, SimpleHTTPRequestHandler
from server.engine import start_engine
from server.register import endpoins
import server.index
import server.api


PORT=int(os.environ.get("HANOI_PORT","8090"))

class Handler(SimpleHTTPRequestHandler):
    def end_headers(self):
        self.send_header("Access-Control-Allow-Origin","*")
        self.send_header("Access-Control-Allow-Headers","Content-Type")
        self.send_header("Access-Control-Allow-Methods","GET,POST,OPTIONS")
        super().end_headers()
    def do_GET(self) -> None:
        param = urlparse(self.path)
        # print(param)
        print(parse_qs(param.query))
        # print(segments)
        target = next((i for i in endpoins if i.matcher.isMatch(param.path)), None)
        if (target):
            instance = target()
            instance.path = param.path
            instance.handler = self
            instance.params = parse_qs(param.query)
            self.send_response(200)
            response = instance.do()
            # self.send_header("Content-type", "text/html")
            # print(self.headers)
            self.end_headers()
            self.wfile.write(response)
            # return response
        else:
            self.send_response(404, "")
            self.wfile.write("".encode("utf-8"))
    def do_POST(self) -> None:
        param = urlparse(self.path)
        # print(param)
        print(parse_qs(param.query))
        target = next((i for i in endpoins if i.matcher.isMatch(param.path)), None)
        if (target):
            instance = target()
            instance.path = param.path
            instance.handler = self
            instance.params = parse_qs(param.query)
            self.send_response(200)
            response = instance.do()
            # self.send_header("Content-type", "text/html")
            # print(self.headers)
            self.end_headers()
            self.wfile.write(response)
            # return response
        else:
            self.send_response(404, "")
            self.wfile.write("".encode("utf-8"))
            

if __name__ == "__main__":
    start_engine()

    # with socketserver.TCPServer(("", PORT), Handler) as httpd:
    #     print(f"Serving at port http://localhost:{PORT} with Custom Handler")
    #     httpd.serve_forever()
    # invoke("receive:Oi")
    print(f"listing on http://127.0.0.1:{PORT}")
    ThreadingHTTPServer(("127.0.0.1",PORT),Handler).serve_forever()
    # print(handle())