# TINNES: Netwerken en Security vervolg

## [Assignment 1: SSL protected web chat app using MQTT](assignment_1/README.md)

Je bent werkzaam als systeem-engineer en je maakt zelf een simpele chat web-applicatie.

Je bent slim genoeg om te bedenken dat je een front-end en een message-broker nodig hebt.  
Ook weet je dat je applicatie moet gaan draaien op een Linux-server waarop docker draait.  
Volgens de opdrachtgever ben je verplicht MQTT te gebruiken als message-broker.  
Jij weet dat een MQTT-broker kan werken via web-sockets.  

De systeembeheerder heeft aangegeven dat er ook nog meer applicaties draaien die een aantal poorten
gebruiken.
De systeembeheerder heeft nog wel genoeg poorten over en geeft jouw poort ```1884``` , ```1883``` , ```80``` en ```443``` .

- Belangrijk is dat het makkelijk moet zijn om het project op te zetten. Dit betekent dat er gebruikt dient te worden gemaakt van een Docker compose bestand.
- Nog belangrijker is dat jouw applicatie wel veilig moet zijn! Denk hierbij dus na over het gebruik van
encryptie (SSL). 
- De front-end (web-app) moet beschikken over een zelf gegenereerd SSL-certificaat die gekoppeld is
aan jouw studentnummer, waardoor je er veilig mee kan verbinden en berichten kan uitwisselen.
- De MQTT-broker moet ook nog worden beveiligd, dit mag je doen via SSL of met een gebruikersnaam
en wachtwoord
- De gebruiker moet zien welke berichten hij zelf heeft verstuurd.

De applicatie is gemaakt voor nerds. Dit betekent dat de berichten niet mogen worden opgeslagen en alleen
de berichten getoond mogen worden die zijn verstuurd sinds de gebruiker begint met luisteren.

De opdrachtgever heeft niet veel kaas gegeten van hoe zo'n systeem in elkaar zit.
Belangrijk is dan ook dat bij het product een netwerk-diagram aanwezig is, waarin de opdrachtgever in één
overzicht kan zien hoe alles aan elkaar zit verbonden (IP-adres, poorten, containers, etc.).
Deze dient te worden ingeleverd als .png of .pdf .
Daarnaast moet ook voor de systeembeheerder duidelijk zijn hoe het systeem dient te worden opgestart.