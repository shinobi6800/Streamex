const streamx = require('node-gyp-build')(__dirname);

class StreamServer {
  constructor(port = 9000) {
    this.server = new streamx.StreamServer(port);
  }

  start() {
    console.log(`[StreamX] Server started on port`);
    this.server.start();
  }

  broadcast(data) {
    this.server.broadcast(data);
  }
}

class StreamClient {
  constructor(host = "127.0.0.1", port = 9000) {
    this.client = new streamx.StreamClient(host, port);
  }

  send(data) {
    this.client.send(data);
  }

  startReceiving() {
    this.client.startReceiving();
  }
}

module.exports = { StreamServer, StreamClient };
