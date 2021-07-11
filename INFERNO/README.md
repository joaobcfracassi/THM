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

### 

