import os
from pathlib import Path
import subprocess
import threading


BASE=Path(__file__).resolve().parents[0]
FRONTEND=BASE/"frontend"
ENGINE=BASE/".."/("main.exe" if os.name=="nt" else "main")

engine: subprocess.Popen[str] = None  # pyright: ignore[reportAssignmentType]
lock=threading.Lock()

def start_engine():
    global engine
    if not ENGINE.exists(): return False
    if engine is None or engine.poll() is not None:
        engine=subprocess.Popen([str(ENGINE), "--engine"],stdin=subprocess.PIPE,stdout=subprocess.PIPE,stderr=subprocess.PIPE,text=True,bufsize=1)
    return True

def handle() -> str:
    result = engine.stdout.readline().strip()  # pyright: ignore[reportOptionalMemberAccess]
    # print(f"engine: {result}")
    return result

def invoke(content: str):
    # print(f"engine message: {content}")
    engine.stdin.write(content + "\n") # pyright: ignore[reportOptionalMemberAccess]
    engine.stdin.flush() # pyright: ignore[reportOptionalMemberAccess]
