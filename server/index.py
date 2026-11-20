from server.register import Endpoint, registerEndpoint, registerGroup


@registerEndpoint("/")
class Index(Endpoint):
    def do(self):
        self.handler.send_header("Content-Type", "text/html")
        return open("index.html", "rb").read()

@registerEndpoint("/create")
class Create(Endpoint):
    def do(self):
        self.handler.send_header("Content-Type", "text/html")
        return open("pages/create.html", "rb").read()

@registerGroup("/assets")
class Assets(Endpoint):
    def do(self):
        if self.path.endswith(".css"):
            self.handler.send_header("Content-type", "text/css")
        else:
            self.handler.send_header("Content-type", "application/octet-stream")
        return open(self.path[1:], "rb").read()