# MTI: MagicTable Input

MTI is an arduino program + python file used to interface with A Pimoroni Skywriter and send data over serial to a Python script. The script will then send data to a running [node-sonos-http-api](https://github.com/jishi/node-sonos-http-api) server.

# Commands

| Skywriter Input | Sonos Command |
| ----------------| ------------- |
| Tap (anywhere) | `play/pause` | 
| Flick from right to left | `next` |
| Flick from left to right | `previous` |
| Airwheel clockwise | `volume up` |
| Airwheel anticlockwise | `volume down` |
