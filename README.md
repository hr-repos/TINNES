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

## [Assignment 2: ESP webbot](assignment_2/README.md)

Het bedrijf voor wie je aan het werk bent, is zeer tevreden met de chat applicatie die je hebt
gebouwd. Het is nu enkele maanden later en het bedrijf is dankzij jouw applicatie enorm
gegroeid in waarde. Er wordt geschat dat het bedrijf nu een waarde heeft van ruim €
500.000,-. Het bedrijf heeft jouw voor de applicatie rijkelijk betaald en is zich nu aan het
verdiepen in de wondere wereld van IoT. Ze willen graag eigen hardware ontwikkelen en
hebben contracten gesloten met Espressif (het bedrijf achter de ESP32/ESP8266
Microcontrollers ) en met Arduino. Dankzij deze contracten mag het bedrijf winst maken
door gebruik maken van de producten van deze bedrijven. Het bedrijf heeft echter jouw
kennis nodig om een prototype te maken met een ESP32 of ESP8266. Hierop moet code
draaien dat is geschreven in Arduino. Het bedrijf wil graag dat de hardware inhaakt op de
geweldige chat applicatie. Hij heeft voor jouw de volgende opdracht klaar staan:

"Maak van een ESP32 of ESP8266 microcontroller een chatbot. Deze chatbot moet de
temperatuur en vochtigheid sturen in de chat wanneer daar om gevraagd wordt door een
chat gebruiker. Daarnaast moet een simpele LED aan en uit gezet kunnen worden."

Uiteraard is het nog steeds van belang dat alle berichten veilig gestuurd worden. Denk ook
hier dus goed over na. De systeembeheerder was blij met de eenvoudige setup van de
vorige opdracht en heeft een broker nu op een vaste plek staan ( netwerkenbasis.com ). De
server waar deze broker staat heeft in totaal twee services draaien. Hierop staan de
volgende poorten open:

- MQTT-broker
    - `8883` -> MQTT (beveiligd met gebruikersnaam en wachtwoord + TLS)
    - `8884` -> MQTT over WebSockets (beveiligd via SSL ( `wss://` ))
    
- Webserver  
    - `80` -> Redirect van HTTP naar HTTPS
    - `443` -> Test-interface beveiligd via SSL en met een gebruikersnaam en
wachtwoord ( <gebruikersnaam>:<wachtwoord> het gaat hier dus om de scheiding
met een " : ")


Het is nu natuurlijk zo dat iedereen op dezelfde MQTT-broker berichten gaat sturen. Om met
elkaar te kunnen communiceren moet een standaard topic worden gekozen waar de
berichten op geplaatst worden. De systeembeheerder heeft je hierbij geholpen en heeft de
keuze al voor je gemaakt. De topic is chat/message hierop worden standaard text berichten
geplaatst. Dit is geen JSON of iets dergelijks. Het bericht wat er op geplaatst wordt, is
letterlijk het bericht dat op de test-interface te zien is.  

Daarnaast wil de opdrachtgever ook dat de interface die je bij opdracht 1 hebt gemaakt,
aanpast zodat hij kan verbinden en communiceren met de broker van de systeembeheerder.
Deze aangepaste versie van jouw interface dient ook te worden opgeleverd.