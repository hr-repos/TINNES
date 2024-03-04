
const url = 'ws://localhost:1884'
const mqttID = generateID(10);      // randomly generated user id

const options = {                   // mqtt connection variables
  clean: true,
  connectTimeout: 4000,
  clientId: mqttID,
  username: 'webserver',
  password: 'h$!8o$#E*7&f6WU',
}

var container = document.getElementById('chat');

const client  = mqtt.connect(url, options)
client.on('connect', function () {
    console.log('Connected')
    client.subscribe('test', function (err) {
        if (!err) {
            // Send message that this user enterd the chat`
            client.publish('test', '{"sender": "' + mqttID + '", "message": "--enterd the chat--"}');
        }
    })
})

client.on('message', function (topic, payload, packet) {
    console.log(`Topic: ${topic}, Message: ${payload.toString()}`)
    var newMessage = document.createElement('div');
    const jsonPayload = JSON.parse(payload.toString());
    var messageSender = jsonPayload.sender;
    var messageString = jsonPayload.message;

    // do nothing when its the announement that the current user enterd the chat
    // if the messages comes from the current user -> put it on the right
    // if the message comes from another user      -> put it on the left
    if (messageString === '--enterd the chat--' && messageSender===mqttID){}
    else if (messageSender == mqttID){
        newMessage.innerHTML = '<div class="message message-right"><b><u>' + messageSender + '</u></b><br/>' + messageString + '</div>';
    }
    else {
        newMessage.innerHTML = '<div class="message message-left"><b><u>' + messageSender + '</u></b><br/>' + messageString + '</div>';
    }
    chat.appendChild(newMessage);
})

// create a random id from all lowercase and uppercase letters and all numbers
function generateID(idLength) {
    var characters = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789';
    var id = '';
    for (let i = 0; i < idLength; i++){
        id += characters.charAt(Math.floor(Math.random() * characters.length));
    }
    return id;
}

// send the message and clear the text box
function sendMessage(){
    var message = document.getElementById("messageInput").value;
    if (message != ""){
        var jsonMessage = '{"sender": "' + mqttID + '", "message": "' + message + '"}';    
        client.publish('test', jsonMessage);
        document.getElementById("messageInput").value = "";
    }
}
