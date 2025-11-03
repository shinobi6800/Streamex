

---

# ⚡ StreamEX

> A **high-performance Node.js streaming library** built with **C++** and **Boost.Asio**, designed for low-latency, bidirectional data streaming between clients and servers.
> StreamX bridges native C++ networking with the JavaScript ecosystem via the **Node-API (N-API)** interface.

---

## 🚀 Features

* 🔥 **Ultra-fast TCP streaming** using Boost.Asio
* 🧩 **Native Node.js Addon** (C++ with N-API)
* 🧠 **Async client/server** architecture
* 🪶 Lightweight & zero dependencies (besides Boost and Node-API)
* 🛡️ Cross-platform: Windows, Linux, macOS
* 🧵 Multi-threaded event loop
* 🔧 Easy integration with any Node.js project

---

## 🧱 Project Structure

```
streamx/
│
├── binding.gyp            # Node-gyp build configuration
├── package.json           # Node package file
├── README.md              # Documentation
│
└── src/
    ├── streamx.cpp        # Node addon entry point (N-API exports)
    ├── StreamServer.cpp   # Core C++ TCP server
    ├── StreamClient.cpp   # Core C++ TCP client
    └── StreamCommon.hpp   # Shared utilities and headers
```

---

## ⚙️ Requirements

### 🧩 Node.js & Compiler

* **Node.js** ≥ 18.x
* **npm** ≥ 9.x
* **C++17** or newer compiler

  * Linux: `g++` or `clang++`
  * Windows: MSVC (Visual Studio Build Tools)

### ⚙️ Libraries

* [**Boost.Asio**](https://www.boost.org/doc/libs/release/doc/html/boost_asio.html)
* [**Node-API**](https://nodejs.org/api/n-api.html)

---

## 📦 Installation

### 🐧 Linux / macOS

#### 1. Install Boost

```bash
# Arch Linux
sudo pacman -S boost

# Ubuntu / Debian
sudo apt install libboost-all-dev
```

#### 2. Clone the repo

```bash
git clone https://github.com/yourusername/streamx.git
cd streamx
```

#### 3. Install dependencies

```bash
npm install
```

#### 4. Build the native addon

```bash
npm run build
```

or manually:

```bash
npx node-gyp configure build
```

---

### 🪟 Windows

#### 1. Install Visual Studio Build Tools

* Install **Desktop development with C++**
* Make sure `cl.exe` is on your PATH

#### 2. Install Boost via [vcpkg](https://github.com/microsoft/vcpkg)

```bash
vcpkg install boost-asio
```

#### 3. Configure build

```bash
npm install
npm run build
```

If Boost is not in a standard location, edit `binding.gyp`:

```json
"include_dirs": [
  "<!(node -p \"require('node-addon-api').include\")",
  "C:/path/to/boost"
]
```

---

## 🧩 Usage Example

```js
const streamx = require('./build/Release/streamx.node');

// Start a server
const server = new streamx.StreamServer(8080);
server.on('data', (clientId, data) => {
  console.log(`[Server] Received from ${clientId}:`, data);
  server.send(clientId, "Hello from server!");
});

// Start a client
const client = new streamx.StreamClient('127.0.0.1', 8080);
client.on('data', (data) => {
  console.log('[Client] Received:', data);
});

client.send('Hello from client!');
```

---

## 🔧 Build Commands

| Command           | Description              |
| ----------------- | ------------------------ |
| `npm run build`   | Build addon via node-gyp |
| `npm run rebuild` | Clean + rebuild addon    |
| `npm run test`    | Run JS tests (optional)  |

---

## 🧠 Internals

StreamX uses:

* `boost::asio::ip::tcp::socket` for asynchronous I/O
* Thread-safe message queues for sending/receiving data
* N-API for bridging Node.js and C++ efficiently
* Separate event loops for network I/O and JS event dispatching

---

## 🧰 Troubleshooting

### ❌ `fatal error: boost/asio.hpp: No such file or directory`

→ Boost is not found by your compiler.
Fix: Add include path to `binding.gyp`:

```json
"include_dirs": [
  "<!(node -p \"require('node-addon-api').include\")",
  "/usr/include/boost"   // Adjust as needed
]
```

### ❌ `undefined symbol: napi_register_module_v1`

→ Node-API version mismatch.
Fix: Rebuild using the correct Node version:

```bash
npx node-gyp rebuild --target=$(node -v)
```

---

## 🧠 Future Ideas

* WebSocket layer for browser compatibility
* UDP streaming mode
* File transfer example
* Encryption (AES or RSA layer)
* Connection pooling

---

## 📜 License
MIT © 2025 **Miranda Nigel**



