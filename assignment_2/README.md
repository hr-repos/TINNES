
# SSL protected web chat app using MQTT

## ESP webbot
The ESP is connected to the given MQTT server at netwerkenbasis.com.
The ESP webbot only listens when the message starts with 'BOT-1051997'.

The following commands can be used:
- <u>BOT-1051997: test</u>     
answer: Test message received
- <u>BOT-1051997: temperatuur</u>  
answer: BOT-1051997: temperature is now XX.XX°C.
- <u>BOT-1051997: vochtigheid</u>  
answer: BOT-1051997: humidity is now XX.XX%.
- <u>BOT-1051997: alle gegevens</u>  
answer: BOT-1051997: temperature is now XX.XX°C. Humidity is now XX.XX%.
- <u>BOT-1051997: led:aan</u>  
answer: BOT-1051997: led is now on  
action: turns the built in led of the esp on
- <u>BOT-1051997: led:uit</u>  
answer: BOT-1051997: led is now off  
action: turns the built in led of the esp off
- <u>BOT-1051997: \<anything else></u>  
answer: BOT-1051997: message not recognised

## SSL protected web chat app using MQTT
The website is hosted using nginx in a docker container. It
uses self signed ssl certificates to use https. The container port 443 is bridged to the same localhost port.

The chat uses the MQTT protocol to automatically subscribe to a predefined topic and has a text box to publish a message to the chat.

When a user enters the chat when going to https://localhost a message is send to already connected users to notify them. 

Each user which uses this webpage is identified by a randomized username of 10 characters which changes each time a user (re)joins the chat.

## How to start the webserver
```bash
# docker and docker-compose need to be installed and running
cd assignment_2
docker-compose up -d
```
