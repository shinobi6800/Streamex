{
  "targets": [
    {
      "target_name": "streamx",
      "sources": [
        "src/streamx.cpp",
        "src/StreamServer.cpp",
        "src/StreamClient.cpp"
      ],
      "include_dirs": [
        "<!(node -p \"require('node-addon-api').include\")",
        "src"
      ],
      "defines": ["NAPI_CPP_EXCEPTIONS"],
      "cflags_cc!": ["-fno-exceptions"]
    }
  ]
}
