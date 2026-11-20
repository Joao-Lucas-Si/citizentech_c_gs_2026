from typing import Any, Type
from http.server import ThreadingHTTPServer, SimpleHTTPRequestHandler


def registerEndpoint(url: str):
    def decorator(cls: Type[Endpoint]):
        cls.matcher = EndPointExactMatcher(url)
        endpoins.append(cls)

    return decorator


def registerGroup(preffix: str):
    def decorator(cls: Type[Endpoint]):
        cls.matcher = EndPointPreffixMatcher(preffix)
        endpoins.append(cls)

    return decorator


class EndPointMatcher:
    def isMatch(self, path: str) -> bool: ...


class EndPointExactMatcher(EndPointMatcher):
    target: str

    def __init__(self, target: str) -> None:
        self.target = target

    def isMatch(self, path: str) -> bool:
        return path == self.target

class EndPointPreffixMatcher(EndPointMatcher):
    preffix: str

    def __init__(self, target: str) -> None:
        self.preffix = target

    def isMatch(self, path: str) -> bool:
        return path.startswith(self.preffix)


class Endpoint:
    handler: SimpleHTTPRequestHandler
    path: str
    params: dict

    matcher: EndPointMatcher

    def do(self) -> Any: ...


endpoins: list[Type[Endpoint]] = []
