# Installation

Copy _env.example.h_ to _env.h_. Set the three options in _.env_:

1. WiFi SSID to connect to
2. Password for the WiFi
3. Name of this garage door (you'll use this to access the web page)

Open _http-on-off/http-on-off.ino_, compile and upload this code to the Wemos D1. Wire the pushbutton input on the garage door to the relay's contacts (in my case, the two NO contacts on the relay shield).

# Assumptions

1. You're using the Wemos relay shield
2. Your search domain is _.local_. Substitute this in the URL you use to access the D1.

# Use

Once the D1 is installed and connected to wifi visit _name-of-garage-door.local_ in a browser. Hit the toggle link to active the garage door.

# Gotchas

- https://news.ycombinator.com/item?id=16964907
