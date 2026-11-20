from abc import ABC
from dataclasses import dataclass
import datetime
from operator import concat

# def splitFirst(char *original, char character): tuple[str, str] {
#   result: tuple[str, str] = ["", ""];
#   result[0] = malloc(strlen(original));
#   result[1] = malloc(strlen(original));
#   int headSize = 0;
#   int tailSize = 0;
#   int size = strlen(original);
#   int found = 0;
#   for (int i = 0; i < size; i++) {
#     if (!found && original[i] == character) {
#       found = 1;
#     } else if (found) {
#       result[1][tailSize] = original[i];
#       tailSize++;
#     } else {
#       result[0][headSize] = original[i];
#       headSize++;
#     }
#   }

#   result[1][tailSize] = 0;
#   result[0][headSize] = 0;

#   return result;
# }

class Entity(ABC):
    def convert_message(self, segments: list[str]) -> None: ...
    def from_message(self, message: str) -> None : 
        segments: list[str] = []

        content= message

        while True:
            result = content.split(",", 1)
            segments.append(result[0])
            if len(result) == 1:
                break
            else:
                content = result[1]
        self.convert_message(segments)

    def from_json(self, dict: dict)-> None :...
    def to_json(self) -> dict: ...

    def to_message(self)-> str: ...

class Patient(Entity):
    id: int
    name: str
    condition: str
    condition_priority: int
    date: datetime.datetime
    position: int

    def convert_message(self, segments: list[str]):
        self.name = segments[0]
        self.condition = segments[1]
        self.condition_priority = int(segments[2])
        self.position = int(segments[3])
        self.id = int(segments[4])
        # self.dat

    def from_json(self, dict: dict):
        self.name = dict["name"]
        self.condition = dict["condition"]
        self.condition_priority = dict["conditionPriority"]
        self.position = 0
        # self.position = dict["position"]
        # self.date = dict["quantity"]

    def to_json(self) -> dict:
        result: dict = {
            "name": self.name,
            "condition": self.condition,
            "conditionPriority": self.condition_priority,
            "position": self.position,
            "id": self.id
        }
        return result

    def to_message(self):
        return f"{self.name},{self.condition},{self.condition_priority}"
