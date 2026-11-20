import json
from typing import Any

from server.data.patient import Patient
from server.engine import handle, invoke
from server.register import Endpoint, registerEndpoint


@registerEndpoint("/api/create")
class CreateEndpoint(Endpoint):
    def do(self) -> Any:
        self.handler.send_header("Content-Type", "text/plain")
        try:
            raw = self.handler.rfile.read(int(self.handler.headers.get("Content-Length","0")))
        
            data = json.loads(raw or b"{}")
            patient = Patient()
            patient.from_json(data)
            invoke(f"create:{patient.to_message()}")
            response = handle()
        
            return response.encode("utf-8")
        except Exception as e:
            print(e)
            return b""

@registerEndpoint("/api/update")
class UpdateEndpoint(Endpoint):
    def do(self) -> Any:
        self.handler.send_header("Content-Type", "text/plain")
        try:
            raw = self.handler.rfile.read(int(self.handler.headers.get("Content-Length","0")))
        
            data = json.loads(raw or b"{}")
            patient = Patient()
            patient.from_json(data)
            message = f"update:{self.params["id"][0]},{patient.to_message()}"
            # print():
            invoke(f"update:{self.params["id"][0]},{patient.to_message()}")
            response = handle()
            
            return response.encode("utf-8")
        except Exception as e:
            print(e)
            return b""


@registerEndpoint("/api/read")
class ReadEndpoint(Endpoint):
    def do(self) -> Any:
        self.handler.send_header("Content-Type", "application/json")
        try:
            invoke(f"read:{self.params.get("order",["position"])[0]},{self.params.get("query",[""])[0]},({",".join(self.params.get("filters", []))})")
            message = handle()
            tests: list[Patient] = []
            while (message != "end" and message != ""):
                if not message.startswith("start:") and message != "":
                    instance = Patient()
                    instance.from_message(message)
                    tests.append(instance)
                message= handle()
            
            return json.dumps([i.to_json() for i in tests]).encode("utf-8")
        except Exception as e:
            print( e)
            return b"[]"

@registerEndpoint("/api/delete")
class DeleteEndpoint(Endpoint):
    def do(self) -> Any:
        self.handler.send_header("Content-Type", "text/plain")
        try:
            raw = self.handler.rfile.read(int(self.handler.headers.get("Content-Length","0")))
        
            data = json.loads(raw or b"{}")
            invoke(f"delete:{data["target"]}")
            message = handle()
            
            return message.encode("utf-8")
            # return json.dumps([i.to_json() for i in tests]).encode("utf-8")
        except Exception as e:
            print( e)
            return "não foi encontradao".encode("utf-8")