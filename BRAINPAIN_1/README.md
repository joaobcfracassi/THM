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

### 
