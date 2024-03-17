
const url = 'wss://netwerkenbasis.com:8884'
const mqttID = generateID(10);      // randomly generated user id

const options = {                   // mqtt connection variables
  clean: true,
  connectTimeout: 4000,
  clientId: mqttID,
  username: 'student',
  password: 'welkom01',
  //cert: FileSystem.readFileSync('netwerkenbasis.crt'),
}

var container = document.getElementById('chat');

const client  = mqtt.connect(url, options)
client.on('connect', function () {
    console.log('Connected')
    client.subscribe('chat/message', function (err) {
        if (!err) {
            // Send message that this user enterd the chat`
            client.publish('chat/message', `${mqttID} joined the chat`);
        }
    })
})

client.on('message', function (topic, payload, packet) {
    console.log(`Topic: ${topic}, Message: ${payload.toString()}`)
    var newMessage = document.createElement('div');
    //const jsonPayload = JSON.parse(payload.toString());
    //var messageSender = jsonPayload.sender;
    //var messageString = jsonPayload.message;

    // do nothing when its the announement that the current user enterd the chat
    // if the messages comes from the current user -> put it on the right
    // if the message comes from another user      -> put it on the left
    if (payload.toString() === `${mqttID} joined the chat`){}
    else {
        newMessage.innerHTML = '<div class="message message-left"><b><u>' + "" + '</u></b><br/>' + payload.toString() + '</div>';
    }
    
    chat.appendChild(newMessage);
    window.scrollTo(0, document.body.scrollHeight);
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
    client.unsubscribe('chat/message')
    var newMessage = document.createElement('div');
    var message = document.getElementById("messageInput").value;
    if (message != ""){
        //var jsonMessage = '{"sender": "' + mqttID + '", "message": "' + message + '"}';    
        client.publish('chat/message', message);
        document.getElementById("messageInput").value = "";
    }
    newMessage.innerHTML = '<div class="message message-right"><b><u>' + mqttID + '</u></b><br/>' + message + '</div>';
    chat.appendChild(newMessage);
    client.subscribe('chat/message')
}
