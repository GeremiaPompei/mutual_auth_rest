# mutual_auth_rest

## Intro
Piccolo programma utile per testare l'autenticazione mutuale tramite certificati. Per eseguire il test è stata usata come libreria *rest* sia lato client 
che server [cpp-httplib](https://github.com/yhirose/cpp-httplib). Questa è stata scelta perché fornisce l'uso di chiamate rest SSL sia lato client che server 
in modo agevole. Oltre a ciò essa è implementata in un unico file h, quindi per semplicità è stata fatta la scelta di aggiungere l'unico file al programma.

Vi è lo script linux [generate-keys.sh](https://github.com/GeremiaPompei/mutual_auth_rest/blob/master/generate_keys.sh) per generare le chiavi che servono per 
effettuare la mutua autenticazione.

## Funzionamento
Appena il programma viene attivato il terminale testa sia il client che il server **http** che il client e il server **https** effettuando dei **ping**. 
Essi vengono inviati ogni 2 secondi.

Nel frattempo è possibile accedere all'indirizzo [http://0.0.0.0:8080](http://0.0.0.0:8080) che mostrerè un pulsante per andare alla pagina 
[https://0.0.0.0:4443](https://0.0.0.0:4443). Ciò sarà possibile solamente se il client importerà nel browser il file **client.p12** all'interno della cartella 
**client**.
