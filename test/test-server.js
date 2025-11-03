const { StreamServer, StreamClient } = require('../index');

// Start server
const server = new StreamServer(9000);
server.start();

// Start client
const client = new StreamClient("127.0.0.1", 9000);
client.startReceiving();

// Send data from client to server
setInterval(() => {
  client.send("Hello from client at " + new Date().toLocaleTimeString());
}, 2000);

// Broadcast data from server to all connected clients
setInterval(() => {
  server.broadcast("Broadcast message from server " + Date.now());
}, 3000);
