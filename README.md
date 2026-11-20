# Execução

O sistema pode ser executado de duas maneiras diferentes, cada uma com sua própria interface

## web

para executar a interface web é necessário compilar o código c e dar inicio ao servidor python

linux
```
gcc -o main main.c && python main.py
```

windows
```
gcc -o main.exe main.c

python main.py
```

após isso entre no seu navegador e abra uma página em http://localhost:8090, ou siga o link que aparecerá em seu terminal

## terminal

para usar apenas a interface de terminal, basta compilar e todar 

linux
```
gcc -o main main.c && ./main
```

windows
```
gcc -o main.exe main.c

./main.exe
```